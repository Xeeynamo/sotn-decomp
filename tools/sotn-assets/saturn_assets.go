package main

// Saturn asset extraction and building
// Uses tools/saturn/assets and config/assets.saturn.yaml

import (
	"fmt"
	"os"
	"os/exec"
	"path/filepath"
	"runtime"

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
	// e.g. audio codec
	Codec string `yaml:"codec"`
	// retail file
	Source string `yaml:"source"`
	// or a directory of retail files
	Dir   string   `yaml:"dir"`
	Files []string `yaml:"files"`
	// editable form
	Path string `yaml:"path"`
	// rebuild output
	Output string `yaml:"output"`
}

// one file of work; a dir entry expands into one per file
type saturnUnit struct {
	name    string
	kind    string
	variant string
	source  string
	path    string
	output  string
}

const saturnAssetOutputDir = "build/saturn/assets"

// the option field this kind uses
func (a saturnAsset) variant() (string, error) {
	switch a.Kind {
	case "font":
		if a.Profile == "" {
			return "", fmt.Errorf("asset %q: font needs a profile", a.Name)
		}
		return a.Profile, nil
	case "audio":
		if a.Codec == "" {
			return "", fmt.Errorf("asset %q: audio needs a codec", a.Name)
		}
		return a.Codec, nil
	default:
		return "", fmt.Errorf("unknown Saturn asset kind %q in asset %q", a.Kind, a.Name)
	}
}

func (a saturnAsset) units() ([]saturnUnit, error) {
	variant, err := a.variant()
	if err != nil {
		return nil, err
	}
	if a.Source != "" && len(a.Files) > 0 {
		return nil, fmt.Errorf("asset %q sets both source and files", a.Name)
	}

	if a.Source != "" {
		output := a.Output
		if output == "" {
			output = filepath.Join(saturnAssetOutputDir, filepath.Base(a.Source))
		}
		return []saturnUnit{{
			name:    a.Name,
			kind:    a.Kind,
			variant: variant,
			source:  a.Source,
			path:    a.Path,
			output:  output,
		}}, nil
	}

	if len(a.Files) == 0 {
		return nil, fmt.Errorf("asset %q names neither source nor files", a.Name)
	}
	outputDir := a.Output
	if outputDir == "" {
		outputDir = saturnAssetOutputDir
	}
	units := make([]saturnUnit, 0, len(a.Files))
	for _, file := range a.Files {
		units = append(units, saturnUnit{
			name:    fmt.Sprintf("%s/%s", a.Name, file),
			kind:    a.Kind,
			variant: variant,
			source:  filepath.Join(a.Dir, file),
			path:    filepath.Join(a.Path, file),
			output:  filepath.Join(outputDir, file),
		})
	}
	return units, nil
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

func saturnUnitArgs(u saturnUnit, command string) ([]string, error) {
	manifest := filepath.Join(u.path, "manifest.json")
	switch command {
	case "extract":
		return []string{u.kind, "extract", u.variant, u.source, u.path}, nil
	case "rebuild":
		return []string{u.kind, "rebuild", manifest, u.output}, nil
	case "verify":
		return []string{u.kind, "verify", manifest, u.source}, nil
	default:
		return nil, fmt.Errorf("unknown command %q", command)
	}
}

func forEachSaturnAsset(c *saturnAssetConfig, command string) error {
	binary, err := saturnAssetsBinary()
	if err != nil {
		return err
	}
	var units []saturnUnit
	for _, asset := range c.Assets {
		expanded, err := asset.units()
		if err != nil {
			return err
		}
		units = append(units, expanded...)
	}

	var eg errgroup.Group
	// audio streams are huge, don't run them all at once
	eg.SetLimit(runtime.NumCPU())
	for _, unit := range units {
		args, err := saturnUnitArgs(unit, command)
		if err != nil {
			return err
		}
		eg.Go(func() error {
			if err := runSaturnAssets(binary, args...); err != nil {
				return fmt.Errorf("asset %q: %w", unit.name, err)
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
