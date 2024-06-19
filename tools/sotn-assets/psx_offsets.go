package main

import (
	"fmt"
	"os"
	"slices"
)

type PsxOffset uint32

const (
	RamNull       = PsxOffset(0)
	RamStageBegin = PsxOffset(0x80180000)
	RamStageEnd   = PsxOffset(0x801C0000)
)

func (off PsxOffset) Format(f fmt.State, c rune) {
	f.Write([]byte(fmt.Sprintf("0x%08X", uint32(off))))
}

func (off PsxOffset) real() int {
	return int(off - RamStageBegin)
}

func (off PsxOffset) align4() PsxOffset {
	if (off & 3) != 0 {
		return (off | 3) + 1
	}
	return off
}

func (off PsxOffset) sum(x int) PsxOffset {
	return PsxOffset(uint32(off) + uint32(x))
}

func (off PsxOffset) distanceTo(x PsxOffset) int {
	return int(x - off)
}

func (off PsxOffset) valid() bool {
	return off >= RamStageBegin && off < RamStageEnd
}

func (off PsxOffset) moveFile(file *os.File) error {
	if !off.valid() {
		err := fmt.Errorf("offset %08X is outside the stage boundaries", off)
		panic(err)
		return err
	}

	stats, err := file.Stat()
	if err != nil {
		return err
	}

	fileOffset := int64(off - RamStageBegin)
	if fileOffset >= stats.Size() {
		return fmt.Errorf("offset %08X is outside the file boundaries", off)
	}

	file.Seek(fileOffset, 0)
	return nil
}

func sortUniqueOffsets(slice []PsxOffset) []PsxOffset {
	unique := map[PsxOffset]struct{}{}
	for _, v := range slice {
		unique[v] = struct{}{}
	}
	newSlice := make([]PsxOffset, 0, len(unique))
	for offset := range unique {
		newSlice = append(newSlice, offset)
	}

	slices.SortFunc(newSlice, func(a, b PsxOffset) int {
		if a < b {
			return -1
		} else if a > b {
			return 1
		}
		return 0
	})
	return newSlice
}
