package main

import (
	"encoding/json"
	"os"
	"testing"

	"github.com/stretchr/testify/assert"
	"github.com/stretchr/testify/require"
)

func TestSaturnSourceFiles(t *testing.T) {
	changeDirToRepoRoot()

	files, err := saturnSourceFiles("config/saturn/game.prg.yaml")
	require.NoError(t, err)
	// game.prg references game_0 and game; each must appear exactly once even
	// though it spans multiple subsegments.
	assert.Equal(t, []string{"game", "game_0"}, files)

	// zero.bin pulls in the shared libraries, including nested paths.
	zeroFiles, err := saturnSourceFiles("config/saturn/zero.bin.yaml")
	require.NoError(t, err)
	assert.Contains(t, zeroFiles, "zero")
	assert.Contains(t, zeroFiles, "lib/dma/dma_cpu0")
	assert.Contains(t, zeroFiles, "lib/spr/spr_slv")
}

func TestGenSaturnObjdiffConfig(t *testing.T) {
	changeDirToRepoRoot()

	// Preserve any existing objdiff.json so we do not clobber the PSX one.
	const cfgPath = "objdiff.json"
	orig, hadOrig := os.ReadFile(cfgPath)
	t.Cleanup(func() {
		if hadOrig == nil {
			_ = os.WriteFile(cfgPath, orig, 0644)
		} else {
			_ = os.Remove(cfgPath)
		}
	})

	require.NoError(t, genSaturnObjdiffConfig())

	raw, err := os.ReadFile(cfgPath)
	require.NoError(t, err)
	var cfg struct {
		Units []struct {
			Name       string `json:"name"`
			BasePath   string `json:"base_path"`
			TargetPath string `json:"target_path"`
			Metadata   struct {
				SourcePath         string   `json:"source_path"`
				ProgressCategories []string `json:"progress_categories"`
			} `json:"metadata"`
		} `json:"units"`
		ProgressCategory []struct {
			ID string `json:"id"`
		} `json:"progress_categories"`
	}
	require.NoError(t, json.Unmarshal(raw, &cfg))

	require.NotEmpty(t, cfg.Units)
	byName := map[string]int{}
	for _, u := range cfg.Units {
		byName[u.Name]++
		// Base = SKIP_ASM build, Target = regular build.
		assert.Contains(t, u.BasePath, "build/satbase/")
		assert.Contains(t, u.TargetPath, "build/saturn/")
		assert.NotContains(t, u.TargetPath, "satbase")
		assert.Contains(t, u.Metadata.SourcePath, "src/saturn/")
		require.Len(t, u.Metadata.ProgressCategories, 2)
		assert.Equal(t, "saturn", u.Metadata.ProgressCategories[0])
	}
	// Unit names must be unique.
	for name, n := range byName {
		assert.Equalf(t, 1, n, "duplicate unit %q", name)
	}
	// A category for the root and one per overlay.
	assert.GreaterOrEqual(t, len(cfg.ProgressCategory), len(saturnOverlays)+1)
}
