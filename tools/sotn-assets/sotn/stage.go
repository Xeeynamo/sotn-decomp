package sotn

import (
	"encoding/binary"
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"io"
)

type StageHeader struct {
	FnUpdate              psx.Addr
	FnHitDetection        psx.Addr
	FnUpdateRoomPos       psx.Addr
	FnInitRoomEntities    psx.Addr
	Rooms                 psx.Addr // ✅
	Sprites               psx.Addr // ✅
	Cluts                 psx.Addr // 🫥
	Layouts               psx.Addr // ✅
	Layers                psx.Addr // ✅
	Graphics              psx.Addr // 🫥 WIP
	FnUpdateStageEntities psx.Addr
}

func ReadStageHeader(r io.ReadSeeker) (StageHeader, error) {
	var header StageHeader
	if _, err := r.Seek(0, io.SeekStart); err != nil {
		return header, fmt.Errorf("failed to seek to stage header: %w", err)
	}
	if err := binary.Read(r, binary.LittleEndian, &header); err != nil {
		return header, fmt.Errorf("failed to read stage header: %w", err)
	}
	return header, nil
}
