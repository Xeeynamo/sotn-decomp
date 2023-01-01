package iso9660

import (
	"encoding/binary"
	"io"
)

// PSX CD-ROM Sector Encoding:
// https://problemkaputt.de/psx-spx.htm

type location uint32
type sectorData []byte

const sectorSize = 0x800
const sectorMode2Size = 0x800 + 0x130

var (
	sync = []byte{
		0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00}
)

func readSector(r io.ReaderAt, loc location, mode TrackMode, useMode2 bool) (sectorData, error) {
	var offset int64
	var secLength int
	if mode == TrackMode1_2048 {
		offset = int64(loc) * sectorSize
		secLength = sectorSize
	} else if mode == TrackMode2_2352 {
		if useMode2 {
			offset = int64(loc) * sectorMode2Size
			secLength = sectorMode2Size
		} else {
			offset = 0x18 + int64(loc)*sectorMode2Size
			secLength = sectorSize
		}
	} else {
		return []byte{}, ErrUnkTrackMode
	}

	sec := sectorData(make([]byte, secLength))
	_, err := r.ReadAt(sec, offset)

	return sec, err
}

func writeSector(w io.WriterAt, loc location, mode TrackMode, s sectorData) error {
	var offset int64
	if mode == TrackMode1_2048 {
		offset = int64(loc) * sectorSize
	} else if mode == TrackMode2_2352 {
		offset = int64(loc) * (sectorSize + 0x130)
	} else {
		return ErrUnkTrackMode
	}

	switch mode {
	case TrackMode1_2048:
		if _, err := w.WriteAt(s, offset); err != nil {
			return err
		}
	case TrackMode2_2352:
		const TrackMode = 2
		const Form2_2352 = 8

		seconds := 2 + loc/75
		subHeader := []byte{
			0x00,       // file
			0x00,       // channel
			Form2_2352, // submode
			0x00,       // coding info
		}
		block := make([]byte, 0x930)
		copy(block[0:], sync)
		copy(block[12:], []byte{
			decToHex(seconds / 60),
			decToHex(seconds % 60),
			decToHex(loc % 75),
			TrackMode})
		copy(block[16:], subHeader)
		copy(block[20:], subHeader)
		copy(block[0x18:], s)
		binary.LittleEndian.PutUint32(block[0x818:], computeEDC(block[0x10:0x818]))
		calcPParity(block)
		calcQParity(block)
		//replicateBugs(block)

		if _, err := w.WriteAt(block, offset); err != nil {
			return err
		}
	}

	return nil
}

func MakeSector() sectorData {
	return sectorData(make([]byte, 2048))
}

func decToHex(n location) byte {
	return byte((n % 10) + (n/10)*16)
}

func replicateBugs(block []byte) {
	block[0x81C] = 0
	block[0x81D] = 0
	block[0x81E] = 0
	block[0x81F] = 0
	block[0x872] = 0
	block[0x873] = 0
	block[0x874] = 0
	block[0x875] = 0
	block[0x8C8] = 0
	block[0x8C9] = 0
	block[0x8F7] = 0
	block[0x8F8] = 0
	block[0x8F9] = 0
	block[0x8FA] = 0
	block[0x8FB] = 0
	block[0x8FC] = 0
	block[0x8FD] = 0
	block[0x92B] = 0
	block[0x92C] = 0
	block[0x92D] = 0
	block[0x92E] = 0
	block[0x92F] = 0
}
