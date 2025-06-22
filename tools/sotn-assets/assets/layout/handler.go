package layout

import (
	"bytes"
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/gfxbanks"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/sotn"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/util"
	"io"
	"path/filepath"
)

const entryCount = 53 // the number seems to be fixed

type handler struct{}

var Handler = &handler{}

func (h *handler) Name() string { return "layout" }

func (h *handler) Extract(e assets.ExtractArgs) error {
	ovlName := filepath.Base(e.AssetDir)
	r := bytes.NewReader(e.Data)
	layoutOff, err := layoutOffset(r, e.RamBase)
	if err != nil {
		return err
	}
	layouts, _, err := readEntityLayout(r, ovlName, layoutOff, e.RamBase, entryCount, true)
	return util.WriteJsonFile(assetPath(e.AssetDir, e.Name), layouts)
}

func (h *handler) Build(e assets.BuildArgs) error {
	return buildEntityLayouts(assetPath(e.AssetDir, e.Name), e.SrcDir)
}

func assetPath(dir, name string) string {
	return filepath.Join(dir, fmt.Sprintf("%s.json", name))
}

func (h *handler) Info(a assets.InfoArgs) (assets.InfoResult, error) {
	r := bytes.NewReader(a.StageData)
	boundaries := psx.Addr(0x80000000).Boundaries()
	layoutOff, err := layoutOffset(r, boundaries.StageBegin)
	if err != nil {
		return assets.InfoResult{}, err
	}
	nLayouts := 53 // it seems there are always 53 elements?!
	_, layoutsRange, err := readEntityLayout(r, "dummy", layoutOff, boundaries.StageBegin, nLayouts, true)
	if err != nil {
		return assets.InfoResult{}, fmt.Errorf("unable to gather all entity layouts: %w", err)
	}
	return assets.InfoResult{
		AssetEntries: []assets.InfoAssetEntry{
			{
				DataRange: layoutsRange[0],
				Kind:      "layout",
				Name:      "entity_layouts",
			},
		},
		SplatEntries: []assets.InfoSplatEntry{
			{
				DataRange: layoutsRange[0],
				Name:      "e_laydef",
				Comment:   "layout entries header",
			},
			{
				DataRange: layoutsRange[1],
				Name:      "e_layout",
				Comment:   "layout entries data",
			},
		},
	}, nil
}

func layoutOffset(r io.ReadSeeker, baseAddr psx.Addr) (psx.Addr, error) {
	header, err := sotn.ReadStageHeader(r)
	if err != nil {
		return psx.RamNull, err
	}
	if header.Layouts != psx.RamNull {
		return header.Layouts, nil
	}

	// ⚠️ assumption
	// some overlays have this field nulled, we have to find the offset ourselves
	// it should be usually be right after header.Graphics
	_, graphicsRange, err := gfxbanks.ReadGraphics(r, baseAddr, header.Graphics, func(addr psx.Addr) string {
		return ""
	})
	if err != nil {
		return psx.RamNull, fmt.Errorf("unable to gather all graphics: %w", err)
	}
	return graphicsRange.End(), nil
}
