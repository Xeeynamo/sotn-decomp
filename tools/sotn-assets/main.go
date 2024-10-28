package main

import (
	"encoding/json"
	"flag"
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/layer"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/datarange"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/sotn"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/util"
	"os"
	"path"
)

type dataContainer[T any] struct {
	dataRange datarange.DataRange
	content   T
}

type ovl struct {
	ranges   []datarange.DataRange
	layers   dataContainer[[]layer.RoomLayers]
	tileMaps dataContainer[map[psx.Addr][]byte]
	tileDefs dataContainer[map[psx.Addr]layer.TileDef]
}

func getOvlAssets(fileName string) (ovl, error) {
	file, err := os.Open(fileName)
	if err != nil {
		return ovl{}, err
	}
	defer file.Close()

	header, err := sotn.ReadStageHeader(file)
	if err != nil {
		return ovl{}, err
	}

	layers, layersRange, err := layer.ReadLayers(file, header.Layers)
	if err != nil {
		return ovl{}, fmt.Errorf("unable to read layers: %w", err)
	}

	tileMaps, tileMapsRange, err := layer.ReadAllTileMaps(file, layers)
	if err != nil {
		return ovl{}, fmt.Errorf("unable to gather all the tile maps: %w", err)
	}

	tileDefs, tileDefsRange, err := layer.ReadAllTiledefs(file, layers)
	if err != nil {
		return ovl{}, fmt.Errorf("unable to gather all the tile defs: %w", err)
	}

	// check for unused tile defs (CEN has one)
	for tileMapsRange.End() < tileDefsRange.Begin() {
		offset := tileDefsRange.Begin().Sum(-0x10)
		unusedTileDef, unusedTileDefRange, err := layer.ReadTiledef(file, offset)
		if err != nil {
			return ovl{}, fmt.Errorf("there is a gap between tileMaps and tileDefs: %w", err)
		}
		tileDefs[offset] = unusedTileDef
		tileDefsRange = datarange.MergeDataRanges([]datarange.DataRange{tileDefsRange, unusedTileDefRange})
	}

	return ovl{
		ranges: datarange.ConsolidateDataRanges([]datarange.DataRange{
			layersRange,
			tileMapsRange,
			tileDefsRange,
		}),
		layers:   dataContainer[[]layer.RoomLayers]{dataRange: layersRange, content: layers},
		tileMaps: dataContainer[map[psx.Addr][]byte]{dataRange: tileMapsRange, content: tileMaps},
		tileDefs: dataContainer[map[psx.Addr]layer.TileDef]{dataRange: tileDefsRange, content: tileDefs},
	}, nil
}

func extractOvlAssets(o ovl, outputDir string) error {
	if err := os.MkdirAll(outputDir, 0755); err != nil {
		return err
	}

	content, err := json.MarshalIndent(o.layers.content, "", "  ")
	if err != nil {
		return err
	}
	if err := os.WriteFile(path.Join(outputDir, "layers.json"), content, 0644); err != nil {
		return fmt.Errorf("unable to create layers file: %w", err)
	}

	for offset, bytes := range o.tileMaps.content {
		fileName := path.Join(outputDir, layer.GetTilemapFileName(offset))
		if err := os.WriteFile(fileName, bytes, 0644); err != nil {
			return fmt.Errorf("unable to create %q: %w", fileName, err)
		}
	}

	for offset, tileDefsData := range o.tileDefs.content {
		defs := layer.TileDefPaths{
			Tiles:      layer.GetTiledefIndicesFileName(offset),
			Pages:      layer.GetTiledefPagesFileName(offset),
			Cluts:      layer.GetTiledefClutsFileName(offset),
			Collisions: layer.GetTiledefCollisionsFileName(offset),
		}
		if err := os.WriteFile(path.Join(outputDir, defs.Tiles), tileDefsData.Tiles, 0644); err != nil {
			return fmt.Errorf("unable to create %q: %w", defs.Tiles, err)
		}
		if err := os.WriteFile(path.Join(outputDir, defs.Pages), tileDefsData.Pages, 0644); err != nil {
			return fmt.Errorf("unable to create %q: %w", defs.Pages, err)
		}
		if err := os.WriteFile(path.Join(outputDir, defs.Cluts), tileDefsData.Cluts, 0644); err != nil {
			return fmt.Errorf("unable to create %q: %w", defs.Cluts, err)
		}
		if err := os.WriteFile(path.Join(outputDir, defs.Collisions), tileDefsData.Cols, 0644); err != nil {
			return fmt.Errorf("unable to create %q: %w", defs.Collisions, err)
		}

		content, err = json.MarshalIndent(defs, "", "  ")
		if err != nil {
			return err
		}
		fileName := path.Join(outputDir, layer.GetTiledefFileName(offset))
		if err := os.WriteFile(fileName, content, 0644); err != nil {
			return fmt.Errorf("unable to create %q: %w", fileName, err)
		}
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
		fmt.Fprintf(os.Stderr, "unknown subcommand %q. Valid subcommands are %s\n", command, util.JoinMapKeys(commands, ", "))
	} else {
		fmt.Fprintf(os.Stderr, "Need a subcommand. Valid subcommands are %s\n", util.JoinMapKeys(commands, ", "))
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
		fmt.Fprintf(os.Stderr, "unknown subcommand %q. Valid subcommand are %s\n", command, util.JoinMapKeys(commands, ", "))
	} else {
		fmt.Fprintf(os.Stderr, "Need a subcommand. Valid subcommand are %s\n", util.JoinMapKeys(commands, ", "))
	}
	os.Exit(1)
	return nil
}

func main() {
	commands := map[string]func(args []string) error{
		"stage":  handlerStage,
		"config": handlerConfig,
		"info":   handlerInfo,
	}

	args := os.Args[1:]
	if len(args) > 0 {
		command := args[0]
		if f, found := commands[command]; found {
			if err := f(args[1:]); err != nil {
				_, _ = fmt.Fprintln(os.Stderr, err)
				os.Exit(1)
			}
			return
		}
		fmt.Fprintf(os.Stderr, "unknown command %q. Valid commands are %s\n", command, util.JoinMapKeys(commands, ", "))
	} else {
		fmt.Fprintf(os.Stderr, "Need a command. Valid commands are %s\n", util.JoinMapKeys(commands, ", "))
	}
	os.Exit(1)
}
