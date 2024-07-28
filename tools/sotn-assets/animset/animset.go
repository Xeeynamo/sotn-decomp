package animset

import (
	"encoding/binary"
	"encoding/json"
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"os"
	"path/filepath"
)

type AnimFrame struct {
	Flags   int16 `json:"flags"`
	Offsetx int16 `json:"offsetx"`
	Offsety int16 `json:"offsety"`
	Width   int16 `json:"width"`
	Height  int16 `json:"height"`
	Clut    int16 `json:"clut"`
	Tileset int16 `json:"tileset"`
	Left    int16 `json:"left"`
	Top     int16 `json:"top"`
	Right   int16 `json:"right"`
	Bottom  int16 `json:"bottom"`
}

func parseAnimFrame(data []byte) AnimFrame {
	return AnimFrame{
		Flags:   int16(binary.LittleEndian.Uint16(data[0:])),
		Offsetx: int16(binary.LittleEndian.Uint16(data[2:])),
		Offsety: int16(binary.LittleEndian.Uint16(data[4:])),
		Width:   int16(binary.LittleEndian.Uint16(data[6:])),
		Height:  int16(binary.LittleEndian.Uint16(data[8:])),
		Clut:    int16(binary.LittleEndian.Uint16(data[10:])),
		Tileset: int16(binary.LittleEndian.Uint16(data[12:])),
		Left:    int16(binary.LittleEndian.Uint16(data[14:])),
		Top:     int16(binary.LittleEndian.Uint16(data[16:])),
		Right:   int16(binary.LittleEndian.Uint16(data[18:])),
		Bottom:  int16(binary.LittleEndian.Uint16(data[20:])),
	}
}

func parse(baseAddr psx.Addr, data []byte, start, end int) []*[]AnimFrame {
	var offsets []psx.Addr
	endAddr := baseAddr.Sum(end)
	for i := start; i < end; i += 4 {
		addr := psx.GetAddr(data[i:])
		if addr != psx.RamNull && !addr.InRange(baseAddr, endAddr) {
			break
		}
		offsets = append(offsets, addr)
	}

	set := make([]*[]AnimFrame, 0)
	for _, addr := range offsets {
		if addr == psx.RamNull {
			set = append(set, nil)
			continue
		}
		var frames []AnimFrame
		cur := data[addr-baseAddr:]
		nFrames := int(binary.LittleEndian.Uint16(cur))
		cur = cur[2:]
		for i := 0; i < nFrames; i++ {
			frames = append(frames, parseAnimFrame(cur))
			cur = cur[22:]
		}
		set = append(set, &frames)
	}
	return set
}

func Extract(path string, addr psx.Addr, data []byte, start, end int) error {
	set := parse(addr, data, start, end)
	content, err := json.MarshalIndent(set, "", "  ")
	if err != nil {
		return err
	}

	dir := filepath.Dir(path)
	if err := os.MkdirAll(dir, 0755); err != nil {
		fmt.Printf("failed to create directory %s: %v\n", dir, err)
		return err
	}
	return os.WriteFile(path, content, 0644)
}
