package main

import (
	"fmt"
	"image/png"
	"os"

	"github.com/xeeynamo/sotn-decomp/tools/gfxsotn/gfx"
	"github.com/xeeynamo/sotn-decomp/tools/tmxsotn/sotn"
	"github.com/xeeynamo/sotn-decomp/tools/tmxsotn/tiled"
)

const tileSize = 16

func main() {
	err := convertMap(
		"../../iso/ST/WRP/WRP.BIN",
		"../../iso/ST/WRP/F_WRP.BIN",
		"wrp",
	)
	if err != nil {
		panic(err)
	}
}

func convertMap(binPath string, gfxPath string, mapName string) error {
	stageRaw, err := os.ReadFile(binPath)
	if err != nil {
		return err
	}

	layers := sotn.ReadStage(stageRaw)
	mainLayer := layers.Layers[layers.Rooms[0].Foreground]

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

	appendRoom(&m, &layers, 0)

	gfxTilesets, err := getGfxTilesets(gfxPath)
	if err != nil {
		return err
	}

	m.Tilesets = make([]tiled.Tileset, len(gfxTilesets))
	for i := 0; i < len(gfxTilesets); i++ {
		gfxTileset := gfxTilesets[i]
		size := gfxTileset.Img.Rect.Size()
		fileName := fmt.Sprintf("%s_%d_%d.png", mapName, gfxTileset.Clut, gfxTileset.Partition)
		m.Tilesets[i] = tiled.Tileset{
			FirstGID:   uint32(1 | (gfxTileset.Clut << 10) | (gfxTileset.Partition << 18)),
			Name:       fmt.Sprintf("%d %d", gfxTileset.Clut, gfxTileset.Partition),
			TileWidth:  tileSize,
			TileHeight: tileSize,
			Image: tiled.Image{
				Width:  size.X,
				Height: size.Y,
				Source: fileName,
			},
		}

		outFile, err := os.Create(fileName)
		if err != nil {
			return err
		}
		defer outFile.Close()
		png.Encode(outFile, gfxTileset.Img)
	}

	return m.EncodeToFile(fmt.Sprintf("%s.tmx", mapName))
}

func getGfxTilesets(filePath string) ([]gfx.ImageInfo, error) {
	gfxData, err := os.ReadFile(filePath)
	if err != nil {
		return []gfx.ImageInfo{}, err
	}

	images, err := gfx.GetGfxAsImages(gfxData)
	if err != nil {
		return []gfx.ImageInfo{}, err
	}

	return images, nil
}

func appendRoom(m *tiled.Map, layers *sotn.LayerBucket, roomIdx int) {
	room := layers.Rooms[roomIdx]
	appendLayer(m, &layers.Layers[room.Background], fmt.Sprintf("room %d bg", roomIdx))
	appendLayer(m, &layers.Layers[room.Foreground], fmt.Sprintf("room %d fg", roomIdx))
}

func appendLayer(m *tiled.Map, layerIn *sotn.LayerDefinition, name string) {
	if layerIn.Flags == 0 {
		return
	}

	m.Layers = append(m.Layers, tiled.Layer{
		Name:   name,
		Width:  layerIn.Width() * tileSize,
		Height: layerIn.Height() * tileSize,
		Properties: []tiled.Property{
			tiled.GetIntProperty("flags", int(layerIn.Flags)),
			tiled.GetIntProperty("unkC", int(layerIn.UnkC)),
			tiled.GetIntProperty("unkE", int(layerIn.UnkE)),
			tiled.GetIntProperty("unkF", int(layerIn.UnkF)),
		},
		Data: tiled.LayerData{
			Encoding: "csv",
			Content:  getLayerContentAsCsv(layerIn.Layout, layerIn.TileDef),
		},
	})
}

func getLayerContentAsCsv(data []uint16, tileDef sotn.TileDefinition) string {
	content := ""
	for _, tid := range data {
		id := 1 + int(tileDef.Tiles[tid]) |
			(int(tileDef.Palettes[tid]) << 10) |
			(int(tileDef.Pages[tid]) << 18)
		content += fmt.Sprintf("%d,", id)
	}

	// remove last ',' character
	return content[:len(content)-1]
}
