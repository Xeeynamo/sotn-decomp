package graphics

import (
	"encoding/binary"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/datarange"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/util"
	"io"
)

type GfxKind uint16

const (
	GfxBankNone = GfxKind(iota)
	GfxBank4bpp
	GfxBank8bpp
	GfxBank16bpp
	GfxBankCompressed
)

type GfxEntry struct {
	X      uint16
	Y      uint16
	Width  uint16
	Height uint16
	Data   psx.Addr
}

type GfxBlock struct {
	kind    GfxKind
	flags   uint16
	entries []GfxEntry
}

type Gfx struct {
	blocks  []GfxBlock
	indices []int
}

func ReadGraphics(r io.ReadSeeker, off psx.Addr) (Gfx, datarange.DataRange, error) {
	if err := off.MoveFile(r, psx.RamStageBegin); err != nil {
		return Gfx{}, datarange.DataRange{}, err
	}

	// all the offsets are before the array, so it is easy to find where the offsets array ends
	var blockOffsets []psx.Addr
	for {
		var offBank psx.Addr
		if err := binary.Read(r, binary.LittleEndian, &offBank); err != nil {
			return Gfx{}, datarange.DataRange{}, err
		}
		if offBank >= off {
			break
		}
		blockOffsets = append(blockOffsets, offBank)
	}

	// the order of each GfxBlock must be preserved
	pool := map[psx.Addr]int{}
	pool[psx.RamNull] = -1
	var blocks []GfxBlock
	var ranges []datarange.DataRange
	for _, blockOffset := range util.SortUniqueOffsets(blockOffsets) {
		if blockOffset == psx.RamNull { // exception for ST0
			continue
		}
		if err := blockOffset.MoveFile(r, psx.RamStageBegin); err != nil {
			return Gfx{}, datarange.DataRange{}, err
		}
		var block GfxBlock
		if err := binary.Read(r, binary.LittleEndian, &block.kind); err != nil {
			return Gfx{}, datarange.DataRange{}, err
		}
		if err := binary.Read(r, binary.LittleEndian, &block.flags); err != nil {
			return Gfx{}, datarange.DataRange{}, err
		}

		if block.kind == GfxKind(0xFFFF) && block.flags == 0xFFFF { // exception for ST0
			pool[blockOffset] = len(blocks)
			blocks = append(blocks, block)
			ranges = append(ranges, datarange.FromAddr(blockOffset, 4))
			continue
		}

		for {
			var entry GfxEntry
			if err := binary.Read(r, binary.LittleEndian, &entry); err != nil {
				return Gfx{}, datarange.DataRange{}, err
			}
			if entry.X == 0xFFFF && entry.Y == 0xFFFF {
				break
			}
			block.entries = append(block.entries, entry)
		}
		pool[blockOffset] = len(blocks)
		blocks = append(blocks, block)
		ranges = append(ranges, datarange.FromAddr(blockOffset, 4+len(block.entries)*12+4))
	}

	var g Gfx
	for _, blockOffset := range blockOffsets {
		g.indices = append(g.indices, pool[blockOffset])
	}

	return g, datarange.MergeDataRanges(append(ranges, datarange.FromAddr(off, len(blockOffsets)*4))), nil
}
