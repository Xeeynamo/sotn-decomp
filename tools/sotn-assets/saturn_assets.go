package main

// Saturn asset extraction and building
// Uses tools/saturn/assets and config/assets.saturn.yaml

import (
	"fmt"
	"os"
	"os/exec"
	"path/filepath"
	"runtime"
	"strconv"

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
	// the player overlay whose tables partition a weapon CHR
	Prg string `yaml:"prg"`
	// matching main-player CHR carrying a bitmap's VDP1 lookup table
	Chr     string `yaml:"chr"`
	Include string `yaml:"include"`
	// or a directory of retail files
	Dir   string   `yaml:"dir"`
	Files []string `yaml:"files"`
	// editable form
	Path string `yaml:"path"`
	// rebuild output
	Output          string `yaml:"output"`
	PaletteInclude  string `yaml:"palette_include"`
	GraphicsInclude string `yaml:"graphics_include"`
	Prefix          string `yaml:"prefix"`
	Zero            string `yaml:"zero"`
	Entity int    `yaml:"entity"`
	Frames string `yaml:"frames"`
}

// one file of work; a dir entry expands into one per file
type saturnUnit struct {
	name            string
	kind            string
	variant         string
	source          string
	path            string
	output          string
	prg             string
	chr             string
	include         string
	paletteInclude  string
	graphicsInclude string
	prefix          string
	zero            string
	entity          int
	frames          string
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
	case "player":
		if a.Profile == "" || a.Prg == "" {
			return "", fmt.Errorf("asset %q: player needs a profile and the overlay prg", a.Name)
		}
		if (a.Include == "") != (a.PaletteInclude == "") {
			return "", fmt.Errorf(
				"asset %q: player needs both include and palette_include, or neither", a.Name)
		}
		return a.Profile, nil
	case "bitmap":
		if a.Profile == "" {
			return "", fmt.Errorf("asset %q: bitmap needs a profile", a.Name)
		}
		if a.Chr == "" {
			return "", fmt.Errorf("asset %q: bitmap needs the matching player chr", a.Name)
		}
		return a.Profile, nil
	case "familiar":
		if a.Profile == "" {
			return "", fmt.Errorf("asset %q: familiar needs a profile", a.Name)
		}
		if a.Prg == "" {
			return "", fmt.Errorf("asset %q: familiar needs the overlay prg", a.Name)
		}
		return a.Profile, nil
	case "weapon":
		if a.Profile == "" {
			return "", fmt.Errorf("asset %q: weapon needs a profile", a.Name)
		}
		// prg has the info to cut the chr into sprites
		if a.Prg == "" {
			return "", fmt.Errorf("asset %q: weapon needs the player prg", a.Name)
		}
		return a.Profile, nil
	case "crt":
		if a.Prg == "" {
			return "", fmt.Errorf("asset %q: crt needs 0.BIN as its prg", a.Name)
		}
		return "", nil
	case "stage":
		if a.Prg == "" || a.Zero == "" {
			return "", fmt.Errorf(
				"asset %q: stage needs the stage prg and the shared zero overlay", a.Name)
		}
		return "", nil
	case "stage-entity":
		if a.Prg == "" || a.Zero == "" {
			return "", fmt.Errorf(
				"asset %q: stage-entity needs the stage prg and the shared zero overlay", a.Name)
		}
		if a.Frames == "" || a.Prefix == "" || a.Include == "" {
			return "", fmt.Errorf(
				"asset %q: stage-entity needs frames, prefix and include", a.Name)
		}
		return "", nil
	case "sprite-package":
		if a.Include == "" {
			return "", fmt.Errorf("asset %q: sprite-package needs include", a.Name)
		}
		return "", nil
	case "map":
		if a.Prg == "" {
			return "", fmt.Errorf("asset %q: map needs the stage prg", a.Name)
		}
		if (a.Include == "") != (a.GraphicsInclude == "") {
			return "", fmt.Errorf(
				"asset %q: map needs both include and graphics_include, or neither", a.Name)
		}
		if (a.Include == "") != (a.Prefix == "") {
			return "", fmt.Errorf(
				"asset %q: map needs a prefix for the headers it generates", a.Name)
		}
		return "", nil
	default:
		return "", fmt.Errorf("unknown Saturn asset kind %q in asset %q", a.Kind, a.Name)
	}
}

func (a saturnAsset) units() ([]saturnUnit, error) {
	variant, err := a.variant()
	if err != nil {
		return nil, err
	}
	if a.Kind == "stage-entity" {
		return []saturnUnit{{
			name:    a.Name,
			kind:    a.Kind,
			prg:     a.Prg,
			zero:    a.Zero,
			entity:  a.Entity,
			frames:  a.Frames,
			prefix:  a.Prefix,
			include: a.Include,
		}}, nil
	}
	if a.Kind == "sprite-package" {
		return []saturnUnit{{
			name:    a.Name,
			kind:    a.Kind,
			include: a.Include,
		}}, nil
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
			name:            a.Name,
			kind:            a.Kind,
			variant:         variant,
			source:          a.Source,
			path:            a.Path,
			output:          output,
			prg:             a.Prg,
			chr:             a.Chr,
			include:         a.Include,
			paletteInclude:  a.PaletteInclude,
			graphicsInclude: a.GraphicsInclude,
			prefix:          a.Prefix,
			zero:            a.Zero,
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
			prg:     a.Prg,
			zero:    a.Zero,
		})
	}
	return units, nil
}

type saturnAssetConfig struct {
	Version sotn.Version  `yaml:"version"`
	Assets  []saturnAsset `yaml:"assets"`
	path string
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
	c.path = path
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
	if u.kind == "stage-entity" || u.kind == "sprite-package" {
		return nil, nil
	}
	manifest := filepath.Join(u.path, "manifest.json")
	switch command {
	case "extract":
		args := []string{u.kind, "extract"}
		if u.variant != "" {
			args = append(args, u.variant)
		}
		if u.kind == "familiar" || u.kind == "player" || u.kind == "map" {
			return append(args, u.prg, u.source, u.path), nil
		}
		if u.kind == "stage" {
			return append(args, u.prg, u.source, u.path, "--zero", u.zero), nil
		}
		if u.kind == "bitmap" {
			return append(args, u.source, u.chr, u.path), nil
		}
		if u.kind == "crt" {
			return append(args, u.prg, u.source, u.path), nil
		}
		args = append(args, u.source, u.path)
		// weapon chr uses tables in player prg
		if u.kind == "weapon" {
			args = append(args, "--prg", u.prg)
		}
		return args, nil
	case "rebuild":
		if u.kind == "player" {
			return []string{u.kind, "rebuild", manifest, u.source, u.output}, nil
		}
		if u.kind == "map" {
			return []string{u.kind, "repack", manifest, u.source, u.output,
				saturnMapLayout(u)}, nil
		}
		return []string{u.kind, "rebuild", manifest, u.output}, nil
	case "verify":
		return []string{u.kind, "verify", manifest, u.source}, nil
	default:
		return nil, fmt.Errorf("unknown command %q", command)
	}
}

var generatedHeaderKinds = map[string]bool{
	"familiar": true, "bitmap": true, "player": true, "map": true,
	"stage-entity": true, "sprite-package": true}

func saturnMapLayout(u saturnUnit) string {
	return filepath.Join(u.path, "layout.json")
}

func runSaturnGeneratedHeader(binary string, configPath string, u saturnUnit, command string) error {
	manifest := filepath.Join(u.path, "manifest.json")
	switch command {
	case "extract":
		return nil
	case "rebuild":
		if u.kind == "player" {
			return runSaturnAssets(binary, u.kind, "generate-headers",
				manifest, u.source, u.include, u.paletteInclude)
		}
		if u.kind == "map" {
			return runSaturnAssets(binary, u.kind, "generate-headers",
				saturnMapLayout(u), u.prefix, u.include, u.graphicsInclude)
		}
		if u.kind == "stage-entity" {
			return runSaturnAssets(binary, "stage", "entity-header",
				u.prg, strconv.Itoa(u.entity), u.frames, u.prefix, u.include, "--zero", u.zero)
		}
		if u.kind == "sprite-package" {
			return runSaturnAssets(binary, "sprite-package", "generate-header",
				configPath, u.name, u.include)
		}
		return runSaturnAssets(binary, u.kind, "generate-header", manifest, u.include)
	case "verify":
		if u.kind == "player" {
			return runSaturnAssets(binary, u.kind, "verify-headers",
				manifest, u.source, u.include, u.paletteInclude)
		}
		if u.kind == "map" {
			temp, err := os.MkdirTemp("", "sotn-saturn-map-verify-")
			if err != nil {
				return err
			}
			defer os.RemoveAll(temp)
			layout := filepath.Join(temp, "layout.json")
			if err := runSaturnAssets(binary, u.kind, "repack",
				manifest, u.source, filepath.Join(temp, "repacked.MAP"), layout); err != nil {
				return err
			}
			return runSaturnAssets(binary, u.kind, "verify-headers",
				layout, u.prefix, u.include, u.graphicsInclude)
		}
		if u.kind == "stage-entity" {
			return runSaturnAssets(binary, "stage", "verify-entity-header",
				u.prg, strconv.Itoa(u.entity), u.frames, u.prefix, u.include, "--zero", u.zero)
		}
		if u.kind == "sprite-package" {
			return runSaturnAssets(binary, "sprite-package", "verify-header",
				configPath, u.name, u.include)
		}
		return runSaturnAssets(binary, u.kind, "verify-header", manifest, u.include)
	default:
		return fmt.Errorf("unknown command %q", command)
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
			var err error
			if args != nil {
				err = runSaturnAssets(binary, args...)
			}
			if err == nil && generatedHeaderKinds[unit.kind] && unit.include != "" {
				err = runSaturnGeneratedHeader(binary, c.path, unit, command)
			}
			if err != nil {
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
