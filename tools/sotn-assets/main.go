package main

import (
	"encoding/binary"
	"encoding/json"
	"flag"
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/spritebanks"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/datarange"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"os"
	"path"
)

type dataContainer[T any] struct {
	dataRange datarange.DataRange
	content   T
}

type ovl struct {
	ranges            []datarange.DataRange
	rooms             dataContainer[[]room]
	layers            dataContainer[[]roomLayers]
	sprites           dataContainer[spritebanks.SpriteBanks]
	graphics          dataContainer[gfx]
	layouts           dataContainer[layouts]
	layoutsExtraRange datarange.DataRange
	tileMaps          dataContainer[map[psx.Addr][]byte]
	tileDefs          dataContainer[map[psx.Addr]tileDef]
}

func getOvlAssets(fileName string) (ovl, error) {
	type stageHeader struct {
		FnUpdate              psx.Addr
		FnHitDetection        psx.Addr
		FnUpdateRoomPos       psx.Addr
		FnInitRoomEntities    psx.Addr
		Rooms                 psx.Addr // ✅
		Sprites               psx.Addr // ✅
		Cluts                 psx.Addr // 🫥
		Layouts               psx.Addr // ✅
		Layers                psx.Addr // ✅
		Graphics              psx.Addr // 🫥 WIP
		FnUpdateStageEntities psx.Addr
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
	for tileMapsRange.End() < tileDefsRange.Begin() {
		offset := tileDefsRange.Begin().Sum(-0x10)
		unusedTileDef, unusedTileDefRange, err := readTiledef(file, offset)
		if err != nil {
			return ovl{}, fmt.Errorf("there is a gap between tileMaps and tileDefs: %w", err)
		}
		tileDefs[offset] = unusedTileDef
		tileDefsRange = datarange.MergeDataRanges([]datarange.DataRange{tileDefsRange, unusedTileDefRange})
	}

	sprites, spritesRange, err := spritebanks.ReadSpritesBanks(file, psx.RamStageBegin, header.Sprites)
	if err != nil {
		return ovl{}, fmt.Errorf("unable to gather all sprites: %w", err)
	}

	graphics, graphicsRange, err := readGraphics(file, header.Graphics)
	if err != nil {
		return ovl{}, fmt.Errorf("unable to gather all graphics: %w", err)
	}

	layoutOff := header.Layouts
	if layoutOff == psx.RamNull {
		// some overlays have this field nulled, we have to find the offset ourselves
		// it should be usually be right after header.Graphics
		layoutOff = graphicsRange.End() // ⚠️ assumption
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
		ranges: datarange.ConsolidateDataRanges([]datarange.DataRange{
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
		sprites:           dataContainer[spritebanks.SpriteBanks]{dataRange: spritesRange, content: sprites},
		graphics:          dataContainer[gfx]{dataRange: graphicsRange, content: graphics},
		layouts:           dataContainer[layouts]{dataRange: layoutsRange[1], content: entityLayouts},
		layoutsExtraRange: layoutsRange[0],
		tileMaps:          dataContainer[map[psx.Addr][]byte]{dataRange: tileMapsRange, content: tileMaps},
		tileDefs:          dataContainer[map[psx.Addr]tileDef]{dataRange: tileDefsRange, content: tileDefs},
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
		dataRange datarange.DataRange
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
		s := fmt.Sprintf("  - [0x%X, .data, %s]", e.dataRange.Begin().Real(psx.RamStageBegin), e.name)
		if e.comment != "" {
			s = fmt.Sprintf("%s # %s", s, e.comment)
		}
		fmt.Println(s)

		// if there is a gap between the current entry and the next one, mark it as unrecognized data
		if i == len(entries)-1 || e.dataRange.End() != entries[i+1].dataRange.Begin() {
			fmt.Printf("  - [0x%X, data]\n", e.dataRange.End().Real(psx.RamStageBegin))
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

func handlerStage(args []string) error {
	commands := map[string]func(args []string) error{}
	commands["info"] = func(args []string) error {
		var stageOvl string
		extractCmd := flag.NewFlagSet("info", flag.ExitOnError)
		extractCmd.StringVar(&stageOvl, "stage_ovl", "", "The overlay file to process")
		extractCmd.Parse(args)
		return info(stageOvl)
	}
	commands["extract"] = func(args []string) error {
		var stageOvl string
		var assetDir string
		extractCmd := flag.NewFlagSet("extract", flag.ExitOnError)
		extractCmd.StringVar(&stageOvl, "stage_ovl", "", "The overlay file to process")
		extractCmd.StringVar(&assetDir, "o", "", "Where to extract the asset files")
		extractCmd.Parse(args)

		if stageOvl == "" || assetDir == "" {
			fmt.Fprintln(os.Stderr, "stage_ovl and asset_dir are required for extract")
			extractCmd.PrintDefaults()
			os.Exit(1)
		}
		return extract(stageOvl, assetDir)
	}
	commands["build"] = func(args []string) error {
		var file string
		var kind string
		var outputDir string
		buildCmd := flag.NewFlagSet("build", flag.ExitOnError)
		buildCmd.StringVar(&file, "file", "", "File to process")
		buildCmd.StringVar(&kind, "kind", "", "Kind of the file to process")
		buildCmd.StringVar(&outputDir, "o", "", "Where to store the processed source files")
		buildCmd.Parse(args)

		if file == "" || kind == "" || outputDir == "" {
			fmt.Fprintln(os.Stderr, "file, kind, and output_dir are required for build")
			buildCmd.PrintDefaults()
			os.Exit(1)
		}

		switch kind {
		case "rooms":
			return buildRooms(file, outputDir)
		case "layers":
			return buildLayers(path.Base(file), file, outputDir)
		case "sprites":
			return spritebanks.BuildSprites(file, outputDir)
		}
		return fmt.Errorf("unknown kind, valid values are 'room', 'layer', 'sprites'")
	}
	commands["build_all"] = func(args []string) error {
		buildCmd := flag.NewFlagSet("build_all", flag.ExitOnError)
		var inputDir string
		var outputDir string
		buildCmd.StringVar(&inputDir, "i", "", "Folder where all the assets are located")
		buildCmd.StringVar(&outputDir, "o", "", "Where to store the processed source files")
		buildCmd.Parse(args)

		if inputDir == "" || outputDir == "" {
			fmt.Fprintln(os.Stderr, "input_dir and output_dir are required for build")
			buildCmd.PrintDefaults()
			os.Exit(1)
		}
		return buildAll(inputDir, outputDir)
	}

	if len(args) > 0 {
		command := args[0]
		if f, found := commands[command]; found {
			return f(args[1:])
		}
		fmt.Fprintf(os.Stderr, "unknown subcommand %q. Valid subcommands are %s\n", command, joinMapKeys(commands, ", "))
	} else {
		fmt.Fprintf(os.Stderr, "Need a subcommand. Valid subcommands are %s\n", joinMapKeys(commands, ", "))
	}
	os.Exit(1)
	return nil
}

func handlerConfigExtract(args []string) error {
	c, err := readConfig(args[0])
	if err != nil {
		return err
	}
	return extractFromConfig(c)
}

func handlerConfigBuild(args []string) error {
	c, err := readConfig(args[0])
	if err != nil {
		return err
	}
	return buildFromConfig(c)
}

func handlerConfig(args []string) error {
	commands := map[string]func(args []string) error{
		"extract": handlerConfigExtract,
		"build":   handlerConfigBuild,
	}

	if len(args) > 0 {
		command := args[0]
		if f, found := commands[command]; found {
			if err := f(args[1:]); err != nil {
				fmt.Fprintln(os.Stderr, err)
				os.Exit(1)
			}
			return nil
		}
		fmt.Fprintf(os.Stderr, "unknown subcommand %q. Valid subcommand are %s\n", command, joinMapKeys(commands, ", "))
	} else {
		fmt.Fprintf(os.Stderr, "Need a subcommand. Valid subcommand are %s\n", joinMapKeys(commands, ", "))
	}
	os.Exit(1)
	return nil
}

func main() {
	commands := map[string]func(args []string) error{
		"stage":  handlerStage,
		"config": handlerConfig,
	}

	args := os.Args[1:]
	if len(args) > 0 {
		command := args[0]
		if f, found := commands[command]; found {
			if err := f(args[1:]); err != nil {
				fmt.Fprintln(os.Stderr, err)
				os.Exit(1)
			}
			return
		}
		fmt.Fprintf(os.Stderr, "unknown command %q. Valid commands are %s\n", command, joinMapKeys(commands, ", "))
	} else {
		fmt.Fprintf(os.Stderr, "Need a command. Valid commands are %s\n", joinMapKeys(commands, ", "))
	}
	os.Exit(1)
}
