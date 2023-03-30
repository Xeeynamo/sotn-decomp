package main

import (
	"fmt"

	"github.com/xeeynamo/sotn-decomp/tools/tmxsotn/sotn"
	"github.com/xeeynamo/sotn-decomp/tools/tmxsotn/tiled"
)

const tileSize = 16

func main() {
	err := writeTmxFromDecomp(
		"wrp",
		"../../assets/out",
		"../../assets/dra",
		"../../assets/st",
		"../../assets/st/wrp",
		"../../assets/st/wrp/D_80186D78.tiledef.json",
		"../../assets/st/wrp/D_80182368.tilelayout.bin",
	)
	// err := writeTmxFromBin(
	// 	"../../iso/ST/WRP/WRP.BIN",
	// 	"../../iso/ST/WRP/F_WRP.BIN",
	// 	"wrp",
	// )
	if err != nil {
		panic(err)
	}
}

func writeTmxFromDecomp(
	name string,
	outPath string,
	draPath string,
	gfxPath string,
	stagePath string,
	tiledefFileName string,
	layoutFileName string) error {

	tiledef, err := sotn.ReadTileDefinitionFromJson(stagePath, tiledefFileName)
	if err != nil {
		return err
	}

	tilemap, err := sotn.ReadLayout(layoutFileName)
	if err != nil {
		return err
	}

	layer := sotn.LayerDefinition{
		TileDef: tiledef,
		Layout:  tilemap,
		Rect: sotn.Rect{
			Left:   0,
			Top:    0,
			Right:  0,
			Bottom: 0,
		},
		ScrollMode: 1,
		ZPriority:  0x60,
		UnkE:       0,
	}
	bucket := sotn.LayerBucket{
		Layers: make([]sotn.LayerDefinition, 0),
	}
	bucket.Layers = append(bucket.Layers, layer)

	m, err := makeTmx(name, gfxPath, bucket, bucket.Layers[0])
	if err != nil {
		return err
	}
	return m.EncodeToFile(fmt.Sprintf("%s.tmx", name))
}

func makeTmx(
	name string,
	gfxPath string,
	bucket sotn.LayerBucket,
	mainLayer sotn.LayerDefinition) (tiled.Map, error) {
	m := tiled.Map{
		Version:     "1.0",
		Orientation: "orthogonal",
		RenderOrder: "right-down",
		Width:       mainLayer.Width() * 16,
		Height:      mainLayer.Height() * 16,
		TileWidth:   tileSize,
		TileHeight:  tileSize,
		Properties:  []tiled.Property{},
		Layers:      make([]tiled.Layer, 0),
	}

	appendLayer(&m, &mainLayer, name)

	gfxTilesets, err := sotn.GetStageTileset(name, gfxPath)
	if err != nil {
		return m, err
	}

	m.Tilesets = make([]tiled.Tileset, len(gfxTilesets))
	for i := 0; i < len(gfxTilesets); i++ {
		clut := 0
		m.Tilesets[i] = tiled.Tileset{
			FirstGID:   uint32(1 | (i << 10) | (clut << 18)),
			Name:       fmt.Sprintf("%s %d", name, i),
			TileWidth:  tileSize,
			TileHeight: tileSize,
			Image: tiled.Image{
				Source: gfxTilesets[i],
			},
		}
	}

	return m, nil
}

func appendRoom(m *tiled.Map, layers *sotn.LayerBucket, roomIdx int) {
	room := layers.Rooms[roomIdx]
	appendLayer(m, &layers.Layers[room.Background], fmt.Sprintf("room %d bg", roomIdx))
	appendLayer(m, &layers.Layers[room.Foreground], fmt.Sprintf("room %d fg", roomIdx))
}

func appendLayer(m *tiled.Map, layerIn *sotn.LayerDefinition, name string) {
	m.Layers = append(m.Layers, tiled.Layer{
		Name:    name,
		Width:   layerIn.Width() * tileSize,
		Height:  layerIn.Height() * tileSize,
		OffsetX: float32(layerIn.Rect.Left) * 256,
		OffsetY: float32(layerIn.Rect.Top) * 256,
		Properties: []tiled.Property{
			tiled.GetIntProperty("ScrollMode", int(layerIn.ScrollMode)),
			tiled.GetIntProperty("ZPriority", int(layerIn.ZPriority)),
			tiled.GetIntProperty("unkE", int(layerIn.UnkE)),
		},
		Data: tiled.LayerData{
			Encoding: "csv",
			Content:  getLayerContentAsCsv(layerIn.Layout, layerIn.TileDef),
		},
	})
}

func getLayerContentAsCsv(data []uint16, tileDef sotn.TileDefinition) string {
	if len(data) == 0 {
		return ""
	}

	content := ""
	for _, tid := range data {
		id := 1 + int(tileDef.Tiles[tid]) | (int(tileDef.Pages[tid]) << 8)
		//id |= (int(tileDef.Palettes[tid]) << 16) // palette support temporarily removed
		content += fmt.Sprintf("%d,", id)
	}

	// remove last ',' character
	return content[:len(content)-1]
}
