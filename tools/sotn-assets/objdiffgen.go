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

type metaOverlay struct {
	id   string
	kind string
	name string
}

var metaOverlays = map[string]metaOverlay{
	"main":   {"main", "engine", "PSX SDK"},
	"dra":    {"dra", "engine", "Game engine"},
	"ric":    {"ric", "engine", "Richter (playable)"},
	"weapon": {"weapon", "engine", "Alucard weapons"},
	"stsel":  {"sel", "engine", "Title Screen / Main Menu"},
	"stno0":  {"no0", "st", "Marble Gallery"},
	"stno1":  {"no1", "st", "Outer Wall"},
	"stlib":  {"lib", "st", "Long Library"},
	"stcat":  {"cat", "st", "Catacombs"},
	"stno2":  {"no2", "st", "Olrox's Quarters"},
	"stchi":  {"chi", "st", "Abandoned Mine"},
	"stdai":  {"dai", "st", "Royal Chapel"},
	"stnp3":  {"np3", "st", "Castle Entrance"},
	"stcen":  {"cen", "st", "Castle Center"},
	"stno4":  {"no4", "st", "Underground Caverns"},
	"stare":  {"are", "st", "Colosseum"},
	"sttop":  {"top", "st", "Castle Keep (Hallway Entrance)"},
	"stnz0":  {"nz0", "st", "Alchemy Laboratory"},
	"stnz1":  {"nz1", "st", "Clock Tower"},
	"stwrp":  {"wrp", "st", "Warp Room"},
	"stdre":  {"dre", "st", "Nightmare"},
	"bobo7":  {"bo7", "bo", "Cerberos (Boss)"},
	"bomar":  {"mar", "bo", "Maria cutscene (clock room)"},
	"bobo6":  {"bo6", "bo", "Richter (Boss)"},
	"bobo5":  {"bo5", "bo", "Hippogryph (Boss)"},
	"bobo4":  {"bo4", "bo", "Doppleganger10 (Boss)"},
	"bobo3":  {"bo3", "bo", "Scylla (Boss)"},
	"bobo2":  {"bo2", "bo", "Minotaurus / Werewolf (Boss)"},
	"bobo1":  {"bo1", "bo", "Granfaloon (Boss)"},
	"bobo0":  {"bo0", "bo", "Olrox (Boss)"},
	"stst0":  {"st0", "st", "Final Stage: Bloodlines"},
	"strno0": {"rno0", "str", "Black Marble Gallery"},
	"strno1": {"rno1", "str", "Reverse Outer Wall"},
	"strlib": {"rlib", "str", "Forbidden Library"},
	"strcat": {"rcat", "str", "Floating Catacombs"},
	"strno2": {"rno2", "str", "Death Wing's Lair"},
	"strchi": {"rchi", "str", "Cave (Reverse Abandoned Mine)"},
	"strdai": {"rdai", "str", "Anti-Chapel"},
	"strno3": {"rno3", "str", "Reverse Castle Entrance"},
	"strcen": {"rcen", "str", "Reverse Castle Center (Shaft Boss Fight)"},
	"strno4": {"rno4", "str", "Reverse Caverns"},
	"strare": {"rare", "str", "Reverse Colosseum"},
	"strtop": {"rtop", "str", "Reverse Castle Keep (Hallway Entrance)"},
	"strnz0": {"rnz0", "str", "Necromancy Laboratory"},
	"strnz1": {"rnz1", "str", "Reverse Clock Tower"},
	"strwrp": {"rwrp", "str", "Reverse Warp Room"},
	"borbo8": {"rbo8", "bor", "Galamoth (Boss)"},
	"borbo7": {"rbo7", "bor", "Akmodan II (Boss)"},
	"borbo6": {"rbo6", "bor", "Dracula (Boss)"},
	"borbo5": {"rbo5", "bor", "Doppleganger40 (Boss)"},
	"borbo4": {"rbo4", "bor", "The Creature (Boss)"},
	"borbo3": {"rbo3", "bor", "Medusa (Boss)"},
	"borbo2": {"rbo2", "bor", "Death (Boss)"},
	"borbo1": {"rbo1", "bor", "Beezelbub (Boss)"},
	"borbo0": {"rbo0", "bor", "Fake Trevor / Fake Grant / Fake Sypha (Boss)"},
	"stmad":  {"mad", "std", "Debug Room"},
	"stno3":  {"no3", "st", "Castle Entrance (Intro / Death Cutscene)"},
	"stte1":  {"te1", "std", "Test Room 1"},
	"stte2":  {"te2", "std", "Test Room 2"},
	"stte3":  {"te3", "std", "Test Room 3"},
	"stte4":  {"te4", "std", "Test Room 4"},
	"stte5":  {"te5", "std", "Test Room 5"},
	"tt_000": {"tt_000", "servant", "Bat familiar"},
	"tt_001": {"tt_001", "servant", "Ghost familiar"},
	"tt_002": {"tt_002", "servant", "Faerie familiar"},
	"tt_003": {"tt_003", "servant", "Demon familiar"},
	"tt_004": {"tt_004", "servant", "Sword familiar"},
	"tt_005": {"tt_005", "servant", "Half fairy familiar"},
	"tt_006": {"tt_006", "servant", "Nose demon familiar"},
}
var metaCategories = map[string]string{
	"engine":  "Game engine/misc",
	"st":      "Stage",
	"str":     "Stage (reverse)",
	"bo":      "Boss",
	"bor":     "Boss (reverse)",
	"std":     "Stage (debug/unused)",
	"servant": "Familiar",
}

func objdiffgen(c *assetConfig, isProgressReport bool) error {
	if c.Version != "" {
		_ = os.Setenv("VERSION", c.Version)
	}
	buildDir := fmt.Sprintf("build/%s", c.Version)
	targetDir := filepath.Join("expected", buildDir)
	if isProgressReport {
		buildDir = filepath.Join("expected", "report", buildDir)
	}
	var units []objdiff.Unit
	var categories []objdiff.ProgressCategory
	for id, name := range metaCategories {
		categories = append(categories, objdiff.ProgressCategory{
			ID:   id,
			Name: name,
		})
	}
	for _, o := range c.Files {
		splatConfig, err := splat.ReadConfig(o.SplatConfigPath)
		if err != nil {
			return fmt.Errorf("unable to read splat config at %q: %v", o.SplatConfigPath, err)
		}
		overlayMeta, ok := metaOverlays[splatConfig.Options.Basename]
		if !ok {
			panic(fmt.Sprintf("no overlay ID found for %q", splatConfig.Options.Basename))
		}
		categoryID := fmt.Sprintf("%s.%s", overlayMeta.kind, overlayMeta.id)
		categories = append(categories, objdiff.ProgressCategory{
			ID:   categoryID,
			Name: overlayMeta.name,
		})
		srcs := map[string]string{}
		splatConfig.ForEachCodeSubsegment(func(_ splat.Segment, subsegments []any) {
			for _, seg := range subsegments {
				segment, ok := seg.([]any)
				if !ok {
					continue
				}
				if len(segment) < 2 {
					continue
				}
				name := ""
				if len(segment) >= 3 {
					if n, ok := segment[2].(string); ok {
						name = n
					} else if n, ok := segment[2].(int); ok {
						name = strconv.FormatInt(int64(n), 10)
					} else if n, ok := segment[2].(uint64); ok {
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
				cat, ok := segment[1].(string)
				if !ok {
					continue
				}
				switch cat {
				case "c":
				case ".data":
				case ".rodata":
				case ".bss":
				case "data":
				case "rodata":
				case "bss":
				default:
					continue
				}
				srcs[name] = cat
			}
		})
		asmDataSections := map[string]struct{}{"data": {}, "rodata": {}, "bss": {}}
		for name, cat := range srcs {
			srcFile := filepath.Join(splatConfig.Options.SrcPath, name+".c")
			if _, isAsm := asmDataSections[cat]; isAsm {
				srcFile = filepath.Join(splatConfig.Options.AsmPath, "data", fmt.Sprintf("%s.%s.s", name, cat))
			}
			objFile := srcFile + ".o"
			units = append(units, objdiff.Unit{
				Name:       fmt.Sprintf("%s/%s", categoryID, name),
				BasePath:   filepath.Join(buildDir, objFile),
				TargetPath: filepath.Join(targetDir, objFile),
				Metadata: objdiff.Metadata{
					SourcePath:         srcFile,
					ProgressCategories: []string{overlayMeta.kind, categoryID},
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
