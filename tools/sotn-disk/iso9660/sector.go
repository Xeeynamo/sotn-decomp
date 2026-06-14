package iso9660

import (
	"encoding/binary"
	"io"
)

// PSX CD-ROM Sector Encoding:
// https://problemkaputt.de/psx-spx.htm

type location uint32
type sectorData []byte

const sectorSize = 0x800              // 2048: data sector with implicit ECC
const sectorXaSize = 0x920            // 2336: subheader (8) + data (2328), no sync/MSF
const sectorMode2Size = 0x800 + 0x130 // 2352: full raw sector

// CD-ROM XA subheader submode flags
const (
	SubModeEOR   byte = 0x01 // End of Record
	SubModeData  byte = 0x08 // Data sector
	SubModeForm2 byte = 0x20 // Form 2 (no ECC, extended data area)
	SubModeEOF   byte = 0x80 // End of File
)

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

func writeSector(w io.WriterAt, loc location, mode TrackMode, subMode byte, s sectorData) error {
	var offset int64
	if mode == TrackMode1_2048 {
		offset = int64(loc) * sectorSize
	} else if mode == TrackMode2_2352 {
		offset = int64(loc) * sectorMode2Size
	} else {
		return ErrUnkTrackMode
	}

	switch mode {
	case TrackMode1_2048:
		if _, err := w.WriteAt(s, offset); err != nil {
			return err
		}
	case TrackMode2_2352:
		switch len(s) {
		case sectorSize:
			const TrackMode = 2
			seconds := 2 + loc/75
			subHeader := []byte{
				0x00,    // file
				0x00,    // channel
				subMode, // submode
				0x00,    // coding info
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

			if subMode&SubModeForm2 != 0 {
				// Form 2: optional EDC at 0x92C, no ECC
				binary.LittleEndian.PutUint32(block[0x92C:], computeEDC(block[0x10:0x92C]))
			} else {
				// Form 1: EDC + ECC
				binary.LittleEndian.PutUint32(block[0x818:], computeEDC(block[0x10:0x818]))
				// Per ECMA-130, Mode 2 Form 1 ECC is computed with the
				// 4-byte header (address) field zeroed out.
				savedHeader := [4]byte{block[12], block[13], block[14], block[15]}
				block[12], block[13], block[14], block[15] = 0, 0, 0, 0
				calcPParity(block)
				calcQParity(block)
				block[12] = savedHeader[0]
				block[13] = savedHeader[1]
				block[14] = savedHeader[2]
				block[15] = savedHeader[3]
			}

			if _, err := w.WriteAt(block, offset); err != nil {
				return err
			}
		case sectorXaSize:
			// 2336-byte XA sector: subheader (8) + data (2328)
			// Wrap with sync pattern and MSF header to produce full 2352-byte sector
			const TrackModeXa = 2
			secondsXa := 2 + loc/75
			block := make([]byte, sectorMode2Size)
			copy(block[0:], sync)
			block[12] = decToHex(secondsXa / 60)
			block[13] = decToHex(secondsXa % 60)
			block[14] = decToHex(loc % 75)
			block[15] = TrackModeXa
			copy(block[16:], s) // subheader (8) + data (2328) from file
			// Form 2 EDC
			binary.LittleEndian.PutUint32(block[0x92C:], computeEDC(block[0x10:0x92C]))
			if _, err := w.WriteAt(block, offset); err != nil {
				return err
			}
		case sectorMode2Size:
			if _, err := w.WriteAt(s, offset); err != nil {
				return err
			}
		}
	}

	return nil
}

func MakeSector(useMode2 bool) sectorData {
	if useMode2 {
		return sectorData(make([]byte, sectorMode2Size))
	}
	return sectorData(make([]byte, sectorSize))
}

// makeSectorForSize creates a sector buffer matching the XA file's sector size.
func makeSectorForSize(fileSize int64) sectorData {
	secSize := xaFileSectorSize(fileSize)
	return sectorData(make([]byte, secSize))
}

// xaFileSectorSize returns the per-sector size for an XA streaming file.
func xaFileSectorSize(fileSize int64) int64 {
	if fileSize%sectorMode2Size == 0 {
		return sectorMode2Size
	}
	if fileSize%sectorXaSize == 0 {
		return sectorXaSize
	}
	return sectorSize
}

func decToHex(n location) byte {
	return byte((n % 10) + (n/10)*16)
}
