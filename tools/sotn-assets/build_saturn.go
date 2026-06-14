package main

import (
	"fmt"
	"os"
	"path/filepath"

	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/deps"
)

var saturnSplitterYAMLs = []string{
	"config/saturn/game.prg.yaml",
	"config/saturn/t_bat.prg.yaml",
	"config/saturn/zero.bin.yaml",
	"config/saturn/stage_02.prg.yaml",
	"config/saturn/warp.prg.yaml",
	"config/saturn/alucard.prg.yaml",
	"config/saturn/richter.prg.yaml",
}

func buildSaturn() error {
	if err := extractSaturn(); err != nil {
		return fmt.Errorf("extract: %w", err)
	}
	if err := genSaturnNinjaIfNeeded(); err != nil {
		return err
	}
	if err := deps.Ninja(); err != nil {
		return fmt.Errorf("ninja: %w", err)
	}
	return checkVersions(os.Stderr, []string{"saturn"})
}

var saturnExtractSentinels = []string{
	"asm/saturn/game",
	"config/saturn/game_syms.txt",
	"config/saturn/zero_syms.txt",
}

func extractSaturn() error {
	for _, sentinel := range saturnExtractSentinels {
		if _, err := os.Stat(sentinel); err != nil {
			return runSaturnSplitter()
		}
	}
	return nil
}

func runSaturnSplitter() error {
	const splitter = "tools/saturn-splitter/rust-dis/target/release/rust-dis"
	for _, yaml := range saturnSplitterYAMLs {
		if err := deps.RunApp(splitter, yaml); err != nil {
			return fmt.Errorf("split %s: %w", filepath.Base(yaml), err)
		}
	}
	return nil
}

func genSaturnNinjaIfNeeded() error {
	const ninjaFile = "build.ninja"
	const stampFile = "build.ninja.version"
	const stamp = "saturn"

	needsRegen := false
	if stampData, err := os.ReadFile(stampFile); err != nil || string(stampData) != stamp {
		needsRegen = true
	}
	if !needsRegen {
		ninjaInfo, err := os.Stat(ninjaFile)
		if err != nil {
			needsRegen = true
		} else if info, err := os.Stat("tools/builds/saturn.py"); err == nil && info.ModTime().After(ninjaInfo.ModTime()) {
			needsRegen = true
		}
	}

	if needsRegen {
		if err := deps.GenSaturnNinja(); err != nil {
			return err
		}
		return os.WriteFile(stampFile, []byte(stamp), 0o644)
	}
	return nil
}
