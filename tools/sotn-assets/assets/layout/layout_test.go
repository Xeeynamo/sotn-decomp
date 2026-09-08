package layout

import (
	"bytes"
	"encoding/binary"
	"encoding/json"
	"os"
	"path/filepath"
	"strings"
	"testing"

	"github.com/stretchr/testify/assert"
	"github.com/stretchr/testify/require"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/datarange"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
)

func TestBuildSelectsHeaderForOutputLocation(t *testing.T) {
	assetDir := t.TempDir()
	data, err := json.Marshal(layouts{
		Entities: [][]layoutEntry{{
			{X: -2, Y: -2, ID: "E_NONE"},
			{X: -1, Y: -1, ID: "E_NONE"},
		}},
		Indices: []int{0},
	})
	require.NoError(t, err)
	require.NoError(t, os.MkdirAll(filepath.Join(assetDir, "us"), 0o755))
	require.NoError(t, os.WriteFile(
		filepath.Join(assetDir, "us", "entity_layouts.json"), data, 0o644))

	args := assets.BuildArgs{
		AssetDir: assetDir,
		Name:     "us/entity_layouts",
		OvlName:  "np3",
	}

	args.SrcDir = t.TempDir()
	require.NoError(t, Handler.Build(args))
	generated, err := os.ReadFile(
		filepath.Join(args.SrcDir, "gen", "us", "e_layout.c"))
	require.NoError(t, err)
	assert.True(t, strings.HasPrefix(string(generated), "#include \"../../np3.h\"\n"))

	args.SrcDir = t.TempDir()
	require.NoError(t, BuildWithOverlayHeader(args))
	generated, err = os.ReadFile(
		filepath.Join(args.SrcDir, "gen", "us", "e_layout.c"))
	require.NoError(t, err)
	assert.True(t, strings.HasPrefix(string(generated), "#include <np3.h>\n"))
}

func TestExtractPropagatesLayoutReadError(t *testing.T) {
	base := psx.Addr(0x80180000)
	data := make([]byte, 0x40)
	binary.LittleEndian.PutUint32(data[0x1C:], uint32(base.Sum(0x40)))

	err := Handler.Extract(assets.ExtractArgs{
		Data:     data,
		AssetDir: t.TempDir(),
		Name:     "entity_layouts",
		RamBase:  base,
	})
	assert.Error(t, err)
}

func TestReadEntityLayoutPreservesUnclaimedRanges(t *testing.T) {
	const count = 2
	base := psx.Addr(0x80180000)
	data := make([]byte, 0xA0)

	blockOffsets := []int{0x20, 0x40, 0x60, 0x80}
	for i, off := range blockOffsets {
		binary.LittleEndian.PutUint32(data[i*4:], uint32(base.Sum(off)))
		binary.LittleEndian.PutUint16(data[off:], uint16(0xFFFE))
		binary.LittleEndian.PutUint16(data[off+2:], uint16(0xFFFE))
		binary.LittleEndian.PutUint16(data[off+10:], uint16(0xFFFF))
		binary.LittleEndian.PutUint16(data[off+12:], uint16(0xFFFF))
	}

	layouts, ranges, err := readEntityLayout(
		bytes.NewReader(data), "dummy", base, base, count, true)
	require.NoError(t, err)
	assert.Len(t, layouts.Entities, count)
	assert.Equal(t, []datarange.DataRange{
		datarange.New(base, base.Sum(0x10)),
		datarange.New(base.Sum(0x20), base.Sum(0x34)),
		datarange.New(base.Sum(0x40), base.Sum(0x54)),
		datarange.New(base.Sum(0x60), base.Sum(0x74)),
		datarange.New(base.Sum(0x80), base.Sum(0x94)),
	}, ranges)
}
