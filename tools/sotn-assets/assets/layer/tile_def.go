package layer

import (
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/tiledef"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/datarange"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"io"
)

func readAllTiledefs(r io.ReadSeeker, baseAddr psx.Addr, roomLayers []roomLayers) (map[psx.Addr]tiledef.TileDef, datarange.DataRange, error) {
	var ranges []datarange.DataRange
	processed := map[psx.Addr]tiledef.TileDef{}
	for _, rl := range roomLayers {
		if rl.fg != nil {
			if _, found := processed[rl.fg.Tiledef]; !found {
				td, r, err := tiledef.Read(r, rl.fg.Tiledef, baseAddr)
				if err != nil {
					return nil, datarange.DataRange{}, fmt.Errorf("unable to read fg tiledef: %w", err)
				}
				processed[rl.fg.Tiledef] = td
				ranges = append(ranges, r)
			}
		}
		if rl.bg != nil {
			if _, found := processed[rl.bg.Tiledef]; !found {
				td, r, err := tiledef.Read(r, rl.bg.Tiledef, baseAddr)
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
