package sotn

import (
	"encoding/binary"
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

func asStageOffset(data []byte, offset int) int {
	raw := binary.LittleEndian.Uint32(data[offset : offset+4])
	if raw < 0x80000000 {
		return int(raw)
	}

	return int(raw - 0x80180000)
}

func ReadStage(data []byte) LayerBucket {
	layerOffset := asStageOffset(data, 0x20)
	return readLayerDefinitions(data, layerOffset, 10)
}
