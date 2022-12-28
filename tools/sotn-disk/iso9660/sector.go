package iso9660

import "io"

type location uint32
type sectorData []byte

const sectorSize = 0x800

func readSector(r io.ReaderAt, loc location, mode TrackMode) (sectorData, error) {
	var offset int64
	if mode == TrackMode1_2048 {
		offset = int64(loc) * sectorSize
	} else if mode == TrackMode2_2352 {
		offset = 0x18 + int64(loc)*(sectorSize+0x130)
	} else {
		return []byte{}, ErrUnkTrackMode
	}

	sec := MakeSector()
	_, err := r.ReadAt(sec, offset)

	return sec, err
}

func writeSector(w io.WriterAt, loc location, mode TrackMode, s sectorData) error {
	var offset int64
	if mode == TrackMode1_2048 {
		offset = int64(loc) * sectorSize
	} else if mode == TrackMode2_2352 {
		offset = 0x18 + int64(loc)*(sectorSize+0x130)
	} else {
		return ErrUnkTrackMode
	}

	if _, err := w.WriteAt(s, offset); err != nil {
		return err
	}

	if mode == TrackMode2_2352 {
		ecc := make([]byte, 0x130)
		// TODO calculate 0x130 ECC
		// old: 538655040
		// new: 538299912
		if _, err := w.WriteAt(ecc, offset+sectorSize); err != nil {
			return err
		}
	}

	return nil
}

func MakeSector() sectorData {
	return sectorData(make([]byte, 2048))
}
