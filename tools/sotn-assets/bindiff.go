package main

import (
	"fmt"
	"path/filepath"

	"github.com/xeeynamo/gobindiff/bindiff"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/splat"
)

func handleBindiff(version, overlay string, bytesPerRow int) error {
	splatConfigPath := fmt.Sprintf("config/splat.%s.%s.yaml", version, overlay)
	splatConfig, err := splat.ReadConfig(splatConfigPath)
	if err != nil {
		return err
	}
	targetPath := splatConfig.Options.TargetPath
	fileName := filepath.Base(targetPath)
	switch overlay {
	case "main":
		fileName = "main.exe"
	}
	basePath := filepath.Join("build", version, fileName)
	return bindiff.Diff(bindiff.MyBinDiff{
		ByteGroup:   2,
		BytesPerRow: bytesPerRow,
	}, []string{basePath, targetPath})
}
