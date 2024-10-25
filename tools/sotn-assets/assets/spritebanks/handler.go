package spritebanks

import (
	"bytes"
	"encoding/json"
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"os"
	"path"
	"path/filepath"
)

type handler struct{}

var Handler = &handler{}

func (h *handler) Name() string { return "sprites" }

func (h *handler) Extract(e assets.ExtractEntry) error {
	if e.Start == e.End {
		return fmt.Errorf("a group of sprites cannot be 0 bytes long")
	}
	r := bytes.NewReader(e.Data)
	banks, _, err := ReadSpritesBanks(r, e.RamBase, e.RamBase.Sum(e.Start))
	if err != nil {
		return fmt.Errorf("failed to read sprites: %w", err)
	}
	content, err := json.MarshalIndent(banks, "", "  ")
	if err != nil {
		return err
	}
	outFileName := assetPath(e.AssetDir, e.Name)
	dir := filepath.Dir(outFileName)
	if err := os.MkdirAll(dir, 0755); err != nil {
		fmt.Printf("failed to create directory %s: %v\n", dir, err)
		return err
	}
	return os.WriteFile(outFileName, content, 0644)
}

func (h *handler) Build(e assets.BuildEntry) error {
	return BuildSprites(assetPath(e.AssetDir, e.Name), e.SrcDir)
}

func assetPath(dir, name string) string {
	if name == "" {
		name = "sprite_banks"
	}
	return path.Join(dir, fmt.Sprintf("%s.json", name))
}

func sourcePath(dir, name string) string {
	if name == "" {
		name = "sprite_banks"
	}
	return path.Join(dir, fmt.Sprintf("%s.h", name))
}
