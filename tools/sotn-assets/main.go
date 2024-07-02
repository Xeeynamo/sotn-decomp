package main

import (
	"encoding/binary"
	"encoding/json"
	"flag"
	"fmt"
	"os"
	"path"
)

type dataContainer[T any] struct {
	dataRange dataRange
	content   T
}

type ovl struct {
	ranges            []dataRange
	rooms             dataContainer[[]room]
	layers            dataContainer[[]roomLayers]
	sprites           dataContainer[spriteDefs]
	graphics          dataContainer[gfx]
	layouts           dataContainer[layouts]
	layoutsExtraRange dataRange
	tileMaps          dataContainer[map[PsxOffset][]byte]
	tileDefs          dataContainer[map[PsxOffset]tileDef]
}

func getOvlAssets(fileName string) (ovl, error) {
	type stageHeader struct {
		FnUpdate              PsxOffset
		FnHitDetection        PsxOffset
		FnUpdateRoomPos       PsxOffset
		FnInitRoomEntities    PsxOffset
		Rooms                 PsxOffset // ✅
		Sprites               PsxOffset // ✅
		Cluts                 PsxOffset // 🫥
		Layouts               PsxOffset // ✅
		Layers                PsxOffset // ✅
		Graphics              PsxOffset // 🫥 WIP
		FnUpdateStageEntities PsxOffset
	}

	file, err := os.Open(fileName)
	if err != nil {
		return ovl{}, err
	}
	defer file.Close()

	var header stageHeader
	if err := binary.Read(file, binary.LittleEndian, &header); err != nil {
		return ovl{}, err
	}

	rooms, roomsRange, err := readRooms(file, header.Rooms)
	if err != nil {
		return ovl{}, fmt.Errorf("unable to read rooms: %w", err)
	}

	layers, layersRange, err := readLayers(file, header.Layers)
	if err != nil {
		return ovl{}, fmt.Errorf("unable to read layers: %w", err)
	}

	tileMaps, tileMapsRange, err := readAllTileMaps(file, layers)
	if err != nil {
		return ovl{}, fmt.Errorf("unable to gather all the tile maps: %w", err)
	}

	tileDefs, tileDefsRange, err := readAllTiledefs(file, layers)
	if err != nil {
		return ovl{}, fmt.Errorf("unable to gather all the tile defs: %w", err)
	}

	// check for unused tile defs (CEN has one)
	for tileMapsRange.end < tileDefsRange.begin {
		offset := tileDefsRange.begin.sum(-0x10)
		unusedTileDef, unusedTileDefRange, err := readTiledef(file, offset)
		if err != nil {
			return ovl{}, fmt.Errorf("there is a gap between tileMaps and tileDefs: %w", err)
		}
		tileDefs[offset] = unusedTileDef
		tileDefsRange = mergeDataRanges([]dataRange{tileDefsRange, unusedTileDefRange})
	}

	sprites, spritesRange, err := readSpritesBanks(file, header.Sprites)
	if err != nil {
		return ovl{}, fmt.Errorf("unable to gather all sprites: %w", err)
	}

	graphics, graphicsRange, err := readGraphics(file, header.Graphics)
	if err != nil {
		return ovl{}, fmt.Errorf("unable to gather all graphics: %w", err)
	}

	layoutOff := header.Layouts
	if layoutOff == RamNull {
		// some overlays have this field nulled, we have to find the offset ourselves
		// it should be usually be right after header.Graphics
		layoutOff = graphicsRange.end // ⚠️ assumption
	}
	nLayouts := maxBy(rooms, func(r room) int { // ⚠️ assumption
		return int(r.EntityLayoutID)
	}) + 1
	nLayouts = 53 // it seems there are always 53 elements?!
	entityLayouts, layoutsRange, err := readEntityLayout(file, layoutOff, nLayouts, true)
	if err != nil {
		return ovl{}, fmt.Errorf("unable to gather all entity layouts: %w", err)
	}

	return ovl{
		ranges: consolidateDataRanges([]dataRange{
			roomsRange,
			layersRange,
			spritesRange,
			graphicsRange,
			layoutsRange[0],
			layoutsRange[1],
			tileMapsRange,
			tileDefsRange,
		}),
		rooms:             dataContainer[[]room]{dataRange: roomsRange, content: rooms},
		layers:            dataContainer[[]roomLayers]{dataRange: layersRange, content: layers},
		sprites:           dataContainer[spriteDefs]{dataRange: spritesRange, content: sprites},
		graphics:          dataContainer[gfx]{dataRange: graphicsRange, content: graphics},
		layouts:           dataContainer[layouts]{dataRange: layoutsRange[1], content: entityLayouts},
		layoutsExtraRange: layoutsRange[0],
		tileMaps:          dataContainer[map[PsxOffset][]byte]{dataRange: tileMapsRange, content: tileMaps},
		tileDefs:          dataContainer[map[PsxOffset]tileDef]{dataRange: tileDefsRange, content: tileDefs},
	}, nil
}

func extractOvlAssets(o ovl, outputDir string) error {
	if err := os.MkdirAll(outputDir, 0755); err != nil {
		return err
	}

	content, err := json.MarshalIndent(o.rooms.content, "", "  ")
	if err != nil {
		return err
	}
	if err := os.WriteFile(path.Join(outputDir, "rooms.json"), content, 0644); err != nil {
		return fmt.Errorf("unable to create rooms file: %w", err)
	}

	content, err = json.MarshalIndent(o.layers.content, "", "  ")
	if err != nil {
		return err
	}
	if err := os.WriteFile(path.Join(outputDir, "layers.json"), content, 0644); err != nil {
		return fmt.Errorf("unable to create layers file: %w", err)
	}

	content, err = json.MarshalIndent(o.layouts.content, "", "  ")
	if err != nil {
		return err
	}
	if err := os.WriteFile(path.Join(outputDir, "entity_layouts.json"), content, 0644); err != nil {
		return fmt.Errorf("unable to create entity layouts file: %w", err)
	}

	for offset, bytes := range o.tileMaps.content {
		fileName := path.Join(outputDir, getTilemapFileName(offset))
		if err := os.WriteFile(fileName, bytes, 0644); err != nil {
			return fmt.Errorf("unable to create %q: %w", fileName, err)
		}
	}

	for offset, tileDefsData := range o.tileDefs.content {
		defs := tileDefPaths{
			Tiles:      getTiledefIndicesFileName(offset),
			Pages:      getTiledefPagesFileName(offset),
			Cluts:      getTiledefClutsFileName(offset),
			Collisions: getTiledefCollisionsFileName(offset),
		}
		if err := os.WriteFile(path.Join(outputDir, defs.Tiles), tileDefsData.tiles, 0644); err != nil {
			return fmt.Errorf("unable to create %q: %w", defs.Tiles, err)
		}
		if err := os.WriteFile(path.Join(outputDir, defs.Pages), tileDefsData.pages, 0644); err != nil {
			return fmt.Errorf("unable to create %q: %w", defs.Pages, err)
		}
		if err := os.WriteFile(path.Join(outputDir, defs.Cluts), tileDefsData.cluts, 0644); err != nil {
			return fmt.Errorf("unable to create %q: %w", defs.Cluts, err)
		}
		if err := os.WriteFile(path.Join(outputDir, defs.Collisions), tileDefsData.cols, 0644); err != nil {
			return fmt.Errorf("unable to create %q: %w", defs.Collisions, err)
		}

		content, err = json.MarshalIndent(defs, "", "  ")
		if err != nil {
			return err
		}
		fileName := path.Join(outputDir, getTiledefFileName(offset))
		if err := os.WriteFile(fileName, content, 0644); err != nil {
			return fmt.Errorf("unable to create %q: %w", fileName, err)
		}
	}

	content, err = json.MarshalIndent(o.sprites.content, "", "  ")
	if err != nil {
		return err
	}
	if err := os.WriteFile(path.Join(outputDir, "sprites.json"), content, 0644); err != nil {
		return fmt.Errorf("unable to create sprites file: %w", err)
	}

	return nil
}

func extract(fileName string, outputDir string) error {
	o, err := getOvlAssets(fileName)
	if err != nil {
		return fmt.Errorf("unable to retrieve OVL assets: %w", err)
	}

	err = extractOvlAssets(o, outputDir)
	if err != nil {
		return fmt.Errorf("unable to extract OVL assets: %w", err)
	}

	return nil
}

func info(fileName string) error {
	o, err := getOvlAssets(fileName)
	if err != nil {
		return fmt.Errorf("unable to retrieve OVL assets: %w", err)
	}

	entries := []struct {
		dataRange dataRange
		name      string
		comment   string
	}{
		{o.layers.dataRange, "header", "layers"},
		{o.layoutsExtraRange, "e_laydef", "layout entries header"},
		{o.rooms.dataRange, "rooms", ""},
		{o.layouts.dataRange, "e_layout", "layout entries data"},
		{o.tileMaps.dataRange, "tile_data", "tile data"},
		{o.tileDefs.dataRange, "tile_data", "tile definitions"},
		{o.sprites.dataRange, "sprites", ""},
	}

	fmt.Printf("data coverage: %+v\n", o.ranges)
	fmt.Println("subsegment hints:")
	fmt.Println("  - [0x0, .data, header]")
	for i := 0; i < len(entries); i++ {
		e := entries[i]
		s := fmt.Sprintf("  - [0x%X, .data, %s]", e.dataRange.begin.real(), e.name)
		if e.comment != "" {
			s = fmt.Sprintf("%s # %s", s, e.comment)
		}
		fmt.Println(s)

		// if there is a gap between the current entry and the next one, mark it as unrecognized data
		if i == len(entries)-1 || e.dataRange.end != entries[i+1].dataRange.begin {
			fmt.Printf("  - [0x%X, data]\n", e.dataRange.end.real())
		}
	}
	return nil
}

func testStuff() {
	_ = []string{
		"ARE", "CAT", "CEN", "CHI", "DAI", "DRE", "LIB", "MAD",
		"NO0", "NO1", "NO2", "NO3", "NO4", "NP3", "NZ0", "NZ1",
		"ST0", "TE1", "TE2", "TE3", "TE4", "TE5", "TOP", "WRP",
		"RARE", "RCAT", "RCEN", "RCHI", "RDAI", "RLIB", "RNO0", "RNO1",
		"RNO2", "RNO3", "RNO4", "RNZ0", "RNZ1", "RTOP", "RWRP"}
	//ovls := []string{
	//	/*"ARE",*/ "CAT", "CEN", "CHI" /*"DAI",*/, "DRE", "LIB", /*"MAD",*/
	//	/*"NO0",*/ "NO1", "NO2", "NO3" /*"NO4",*/, "NP3", "NZ0", "NZ1",
	//	"ST0", "TE1", "TE2", "TE3", "TE4", "TE5" /*"TOP",*/, "WRP",
	//	"RARE", "RCAT" /*"RCEN",*/, "RCHI" /*"RDAI",*/ /*"RLIB",*/ /*"RNO0",*/, "RNO1",
	//	/*"RNO2",*/ "RNO3" /*"RNO4",*/ /*"RNZ0",*/ /*"RNZ1",*/ /*"RTOP",*/, "RWRP"}
	ovls := []string{"NZ0"}

	for _, ovl := range ovls {
		fmt.Printf("processing %s...\n", ovl)
		fileName := fmt.Sprintf("../../disks/us/ST/%s/%s.BIN", ovl, ovl)
		if err := extract(fileName, "sample/"+ovl); err != nil {
			panic(err)
		}
	}

	if err := buildAll("sample/NZ0", "buildAll/nz0"); err != nil {
		panic(err)
	}
}

func main() {
	if len(os.Args) < 2 {
		fmt.Println("expected 'info', 'extract', 'build' or 'build_all' subcommands")
		os.Exit(1)
	}

	switch os.Args[1] {
	case "info":
		extractCmd := flag.NewFlagSet("info", flag.ExitOnError)
		var stageOvl string
		extractCmd.StringVar(&stageOvl, "stage_ovl", "", "The overlay file to process")
		extractCmd.Parse(os.Args[2:])
		if err := info(stageOvl); err != nil {
			panic(err)
		}

	case "extract":
		extractCmd := flag.NewFlagSet("extract", flag.ExitOnError)
		var stageOvl string
		var assetDir string
		extractCmd.StringVar(&stageOvl, "stage_ovl", "", "The overlay file to process")
		extractCmd.StringVar(&assetDir, "o", "", "Where to extract the asset files")

		extractCmd.Parse(os.Args[2:])
		if stageOvl == "" || assetDir == "" {
			fmt.Println("stage_ovl and asset_dir are required for extract")
			extractCmd.PrintDefaults()
			os.Exit(1)
		}
		if err := extract(stageOvl, assetDir); err != nil {
			panic(err)
		}

	case "build":
		buildCmd := flag.NewFlagSet("build", flag.ExitOnError)
		var file string
		var kind string
		var outputDir string
		buildCmd.StringVar(&file, "file", "", "File to process")
		buildCmd.StringVar(&kind, "kind", "", "Kind of the file to process")
		buildCmd.StringVar(&outputDir, "o", "", "Where to store the processed source files")

		buildCmd.Parse(os.Args[2:])

		if file == "" || kind == "" || outputDir == "" {
			fmt.Println("file, kind, and output_dir are required for build")
			buildCmd.PrintDefaults()
			os.Exit(1)
		}

		var err error
		switch kind {
		case "rooms":
			err = buildRooms(file, outputDir)
		case "layers":
			err = buildLayers(path.Base(file), file, outputDir)
		case "sprites":
			err = buildSprites(file, outputDir)
		default:
			fmt.Println("unknown kind, valid values are 'room', 'layer', 'sprites'")
		}
		if err != nil {
			panic(err)
		}

	case "build_all":
		buildCmd := flag.NewFlagSet("build_all", flag.ExitOnError)
		var inputDir string
		var outputDir string
		buildCmd.StringVar(&inputDir, "i", "", "Folder where all the assets are located")
		buildCmd.StringVar(&outputDir, "o", "", "Where to store the processed source files")

		buildCmd.Parse(os.Args[2:])

		if inputDir == "" || outputDir == "" {
			fmt.Println("input_dir and output_dir are required for build")
			buildCmd.PrintDefaults()
			os.Exit(1)
		}

		if err := buildAll(inputDir, outputDir); err != nil {
			panic(err)
		}

	default:
		fmt.Println("expected 'info', 'extract', 'build' or 'build_all' subcommands")
		os.Exit(1)
	}
}
