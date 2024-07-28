package main

import (
	"encoding/binary"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"os"
)

type room struct {
	Left           int8 `json:"left"`
	Top            int8 `json:"top"`
	Right          int8 `json:"right"`
	Bottom         int8 `json:"bottom"`
	LayerID        int8 `json:"layerId"`
	TileDefID      int8 `json:"tileDefId"`
	EntityGfxID    int8 `json:"entityGfxId"`
	EntityLayoutID int8 `json:"entityLayoutId"`
}

func (r room) isTerminator() bool {
	return r.Left == 0x40
}

func readRooms(file *os.File, off psx.Addr) ([]room, dataRange, error) {
	if off == 0 {
		return nil, dataRange{}, nil
	}
	if err := off.MoveFile(file, psx.RamStageBegin); err != nil {
		return nil, dataRange{}, err
	}

	rooms := []room{}
	for {
		var room room
		if err := binary.Read(file, binary.LittleEndian, &room); err != nil {
			return nil, dataRange{}, err
		}
		if room.isTerminator() {
			break
		}
		rooms = append(rooms, room)
	}
	return rooms, dataRange{
		begin: off,
		end:   off.Sum(len(rooms)*8 + 4),
	}, nil
}
