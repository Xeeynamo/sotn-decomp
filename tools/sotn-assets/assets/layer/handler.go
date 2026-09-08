package layer

import (
	"bytes"
	"fmt"
	"path/filepath"
	"sort"

	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/tiledef"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/sotn"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/util"
)

type handler struct{}

var Handler = &handler{}

func (h *handler) Name() string { return "layers" }

func (h *handler) Extract(e assets.ExtractArgs) error {
	roomLayersOffset, err := findRoomsLayerArray(e)
	if err != nil {
		return fmt.Errorf("unable to find the start of rooms_layers: %w", err)
	}
	r := bytes.NewReader(e.Data)
	l, _, err := readLayers(r, roomLayersOffset, e.RamBase)
	if err != nil {
		return fmt.Errorf("unable to read layers: %w", err)
	}
	tileMaps, _, err := readAllTileMaps(r, e.RamBase, l)
	if err != nil {
		return fmt.Errorf("unable to gather all the tile maps: %w", err)
	}
	tileDefs, err := readAllTiledefs(r, e.RamBase, l)
	if err != nil {
		return fmt.Errorf("unable to gather all the tile defs: %w", err)
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
	tilemapIndices := util.SortedIndexMap(tileMaps)
	tiledefSuffixes := tiledefNames(tileDefs, e.OvlName)

	roomLayers := make([]map[string]layerUnpacked, len(l))
	for i, layerData := range l {
		roomLayers[i] = make(map[string]layerUnpacked)
		if layerData.fg != nil {
			roomLayers[i]["fg"] = layerData.fg.unpack(e.OvlName, tilemapIndices, tiledefSuffixes)
		}
		if layerData.bg != nil {
			roomLayers[i]["bg"] = layerData.bg.unpack(e.OvlName, tilemapIndices, tiledefSuffixes)
		}
	}
	if err := util.WriteJsonFile(assetPath(e.AssetDir, e.Name), roomLayers); err != nil {
		return fmt.Errorf("unable to create layers file: %w", err)
	}

	tilesDir := filepath.Dir(filepath.Join(e.AssetDir, e.Name))
	for offset, data := range tileMaps {
		fileName := filepath.Join(tilesDir, tilemapFileName(e.OvlName, tilemapIndices[offset]))
		if err := util.WriteFile(fileName, data); err != nil {
			return fmt.Errorf("unable to create %q: %w", fileName, err)
		}
	}

	for offset, td := range tileDefs {
		if err := tiledef.Write(td, tilesDir, e.OvlName, tiledefSuffixes[offset]); err != nil {
			return err
		}
	}
	return nil
}

func tiledefNames(tileDefs map[psx.Addr]tiledef.TileDef, ovlName string) map[psx.Addr]string {
	addrs := make([]psx.Addr, 0, len(tileDefs))
	for addr := range tileDefs {
		addrs = append(addrs, addr)
	}
	sort.Slice(addrs, func(i, j int) bool { return addrs[i] < addrs[j] })

	names := make(map[psx.Addr]string, len(tileDefs))
	nth := 0
	for _, addr := range addrs {
		if name, found := tiledef.WellKnownName(tileDefs[addr]); found {
			names[addr] = name
			continue
		}
		if nth == 0 {
			names[addr] = ovlName
		} else {
			names[addr] = fmt.Sprintf("%s_%d", ovlName, nth)
		}
		nth++
	}
	return names
}

func (h *handler) Build(e assets.BuildArgs) error {
	outString, err := buildLayers(e.AssetDir, assetPath(e.AssetDir, e.Name), e.SrcDir, e.OvlName)
	if err != nil {
		return err
	}
	return util.WriteFile(sourcePath(e.SrcDir, e.Name), []byte(outString))
}

func (h *handler) Info(a assets.InfoArgs) (assets.InfoResult, error) {
	r := bytes.NewReader(a.StageData)
	header, err := sotn.ReadStageHeader(r)
	if err != nil {
		return assets.InfoResult{}, err
	}
	if header.Layers == psx.RamNull || header.Layers == 0 {
		// SEL and friends have no layers at all
		return assets.InfoResult{}, nil
	}
	boundaries := header.Layers.Boundaries()
	_, rng, err := readLayers(r, header.Layers, boundaries.StageBegin)
	if err != nil {
		return assets.InfoResult{}, fmt.Errorf("unable to read layers at %s: %w", header.Layers, err)
	}
	if rng.Empty() {
		return assets.InfoResult{}, nil
	}
	return assets.InfoResult{
		AssetEntries: []assets.InfoAssetEntry{
			{DataRange: rng, Kind: h.Name(), Name: "layers"},
		},
		SplatEntries: []assets.InfoSplatEntry{
			{DataRange: rng, Name: "layers"},
		},
	}, nil
}

func findRoomsLayerArray(e assets.ExtractArgs) (psx.Addr, error) {
	// format is:
	//   LayerDef layer_empty = {a bunch of nulls}
	//   LayerDef layers[???] = {...}
	//   RoomDef rooms_layers[???] = {...}
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

func assetPath(dir, name string) string {
	return filepath.Join(dir, fmt.Sprintf("%s.json", name))
}
func sourcePath(dir, name string) string {
	return filepath.Join(dir, fmt.Sprintf("gen/%s.h", name))
}
