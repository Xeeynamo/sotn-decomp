package main

import (
	"encoding/json"
	"errors"
	"fmt"
	"golang.org/x/sync/errgroup"
	"hash/fnv"
	"io"
	"io/fs"
	"os"
	"path"
	"sort"
	"strconv"
	"strings"
)

func makeSymbolFromFileName(fileName string) string {
	return strings.Split(path.Base(fileName), ".")[0]
}

func writeStaticU8(w io.Writer, fileName string, symbol string) error {
	data, err := os.ReadFile(fileName)
	if err != nil {
		return err
	}

	var sb strings.Builder
	sb.WriteString("// clang-format off\n")
	sb.WriteString(fmt.Sprintf("static unsigned char %s[] = {\n", symbol))
	for i := 0; i < len(data); i++ {
		sb.WriteString(fmt.Sprintf("0x%02X,", data[i]))
		if (i & 15) == 15 {
			sb.WriteString("\n")
		}
	}
	sb.WriteString("};\n")

	_, err = w.Write([]byte(sb.String()))
	return err
}

func buildGenericU16(fileName string, symbol string, outputDir string) error {
	data, err := os.ReadFile(fileName)
	if err != nil {
		return err
	}

	var sb strings.Builder
	sb.WriteString("// clang-format off\n")
	sb.WriteString(fmt.Sprintf("u16 %s[] = {\n", symbol))
	for i := 0; i < len(data); i += 2 {
		sb.WriteString(fmt.Sprintf("0x%02X%02X,", data[i+1], data[i]))
		if (i & 31) == 30 {
			sb.WriteString("\n")
		}
	}
	sb.WriteString("};\n")

	return os.WriteFile(path.Join(outputDir, fmt.Sprintf("%s.h", symbol)), []byte(sb.String()), 0644)
}

func buildTiledefs(fileName string, symbol string, outputDir string) error {
	data, err := os.ReadFile(fileName)
	if err != nil {
		return err
	}

	var tiledef tileDefPaths
	if err := json.Unmarshal(data, &tiledef); err != nil {
		return err
	}

	f, err := os.Create(path.Join(outputDir, fmt.Sprintf("%s.h", symbol)))
	if err != nil {
		return err
	}
	defer f.Close()

	tilesSymbol := makeSymbolFromFileName(tiledef.Tiles)
	tilesFileName := path.Join(path.Dir(fileName), tiledef.Tiles)
	if err := writeStaticU8(f, tilesFileName, tilesSymbol); err != nil {
		return err
	}

	pagesSymbol := makeSymbolFromFileName(tiledef.Pages)
	pagesFileName := path.Join(path.Dir(fileName), tiledef.Pages)
	if err := writeStaticU8(f, pagesFileName, pagesSymbol); err != nil {
		return err
	}

	clutsSymbol := makeSymbolFromFileName(tiledef.Cluts)
	clutsFileName := path.Join(path.Dir(fileName), tiledef.Cluts)
	if err := writeStaticU8(f, clutsFileName, clutsSymbol); err != nil {
		return err
	}

	colsSymbol := makeSymbolFromFileName(tiledef.Collisions)
	colsFileName := path.Join(path.Dir(fileName), tiledef.Collisions)
	if err := writeStaticU8(f, colsFileName, colsSymbol); err != nil {
		return err
	}

	_, _ = f.WriteString("// clang-format off\n")
	_, _ = f.WriteString(fmt.Sprintf("TileDefinition %s[] = {\n", symbol))
	_, _ = f.WriteString(fmt.Sprintf("    %s,\n", tilesSymbol))
	_, _ = f.WriteString(fmt.Sprintf("    %s,\n", pagesSymbol))
	_, _ = f.WriteString(fmt.Sprintf("    %s,\n", clutsSymbol))
	_, _ = f.WriteString(fmt.Sprintf("    %s,\n", colsSymbol))
	_, _ = f.WriteString("};\n")

	return nil
}

func buildLayers(inputDir string, fileName string, outputDir string) error {
	getHash := func(l layerUnpacked) string {
		return fmt.Sprintf("%s-%s-%d-%d-%d-%d", l.Data, l.Tiledef, l.Left, l.Top, l.Right, l.Bottom)
	}
	pack := func(l layerUnpacked) map[string]interface{} {
		return map[string]interface{}{
			"data":    makeSymbolFromFileName(l.Data),
			"tiledef": makeSymbolFromFileName(l.Tiledef),
			"params": l.Left | (l.Top << 6) | (l.Right << 12) | (l.Bottom << 18) | (l.ScrollMode << 24) |
				(btoi(l.IsSaveRoom) << 29) | (btoi(l.IsLoadingRoom) << 30) | (btoi(l.UnusedFlag) << 31),
			"zPriority": l.ZPriority,
			"unkE":      l.UnkE,
			"unkF":      l.UnkF,
		}
	}

	data, err := os.ReadFile(fileName)
	if err != nil {
		return err
	}

	var roomsLayers []map[string]*layerUnpacked
	if err := json.Unmarshal(data, &roomsLayers); err != nil {
		return err
	}

	tilemaps := map[string]struct{}{}
	tiledefs := map[string]struct{}{}
	for _, room := range roomsLayers {
		// the split on '.' is to remove the extension
		if layer, found := room["fg"]; found {
			tilemaps[layer.Data] = struct{}{}
			tiledefs[layer.Tiledef] = struct{}{}
		}
		if layer, found := room["bg"]; found {
			tilemaps[layer.Data] = struct{}{}
			tiledefs[layer.Tiledef] = struct{}{}
		}
	}

	// use unused tiledefs
	files, err := os.ReadDir(inputDir)
	if err != nil {
		return err
	}
	for _, file := range files {
		if !file.IsDir() && strings.HasPrefix(file.Name(), "tiledef_") && strings.HasSuffix(file.Name(), ".json") {
			tiledefs[file.Name()] = struct{}{}
		}
	}

	eg := errgroup.Group{}
	for name := range tilemaps {
		fullPath := path.Join(path.Dir(fileName), name)
		symbol := makeSymbolFromFileName(name)
		eg.Go(func() error {
			return buildGenericU16(fullPath, symbol, outputDir)
		})
	}
	for name := range tiledefs {
		fullPath := path.Join(path.Dir(fileName), name)
		symbol := makeSymbolFromFileName(name)
		eg.Go(func() error {
			return buildTiledefs(fullPath, symbol, outputDir)
		})
	}
	if err := eg.Wait(); err != nil {
		return err
	}

	layers := []map[string]interface{}{} // first layer is always empty
	layers = append(layers, map[string]interface{}{})
	roomLayersId := make([]int, len(roomsLayers)*2)
	pool := map[string]int{}
	pool[""] = 0
	for _, rl := range roomsLayers {
		if l, fgFound := rl["fg"]; fgFound {
			hash := getHash(*l)
			if index, found := pool[hash]; !found {
				pool[hash] = len(layers)
				roomLayersId = append(roomLayersId, len(layers))
				layers = append(layers, pack(*l))
			} else {
				roomLayersId = append(roomLayersId, index)
			}
		} else {
			roomLayersId = append(roomLayersId, 0)
		}
		if l, bgFound := rl["bg"]; bgFound {
			hash := getHash(*l)
			if index, found := pool[hash]; !found {
				pool[hash] = len(layers)
				roomLayersId = append(roomLayersId, len(layers))
				layers = append(layers, pack(*l))
			} else {
				roomLayersId = append(roomLayersId, index)
			}
		} else {
			roomLayersId = append(roomLayersId, 0)
		}
	}

	sb := strings.Builder{}
	sb.WriteString("// clang-format off\n")
	for name := range tilemaps {
		symbol := makeSymbolFromFileName(name)
		sb.WriteString(fmt.Sprintf("extern u16 %s[];\n", symbol))
	}
	for name := range tiledefs {
		symbol := makeSymbolFromFileName(name)
		sb.WriteString(fmt.Sprintf("extern TileDefinition %s[];\n", symbol))
	}

	sb.WriteString("static MyLayer layers[] = {\n")
	sb.WriteString("    { NULL, NULL, 0, 0, 0, 0 },\n")
	for _, l := range layers[1:] {
		sb.WriteString(fmt.Sprintf("    { %s, %s, 0x%08X, 0x%02X, %d, %d },\n",
			makeSymbolFromFileName(l["data"].(string)),
			makeSymbolFromFileName(l["tiledef"].(string)),
			l["params"],
			l["zPriority"],
			l["unkE"],
			l["unkF"],
		))
	}
	sb.WriteString("};\n")

	sb.WriteString("MyRoomDef OVL_EXPORT(rooms_layers)[] = {\n")
	for _, rl := range roomsLayers {
		if l, found := rl["fg"]; found {
			sb.WriteString(fmt.Sprintf("    { &layers[%d], ", pool[getHash(*l)]))
		} else {
			sb.WriteString(fmt.Sprintf("    { &layers[0], "))
		}
		if l, found := rl["bg"]; found {
			sb.WriteString(fmt.Sprintf("&layers[%d] },\n", pool[getHash(*l)]))
		} else {
			sb.WriteString(fmt.Sprintf("&layers[0] },\n"))
		}
	}
	sb.WriteString("};\n")
	return os.WriteFile(path.Join(outputDir, "layers.h"), []byte(sb.String()), 0644)
}

func buildEntityLayouts(fileName string, outputDir string) error {
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

	var el layouts
	if err := json.Unmarshal(data, &el); err != nil {
		return err
	}

	h := fnv.New32()
	h.Write([]byte(outputDir))
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

func buildAll(inputDir string, outputDir string) error {
	if err := os.MkdirAll(outputDir, 0755); err != nil {
		return err
	}

	eg := errgroup.Group{}
	eg.Go(func() error {
		if err := buildLayers(inputDir, path.Join(inputDir, "layers.json"), outputDir); err != nil {
			if !errors.Is(err, fs.ErrNotExist) {
				return err
			}
		}
		return nil
	})
	eg.Go(func() error {
		if err := buildEntityLayouts(path.Join(inputDir, "entity_layouts.json"), outputDir); err != nil {
			if !errors.Is(err, fs.ErrNotExist) {
				return err
			}
		}
		return nil
	})

	return eg.Wait()
}
