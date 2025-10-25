package tiledef

import (
	"bytes"
	"encoding/binary"
	"encoding/json"
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/datarange"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/util"
	"io"
	"os"
	"path/filepath"
	"strings"
)

type handler struct{}

type TileDef struct {
	Tiles []byte
	Pages []byte
	Cluts []byte
	Cols  []byte
}

type tileDefPaths struct {
	Tiles      string `json:"tiles"`
	Pages      string `json:"pages"`
	Cluts      string `json:"cluts"`
	Collisions string `json:"collisions"`
}

var Handler = &handler{}

func (h *handler) Name() string { return "tiledef" }

func (h *handler) Extract(e assets.ExtractArgs) error {
	r := bytes.NewReader(e.Data)
	td, _, err := Read(r, e.RamBase.Sum(e.End-0x10), e.RamBase)
	if err != nil {
		return err
	}
	return Write(td, e.AssetDir, e.OvlName, e.Name)
}

func (h *handler) Build(e assets.BuildArgs) error {
	name := tiledefFileName(e.OvlName, e.Name)
	fullPath := filepath.Join(e.AssetDir, name)
	symbol := makeSymbolFromFileName(name)
	return Build(fullPath, symbol, e.SrcDir)
}

func (h *handler) Info(a assets.InfoArgs) (assets.InfoResult, error) {
	return assets.InfoResult{}, nil
}

func Read(r io.ReadSeeker, off, baseAddr psx.Addr) (TileDef, datarange.DataRange, error) {
	if err := off.MoveFile(r, baseAddr); err != nil {
		return TileDef{}, datarange.DataRange{}, err
	}

	offsets := make([]psx.Addr, 4)
	if err := binary.Read(r, binary.LittleEndian, offsets); err != nil {
		return TileDef{}, datarange.DataRange{}, err
	}

	// one of these sections might fall to BSS on PSP, we need to be careful.
	// whenever we do offsets[x] < off, we check if the data falls to BSS.
	assumedLength := 0x7FFFFFFF
	if offsets[1] < off && offsets[0] < off {
		assumedLength = int(offsets[1] - offsets[0])
	}
	if offsets[2] < off && offsets[1] < off {
		assumedLength = min(assumedLength, int(offsets[2]-offsets[1]))
	}
	if offsets[3] < off && offsets[2] < off {
		assumedLength = min(assumedLength, int(offsets[2]-offsets[1]))
	}
	td := TileDef{
		Tiles: make([]byte, assumedLength),
		Pages: make([]byte, assumedLength),
		Cluts: make([]byte, assumedLength),
		Cols:  make([]byte, assumedLength),
	}

	if offsets[0] < off {
		if err := offsets[0].MoveFile(r, baseAddr); err != nil {
			return TileDef{}, datarange.DataRange{}, err
		}
		if _, err := r.Read(td.Tiles); err != nil {
			return TileDef{}, datarange.DataRange{}, err
		}
	}
	if offsets[1] < off {
		if err := offsets[1].MoveFile(r, baseAddr); err != nil {
			return TileDef{}, datarange.DataRange{}, err
		}
		if _, err := r.Read(td.Pages); err != nil {
			return TileDef{}, datarange.DataRange{}, err
		}
	}
	if offsets[2] < off {
		if err := offsets[2].MoveFile(r, baseAddr); err != nil {
			return TileDef{}, datarange.DataRange{}, err
		}
		if _, err := r.Read(td.Cluts); err != nil {
			return TileDef{}, datarange.DataRange{}, err
		}
	}
	if offsets[3] < off {
		if err := offsets[3].MoveFile(r, baseAddr); err != nil {
			return TileDef{}, datarange.DataRange{}, err
		}
		if _, err := r.Read(td.Cols); err != nil {
			return TileDef{}, datarange.DataRange{}, err
		}
	}
	return td, datarange.New(offsets[0], off.Sum(0x10)), nil
}

func Write(td TileDef, outPath, ovl, suffix string) error {
	defs := tileDefPaths{
		Tiles:      tiledefIndicesFileName(ovl, suffix),
		Pages:      tiledefPagesFileName(ovl, suffix),
		Cluts:      tiledefClutsFileName(ovl, suffix),
		Collisions: tiledefCollisionsFileName(ovl, suffix),
	}
	if err := util.WriteFile(filepath.Join(outPath, defs.Tiles), td.Tiles); err != nil {
		return fmt.Errorf("unable to create %q: %w", defs.Tiles, err)
	}
	if err := util.WriteFile(filepath.Join(outPath, defs.Pages), td.Pages); err != nil {
		return fmt.Errorf("unable to create %q: %w", defs.Pages, err)
	}
	if err := util.WriteFile(filepath.Join(outPath, defs.Cluts), td.Cluts); err != nil {
		return fmt.Errorf("unable to create %q: %w", defs.Cluts, err)
	}
	if err := util.WriteFile(filepath.Join(outPath, defs.Collisions), td.Cols); err != nil {
		return fmt.Errorf("unable to create %q: %w", defs.Collisions, err)
	}
	if err := util.WriteJsonFile(filepath.Join(outPath, tiledefFileName(ovl, suffix)), defs); err != nil {
		return fmt.Errorf("unable to create layers file: %w", err)
	}
	return nil
}

func Build(inFile, symbol, outDir string) error {
	data, err := os.ReadFile(inFile)
	if err != nil {
		return err
	}

	var tiledef tileDefPaths
	if err := json.Unmarshal(data, &tiledef); err != nil {
		return err
	}

	outFileName := filepath.Join(outDir, fmt.Sprintf("gen/%s.h", symbol))
	if err := os.MkdirAll(filepath.Dir(outFileName), 0755); err != nil {
		return err
	}
	f, err := os.Create(outFileName)
	if err != nil {
		return err
	}
	defer f.Close()

	tilesSymbol := makeSymbolFromFileName(tiledef.Tiles)
	tilesFileName := filepath.Join(filepath.Dir(inFile), tiledef.Tiles)
	if err := writeStaticU8(f, tilesFileName, tilesSymbol); err != nil {
		return err
	}

	pagesSymbol := makeSymbolFromFileName(tiledef.Pages)
	pagesFileName := filepath.Join(filepath.Dir(inFile), tiledef.Pages)
	if err := writeStaticU8(f, pagesFileName, pagesSymbol); err != nil {
		return err
	}

	clutsSymbol := makeSymbolFromFileName(tiledef.Cluts)
	clutsFileName := filepath.Join(filepath.Dir(inFile), tiledef.Cluts)
	if err := writeStaticU8(f, clutsFileName, clutsSymbol); err != nil {
		return err
	}

	colsSymbol := makeSymbolFromFileName(tiledef.Collisions)
	colsFileName := filepath.Join(filepath.Dir(inFile), tiledef.Collisions)
	if err := writeStaticU8(f, colsFileName, colsSymbol); err != nil {
		return err
	}

	_, _ = f.WriteString("// clang-format off\n")
	_, _ = f.WriteString(fmt.Sprintf("TileDefinition %s[] = {\n", symbol))
	_, _ = f.WriteString(fmt.Sprintf("    %s,\n", tilesSymbol))
	_, _ = f.WriteString(fmt.Sprintf("    %s,\n", pagesSymbol))
	_, _ = f.WriteString(fmt.Sprintf("    %s,\n", clutsSymbol))
	_, _ = f.WriteString(fmt.Sprintf("    %s,\n", colsSymbol))
	_, _ = f.WriteString("};\n")

	return nil
}

func tiledefFileName(ovl string, suffix string) string {
	return fmt.Sprintf("%s_tiledef_%s.json", ovl, suffix)
}

func tiledefIndicesFileName(ovl string, suffix string) string {
	return fmt.Sprintf("%s_tiledef_%s_tiles.bin", ovl, suffix)
}

func tiledefPagesFileName(ovl string, suffix string) string {
	return fmt.Sprintf("%s_tiledef_%s_pages.bin", ovl, suffix)
}

func tiledefClutsFileName(ovl string, suffix string) string {
	return fmt.Sprintf("%s_tiledef_%s_cluts.bin", ovl, suffix)
}

func tiledefCollisionsFileName(ovl string, suffix string) string {
	return fmt.Sprintf("%s_tiledef_%s_cols.bin", ovl, suffix)
}

func makeSymbolFromFileName(fileName string) string {
	return strings.Split(filepath.Base(fileName), ".")[0]
}

func writeStaticU8(w io.Writer, fileName string, symbol string) error {
	data, err := os.ReadFile(fileName)
	if err != nil {
		return err
	}

	var sb strings.Builder
	sb.WriteString("// clang-format off\n")
	sb.WriteString(fmt.Sprintf("static unsigned char %s[] = {\n", symbol))
	util.WriteBytesAsHex(&sb, data)
	sb.WriteString("};\n")

	_, err = w.Write([]byte(sb.String()))
	return err
}
