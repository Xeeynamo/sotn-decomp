package main

import (
	"encoding/json"
	"fmt"
	"os"
	"path/filepath"
	"sort"
	"strings"

	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/deps"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/objdiff"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/splat"
)

type saturnOverlay struct {
	id             string
	name           string
	splitterConfig string
}

// saturnOverlays lists the Saturn programs covered by the progress report, in
// the same order as saturnSplitterYAMLs.
var saturnOverlays = []saturnOverlay{
	{"game", "GAME: Main engine", "config/saturn/game.prg.yaml"},
	{"t_bat", "T_BAT: Title / battle", "config/saturn/t_bat.prg.yaml"},
	{"zero", "ZERO: Boot / libraries", "config/saturn/zero.bin.yaml"},
	{"stage_02", "STAGE_02: Stage", "config/saturn/stage_02.prg.yaml"},
	{"warp", "WARP: Warp room", "config/saturn/warp.prg.yaml"},
	{"alucard", "ALUCARD: Alucard", "config/saturn/alucard.prg.yaml"},
	{"richter", "RICHTER: Richter", "config/saturn/richter.prg.yaml"},
}

const saturnKind = "saturn"
const saturnBuildDir = "build/saturn"
const saturnBaseDir = "expected/report/build/saturn"

func saturnSourceFiles(configPath string) ([]string, error) {
	cfg, err := splat.ReadConfig(configPath)
	if err != nil {
		return nil, fmt.Errorf("read splat config %q: %w", configPath, err)
	}
	seen := map[string]struct{}{}
	var files []string
	cfg.ForEachCodeSubsegment(func(_ splat.Segment, subsegments []any) {
		for _, raw := range subsegments {
			ss, ok := raw.(map[string]any)
			if !ok {
				continue
			}
			file, ok := ss["file"].(string)
			if !ok || file == "" {
				continue
			}
			if _, dup := seen[file]; dup {
				continue
			}
			seen[file] = struct{}{}
			files = append(files, file)
		}
	})
	sort.Strings(files)
	return files, nil
}

func genSaturnObjdiffConfig() error {
	var units []objdiff.Unit
	categories := []objdiff.ProgressCategory{{ID: saturnKind, Name: "Saturn"}}
	for _, ovl := range saturnOverlays {
		categoryID := fmt.Sprintf("%s.%s", saturnKind, ovl.id)
		categories = append(categories, objdiff.ProgressCategory{
			ID:   categoryID,
			Name: ovl.name,
		})
		files, err := saturnSourceFiles(ovl.splitterConfig)
		if err != nil {
			return err
		}
		for _, name := range files {
			obj := name + ".o"
			units = append(units, objdiff.Unit{
				Name:       fmt.Sprintf("%s/%s", categoryID, name),
				BasePath:   filepath.Join(saturnBaseDir, obj),
				TargetPath: filepath.Join(saturnBuildDir, obj),
				Metadata: objdiff.Metadata{
					SourcePath:         filepath.Join("src/saturn", name+".c"),
					ProgressCategories: []string{saturnKind, categoryID},
				},
			})
		}
	}
	cfg := objdiff.Config{
		CustomMake:       "ninja",
		BuildBase:        false,
		BuildTarget:      false,
		Units:            units,
		ProgressCategory: categories,
	}
	data, err := json.MarshalIndent(cfg, "", "  ")
	if err != nil {
		return err
	}
	return os.WriteFile("objdiff.json", data, 0644)
}

func handleSaturnReport() error {
	defer func() {
		_ = os.Unsetenv("SOTN_PROGRESS_REPORT")
		_ = regenSaturnNinja()
	}()

	_ = os.Unsetenv("SOTN_PROGRESS_REPORT")
	if err := regenSaturnNinja(); err != nil {
		return err
	}
	if err := buildSaturnObjects(); err != nil {
		return fmt.Errorf("build saturn target: %w", err)
	}
	if err := os.Setenv("SOTN_PROGRESS_REPORT", "1"); err != nil {
		return err
	}
	if err := regenSaturnNinja(); err != nil {
		return err
	}
	if err := deps.Ninja(); err != nil {
		return fmt.Errorf("build saturn base: %w", err)
	}
	if err := genSaturnObjdiffConfig(); err != nil {
		return err
	}
	reportPath := filepath.Join(saturnBuildDir, "report.json")
	if err := deps.ObjdiffCLI("report", "generate", "-o", reportPath); err != nil {
		return err
	}
	return summarizeSaturnReport(reportPath)
}

func regenSaturnNinja() error {
	if err := deps.GenSaturnNinja(); err != nil {
		return err
	}
	// Invalidate the stamp so the next plain `build saturn` regenerates too.
	_ = os.Remove("build.ninja.version")
	return nil
}

func summarizeSaturnReport(reportPath string) error {
	raw, err := os.ReadFile(reportPath)
	if err != nil {
		return err
	}
	var report struct {
		Measures struct {
			MatchedCodePercent float64 `json:"matched_code_percent"`
			TotalCode          string  `json:"total_code"`
		} `json:"measures"`
		Units []struct {
			Name     string `json:"name"`
			Measures struct {
				MatchedCodePercent float64 `json:"matched_code_percent"`
			} `json:"measures"`
		} `json:"units"`
	}
	if err := json.Unmarshal(raw, &report); err != nil {
		return fmt.Errorf("parse %s: %w", reportPath, err)
	}
	fmt.Printf("Saturn progress report written to %s\n", reportPath)
	fmt.Printf("  overall matched code: %.2f%% (%s bytes total)\n",
		report.Measures.MatchedCodePercent, report.Measures.TotalCode)
	fmt.Printf("  units: %d\n", len(report.Units))
	if strings.TrimSpace(report.Measures.TotalCode) == "" {
		fmt.Println("  warning: no code measured; were the objects built?")
	}
	return nil
}
