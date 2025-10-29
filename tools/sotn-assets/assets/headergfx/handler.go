package headergfx

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
	"strings"
)

type handler struct{}

var Handler = &handler{}

func (h *handler) Name() string { return "headergfx" }

func (h *handler) Extract(e assets.ExtractArgs) error {
	if e.Start+4 > e.End {
		return fmt.Errorf("the image data is too short")
	}
	header := e.Data[e.Start : e.Start+4]
	dec := e.Data[e.Start+4 : e.End]
	const bpp = 4
	width := int(header[0])
	height := int(header[1])
	var palette []color.RGBA
	if len(e.Args) == 1 {
		palOffset, err := util.ParseCNumber(e.Args[0])
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
	bitmap, err := util.MakeBitmap(dec, bpp)
	if err != nil {
		return fmt.Errorf("error generating image: %v", err)
	}
	if err := os.MkdirAll(e.AssetDir, 0755); err != nil {
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
	width, height := palettedImg.Rect.Max.X, palettedImg.Rect.Max.Y
	if width >= 256 || height >= 256 {
		return fmt.Errorf("image size %dx%d exceeds the limit of 255x255", width, height)
	}
	data := util.Make4bppFromBitmap(palettedImg.Pix)
	sb := strings.Builder{}
	sb.WriteString("// clang-format off\n")
	util.WriteBytesAsHex(&sb, []byte{byte(width), byte(height), 0, 0})
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
