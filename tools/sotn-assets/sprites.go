package main

import (
	"encoding/binary"
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"io"
	"sort"
)

type sprite struct {
	Flags   uint16 `json:"flags"`
	X       int16  `json:"x"`
	Y       int16  `json:"y"`
	Width   uint16 `json:"width"`
	Height  uint16 `json:"height"`
	Clut    uint16 `json:"clut"`
	Tileset uint16 `json:"tileset"`
	Left    uint16 `json:"left"`
	Top     uint16 `json:"top"`
	Right   uint16 `json:"right"`
	Bottom  uint16 `json:"bottom"`
}

type spriteDefs struct {
	Banks   [][]*[]sprite `json:"banks"`
	Indices []int         `json:"indices"`
}

func readSprites(r io.ReadSeeker, baseAddr, addr psx.Addr) ([]sprite, dataRange, error) {
	if err := addr.MoveFile(r, baseAddr); err != nil {
		return nil, dataRange{}, fmt.Errorf("invalid sprites: %w", err)
	}

	var count uint16
	if err := binary.Read(r, binary.LittleEndian, &count); err != nil {
		return nil, dataRange{}, err
	}

	sprites := make([]sprite, count)
	if err := binary.Read(r, binary.LittleEndian, sprites); err != nil {
		return nil, dataRange{}, err
	}

	return sprites, dataRange{
		begin: addr,
		end:   addr.Sum(4 + 0x16*int(count)).Align4(),
	}, nil
}

func readFrameSet(r io.ReadSeeker, baseAddr, addr psx.Addr) ([]*[]sprite, dataRange, error) {
	if err := addr.MoveFile(r, baseAddr); err != nil {
		return nil, dataRange{}, fmt.Errorf("invalid sprite Indices: %w", err)
	}

	// the end of the sprite array is the beginning of the earliest sprite offset
	earliestSpriteOff := psx.RamStageEnd
	currentOff := addr
	spriteOffsets := make([]psx.Addr, 0)
	for {
		if currentOff == earliestSpriteOff {
			break
		}
		currentOff += 4

		var spriteOffset psx.Addr
		if err := binary.Read(r, binary.LittleEndian, &spriteOffset); err != nil {
			return nil, dataRange{}, err
		}
		spriteOffsets = append(spriteOffsets, spriteOffset)
		if spriteOffset != psx.RamNull {
			if !spriteOffset.InRange(baseAddr, psx.RamGameEnd) {
				err := fmt.Errorf("sprite offset %s is not valid", spriteOffset)
				return nil, dataRange{}, err
			}
			earliestSpriteOff = min(earliestSpriteOff, spriteOffset)
		}
	}
	headerRange := dataRange{
		begin: addr,
		end:   earliestSpriteOff,
	}

	spriteBank := make([]*[]sprite, len(spriteOffsets))
	spriteRanges := []dataRange{}
	for i, offset := range spriteOffsets {
		if offset == psx.RamNull {
			spriteBank[i] = nil
			continue
		}
		sprites, ranges, err := readSprites(r, baseAddr, offset)
		if err != nil {
			return nil, dataRange{}, fmt.Errorf("unable to read sprites: %w", err)
		}
		spriteBank[i] = &sprites
		spriteRanges = append(spriteRanges, ranges)
	}

	return spriteBank, mergeDataRanges(append(spriteRanges, headerRange)), nil
}

func readSpritesBanks(r io.ReadSeeker, baseAddr, addr psx.Addr) (spriteDefs, dataRange, error) {
	if err := addr.MoveFile(r, baseAddr); err != nil {
		return spriteDefs{}, dataRange{}, err
	}

	// start with a capacity of 24 as that's the length for all the stage overlays
	offBanks := make([]psx.Addr, 0, 24)
	for {
		addr := psx.ReadAddr(r)
		if addr != psx.RamNull && !addr.InRange(baseAddr, psx.RamGameEnd) {
			break
		}
		offBanks = append(offBanks, addr)
	}
	r.Seek(-4, io.SeekCurrent)

	// the order sprites are stored must be preserved
	pool := map[psx.Addr][]*[]sprite{}
	spriteRanges := []dataRange{}
	for _, spriteAddr := range offBanks {
		if spriteAddr == psx.RamNull {
			continue
		}
		if _, found := pool[spriteAddr]; found {
			continue
		}
		bank, bankRange, err := readFrameSet(r, baseAddr, spriteAddr)
		if err != nil {
			return spriteDefs{}, dataRange{}, fmt.Errorf("unable to read sprite Indices: %w", err)
		}
		pool[spriteAddr] = bank
		spriteRanges = append(spriteRanges, bankRange)
	}

	// the indices do not guarantee sprites to be stored in a linear order
	// we must sort the offsets to preserve the order sprites are stored
	sortedOffsets := make([]psx.Addr, 0, len(pool))
	for offset := range pool {
		sortedOffsets = append(sortedOffsets, offset)
	}
	sort.Slice(sortedOffsets, func(i, j int) bool { return sortedOffsets[i] < sortedOffsets[j] })

	// create a list of indices to replace the original pointers
	indices := make([]int, len(offBanks))
	for i, offset := range offBanks {
		if offset == psx.RamNull {
			indices[i] = -1
		}
		for j, sortedOffset := range sortedOffsets {
			if offset == sortedOffset {
				indices[i] = j
			}
		}
	}

	banks := make([][]*[]sprite, len(sortedOffsets))
	for i, offset := range sortedOffsets {
		banks[i] = pool[offset]
	}

	return spriteDefs{
		Banks:   banks,
		Indices: indices,
	}, mergeDataRanges(spriteRanges), nil
}
