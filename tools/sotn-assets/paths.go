package main

import (
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
)

func getTilemapFileName(off psx.Addr) string {
	return fmt.Sprintf("tilemap_%05X.bin", off.Real(psx.RamStageBegin))
}

func getTiledefFileName(off psx.Addr) string {
	return fmt.Sprintf("tiledef_%05X.json", off.Real(psx.RamStageBegin))
}

func getTiledefIndicesFileName(off psx.Addr) string {
	return fmt.Sprintf("tiledef_%05X_tiles.bin", off.Real(psx.RamStageBegin))
}

func getTiledefPagesFileName(off psx.Addr) string {
	return fmt.Sprintf("tiledef_%05X_pages.bin", off.Real(psx.RamStageBegin))
}

func getTiledefClutsFileName(off psx.Addr) string {
	return fmt.Sprintf("tiledef_%05X_cluts.bin", off.Real(psx.RamStageBegin))
}

func getTiledefCollisionsFileName(off psx.Addr) string {
	return fmt.Sprintf("tiledef_%05X_cols.bin", off.Real(psx.RamStageBegin))
}
