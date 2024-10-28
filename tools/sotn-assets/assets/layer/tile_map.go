package layer

import (
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/datarange"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"os"
)

func ReadTilemap(file *os.File, layer *Layer) ([]byte, datarange.DataRange, error) {
	if err := layer.Data.MoveFile(file, psx.RamStageBegin); err != nil {
		return nil, datarange.DataRange{}, err
	}
	data := make([]byte, layer.TilemapFileSize())
	if _, err := file.Read(data); err != nil {
		return nil, datarange.DataRange{}, err
	}
	return data, datarange.FromAddr(layer.Data, len(data)), nil
}

func ReadAllTileMaps(file *os.File, roomLayers []RoomLayers) (map[psx.Addr][]byte, datarange.DataRange, error) {
	ranges := []datarange.DataRange{}
	processed := map[psx.Addr][]byte{}
	for _, rl := range roomLayers {
		if rl.fg != nil {
			if _, found := processed[rl.fg.Data]; !found {
				td, r, err := ReadTilemap(file, rl.fg)
				if err != nil {
					return nil, datarange.DataRange{}, fmt.Errorf("unable to read fg tilemap: %w", err)
				}
				processed[rl.fg.Data] = td
				ranges = append(ranges, r)
			}
		}
		if rl.bg != nil {
			if _, found := processed[rl.bg.Data]; !found {
				td, r, err := ReadTilemap(file, rl.bg)
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
