package layer

import (
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/datarange"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"io"
)

func readTilemap(r io.ReadSeeker, layer *layerDef) ([]byte, datarange.DataRange, error) {
	if err := layer.Data.MoveFile(r, psx.RamStageBegin); err != nil {
		return nil, datarange.DataRange{}, err
	}
	data := make([]byte, layer.tilemapFileSize())
	if _, err := r.Read(data); err != nil {
		return nil, datarange.DataRange{}, err
	}
	return data, datarange.FromAddr(layer.Data, len(data)), nil
}

func readAllTileMaps(r io.ReadSeeker, roomLayers []roomLayers) (map[psx.Addr][]byte, datarange.DataRange, error) {
	var ranges []datarange.DataRange
	processed := map[psx.Addr][]byte{}
	for _, rl := range roomLayers {
		if rl.fg != nil {
			if _, found := processed[rl.fg.Data]; !found {
				td, r, err := readTilemap(r, rl.fg)
				if err != nil {
					return nil, datarange.DataRange{}, fmt.Errorf("unable to read fg tilemap: %w", err)
				}
				processed[rl.fg.Data] = td
				ranges = append(ranges, r)
			}
		}
		if rl.bg != nil {
			if _, found := processed[rl.bg.Data]; !found {
				td, r, err := readTilemap(r, rl.bg)
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
