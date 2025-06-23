package layer

import (
	"bytes"
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/tiledef"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/datarange"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/util"
	"path/filepath"
	"strconv"
)

type handler struct{}

var Handler = &handler{}

func (h *handler) Name() string { return "layers" }

func (h *handler) Extract(e assets.ExtractArgs) error {
	roomLayersOffset, err := findRoomsLayerArray(e)
	if err != nil {
		return fmt.Errorf("unable to find the start of OVL_EXPORT(rooms_layers): %w", err)
	}
	r := bytes.NewReader(e.Data)
	l, _, err := readLayers(r, roomLayersOffset, e.RamBase)
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
		unusedTileDef, unusedTileDefRange, err := tiledef.Read(r, offset, e.RamBase)
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

	for offset, td := range tileDefs {
		i := addrPool[offset]
		if err := tiledef.Write(td, e.AssetDir, e.OvlName, strconv.Itoa(i)); err != nil {
			return err
		}
	}
	return nil
}

func (h *handler) Build(e assets.BuildArgs) error {
	return buildLayers(e.AssetDir, filepath.Join(e.AssetDir, "layers.json"), e.SrcDir, e.OvlName)
}

func (h *handler) Info(a assets.InfoArgs) (assets.InfoResult, error) {
	// this will not work anymore. Ignore.
	return assets.InfoResult{}, nil
}

func findRoomsLayerArray(e assets.ExtractArgs) (psx.Addr, error) {
	// format is:
	//   LayerDef layer_empty = {a bunch of nulls}
	//   LayerDef layers[???] = {...}
	//   RoomDef OVL_EXPORT(rooms_layers)[???] = {...}
	// we need to find 'rooms_layers' first. This is done by assuming each entry
	// is a 0x10 long 'LayerDef'. We need to save the offset of each entry.
	// As soon as we read an entry where the address points to one of the LayerDef,
	// we can assume that is the 'rooms_layers' we've been looking for.
	//
	r := bytes.NewReader(e.Data)
	layersAddr := map[psx.Addr]struct{}{}
	for cur := e.Start; cur < e.End; cur += 4 {
		offset := e.RamBase.Sum(cur)
		if err := offset.MoveFile(r, e.RamBase); err != nil {
			return 0, err
		}
		if _, isLayerAddr := layersAddr[psx.ReadAddr(r)]; isLayerAddr == true {
			return offset, nil
		}
		layersAddr[offset] = struct{}{}
	}
	return 0, fmt.Errorf("EOF")
}

func tilemapFileName(ovl string, n int) string {
	return fmt.Sprintf("%s_tilemap_%d.bin", ovl, n)
}

func tiledefFileName(ovl string, n int) string {
	return fmt.Sprintf("%s_tiledef_%d.json", ovl, n)
}

func tiledefIndicesFileName(ovl string, n int) string {
	return fmt.Sprintf("%s_tiledef_%d_tiles.bin", ovl, n)
}

func tiledefPagesFileName(ovl string, n int) string {
	return fmt.Sprintf("%s_tiledef_%d_pages.bin", ovl, n)
}

func tiledefClutsFileName(ovl string, n int) string {
	return fmt.Sprintf("%s_tiledef_%d_cluts.bin", ovl, n)
}

func tiledefCollisionsFileName(ovl string, n int) string {
	return fmt.Sprintf("%s_tiledef_%d_cols.bin", ovl, n)
}
