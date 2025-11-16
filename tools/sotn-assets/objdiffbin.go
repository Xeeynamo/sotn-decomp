package main

import (
	"fmt"
	"path/filepath"
	"strings"

	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/deps"
)

func handleObjdiffGUI(version string) error {
	configPath := fmt.Sprintf("config/assets.%s.yaml", version)
	if err := objdiffgen(configPath); err != nil {
		return err
	}
	return deps.ExecObjdiffGUI("--project-dir", ".")
}

func handlerObjdiffCLI(version, srcPath, symbol string) error {
	if err := objdiffgen(version); err != nil {
		return err
	}
	if !strings.HasSuffix(srcPath, ".c") {
		srcPath += ".c"
	}
	if !strings.HasPrefix(srcPath, "src/") {
		srcPath = "src/" + srcPath
	}
	basePath := filepath.Join("build", version, srcPath+".o")
	targetPath := filepath.Join("expected", basePath)
	return deps.ExecObjdiffCLI("diff", "-1", basePath, "-2", targetPath, symbol)
}
