package paldef

import (
	"bytes"
	"encoding/binary"
	"encoding/json"
	"fmt"
	"io"
	"os"
	"path/filepath"
	"sort"
	"strings"

	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/datarange"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/sotn"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/util"
)

const palCopy = 1               // PAL_COPY
const palBulkCopy = 5           // PAL_BULK_COPY
const palTerminate = 0xFFFFFFFF // PAL_TERMINATE

type handler struct{}

var Handler = &handler{}

func (h *handler) Name() string { return "paldef" }

func (h *handler) Extract(e assets.ExtractArgs) error {
	r := bytes.NewReader(e.Data)
	defs, clutsOff, err := readPaletteDefs(r, e.RamBase, e.Start, e.End)
	if err != nil {
		return err
	}
	cluts, err := readClutsArray(r, e.RamBase, clutsOff, e.End, defs)
	if err != nil {
		return err
	}
	for i := range defs {
		resolveSymbols(&defs[i], e.Symbol, e.RamBase)
	}
	doc := paletteDefs{Cluts: cluts, Defs: defs}
	return util.WriteJsonFile(assetPath(e.AssetDir, e.Name), doc)
}

func (h *handler) Build(e assets.BuildArgs) error {
	data, err := os.ReadFile(assetPath(e.AssetDir, e.Name))
	if err != nil {
		return err
	}
	var doc paletteDefs
	if err := json.Unmarshal(data, &doc); err != nil {
		return err
	}
	content := strings.Builder{}
	content.WriteString("// clang-format off\n")
	// declare each referenced palette once; entries referenced by their base
	// keep the sized declaration so PAL_BULK's LEN() works, while palettes
	// referenced mid-array can only be declared as incomplete arrays
	declared := map[string]bool{}
	for _, def := range doc.Defs {
		for _, entry := range def.Entries {
			sym := util.RemoveFileNameExt(entry.Name)
			if !declared[sym] && entry.Offset == 0 {
				declared[sym] = true
				content.WriteString(fmt.Sprintf("extern u16* %s[0x%X];\n", sym, entry.Length))
			}
		}
	}
	for _, def := range doc.Defs {
		for _, ref := range append(append([]paletteEntry{}, def.Data...), def.Entries...) {
			sym := util.RemoveFileNameExt(ref.Name)
			if !declared[sym] {
				declared[sym] = true
				content.WriteString(fmt.Sprintf("extern u16 %s[];\n", sym))
			}
		}
	}
	for i, def := range doc.Defs {
		content.WriteString(fmt.Sprintf("static u_long* pal_def_%d[] = {\n", i))
		content.WriteString(fmt.Sprintf("    MAKE_PAL_OP(%s, %d),\n", palOpName(def.Kind), def.Freq))
		if def.Kind == palBulkCopy || def.Kind == palCopy {
			for _, entry := range def.Entries {
				if entry.Offset == 0 {
					content.WriteString(fmt.Sprintf("    PAL_BULK(0x%04X, %s),\n",
						entry.Destination, util.RemoveFileNameExt(entry.Name)))
				} else {
					content.WriteString(fmt.Sprintf("    PAL_COPY_DATA_(0x%04X, %s, 0x%X),\n",
						entry.Destination, symRef(entry.Name, entry.Offset), entry.Length))
				}
			}
		} else {
			content.WriteString(fmt.Sprintf("    (u_long*)0x%04X, (u_long*)0x%X,\n", def.Destination, def.Count))
			for _, ref := range def.Data {
				content.WriteString(fmt.Sprintf("    (u_long*)(%s),\n", symRef(ref.Name, ref.Offset)))
			}
		}
		content.WriteString("    PAL_TERMINATE(),\n")
		content.WriteString("};\n")
	}
	content.WriteString("u_long* cluts[] = {\n")
	for _, idx := range doc.Cluts {
		if idx < 0 || idx >= len(doc.Defs) {
			return fmt.Errorf("cluts index %d out of range", idx)
		}
		content.WriteString(fmt.Sprintf("    (u_long*)&pal_def_%d,\n", idx))
	}
	content.WriteString("};\n")
	return util.WriteFile(sourcePath(e.SrcDir, e.Name), []byte(content.String()))
}

func (h *handler) Info(a assets.InfoArgs) (assets.InfoResult, error) {
	r := bytes.NewReader(a.StageData)
	header, err := sotn.ReadStageHeader(r)
	if err != nil {
		return assets.InfoResult{}, err
	}
	boundaries := header.Cluts.Boundaries()
	clutsOff := header.Cluts.Real(boundaries.StageBegin)
	cluts, err := readClutsPointers(r, boundaries.StageBegin, clutsOff, len(a.StageData))
	if err != nil {
		return assets.InfoResult{}, err
	}
	if len(cluts) == 0 {
		return assets.InfoResult{}, fmt.Errorf("empty cluts array at %s", header.Cluts)
	}
	start := cluts[0]
	for _, addr := range cluts {
		if addr < start {
			start = addr
		}
	}
	defs, _, err := readPaletteDefs(
		r, boundaries.StageBegin, start.Real(boundaries.StageBegin), clutsOff)
	if err != nil {
		return assets.InfoResult{}, err
	}
	palDefRange := datarange.New(start, header.Cluts.Sum(len(cluts)*4))
	var splatEntries []assets.InfoSplatEntry
	for _, def := range defs {
		for _, entry := range def.Entries {
			splatEntries = append(splatEntries, assets.InfoSplatEntry{
				DataRange: datarange.FromAddr(entry.addr, entry.Length*2),
				Kind:      "pal",
				Name:      fmt.Sprintf("D_%08X", uint32(entry.addr)),
			})
		}
	}
	splatEntries = addGuessedUnusedPalettes(splatEntries)
	splatEntries = append(splatEntries, assets.InfoSplatEntry{
		DataRange: palDefRange,
		Name:      "header",
		Comment:   "palette definitions",
	})
	return assets.InfoResult{
		AssetEntries: []assets.InfoAssetEntry{
			{
				DataRange: palDefRange,
				Kind:      h.Name(),
				Name:      "palette_def",
			},
		},
		SplatEntries: splatEntries,
	}, nil
}

func assetPath(dir, name string) string {
	return filepath.Join(dir, fmt.Sprintf("%s.json", name))
}

func sourcePath(dir, name string) string {
	return filepath.Join(dir, fmt.Sprintf("gen/%s.h", name))
}

type paletteEntry struct {
	Destination int    `json:"destination,omitempty"`
	Length      int    `json:"length,omitempty"`
	Name        string `json:"name"`
	Offset      int    `json:"offset,omitempty"` // in u16 units from Name
	addr        psx.Addr
}

// one pal_def blob referenced by the cluts[] array; PAL_COPY and
// PAL_BULK_COPY carry (destination, length, data) triplets in Entries, the
// other ops carry a (destination, count) pair followed by data pointers
type paletteDef struct {
	Kind        int            `json:"kind"`
	Freq        int            `json:"freq,omitempty"`
	Destination int            `json:"destination,omitempty"`
	Count       int            `json:"count,omitempty"`
	Entries     []paletteEntry `json:"entries,omitempty"`
	Data        []paletteEntry `json:"data,omitempty"`
	addr        psx.Addr
}

type paletteDefs struct {
	// cluts[] content as indices into Defs, preserving the original order
	Cluts []int        `json:"cluts"`
	Defs  []paletteDef `json:"defs"`
}

// readPaletteDefs parses consecutive pal_def blobs starting at 'start' until
// the next word no longer looks like a palette op, which marks the beginning
// of the cluts[] pointer array. It returns the parsed defs and the offset
// where the cluts array starts.
func readPaletteDefs(r io.ReadSeeker, baseAddr psx.Addr, start, end int) ([]paletteDef, int, error) {
	var defs []paletteDef
	off := start
	for off < end {
		addr := baseAddr.Sum(off)
		if err := addr.MoveFile(r, baseAddr); err != nil {
			return nil, 0, fmt.Errorf("invalid offset: %w", err)
		}
		var op uint32
		if err := binary.Read(r, binary.LittleEndian, &op); err != nil {
			return nil, 0, fmt.Errorf("error reading palette op: %w", err)
		}
		kind := int(op & 0xFFFF)
		freq := int(op >> 16)
		// a palette op has a small kind and frequency, anything else is a
		// pointer and marks the beginning of the cluts[] array
		if kind < palCopy || kind > palBulkCopy || freq > 0xFF {
			break
		}
		def := paletteDef{Kind: kind, Freq: freq, addr: addr}
		if err := readPaletteEntries(r, baseAddr, addr, &def); err != nil {
			return nil, 0, err
		}
		cur, _ := r.Seek(0, io.SeekCurrent)
		off = int(cur)
		defs = append(defs, def)
	}
	if len(defs) == 0 {
		return nil, 0, fmt.Errorf("no palette defs found at %s", baseAddr.Sum(start))
	}
	return defs, off, nil
}

func readPaletteEntries(r io.ReadSeeker, baseAddr, defAddr psx.Addr, def *paletteDef) error {
	boundaries := baseAddr.Boundaries()
	triplets := def.Kind == palCopy || def.Kind == palBulkCopy
	if !triplets {
		var dst, count uint32
		_ = binary.Read(r, binary.LittleEndian, &dst)
		if err := binary.Read(r, binary.LittleEndian, &count); err != nil {
			return fmt.Errorf("error reading palette def info: %w", err)
		}
		if dst > 0x8000 || count > 0x1000 {
			return fmt.Errorf("invalid palette def at %s: destination 0x%X, count 0x%X", defAddr, dst, count)
		}
		def.Destination = int(dst)
		def.Count = int(count)
	}
	for i := 0; ; i++ {
		var dst uint32
		var length uint32
		var addr psx.Addr
		if err := binary.Read(r, binary.LittleEndian, &dst); err != nil {
			return fmt.Errorf("error reading palette entries: %w", err)
		}
		if dst == palTerminate {
			break
		}
		if triplets {
			_ = binary.Read(r, binary.LittleEndian, &length)
			_ = binary.Read(r, binary.LittleEndian, &addr)
			if dst > 0x8000 {
				return fmt.Errorf("invalid palette entry at %s, destination out of range: got 0x%08X, expected less than 0x8000", defAddr.Sum(i*4*3+4), dst)
			}
			if length > 0x1000 {
				return fmt.Errorf("invalid palette entry at %s, length out of range: got 0x%08X, expected less than 0x1000", defAddr.Sum(i*4*3+4), length)
			}
		} else {
			// non-triplet ops only carry data pointers
			addr = psx.Addr(dst)
		}
		if !addr.InRange(baseAddr, boundaries.GameEnd) {
			return fmt.Errorf("invalid palette entry at %s, address out of the stage range: got %s", defAddr.Sum(i*4*3+4), addr)
		}
		entry := paletteEntry{Destination: int(dst), Length: int(length), addr: addr}
		if triplets {
			def.Entries = append(def.Entries, entry)
		} else {
			def.Data = append(def.Data, paletteEntry{addr: addr})
		}
	}
	return nil
}

// readClutsArray reads the cluts pointer array at 'off' until 'end',
// skipping trailing zero padding, and maps each pointer back to a def index
func readClutsArray(r io.ReadSeeker, baseAddr psx.Addr, off, end int, defs []paletteDef) ([]int, error) {
	byAddr := map[psx.Addr]int{}
	for i, def := range defs {
		byAddr[def.addr] = i
	}
	if err := baseAddr.Sum(off).MoveFile(r, baseAddr); err != nil {
		return nil, fmt.Errorf("invalid cluts offset: %w", err)
	}
	var cluts []int
	for pos := off; pos+4 <= end; pos += 4 {
		var addr psx.Addr
		if err := binary.Read(r, binary.LittleEndian, &addr); err != nil {
			return nil, fmt.Errorf("error reading cluts array: %w", err)
		}
		if addr == 0 { // trailing alignment padding
			continue
		}
		idx, found := byAddr[addr]
		if !found {
			return nil, fmt.Errorf("cluts entry at offset 0x%X points to %s, which is not a known palette def", pos, addr)
		}
		cluts = append(cluts, idx)
	}
	if len(cluts) == 0 {
		return nil, fmt.Errorf("empty cluts array at offset 0x%X", off)
	}
	return cluts, nil
}

// readClutsPointers reads raw cluts pointers for Info, stopping at the first
// word that is not a valid in-stage pointer
func readClutsPointers(r io.ReadSeeker, baseAddr psx.Addr, off, dataLen int) ([]psx.Addr, error) {
	if err := baseAddr.Sum(off).MoveFile(r, baseAddr); err != nil {
		return nil, fmt.Errorf("invalid cluts offset: %w", err)
	}
	boundaries := baseAddr.Boundaries()
	var cluts []psx.Addr
	for pos := off; pos+4 <= dataLen; pos += 4 {
		var addr psx.Addr
		if err := binary.Read(r, binary.LittleEndian, &addr); err != nil {
			break
		}
		if !addr.InRange(baseAddr, boundaries.StageEnd) || addr.Real(baseAddr) >= off {
			break
		}
		cluts = append(cluts, addr)
	}
	return cluts, nil
}

// resolveSymbols assigns a name to each palette reference; a reference may
// point in the middle of a palette, in which case it is expressed as the
// closest symbol below plus an offset in u16 units
func resolveSymbols(def *paletteDef, symbol func(psx.Addr) string, baseAddr psx.Addr) {
	resolve := func(entry *paletteEntry) {
		// scan back one color (2 bytes) at a time; palettes are small so
		// bound the search to 0x2000 bytes
		for off := 0; off <= 0x2000; off += 2 {
			probe := entry.addr.Sum(-off)
			if probe.Real(baseAddr) < 0 {
				break
			}
			if sym := symbol(probe); sym != "" {
				entry.Name = sym + ".palbin"
				entry.Offset = off / 2
				return
			}
		}
		entry.Name = fmt.Sprintf("D_%08X.palbin", uint32(entry.addr))
	}
	for i := range def.Entries {
		resolve(&def.Entries[i])
	}
	for i := range def.Data {
		resolve(&def.Data[i])
	}
}

// symRef formats a reference to a palette symbol with an optional offset
// expressed in u16 units
func symRef(name string, offset int) string {
	sym := util.RemoveFileNameExt(name)
	if offset != 0 {
		return fmt.Sprintf("(u16*)%s + 0x%X", sym, offset)
	}
	return sym
}

func palOpName(kind int) string {
	switch kind {
	case palCopy:
		return "PAL_COPY"
	case 2:
		return "PAL_UNK_OP2"
	case 3:
		return "PAL_UNK_OP3"
	case 4:
		return "PAL_GLOW_ANIM"
	case palBulkCopy:
		return "PAL_BULK_COPY"
	}
	return fmt.Sprintf("%d", kind)
}

func addGuessedUnusedPalettes(entries []assets.InfoSplatEntry) []assets.InfoSplatEntry {
	sort.Slice(entries, func(i, j int) bool {
		return entries[i].DataRange.Begin() < entries[j].DataRange.Begin()
	})
	newEntries := make([]assets.InfoSplatEntry, 0, len(entries))
	newEntries = append(newEntries, entries[0])
	for i := 1; i < len(entries); i++ {
		// if there is a gap between two entries then we add the new guessed unused palette
		addrLeft := entries[i-1].DataRange.End()
		addrRight := entries[i].DataRange.Begin()
		if addrLeft != addrRight {
			newEntries = append(newEntries, assets.InfoSplatEntry{
				DataRange: datarange.New(addrLeft, addrRight),
				Name:      fmt.Sprintf("D_%08X", uint32(addrLeft)),
				Kind:      "pal",
				Comment:   "unused",
			})
		}
		newEntries = append(newEntries, entries[i])
	}
	return newEntries
}
