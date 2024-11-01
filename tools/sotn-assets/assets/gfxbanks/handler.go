package gfxbanks

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
	"os"
	"path"
	"strings"
)

type handler struct{}

var Handler = &handler{}

func (h *handler) Name() string { return "gfx_banks" }

func (h *handler) Extract(e assets.ExtractArgs) error {
	r := bytes.NewReader(e.Data)
	baseStart := e.RamBase.Sum(e.Start)
	if err := baseStart.MoveFile(r, e.RamBase); err != nil {
		return fmt.Errorf("failed to extract graphics: %v", err)
	}
	// the data starts from the first GfxBank, not from the GfxBanks array
	// we need to search the actual begin
	actualStart := baseStart
	for {
		var a psx.Addr
		if err := binary.Read(r, binary.LittleEndian, &a); err != nil {
			return fmt.Errorf("failed to extract graphics: %v", err)
		}
		if a == baseStart {
			break
		}
		actualStart = actualStart.Sum(4)
	}
	banks, _, err := ReadGraphics(r, e.RamBase, actualStart)
	if err != nil {
		return fmt.Errorf("failed to read graphics banks: %w", err)
	}
	return util.WriteJsonFile(assetPath(e.AssetDir, e.Name), banks)
}

func (h *handler) Build(e assets.BuildArgs) error {
	ovlName := path.Base(e.SrcDir)
	data, err := os.ReadFile(assetPath(e.AssetDir, e.Name))
	if err != nil {
		return err
	}

	var gfxBanks GfxBanks
	if err := json.Unmarshal(data, &gfxBanks); err != nil {
		return err
	}
	bankSymbolNames := make([]string, len(gfxBanks.Banks))
	sb := strings.Builder{}
	sb.WriteString("// clang-format off\n")
	for i, bank := range gfxBanks.Banks {
		bankSymbolNames[i] = fmt.Sprintf("%s_gfxbank_%d", ovlName, i)
		for _, e := range bank.Entries {
			if e.isEmpty() {
				continue
			}
			sb.WriteString(fmt.Sprintf("extern u8 %s[];\n", e.symbol()))
		}
		sb.WriteString(fmt.Sprintf("static u_long* %s[] = {\n", bankSymbolNames[i]))
		switch bank.Kind {
		case GfxBankNone:
			sb.WriteString("    GFX_BANK_NONE,\n")
		case GfxBank4bpp:
			sb.WriteString("    GFX_BANK_4BPP,\n")
		case GfxBank8bpp:
			sb.WriteString("    GFX_BANK_8BPP,\n")
		case GfxBank16bpp:
			sb.WriteString("    GFX_BANK_16BPP,\n")
		case GfxBankCompressed:
			sb.WriteString("    GFX_BANK_COMPRESSED,\n")
		case GfxBankTerminate:
			break
		default:
			return fmt.Errorf("unknown gfx kind %v, valid values are "+
				"0 (none), 1 (4bpp), 2 (8bpp), 3 (16bpp) or 4 (compressed)", bank.Kind)
		}
		for _, e := range bank.Entries {
			sb.WriteString(fmt.Sprintf("    GFX_ENTRY(0x%03X, 0x%03X, %d, %d, %s),\n",
				e.X, e.Y, e.Width, e.Height, e.symbol()))
		}
		sb.WriteString("    GFX_TERMINATE(),\n")
		sb.WriteString("};\n")
	}
	sb.WriteString("u_long* OVL_EXPORT(gfxBanks)[] = {\n")
	for _, i := range gfxBanks.Indices {
		if i == -1 { // exception for ST0
			sb.WriteString("    NULL,\n")
			continue
		}
		if i < 0 || i >= len(gfxBanks.Banks) {
			return fmt.Errorf("graphics index %d (min:0, max:%d) out of range", i, len(gfxBanks.Banks))
		}
		sb.WriteString(fmt.Sprintf("    %s,\n", bankSymbolNames[i]))
	}
	sb.WriteString("};\n")
	return os.WriteFile(sourcePath(e.SrcDir, e.Name), []byte(sb.String()), 0644)
}

func (h *handler) Info(a assets.InfoArgs) (assets.InfoResult, error) {
	r := bytes.NewReader(a.StageData)
	header, err := sotn.ReadStageHeader(r)
	if err != nil {
		return assets.InfoResult{}, err
	}
	gfx, headerDataRange, err := ReadGraphics(r, psx.RamStageBegin, header.Graphics)
	if err != nil {
		return assets.InfoResult{}, fmt.Errorf("failed to read graphics banks: %w", err)
	}
	splatEntries := []assets.InfoSplatEntry{
		{
			DataRange: headerDataRange,
			Name:      "header",
			Comment:   "graphics banks",
		},
	}
	var gfxOffsets []psx.Addr
	for _, bank := range gfx.Banks {
		for _, entry := range bank.Entries {
			gfxOffsets = append(gfxOffsets, entry.addr)
		}
	}
	gfxOffsets = util.SortUniqueOffsets(gfxOffsets)
	if gfxOffsets[0] == psx.RamNull {
		gfxOffsets = gfxOffsets[1:]
	}
	for i := 0; i < len(gfxOffsets)-1; i++ {
		splatEntries = append(splatEntries, assets.InfoSplatEntry{
			DataRange: datarange.New(gfxOffsets[i], gfxOffsets[i+1]),
			Kind:      "cmp",
			Name:      fmt.Sprintf("D_%08X", uint32(gfxOffsets[i])),
		})
	}
	splatEntries = append(splatEntries, assets.InfoSplatEntry{
		DataRange: datarange.FromAddr(gfxOffsets[len(gfxOffsets)-1], 4),
		Kind:      "cmp",
		Name:      fmt.Sprintf("D_%08X", uint32(gfxOffsets[len(gfxOffsets)-1])),
		Comment:   "unknown size, please double-check",
	})
	return assets.InfoResult{
		AssetEntries: []assets.InfoAssetEntry{
			{
				DataRange: headerDataRange,
				Kind:      h.Name(),
				Name:      "graphics_banks",
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
