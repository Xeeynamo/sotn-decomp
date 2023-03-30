package sotn

import (
	"encoding/json"
	"io/ioutil"
	"os"
	"path"
	"strings"
)

type tiledefConfig struct {
	GfxPage   string `json:"gfxPage"`
	GfxIndex  string `json:"gfxIndex"`
	Clut      string `json:"clut"`
	Collision string `json:"collision"`
}

func MakeLayerBucket(
	name string,
	outPath string,
	draPath string,
	gfxPath string,
	stagePath string,
	tiledefFileName string,
	layoutFileName string) (LayerBucket, error) {
	bucket := LayerBucket{
		Layers: make([]LayerDefinition, 0),
	}

	tiledef, err := ReadTileDefinitionFromJson(stagePath, tiledefFileName)
	if err != nil {
		return bucket, err
	}

	layout, err := ReadLayout(layoutFileName)
	if err != nil {
		return bucket, err
	}

	layer := LayerDefinition{
		TileDef: tiledef,
		Layout:  layout,
		Rect: Rect{
			Left:   0,
			Top:    0,
			Right:  1,
			Bottom: 1,
		},
	}
	bucket.Layers = append(bucket.Layers, layer)
	return bucket, nil
}

func ReadLayout(fileName string) ([]uint16, error) {
	raw, err := os.ReadFile(fileName)
	if err != nil {
		return nil, err
	}

	tileMap := make([]uint16, len(raw)/2)
	for i := 0; i < len(tileMap); i++ {
		tileMap[i] = uint16(raw[i*2+0]) | (uint16(raw[i*2+1]) << 8)
	}
	return tileMap, err
}

func ReadTileDefinitionFromJson(
	stagePath string, fileName string) (TileDefinition, error) {
	tiledef := TileDefinition{}

	f, err := os.Open(fileName)
	if err != nil {
		return tiledef, err
	}

	jsonData, err := ioutil.ReadAll(f)
	if err != nil {
		return tiledef, err
	}

	cfg := tiledefConfig{}
	if err = json.Unmarshal(jsonData, &cfg); err != nil {
		return tiledef, err
	}

	raw, err := os.ReadFile(path.Join(stagePath, cfg.GfxPage) + ".bin")
	if err != nil {
		return tiledef, err
	}
	tiledef.Pages = raw

	raw, err = os.ReadFile(path.Join(stagePath, cfg.GfxIndex) + ".bin")
	if err != nil {
		return tiledef, err
	}
	tiledef.Tiles = raw

	raw, err = os.ReadFile(path.Join(stagePath, cfg.Clut) + ".bin")
	if err != nil {
		return tiledef, err
	}
	tiledef.Palettes = raw

	raw, err = os.ReadFile(path.Join(stagePath, cfg.Collision) + ".bin")
	if err != nil {
		return tiledef, err
	}
	tiledef.Collisions = raw

	return tiledef, err
}

func GetStageTileset(name string, gfxPath string) ([]string, error) {
	fileNames := make([]string, 0)

	dir, err := os.ReadDir(gfxPath)
	if err != nil {
		return nil, err
	}

	for _, v := range dir {
		if v.IsDir() {
			continue
		}

		fileName := v.Name()
		if strings.HasPrefix(fileName, name) &&
			strings.HasSuffix(fileName, ".png") &&
			!strings.Contains(fileName, "clut") {
			fileNames = append(fileNames, path.Join(gfxPath, fileName))
		}
	}

	return fileNames, nil
}
