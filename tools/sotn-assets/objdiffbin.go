package main

import (
	"fmt"
	"os"
	"path/filepath"
	"strings"

	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/deps"
)

func handleObjdiffGUI(version string) error {
	c, err := readConfigVersion(version)
	if err != nil {
		return err
	}
	if err := objdiffgen(c, false); err != nil {
		return err
	}
	return deps.ObjdiffGUI("--project-dir", ".")
}

func handlerObjdiffCLI(version, srcPath, symbol string) error {
	c, err := readConfigVersion(version)
	if err != nil {
		return err
	}
	if err := objdiffgen(c, false); err != nil {
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
	return deps.ObjdiffCLI("diff", "-1", basePath, "-2", targetPath, symbol)
}

func handleObjdiffReport(version string) error {
	c, err := readConfigVersion(version)
	if err != nil {
		return err
	}
	if err := os.Setenv("VERSION", version); err != nil {
		return err
	}

	// generate a valid fully-complete expected/build/{VERSION}
	if err := objdiffgen(c, false); err != nil {
		return err
	}
	if err := os.Setenv("SOTN_PROGRESS_REPORT", "0"); err != nil {
		return err
	}
	if err := deps.GenAndRunNinja(); err != nil {
		return err
	}
	buildPath := filepath.Join("build", version)
	expectedPath := filepath.Join("expected", "build", version)
	_ = os.RemoveAll(expectedPath)
	if err := os.CopyFS(expectedPath, os.DirFS(buildPath)); err != nil {
		return err
	}

	// now re-build but with SKIP_ASM=1 with SOTN_PROGRESS_REPORT=1
	if err := objdiffgen(c, true); err != nil {
		return err
	}
	if err := os.Setenv("SOTN_PROGRESS_REPORT", "1"); err != nil {
		return err
	}
	if err := deps.GenAndRunNinja(); err != nil {
		return err
	}

	reportPath := filepath.Join("build", fmt.Sprintf("report.%s.json", version))
	return deps.ObjdiffCLI("report", "generate", "-o", reportPath)
}
