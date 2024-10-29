package main

import (
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/cutscene"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/layer"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/layout"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/rooms"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/skip"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/spritebanks"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/spriteset"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"golang.org/x/sync/errgroup"
	"gopkg.in/yaml.v2"
	"os"
	"strconv"
)

type assetSegmentEntry struct {
	Start  int        `yaml:"start"`
	Vram   psx.Addr   `yaml:"vram"`
	Assets [][]string `yaml:"assets"`
}

type assetFileEntry struct {
	Target    string              `yaml:"target"`
	AssetDir  string              `yaml:"asset_path"`
	SourceDir string              `yaml:"src_path"`
	Segments  []assetSegmentEntry `yaml:"segments"`
}

type assetConfig struct {
	Files []assetFileEntry `yaml:"files"`
}

var handlers = func() map[string]assets.Handler {
	m := make(map[string]assets.Handler)
	for _, handler := range []assets.Handler{
		cutscene.Handler,
		layer.Handler,
		layout.Handler,
		rooms.Handler,
		skip.Handler,
		spritebanks.Handler,
		spriteset.Handler,
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
	name string,
	data []byte,
	start int,
	end int,
	args []string,
	ramBase psx.Addr) {
	eg.Go(func() error {
		defer func() {
			if err := recover(); err != nil {
				fmt.Printf("unable to extract asset %q: %v", name, err)
			}
		}()
		if err := handler.Extract(assets.ExtractArgs{
			Data:     data,
			Start:    start,
			End:      end,
			AssetDir: assetDir,
			RamBase:  ramBase,
			Name:     name,
			Args:     args,
		}); err != nil {
			return fmt.Errorf("unable to extract asset %q: %v", name, err)
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
					enqueueExtractAssetEntry(&eg, handler, file.AssetDir, name, data[segment.Start:], start, end, args, segment.Vram)
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
	name string) {
	eg.Go(func() error {
		err := handler.Build(assets.BuildArgs{
			AssetDir: assetDir,
			SrcDir:   sourceDir,
			Name:     name,
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
				enqueueBuildAssetEntry(&eg, handler, file.AssetDir, file.SourceDir, name)
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
