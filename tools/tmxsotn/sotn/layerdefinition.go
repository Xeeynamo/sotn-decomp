package sotn

type LayerDefinition struct {
	Layout        []uint16
	TileDef       TileDefinition
	Rect          Rect
	ScrollMode    uint8
	ZPriority     uint16
	IsSaveRoom    bool
	IsLoadingRoom bool
	UnkE          byte
	UnkF          byte
}

type layerDef struct {
	DataFilePath    string `json:"data"`
	TiledefFilePath string `json:"tiledef"`
	Left            int    `json:"left"`
	Top             int    `json:"top"`
	Right           int    `json:"right"`
	Bottom          int    `json:"bottom"`
	ScrollMode      int    `json:"scrollMode"`
	IsSaveRoom      bool   `json:"isSaveRoom"`
	IsLoadingRoom   bool   `json:"isLoadingRoom"`
	ZPriority       int    `json:"zPriority"`
	UnkE            int    `json:"unkE"`
	UnkF            int    `json:"unkF"`
}

func (l *LayerDefinition) Width() int {
	return l.Rect.Width()
}
func (l *LayerDefinition) Height() int {
	return l.Rect.Height()
}

func readLayout(data []byte, offset int) []uint16 {
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
