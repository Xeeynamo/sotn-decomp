package palette

import (
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/util"
	"golang.org/x/sync/errgroup"
	"gopkg.in/yaml.v2"
	"image/color"
	"io"
	"os"
	"path"
	"path/filepath"
	"strconv"
	"strings"
)

type handler struct{}

type paletteFormater interface {
	Export(io.Writer, []color.RGBA) error
	Import(io.Reader) ([]color.RGBA, error)
}

type paletteContainer struct {
	ColorsPerPalette int      `yaml:"colors_per_palette"`
	Palettes         []string `yaml:"palettes"`
}

var Handler = &handler{}

var formats = map[string]paletteFormater{
	"jasc": &paletteJasc{},
	"png":  &palettePng{},
}
var extensions = map[string]string{
	"jasc": "pal",
	"png":  "png",
}

func (h *handler) Name() string { return "palette" }

func (h *handler) Extract(e assets.ExtractArgs) error {
	const format string = "png"
	if len(e.Args) != 1 {
		return fmt.Errorf("must specify <color_count>")
	}
	formatHandler := formats[format]
	colorsPerPalette, err := strconv.Atoi(e.Args[0])
	if err != nil || (colorsPerPalette != 16 && colorsPerPalette != 256) {
		return fmt.Errorf("color count must be 16 or 256, got %q", e.Args[0])
	}
	byteCountPerPalette := colorsPerPalette * 2
	paletteCount := (e.End - e.Start) / byteCountPerPalette
	paletteNames := make([]string, paletteCount)
	if paletteCount == 1 {
		fileName := fmt.Sprintf("%s.%s", filepath.Base(e.Name), extensions[format])
		paletteNames[0] = filepath.Join(e.Name, fileName)
	} else {
		extension := extensions[format]
		for i := 0; i < paletteCount; i++ {
			fileName := fmt.Sprintf("%s_%d.%s", filepath.Base(e.Name), i, extension)
			paletteNames[i] = filepath.Join(e.Name, fileName)
		}
	}
	if err := os.MkdirAll(filepath.Join(e.AssetDir, e.Name), 0755); err != nil && !os.IsExist(err) {
		return err
	}
	var eg errgroup.Group
	eg.Go(func() error {
		data, err := yaml.Marshal(paletteContainer{
			ColorsPerPalette: colorsPerPalette,
			Palettes:         paletteNames,
		})
		if err != nil {
			return err
		}
		return util.WriteFile(assetPath(e.AssetDir, e.Name), data)
	})
	data := e.Data[e.Start:e.End]
	for i, paletteFileName := range paletteNames {
		i, paletteFileName := i, paletteFileName
		eg.Go(func() error {
			f, err := util.CreateAtomicWriter(filepath.Join(e.AssetDir, paletteFileName))
			if err != nil {
				return err
			}
			defer f.Close()
			offset := i * byteCountPerPalette
			paletteData := data[offset : offset+byteCountPerPalette]
			return formatHandler.Export(f, util.MakePaletteFromR5G5B5A1(paletteData, false))
		})
	}
	return eg.Wait()
}

func (h *handler) Build(e assets.BuildArgs) error {
	assetMetadata, err := os.ReadFile(assetPath(e.AssetDir, e.Name))
	if err != nil {
		return err
	}
	var paletteContainer paletteContainer
	if err := yaml.Unmarshal(assetMetadata, &paletteContainer); err != nil {
		return fmt.Errorf("failed to parse %s: %w", assetPath(e.AssetDir, e.Name), err)
	}
	data := make([]uint16, 0, paletteContainer.ColorsPerPalette*len(paletteContainer.Palettes))
	for _, paletteFileName := range paletteContainer.Palettes {
		actualFileName := filepath.Join(e.AssetDir, paletteFileName)
		f, err := os.Open(actualFileName)
		if err != nil {
			return fmt.Errorf("failed to read palette: %w", err)
		}
		defer f.Close()
		var formatHandler paletteFormater
		switch path.Ext(paletteFileName) {
		case ".png":
			formatHandler = formats["png"]
		case ".pal":
			formatHandler = formats["jasc"]
		default:
			return fmt.Errorf("unknown palette format for %s", path.Ext(paletteFileName))
		}
		palette, err := formatHandler.Import(f)
		if err != nil {
			return fmt.Errorf("failed to parse palette at %s: %w", actualFileName, err)
		}
		if len(palette) != paletteContainer.ColorsPerPalette {
			return fmt.Errorf("palette at %s has %d colors, expected %d", actualFileName, len(palette), paletteContainer.ColorsPerPalette)
		}
		for _, c := range palette {
			transparencyBit := 0
			if c.A < 128 {
				transparencyBit = 0x8000
			}
			data = append(data, uint16(int(c.R)>>3|int(c.G)>>3<<5|int(c.B)>>3<<10|transparencyBit))
		}
	}
	sb := strings.Builder{}
	sb.WriteString("// clang-format off\n")
	util.WriteWordsAsHex(&sb, data)
	return util.WriteFile(sourcePath(e.SrcDir, e.Name), []byte(sb.String()))
}

func (h *handler) Info(a assets.InfoArgs) (assets.InfoResult, error) {
	return assets.InfoResult{}, nil
}

func assetPath(dir, name string) string {
	return filepath.Join(dir, fmt.Sprintf("%s.yaml", name))
}

func sourcePath(dir, name string) string {
	return filepath.Join(dir, fmt.Sprintf("gen/%s.h", name))
}
