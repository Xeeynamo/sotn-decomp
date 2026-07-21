package spriteset

import (
	"encoding/binary"
	"fmt"
	"io"

	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/datarange"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/sotn"
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

// isPlayerSprite reports whether a group uses the special single-sprite format
// {flags|0x8000, X, Y, 0} (e.g. Maria/Richter) rather than a count + full sprites.
func isPlayerSprite(group spriteParts) bool {
	return len(group) == 1 && group[0].Flags >= 0x8000
}

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

	alignment := 4
	if sotn.GetPlatform() == sotn.PlatformPSP {
		alignment = 8
	}

	if count >= 0x8000 {
		// Special single-sprite format (e.g. Maria/Richter):
		// {flags|0x8000, X, Y, W} — 4 s16 total, not a count + full sprites.
		// The value read as count is actually the Flags field.
		var rest [3]int16
		if err := binary.Read(r, binary.LittleEndian, &rest); err != nil {
			return nil, datarange.DataRange{}, err
		}
		s := sprite{
			Flags: count, // includes the 0x8000 bit
			X:     rest[0],
			Y:     rest[1],
			Width: uint16(rest[2]), // Height..Bottom stay 0
		}
		return []sprite{s}, datarange.FromAlignedAddr(addr, 8, alignment), nil
	}

	sprites := make([]sprite, count)
	if err := binary.Read(r, binary.LittleEndian, sprites); err != nil {
		return nil, datarange.DataRange{}, err
	}
	return sprites, datarange.FromAlignedAddr(addr, 4+0x16*int(count), alignment), nil
}
