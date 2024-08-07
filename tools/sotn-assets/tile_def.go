package main

import (
	"encoding/binary"
	"fmt"
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

func readTiledef(file *os.File, off PsxOffset) (tileDef, dataRange, error) {
	if err := off.moveFile(file); err != nil {
		return tileDef{}, dataRange{}, err
	}

	offsets := make([]PsxOffset, 4)
	if err := binary.Read(file, binary.LittleEndian, offsets); err != nil {
		return tileDef{}, dataRange{}, err
	}

	td := tileDef{
		tiles: make([]byte, offsets[1]-offsets[0]),
		pages: make([]byte, offsets[2]-offsets[1]),
		cluts: make([]byte, offsets[3]-offsets[2]),
		cols:  make([]byte, off-offsets[3]),
	}

	if err := offsets[0].moveFile(file); err != nil {
		return tileDef{}, dataRange{}, err
	}
	if _, err := file.Read(td.tiles); err != nil {
		return tileDef{}, dataRange{}, err
	}

	if err := offsets[1].moveFile(file); err != nil {
		return tileDef{}, dataRange{}, err
	}
	if _, err := file.Read(td.pages); err != nil {
		return tileDef{}, dataRange{}, err
	}

	if err := offsets[2].moveFile(file); err != nil {
		return tileDef{}, dataRange{}, err
	}
	if _, err := file.Read(td.cluts); err != nil {
		return tileDef{}, dataRange{}, err
	}

	if err := offsets[3].moveFile(file); err != nil {
		return tileDef{}, dataRange{}, err
	}
	if _, err := file.Read(td.cols); err != nil {
		return tileDef{}, dataRange{}, err
	}

	return td, dataRange{
		begin: offsets[0],
		end:   off.sum(0x10),
	}, nil
}

func readAllTiledefs(file *os.File, roomLayers []roomLayers, offBegin PsxOffset) (map[PsxOffset]tileDef, dataRange, error) {
	ranges := []dataRange{}
	processed := map[PsxOffset]tileDef{}
	for _, rl := range roomLayers {
		if rl.fg != nil {
			if _, found := processed[rl.fg.Tiledef]; !found {
				td, r, err := readTiledef(file, rl.fg.Tiledef)
				if err != nil {
					return nil, dataRange{}, fmt.Errorf("unable to read fg tiledef: %w", err)
				}
				processed[rl.fg.Tiledef] = td
				ranges = append(ranges, r)
			}
		}
		if rl.bg != nil {
			if _, found := processed[rl.bg.Tiledef]; !found {
				td, r, err := readTiledef(file, rl.bg.Tiledef)
				if err != nil {
					return nil, dataRange{}, fmt.Errorf("unable to read fg tiledef: %w", err)
				}
				processed[rl.bg.Tiledef] = td
				ranges = append(ranges, r)
			}
		}
	}

	// In CEN there is an unused tiledef at the beginning
	for offBegin < getDataRangeBegin(ranges) {
		offset := getDataRangeBegin(ranges).sum(-0x10)
		td, r, err := readTiledef(file, offset)
		if err != nil {
			return nil, dataRange{}, err
		}
		processed[offset] = td
		ranges = append(ranges, r)
	}

	// In MAD there is an unused tiledef between two used tiledefs
	// search for gaps and fill them with the missing tiledef
	sortDataRanges(ranges)
	for i := 0; i < len(ranges)-1; i++ {
		if ranges[i].end == ranges[i+1].begin {
			continue
		}
		offset := ranges[i+1].begin.sum(-0x10)
		td, r, err := readTiledef(file, offset)
		if err != nil {
			return nil, dataRange{}, err
		}
		processed[offset] = td
		ranges = append(ranges, r)
		sortDataRanges(ranges)
	}

	return processed, mergeDataRanges(ranges), nil
}
