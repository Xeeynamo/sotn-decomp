package main

import (
	"encoding/binary"
	"encoding/json"
	"os"
	"slices"
)

type layer struct {
	Data       PsxOffset
	Tiledef    PsxOffset
	PackedInfo uint32
	ZPriority  uint16
	UnkE       uint8
	UnkF       uint8
}

type layerUnpacked struct {
	Data          string `json:"data"`
	Tiledef       string `json:"tiledef"`
	Left          int    `json:"left"`
	Top           int    `json:"top"`
	Right         int    `json:"right"`
	Bottom        int    `json:"bottom"`
	ScrollMode    int    `json:"scrollMode"`
	IsSaveRoom    bool   `json:"isSaveRoom"`
	IsLoadingRoom bool   `json:"isLoadingRoom"`
	UnusedFlag    bool   `json:"unusedFlag"`
	ZPriority     int    `json:"zPriority"`
	UnkE          int    `json:"unkE"`
	UnkF          int    `json:"unkF"`
}

type roomLayers struct {
	fg *layer
	bg *layer
}

func (l *layer) tilemapFileSize() int {
	sx := int((l.PackedInfo >> 0) & 0x3F)
	sy := int((l.PackedInfo >> 6) & 0x3F)
	ex := int((l.PackedInfo >> 12) & 0x3F)
	ey := int((l.PackedInfo >> 18) & 0x3F)
	w := ex - sx + 1
	h := ey - sy + 1
	return w * h * 512
}

func (l *layer) unpack() layerUnpacked {
	return layerUnpacked{
		Data:          getTilemapFileName(l.Data),
		Tiledef:       getTiledefFileName(l.Tiledef),
		Left:          int((l.PackedInfo >> 0) & 0x3F),
		Top:           int((l.PackedInfo >> 6) & 0x3F),
		Right:         int((l.PackedInfo >> 12) & 0x3F),
		Bottom:        int((l.PackedInfo >> 18) & 0x3F),
		ScrollMode:    int((l.PackedInfo >> 24) & 0x1F),
		IsSaveRoom:    int((l.PackedInfo>>24)&0x20) != 0,
		IsLoadingRoom: int((l.PackedInfo>>24)&0x40) != 0,
		UnusedFlag:    int((l.PackedInfo>>24)&0x80) != 0,
		ZPriority:     int(l.ZPriority),
		UnkE:          int(l.UnkE),
		UnkF:          int(l.UnkF),
	}
}

func (r roomLayers) MarshalJSON() ([]byte, error) {
	m := map[string]interface{}{}
	if r.fg != nil {
		m["fg"] = r.fg.unpack()
	}
	if r.bg != nil {
		m["bg"] = r.bg.unpack()
	}
	return json.Marshal(m)
}

func readLayers(file *os.File, off PsxOffset) ([]roomLayers, dataRange, error) {
	if off == 0 {
		return nil, dataRange{}, nil
	}
	if err := off.moveFile(file); err != nil {
		return nil, dataRange{}, err
	}

	// when the data starts to no longer makes sense, we can assume we reached the end of the array
	layerOffsets := []PsxOffset{}
	layersOff := make([]PsxOffset, 2)
	for {
		if err := binary.Read(file, binary.LittleEndian, layersOff); err != nil {
			return nil, dataRange{}, err
		}
		if layersOff[0] <= RamStageBegin || layersOff[0] >= off ||
			layersOff[1] <= RamStageBegin || layersOff[1] >= off {
			break
		}
		layerOffsets = append(layerOffsets, layersOff...)
	}

	// Creates a map of layers, so we can re-use them when a layer is used by multiple rooms
	pool := map[PsxOffset]*layer{}
	pool[PsxOffset(0)] = nil
	for _, layerOffset := range layerOffsets {
		if _, exists := pool[layerOffset]; exists {
			continue
		}

		if err := layerOffset.moveFile(file); err != nil {
			return nil, dataRange{}, err
		}
		var l layer
		if err := binary.Read(file, binary.LittleEndian, &l); err != nil {
			return nil, dataRange{}, err
		}
		if l.Data != RamNull || l.Tiledef != RamNull || l.PackedInfo != 0 {
			pool[layerOffset] = &l
		} else {
			pool[layerOffset] = nil
		}
	}

	// creates the real array with all the layers mapped
	count := len(layerOffsets) >> 1
	roomsLayers := make([]roomLayers, count)
	for i := 0; i < count; i++ {
		roomsLayers[i].fg = pool[layerOffsets[i*2+0]]
		roomsLayers[i].bg = pool[layerOffsets[i*2+1]]
	}
	return roomsLayers, dataRange{
		begin: slices.Min(layerOffsets),
		end:   off.sum(count * 8),
	}, nil
}
