package layout

import (
	"bytes"
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	graphics2 "github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/graphics"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/sotn"
)

const entryCount = 53 // the number seems to be fixed

type handler struct{}

var Handler = &handler{}

func (h *handler) Name() string { return "layout" }

func (h *handler) Extract(e assets.ExtractArgs) error {
	return nil
}

func (h *handler) Build(e assets.BuildArgs) error {
	return nil
}

func (h *handler) Info(a assets.InfoArgs) (assets.InfoResult, error) {
	r := bytes.NewReader(a.StageData)
	header, err := sotn.ReadStageHeader(r)
	if err != nil {
		return assets.InfoResult{}, err
	}
	layoutOff := header.Layouts
	if layoutOff == psx.RamNull {
		// ⚠️ assumption
		// some overlays have this field nulled, we have to find the offset ourselves
		// it should be usually be right after header.Graphics
		_, graphicsRange, err := graphics2.ReadGraphics(r, header.Graphics)
		if err != nil {
			return assets.InfoResult{}, fmt.Errorf("unable to gather all graphics: %w", err)
		}
		layoutOff = graphicsRange.End()
	}
	nLayouts := 53 // it seems there are always 53 elements?!
	_, layoutsRange, err := ReadEntityLayout(r, "dummy", layoutOff, nLayouts, true)
	if err != nil {
		return assets.InfoResult{}, fmt.Errorf("unable to gather all entity layouts: %w", err)
	}
	return assets.InfoResult{
		SplatEntries: []assets.InfoEntry{
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
