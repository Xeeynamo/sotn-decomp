package layer

import (
	"bytes"
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/datarange"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/sotn"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/util"
	"path/filepath"
)

type handler struct{}

var Handler = &handler{}

func (h *handler) Name() string { return "layers" }

func (h *handler) Extract(e assets.ExtractArgs) error {
	r := bytes.NewReader(e.Data)
	header, err := sotn.ReadStageHeader(r)
	if err != nil {
		return err
	}
	l, _, err := readLayers(r, header.Layers, e.RamBase)
	if err != nil {
		return fmt.Errorf("unable to read layers: %w", err)
	}
	tileMaps, tileMapsRange, err := readAllTileMaps(r, e.RamBase, l)
	if err != nil {
		return fmt.Errorf("unable to gather all the tile maps: %w", err)
	}
	tileDefs, tileDefsRange, err := readAllTiledefs(r, e.RamBase, l)
	if err != nil {
		return fmt.Errorf("unable to gather all the tile defs: %w", err)
	}

	// check for unused tile defs (CEN has one)
	for tileMapsRange.End() < tileDefsRange.Begin() {
		offset := tileDefsRange.Begin().Sum(-0x10)
		unusedTileDef, unusedTileDefRange, err := readTiledef(r, offset, e.RamBase)
		if err != nil {
			return fmt.Errorf("there is a gap between tileMaps and tileDefs: %w", err)
		}
		tileDefs[offset] = unusedTileDef
		tileDefsRange = datarange.MergeDataRanges([]datarange.DataRange{tileDefsRange, unusedTileDefRange})
	}

	for _, layerData := range l { // cheap solution to "adjust" the addresses
		if layerData.fg != nil {
			layerData.fg.Data = psx.Addr(layerData.fg.Data.Real(e.RamBase))
			layerData.fg.Tiledef = psx.Addr(layerData.fg.Tiledef.Real(e.RamBase))
		}
		if layerData.bg != nil {
			layerData.bg.Data = psx.Addr(layerData.bg.Data.Real(e.RamBase))
			layerData.bg.Tiledef = psx.Addr(layerData.bg.Tiledef.Real(e.RamBase))
		}
	}
	if err := util.WriteJsonFile(filepath.Join(e.AssetDir, "layers.json"), l); err != nil {
		return fmt.Errorf("unable to create layers file: %w", err)
	}

	for offset, data := range tileMaps {
		fileName := filepath.Join(e.AssetDir, tilemapFileName(offset.Real(e.RamBase)))
		if err := util.WriteFile(fileName, data); err != nil {
			return fmt.Errorf("unable to create %q: %w", fileName, err)
		}
	}

	for offset, tileDefsData := range tileDefs {
		real := offset.Real(e.RamBase)
		defs := tileDefPaths{
			Tiles:      tiledefIndicesFileName(real),
			Pages:      tiledefPagesFileName(real),
			Cluts:      tiledefClutsFileName(real),
			Collisions: tiledefCollisionsFileName(real),
		}
		if err := util.WriteFile(filepath.Join(e.AssetDir, defs.Tiles), tileDefsData.Tiles); err != nil {
			return fmt.Errorf("unable to create %q: %w", defs.Tiles, err)
		}
		if err := util.WriteFile(filepath.Join(e.AssetDir, defs.Pages), tileDefsData.Pages); err != nil {
			return fmt.Errorf("unable to create %q: %w", defs.Pages, err)
		}
		if err := util.WriteFile(filepath.Join(e.AssetDir, defs.Cluts), tileDefsData.Cluts); err != nil {
			return fmt.Errorf("unable to create %q: %w", defs.Cluts, err)
		}
		if err := util.WriteFile(filepath.Join(e.AssetDir, defs.Collisions), tileDefsData.Cols); err != nil {
			return fmt.Errorf("unable to create %q: %w", defs.Collisions, err)
		}
		if err := util.WriteJsonFile(filepath.Join(e.AssetDir, tiledefFileName(real)), defs); err != nil {
			return fmt.Errorf("unable to create layers file: %w", err)
		}
	}
	return nil
}

func (h *handler) Build(e assets.BuildArgs) error {
	return buildLayers(e.AssetDir, filepath.Join(e.AssetDir, "layers.json"), e.SrcDir)
}

func (h *handler) Info(a assets.InfoArgs) (assets.InfoResult, error) {
	r := bytes.NewReader(a.StageData)
	header, err := sotn.ReadStageHeader(r)
	if err != nil {
		return assets.InfoResult{}, err
	}
	boundaries := header.Layers.Boundaries()
	l, layersRange, err := readLayers(r, header.Layers, boundaries.StageBegin)
	if err != nil {
		return assets.InfoResult{}, fmt.Errorf("unable to read layers: %w", err)
	}
	_, tileMapsRange, err := readAllTileMaps(r, boundaries.StageBegin, l)
	if err != nil {
		return assets.InfoResult{}, fmt.Errorf("unable to gather all the tile maps: %w", err)
	}
	tileDefs, tileDefsRange, err := readAllTiledefs(r, boundaries.StageBegin, l)
	if err != nil {
		return assets.InfoResult{}, fmt.Errorf("unable to gather all the tile defs: %w", err)
	}

	// check for unused tile defs (CEN has one)
	for tileMapsRange.End() < tileDefsRange.Begin() {
		offset := tileDefsRange.Begin().Sum(-0x10)
		unusedTileDef, unusedTileDefRange, err := readTiledef(r, offset, boundaries.StageBegin)
		if err != nil {
			return assets.InfoResult{}, fmt.Errorf("there is a gap between tileMaps and tileDefs: %w", err)
		}
		tileDefs[offset] = unusedTileDef
		tileDefsRange = datarange.MergeDataRanges([]datarange.DataRange{tileDefsRange, unusedTileDefRange})
	}

	return assets.InfoResult{
		AssetEntries: []assets.InfoAssetEntry{
			{
				DataRange: layersRange,
				Kind:      "layers",
				Name:      "layers",
			},
		},
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

func tilemapFileName(off int) string {
	return fmt.Sprintf("tilemap_%05X.bin", uint32(off&0x7FFFFFFF))
}

func tiledefFileName(off int) string {
	return fmt.Sprintf("tiledef_%05X.json", uint32(off&0x7FFFFFFF))
}

func tiledefIndicesFileName(off int) string {
	return fmt.Sprintf("tiledef_%05X_tiles.bin", uint32(off&0x7FFFFFFF))
}

func tiledefPagesFileName(off int) string {
	return fmt.Sprintf("tiledef_%05X_pages.bin", uint32(off&0x7FFFFFFF))
}

func tiledefClutsFileName(off int) string {
	return fmt.Sprintf("tiledef_%05X_cluts.bin", uint32(off&0x7FFFFFFF))
}

func tiledefCollisionsFileName(off int) string {
	return fmt.Sprintf("tiledef_%05X_cols.bin", uint32(off&0x7FFFFFFF))
}
