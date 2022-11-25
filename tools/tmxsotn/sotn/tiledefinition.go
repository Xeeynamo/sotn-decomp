package sotn

type TileDefinition struct {
	Pages      []byte
	Tiles      []byte
	Palettes   []byte
	Collisions []byte
}

func readTileDefinition(data []byte, offset int) TileDefinition {
	const Length = 0x1000
	offPages := asStageOffset(data, offset+0)
	offTiles := asStageOffset(data, offset+4)
	offPalettes := asStageOffset(data, offset+8)
	offCollisions := asStageOffset(data, offset+12)
	return TileDefinition{
		Pages:      data[offPages : offPages+Length],
		Tiles:      data[offTiles : offTiles+Length],
		Palettes:   data[offPalettes : offPalettes+Length],
		Collisions: data[offCollisions : offCollisions+Length],
	}
}
