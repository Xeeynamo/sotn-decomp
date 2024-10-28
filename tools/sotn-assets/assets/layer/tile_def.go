package layer

import (
	"encoding/binary"
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/datarange"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"os"
)

type TileDef struct {
	Tiles []byte
	Pages []byte
	Cluts []byte
	Cols  []byte
}

type TileDefPaths struct {
	Tiles      string `json:"tiles"`
	Pages      string `json:"pages"`
	Cluts      string `json:"cluts"`
	Collisions string `json:"collisions"`
}

func ReadTiledef(file *os.File, off psx.Addr) (TileDef, datarange.DataRange, error) {
	if err := off.MoveFile(file, psx.RamStageBegin); err != nil {
		return TileDef{}, datarange.DataRange{}, err
	}

	offsets := make([]psx.Addr, 4)
	if err := binary.Read(file, binary.LittleEndian, offsets); err != nil {
		return TileDef{}, datarange.DataRange{}, err
	}

	td := TileDef{
		Tiles: make([]byte, offsets[1]-offsets[0]),
		Pages: make([]byte, offsets[2]-offsets[1]),
		Cluts: make([]byte, offsets[3]-offsets[2]),
		Cols:  make([]byte, off-offsets[3]),
	}

	if err := offsets[0].MoveFile(file, psx.RamStageBegin); err != nil {
		return TileDef{}, datarange.DataRange{}, err
	}
	if _, err := file.Read(td.Tiles); err != nil {
		return TileDef{}, datarange.DataRange{}, err
	}

	if err := offsets[1].MoveFile(file, psx.RamStageBegin); err != nil {
		return TileDef{}, datarange.DataRange{}, err
	}
	if _, err := file.Read(td.Pages); err != nil {
		return TileDef{}, datarange.DataRange{}, err
	}

	if err := offsets[2].MoveFile(file, psx.RamStageBegin); err != nil {
		return TileDef{}, datarange.DataRange{}, err
	}
	if _, err := file.Read(td.Cluts); err != nil {
		return TileDef{}, datarange.DataRange{}, err
	}

	if err := offsets[3].MoveFile(file, psx.RamStageBegin); err != nil {
		return TileDef{}, datarange.DataRange{}, err
	}
	if _, err := file.Read(td.Cols); err != nil {
		return TileDef{}, datarange.DataRange{}, err
	}

	return td, datarange.New(offsets[0], off.Sum(0x10)), nil
}

func ReadAllTiledefs(file *os.File, roomLayers []RoomLayers) (map[psx.Addr]TileDef, datarange.DataRange, error) {
	ranges := []datarange.DataRange{}
	processed := map[psx.Addr]TileDef{}
	for _, rl := range roomLayers {
		if rl.fg != nil {
			if _, found := processed[rl.fg.Tiledef]; !found {
				td, r, err := ReadTiledef(file, rl.fg.Tiledef)
				if err != nil {
					return nil, datarange.DataRange{}, fmt.Errorf("unable to read fg tiledef: %w", err)
				}
				processed[rl.fg.Tiledef] = td
				ranges = append(ranges, r)
			}
		}
		if rl.bg != nil {
			if _, found := processed[rl.bg.Tiledef]; !found {
				td, r, err := ReadTiledef(file, rl.bg.Tiledef)
				if err != nil {
					return nil, datarange.DataRange{}, fmt.Errorf("unable to read fg tiledef: %w", err)
				}
				processed[rl.bg.Tiledef] = td
				ranges = append(ranges, r)
			}
		}
	}
	return processed, datarange.MergeDataRanges(ranges), nil
}
