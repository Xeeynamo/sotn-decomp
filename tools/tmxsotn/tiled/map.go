package tiled

import (
	"encoding/xml"
	"os"
)

type Map struct {
	XMLName      xml.Name   `xml:"map"`
	Version      string     `xml:"version,attr"`
	Orientation  string     `xml:"orientation,attr"`
	RenderOrder  string     `xml:"renderorder,attr"`
	Width        int        `xml:"width,attr"`
	Height       int        `xml:"height,attr"`
	TileWidth    int        `xml:"tilewidth,attr"`
	TileHeight   int        `xml:"tileheight,attr"`
	NextObjectID uint32     `xml:"nextobjectid,attr"`
	Properties   []Property `xml:"properties>property"`
	Tilesets     []Tileset  `xml:"tileset"`
	Layers       []Layer    `xml:"layer"`
}

type Tileset struct {
	FirstGID   uint32 `xml:"firstgid,attr"`
	Name       string `xml:"name,attr"`
	TileWidth  int    `xml:"tilewidth,attr"`
	TileHeight int    `xml:"tileheight,attr"`
	Image      Image  `xml:"image"`
}

type Image struct {
	Source       string `xml:"source,attr"`
	Width        int    `xml:"width,attr"`
	Height       int    `xml:"height,attr"`
	Transparency string `xml:"trans,attr"`
}

type Layer struct {
	Name       string     `xml:"name,attr"`
	Width      int        `xml:"width,attr"`
	Height     int        `xml:"height,attr"`
	OffsetX    float32    `xml:"offsetx,attr"`
	OffsetY    float32    `xml:"offsety,attr"`
	Visible    int        `xml:"visible,attr"`
	Properties []Property `xml:"properties>property"`
	Data       LayerData  `xml:"data"`
}

type LayerData struct {
	Encoding string `xml:"encoding,attr"`
	Content  string `xml:",innerxml"`
}

func DecodeFromFile(fileName string) (Map, error) {
	data, err := os.ReadFile(fileName)
	if err != nil {
		return Map{}, err
	}

	return DecodeFromBytes(data)
}

func DecodeFromBytes(data []byte) (Map, error) {
	var tiledMap Map
	err := xml.Unmarshal(data, &tiledMap)
	return tiledMap, err
}

func (m Map) EncodeToBytes() ([]byte, error) {
	return xml.Marshal(m)
}

func (m Map) EncodeToFile(fileName string) error {
	data, err := m.EncodeToBytes()
	if err != nil {
		return err
	}

	return os.WriteFile(fileName, data, 0644)
}
