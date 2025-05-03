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
	palette := makeGreyPalette(bpp)
	cmp := e.Data[e.Start:e.End]
	dec := sotn.Inflate(cmp)
	bitmap, err := makeBitmap(dec, bpp)
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
	return os.WriteFile(sourcePath(e.SrcDir, e.Name), []byte(sb.String()), 0644)
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
	return filepath.Join(dir, fmt.Sprintf("gen_%s.h", name))
}

func makeBitmap(data []byte, bpp int) ([]byte, error) {
	switch bpp {
	case 4:
		out := make([]byte, len(data)*2)
		for i := 0; i < len(data); i++ {
			out[i*2+0] = data[i] & 15
			out[i*2+1] = data[i] >> 4
		}
		return out, nil
	case 8:
		return data, nil
	default:
		return nil, fmt.Errorf("bpp %d invalid or not supported", bpp)
	}
}

func makeGreyPalette(bpp int) []color.RGBA {
	switch bpp {
	case 4:
		colors := make([]color.RGBA, 16)
		for i := range colors {
			c := uint8(i << 4)
			colors[i] = color.RGBA{R: c, G: c, B: c, A: 255}
		}
		return colors
	case 8:
		colors := make([]color.RGBA, 256)
		for i := range colors {
			c := uint8(i)
			colors[i] = color.RGBA{R: c, G: c, B: c, A: 255}
		}
		return colors
	default:
		return nil
	}
}
