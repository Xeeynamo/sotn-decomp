package sotn

import (
	"encoding/json"
	"os"
	"path"
)

type Rect struct {
	Left, Top, Right, Bottom int
}

func (r *Rect) Width() int {
	return r.Right - r.Left + 1
}
func (r *Rect) Height() int {
	return r.Bottom - r.Top + 1
}

type roomsDef []struct {
	Fg layerDef `json:"fg"`
	Bg layerDef `json:"bg,omitempty"`
}

type Room struct {
	Fg *LayerDefinition
	Bg *LayerDefinition
}

type Stage struct {
	Name    string
	Path    string
	GfxPath string
	DraPath string
	Rooms   []Room
}

func MakeStage(name string, roomFilePath string, gfxPath string, draPath string) (Stage, error) {
	tiledefs := make(map[string]TileDefinition, 0)
	tiledata := make(map[string][]uint16, 0)
	basePath := path.Dir(roomFilePath)
	makeLayerDefinition := func(layer layerDef) *LayerDefinition {
		return &LayerDefinition{
			Layout:  tiledata[layer.DataFilePath],
			TileDef: tiledefs[layer.TiledefFilePath],
			Rect: Rect{
				Left:   layer.Left,
				Top:    layer.Top,
				Right:  layer.Right,
				Bottom: layer.Bottom,
			},
			ZPriority:     uint16(layer.ZPriority),
			ScrollMode:    uint8(layer.ScrollMode),
			IsSaveRoom:    layer.IsSaveRoom,
			IsLoadingRoom: layer.IsLoadingRoom,
			UnkE:          byte(layer.UnkE),
			UnkF:          byte(layer.UnkF),
		}
	}

	jsonData, err := os.ReadFile(roomFilePath)
	if err != nil {
		return Stage{}, err
	}

	roomsDef := roomsDef{}
	err = json.Unmarshal(jsonData, &roomsDef)
	if err != nil {
		return Stage{}, err
	}

	rooms := make([]Room, len(roomsDef))
	for i, room := range roomsDef {
		var tiledef TileDefinition
		var data []byte
		if _, isFound := tiledefs[room.Fg.TiledefFilePath]; !isFound {
			filePath := path.Join(basePath, room.Fg.TiledefFilePath) + ".tiledef.json"
			if tiledef, err = readTiledef(filePath); err != nil {
				return Stage{}, err
			}
			tiledefs[room.Fg.TiledefFilePath] = tiledef
		}
		if _, isFound := tiledata[room.Fg.DataFilePath]; !isFound {
			filePath := path.Join(basePath, room.Fg.DataFilePath) + ".tilelayout.bin"
			if data, err = os.ReadFile(filePath); err != nil {
				return Stage{}, err
			}
			tiledata[room.Fg.DataFilePath] = readLayout(data, 0)
		}
		rooms[i].Fg = makeLayerDefinition(room.Fg)

		if len(room.Bg.TiledefFilePath) > 0 {
			if _, isFound := tiledefs[room.Bg.TiledefFilePath]; !isFound {
				filePath := path.Join(basePath, room.Bg.TiledefFilePath) + ".tiledef.json"
				if tiledef, err = readTiledef(filePath); err != nil {
					return Stage{}, err
				}
				tiledefs[room.Bg.TiledefFilePath] = tiledef
			}
			if _, isFound := tiledata[room.Bg.DataFilePath]; !isFound {
				filePath := path.Join(basePath, room.Bg.DataFilePath) + ".tilelayout.bin"
				if data, err = os.ReadFile(filePath); err != nil {
					return Stage{}, err
				}
				tiledata[room.Bg.DataFilePath] = readLayout(data, 0)
			}
			rooms[i].Bg = makeLayerDefinition(room.Bg)
		}
	}

	return Stage{
		Name:    name,
		Path:    basePath,
		GfxPath: gfxPath,
		DraPath: draPath,
		Rooms:   rooms,
	}, nil
}
