package main

import (
	"encoding/binary"
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"io"
	"os"
)

type layoutEntry struct {
	X       int16  `json:"x"`
	Y       int16  `json:"y"`
	ID      uint8  `json:"id"`
	Flags   uint8  `json:"flags"` // TODO properly de-serialize this
	Slot    uint8  `json:"slot"`
	SpawnID uint8  `json:"spawnId"`
	Params  uint16 `json:"params"`
	YOrder  *int   `json:"yOrder,omitempty"`
}

type layouts struct {
	Entities [][]layoutEntry `json:"entities"`
	Indices  []int           `json:"indices"`
}

func readEntityLayoutEntry(file *os.File) (layoutEntry, error) {
	bs := make([]byte, 10)
	if _, err := io.ReadFull(file, bs); err != nil {
		return layoutEntry{}, err
	}
	return layoutEntry{
		X:       int16(binary.LittleEndian.Uint16(bs[0:2])),
		Y:       int16(binary.LittleEndian.Uint16(bs[2:4])),
		ID:      bs[4],
		Flags:   bs[5],
		Slot:    bs[6],
		SpawnID: bs[7],
		Params:  binary.LittleEndian.Uint16(bs[8:10]),
	}, nil
}

// the Y-ordered entries list has a different order than the X-ordered one. The order cannot consistently get
// restored by just sorting entries by Y as usually entries with the same Y results swapped.
// This algorithm will fill the optional field YOrder, only useful to restore the original order.
func hydrateYOrderFields(x layouts, y layouts) error {
	if len(x.Indices) != len(y.Indices) {
		return fmt.Errorf("number of X and Y layout indices do not match")
	}
	if len(x.Entities) != len(y.Entities) {
		return fmt.Errorf("number of X and Y layout entries do not match")
	}

	populateYOrderField := func(xEntries []layoutEntry, yEntries []layoutEntry) {
		yIndexMap := make(map[layoutEntry]int, len(yEntries))
		for i, e := range yEntries {
			yIndexMap[e] = i
		}
		for i := 0; i < len(xEntries); i++ {
			if yOrder, found := yIndexMap[xEntries[i]]; found {
				xEntries[i].YOrder = &yOrder
			}
		}
	}

	for i := 0; i < len(x.Entities); i++ {
		xList := x.Entities[i]
		yList := y.Entities[i]
		if len(xList) != len(yList) {
			return fmt.Errorf("number of X and Y entries do not match")
		}
		populateYOrderField(xList, yList)
	}
	return nil
}

func readEntityLayout(file *os.File, off psx.Addr, count int, isX bool) (layouts, []dataRange, error) {
	if err := off.MoveFile(file, psx.RamStageBegin); err != nil {
		return layouts{}, nil, err
	}

	// there are two copies of the layout, one ordered by X and the other one ordered by Y
	// we will only read the first one, which is ordered by Y
	blockOffsets := make([]psx.Addr, count)
	if err := binary.Read(file, binary.LittleEndian, blockOffsets); err != nil {
		return layouts{}, nil, err
	}

	// the order of each layout entry must be preserved
	pool := map[psx.Addr]int{}
	blocks := [][]layoutEntry{}
	xRanges := []dataRange{}
	for _, blockOffset := range sortUniqueOffsets(blockOffsets) {
		if err := blockOffset.MoveFile(file, psx.RamStageBegin); err != nil {
			return layouts{}, nil, err
		}
		entries := []layoutEntry{}
		for {
			entry, err := readEntityLayoutEntry(file)
			if err != nil {
				return layouts{}, nil, err
			}
			if entry.X == -1 && entry.Y == -1 {
				entries = append(entries, entry)
				break
			}
			entries = append(entries, entry)
		}

		// sanity check on the first entry
		if entries[0].X != -2 || entries[0].Y != -2 {
			err := fmt.Errorf("first layout entry does not mark the beginning of the array: %v", entries[0])
			return layouts{}, nil, err
		}

		pool[blockOffset] = len(blocks)
		blocks = append(blocks, entries)
		xRanges = append(xRanges, dataRange{
			begin: blockOffset,
			end:   blockOffset.Sum(len(entries) * 10),
		})
	}
	// the very last entry needs to be aligned by 4
	xRanges[len(xRanges)-1].end = xRanges[len(xRanges)-1].end.Align4()

	l := layouts{Entities: blocks}
	for _, blockOffset := range blockOffsets {
		l.Indices = append(l.Indices, pool[blockOffset])
	}

	endOfArray := off.Sum(count * 4)
	if isX { // we want to do the same thing with the vertically aligned layout
		yLayouts, yRanges, err := readEntityLayout(file, endOfArray, count, false)
		if err != nil {
			return layouts{}, nil, fmt.Errorf("readEntityLayout failed on Y: %w", err)
		}
		if err := hydrateYOrderFields(l, yLayouts); err != nil {
			return layouts{}, nil, fmt.Errorf("unable to populate YOrder field: %w", err)
		}
		xMerged := mergeDataRanges(xRanges)
		yMerged := yRanges[1]
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
