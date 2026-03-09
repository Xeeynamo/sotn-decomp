package main

import (
	"fmt"
	"os"
	"path/filepath"
	"slices"
	"strings"

	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/deps"
)

var allVersions = []string{"us", "hd", "pspeu"}

func buildVersions(versions []string) error {
	if err := deps.EnsureBuildDeps(versions); err != nil {
		return fmt.Errorf("ensuring build deps: %w", err)
	}
	versionStr := strings.Join(versions, ",")
	if err := genNinjaIfNeeded(versionStr, versions); err != nil {
		return err
	}
	return deps.Ninja()
}

func ninjaStampValue(versionStr string) string {
	stamp := versionStr
	// These env vars change gen.py output, so include them in the stamp
	for _, key := range []string{"SKIP_CHECK", "SOTN_PROGRESS_REPORT", "FORCE_SYMBOLS"} {
		if _, ok := os.LookupEnv(key); ok {
			stamp += "," + key
		}
	}
	return stamp
}

func genNinjaIfNeeded(versionStr string, versions []string) error {
	ninjaFile := "build.ninja"
	stampFile := "build.ninja.version"
	needsRegen := false
	stamp := ninjaStampValue(versionStr)

	// Check if the version set or env flags changed since last gen
	if stampData, err := os.ReadFile(stampFile); err != nil || string(stampData) != stamp {
		needsRegen = true
	}

	if !needsRegen {
		ninjaInfo, err := os.Stat(ninjaFile)
		if err != nil {
			needsRegen = true
		} else {
			ninjaModTime := ninjaInfo.ModTime()
			genPy := "tools/builds/gen.py"
			if info, err := os.Stat(genPy); err == nil && info.ModTime().After(ninjaModTime) {
				needsRegen = true
			}
			if !needsRegen {
				for _, version := range versions {
					pattern := fmt.Sprintf("config/splat.%s.*.yaml", version)
					matches, _ := filepath.Glob(pattern)
					for _, m := range matches {
						if info, err := os.Stat(m); err == nil && info.ModTime().After(ninjaModTime) {
							needsRegen = true
							break
						}
					}
					if needsRegen {
						break
					}
				}
			}
		}
	}

	if needsRegen {
		os.Setenv("VERSION", versionStr)
		if err := deps.GenNinja(); err != nil {
			return err
		}
		return os.WriteFile(stampFile, []byte(stamp), 0o644)
	}
	return nil
}

func parseBuildArgs(args []string) ([]string, error) {
	if len(args) == 0 {
		return allVersions, nil
	}
	var versions []string
	for _, arg := range args {
		if arg == "all" {
			return allVersions, nil
		}
		if !slices.Contains(allVersions, arg) {
			return nil, fmt.Errorf("unknown version %q; valid values: %v", arg, allVersions)
		}
		versions = append(versions, arg)
	}
	return versions, nil
}
