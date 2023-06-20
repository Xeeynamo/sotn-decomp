package main

import (
	"fmt"
	"os"

	"github.com/xeeynamo/sotn-decomp/tools/tmxsotn/sotn"
	"github.com/xeeynamo/sotn-decomp/tools/tmxsotn/tiled"
)

const tileSize = 16

type SotnStage struct {
	Name      string
	Path      string
	GfxPath   string
	DraBin    string
	TileDef   string
	LayoutBin string
}

func main() {
	err := exportOvlToTmx("nz0", false)
	if err != nil {
		panic(err)
	}
}

func isCollisionLayer(layer *tiled.Layer) bool {
	for _, p := range layer.Properties {
		if p.Name == "IsCollisionLayer" && p.Value == "1" {
			return true
		}
	}
	return false
}

func exportOvlToTmx(name string, showCollisionLayer bool) error {
	stage, err := sotn.MakeStage(
		name,
		fmt.Sprintf("../../assets/st/%s/rooms.layers.json", name),
		"../../assets/st",
		"../../assets/dra")
	if err != nil {
		return err
	}

	m, err := makeTmx(&stage)
	for i := 0; i < len(m.Layers); i++ {
		layer := &m.Layers[i]
		if showCollisionLayer && isCollisionLayer(layer) {
			layer.Visible = 1
		}
	}

	if err != nil {
		return err
	}

	return m.EncodeToFile(fmt.Sprintf("%s.tmx", stage.Name))
}

func makeTmx(stage *sotn.Stage) (tiled.Map, error) {
	m := tiled.Map{
		Version:     "1.0",
		Orientation: "orthogonal",
		RenderOrder: "right-down",
		TileWidth:   tileSize,
		TileHeight:  tileSize,
		Properties:  []tiled.Property{},
		Layers:      make([]tiled.Layer, 0),
	}

	gfxTilesets, err := sotn.GetStageTileset(stage.Name, stage.GfxPath)
	if err != nil {
		return m, err
	}

	m.Tilesets = make([]tiled.Tileset, len(gfxTilesets))
	for i := 0; i < len(gfxTilesets); i++ {
		clut := 0
		m.Tilesets[i] = tiled.Tileset{
			FirstGID:   uint32(1 | (i << 10) | (clut << 18)),
			Name:       fmt.Sprintf("%s %d", stage.Name, i),
			TileWidth:  tileSize,
			TileHeight: tileSize,
			Image: tiled.Image{
				Source: gfxTilesets[i],
			},
		}
	}
	m.Tilesets = append(m.Tilesets, tiled.Tileset{
		FirstGID:   0x10001,
		Name:       "col",
		TileWidth:  16,
		TileHeight: 16,
		Image: tiled.Image{
			Transparency: "#FF00FF",
			Source:       "collisions.png",
		},
	})

	for i, room := range stage.Rooms {
		appendLayer(&m, room.Fg, fmt.Sprintf("room %d fg", i))
		m.Layers = append(m.Layers, tiled.Layer{
			Name:    fmt.Sprintf("room %d col", i),
			Width:   room.Fg.Width() * tileSize,
			Height:  room.Fg.Height() * tileSize,
			OffsetX: float32(room.Fg.Rect.Left) * 256,
			OffsetY: float32(room.Fg.Rect.Top) * 256,
			Visible: 0,
			Properties: []tiled.Property{
				tiled.GetIntProperty("IsCollisionLayer", int(1)),
			},
			Data: tiled.LayerData{
				Encoding: "csv",
				Content:  getLayerCollisionContentAsCsv(room.Fg.Layout, 0x10001, room.Fg.TileDef),
			},
		})
	}

	return m, nil
}

func appendLayer(m *tiled.Map, layer *sotn.LayerDefinition, name string) {
	expectedLayoutLen := layer.Width() * tileSize * layer.Height() * tileSize
	if len(layer.Layout) != expectedLayoutLen {
		fmt.Fprintf(os.Stderr, "%s (%s) unexpected len (expected: %X, actual: %X)\n", name, layer.Symbol, expectedLayoutLen*2, len(layer.Layout)*2)
	}

	m.Layers = append(m.Layers, tiled.Layer{
		Name:    fmt.Sprintf("%s (%s)", name, layer.Symbol),
		Width:   layer.Width() * tileSize,
		Height:  layer.Height() * tileSize,
		OffsetX: float32(layer.Rect.Left) * 256,
		OffsetY: float32(layer.Rect.Top) * 256,
		Visible: 1,
		Properties: []tiled.Property{
			tiled.GetIntProperty("ScrollMode", int(layer.ScrollMode)),
			tiled.GetIntProperty("ZPriority", int(layer.ZPriority)),
			tiled.GetIntProperty("unkE", int(layer.UnkE)),
		},
		Data: tiled.LayerData{
			Encoding: "csv",
			Content:  getLayerContentAsCsv(layer.Layout, 1, layer.TileDef),
		},
	})
}

func getLayerContentAsCsv(data []uint16, base int, tileDef sotn.TileDefinition) string {
	if len(data) == 0 {
		return ""
	}

	content := ""
	for _, tid := range data {
		id := base + int(tileDef.Tiles[tid]) | (int(tileDef.Pages[tid]) << 10)
		//id |= (int(tileDef.Palettes[tid]) << 16) // palette support temporarily removed
		content += fmt.Sprintf("%d,", id)
	}

	// remove last ',' character
	return content[:len(content)-1]
}

func getLayerCollisionContentAsCsv(data []uint16, base int, tileDef sotn.TileDefinition) string {
	if len(data) == 0 {
		return ""
	}

	content := ""
	for _, tid := range data {
		id := base + int(tileDef.Collisions[tid])
		content += fmt.Sprintf("%d,", id)
	}

	// remove last ',' character
	return content[:len(content)-1]
}
