package main

import (
	"encoding/binary"
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/datarange"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"os"
)

type tileDef struct {
	tiles []byte
	pages []byte
	cluts []byte
	cols  []byte
}

type tileDefPaths struct {
	Tiles      string `json:"tiles"`
	Pages      string `json:"pages"`
	Cluts      string `json:"cluts"`
	Collisions string `json:"collisions"`
}

func readTiledef(file *os.File, off psx.Addr) (tileDef, datarange.DataRange, error) {
	if err := off.MoveFile(file, psx.RamStageBegin); err != nil {
		return tileDef{}, datarange.DataRange{}, err
	}

	offsets := make([]psx.Addr, 4)
	if err := binary.Read(file, binary.LittleEndian, offsets); err != nil {
		return tileDef{}, datarange.DataRange{}, err
	}

	td := tileDef{
		tiles: make([]byte, offsets[1]-offsets[0]),
		pages: make([]byte, offsets[2]-offsets[1]),
		cluts: make([]byte, offsets[3]-offsets[2]),
		cols:  make([]byte, off-offsets[3]),
	}

	if err := offsets[0].MoveFile(file, psx.RamStageBegin); err != nil {
		return tileDef{}, datarange.DataRange{}, err
	}
	if _, err := file.Read(td.tiles); err != nil {
		return tileDef{}, datarange.DataRange{}, err
	}

	if err := offsets[1].MoveFile(file, psx.RamStageBegin); err != nil {
		return tileDef{}, datarange.DataRange{}, err
	}
	if _, err := file.Read(td.pages); err != nil {
		return tileDef{}, datarange.DataRange{}, err
	}

	if err := offsets[2].MoveFile(file, psx.RamStageBegin); err != nil {
		return tileDef{}, datarange.DataRange{}, err
	}
	if _, err := file.Read(td.cluts); err != nil {
		return tileDef{}, datarange.DataRange{}, err
	}

	if err := offsets[3].MoveFile(file, psx.RamStageBegin); err != nil {
		return tileDef{}, datarange.DataRange{}, err
	}
	if _, err := file.Read(td.cols); err != nil {
		return tileDef{}, datarange.DataRange{}, err
	}

	return td, datarange.New(offsets[0], off.Sum(0x10)), nil
}

func readAllTiledefs(file *os.File, roomLayers []roomLayers) (map[psx.Addr]tileDef, datarange.DataRange, error) {
	ranges := []datarange.DataRange{}
	processed := map[psx.Addr]tileDef{}
	for _, rl := range roomLayers {
		if rl.fg != nil {
			if _, found := processed[rl.fg.Tiledef]; !found {
				td, r, err := readTiledef(file, rl.fg.Tiledef)
				if err != nil {
					return nil, datarange.DataRange{}, fmt.Errorf("unable to read fg tiledef: %w", err)
				}
				processed[rl.fg.Tiledef] = td
				ranges = append(ranges, r)
			}
		}
		if rl.bg != nil {
			if _, found := processed[rl.bg.Tiledef]; !found {
				td, r, err := readTiledef(file, rl.bg.Tiledef)
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
