// Package graphics turns the raw graphic and palette facts reported by the
// gfx bank and palette def handlers into asset config entries with exact
// boundaries, and classifies the data left between them.
package graphics

import (
	"fmt"
	"sort"

	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/datarange"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/sotn"
)

type Args struct {
	Data        []byte
	RamBase     psx.Addr
	Graphics    []assets.InfoGraphic
	Palettes    []assets.InfoPalette
	RegionStart psx.Addr // first address of the region; zero means "first known entry"
	RegionEnd   psx.Addr // first address after the region
	// Claimed are ranges other handlers already explain. A gap overlapping one
	// of them is left alone: some overlays keep a palette or two down among the
	// header structures, and without this the span between such a palette and
	// the first real graphic would be "explained" as image data when it is
	// actually the headers themselves.
	Claimed []datarange.DataRange
}

// rawShape is a candidate raw image size used only when guessing what an
// unreferenced gap contains. Restricted to shapes that actually occur in
// stage overlays in config/assets.us.yaml: widening this set weakens rule 2,
// so additions should be weighed rather than assumed.
type rawShape struct {
	width  int
	height int
	bpp    int
}

var rawShapes = []rawShape{
	{48, 72, 8}, // character portraits
}

func (s rawShape) size() int { return s.width * s.height * s.bpp / 8 }

// bppForKind maps a gfx bank kind to its bit depth. Kind 4 is compressed and
// always 4bpp once inflated.
func bppForKind(kind uint32) (bpp int, compressed bool, ok bool) {
	switch kind {
	case 1:
		return 4, false, true
	case 2:
		return 8, false, true
	case 3:
		return 16, false, true
	case 4:
		return 4, true, true
	}
	return 0, false, false
}

func Classify(a Args) ([]assets.InfoAssetEntry, datarange.DataRange, error) {
	var entries []assets.InfoAssetEntry

	// palettes first: their address and length are both exact
	for _, p := range a.Palettes {
		e := assets.InfoAssetEntry{
			DataRange: datarange.FromAddr(p.Addr, p.Length),
			Kind:      "palette",
			Name:      fmt.Sprintf("pal_%X", p.Addr.Real(a.RamBase)),
			Args:      "16",
		}
		if p.ClutID >= 0 {
			e.Comment = fmt.Sprintf("0x%X", p.ClutID)
		}
		entries = append(entries, e)
	}

	// then referenced graphics, whose dimensions come from the bank entry
	for _, g := range a.Graphics {
		bpp, compressed, ok := bppForKind(g.Kind)
		if !ok {
			continue // empty or terminator bank carries no image
		}
		off := g.Addr.Real(a.RamBase)
		if off < 0 || off >= len(a.Data) {
			continue
		}
		name := fmt.Sprintf("gfx_%X", off)
		args := fmt.Sprintf("%d, %d, %d", g.Width, g.Height, bpp)
		if !compressed {
			entries = append(entries, assets.InfoAssetEntry{
				DataRange: datarange.FromAddr(g.Addr, g.Width*g.Height*bpp/8),
				Kind:      "rawgfx",
				Name:      name,
				Args:      args,
			})
			continue
		}
		size, inflated, ok := sotn.InflateSize(a.Data[off:])
		if !ok {
			// a bank said this is compressed but the stream does not decode
			entries = append(entries, assets.InfoAssetEntry{
				DataRange: datarange.FromAddr(g.Addr, 4),
				Kind:      "cmpgfx",
				Name:      name,
				Args:      args,
				Comment:   "unknown size: stream does not decode, please double-check",
			})
			continue
		}
		e := assets.InfoAssetEntry{
			DataRange: datarange.New(g.Addr, g.Addr.Sum(size).Align4()),
			Kind:      "cmpgfx",
			Name:      name,
			Args:      args,
		}
		// the inflated length must match the dimensions the bank declared;
		// disagreement means one of the two facts is wrong
		if want := g.Width * g.Height * bpp / 8; inflated != want {
			e.Comment = fmt.Sprintf("inflates to 0x%X, expected 0x%X for %dx%d %dbpp, please double-check",
				inflated, want, g.Width, g.Height, bpp)
		}
		entries = append(entries, e)
	}

	if len(entries) == 0 {
		return nil, datarange.DataRange{}, nil
	}
	sortEntries(entries)

	// everything not claimed above is unreferenced: probe each gap
	entries = append(entries, classifyGaps(a, entries)...)
	sortEntries(entries)

	// built directly, not via MergeDataRanges, which panics on the gaps this
	// function exists to report
	return entries, spannedRegion(a, entries), nil
}

// spannedRegion is the one blob the splat config needs for the graphics and
// palette data. It spans the recognized entries at or above RegionStart, since
// an overlay may park a palette down among the header structures and those are
// described by the surrounding splat entries. Leading and trailing skips are
// excluded: a skip means the contents are unknown, so folding one into this
// blob would claim it as graphics data on no evidence.
func spannedRegion(a Args, entries []assets.InfoAssetEntry) datarange.DataRange {
	var region datarange.DataRange
	for _, e := range entries {
		if e.Kind == "skip" || e.DataRange.Begin() < a.RegionStart {
			continue
		}
		if region.Empty() {
			region = e.DataRange
			continue
		}
		region = datarange.New(region.Begin(), e.DataRange.End())
	}
	return region
}

func sortEntries(entries []assets.InfoAssetEntry) {
	sort.Slice(entries, func(i, j int) bool {
		return entries[i].DataRange.Begin() < entries[j].DataRange.Begin()
	})
}

// classifyGaps finds every span between known entries and tries to explain it.
func classifyGaps(a Args, known []assets.InfoAssetEntry) []assets.InfoAssetEntry {
	var out []assets.InfoAssetEntry
	cursor := known[0].DataRange.Begin()
	if a.RegionStart != 0 && a.RegionStart < cursor {
		cursor = a.RegionStart
	}
	var prev *assets.InfoAssetEntry
	for i := range known {
		e := &known[i]
		if cursor < e.DataRange.Begin() {
			out = append(out, a.explainUnclaimed(cursor, e.DataRange.Begin(), prev, e)...)
		}
		if e.DataRange.End() > cursor {
			cursor = e.DataRange.End()
		}
		prev = e
	}
	if a.RegionEnd != 0 && cursor < a.RegionEnd {
		out = append(out, a.explainUnclaimed(cursor, a.RegionEnd, prev, nil)...)
	}
	return out
}

// explainUnclaimed drops the parts of a span that another handler describes and
// explains what is left. A gap can straddle claimed data: in LIB the span below
// the first bank entry covers the layer and cutscene headers as well as an
// image only C code refers to.
func (a Args) explainUnclaimed(begin, end psx.Addr, prev, next *assets.InfoAssetEntry) []assets.InfoAssetEntry {
	var out []assets.InfoAssetEntry
	for _, span := range a.unclaimedSpans(begin, end) {
		// only a span touching an original edge can trust that neighbour: an
		// inner span is bounded by claimed data, not by prev or next
		p, n := prev, next
		if span.Begin() != begin {
			p = nil
		}
		if span.End() != end {
			n = nil
		}
		out = append(out, explainGap(a, span.Begin(), span.End(), p, n)...)
	}
	return out
}

// unclaimedSpans splits [begin, end) around every range another handler owns.
func (a Args) unclaimedSpans(begin, end psx.Addr) []datarange.DataRange {
	blockers := make([]datarange.DataRange, 0, len(a.Claimed))
	for _, c := range a.Claimed {
		if c.Begin() < end && begin < c.End() {
			blockers = append(blockers, c)
		}
	}
	sort.Slice(blockers, func(i, j int) bool {
		return blockers[i].Begin() < blockers[j].Begin()
	})
	var out []datarange.DataRange
	cursor := begin
	for _, b := range blockers {
		if b.Begin() > cursor {
			out = append(out, datarange.New(cursor, b.Begin()))
		}
		if b.End() > cursor {
			cursor = b.End()
		}
	}
	if cursor < end {
		out = append(out, datarange.New(cursor, end))
	}
	return out
}

// explainGap applies the gap rules in order, first match winning. prev and
// next are the known entries bracketing the gap, nil when the gap runs to a
// region edge.
func explainGap(a Args, begin, end psx.Addr, prev, next *assets.InfoAssetEntry) []assets.InfoAssetEntry {
	if entries, ok := gapAsUnusedPalettes(a, begin, end, prev, next); ok {
		return entries
	}
	if entries, ok := gapAsCompressedChain(a, begin, end); ok {
		return entries
	}
	if entries, ok := gapAsRawImages(a, begin, end); ok {
		return entries
	}
	if entries, ok := gapAsTrailingCompressed(a, begin, end); ok {
		return entries
	}
	return []assets.InfoAssetEntry{skipEntry(begin, end)}
}

func skipEntry(begin, end psx.Addr) assets.InfoAssetEntry {
	return assets.InfoAssetEntry{
		DataRange: datarange.New(begin, end),
		Kind:      "skip",
		Comment:   fmt.Sprintf("0x%X unreferenced bytes, unrecognized", begin.DistanceTo(end)),
	}
}

// maxChainScan bounds how far into a gap gapAsTrailingCompressed looks for the
// start of an image chain. Unreferenced images sit close to the boundary that
// corroborates them; scanning a huge gap word by word would cost more than the
// weak guesses it produced are worth.
const maxChainScan = 0x2000

// gapAsTrailingCompressed handles a gap whose leading bytes are something else
// but whose tail is compressed images. Only the gap end is a trusted boundary,
// so the scan runs forward from the start and keeps the earliest offset whose
// chain lands on it exactly.
//
// The start of that chain is a new boundary the leading bytes can be measured
// against, so they get one more pass through the rules rather than going
// straight to skip. In ST0 the whole gap is 0x20A8 and matches no shape, but
// below the trailing image sit 0x1B00 bytes: two 48x72 8bpp portraits.
func gapAsTrailingCompressed(a Args, begin, end psx.Addr) ([]assets.InfoAssetEntry, bool) {
	limit := begin.Sum(maxChainScan)
	if limit > end {
		limit = end
	}
	for cursor := begin.Align4(); cursor < limit; cursor = cursor.Sum(4) {
		if cursor == begin {
			continue // already tried by gapAsCompressedChain
		}
		entries, ok := gapAsCompressedChain(a, cursor, end)
		if !ok {
			continue
		}
		return append(explainLeading(a, begin, cursor), entries...), true
	}
	return nil, false
}

// explainLeading re-runs the rules on the bytes below a chain start. Only the
// raw shapes are retried: a compressed chain already failed to start at begin,
// recursing into gapAsTrailingCompressed would rediscover the same chain, and
// the unused-palette rule needs a palette on both sides, which a compressed
// image is not.
func explainLeading(a Args, begin, end psx.Addr) []assets.InfoAssetEntry {
	if entries, ok := gapAsRawImages(a, begin, end); ok {
		return entries
	}
	return []assets.InfoAssetEntry{skipEntry(begin, end)}
}

// gapAsUnusedPalettes claims a gap sitting between two known palettes. Both
// neighbours must be palettes: palette data lives at the tail of the overlay,
// so a gap bracketed on both sides is a palette no def refers to, whereas a
// gap next to a graphic could be anything.
func gapAsUnusedPalettes(a Args, begin, end psx.Addr, prev, next *assets.InfoAssetEntry) ([]assets.InfoAssetEntry, bool) {
	if prev == nil || next == nil || prev.Kind != "palette" || next.Kind != "palette" {
		return nil, false
	}
	const paletteSize = 0x20 // 16 colours at 2 bytes each
	total := begin.DistanceTo(end)
	if total <= 0 || total%paletteSize != 0 {
		return nil, false
	}
	return []assets.InfoAssetEntry{{
		DataRange: datarange.New(begin, end),
		Kind:      "palette",
		Name:      fmt.Sprintf("pal_%X", begin.Real(a.RamBase)),
		Args:      "16",
		Comment:   "guessed: unused, no palette def refers to it",
	}}, true
}

// cmpInflatedSize is what a compressed gfx bank image inflates to: 128x128 at
// 4bpp. Every compressed image in a stage overlay has these dimensions.
const cmpInflatedSize = 128 * 128 * 4 / 8

// gapAsCompressedChain walks one or more compressed images back to back. It
// only claims the gap if every walk inflates to a full image and the last one
// lands exactly on the gap end. Both checks are needed: InflateSize succeeds
// on arbitrary data, and rounding the end up to a 4-byte boundary means a
// stream finishing within 3 bytes of the gap end hits it by luck. Requiring
// the inflated size is what rejects those.
func gapAsCompressedChain(a Args, begin, end psx.Addr) ([]assets.InfoAssetEntry, bool) {
	var out []assets.InfoAssetEntry
	for cursor := begin; cursor < end; {
		off := cursor.Real(a.RamBase)
		if off < 0 || off >= len(a.Data) {
			return nil, false
		}
		size, inflated, ok := sotn.InflateSize(a.Data[off:])
		if !ok || inflated != cmpInflatedSize {
			return nil, false
		}
		next := cursor.Sum(size).Align4()
		if next <= cursor || next > end {
			return nil, false
		}
		out = append(out, assets.InfoAssetEntry{
			DataRange: datarange.New(cursor, next),
			Kind:      "cmpgfx",
			Name:      fmt.Sprintf("gfx_%X", off),
			Args:      fmt.Sprintf("%d, %d, %d", 128, 128, 4),
			Comment:   fmt.Sprintf("guessed: unreferenced, inflates to 0x%X", inflated),
		})
		cursor = next
	}
	if len(out) == 0 {
		return nil, false
	}
	return out, true
}

// gapAsRawImages splits a gap that divides evenly into a candidate raw shape.
func gapAsRawImages(a Args, begin, end psx.Addr) ([]assets.InfoAssetEntry, bool) {
	total := begin.DistanceTo(end)
	if total <= 0 {
		return nil, false
	}
	for _, shape := range rawShapes {
		size := shape.size()
		if size == 0 || total%size != 0 {
			continue
		}
		count := total / size
		out := make([]assets.InfoAssetEntry, 0, count)
		for i := 0; i < count; i++ {
			addr := begin.Sum(i * size)
			out = append(out, assets.InfoAssetEntry{
				DataRange: datarange.FromAddr(addr, size),
				Kind:      "rawgfx",
				Name:      fmt.Sprintf("gfx_%X", addr.Real(a.RamBase)),
				Args:      fmt.Sprintf("%d, %d, %d", shape.width, shape.height, shape.bpp),
				Comment: fmt.Sprintf("guessed: unreferenced, size fits %dx%d %dbpp",
					shape.width, shape.height, shape.bpp),
			})
		}
		return out, true
	}
	return nil, false
}
