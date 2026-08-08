package graphics

import (
	"os"
	"path/filepath"
	"testing"

	"github.com/stretchr/testify/assert"
	"github.com/stretchr/testify/require"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
)

const ramBase = psx.Addr(0x80180000)

func repoRoot(t *testing.T) string {
	t.Helper()
	dir, err := os.Getwd()
	require.NoError(t, err)
	for {
		if _, err := os.Stat(filepath.Join(dir, "disks/us/DRA.BIN")); err == nil {
			return dir
		}
		parent := filepath.Dir(dir)
		require.NotEqual(t, dir, parent, "unable to find repo root")
		dir = parent
	}
}

func overlay(t *testing.T, name string) []byte {
	t.Helper()
	data, err := os.ReadFile(filepath.Join(repoRoot(t), name))
	require.NoError(t, err)
	return data
}

// findEntry returns the entry starting at the given file offset.
func findEntry(entries []assets.InfoAssetEntry, offset int) *assets.InfoAssetEntry {
	for i := range entries {
		if entries[i].DataRange.Begin() == ramBase.Sum(offset) {
			return &entries[i]
		}
	}
	return nil
}

func TestClassifyCompressedBoundaries(t *testing.T) {
	// three consecutive LIB images: each end must be the next one's start
	entries, _, err := Classify(Args{
		Data:    overlay(t, "disks/us/ST/LIB/LIB.BIN"),
		RamBase: ramBase,
		Graphics: []assets.InfoGraphic{
			{Addr: ramBase.Sum(0x4FC8), Kind: 4, Width: 128, Height: 128},
			{Addr: ramBase.Sum(0x5294), Kind: 4, Width: 128, Height: 128},
			{Addr: ramBase.Sum(0x5784), Kind: 4, Width: 128, Height: 128},
		},
		RegionEnd: ramBase.Sum(0x65F0),
	})
	require.NoError(t, err)

	e := findEntry(entries, 0x4FC8)
	require.NotNil(t, e)
	assert.Equal(t, "cmpgfx", e.Kind)
	assert.Equal(t, ramBase.Sum(0x5294), e.DataRange.End())
	assert.Empty(t, e.Comment, "a confident read carries no comment")

	e = findEntry(entries, 0x5294)
	require.NotNil(t, e)
	assert.Equal(t, ramBase.Sum(0x5784), e.DataRange.End())
}

func TestClassifyRawGraphic(t *testing.T) {
	// kind 2 is raw 8bpp: 48*72*8/8 == 0xD80 bytes
	entries, _, err := Classify(Args{
		Data:    overlay(t, "disks/us/ST/LIB/LIB.BIN"),
		RamBase: ramBase,
		Graphics: []assets.InfoGraphic{
			{Addr: ramBase.Sum(0xA488), Kind: 2, Width: 48, Height: 72},
		},
		RegionEnd: ramBase.Sum(0xB208),
	})
	require.NoError(t, err)
	e := findEntry(entries, 0xA488)
	require.NotNil(t, e)
	assert.Equal(t, "rawgfx", e.Kind)
	assert.Equal(t, "48, 72, 8", e.Args)
	assert.Equal(t, ramBase.Sum(0xB208), e.DataRange.End())
}

func TestClassifyPaletteCarriesClutID(t *testing.T) {
	entries, _, err := Classify(Args{
		Data:    overlay(t, "disks/us/ST/NZ0/NZ0.BIN"),
		RamBase: ramBase,
		Palettes: []assets.InfoPalette{
			{Addr: ramBase.Sum(0x15C3C), Length: 0x80, ClutID: 0x200},
			{Addr: ramBase.Sum(0x15CDC), Length: 0x20, ClutID: 0x204},
		},
		RegionEnd: ramBase.Sum(0x15CFC),
	})
	require.NoError(t, err)
	e := findEntry(entries, 0x15C3C)
	require.NotNil(t, e)
	assert.Equal(t, "palette", e.Kind)
	assert.Equal(t, "16", e.Args)
	assert.Equal(t, "0x200", e.Comment)
}

func TestClassifyPaletteWithoutClutID(t *testing.T) {
	// ClutID -1 means the palette def carried no destination to derive it from
	entries, _, err := Classify(Args{
		Data:    overlay(t, "disks/us/ST/NZ0/NZ0.BIN"),
		RamBase: ramBase,
		Palettes: []assets.InfoPalette{
			{Addr: ramBase.Sum(0x15C3C), Length: 0x80, ClutID: -1},
		},
		RegionEnd: ramBase.Sum(0x15CBC),
	})
	require.NoError(t, err)
	e := findEntry(entries, 0x15C3C)
	require.NotNil(t, e)
	assert.Empty(t, e.Comment, "an underivable clut id must not be invented")
}

func TestClassifyUnusedPaletteGap(t *testing.T) {
	// the gap between two palettes is an unused palette
	entries, _, err := Classify(Args{
		Data:    overlay(t, "disks/us/ST/NZ0/NZ0.BIN"),
		RamBase: ramBase,
		Palettes: []assets.InfoPalette{
			{Addr: ramBase.Sum(0x15C3C), Length: 0x80, ClutID: 0x200},
			{Addr: ramBase.Sum(0x15CDC), Length: 0x20, ClutID: 0x204},
		},
		RegionEnd: ramBase.Sum(0x15CFC),
	})
	require.NoError(t, err)
	e := findEntry(entries, 0x15CBC)
	require.NotNil(t, e, "the 0x15CBC..0x15CDC gap must be reported")
	assert.Equal(t, "palette", e.Kind)
	assert.Contains(t, e.Comment, "unused")
}

func TestClassifyGapRuleChainedCompressed(t *testing.T) {
	// NZ0 0x3CCC is referenced only from C; one inflate walk reaches the next
	// known boundary at 0x4154 exactly, so rule 1 claims it
	entries, _, err := Classify(Args{
		Data:    overlay(t, "disks/us/ST/NZ0/NZ0.BIN"),
		RamBase: ramBase,
		Graphics: []assets.InfoGraphic{
			{Addr: ramBase.Sum(0x4154), Kind: 4, Width: 128, Height: 128},
		},
		RegionStart: ramBase.Sum(0x3CCC),
		RegionEnd:   ramBase.Sum(0x4CE4),
	})
	require.NoError(t, err)
	e := findEntry(entries, 0x3CCC)
	require.NotNil(t, e, "the unreferenced image at 0x3CCC must be found")
	assert.Equal(t, "cmpgfx", e.Kind)
	assert.Equal(t, ramBase.Sum(0x4154), e.DataRange.End())
	assert.Contains(t, e.Comment, "guessed")
}

func TestClassifyGapRuleRawMultiple(t *testing.T) {
	// LIB 0xA488..0xBF88 is 0x1B00 == 2 * 0xD80 (48x72 8bpp): two portraits.
	// The inflate walk from 0xA488 stops at 0xA652, so rule 1 must decline.
	entries, _, err := Classify(Args{
		Data:    overlay(t, "disks/us/ST/LIB/LIB.BIN"),
		RamBase: ramBase,
		Graphics: []assets.InfoGraphic{
			{Addr: ramBase.Sum(0x9990), Kind: 4, Width: 128, Height: 128},
			{Addr: ramBase.Sum(0xBF88), Kind: 4, Width: 128, Height: 128},
		},
		RegionEnd: ramBase.Sum(0xD2B4),
	})
	require.NoError(t, err)

	first := findEntry(entries, 0xA488)
	require.NotNil(t, first, "first portrait must be recovered")
	assert.Equal(t, "rawgfx", first.Kind)
	assert.Equal(t, "48, 72, 8", first.Args)
	assert.Contains(t, first.Comment, "guessed")

	second := findEntry(entries, 0xB208)
	require.NotNil(t, second, "second portrait must be recovered")
	assert.Equal(t, "rawgfx", second.Kind)
	assert.Equal(t, ramBase.Sum(0xBF88), second.DataRange.End())
}

func TestClassifyGapLeadingRawAfterTrailingCompressed(t *testing.T) {
	// ST0 0xF130..0x111D8 is 0x20A8, no raw multiple. But its tail is an
	// unreferenced compressed image at 0x10C30, and what is left below that is
	// 0x1B00 == 2 * 0xD80: the Richter and Dracula portraits.
	entries, _, err := Classify(Args{
		Data:    overlay(t, "disks/us/ST/ST0/ST0.BIN"),
		RamBase: ramBase,
		Graphics: []assets.InfoGraphic{
			{Addr: ramBase.Sum(0xE3D0), Kind: 4, Width: 128, Height: 128},
			{Addr: ramBase.Sum(0x111D8), Kind: 4, Width: 128, Height: 128},
		},
		RegionEnd: ramBase.Sum(0x11B8C),
	})
	require.NoError(t, err)

	richter := findEntry(entries, 0xF130)
	require.NotNil(t, richter, "the portrait below the trailing image must be found")
	assert.Equal(t, "rawgfx", richter.Kind)
	assert.Equal(t, "48, 72, 8", richter.Args)
	assert.Equal(t, ramBase.Sum(0xFEB0), richter.DataRange.End())

	dracula := findEntry(entries, 0xFEB0)
	require.NotNil(t, dracula)
	assert.Equal(t, "rawgfx", dracula.Kind)
	assert.Equal(t, ramBase.Sum(0x10C30), dracula.DataRange.End())

	trailing := findEntry(entries, 0x10C30)
	require.NotNil(t, trailing, "the trailing image itself must survive the split")
	assert.Equal(t, "cmpgfx", trailing.Kind)
}

func TestClassifyGapRuleUnrecognized(t *testing.T) {
	// a gap that is neither a compressed chain nor a clean raw multiple must
	// be reported as skip rather than absorbed into a neighbour
	entries, _, err := Classify(Args{
		Data:    overlay(t, "disks/us/ST/LIB/LIB.BIN"),
		RamBase: ramBase,
		Graphics: []assets.InfoGraphic{
			{Addr: ramBase.Sum(0x4FC8), Kind: 4, Width: 128, Height: 128},
		},
		// leave an odd 0x101-byte tail that fits no candidate shape
		RegionStart: ramBase.Sum(0x4EC7),
		RegionEnd:   ramBase.Sum(0x5294),
	})
	require.NoError(t, err)
	e := findEntry(entries, 0x4EC7)
	require.NotNil(t, e)
	assert.Equal(t, "skip", e.Kind)
}

func TestClassifyGapRuleRejectsPartialInflate(t *testing.T) {
	// 0x4EC7..0x4FC8 inflates "successfully" to only 0x152 bytes, nowhere near
	// a full 128x128 4bpp image, and lands on the gap end only because the end
	// is rounded up to 4. Rule 1 must not claim it.
	entries, ok := gapAsCompressedChain(Args{
		Data:    overlay(t, "disks/us/ST/LIB/LIB.BIN"),
		RamBase: ramBase,
	}, ramBase.Sum(0x4EC7), ramBase.Sum(0x4FC8))
	assert.False(t, ok, "a stream that under-inflates is not an image")
	assert.Empty(t, entries)
}

func TestClassifyRegionExcludesSkips(t *testing.T) {
	// the 0x4EC7 tail is unrecognized, so the splat blob must start at the
	// image after it rather than claiming unknown bytes as graphics
	_, region, err := Classify(Args{
		Data:    overlay(t, "disks/us/ST/LIB/LIB.BIN"),
		RamBase: ramBase,
		Graphics: []assets.InfoGraphic{
			{Addr: ramBase.Sum(0x4FC8), Kind: 4, Width: 128, Height: 128},
		},
		RegionStart: ramBase.Sum(0x4EC7),
		RegionEnd:   ramBase.Sum(0x5294),
	})
	require.NoError(t, err)
	assert.Equal(t, ramBase.Sum(0x4FC8), region.Begin())
	assert.Equal(t, ramBase.Sum(0x5294), region.End())
}

func TestClassifyEmptyInput(t *testing.T) {
	// no graphics and no palettes must not panic or produce entries
	entries, _, err := Classify(Args{
		Data:    overlay(t, "disks/us/ST/LIB/LIB.BIN"),
		RamBase: ramBase,
	})
	require.NoError(t, err)
	assert.Empty(t, entries)
}
