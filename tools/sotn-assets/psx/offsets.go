package psx

import (
	"encoding/binary"
	"fmt"
	"os"
)

type Addr uint32

const (
	RamNull       = Addr(0)
	RamGameBegin  = Addr(0x800A0000)
	RamStageBegin = Addr(0x80180000)
	RamStageEnd   = Addr(0x801C0000)
	RamGameEnd    = Addr(0x801F8000)
)

func (off Addr) Format(f fmt.State, c rune) {
	f.Write([]byte(fmt.Sprintf("0x%08X", uint32(off))))
}

func (off Addr) Real(begin Addr) int {
	return int(off - begin)
}

func (off Addr) Align4() Addr {
	if (off & 3) != 0 {
		return (off | 3) + 1
	}
	return off
}

func (off Addr) Sum(x int) Addr {
	return Addr(uint32(off) + uint32(x))
}

func (off Addr) DistanceTo(x Addr) int {
	return int(x - off)
}

func (off Addr) InRange(begin Addr, end Addr) bool {
	return off >= begin && off < end
}

func (off Addr) MoveFile(file *os.File, begin Addr) error {
	info, err := file.Stat()
	if err != nil {
		return fmt.Errorf("could not stat file: %w", err)
	}

	end := begin.Sum(int(info.Size()))
	if !off.InRange(begin, end) {
		err := fmt.Errorf("offset %s is outside the boundaries [%s, %s]", off, begin, end)
		panic(err)
		return err
	}

	fileOffset := int64(off - begin)
	file.Seek(fileOffset, 0)
	return nil
}

func GetAddr(data []byte) Addr {
	return Addr(binary.LittleEndian.Uint32(data))
}
