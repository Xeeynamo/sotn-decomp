package main

import (
	"encoding/binary"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"os"
)

type gfxKind uint16

const (
	gfxBankNone = gfxKind(iota)
	gfxBank4bpp
	gfxBank8bpp
	gfxBank16bpp
	gfxBankCompressed
)

type gfxEntry struct {
	X      uint16
	Y      uint16
	Width  uint16
	Height uint16
	Data   psx.Addr
}

type gfxBlock struct {
	kind    gfxKind
	flags   uint16
	entries []gfxEntry
}

type gfx struct {
	blocks  []gfxBlock
	indices []int
}

func readGraphics(file *os.File, off psx.Addr) (gfx, dataRange, error) {
	if err := off.MoveFile(file, psx.RamStageBegin); err != nil {
		return gfx{}, dataRange{}, err
	}

	// all the offsets are before the array, so it is easy to find where the offsets array ends
	blockOffsets := []psx.Addr{}
	for {
		var offBank psx.Addr
		if err := binary.Read(file, binary.LittleEndian, &offBank); err != nil {
			return gfx{}, dataRange{}, err
		}
		if offBank >= off {
			break
		}
		blockOffsets = append(blockOffsets, offBank)
	}

	// the order of each gfxBlock must be preserved
	pool := map[psx.Addr]int{}
	pool[psx.RamNull] = -1
	blocks := []gfxBlock{}
	ranges := []dataRange{}
	for _, blockOffset := range sortUniqueOffsets(blockOffsets) {
		if blockOffset == psx.RamNull { // exception for ST0
			continue
		}
		if err := blockOffset.MoveFile(file, psx.RamStageBegin); err != nil {
			return gfx{}, dataRange{}, err
		}
		var block gfxBlock
		if err := binary.Read(file, binary.LittleEndian, &block.kind); err != nil {
			return gfx{}, dataRange{}, err
		}
		if err := binary.Read(file, binary.LittleEndian, &block.flags); err != nil {
			return gfx{}, dataRange{}, err
		}

		if block.kind == gfxKind(0xFFFF) && block.flags == 0xFFFF { // exception for ST0
			pool[blockOffset] = len(blocks)
			blocks = append(blocks, block)
			ranges = append(ranges, dataRange{
				begin: blockOffset,
				end:   blockOffset.Sum(4),
			})
			continue
		}

		for {
			var entry gfxEntry
			if err := binary.Read(file, binary.LittleEndian, &entry); err != nil {
				return gfx{}, dataRange{}, err
			}
			if entry.X == 0xFFFF && entry.Y == 0xFFFF {
				break
			}
			block.entries = append(block.entries, entry)
		}
		pool[blockOffset] = len(blocks)
		blocks = append(blocks, block)
		ranges = append(ranges, dataRange{
			begin: blockOffset,
			end:   blockOffset.Sum(4 + len(block.entries)*12 + 4),
		})
	}

	var g gfx
	for _, blockOffset := range blockOffsets {
		g.indices = append(g.indices, pool[blockOffset])
	}

	return g, mergeDataRanges(append(ranges, dataRange{
		begin: off,
		end:   off.Sum(len(blockOffsets) * 4),
	})), nil
}
