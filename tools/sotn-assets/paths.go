package main

import "fmt"

func getTilemapFileName(off PsxOffset) string {
	return fmt.Sprintf("tilemap_%05X.bin", off.real())
}

func getTiledefFileName(off PsxOffset) string {
	return fmt.Sprintf("tiledef_%05X.json", off.real())
}

func getTiledefIndicesFileName(off PsxOffset) string {
	return fmt.Sprintf("tiledef_%05X_tiles.bin", off.real())
}

func getTiledefPagesFileName(off PsxOffset) string {
	return fmt.Sprintf("tiledef_%05X_pages.bin", off.real())
}

func getTiledefClutsFileName(off PsxOffset) string {
	return fmt.Sprintf("tiledef_%05X_cluts.bin", off.real())
}

func getTiledefCollisionsFileName(off PsxOffset) string {
	return fmt.Sprintf("tiledef_%05X_cols.bin", off.real())
}
