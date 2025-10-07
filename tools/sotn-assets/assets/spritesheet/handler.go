package spritesheet

import (
	"bytes"
	"crypto/sha1"
	"encoding/binary"
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/sotn"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/util"
	"golang.org/x/sync/errgroup"
	"gopkg.in/yaml.v3"
	"image"
	"image/color"
	"image/png"
	"io"
	"os"
	"path/filepath"
	"strings"
)

const BPP = 4

type spriteEntry struct {
	Name           string
	PivotX, PivotY uint8
	Padding        uint16 `yaml:"padding,omitempty"`
}

type handler struct{}

var Handler = &handler{}

func (h *handler) Name() string { return "spritesheet" }

func (h *handler) Extract(e assets.ExtractArgs) error {
	if e.Start == e.End {
		return fmt.Errorf("a compressed image cannot be 0 bytes long")
	}
	if len(e.Args) >= 3 {
		return fmt.Errorf("invalid arguments, expected <palette_file> <palette_offset>")
	}
	var palette []color.RGBA
	if len(e.Args) >= 2 {
		offset, err := util.ParseCNumber(e.Args[1])
		f, err := os.Open(e.Args[0])
		if err != nil {
			return fmt.Errorf("failed to open palette file %s: %w", e.Args[0], err)
		}
		_, _ = f.Seek(int64(offset), io.SeekStart)
		data := make([]byte, 0x20)
		read, err := f.Read(data)
		if err != nil || read != len(data) {
			if err == nil {
				err = io.ErrUnexpectedEOF
			}
			return fmt.Errorf("failed to read palette file %s: %w", e.Args[0], err)
		}
		palette = util.MakePaletteFromR5G5B5A1(data, true)
	} else {
		palette = util.MakeGreyPalette(BPP)
	}
	headerFirst := sotn.GetPlatform() == sotn.PlatformPSX
	start := e.Start
	maxSpritCount := 0x100
	r := bytes.NewReader(e.Data)
	if !headerFirst {
		// on PSP the header is at the end, so we need to find the pointers from the end
		start = e.End
		maxSpritCount = 0
		for {
			addr := psx.GetAddr(e.Data[start-4 : start])
			if addr.Real(e.RamBase) >= e.End || addr.Real(e.RamBase) < e.Start {
				break
			}
			start -= 4
			maxSpritCount++
		}
	}
	if err := e.RamBase.Sum(start).MoveFile(r, e.RamBase); err != nil {
		return err
	}
	if err := os.MkdirAll(filepath.Join(e.AssetDir, e.Name), 0755); err != nil && !os.IsExist(err) {
		return err
	}
	eg := errgroup.Group{}
	entries := make([]spriteEntry, 0, 0x100)
	for i := 0; i < maxSpritCount; i++ {
		spritePtr := psx.ReadAddr(r)
		if spritePtr < e.RamBase {
			break
		}
		offset := spritePtr.Real(e.RamBase)
		if offset < e.Start || offset >= e.End {
			return fmt.Errorf("sprite pointer %v is out of bounds [%X:%X]", spritePtr, e.Start, e.End)
		}
		spriteData := e.Data[offset:]
		entry := spriteEntry{
			Name:   fmt.Sprintf("%s/%s_%d.png", e.Name, e.Name, len(entries)),
			PivotX: spriteData[2],
			PivotY: spriteData[3],
		}
		w := int(spriteData[0])
		h := int(spriteData[1])
		byteCount := (w*h + 1) / 2
		padding := 4 - (byteCount & 3)

		if padding == 2 {
			paddingData := binary.LittleEndian.Uint16(spriteData[4+byteCount:])
			if paddingData != 0 {
				entry.Padding = paddingData
			}
		}
		entries = append(entries, entry)
		eg.Go(func() error {
			bitmap, err := util.MakeBitmap(spriteData[4:4+w*h/2], BPP)
			if err != nil {
				return fmt.Errorf("error generating image: %v", err)
			}
			f, err := util.CreateAtomicWriter(filepath.Join(e.AssetDir, entry.Name))
			if err != nil {
				return err
			}
            defer f.Close()
			if err := util.PngEncode(f, bitmap, w, h, palette); err != nil {
				return fmt.Errorf("failed to encode %s: %w", entry.Name, err)
			}
			return nil
		})
	}
	eg.Go(func() error {
		asYaml, err := yaml.Marshal(entries)
		if err != nil {
			return fmt.Errorf("yaml error: %w", err)
		}
		return util.WriteFile(assetPath(e.AssetDir, e.Name), asYaml)
	})
	return eg.Wait()
}

func (h *handler) Build(e assets.BuildArgs) error {
	yamlFileName := assetPath(e.AssetDir, e.Name)
	yamlData, err := os.ReadFile(yamlFileName)
	if err != nil {
		return nil
	}
	var entries []spriteEntry
	if err := yaml.Unmarshal(yamlData, &entries); err != nil {
		return fmt.Errorf("yaml error for %s: %w", yamlFileName, err)
	}
	headerFirst := sotn.GetPlatform() == sotn.PlatformPSX
	symbols := make([]string, len(entries))
	symbolDataLen := make([]int, len(entries))
	lastHash := [20]byte{}
	lastSymbol := ""
	sbData := strings.Builder{}
	sbData.WriteString("// clang-format off\n")
	for i, entry := range entries {
		pngData, err := os.ReadFile(filepath.Join(e.AssetDir, entry.Name))
		if err != nil {
			return err
		}
		hash := sha1.Sum(pngData)
		if hash == lastHash {
			symbols[i] = lastSymbol
			symbolDataLen[i] = -1
			continue
		}
		img, err := png.Decode(bytes.NewReader(pngData))
		if err != nil {
			return fmt.Errorf("failed to decode PNG %s: %w", entry.Name, err)
		}
		palettedImg, ok := img.(*image.Paletted)
		if !ok {
			return fmt.Errorf("image %s is not paletted", entry.Name)
		}
		if palettedImg.Rect.Dx()%4 != 0 {
			return fmt.Errorf("image %s is not a multiple of 4 pixels wide", entry.Name)
		}
		rawData := util.Make4bppFromBitmap(palettedImg.Pix)
		symbolDataLen[i] = 4 + len(rawData)
		if entry.Padding != 0 {
			symbolDataLen[i] += 2
		}
		symbol := fmt.Sprintf("%s_%d", e.Name, i)
		symbols[i] = symbol
		lastHash = hash
		lastSymbol = symbol
		sbData.WriteString(fmt.Sprintf("static unsigned char %s[] = {\n", symbol))
		sbData.WriteString(fmt.Sprintf("%d, %d, %d, %d,\n",
			palettedImg.Rect.Dx(),
			palettedImg.Rect.Dy(),
			entry.PivotX,
			entry.PivotY))
		util.WriteBytesAsHex(&sbData, rawData)
		if entry.Padding != 0 {
			util.WriteBytesAsHex(&sbData, []byte{byte(entry.Padding & 0xFF), byte(entry.Padding >> 8)})
		}
		sbData.WriteString("};\n")
	}
	sbHeader := strings.Builder{}
	sbHeader.WriteString("// clang-format off\n")
	if headerFirst {
		for i := 0; i < len(entries); i++ {
			if symbolDataLen[i] == -1 {
				continue
			}
			sbHeader.WriteString(fmt.Sprintf("static unsigned char %s[%d];\n", symbols[i], symbolDataLen[i]))
		}
	}
	sbHeader.WriteString(fmt.Sprintf("unsigned char* %s_sprites[] = {\n", e.Name))
	for i := 0; i < len(entries); i++ {
		sbHeader.WriteString(symbols[i])
		sbHeader.WriteString(",\n")
	}
	sbHeader.WriteString("};\n")

	dstFile := sourcePath(e.SrcDir, e.Name)
	if err := os.MkdirAll(filepath.Dir(dstFile), 0755); err != nil {
		return fmt.Errorf("failed to create directory: %w", err)
	}
	f, err := util.CreateAtomicWriter(dstFile)
	if err != nil {
		return err
	}
	defer f.Close()
	if headerFirst {
		if _, err := f.WriteString(sbHeader.String()); err != nil {
			return fmt.Errorf("failed to write header in %s: %w", f.Name(), err)
		}
		if _, err := f.WriteString(sbData.String()); err != nil {
			return fmt.Errorf("failed to write data in %s: %w", f.Name(), err)
		}
	} else {
		if _, err := f.WriteString(sbData.String()); err != nil {
			return fmt.Errorf("failed to write data in %s: %w", f.Name(), err)
		}
		if _, err := f.WriteString(sbHeader.String()); err != nil {
			return fmt.Errorf("failed to write header in %s: %w", f.Name(), err)
		}
	}
	return nil
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
