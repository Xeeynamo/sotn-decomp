package main

import (
	"encoding/binary"
	"fmt"
	"os"
)

type layoutEntry struct {
	X      uint16 `json:"x"`
	Y      uint16 `json:"y"`
	ID     uint16 `json:"id"`
	Slot   uint16 `json:"slot"`
	Params uint16 `json:"params"`
}

type layouts struct {
	Entities [][]layoutEntry `json:"entities"`
	Indices  []int           `json:"indices"`
}

func readEntityLayout(file *os.File, off PsxOffset, count int, isX bool) (layouts, []dataRange, error) {

	if err := off.moveFile(file); err != nil {
		return layouts{}, nil, err
	}

	// there are two copies of the layout, one ordered by X and the other one ordered by Y
	// we will only read the first one, which is ordered by Y
	blockOffsets := make([]PsxOffset, count)
	if err := binary.Read(file, binary.LittleEndian, blockOffsets); err != nil {
		return layouts{}, nil, err
	}

	// the order of each layout entry must be preserved
	pool := map[PsxOffset]int{}
	blocks := [][]layoutEntry{}
	xRanges := []dataRange{}
	for _, blockOffset := range sortUniqueOffsets(blockOffsets) {
		if err := blockOffset.moveFile(file); err != nil {
			return layouts{}, nil, err
		}
		entries := []layoutEntry{}
		for {
			var entry layoutEntry
			if err := binary.Read(file, binary.LittleEndian, &entry); err != nil {
				return layouts{}, nil, err
			}
			if entry.X == 0xFFFF && entry.Y == 0xFFFF {
				break
			}
			entries = append(entries, entry)
		}

		// sanity check on the first entry
		if entries[0].X != 0xFFFE || entries[0].Y != 0xFFFE {
			err := fmt.Errorf("first layout entry does not mark the beginning of the array: %v", entries[0])
			return layouts{}, nil, err
		}
		entries = entries[1:] // both first and last items are terminators, ignore them

		pool[blockOffset] = len(blocks)
		blocks = append(blocks, entries)
		xRanges = append(xRanges, dataRange{
			begin: blockOffset,
			end:   blockOffset.sum((len(entries) + 2) * 10),
		})
	}
	// the very last entry needs to be aligned by 4
	xRanges[len(xRanges)-1].end = xRanges[len(xRanges)-1].end.align4()

	l := layouts{Entities: blocks}
	for _, blockOffset := range blockOffsets {
		l.Indices = append(l.Indices, pool[blockOffset])
	}

	endOfArray := off.sum(count * 4)
	if isX { // we want to do the same thing with the vertically aligned layout
		_, yRanges, err := readEntityLayout(file, endOfArray, count, false)
		if err != nil {
			err := fmt.Errorf("readEntityLayout failed on Y: %w", err)
			return layouts{}, nil, err
		}
		xMerged := mergeDataRanges(xRanges)
		yMerged := yRanges[1]
		fmt.Printf("%+v\n", yMerged)
		return l, []dataRange{
			mergeDataRanges([]dataRange{
				{
					begin: off,
					end:   endOfArray,
				},
				yRanges[0],
			}),
			mergeDataRanges([]dataRange{xMerged, yMerged}),
		}, nil
	} else {
		return l, []dataRange{
			{
				begin: off,
				end:   endOfArray,
			},
			mergeDataRanges(xRanges),
		}, nil
	}
}
