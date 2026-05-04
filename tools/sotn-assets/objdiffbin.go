package main

import (
	"encoding/json"
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

	reportPath := filepath.Join("build", version, "report.json")
	if err := deps.ObjdiffCLI("report", "generate", "-o", reportPath); err != nil {
		return err
	}
	return addNonmatchingData(reportPath)
}

func addNonmatchingData(reportPath string) error {
	// rewrites reportPath content to manually inject data+rodata+bss percentage report
	// every file containing data that comes from asm/ instead of src/, it marked as non-matching
	raw, err := os.ReadFile(reportPath)
	if err != nil {
		return err
	}
	var report map[string]any
	if err := json.Unmarshal(raw, &report); err != nil {
		return fmt.Errorf("parse %s: %v", reportPath, err)
	}
	units, _ := report["units"].([]any)
	for _, u := range units {
		unit, _ := u.(map[string]any)
		if unit == nil {
			continue
		}
		meta, _ := unit["metadata"].(map[string]any)
		if meta == nil {
			continue
		}
		srcPath, _ := meta["source_path"].(string)
		if !strings.HasPrefix(srcPath, "asm/") {
			continue
		}
		measures, _ := unit["measures"].(map[string]any)
		if measures == nil {
			measures = map[string]any{}
			unit["measures"] = measures
		}
		// Force the unit to display as 0% on decomp.dev. matched_data is
		// already 0 (proto3 default-suppressed); we set it explicitly so it
		// survives any re-serialization downstream.
		for _, k := range []string{
			"fuzzy_match_percent",
			"matched_code_percent",
			"matched_data_percent",
			"matched_functions_percent",
			"complete_code_percent",
			"complete_data_percent",
		} {
			measures[k] = 0.0
		}
		measures["matched_code"] = "0"
		measures["matched_data"] = "0"
		measures["matched_functions"] = 0
		measures["complete_code"] = "0"
		measures["complete_data"] = "0"
		measures["complete_units"] = 0
	}
	out, err := json.Marshal(report)
	if err != nil {
		return err
	}
	return os.WriteFile(reportPath, out, 0644)
}
