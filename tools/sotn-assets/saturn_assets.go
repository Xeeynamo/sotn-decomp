package main

// Saturn asset extraction and building
// Uses tools/saturn/assets and config/assets.saturn.yaml

import (
	"fmt"
	"os"
	"os/exec"
	"path/filepath"

	"github.com/goccy/go-yaml"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/sotn"
	"golang.org/x/sync/errgroup"
)

const (
	saturnAssetsManifest  = "tools/saturn/assets/Cargo.toml"
	saturnAssetsTargetDir = "build/saturn-assets"
)

type saturnAsset struct {
	Name string `yaml:"name"`
	// asset type
	Kind string `yaml:"kind"`
	// e.g. font profile
	Profile string `yaml:"profile"`
	// retail file
	Source string `yaml:"source"`
	// editable form
	Path string `yaml:"path"`
	// rebuild output
	Output string `yaml:"output"`
}

func (a saturnAsset) outputPath() string {
	if a.Output != "" {
		return a.Output
	}
	return filepath.Join("build/saturn/assets", filepath.Base(a.Source))
}

type saturnAssetConfig struct {
	Version sotn.Version  `yaml:"version"`
	Assets  []saturnAsset `yaml:"assets"`
}

func readSaturnAssetConfig(path string) (*saturnAssetConfig, bool, error) {
	data, err := os.ReadFile(path)
	if err != nil {
		return nil, false, fmt.Errorf("error reading YAML file: %v", err)
	}
	var c saturnAssetConfig
	if err := yaml.Unmarshal(data, &c); err != nil {
		return nil, false, fmt.Errorf("error unmarshalling YAML file: %v", err)
	}
	if c.Version != sotn.VersionSaturn {
		return nil, false, nil
	}
	return &c, true, nil
}

func saturnAssetsBinary() (string, error) {
	cmd := exec.Command("cargo", "build", "--release",
		"--manifest-path", saturnAssetsManifest,
		"--target-dir", saturnAssetsTargetDir)
	cmd.Stdout = os.Stderr
	cmd.Stderr = os.Stderr
	if err := cmd.Run(); err != nil {
		return "", fmt.Errorf("unable to build %s: %w", saturnAssetsManifest, err)
	}
	return filepath.Join(saturnAssetsTargetDir, "release", "saturn-assets"), nil
}

func runSaturnAssets(binary string, args ...string) error {
	cmd := exec.Command(binary, args...)
	cmd.Stdout = os.Stderr
	cmd.Stderr = os.Stderr
	if err := cmd.Run(); err != nil {
		return fmt.Errorf("%s %v: %w", binary, args, err)
	}
	return nil
}

func saturnAssetArgs(a saturnAsset, command string) ([]string, error) {
	switch a.Kind {
	case "font":
		switch command {
		case "extract":
			return []string{"font", "extract", a.Profile, a.Source, a.Path}, nil
		case "rebuild":
			return []string{"font", "rebuild",
				filepath.Join(a.Path, "manifest.json"), a.outputPath()}, nil
		case "verify":
			return []string{"font", "verify",
				filepath.Join(a.Path, "manifest.json"), a.Source}, nil
		}
		return nil, fmt.Errorf("unknown command %q", command)
	default:
		return nil, fmt.Errorf("unknown Saturn asset kind %q in asset %q", a.Kind, a.Name)
	}
}

func forEachSaturnAsset(c *saturnAssetConfig, command string) error {
	binary, err := saturnAssetsBinary()
	if err != nil {
		return err
	}
	var eg errgroup.Group
	for _, asset := range c.Assets {
		args, err := saturnAssetArgs(asset, command)
		if err != nil {
			return err
		}
		eg.Go(func() error {
			if err := runSaturnAssets(binary, args...); err != nil {
				return fmt.Errorf("asset %q: %w", asset.Name, err)
			}
			return nil
		})
	}
	return eg.Wait()
}

func extractSaturnAssets(c *saturnAssetConfig) error {
	return forEachSaturnAsset(c, "extract")
}

func buildSaturnAssets(c *saturnAssetConfig) error {
	return forEachSaturnAsset(c, "rebuild")
}

func verifySaturnAssets(c *saturnAssetConfig) error {
	return forEachSaturnAsset(c, "verify")
}
