package layout

import (
	"bytes"
	"encoding/json"
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/graphics"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/sotn"
	"io"
	"os"
	"path"
)

const entryCount = 53 // the number seems to be fixed

type handler struct{}

var Handler = &handler{}

func (h *handler) Name() string { return "layout" }

func (h *handler) Extract(e assets.ExtractArgs) error {
	ovlName := path.Base(e.AssetDir)
	r := bytes.NewReader(e.Data)
	layoutOff, err := layoutOffset(r)
	if err != nil {
		return err
	}
	layouts, _, err := readEntityLayout(r, ovlName, layoutOff, entryCount, true)
	if err != nil {
		return err
	}
	content, err := json.MarshalIndent(layouts, "", "  ")
	if err != nil {
		return err
	}
	return os.WriteFile(assetPath(e.AssetDir, e.Name), content, 0644)
}

func (h *handler) Build(e assets.BuildArgs) error {
	return buildEntityLayouts(assetPath(e.AssetDir, e.Name), e.SrcDir)
}

func assetPath(dir, name string) string {
	return path.Join(dir, fmt.Sprintf("%s.json", name))
}

func (h *handler) Info(a assets.InfoArgs) (assets.InfoResult, error) {
	r := bytes.NewReader(a.StageData)
	layoutOff, err := layoutOffset(r)
	if err != nil {
		return assets.InfoResult{}, err
	}
	nLayouts := 53 // it seems there are always 53 elements?!
	_, layoutsRange, err := readEntityLayout(r, "dummy", layoutOff, nLayouts, true)
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

func layoutOffset(r io.ReadSeeker) (psx.Addr, error) {
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
	_, graphicsRange, err := graphics.ReadGraphics(r, header.Graphics)
	if err != nil {
		return psx.RamNull, fmt.Errorf("unable to gather all graphics: %w", err)
	}
	return graphicsRange.End(), nil
}
