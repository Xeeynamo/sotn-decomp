package layer

import (
	"bytes"
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/datarange"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/sotn"
)

type handler struct{}

var Handler = &handler{}

func (h *handler) Name() string { return "layer" }

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
	l, layersRange, err := ReadLayers(r, header.Layers)
	if err != nil {
		return assets.InfoResult{}, fmt.Errorf("unable to read layers: %w", err)
	}
	_, tileMapsRange, err := ReadAllTileMaps(r, l)
	if err != nil {
		return assets.InfoResult{}, fmt.Errorf("unable to gather all the tile maps: %w", err)
	}
	tileDefs, tileDefsRange, err := ReadAllTiledefs(r, l)
	if err != nil {
		return assets.InfoResult{}, fmt.Errorf("unable to gather all the tile defs: %w", err)
	}

	// check for unused tile defs (CEN has one)
	for tileMapsRange.End() < tileDefsRange.Begin() {
		offset := tileDefsRange.Begin().Sum(-0x10)
		unusedTileDef, unusedTileDefRange, err := ReadTiledef(r, offset)
		if err != nil {
			return assets.InfoResult{}, fmt.Errorf("there is a gap between tileMaps and tileDefs: %w", err)
		}
		tileDefs[offset] = unusedTileDef
		tileDefsRange = datarange.MergeDataRanges([]datarange.DataRange{tileDefsRange, unusedTileDefRange})
	}

	return assets.InfoResult{
		SplatEntries: []assets.InfoSplatEntry{
			{
				DataRange: layersRange,
				Name:      "header",
				Comment:   "layers",
			},
			{
				DataRange: tileMapsRange,
				Name:      "tile_data",
				Comment:   "tile data",
			},
			{
				DataRange: tileDefsRange,
				Name:      "tile_data",
				Comment:   "tile definitions",
			},
		},
	}, nil
}
