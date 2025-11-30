package main

import (
	"encoding/json"
	"fmt"
	"os"
	"os/exec"
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
	"stsel":  {"sel", "engine", "SEL: Title Screen / Main Menu"},
	"stno0":  {"no0", "st", "NO0: Marble Gallery"},
	"stno1":  {"no1", "st", "NO1: Outer Wall"},
	"stlib":  {"lib", "st", "LIB: Long Library"},
	"stcat":  {"cat", "st", "CAT: Catacombs"},
	"stno2":  {"no2", "st", "NO2: Olrox's Quarters"},
	"stchi":  {"chi", "st", "CHI: Abandoned Mine"},
	"stdai":  {"dai", "st", "DAI: Royal Chapel"},
	"stnp3":  {"np3", "st", "NP3: Castle Entrance"},
	"stcen":  {"cen", "st", "CEN: Castle Center"},
	"stno4":  {"no4", "st", "NO4: Underground Caverns"},
	"stare":  {"are", "st", "ARE: Colosseum"},
	"sttop":  {"top", "st", "TOP: Castle Keep (Hallway Entrance)"},
	"stnz0":  {"nz0", "st", "NZ0: Alchemy Laboratory"},
	"stnz1":  {"nz1", "st", "NZ1: Clock Tower"},
	"stwrp":  {"wrp", "st", "WRP: Warp Room"},
	"stdre":  {"dre", "st", "DRE: Nightmare"},
	"bobo7":  {"bo7", "bo", "BO7: Cerberos (Boss)"},
	"bomar":  {"mar", "bo", "MAR: Maria cutscene (clock room)"},
	"bobo6":  {"bo6", "bo", "BO6: Richter (Boss)"},
	"bobo5":  {"bo5", "bo", "BO5: Hippogryph (Boss)"},
	"bobo4":  {"bo4", "bo", "BO4: Doppleganger10 (Boss)"},
	"bobo3":  {"bo3", "bo", "BO3: Scylla (Boss)"},
	"bobo2":  {"bo2", "bo", "BO2: Minotaurus / Werewolf (Boss)"},
	"bobo1":  {"bo1", "bo", "BO1: Granfaloon (Boss)"},
	"bobo0":  {"bo0", "bo", "BO0: Olrox (Boss)"},
	"stst0":  {"st0", "st", "ST0: Final Stage: Bloodlines"},
	"strno0": {"rno0", "st", "RNO0: Black Marble Gallery"},
	"strno1": {"rno1", "st", "RNO1: Reverse Outer Wall"},
	"strlib": {"rlib", "st", "RLIB: Forbidden Library"},
	"strcat": {"rcat", "st", "RCAT: Floating Catacombs"},
	"strno2": {"rno2", "st", "RNO2: Death Wing's Lair"},
	"strchi": {"rchi", "st", "RCHI: Cave (Reverse Abandoned Mine)"},
	"strdai": {"rdai", "st", "RDAI: Anti-Chapel"},
	"strno3": {"rno3", "st", "RNO3: Reverse Castle Entrance"},
	"strcen": {"rcen", "st", "RCEN: Reverse Castle Center (Shaft Boss Fight)"},
	"strno4": {"rno4", "st", "RNO4: Reverse Caverns"},
	"strare": {"rare", "st", "RARE: Reverse Colosseum"},
	"strtop": {"rtop", "st", "RTOP: Reverse Castle Keep (Hallway Entrance)"},
	"strnz0": {"rnz0", "st", "RNZ0: Necromancy Laboratory"},
	"strnz1": {"rnz1", "st", "RNZ1: Reverse Clock Tower"},
	"strwrp": {"rwrp", "st", "RWRP: Reverse Warp Room"},
	"borbo8": {"rbo8", "bo", "RBO8: Galamoth (Boss)"},
	"borbo7": {"rbo7", "bo", "RBO7: Akmodan II (Boss)"},
	"borbo6": {"rbo6", "bo", "RBO6: Dracula (Boss)"},
	"borbo5": {"rbo5", "bo", "RBO5: Doppleganger40 (Boss)"},
	"borbo4": {"rbo4", "bo", "RBO4: The Creature (Boss)"},
	"borbo3": {"rbo3", "bo", "RBO3: Medusa (Boss)"},
	"borbo2": {"rbo2", "bo", "RBO2: Death (Boss)"},
	"borbo1": {"rbo1", "bo", "RBO1: Beezelbub (Boss)"},
	"borbo0": {"rbo0", "bo", "RBO0: Fake Trevor / Fake Grant / Fake Sypha (Boss)"},
	"stmad":  {"mad", "st", "MAD: Debug Room"},
	"stno3":  {"no3", "st", "NO3: Castle Entrance (Intro / Death Cutscene)"},
	"stte1":  {"te1", "st", "TE1: Test Room 1"},
	"stte2":  {"te2", "st", "TE2: Test Room 2"},
	"stte3":  {"te3", "st", "TE3: Test Room 3"},
	"stte4":  {"te4", "st", "TE4: Test Room 4"},
	"stte5":  {"te5", "st", "TE5: Test Room 5"},
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
	"bo":      "Boss",
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
		if o.SplatConfigPath == "" {
			if !isProgressReport {
				continue
			}
			if o.Target == "" {
				continue
			}
			ovlID := strings.ToLower(strings.Split(filepath.Base(o.Target), ".")[0])
			var overlayMeta metaOverlay
			for _, val := range metaOverlays {
				if val.id == ovlID {
					overlayMeta = val
					break
				}
			}
			if overlayMeta.id == "" {
				panic(fmt.Sprintf("OVL ID %s not found", ovlID))
			}
			categoryID := fmt.Sprintf("%s.%s", overlayMeta.kind, overlayMeta.id)
			categories = append(categories, objdiff.ProgressCategory{
				ID:   categoryID,
				Name: overlayMeta.name,
			})
			elfName := ovlID + ".elf"
			elfTargetPath := filepath.Join(targetDir, elfName)
			elfBasePath := filepath.Join(buildDir, elfName)
			mipselAsPath, err := exec.LookPath("mipsel-linux-gnu-as")
			if err != nil {
				return err
			}
			if err := (&exec.Cmd{
				Path: mipselAsPath,
				Args: []string{mipselAsPath, "-o", elfTargetPath},
				Stdin: strings.NewReader(
					".section .text\n" +
						".global func_fake, func_fake_end\n" +
						"func_fake:\n" +
						".incbin \"" + o.Target + "\"\n" +
						"func_fake_end:\n"),
				Stdout: os.Stdout,
				Stderr: os.Stderr,
			}).Run(); err != nil {
				return err
			}
			if err := (&exec.Cmd{
				Path: mipselAsPath,
				Args: []string{mipselAsPath, "-o", elfBasePath},
				Stdin: strings.NewReader(
					".section .text\n" +
						".global func_fake, func_fake_end\n" +
						"func_fake:\n" +
						"func_fake_end:\n"),
				Stdout: os.Stdout,
				Stderr: os.Stderr,
			}).Run(); err != nil {
				return err
			}
			units = append(units, objdiff.Unit{
				Name:       categoryID,
				BasePath:   elfBasePath,
				TargetPath: elfTargetPath,
				Metadata: objdiff.Metadata{
					ProgressCategories: []string{overlayMeta.kind, categoryID},
				},
			})
			continue
		}
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
