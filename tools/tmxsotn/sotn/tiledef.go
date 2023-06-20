package sotn

import (
	"encoding/json"
	"os"
	"path"
)

type TileDefinition struct {
	Pages      []byte
	Tiles      []byte
	Palettes   []byte
	Collisions []byte
}

type tiledefConfig struct {
	GfxPage   string `json:"gfxPage"`
	GfxIndex  string `json:"gfxIndex"`
	Clut      string `json:"clut"`
	Collision string `json:"collision"`
}

func readTiledef(fileName string) (TileDefinition, error) {
	tiledef := TileDefinition{}
	basePath := path.Dir(fileName)

	jsonData, err := os.ReadFile(fileName)
	if err != nil {
		return tiledef, err
	}

	cfg := tiledefConfig{}
	err = json.Unmarshal(jsonData, &cfg)
	if err != nil {
		return tiledef, err
	}

	dataTiles, err := os.ReadFile(path.Join(basePath, cfg.GfxIndex) + ".bin")
	if err != nil {
		return tiledef, err
	}

	dataPages, err := os.ReadFile(path.Join(basePath, cfg.GfxPage) + ".bin")
	if err != nil {
		return tiledef, err
	}

	dataClut, err := os.ReadFile(path.Join(basePath, cfg.Clut) + ".bin")
	if err != nil {
		return tiledef, err
	}

	dataCollision, err := os.ReadFile(path.Join(basePath, cfg.Collision) + ".bin")
	if err != nil {
		return tiledef, err
	}

	return TileDefinition{
		Tiles:      dataTiles,
		Pages:      dataPages,
		Palettes:   dataClut,
		Collisions: dataCollision,
	}, err
}
