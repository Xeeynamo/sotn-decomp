package cmpgfx

import (
	"fmt"
	"image/color"
	"os"
	"path/filepath"
	"strconv"
	"strings"

	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/sotn"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/util"
)

type handler struct{}

var Handler = &handler{}

func (h *handler) Name() string { return "cmpgfx" }

func (h *handler) Extract(e assets.ExtractArgs) error {
	if e.Start == e.End {
		return fmt.Errorf("a compressed image cannot be 0 bytes long")
	}
	if len(e.Args) < 3 || len(e.Args) > 4 {
		return fmt.Errorf("invalid arguments, expected <width> <height> <bpp> <palette>")
	}
	width, err := strconv.Atoi(e.Args[0])
	if err != nil {
		return fmt.Errorf("width value %v is not a number", e.Args[0])
	}
	height, err := strconv.Atoi(e.Args[1])
	if err != nil {
		return fmt.Errorf("height value %v is not a number", e.Args[1])
	}
	bpp, err := strconv.Atoi(e.Args[2])
	if err != nil {
		return fmt.Errorf("bpp value %v is not a number", e.Args[2])
	}
	var palette []color.RGBA
	if len(e.Args) == 4 {
		str := e.Args[3]
		if len(str) > 2 {
			str = str[2:]
		}
		palOffset, err := util.ParseCNumber(e.Args[3])
		if err != nil {
			return err
		}
		if palOffset < 0 || palOffset >= len(e.Data) {
			return fmt.Errorf("palette offset value %s is out of bounds", e.Args[3])
		}
		palData := e.Data[int(palOffset) : palOffset+(1<<bpp)*2]
		palette = util.MakePaletteFromR5G5B5A1(palData, false)
	} else {
		palette = util.MakeGreyPalette(bpp)
	}
	cmp := e.Data[e.Start:e.End]
	dec := sotn.Inflate(cmp)
	bitmap, err := util.MakeBitmap(dec, bpp)
	if err != nil {
		return fmt.Errorf("error generating image: %v", err)
	}
	if err := util.WriteFile(assetPathAsRAW(e.AssetDir, e.Name), cmp); err != nil {
		return fmt.Errorf("error writing file: %v", err)
	}
	fout, err := util.CreateAtomicWriter(assetPathAsPNG(e.AssetDir, e.Name))
	if err != nil {
		return fmt.Errorf("error creating file: %v", err)
	}
	defer fout.Close()
	return util.PngEncode(fout, bitmap, width, height, palette)
}

func (h *handler) Build(e assets.BuildArgs) error {
	inFileName := assetPathAsRAW(e.AssetDir, e.Name)
	data, err := os.ReadFile(inFileName)
	if err != nil {
		return fmt.Errorf("failed to read file: %w", err)
	}
	sb := strings.Builder{}
	sb.WriteString("// clang-format off\n")
	util.WriteBytesAsHex(&sb, data)
	return util.WriteFile(sourcePath(e.SrcDir, e.Name), []byte(sb.String()))
}

func (h *handler) Info(a assets.InfoArgs) (assets.InfoResult, error) {
	return assets.InfoResult{}, nil
}

func assetPathAsPNG(dir, name string) string {
	return filepath.Join(dir, fmt.Sprintf("%s.png", name))
}

func assetPathAsRAW(dir, name string) string {
	return filepath.Join(dir, fmt.Sprintf("%s.cmp", name))
}

func sourcePath(dir, name string) string {
	return filepath.Join(dir, fmt.Sprintf("gen/%s.h", name))
}
