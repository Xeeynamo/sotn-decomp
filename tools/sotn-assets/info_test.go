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
			assert.Contains(t, stdout, "  - [0x8C, skip]")
			assert.Contains(t, stdout, "  - [0x272C, rooms, rooms]")
			assert.Contains(t, stdout, "  - [0x2830, skip]")
			if t.Failed() {
				require.FailNow(t, "unexpected output", stdout)
			}
		})
		t.Run("splat config hints", func(t *testing.T) {
			assert.Contains(t, stdout, "splat config hints:\n")
			assert.Contains(t, stdout, "  - [0x0, .data, header]")
			assert.Contains(t, stdout, "  - [0x164, .data, header] # layers")
			assert.Contains(t, stdout, "  - [0x8EC, .data, e_laydef] # layout entries header")
			assert.Contains(t, stdout, "  - [0xA94, data]")
			assert.Contains(t, stdout, "  - [0x272C, .data, rooms]")
			assert.Contains(t, stdout, "  - [0x2830, data]")
			assert.Contains(t, stdout, "  - [0x2884, .data, e_layout] # layout entries data")
			assert.Contains(t, stdout, "  - [0x3B0C, data]")
			assert.Contains(t, stdout, "  - [0x16A5C, .data, tile_data] # tile data")
			assert.Contains(t, stdout, "  - [0x20A5C, .data, tile_data] # tile definitions")
			assert.Contains(t, stdout, "  - [0x26E8C, .data, sprites]")
			assert.Contains(t, stdout, "  - [0x3058C, data]")
			if t.Failed() {
				require.FailNow(t, "unexpected output", stdout)
			}
		})
	})
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
