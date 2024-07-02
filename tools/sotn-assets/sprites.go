package main

import (
	"encoding/binary"
	"fmt"
	"os"
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

func readSprites(file *os.File, off PsxOffset) ([]sprite, dataRange, error) {
	if err := off.moveFile(file); err != nil {
		return nil, dataRange{}, fmt.Errorf("invalid sprites: %w", err)
	}

	var count uint16
	if err := binary.Read(file, binary.LittleEndian, &count); err != nil {
		return nil, dataRange{}, err
	}

	sprites := make([]sprite, count)
	if err := binary.Read(file, binary.LittleEndian, sprites); err != nil {
		return nil, dataRange{}, err
	}

	return sprites, dataRange{
		begin: off,
		end:   off.sum(4 + 0x16*int(count)).align4(),
	}, nil
}

func readSpriteBank(file *os.File, off PsxOffset) ([]*[]sprite, dataRange, error) {
	if err := off.moveFile(file); err != nil {
		return nil, dataRange{}, fmt.Errorf("invalid sprite Indices: %w", err)
	}

	// the end of the sprite array is the beginning of the earliest sprite offset
	earliestSpriteOff := RamStageEnd
	currentOff := off
	spriteOffsets := make([]PsxOffset, 0)
	for {
		if currentOff == earliestSpriteOff {
			break
		}
		currentOff += 4

		var spriteOffset PsxOffset
		if err := binary.Read(file, binary.LittleEndian, &spriteOffset); err != nil {
			return nil, dataRange{}, err
		}
		spriteOffsets = append(spriteOffsets, spriteOffset)
		if spriteOffset != RamNull {
			if !spriteOffset.valid() {
				err := fmt.Errorf("sprite offset %s is not valid", spriteOffset)
				return nil, dataRange{}, err
			}
			earliestSpriteOff = min(earliestSpriteOff, spriteOffset)
		}
	}
	headerRange := dataRange{
		begin: off,
		end:   earliestSpriteOff,
	}

	spriteBank := make([]*[]sprite, len(spriteOffsets))
	spriteRanges := []dataRange{}
	for i, offset := range spriteOffsets {
		if offset == RamNull {
			spriteBank[i] = nil
			continue
		}
		sprites, ranges, err := readSprites(file, offset)
		if err != nil {
			return nil, dataRange{}, fmt.Errorf("unable to read sprites: %w", err)
		}
		spriteBank[i] = &sprites
		spriteRanges = append(spriteRanges, ranges)
	}

	return spriteBank, mergeDataRanges(append(spriteRanges, headerRange)), nil
}

func readSpritesBanks(file *os.File, off PsxOffset) (spriteDefs, dataRange, error) {
	if err := off.moveFile(file); err != nil {
		return spriteDefs{}, dataRange{}, err
	}

	offBanks := make([]PsxOffset, 24)
	if err := binary.Read(file, binary.LittleEndian, offBanks); err != nil {
		return spriteDefs{}, dataRange{}, err
	}

	// the order sprites are stored must be preserved
	pool := map[PsxOffset][]*[]sprite{}
	spriteRanges := []dataRange{}
	for _, offset := range offBanks {
		if offset == RamNull {
			continue
		}
		if _, found := pool[offset]; found {
			continue
		}
		bank, bankRange, err := readSpriteBank(file, offset)
		if err != nil {
			return spriteDefs{}, dataRange{}, fmt.Errorf("unable to read sprite Indices: %w", err)
		}
		pool[offset] = bank
		spriteRanges = append(spriteRanges, bankRange)
	}

	// the indices do not guarantee sprites to be stored in a linear order
	// we must sort the offsets to preserve the order sprites are stored
	sortedOffsets := make([]PsxOffset, 0, len(pool))
	for offset := range pool {
		sortedOffsets = append(sortedOffsets, offset)
	}
	sort.Slice(sortedOffsets, func(i, j int) bool { return sortedOffsets[i] < sortedOffsets[j] })

	// create a list of indices to replace the original pointers
	indices := make([]int, len(offBanks))
	for i, offset := range offBanks {
		if offset == RamNull {
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
