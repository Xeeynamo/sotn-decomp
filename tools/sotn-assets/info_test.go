package main

import (
	"bytes"
	"fmt"
	"os"
	"path/filepath"
	"sync"
	"testing"

	"github.com/stretchr/testify/assert"
	"github.com/stretchr/testify/require"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/datarange"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
)

var chdirMutex sync.Mutex

func TestGatherAssetInfo(t *testing.T) {
	changeDirToRepoRoot()
	t.Run("for NZ0", func(t *testing.T) {
		buf := new(bytes.Buffer)
		require.NoError(t, info(buf, "disks/us/ST/NZ0/NZ0.BIN"))
		stdout := buf.String()
		t.Run("asset config hints", func(t *testing.T) {
			assert.Contains(t, stdout, "asset config hints:\n")
			assert.Contains(t, stdout, "  - [0x2C, sprite_banks, sprite_banks]")
			assert.Contains(t, stdout, "  - [0x8C, paldef, palette_def]")
			assert.Contains(t, stdout, "  - [0x164, layers, layers]\n")
			assert.Contains(t, stdout, "  - [0x47C, gfx_banks, graphics_banks]\n")
			assert.Contains(t, stdout, "  - [0x8EC, layout, entity_layouts]\n")
			assert.Contains(t, stdout, "  - [0x272C, rooms, rooms]")
			assert.Contains(t, stdout, "  - [0x2830, skip]")
			if t.Failed() {
				require.FailNow(t, "unexpected output", stdout)
			}
		})
		t.Run("splat config hints", func(t *testing.T) {
			assert.Contains(t, stdout, "splat config hints:\n")
			assert.Contains(t, stdout, "  - [0x0, .data, header]\n")
			assert.Contains(t, stdout, "  - [0x8C, .data, header] # palette definitions\n")
			assert.Contains(t, stdout, "  - [0x164, .data, layers]\n")
			assert.Contains(t, stdout, "  - [0x47C, .data, header] # graphics banks\n")
			assert.Contains(t, stdout, "  - [0x8EC, .data, e_laydef] # layout entries header\n")
			assert.Contains(t, stdout, "  - [0xA94, data]\n")
			assert.Contains(t, stdout, "  - [0x272C, .data, rooms]\n")
			assert.Contains(t, stdout, "  - [0x2830, data]\n")
			assert.Contains(t, stdout, "  - [0x2884, .data, e_layout] # layout entries data\n")
			assert.NotContains(t, stdout, ", pal, ", "palettes belong in the asset hints, not splat")
			assert.NotContains(t, stdout, ", cmp, ", "graphics belong in the asset hints, not splat")
			assert.NotContains(t, stdout, "unknown size", "exact boundaries make this comment obsolete")
			// the whole graphics and palette span is one blob to splat, starting
			// at the recovered image below the first bank entry
			assert.Contains(t, stdout, "  - [0x3CCC, .data, stage_data]\n")
			assert.Contains(t, stdout, "  - [0x26E8C, .data, sprites]\n")
			assert.Contains(t, stdout, "  - [0x3058C, data]\n")
			if t.Failed() {
				require.FailNow(t, "unexpected output", stdout)
			}
		})
		t.Run("graphics and palettes in asset hints", func(t *testing.T) {
			// palettes carry their clut id, derived from destination >> 4
			assert.Contains(t, stdout, "  - [0x15C3C, palette, pal_15C3C, 16] # 0x200\n")
			assert.Contains(t, stdout, "  - [0x15CDC, palette, pal_15CDC, 16] # 0x204\n")
			assert.Contains(t, stdout, "  - [0x15D3C, palette, pal_15D3C, 16] # 0x205\n")
			// the last image had no successor to bound it; now it is exact
			assert.Contains(t, stdout, "  - [0x156A4, cmpgfx, gfx_156A4, 128, 128, 4]\n")
			// referenced images get exact boundaries with no caveat comment
			assert.Contains(t, stdout, "  - [0x4154, cmpgfx, gfx_4154, 128, 128, 4]\n")
			// an image only C code refers to, recovered by probing the gap below
			// the first bank entry
			assert.Contains(t, stdout, "  - [0x3CCC, cmpgfx, gfx_3CCC, 128, 128, 4] # guessed:")
			if t.Failed() {
				require.FailNow(t, "unexpected output", stdout)
			}
		})
	})
}

func TestInfoAssetEntryComment(t *testing.T) {
	buf := new(bytes.Buffer)
	boundaries := psx.Addr(0x80180000).Boundaries()
	infoAssetEntries(buf, []assets.InfoAssetEntry{
		{
			DataRange: datarange.New(psx.Addr(0x80180100), psx.Addr(0x80180200)),
			Kind:      "palette",
			Name:      "pal_100",
			Args:      "16",
			Comment:   "0x20A",
		},
	}, boundaries)
	assert.Contains(t, buf.String(), "  - [0x100, palette, pal_100, 16] # 0x20A\n")
}

func TestStagesCompatibility(t *testing.T) {
	changeDirToRepoRoot()

	// Any failure in these tests marks a regression
	for _, ovlPath := range []string{
		"disks/us/BOSS/BO0/BO0.BIN",
		"disks/us/BOSS/BO1/BO1.BIN",
		"disks/us/BOSS/BO2/BO2.BIN",
		"disks/us/BOSS/BO3/BO3.BIN",
		"disks/us/BOSS/BO5/BO5.BIN",
		"disks/us/BOSS/BO6/BO6.BIN",
		"disks/us/BOSS/BO7/BO7.BIN",
		"disks/us/BOSS/MAR/MAR.BIN",
		"disks/us/BOSS/RBO0/RBO0.BIN",
		"disks/us/BOSS/RBO1/RBO1.BIN",
		"disks/us/BOSS/RBO2/RBO2.BIN",
		"disks/us/BOSS/RBO3/RBO3.BIN",
		"disks/us/BOSS/RBO4/RBO4.BIN",
		"disks/us/BOSS/RBO6/RBO6.BIN",
		"disks/us/BOSS/RBO7/RBO7.BIN",
		"disks/us/BOSS/RBO8/RBO8.BIN",
		"disks/us/ST/ARE/ARE.BIN",
		"disks/us/ST/CAT/CAT.BIN",
		"disks/us/ST/CEN/CEN.BIN",
		"disks/us/ST/CHI/CHI.BIN",
		"disks/us/ST/DAI/DAI.BIN",
		"disks/us/ST/DRE/DRE.BIN",
		"disks/us/ST/LIB/LIB.BIN",
		"disks/us/ST/NO0/NO0.BIN",
		"disks/us/ST/NO1/NO1.BIN",
		"disks/us/ST/NO2/NO2.BIN",
		"disks/us/ST/NO3/NO3.BIN",
		"disks/us/ST/NO4/NO4.BIN",
		"disks/us/ST/NP3/NP3.BIN",
		"disks/us/ST/NZ0/NZ0.BIN",
		"disks/us/ST/NZ1/NZ1.BIN",
		"disks/us/ST/ST0/ST0.BIN",
		"disks/us/ST/WRP/WRP.BIN",
		"disks/us/ST/RARE/RARE.BIN",
		"disks/us/ST/RCAT/RCAT.BIN",
		"disks/us/ST/RCEN/RCEN.BIN",
		"disks/us/ST/RCHI/RCHI.BIN",
		"disks/us/ST/RDAI/RDAI.BIN",
		"disks/us/ST/RLIB/RLIB.BIN",
		"disks/us/ST/RNO0/RNO0.BIN",
		"disks/us/ST/RNO1/RNO1.BIN",
		"disks/us/ST/RNO2/RNO2.BIN",
		"disks/us/ST/RNO3/RNO3.BIN",
		"disks/us/ST/RNO4/RNO4.BIN",
		"disks/us/ST/RNZ0/RNZ0.BIN",
		"disks/us/ST/RNZ1/RNZ1.BIN",
		"disks/us/ST/RTOP/RTOP.BIN",
		"disks/us/ST/RWRP/RWRP.BIN",
		"disks/us/ST/TE1/TE1.BIN",
		"disks/us/ST/TE2/TE2.BIN",
		"disks/us/ST/TE3/TE3.BIN",
		"disks/us/ST/TE4/TE4.BIN",
		"disks/us/ST/TE5/TE5.BIN",
		"disks/us/ST/TOP/TOP.BIN",
		"disks/us/ST/MAD/MAD.BIN",
	} {
		t.Run(fmt.Sprintf("should be able to gather info for %q", ovlPath), func(t *testing.T) {
			defer func() {
				if err := recover(); err != nil {
					assert.Fail(t, fmt.Sprintf("%v", err))
				}
			}()
			assert.NoError(t, info(new(bytes.Buffer), ovlPath))
		})
	}

	// Any "failure" in one of these tests means the overlay compatibility increased.
	// A test failure here should be good news and it should be moved to the test above
	for _, ovlPath := range []string{
		"disks/us/ST/SEL/SEL.BIN",
		"disks/us/BOSS/BO4/BO4.BIN",
		"disks/us/BOSS/RBO5/RBO5.BIN",
	} {
		t.Run(fmt.Sprintf("currently fails for %q", ovlPath), func(t *testing.T) {
			defer func() {
				recover()
			}()
			assert.Error(t, info(new(bytes.Buffer), ovlPath))
		})
	}
}

func changeDirToRepoRoot() {
	chdirMutex.Lock()
	defer chdirMutex.Unlock()
	for {
		stat, err := os.Stat("disks/us/DRA.BIN")
		if err == nil && !stat.IsDir() {
			return
		}
		if !os.IsNotExist(err) {
			panic(err)
		}
		cwd, err := os.Getwd()
		if err != nil {
			panic(err)
		}
		parent := filepath.Dir(cwd)
		if cwd == parent {
			panic(fmt.Errorf("unable to find repo root"))
		}
		if err := os.Chdir(".."); err != nil {
			panic(err)
		}
	}
}
