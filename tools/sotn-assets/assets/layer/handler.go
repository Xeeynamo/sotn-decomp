package layer

import (
	"bytes"
	"encoding/json"
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/datarange"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/sotn"
	"os"
	"path"
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
	l, _, err := ReadLayers(r, header.Layers)
	if err != nil {
		return fmt.Errorf("unable to read layers: %w", err)
	}
	tileMaps, tileMapsRange, err := ReadAllTileMaps(r, l)
	if err != nil {
		return fmt.Errorf("unable to gather all the tile maps: %w", err)
	}
	tileDefs, tileDefsRange, err := ReadAllTiledefs(r, l)
	if err != nil {
		return fmt.Errorf("unable to gather all the tile defs: %w", err)
	}

	// check for unused tile defs (CEN has one)
	for tileMapsRange.End() < tileDefsRange.Begin() {
		offset := tileDefsRange.Begin().Sum(-0x10)
		unusedTileDef, unusedTileDefRange, err := ReadTiledef(r, offset)
		if err != nil {
			return fmt.Errorf("there is a gap between tileMaps and tileDefs: %w", err)
		}
		tileDefs[offset] = unusedTileDef
		tileDefsRange = datarange.MergeDataRanges([]datarange.DataRange{tileDefsRange, unusedTileDefRange})
	}

	outFileName := path.Join(e.AssetDir, "layers.json")
	dir := filepath.Dir(outFileName)
	if err := os.MkdirAll(dir, 0755); err != nil {
		fmt.Printf("failed to create directory %s: %v\n", dir, err)
		return err
	}

	content, err := json.MarshalIndent(l, "", "  ")
	if err != nil {
		return err
	}
	if err := os.WriteFile(outFileName, content, 0644); err != nil {
		return fmt.Errorf("unable to create layers file: %w", err)
	}

	for offset, data := range tileMaps {
		fileName := path.Join(e.AssetDir, GetTilemapFileName(offset))
		if err := os.WriteFile(fileName, data, 0644); err != nil {
			return fmt.Errorf("unable to create %q: %w", fileName, err)
		}
	}

	for offset, tileDefsData := range tileDefs {
		defs := TileDefPaths{
			Tiles:      GetTiledefIndicesFileName(offset),
			Pages:      GetTiledefPagesFileName(offset),
			Cluts:      GetTiledefClutsFileName(offset),
			Collisions: GetTiledefCollisionsFileName(offset),
		}
		if err := os.WriteFile(path.Join(e.AssetDir, defs.Tiles), tileDefsData.Tiles, 0644); err != nil {
			return fmt.Errorf("unable to create %q: %w", defs.Tiles, err)
		}
		if err := os.WriteFile(path.Join(e.AssetDir, defs.Pages), tileDefsData.Pages, 0644); err != nil {
			return fmt.Errorf("unable to create %q: %w", defs.Pages, err)
		}
		if err := os.WriteFile(path.Join(e.AssetDir, defs.Cluts), tileDefsData.Cluts, 0644); err != nil {
			return fmt.Errorf("unable to create %q: %w", defs.Cluts, err)
		}
		if err := os.WriteFile(path.Join(e.AssetDir, defs.Collisions), tileDefsData.Cols, 0644); err != nil {
			return fmt.Errorf("unable to create %q: %w", defs.Collisions, err)
		}

		content, err = json.MarshalIndent(defs, "", "  ")
		if err != nil {
			return err
		}
		fileName := path.Join(e.AssetDir, GetTiledefFileName(offset))
		if err := os.WriteFile(fileName, content, 0644); err != nil {
			return fmt.Errorf("unable to create %q: %w", fileName, err)
		}
	}
	return nil
}

func (h *handler) Build(e assets.BuildArgs) error {
	return BuildLayers(e.AssetDir, path.Join(e.AssetDir, "layers.json"), e.SrcDir)
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
