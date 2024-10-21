package main

import (
	"encoding/binary"
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/datarange"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"io"
	"os"
	"path"
	"strconv"
	"strings"
)

type layoutEntry struct {
	X       int16  `json:"x"`
	Y       int16  `json:"y"`
	ID      string  `json:"id"`
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

func fetchEntityIDsFromHFile(overlay string) (map[int]string, error) {
	// Get the EntityIDs enum from the .h file and invert it to get a lookup table
	// Keys are integers, values are the names from the enum.
	hFile, err := os.ReadFile("src/st/" + overlay + "/" + overlay + ".h")
	if err != nil {
		return nil, err
	}
	lines := strings.Split(string(hFile), "\n")
	// Extract all the lines that are part of the enum.
	// Do this by searching for the first "EntityIDs" (in typedef enum EntityIDs {)
	// and the last "EntityIDs" (in } EntityIDs;)
	enumData := []string{}
	inEnum := false
	for _,line := range lines {
		if strings.Contains(line, "EntityIDs"){
			if inEnum{
				break
			} else {
				inEnum = true
			}
		} else if inEnum {
			enumData = append(enumData, line)
		}
	}
	// Now we have the enum's lines loaded. Iterate through populating a map.
	entityNames := make(map[int]string, 255)
	// Increments in the enum, updates if enum has a direct assign
	index := -1 // start at -1 so first increment takes it to 0 to begin
	for _,line := range enumData {
		line = strings.Split(line, ",")[0] // go up to the comma
		parts := strings.Split(line, " = ")
		if len(parts) > 1 {
			hexVal := strings.Replace(parts[1], "0x", "", -1)
			// Windows nonsense, remove any \r that exists
			hexVal = strings.Replace(hexVal, "\r", "", -1)
			parsed, err := strconv.ParseInt(hexVal, 16, 16)
			if err != nil {
				return nil, err
			}
			index = int(parsed)
		} else {
			index ++
		}
		parts = strings.Split(parts[0], " ")
		name := parts[len(parts) - 1]
		entityNames[index] = name
	}
    return entityNames, nil
}

func readEntityLayoutEntry(file *os.File) (layoutEntry, error) {
	ovlName := strings.ToLower(path.Base(path.Dir(file.Name())))
	entityIDs, _ := fetchEntityIDsFromHFile(ovlName)

	bs := make([]byte, 10)
	if _, err := io.ReadFull(file, bs); err != nil {
		return layoutEntry{}, err
	}

	var entityIDStr string
	id := int(bs[4])
	// Try to load the proper enum
	entityIDStr = entityIDs[id]
	// If enum unknown or flags are set, override, don't use enums
	if entityIDStr == "" || bs[5] != 0 {
		entityIDStr = fmt.Sprintf("0x%02X", id)
	}

	return layoutEntry{
		X:       int16(binary.LittleEndian.Uint16(bs[0:2])),
		Y:       int16(binary.LittleEndian.Uint16(bs[2:4])),
		ID:      entityIDStr,
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

func readEntityLayout(file *os.File, off psx.Addr, count int, isX bool) (layouts, []datarange.DataRange, error) {
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
	xRanges := []datarange.DataRange{}
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
		xRanges = append(xRanges, datarange.FromAddr(blockOffset, len(entries)*10))
	}
	// the very last entry needs to be aligned by 4
	xRanges[len(xRanges)-1] = xRanges[len(xRanges)-1].Align4()

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
		xMerged := datarange.MergeDataRanges(xRanges)
		yMerged := yRanges[1]
		return l, []datarange.DataRange{
			datarange.MergeDataRanges([]datarange.DataRange{datarange.New(off, endOfArray), yRanges[0]}),
			datarange.MergeDataRanges([]datarange.DataRange{xMerged, yMerged}),
		}, nil
	} else {
		return l, []datarange.DataRange{datarange.New(off, endOfArray), datarange.MergeDataRanges(xRanges)}, nil
	}
}
