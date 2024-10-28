package layer

import (
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
)

func GetTilemapFileName(off psx.Addr) string {
	return fmt.Sprintf("tilemap_%05X.bin", off.Real(psx.RamStageBegin))
}

func GetTiledefFileName(off psx.Addr) string {
	return fmt.Sprintf("tiledef_%05X.json", off.Real(psx.RamStageBegin))
}

func GetTiledefIndicesFileName(off psx.Addr) string {
	return fmt.Sprintf("tiledef_%05X_tiles.bin", off.Real(psx.RamStageBegin))
}

func GetTiledefPagesFileName(off psx.Addr) string {
	return fmt.Sprintf("tiledef_%05X_pages.bin", off.Real(psx.RamStageBegin))
}

func GetTiledefClutsFileName(off psx.Addr) string {
	return fmt.Sprintf("tiledef_%05X_cluts.bin", off.Real(psx.RamStageBegin))
}

func GetTiledefCollisionsFileName(off psx.Addr) string {
	return fmt.Sprintf("tiledef_%05X_cols.bin", off.Real(psx.RamStageBegin))
}
