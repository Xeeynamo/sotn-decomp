package rawgfx

import (
	"bytes"
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/util"
	"image"
	"image/color"
	"image/png"
	"os"
	"path/filepath"
	"strconv"
	"strings"
)

type handler struct{}

var Handler = &handler{}

func (h *handler) Name() string { return "rawgfx" }

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
		palOffset, err := util.ParseCNumber(e.Args[3])
		if err != nil {
			return err
		}
		if palOffset < 0 || palOffset >= len(e.Data) {
			return fmt.Errorf("palette offset value %s is out of bounds", e.Args[3])
		}
		palData := e.Data[palOffset : palOffset+(1<<bpp)*2]
		palette = util.MakePaletteFromR5G5B5A1(palData, true)
	} else {
		palette = util.MakeGreyPalette(bpp)
	}
	dec := e.Data[e.Start:e.End]
	bitmap, err := util.MakeBitmap(dec, bpp)
	if err != nil {
		return fmt.Errorf("error generating image: %v", err)
	}
	if err := os.MkdirAll(filepath.Dir(assetPath(e.AssetDir, e.Name)), 0755); err != nil {
		return fmt.Errorf("error creating directory: %v", err)
	}
	fout, err := util.CreateAtomicWriter(assetPath(e.AssetDir, e.Name))
	if err != nil {
		return fmt.Errorf("error creating file: %v", err)
	}
	defer fout.Close()
	return util.PngEncode(fout, bitmap, width, height, palette)
}

func (h *handler) Build(e assets.BuildArgs) error {
	inFileName := assetPath(e.AssetDir, e.Name)
	pngData, err := os.ReadFile(inFileName)
	if err != nil {
		return fmt.Errorf("failed to read file: %w", err)
	}

	img, err := png.Decode(bytes.NewReader(pngData))
	if err != nil {
		return fmt.Errorf("failed to decode PNG %s: %w", inFileName, err)
	}
	palettedImg, ok := img.(*image.Paletted)
	if !ok {
		return fmt.Errorf("image %s is not paletted", inFileName)
	}
	bpp, err := strconv.Atoi(e.Args[2])
	if err != nil {
		return fmt.Errorf("bpp value %v is not a number", e.Args[2])
	}
	data := palettedImg.Pix
	switch bpp {
	case 1:
		data = util.Make1bppFromBitmap(data)
	case 4:
		data = util.Make4bppFromBitmap(data)
	case 8:
	default:
		return fmt.Errorf("bpp value %v is not supported", bpp)
	}
	sb := strings.Builder{}
	sb.WriteString("// clang-format off\n")
	util.WriteBytesAsHex(&sb, data)
	return util.WriteFile(sourcePath(e.SrcDir, e.Name), []byte(sb.String()))
}

func (h *handler) Info(a assets.InfoArgs) (assets.InfoResult, error) {
	return assets.InfoResult{}, nil
}

func assetPath(dir, name string) string {
	return filepath.Join(dir, fmt.Sprintf("%s.png", name))
}

func sourcePath(dir, name string) string {
	return filepath.Join(dir, fmt.Sprintf("gen/%s.h", name))
}
