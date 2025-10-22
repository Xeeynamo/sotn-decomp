package gfxbanks

import (
	"encoding/binary"
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/datarange"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/sotn"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/util"
	"io"
	"path/filepath"
)

type GfxKind uint32

const (
	GfxBankNone = GfxKind(iota)
	GfxBank4bpp
	GfxBank8bpp
	GfxBank16bpp
	GfxBankCompressed
	GfxBankTerminate = GfxKind(0xFFFFFFFF)
)

type GfxEntry struct {
	X      uint16 `json:"x,omitempty"`
	Y      uint16 `json:"y,omitempty"`
	Width  uint16 `json:"width,omitempty"`
	Height uint16 `json:"height,omitempty"`
	addr   psx.Addr
	Name   string `json:"name,omitempty"`
}

func (e GfxEntry) isTerminate() bool {
	return e.X == 0xFFFF && e.Y == 0xFFFF
}

func (e GfxEntry) isEmpty() bool {
	return e.X == 0 && e.Y == 0 && e.Width == 0 && e.Height == 0
}

func (e GfxEntry) symbol() string {
	if e.Name == "" {
		return "NULL"
	}
	return util.RemoveFileNameExt(filepath.Base(e.Name))
}

type GfxBank struct {
	Kind    GfxKind    `json:"kind"`
	Entries []GfxEntry `json:"entries,omitempty"`
}

func (block GfxBank) isTerminate() bool {
	return block.Kind == GfxBankTerminate
}

type GfxBanks struct {
	Banks   []GfxBank `json:"banks"`
	Indices []int     `json:"indices"`
}

func ReadGraphics(r io.ReadSeeker, ramBase, addr psx.Addr, symbol func(addr psx.Addr) string) (GfxBanks, datarange.DataRange, error) {
	if err := addr.MoveFile(r, ramBase); err != nil {
		return GfxBanks{}, datarange.DataRange{}, err
	}
	var addrGfxBanks []psx.Addr
	for {
		var addrGfxBankEntry psx.Addr
		if err := binary.Read(r, binary.LittleEndian, &addrGfxBankEntry); err != nil {
			return GfxBanks{}, datarange.DataRange{}, err
		}
		// exception for ST0, where one of the bank offsets can point to NULL
		if addrGfxBankEntry == psx.RamNull {
			addrGfxBanks = append(addrGfxBanks, psx.RamNull)
			continue
		}
		// all the offsets are before the GFX banks array, so it is easy to find where the offsets array ends
		if !addrGfxBankEntry.InRange(ramBase, addr) {
			break
		}
		addrGfxBanks = append(addrGfxBanks, addrGfxBankEntry)
	}
	headerRange := datarange.FromAddr(addr, len(addrGfxBanks)*4)

	// the order of each GfxBank must be preserved
	pool := map[psx.Addr]int{}
	pool[psx.RamNull] = -1
	var banks []GfxBank
	var ranges []datarange.DataRange
	var newRange datarange.DataRange
	sortedBanks := util.SortAndFilterOffsets(addrGfxBanks)
	lastAddr := sortedBanks[len(sortedBanks)-1]
	for addrGfxBank := sortedBanks[0]; addrGfxBank <= lastAddr; addrGfxBank = newRange.End() {
		if err := addrGfxBank.MoveFile(r, ramBase); err != nil {
			return GfxBanks{}, datarange.DataRange{}, err
		}
		var bank GfxBank
		if err := binary.Read(r, binary.LittleEndian, &bank.Kind); err != nil {
			return GfxBanks{}, datarange.DataRange{}, err
		}
		if bank.isTerminate() { // ST0 exception where no gfx entries are found
			newRange = datarange.FromAddr(addrGfxBank, 4)
		} else {
			for {
				var entry GfxEntry
				_ = binary.Read(r, binary.LittleEndian, &entry.X)
				_ = binary.Read(r, binary.LittleEndian, &entry.Y)
				if entry.isTerminate() {
					break
				}
				_ = binary.Read(r, binary.LittleEndian, &entry.Width)
				_ = binary.Read(r, binary.LittleEndian, &entry.Height)
				_ = binary.Read(r, binary.LittleEndian, &entry.addr)
				if !entry.isEmpty() {
					entry.Name = symbol(entry.addr)
					if entry.Name == "" {
						entry.Name = fmt.Sprintf("D_%08X", uint32(entry.addr))
					}
				}
				bank.Entries = append(bank.Entries, entry)
			}
			alignment := 4
			if sotn.GetPlatform() == sotn.PlatformPSP {
				alignment = 8
			}
			newRange = datarange.FromAlignedAddr(addrGfxBank, 4+len(bank.Entries)*12+4, alignment)
		}
		pool[addrGfxBank] = len(banks)
		banks = append(banks, bank)
		ranges = append(ranges, newRange)
	}

	var g GfxBanks
	for _, addrGfxBank := range addrGfxBanks {
		g.Banks = banks
		g.Indices = append(g.Indices, pool[addrGfxBank])
	}
	return g, datarange.MergeDataRanges(append(ranges, headerRange)), nil
}
