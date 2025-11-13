package main

import (
	"fmt"
	"os"
	"path/filepath"
	"strings"

	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/deps"
)

func handleObjdiffGUI(_ []string) error {
	if os.Getenv("VERSION") == "" {
		return fmt.Errorf("VERSION not set")
	}
	configPath := fmt.Sprintf("config/assets.%s.yaml", os.Getenv("VERSION"))
	if err := objdiffgen(configPath); err != nil {
		return err
	}
	return deps.ExecObjdiffGUI("--project-dir", ".")
}

func handlerObjdiffCLI(args []string) error {
	if os.Getenv("VERSION") == "" {
		return fmt.Errorf("VERSION not set")
	}
	configPath := fmt.Sprintf("config/assets.%s.yaml", os.Getenv("VERSION"))
	if err := objdiffgen(configPath); err != nil {
		return err
	}
	if len(args) < 2 {
		return fmt.Errorf("usage: sotn-assets objdiff <src_path> <symbol>\n\t(e.g. objdiff dra/4A538 func_800EAD0C)")
	}
	srcPath := args[0]
	symbol := args[1]
	if !strings.HasSuffix(srcPath, ".c") {
		srcPath += ".c"
	}
	if !strings.HasPrefix(srcPath, "src/") {
		srcPath = "src/" + srcPath
	}
	basePath := filepath.Join("build", "us", srcPath+".o")
	targetPath := filepath.Join("expected", basePath)
	return deps.ExecObjdiffCLI("diff", "-1", basePath, "-2", targetPath, symbol)
}
