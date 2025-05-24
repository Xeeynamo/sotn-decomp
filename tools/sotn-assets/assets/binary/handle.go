package binary

import (
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/util"
	"os"
	"path/filepath"
	"slices"
	"strings"
)

type handler struct{}

var Handler = &handler{}

func (h *handler) Name() string { return "binary" }

func (h *handler) Extract(e assets.ExtractArgs) error {
	return util.WriteFile(assetPath(e.AssetDir, e.Name+extension(e.Args)), e.Data[e.Start:e.End])
}

func (h *handler) Build(e assets.BuildArgs) error {
	if slices.Contains(e.Args, "--skip-build") {
		return nil
	}
	data, err := os.ReadFile(assetPath(e.AssetDir, e.Name+extension(e.Args)))
	if err != nil {
		return fmt.Errorf("failed to read file: %w", err)
	}
	sb := strings.Builder{}
	util.WriteBytesAsHex(&sb, data)
	return util.WriteFile(sourcePath(e.SrcDir, e.Name), []byte(sb.String()))
}

func (h *handler) Info(a assets.InfoArgs) (assets.InfoResult, error) {
	return assets.InfoResult{}, nil
}

func assetPath(dir, name string) string {
	return filepath.Join(dir, name)
}

func sourcePath(dir, name string) string {
	return filepath.Join(dir, fmt.Sprintf("gen/%s.h", name))
}

func extension(args []string) string {
	if len(args) > 0 {
		return "." + args[0]
	}
	return ".bin"
}
