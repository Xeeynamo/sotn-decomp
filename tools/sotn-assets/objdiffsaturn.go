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

var saturnOverlays = []saturnOverlay{
	{"zero", "ZERO: Boot / libraries", "config/saturn/zero.bin.yaml"},
	{"game", "GAME: Main engine", "config/saturn/game.prg.yaml"},
	{"stage_02", "STAGE_02: Alchemy Laboratory", "config/saturn/stage_02.prg.yaml"},
	{"warp", "WARP: Warp room", "config/saturn/warp.prg.yaml"},
	{"alucard", "Alucard", "config/saturn/alucard.prg.yaml"},
	{"richter", "Richter", "config/saturn/richter.prg.yaml"},
	{"maria", "Maria", "config/saturn/maria.prg.yaml"},
	{"t_bat", "T_BAT: Bat familiar", "config/saturn/t_bat.prg.yaml"},
}

const saturnKind = "saturn"
const saturnBuildDir = "build/saturn"

// saturnBaseDir is kept short because dosemu resolves it as a DOS path.
const saturnBaseDir = "rpt/saturn"

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
	defer func() { _ = regenSaturnNinjaWithoutProgressReport() }()

	if err := buildSaturnTargetWithAsm(); err != nil {
		return err
	}
	if err := buildSaturnBaseWithoutAsm(); err != nil {
		return err
	}
	if err := genSaturnObjdiffConfig(); err != nil {
		return err
	}
	reportPath := filepath.Join(saturnBuildDir, "report.json")
	if err := deps.ObjdiffCLI("report", "generate", "-o", reportPath); err != nil {
		return err
	}
	if err := removeDataMeasures(reportPath); err != nil {
		return err
	}
	return summarizeSaturnReport(reportPath)
}

// temporarily remove data reporting on Saturn, as it's not accurate
func removeDataMeasures(reportPath string) error {
	raw, err := os.ReadFile(reportPath)
	if err != nil {
		return err
	}
	var report map[string]any
	if err := json.Unmarshal(raw, &report); err != nil {
		return fmt.Errorf("parse %s: %w", reportPath, err)
	}
	stripDataMeasures(report["measures"])
	units, _ := report["units"].([]any)
	for _, u := range units {
		unit, _ := u.(map[string]any)
		if unit == nil {
			continue
		}
		stripDataMeasures(unit["measures"])
	}
	out, err := json.Marshal(report)
	if err != nil {
		return err
	}
	return os.WriteFile(reportPath, out, 0644)
}

func stripDataMeasures(rawMeasures any) {
	measures, _ := rawMeasures.(map[string]any)
	if measures == nil {
		return
	}
	for _, key := range []string{
		"total_data",
		"matched_data",
		"matched_data_percent",
		"complete_data",
		"complete_data_percent",
	} {
		delete(measures, key)
	}
}

func buildSaturnTargetWithAsm() error {
	if err := regenSaturnNinjaWithoutProgressReport(); err != nil {
		return err
	}
	if err := buildSaturnObjects(); err != nil {
		return fmt.Errorf("build saturn target: %w", err)
	}
	return nil
}

func buildSaturnBaseWithoutAsm() error {
	if err := os.Setenv("SOTN_PROGRESS_REPORT", "1"); err != nil {
		return err
	}
	if err := regenSaturnNinja(); err != nil {
		return err
	}
	if err := deps.Ninja(); err != nil {
		return fmt.Errorf("build saturn base: %w", err)
	}
	return nil
}

func regenSaturnNinjaWithoutProgressReport() error {
	if err := os.Unsetenv("SOTN_PROGRESS_REPORT"); err != nil {
		return err
	}
	return regenSaturnNinja()
}

func regenSaturnNinja() error {
	if err := deps.GenSaturnNinja(); err != nil {
		return err
	}
	if err := os.Remove(saturnNinjaStampFile); err != nil && !os.IsNotExist(err) {
		return err
	}
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
