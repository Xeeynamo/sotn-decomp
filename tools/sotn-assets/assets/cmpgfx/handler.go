package cmpgfx

import (
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/sotn"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/util"
	"image"
	"image/color"
	"image/png"
	"os"
	"path"
	"strconv"
	"strings"
)

type handler struct{}

var Handler = &handler{}

func (h *handler) Name() string { return "cmpgfx" }

func (h *handler) Extract(e assets.ExtractArgs) error {
	if e.Start == e.End {
		return fmt.Errorf("a compressed image cannot be 0 bytes long")
	}
	if len(e.Args) != 3 {
		return fmt.Errorf("expected 3 arguments (width, height, bpp), got %d: %v", len(e.Args), e.Args)
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
	cmp := e.Data[e.Start:e.End]
	dec := sotn.Inflate(cmp)
	image, err := makeImage(dec, width, height, bpp, makeGreyPalette(bpp))
	if err != nil {
		return fmt.Errorf("error generating image: %v", err)
	}
	if err := util.WriteFile(assetPathAsRAW(e.AssetDir, e.Name), cmp); err != nil {
		return fmt.Errorf("error writing file: %v", err)
	}
	fout, err := os.Create(assetPathAsPNG(e.AssetDir, e.Name))
	if err != nil {
		return fmt.Errorf("error creating file: %v", err)
	}
	defer fout.Close()
	return png.Encode(fout, image)
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
	return os.WriteFile(sourcePath(e.SrcDir, e.Name), []byte(sb.String()), 0644)
}

func (h *handler) Info(a assets.InfoArgs) (assets.InfoResult, error) {
	return assets.InfoResult{}, nil
}

func assetPathAsPNG(dir, name string) string {
	return path.Join(dir, fmt.Sprintf("%s.png", name))
}

func assetPathAsRAW(dir, name string) string {
	return path.Join(dir, fmt.Sprintf("%s.cmp", name))
}

func sourcePath(dir, name string) string {
	return path.Join(dir, fmt.Sprintf("%s.h", name))
}

func makeImage(data []byte, width, height, bpp int, p color.Palette) (image.Image, error) {
	img := image.NewPaletted(image.Rectangle{image.Point{0, 0}, image.Point{width, height}}, p)
	switch bpp {
	case 4:
		if len(data)*2 < len(img.Pix) {
			return nil, fmt.Errorf("data is too small: expected %X, got %X", len(data)*2, len(img.Pix))
		}
		for i := 0; i < len(img.Pix)/2; i++ {
			img.Pix[i*2+0] = data[i] & 15
			img.Pix[i*2+1] = data[i] >> 4
		}
	case 8:
		if len(data) < len(img.Pix) {
			return nil, fmt.Errorf("data is too small: expected %X, got %X", len(data), len(img.Pix))
		}
		copy(img.Pix, data[:len(img.Pix)])
	default:
		return nil, fmt.Errorf("bpp %d invalid or not supported", bpp)
	}
	return img, nil
}

func makeGreyPalette(bpp int) color.Palette {
	switch bpp {
	case 4:
		colors := make([]color.Color, 16)
		for i := range colors {
			colors[i] = color.Gray{uint8(i << 4)}
		}
		return colors
	case 8:
		colors := make([]color.Color, 256)
		for i := range colors {
			colors[i] = color.Gray{uint8(i)}
		}
		return colors
	default:
		return nil
	}
}
