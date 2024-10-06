package main

import (
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/datarange"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"os"
)

func readTilemap(file *os.File, layer *layer) ([]byte, datarange.DataRange, error) {
	if err := layer.Data.MoveFile(file, psx.RamStageBegin); err != nil {
		return nil, datarange.DataRange{}, err
	}
	data := make([]byte, layer.tilemapFileSize())
	if _, err := file.Read(data); err != nil {
		return nil, datarange.DataRange{}, err
	}
	return data, datarange.FromAddr(layer.Data, len(data)), nil
}

func readAllTileMaps(file *os.File, roomLayers []roomLayers) (map[psx.Addr][]byte, datarange.DataRange, error) {
	ranges := []datarange.DataRange{}
	processed := map[psx.Addr][]byte{}
	for _, rl := range roomLayers {
		if rl.fg != nil {
			if _, found := processed[rl.fg.Data]; !found {
				td, r, err := readTilemap(file, rl.fg)
				if err != nil {
					return nil, datarange.DataRange{}, fmt.Errorf("unable to read fg tilemap: %w", err)
				}
				processed[rl.fg.Data] = td
				ranges = append(ranges, r)
			}
		}
		if rl.bg != nil {
			if _, found := processed[rl.bg.Data]; !found {
				td, r, err := readTilemap(file, rl.bg)
				if err != nil {
					return nil, datarange.DataRange{}, fmt.Errorf("unable to read fg tilemap: %w", err)
				}
				processed[rl.bg.Data] = td
				ranges = append(ranges, r)
			}
		}
	}
	return processed, datarange.MergeDataRanges(ranges), nil
}
