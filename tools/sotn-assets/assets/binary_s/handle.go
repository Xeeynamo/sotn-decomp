package binary_s

import (
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/util"
	"os"
	"path/filepath"
	"strings"
)

type handler struct{}

var Handler = &handler{}

func (h *handler) Name() string { return "binary_s" }

func (h *handler) Extract(e assets.ExtractArgs) error {
	return util.WriteFile(assetPath(e.AssetDir, e.Name+extension(e.Args)), e.Data[e.Start:e.End])
}

func (h *handler) Build(e assets.BuildArgs) error {
	data, err := os.ReadFile(assetPath(e.AssetDir, e.Name+extension(e.Args)))
	if err != nil {
		return fmt.Errorf("failed to read file: %w", err)
	}
	sb := strings.Builder{}
	util.WriteBytesAsHexAsm(&sb, data)
	return util.WriteFile(sourcePath(e.SrcDir, e.Name), []byte(sb.String()))
}

func (h *handler) Info(a assets.InfoArgs) (assets.InfoResult, error) {
	return assets.InfoResult{}, nil
}

func assetPath(dir, name string) string {
	return filepath.Join(dir, name)
}

func sourcePath(dir, name string) string {
	return filepath.Join(dir, fmt.Sprintf("gen/%s.s", name))
}

func extension(args []string) string {
	if len(args) > 0 {
		return "." + args[0]
	}
	return ".bin"
}
