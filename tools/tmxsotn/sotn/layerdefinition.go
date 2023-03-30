package sotn

import (
	"encoding/binary"
)

type LayerDefinition struct {
	Layout     []uint16
	TileDef    TileDefinition
	Rect       Rect
	ScrollMode uint8
	ZPriority  uint16
	UnkE       uint16
}

type LayerBucket struct {
	Layers []LayerDefinition
	Rooms  []RoomLayers
}

type RoomLayers struct {
	Foreground int
	Background int
}

func (l *LayerDefinition) Width() int {
	return l.Rect.Width()
}
func (l *LayerDefinition) Height() int {
	return l.Rect.Height()
}

func readLayerDefinitions(data []byte, offset int, nRooms int) LayerBucket {
	bucket := LayerBucket{
		Layers: make([]LayerDefinition, 0),
		Rooms:  make([]RoomLayers, 0),
	}

	offsets := make(map[int]int, 0)
	for i := 0; i < nRooms; i++ {
		offBg := asStageOffset(data, offset+i*4+4)
		bgIdx, found := offsets[offBg]
		if !found {
			bgIdx = len(bucket.Layers)
			bucket.Layers = append(bucket.Layers, readLayerDefinition(data, offBg))
		}

		offFg := asStageOffset(data, offset+i*4+0)
		fgIdx, found := offsets[offFg]
		if !found {
			fgIdx = len(bucket.Layers)
			bucket.Layers = append(bucket.Layers, readLayerDefinition(data, offFg))
		}

		bucket.Rooms = append(bucket.Rooms, RoomLayers{
			Foreground: fgIdx,
			Background: bgIdx,
		})
	}

	return bucket
}

func readLayerDefinition(data []byte, offset int) LayerDefinition {
	offLayout := asStageOffset(data, offset+0)
	offTileDef := asStageOffset(data, offset+4)
	rectData := binary.LittleEndian.Uint32(data[offset+8:])
	if offLayout == 0 || offTileDef == 0 || rectData == 0 {
		return LayerDefinition{}
	}

	rect := Rect{
		Left:   int((rectData >> 0) & 63),
		Top:    int((rectData >> 6) & 63),
		Right:  int((rectData >> 12) & 63),
		Bottom: int((rectData >> 18) & 63),
	}

	return LayerDefinition{
		Layout:     readLayout(data, offLayout, rect),
		TileDef:    readTileDefinition(data, offTileDef),
		Rect:       rect,
		ScrollMode: uint8(rectData >> 24),
		ZPriority:  binary.LittleEndian.Uint16(data[offset+12:]),
		UnkE:       binary.LittleEndian.Uint16(data[offset+14:]),
	}
}

func readLayout(data []byte, offset int, rect Rect) []uint16 {
	w := 16
	h := 16
	count := w * h
	layout := make([]uint16, count)

	for i := 0; i < count; i++ {
		ch1 := data[offset+i*2+0]
		ch2 := data[offset+i*2+1]
		layout[i] = uint16(ch1) | (uint16(ch2) << 8)
	}

	return layout
}
