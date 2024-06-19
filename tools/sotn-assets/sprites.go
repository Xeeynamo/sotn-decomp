package main

import (
	"encoding/binary"
	"fmt"
	"os"
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

func readSpriteBank(file *os.File, off PsxOffset) ([][]sprite, dataRange, error) {
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

	spriteBank := make([][]sprite, len(spriteOffsets))
	spriteRanges := []dataRange{}
	for i, offset := range spriteOffsets {
		if offset == RamNull {
			spriteBank[i] = []sprite{}
			continue
		}
		sprites, ranges, err := readSprites(file, offset)
		if err != nil {
			return nil, dataRange{}, fmt.Errorf("unable to read sprites: %w", err)
		}
		spriteBank[i] = sprites
		spriteRanges = append(spriteRanges, ranges)
	}

	return spriteBank, mergeDataRanges(append(spriteRanges, headerRange)), nil
}

func readSpritesBanks(file *os.File, off PsxOffset) ([][][]sprite, dataRange, error) {
	if err := off.moveFile(file); err != nil {
		return nil, dataRange{}, err
	}

	offBanks := make([]PsxOffset, 24)
	if err := binary.Read(file, binary.LittleEndian, offBanks); err != nil {
		return nil, dataRange{}, err
	}

	banks := [][][]sprite{}
	spriteRanges := []dataRange{}
	for _, bank := range offBanks {
		if bank == RamNull {
			banks = append(banks, [][]sprite{})
			continue
		}
		bank, bankRange, err := readSpriteBank(file, bank)
		if err != nil {
			return nil, dataRange{}, fmt.Errorf("unable to read sprite Indices: %w", err)
		}
		banks = append(banks, bank)
		spriteRanges = append(spriteRanges, bankRange)
	}

	return banks, mergeDataRanges(spriteRanges), nil
}
