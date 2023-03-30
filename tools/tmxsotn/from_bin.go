package main

import (
	"fmt"
	"image/png"
	"os"

	"github.com/xeeynamo/sotn-decomp/tools/gfxsotn/gfx"
	"github.com/xeeynamo/sotn-decomp/tools/tmxsotn/sotn"
	"github.com/xeeynamo/sotn-decomp/tools/tmxsotn/tiled"
)

// This code path is pretty much unmaintained. It was used to convert stages
// into TMX directly from the ST/*/*.BIN but the system is pretty much
// obsolete as it does not allow to relocate any data

func writeTmxFromBin(binPath string, gfxPath string, name string) error {
	stageRaw, err := os.ReadFile(binPath)
	if err != nil {
		return err
	}

	bucket := sotn.ReadStage(stageRaw)
	mainLayer := bucket.Layers[bucket.Rooms[0].Foreground]
	m, err := makeTmx(name, gfxPath, bucket, mainLayer)
	if err != nil {
		return err
	}

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
			FirstGID:   uint32(1 | (gfxTileset.Clut << 8) | (gfxTileset.Partition << 16)),
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

	return m.EncodeToFile(fmt.Sprintf("%s.tmx", name))
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
