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
		"wrp.tmx",
		"wrp",
	)
	if err != nil {
		panic(err)
	}
}

func convertMap(binPath string, gfxPath string, outPath string, name string) error {
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

	appendLayer(&m, &layers, 0)

	gfxTilesets, err := getGfxTilesets(gfxPath)
	if err != nil {
		return err
	}

	m.Tilesets = make([]tiled.Tileset, len(gfxTilesets))
	for i := 0; i < len(gfxTilesets); i++ {
		gfxTileset := gfxTilesets[i]
		size := gfxTileset.Img.Rect.Size()
		fileName := fmt.Sprintf("%s_%d_%d.png", name, gfxTileset.Clut, gfxTileset.Partition)
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

	return m.EncodeToFile(outPath)
}

func getGfxTilesets(filePath string) ([]gfx.ImageInfo, error) {
	gfxData, err := os.ReadFile(filePath)
	if err != nil {
		return []gfx.ImageInfo{}, err
	}

	images, err := gfx.GetGfxAsImages(gfxData, gfx.DefaultConfig)
	if err != nil {
		return []gfx.ImageInfo{}, err
	}

	return images, nil
}

func appendLayer(m *tiled.Map, layers *sotn.LayerBucket, roomIdx int) {
	room := layers.Rooms[0]
	lin := layers.Layers[room.Foreground]
	lout := tiled.Layer{}

	lout.Name = fmt.Sprintf("room %d fg", roomIdx)
	lout.Width = lin.Width() * tileSize
	lout.Height = lin.Height() * tileSize
	lout.Data.Encoding = "csv"
	lout.Properties = []tiled.Property{
		tiled.GetIntProperty("flags", int(lin.Flags)),
		tiled.GetIntProperty("unkC", int(lin.UnkC)),
		tiled.GetIntProperty("unkE", int(lin.UnkE)),
		tiled.GetIntProperty("unkF", int(lin.UnkF)),
	}

	for _, tid := range lin.Layout {
		id := 1 + int(lin.TileDef.Tiles[tid]) |
			(int(lin.TileDef.Palettes[tid]) << 10) |
			(int(lin.TileDef.Pages[tid]) << 18)
		lout.Data.Content += fmt.Sprintf("%d,", id)
	}
	// remove last ',' character
	lout.Data.Content = lout.Data.Content[:len(lout.Data.Content)-1]

	m.Layers = append(m.Layers, lout)
}
