package main

import (
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/animset"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"golang.org/x/sync/errgroup"
	"gopkg.in/yaml.v2"
	"os"
	"path"
	"strconv"
)

type assetSegmentEntry struct {
	Start  int        `yaml:"start"`
	Vram   psx.Addr   `yaml:"vram"`
	Assets [][]string `yaml:"assets"`
}

type assetFileEntry struct {
	Target   string              `yaml:"target"`
	AssetDir string              `yaml:"asset_path"`
	Segments []assetSegmentEntry `yaml:"segments"`
}

type assetConfig struct {
	Files []assetFileEntry `yaml:"files"`
}

type assetEntry struct {
	data    []byte
	start   int
	end     int
	outDir  string
	name    string
	args    []string
	ramBase psx.Addr
}

var handlers = map[string]func(assetEntry) error{
	"animset": func(e assetEntry) error {
		outPath := path.Join(e.outDir, fmt.Sprintf("%s.animset_test.json", e.name))
		return animset.Extract(outPath, e.ramBase, e.data, e.start, e.end)
	},
}

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
		return nil, fmt.Errorf("Error reading YAML file: %v", err)
	}
	var data assetConfig
	if err = yaml.Unmarshal(yamlFile, &data); err != nil {
		return nil, fmt.Errorf("Error unmarshalling YAML file: %v", err)
	}
	return &data, nil
}

func enqueueExtractAssetEntry(
	eg errgroup.Group,
	handler func(assetEntry) error,
	assetDir string,
	name string,
	data []byte,
	start int,
	end int,
	args []string,
	ramBase psx.Addr) {
	eg.Go(func() error {
		if err := handler(assetEntry{
			data:    data,
			start:   start,
			end:     end,
			outDir:  assetDir,
			ramBase: ramBase,
			name:    name,
			args:    args,
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
			if kind == "skip" {
				continue
			}
			if handler, found := handlers[kind]; found {
				name := strconv.FormatUint(uint64(off), 16)
				if len(args) > 0 {
					name = args[0]
					args = args[1:]
				}
				start := int(off) - segment.Start
				end := start + size
				enqueueExtractAssetEntry(eg, handler, file.AssetDir, name, data[segment.Start:], start, end, args, segment.Vram)
			}
			off = off2
			kind = kind2
			args = args2
		}
	}
	return eg.Wait()
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
