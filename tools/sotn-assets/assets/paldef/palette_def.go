package paldef

import (
	"bytes"
	"encoding/binary"
	"encoding/json"
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/datarange"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/sotn"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/util"
	"io"
	"os"
	"path"
	"strings"
)

const palBulkCopy = 5           // PAL_BULK_COPY
const palTerminate = 0xFFFFFFFF // PAL_BULK_COPY
const baseDst = 0x2000

type handler struct{}

var Handler = &handler{}

func (h *handler) Name() string { return "paldef" }

func (h *handler) Extract(e assets.ExtractArgs) error {
	r := bytes.NewReader(e.Data)
	clutAddr := e.RamBase.Sum(e.End - 4)
	if err := clutAddr.MoveFile(r, e.RamBase); err != nil {
		return fmt.Errorf("invalid offset: %w", err)
	}
	var palDefAddr psx.Addr
	if err := binary.Read(r, binary.LittleEndian, &palDefAddr); err != nil {
		return fmt.Errorf("error reading exported clut first entry: %w", err)
	}
	if palDefAddr.Real(psx.RamStageBegin) != e.Start {
		return fmt.Errorf("invalid palette entry offset, got %s but expected %s", palDefAddr, e.RamBase.Sum(e.Start))
	}
	entries, err := readPaletteEntries(r, e.RamBase, palDefAddr)
	if err != nil {
		return err
	}
	return util.WriteJsonFile(assetPath(e.AssetDir, e.Name), entries)
}

func (h *handler) Build(e assets.BuildArgs) error {
	data, err := os.ReadFile(assetPath(e.AssetDir, e.Name))
	if err != nil {
		return err
	}
	var entries []paletteEntry
	if err := json.Unmarshal(data, &entries); err != nil {
		return err
	}
	content := strings.Builder{}
	content.WriteString("// clang-format off\n")
	for _, entry := range entries {
		content.WriteString(fmt.Sprintf("extern u16* %s[0x%X];\n",
			util.RemoveFileNameExt(entry.Name), entry.Length))
	}
	content.WriteString("static u_long* pal_def[] = {\n")
	content.WriteString("    MAKE_PAL_OP(PAL_BULK_COPY, 0),\n")
	for _, entry := range entries {
		content.WriteString(fmt.Sprintf("    PAL_BULK(0x%04X, %s),\n",
			entry.Destination+baseDst,
			util.RemoveFileNameExt(entry.Name)))
	}
	content.WriteString("    PAL_TERMINATE(),\n")
	content.WriteString("};\n")
	content.WriteString("u_long** OVL_EXPORT(cluts)[] = {&pal_def};\n")
	return os.WriteFile(sourcePath(e.SrcDir, e.Name), []byte(content.String()), 0644)
}

func (h *handler) Info(a assets.InfoArgs) (assets.InfoResult, error) {
	r := bytes.NewReader(a.StageData)
	header, err := sotn.ReadStageHeader(r)
	if err != nil {
		return assets.InfoResult{}, err
	}
	if err := header.Cluts.MoveFile(r, psx.RamStageBegin); err != nil {
		return assets.InfoResult{}, fmt.Errorf("invalid offset: %w", err)
	}
	var palDefAddr psx.Addr
	if err := binary.Read(r, binary.LittleEndian, &palDefAddr); err != nil {
		return assets.InfoResult{}, fmt.Errorf("error reading exported clut first entry: %w", err)
	}
	if !palDefAddr.InRange(psx.RamStageBegin, psx.RamStageEnd) {
		return assets.InfoResult{}, fmt.Errorf("invalid palette entry at %s, address out of the stage range: got %s", header.Cluts, palDefAddr)
	}
	entries, err := readPaletteEntries(r, psx.RamStageBegin, palDefAddr)
	if err != nil {
		return assets.InfoResult{}, err
	}
	palDefRange := datarange.New(palDefAddr, header.Cluts.Sum(4))
	var splatEntries []assets.InfoSplatEntry
	splatEntries = append(splatEntries, assets.InfoSplatEntry{
		DataRange: palDefRange,
		Name:      "header",
		Comment:   "palette definitions",
	})
	for _, entry := range entries {
		splatEntries = append(splatEntries, assets.InfoSplatEntry{
			DataRange: datarange.FromAddr(entry.addr, entry.Length*2),
			Kind:      "pal",
			Name:      util.RemoveFileNameExt(entry.Name),
		})
	}
	return assets.InfoResult{
		AssetEntries: []assets.InfoAssetEntry{
			{
				DataRange: palDefRange,
				Kind:      h.Name(),
				Name:      "palette_def",
			},
		},
		SplatEntries: splatEntries,
	}, nil
}

func assetPath(dir, name string) string {
	return path.Join(dir, fmt.Sprintf("%s.json", name))
}

func sourcePath(dir, name string) string {
	return path.Join(dir, fmt.Sprintf("%s.h", name))
}

type paletteEntry struct {
	Destination int    `json:"destination"`
	Length      int    `json:"length"`
	Name        string `json:"name"`
	addr        psx.Addr
}

func readPaletteEntries(r io.ReadSeeker, baseAddr, addr psx.Addr) ([]paletteEntry, error) {
	var entries []paletteEntry
	if err := addr.MoveFile(r, baseAddr); err != nil {
		return nil, fmt.Errorf("invalid offset: %w", err)
	}
	var paletteOp uint32
	if err := binary.Read(r, binary.LittleEndian, &paletteOp); err != nil {
		return nil, fmt.Errorf("error reading palette entries: %w", err)
	}
	if paletteOp != palBulkCopy {
		return nil, fmt.Errorf("invalid palette op, expected %08X but got %08X", palBulkCopy, paletteOp)
	}
	for i := 0; ; i++ {
		var dst uint32
		var length uint32
		var addr psx.Addr
		_ = binary.Read(r, binary.LittleEndian, &dst)
		if dst == palTerminate {
			break
		}
		_ = binary.Read(r, binary.LittleEndian, &length)
		_ = binary.Read(r, binary.LittleEndian, &addr)
		if dst < baseDst {
			return nil, fmt.Errorf("invalid palette entry at %s, destination out of range: got 0x%04X, expected more than 0x%04X", baseAddr.Sum(i*4*3+4), dst, baseDst)
		}
		if dst > 0x8000 {
			return nil, fmt.Errorf("invalid palette entry at %s, destination out of range: got 0x%08X, expected less than 0x8000", baseAddr.Sum(i*4*3+4), dst)
		}
		if length > 0x1000 {
			return nil, fmt.Errorf("invalid palette entry at %s, length out of range: got 0x%08X, expected less than 0x1000", baseAddr.Sum(i*4*3+4), length)
		}
		if !addr.InRange(psx.RamStageBegin, psx.RamStageEnd) {
			return nil, fmt.Errorf("invalid palette entry at %s, address out of the stage range: got %s", baseAddr.Sum(i*4*3+4), addr)
		}
		entries = append(entries, paletteEntry{
			Destination: int(dst - baseDst),
			Length:      int(length),
			Name:        fmt.Sprintf("D_%08X.bin", uint32(addr)),
			addr:        addr,
		})
	}
	return entries, nil
}
