package psx

// this package is effectively no longer 'psx' exclusive, as it now also covers psp

import (
	"encoding/binary"
	"fmt"
	"io"
)

type Addr uint32

type Offsets struct {
	GameBegin  Addr
	StageBegin Addr
	StageEnd   Addr
	GameEnd    Addr
}

const RamNull = Addr(0)

var (
	ramPSX = Offsets{
		GameBegin:  Addr(0x800A0000),
		StageBegin: Addr(0x80180000),
		StageEnd:   Addr(0x801E0000),
		GameEnd:    Addr(0x801F8000),
	}
	ramPSP = Offsets{
		GameBegin:  Addr(0x090DCA00),
		StageBegin: Addr(0x09237700),
		StageEnd:   Addr(0x092A5500),
		GameEnd:    Addr(0x09800000),
	}
)

func (off Addr) Boundaries() Offsets {
	if off >= Addr(0x80000000) {
		return ramPSX
	}
	return ramPSP
}

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

func (off Addr) Align(alignment int) Addr {
	if (off % Addr(alignment)) != 0 {
		return (off | Addr(alignment-1)) + 1
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

func (off Addr) MoveFile(r io.ReadSeeker, begin Addr) error {
	end := off.Boundaries().GameEnd
	if !off.InRange(begin, end) {
		err := fmt.Errorf("offset %s is outside the boundaries [%s, %s]", off, begin, end)
		panic(err)
		return err
	}

	fileOffset := int64(off - begin)
	r.Seek(fileOffset, 0)
	return nil
}

func GetAddr(data []byte) Addr {
	return Addr(binary.LittleEndian.Uint32(data))
}

func ReadAddr(r io.Reader) Addr {
	b := make([]byte, 4)
	_, _ = r.Read(b)
	return GetAddr(b)
}
