package spriteset

import (
	"encoding/binary"
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/datarange"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/sotn"
	"io"
)

type sprite struct {
	Flags   uint16 `json:"flags"`
	X       int16  `json:"x"`
	Y       int16  `json:"y"`
	Width   uint16 `json:"width"`
	Height  uint16 `json:"height"`
	Clut    uint16 `json:"clut"`
	Tileset uint16 `json:"tileset"`
	Left    uint16 `json:"left"`
	Top     uint16 `json:"top"`
	Right   uint16 `json:"right"`
	Bottom  uint16 `json:"bottom"`
}
type spriteParts []sprite

func readSpriteParts(r io.ReadSeeker, baseAddr, addr psx.Addr) (spriteParts, datarange.DataRange, error) {
	if err := addr.MoveFile(r, baseAddr); err != nil {
		return nil, datarange.DataRange{}, fmt.Errorf("invalid sprites: %w", err)
	}

	var count uint16
	if err := binary.Read(r, binary.LittleEndian, &count); err != nil {
		if err == io.EOF {
			// special case for PSP, where an empty sprite part will fall to the BSS section
			return []sprite{}, datarange.DataRange{}, nil
		}
		return nil, datarange.DataRange{}, err
	}
	sprites := make([]sprite, count)
	if err := binary.Read(r, binary.LittleEndian, sprites); err != nil {
		return nil, datarange.DataRange{}, err
	}
	alignment := 4
	if sotn.GetPlatform() == sotn.PlatformPSP {
		alignment = 8
	}
	return sprites, datarange.FromAlignedAddr(addr, 4+0x16*int(count), alignment), nil
}
