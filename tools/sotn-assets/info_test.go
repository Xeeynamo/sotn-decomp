package main

import (
	"bytes"
	"fmt"
	"github.com/stretchr/testify/assert"
	"github.com/stretchr/testify/require"
	"os"
	"path"
	"sync"
	"testing"
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
			assert.Contains(t, stdout, "  - [0x164, .data, header] # layers\n")
			assert.Contains(t, stdout, "  - [0x47C, .data, header] # graphics banks\n")
			assert.Contains(t, stdout, "  - [0x8EC, .data, e_laydef] # layout entries header\n")
			assert.Contains(t, stdout, "  - [0xA94, data]\n")
			assert.Contains(t, stdout, "  - [0x272C, .data, rooms]\n")
			assert.Contains(t, stdout, "  - [0x2830, data]\n")
			assert.Contains(t, stdout, "  - [0x2884, .data, e_layout] # layout entries data\n")
			assert.Contains(t, stdout, "  - [0x3B0C, data]\n")
			assert.Contains(t, stdout, "  - [0x15C3C, pal, D_80195C3C]\n")
			assert.Contains(t, stdout, "  - [0x1601C, pal, D_8019601C]\n")
			assert.Contains(t, stdout, "  - [0x1621C, pal, D_8019621C] # unused\n")
			assert.Contains(t, stdout, "  - [0x162DC, pal, D_801962DC]\n")
			assert.Contains(t, stdout, "  - [0x16A5C, .data, tile_data] # tile data\n")
			assert.Contains(t, stdout, "  - [0x20A5C, .data, tile_data] # tile definitions\n")
			assert.Contains(t, stdout, "  - [0x26E8C, .data, sprites]\n")
			assert.Contains(t, stdout, "  - [0x3058C, data]\n")
			if t.Failed() {
				require.FailNow(t, "unexpected output", stdout)
			}
		})
	})
}

func TestStagesCompatibility(t *testing.T) {
	changeDirToRepoRoot()
	files := []string{
		"disks/us/BOSS/BO0/BO0.BIN",
		"disks/us/BOSS/BO1/BO1.BIN",
		"disks/us/BOSS/BO2/BO2.BIN",
		"disks/us/BOSS/BO3/BO3.BIN",
		"disks/us/BOSS/BO4/BO4.BIN",
		"disks/us/BOSS/BO5/BO5.BIN",
		"disks/us/BOSS/BO6/BO6.BIN",
		"disks/us/BOSS/BO7/BO7.BIN",
		"disks/us/BOSS/MAR/MAR.BIN",
		"disks/us/BOSS/RBO0/RBO0.BIN",
		"disks/us/BOSS/RBO1/RBO1.BIN",
		"disks/us/BOSS/RBO2/RBO2.BIN",
		"disks/us/BOSS/RBO3/RBO3.BIN",
		"disks/us/BOSS/RBO4/RBO4.BIN",
		"disks/us/BOSS/RBO5/RBO5.BIN",
		"disks/us/BOSS/RBO6/RBO6.BIN",
		"disks/us/BOSS/RBO7/RBO7.BIN",
		"disks/us/BOSS/RBO8/RBO8.BIN",
		"disks/us/ST/SEL/SEL.BIN",
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
		"disks/us/ST/TOP/TOP.BIN",
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
		"disks/us/ST/MAD/MAD.BIN",
		"disks/us/ST/TE1/TE1.BIN",
		"disks/us/ST/TE2/TE2.BIN",
		"disks/us/ST/TE3/TE3.BIN",
		"disks/us/ST/TE4/TE4.BIN",
		"disks/us/ST/TE5/TE5.BIN",
	}
	succeeded := 0
	for _, p := range files {
		t.Run(fmt.Sprintf("can gather info for %q", p), func(t *testing.T) {
			defer func() {
				if err := recover(); err != nil {
					assert.Fail(t, fmt.Sprintf("%v", err))
				}
			}()
			buf := new(bytes.Buffer)
			err := info(buf, p)
			assert.NoError(t, err)
			if err == nil {
				succeeded++
			}
		})
	}
	assert.Equal(t, len(files), succeeded, "not all succeeded")
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
		parent := path.Dir(cwd)
		if cwd == parent {
			panic(fmt.Errorf("unable to find repo root"))
		}
		if err := os.Chdir(".."); err != nil {
			panic(err)
		}
	}
}
