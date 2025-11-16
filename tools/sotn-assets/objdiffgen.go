package main

import (
	"encoding/json"
	"fmt"
	"os"
	"path/filepath"
	"strconv"
	"strings"

	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/objdiff"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/splat"
)

func objdiffgen(version string) error {
	configPath := fmt.Sprintf("config/assets.%s.yaml", version)
	c, err := readConfig(configPath)
	if err != nil {
		return err
	}
	if c.Version != "" {
		_ = os.Setenv("VERSION", c.Version)
	}
	buildDir := fmt.Sprintf("build/%s", c.Version)
	targetDir := filepath.Join("expected", buildDir)
	var units []objdiff.Unit
	var categories []objdiff.ProgressCategory
	for _, o := range c.Files {
		splatConfig, err := splat.ReadConfig(o.SplatConfigPath)
		if err != nil {
			return fmt.Errorf("unable to read splat config at %q: %v", o.SplatConfigPath, err)
		}
		categories = append(categories, objdiff.ProgressCategory{
			ID: splatConfig.Options.Basename,
		})
		srcs := map[string]struct{}{}
		splatConfig.ForEachCodeSubsegment(func(_ splat.Segment, subsegments []any) {
			for _, seg := range subsegments {
				segment, ok := seg.([]any)
				if !ok {
					continue
				}
				if len(segment) < 2 {
					continue
				}
				cat, ok := segment[1].(string)
				if !ok {
					continue
				}
				switch cat {
				case "c":
				case ".data":
				case ".rodata":
				case ".bss":
				default:
					continue
				}
				name := ""
				if len(segment) >= 3 {
					if n, ok := segment[2].(string); ok {
						name = n
					} else if n, ok := segment[2].(int); ok {
						name = strconv.FormatInt(int64(n), 10)
					}
				}
				if name == "" {
					if v, ok := segment[0].(uint64); ok {
						name = strconv.FormatInt(int64(v), 16)
						name = strings.ToUpper(name)
					}
				}
				if name == "" {
					panic("bug")
				}
				srcs[name] = struct{}{}
			}
		})
		for name, _ := range srcs {
			srcFile := filepath.Join(o.SourceDir, name+".c")
			objFile := srcFile + ".o"
			units = append(units, objdiff.Unit{
				Name:       fmt.Sprintf("%s/%s", splatConfig.Options.Basename, name),
				BasePath:   filepath.Join(buildDir, objFile),
				TargetPath: filepath.Join(targetDir, objFile),
				Metadata: objdiff.Metadata{
					SourcePath:         srcFile,
					ProgressCategories: []string{splatConfig.Options.Basename},
				},
			})
		}
	}
	data, err := json.Marshal(objdiff.Config{
		CustomMake:  "ninja",
		BaseDir:     buildDir,
		BuildBase:   true,
		TargetDir:   targetDir,
		BuildTarget: false,
		WatchPatterns: []string{
			"include/**.h",
			"src/**.c",
			"src/**.h",
		},
		IgnorePatterns: []string{
			"build/**/*",
		},
		Units:            units,
		ProgressCategory: categories,
	})
	if err != nil {
		return err
	}
	return os.WriteFile("objdiff.json", data, 0644)
}
