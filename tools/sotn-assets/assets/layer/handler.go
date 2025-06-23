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

	tilemapAddrs := map[psx.Addr]struct{}{}
	tiledefAddrs := map[psx.Addr]struct{}{}
	for _, layerData := range l {
		if layerData.fg != nil {
			tilemapAddrs[layerData.fg.Data] = struct{}{}
			tiledefAddrs[layerData.fg.Tiledef] = struct{}{}
		}
		if layerData.bg != nil {
			tilemapAddrs[layerData.bg.Data] = struct{}{}
			tiledefAddrs[layerData.bg.Tiledef] = struct{}{}
		}
	}
	addrPool := util.MergeMaps(util.SortedIndexMap(tileMaps), util.SortedIndexMap(tileDefs))
	roomLayers := make([]map[string]layerUnpacked, len(l))
	for i, layerData := range l {
		roomLayers[i] = make(map[string]layerUnpacked)
		if layerData.fg != nil {
			roomLayers[i]["fg"] = layerData.fg.unpack(e.OvlName, addrPool)
		}
		if layerData.bg != nil {
			roomLayers[i]["bg"] = layerData.bg.unpack(e.OvlName, addrPool)
		}
	}
	if err := util.WriteJsonFile(filepath.Join(e.AssetDir, "layers.json"), roomLayers); err != nil {
		return fmt.Errorf("unable to create layers file: %w", err)
	}

	for offset, data := range tileMaps {
		fileName := filepath.Join(e.AssetDir, tilemapFileName(e.OvlName, addrPool[offset]))
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
		if err := util.WriteJsonFile(filepath.Join(e.AssetDir, tiledefFileName(e.OvlName, addrPool[offset])), defs); err != nil {
			return fmt.Errorf("unable to create layers file: %w", err)
		}
	}
	return nil
}

func (h *handler) Build(e assets.BuildArgs) error {
	return buildLayers(e.AssetDir, filepath.Join(e.AssetDir, "layers.json"), e.SrcDir, e.OvlName)
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

func tilemapFileName(ovl string, n int) string {
	return fmt.Sprintf("%s_tilemap_%d.bin", ovl, n)
}

func tiledefFileName(ovl string, n int) string {
	return fmt.Sprintf("%s_tiledef_%d.json", ovl, n)
}

func tiledefIndicesFileName(n int) string {
	return fmt.Sprintf("tiledef_%05X_tiles.bin", n)
}

func tiledefPagesFileName(n int) string {
	return fmt.Sprintf("tiledef_%05X_pages.bin", n)
}

func tiledefClutsFileName(n int) string {
	return fmt.Sprintf("tiledef_%05X_cluts.bin", n)
}

func tiledefCollisionsFileName(n int) string {
	return fmt.Sprintf("tiledef_%05X_cols.bin", n)
}
