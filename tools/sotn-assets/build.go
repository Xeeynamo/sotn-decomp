package main

import (
	"errors"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/layer"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/layout"
	"golang.org/x/sync/errgroup"
	"io/fs"
	"os"
	"path"
)

func buildAll(inputDir string, outputDir string) error {
	if err := os.MkdirAll(outputDir, 0755); err != nil {
		return err
	}

	eg := errgroup.Group{}
	eg.Go(func() error {
		if err := layer.BuildLayers(inputDir, path.Join(inputDir, "layers.json"), outputDir); err != nil {
			if !errors.Is(err, fs.ErrNotExist) {
				return err
			}
		}
		return nil
	})
	eg.Go(func() error {
		if err := layout.BuildEntityLayouts(path.Join(inputDir, "entity_layouts.json"), outputDir); err != nil {
			if !errors.Is(err, fs.ErrNotExist) {
				return err
			}
		}
		return nil
	})

	return eg.Wait()
}
