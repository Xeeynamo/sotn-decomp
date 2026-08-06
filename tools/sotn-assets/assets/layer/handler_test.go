package layer

import (
	"os"
	"path/filepath"
	"testing"

	"github.com/stretchr/testify/assert"
	"github.com/stretchr/testify/require"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
)

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

func infoFor(t *testing.T, overlay string) assets.InfoResult {
	t.Helper()
	data, err := os.ReadFile(filepath.Join(repoRoot(t), overlay))
	require.NoError(t, err)
	res, err := Handler.Info(assets.InfoArgs{
		StageFilePath: overlay,
		StageData:     data,
		Boundaries:    psx.Addr(0x80000000).Boundaries(),
	})
	require.NoError(t, err)
	return res
}

func TestInfoReportsLayersRange(t *testing.T) {
	// LIB's layers run from 0x19C up to the graphics banks at 0x314, which is
	// what config/assets.us.yaml describes as `- [0x19C, layers, layers]`
	res := infoFor(t, "disks/us/ST/LIB/LIB.BIN")
	require.Len(t, res.AssetEntries, 1)
	e := res.AssetEntries[0]
	assert.Equal(t, "layers", e.Kind)
	assert.Equal(t, "layers", e.Name)
	assert.Equal(t, 0x19C, e.DataRange.Begin().Real(psx.Addr(0x80180000)))
	assert.Equal(t, 0x314, e.DataRange.End().Real(psx.Addr(0x80180000)))
}

func TestInfoReportsSplatEntry(t *testing.T) {
	// the layers are one blob for splat, so the region gets a name there too
	res := infoFor(t, "disks/us/ST/LIB/LIB.BIN")
	require.Len(t, res.SplatEntries, 1)
	e := res.SplatEntries[0]
	assert.Equal(t, "layers", e.Name)
	assert.Equal(t, 0x19C, e.DataRange.Begin().Real(psx.Addr(0x80180000)))
}

func TestInfoStartsAtFirstReferencedLayer(t *testing.T) {
	// MAR keeps an unreferenced layer_empty at 0xBC, below the first LayerDef a
	// room points at. The reported range starts at the referenced one, which is
	// what MAR's own config says; RBO5 has the same shape but its config
	// includes the empty def, so the configs disagree and only the referenced
	// boundary is a fact the data supports.
	res := infoFor(t, "disks/us/BOSS/MAR/MAR.BIN")
	require.Len(t, res.AssetEntries, 1)
	assert.Equal(t, 0xCC, res.AssetEntries[0].DataRange.Begin().Real(psx.Addr(0x80180000)))
}

func TestInfoNoLayers(t *testing.T) {
	// SEL has a null layers pointer; that is not an error, there is just
	// nothing to report
	res := infoFor(t, "disks/us/ST/SEL/SEL.BIN")
	assert.Empty(t, res.AssetEntries)
	assert.Empty(t, res.SplatEntries)
}
