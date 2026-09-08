package main

import (
	"os"
	"path/filepath"

	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/layer"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/layout"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/rooms"
)

func packStageAssets(stage, assetDir, sourceDir, roomFile, layerFile, layoutFile string) error {
	args := assets.BuildArgs{AssetDir: assetDir, SrcDir: sourceDir, OvlName: stage}
	args.Name = roomFile
	if err := rooms.Handler.Build(args); err != nil {
		return err
	}
	args.Name = layerFile
	if err := layer.Handler.Build(args); err != nil {
		return err
	}
	args.Name = layoutFile
	if err := layout.BuildWithOverlayHeader(args); err != nil {
		return err
	}
	return os.WriteFile(filepath.Join(sourceDir, "packed.stamp"), nil, 0o644)
}
