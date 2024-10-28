package layout

import (
	"encoding/binary"
	"encoding/json"
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/datarange"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/util"
	"hash/fnv"
	"io"
	"os"
	"path"
	"sort"
	"strconv"
	"strings"
)

type layoutEntry struct {
	X       int16  `json:"x"`
	Y       int16  `json:"y"`
	ID      string `json:"id"`
	Flags   uint8  `json:"flags"` // TODO properly de-serialize this
	Slot    uint8  `json:"slot"`
	SpawnID uint8  `json:"spawnId"`
	Params  uint16 `json:"params"`
	YOrder  *int   `json:"yOrder,omitempty"`
}

type Layouts struct {
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
	var enumData []string
	inEnum := false
	for _, line := range lines {
		if strings.Contains(line, "EntityIDs") {
			if inEnum {
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
	for _, line := range enumData {
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
			index++
		}
		parts = strings.Split(parts[0], " ")
		name := parts[len(parts)-1]
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
func hydrateYOrderFields(x Layouts, y Layouts) error {
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

func ReadEntityLayout(file *os.File, off psx.Addr, count int, isX bool) (Layouts, []datarange.DataRange, error) {
	if err := off.MoveFile(file, psx.RamStageBegin); err != nil {
		return Layouts{}, nil, err
	}

	// there are two copies of the layout, one ordered by X and the other one ordered by Y
	// we will only read the first one, which is ordered by Y
	blockOffsets := make([]psx.Addr, count)
	if err := binary.Read(file, binary.LittleEndian, blockOffsets); err != nil {
		return Layouts{}, nil, err
	}

	// the order of each layout entry must be preserved
	pool := map[psx.Addr]int{}
	var blocks [][]layoutEntry
	var xRanges []datarange.DataRange
	for _, blockOffset := range util.SortUniqueOffsets(blockOffsets) {
		if err := blockOffset.MoveFile(file, psx.RamStageBegin); err != nil {
			return Layouts{}, nil, err
		}
		var entries []layoutEntry
		for {
			entry, err := readEntityLayoutEntry(file)
			if err != nil {
				return Layouts{}, nil, err
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
			return Layouts{}, nil, err
		}

		pool[blockOffset] = len(blocks)
		blocks = append(blocks, entries)
		xRanges = append(xRanges, datarange.FromAddr(blockOffset, len(entries)*10))
	}
	// the very last entry needs to be aligned by 4
	xRanges[len(xRanges)-1] = xRanges[len(xRanges)-1].Align4()

	l := Layouts{Entities: blocks}
	for _, blockOffset := range blockOffsets {
		l.Indices = append(l.Indices, pool[blockOffset])
	}

	endOfArray := off.Sum(count * 4)
	if isX { // we want to do the same thing with the vertically aligned layout
		yLayouts, yRanges, err := ReadEntityLayout(file, endOfArray, count, false)
		if err != nil {
			return Layouts{}, nil, fmt.Errorf("ReadEntityLayout failed on Y: %w", err)
		}
		if err := hydrateYOrderFields(l, yLayouts); err != nil {
			return Layouts{}, nil, fmt.Errorf("unable to populate YOrder field: %w", err)
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

func BuildEntityLayouts(fileName string, outputDir string) error {
	ovlName := path.Base(outputDir)

	writeLayoutEntries := func(sb *strings.Builder, banks [][]layoutEntry, align4 bool) error {
		nWritten := 0
		for i, entries := range banks {
			// do a sanity check on the entries as we do not want to build something that will cause the game to crash
			if entries[0].X != -2 || entries[0].Y != -2 {
				return fmt.Errorf("layout entity bank %d needs to have a X:-2 and Y:-2 entry at the beginning", i)
			}
			lastEntry := entries[len(entries)-1]
			if lastEntry.X != -1 || lastEntry.Y != -1 {
				return fmt.Errorf("layout entity bank %d needs to have a X:-1 and Y:-1 entry at the end", i)
			}
			sb.WriteString(fmt.Sprintf("//%d\n", nWritten)) //label each block with offsets
			for _, e := range entries {
				var entityIDStr string
				if int(e.Flags) != 0 {
					// This will only ever be 0xA001.
					id, _ := strconv.ParseInt(strings.Replace(e.ID, "0x", "", -1), 16, 16)
					entityIDStr = fmt.Sprintf("0x%04X", (int(e.Flags)<<8)|int(id))
				} else {
					entityIDStr = e.ID
				}
				sb.WriteString(fmt.Sprintf("    0x%04X, 0x%04X, %s, 0x%04X, 0x%04X,\n",
					uint16(e.X), uint16(e.Y), entityIDStr, int(e.Slot)|(int(e.SpawnID)<<8), e.Params))
			}
			nWritten += len(entries)
		}
		if align4 && nWritten%2 != 0 {
			sb.WriteString("    0, // padding\n")
		}
		return nil
	}
	makeSortedBanks := func(banks [][]layoutEntry, sortByX bool) [][]layoutEntry {
		var toSort []layoutEntry
		var less func(i, j int) bool
		if sortByX {
			less = func(i, j int) bool {
				return toSort[i].X < toSort[j].X
			}
		} else {
			less = func(i, j int) bool {
				if toSort[i].Y < toSort[j].Y {
					return true
				}
				if toSort[i].Y > toSort[j].Y {
					return false
				}
				if toSort[i].YOrder != nil && toSort[j].YOrder != nil {
					return *toSort[i].YOrder < *toSort[j].YOrder
				}
				return i < j
			}
		}
		sorting := make([][]layoutEntry, len(banks))
		for i, entries := range banks {
			sorting[i] = make([]layoutEntry, len(entries)-2)
			if len(sorting[i]) > 0 { // do not sort if the list is empty
				copy(sorting[i], entries[1:len(entries)-1]) // do not sort the -2 and -1 entries
				toSort = sorting[i]
				sort.SliceStable(toSort, less)
			}

			// put back the -2 and -1
			sorting[i] = append([]layoutEntry{entries[0]}, sorting[i]...)
			sorting[i] = append(sorting[i], entries[len(entries)-1])
		}
		return sorting
	}

	data, err := os.ReadFile(fileName)
	if err != nil {
		return err
	}

	var el Layouts
	if err := json.Unmarshal(data, &el); err != nil {
		return err
	}

	h := fnv.New32()
	_, _ = h.Write([]byte(outputDir))
	symbolVariant := strconv.FormatUint(uint64(h.Sum32()), 16)
	symbolName := fmt.Sprintf("entity_layout_%s", symbolVariant)
	offsets := make([]int, len(el.Entities))
	offsetCur := 0
	for i := 0; i < len(el.Entities); i++ {
		offsets[i] = offsetCur
		offsetCur += len(el.Entities[i]) * 5
	}

	sbHeader := strings.Builder{}
	sbHeader.WriteString("#include <stage.h>\n\n")
	sbHeader.WriteString("#include \"common.h\"\n\n")
	sbHeader.WriteString("// clang-format off\n")
	sbHeader.WriteString(fmt.Sprintf("extern LayoutEntity %s_x[];\n", symbolName))
	sbHeader.WriteString(fmt.Sprintf("LayoutEntity* %s_pStObjLayoutHorizontal[] = {\n", strings.ToUpper(ovlName)))
	for _, i := range el.Indices {
		sbHeader.WriteString(fmt.Sprintf("    &%s_x[%d],\n", symbolName, offsets[i]/5))
	}
	sbHeader.WriteString(fmt.Sprintf("};\n"))
	sbHeader.WriteString(fmt.Sprintf("extern LayoutEntity %s_y[];\n", symbolName))
	sbHeader.WriteString(fmt.Sprintf("LayoutEntity* %s_pStObjLayoutVertical[] = {\n", strings.ToUpper(ovlName)))
	for _, i := range el.Indices {
		sbHeader.WriteString(fmt.Sprintf("    &%s_y[%d],\n", symbolName, offsets[i]/5))
	}
	sbHeader.WriteString(fmt.Sprintf("};\n"))

	sbData := strings.Builder{}
	sbData.WriteString(fmt.Sprintf("#include \"%s.h\"\n\n", ovlName))
	sbData.WriteString("// clang-format off\n")
	sbData.WriteString(fmt.Sprintf("u16 %s_x[] = {\n", symbolName))
	if err := writeLayoutEntries(&sbData, makeSortedBanks(el.Entities, true), false); err != nil {
		return fmt.Errorf("unable to build X entity layout: %w", err)
	}
	sbData.WriteString(fmt.Sprintf("};\n"))
	sbData.WriteString(fmt.Sprintf("u16 %s_y[] = {\n", symbolName))
	if err := writeLayoutEntries(&sbData, makeSortedBanks(el.Entities, false), true); err != nil {
		return fmt.Errorf("unable to build Y entity layout: %w", err)
	}
	sbData.WriteString(fmt.Sprintf("};\n"))

	if err := os.WriteFile(path.Join(outputDir, "e_layout.c"), []byte(sbData.String()), 0644); err != nil {
		return err
	}
	return os.WriteFile(path.Join(outputDir, "e_laydef.c"), []byte(sbHeader.String()), 0644)
}
