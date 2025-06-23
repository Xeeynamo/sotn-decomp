package layer

import (
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/tiledef"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"io"
)

func readAllTiledefs(r io.ReadSeeker, baseAddr psx.Addr, roomLayers []roomLayers) (map[psx.Addr]tiledef.TileDef, error) {
	processed := map[psx.Addr]tiledef.TileDef{}
	for _, rl := range roomLayers {
		if rl.fg != nil {
			if _, found := processed[rl.fg.Tiledef]; !found {
				td, _, err := tiledef.Read(r, rl.fg.Tiledef, baseAddr)
				if err != nil {
					return nil, fmt.Errorf("unable to read fg tiledef: %w", err)
				}
				processed[rl.fg.Tiledef] = td
			}
		}
		if rl.bg != nil {
			if _, found := processed[rl.bg.Tiledef]; !found {
				td, _, err := tiledef.Read(r, rl.bg.Tiledef, baseAddr)
				if err != nil {
					return nil, fmt.Errorf("unable to read fg tiledef: %w", err)
				}
				processed[rl.bg.Tiledef] = td
			}
		}
	}
	return processed, nil
}
