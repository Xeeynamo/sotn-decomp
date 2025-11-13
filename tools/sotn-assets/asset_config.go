package main

import (
	"fmt"
	"os"
	"path/filepath"
	"strconv"

	"github.com/goccy/go-yaml"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/binary"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/blueprintsdef"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/cmpgfx"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/cutscene"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/gfxbanks"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/headergfx"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/layer"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/layout"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/paldef"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/palette"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/rawgfx"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/rooms"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/sfxconfig"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/skip"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/spritebanks"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/spriteset"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/spritesheet"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/subweaponsdef"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/tiledef"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/xamusicconfig"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/splat"
	"golang.org/x/sync/errgroup"
)

type assetSegmentEntry struct {
	Start  int        `yaml:"start"`
	Vram   psx.Addr   `yaml:"vram"`
	Assets [][]string `yaml:"assets"`
}

type assetFileEntry struct {
	Target          string              `yaml:"target"`
	AssetDir        string              `yaml:"asset_path"`
	SourceDir       string              `yaml:"src_path"`
	SplatConfigPath string              `yaml:"splat_config_path"`
	Segments        []assetSegmentEntry `yaml:"segments"`
}

type assetConfig struct {
	Version string           `yaml:"version"`
	Files   []assetFileEntry `yaml:"files"`
}

var handlers = func() map[string]assets.Handler {
	m := make(map[string]assets.Handler)
	for _, handler := range []assets.Handler{
		binary.Handler,
		blueprintsdef.Handler,
		cmpgfx.Handler,
		cutscene.Handler,
		gfxbanks.Handler,
		headergfx.Handler,
		layer.Handler,
		layout.Handler,
		paldef.Handler,
		palette.Handler,
		rawgfx.Handler,
		rooms.Handler,
		sfxconfig.Handler,
		skip.Handler,
		spritebanks.Handler,
		spriteset.Handler,
		spritesheet.Handler,
		tiledef.Handler,
		subweaponsdef.Handler,
		xamusicconfig.Handler,
	} {
		m[handler.Name()] = handler
	}
	return m
}()

func parseArgs(entry []string) (offset int64, kind string, args []string, err error) {
	if len(entry) < 2 {
		err = fmt.Errorf("asset %v is malformed", entry)
		return
	}
	offsetRaw := entry[0]
	if len(offsetRaw) >= 2 && offsetRaw[0] == '0' && offsetRaw[1] == 'x' {
		offset, err = strconv.ParseInt(offsetRaw[2:], 16, 32)
	} else {
		offset, err = strconv.ParseInt(offsetRaw, 10, 32)
	}
	if err != nil {
		err = fmt.Errorf("offset %q in asset %v is malformed", offset, entry)
		return
	}
	kind = entry[1]
	args = entry[2:]
	return
}

func readConfig(path string) (*assetConfig, error) {
	yamlFile, err := os.ReadFile(path)
	if err != nil {
		return nil, fmt.Errorf("error reading YAML file: %v", err)
	}
	var data assetConfig
	if err = yaml.Unmarshal(yamlFile, &data); err != nil {
		return nil, fmt.Errorf("error unmarshalling YAML file: %v", err)
	}
	return &data, nil
}

func enqueueExtractAssetEntry(
	eg *errgroup.Group,
	handler assets.Extractor,
	assetDir string,
	srcDir string,
	name string,
	data []byte,
	start int,
	end int,
	args []string,
	ramBase psx.Addr,
	symbol func(psx.Addr) string,
	splatConfig *splat.Config) {
	eg.Go(func() error {
		defer func() {
			if err := recover(); err != nil {
				fmt.Fprintf(os.Stderr, "\033[31munable to extract asset %q in %q: %v\033[0m\n", name, assetDir, err)
			}
		}()
		if err := handler.Extract(assets.ExtractArgs{
			Data:        data,
			Start:       start,
			End:         end,
			AssetDir:    assetDir,
			SrcDir:      srcDir,
			RamBase:     ramBase,
			Boundaries:  ramBase.Boundaries(),
			Name:        name,
			Args:        args,
			OvlName:     filepath.Base(assetDir),
			SplatConfig: splatConfig,
			Symbol:      symbol,
		}); err != nil {
			return fmt.Errorf("unable to extract asset %q in %q: %v", name, assetDir, err)
		}
		return nil
	})
}

func extractAssetFile(file assetFileEntry) error {
	var eg errgroup.Group
	data, err := os.ReadFile(file.Target)
	if err != nil {
		return err
	}
	splatConfig, err := splat.ReadConfig(file.SplatConfigPath)
	if err != nil {
		return fmt.Errorf("unable to read splat config at %q: %v", file.SplatConfigPath, err)
	}
	symbols := make(map[psx.Addr]string)
	addSplatSymbols(symbols, splatConfig)
	addAssetSymbols(symbols, &file)
	for _, segment := range file.Segments {
		if len(segment.Assets) == 0 {
			continue
		}
		off, kind, args, err := parseArgs(segment.Assets[0])
		if err != nil {
			return err
		}
		for i := 1; i < len(segment.Assets); i++ {
			off2, kind2, args2, err2 := parseArgs(segment.Assets[i])
			if err2 != nil {
				return err2
			}
			size := int(off2 - off)
			if size < 0 {
				return fmt.Errorf("offset 0x%X should be smaller than 0x%X, asset %v", off, off2, segment.Assets[i-1])
			}
			if kind != "skip" {
				if handler, found := handlers[kind]; found {
					name := strconv.FormatUint(uint64(off), 16)
					if len(args) > 0 {
						name = args[0]
						args = args[1:]
					}
					start := int(off) - segment.Start
					end := start + size
					enqueueExtractAssetEntry(&eg, handler, file.AssetDir, file.SourceDir, name, data[segment.Start:], start, end, args, segment.Vram, func(addr psx.Addr) string {
						if sym, ok := symbols[addr]; ok {
							return sym
						}
						return ""
					}, splatConfig)
				} else {
					return fmt.Errorf("handler %q not found", kind)
				}
			}
			off = off2
			kind = kind2
			args = args2
		}
	}
	return eg.Wait()
}

func enqueueBuildAssetEntry(
	eg *errgroup.Group,
	handler assets.Builder,
	assetDir,
	sourceDir,
	name string,
	args []string,
) {
	eg.Go(func() error {
		err := handler.Build(assets.BuildArgs{
			AssetDir: assetDir,
			SrcDir:   sourceDir,
			Name:     name,
			Args:     args,
			OvlName:  filepath.Base(assetDir),
		})
		if err != nil {
			return fmt.Errorf("unable to build asset %q at %q: %v", name, assetDir, err)
		}
		return nil
	})
}

func extractFromConfig(c *assetConfig) error {
	var eg errgroup.Group
	for _, file := range c.Files {
		if len(file.Segments) == 0 {
			continue
		}
		eg.Go(func() error {
			return extractAssetFile(file)
		})
	}
	return eg.Wait()
}

func buildAssetFile(file assetFileEntry) error {
	var eg errgroup.Group
	for _, segment := range file.Segments {
		if len(segment.Assets) == 0 {
			continue
		}
		for _, asset := range segment.Assets {
			off, kind, args, err := parseArgs(asset)
			if err != nil {
				return err
			}
			if kind == "skip" {
				continue
			}
			if handler, found := handlers[kind]; found {
				name := strconv.FormatUint(uint64(off), 16)
				if len(args) > 0 {
					name = args[0]
					args = args[1:]
				}
				enqueueBuildAssetEntry(&eg, handler, file.AssetDir, file.SourceDir, name, args)
			}
		}
	}
	return eg.Wait()
}

func buildFromConfig(c *assetConfig) error {
	var eg errgroup.Group
	for _, file := range c.Files {
		if len(file.Segments) == 0 {
			continue
		}
		eg.Go(func() error {
			return buildAssetFile(file)
		})
	}
	return eg.Wait()
}

func addAssetSymbols(m map[psx.Addr]string, a *assetFileEntry) {
	for _, segment := range a.Segments {
		for _, asset := range segment.Assets {
			offset, kind, args, err := parseArgs(asset)
			if err != nil {
				continue
			}
			if kind == "skip" {
				continue
			}
			sym := ""
			if len(args) > 0 {
				sym = args[0]
			}
			m[segment.Vram.Sum(int(offset)-segment.Start)] = sym
		}
	}
}

func addSplatSymbols(m map[psx.Addr]string, c *splat.Config) {
	c.ForEachCodeSubsegment(func(segment splat.Segment, subsegments []any) {
		for _, seg := range subsegments {
			subsegment, ok := seg.([]any)
			if !ok {
				continue
			}
			off := subsegment[0].(uint64)
			addr := psx.Addr(segment.VRAM).Sum(int(off))
			if len(subsegment) > 2 {
				switch subsegment[1] {
				case "c":
				case "data":
				case ".data":
				case "rodata":
				case ".rodata":
				case "bss":
				case ".bss":
				case "sbss":
				default:
					m[addr] = subsegment[2].(string)
				}
			}
		}
	})
}
