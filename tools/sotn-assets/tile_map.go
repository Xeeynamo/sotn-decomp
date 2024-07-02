package main

import (
	"fmt"
	"os"
)

func readTilemap(file *os.File, layer *layer) ([]byte, dataRange, error) {
	if err := layer.Data.moveFile(file); err != nil {
		return nil, dataRange{}, err
	}
	data := make([]byte, layer.tilemapFileSize())
	if _, err := file.Read(data); err != nil {
		return nil, dataRange{}, err
	}
	return data, dataRange{
		begin: layer.Data,
		end:   layer.Data.sum(len(data)),
	}, nil
}

func readAllTileMaps(file *os.File, roomLayers []roomLayers) (map[PsxOffset][]byte, dataRange, error) {
	ranges := []dataRange{}
	processed := map[PsxOffset][]byte{}
	for _, rl := range roomLayers {
		if rl.fg != nil {
			if _, found := processed[rl.fg.Data]; !found {
				td, r, err := readTilemap(file, rl.fg)
				if err != nil {
					return nil, dataRange{}, fmt.Errorf("unable to read fg tilemap: %w", err)
				}
				processed[rl.fg.Data] = td
				ranges = append(ranges, r)
			}
		}
		if rl.bg != nil {
			if _, found := processed[rl.bg.Data]; !found {
				td, r, err := readTilemap(file, rl.bg)
				if err != nil {
					return nil, dataRange{}, fmt.Errorf("unable to read fg tilemap: %w", err)
				}
				processed[rl.bg.Data] = td
				ranges = append(ranges, r)
			}
		}
	}
	return processed, mergeDataRanges(ranges), nil
}
