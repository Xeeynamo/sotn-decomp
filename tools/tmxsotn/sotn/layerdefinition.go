package sotn

type LayerDefinition struct {
	Symbol        string
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

func parseLayout(data []byte) []uint16 {
	result := make([]uint16, len(data)/2)

	for i := 0; i < len(result); i++ {
		result[i] = uint16(data[i*2]) | uint16(data[i*2+1])<<8
	}

	return result
}
