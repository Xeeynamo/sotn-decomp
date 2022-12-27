package iso9660

import "io"

type sectorData []byte

func readSector(r io.ReaderAt, sector int64, mode TrackMode) (sectorData, error) {
	var offset int64
	if mode == TrackMode1_2048 {
		offset = sector * 0x800
	} else if mode == TrackMode2_2352 {
		offset = 0x18 + sector*0x930
	} else {
		return []byte{}, ErrUnkTrackMode
	}

	buf := make([]byte, 2048)
	_, err := r.ReadAt(buf, offset)

	return sectorData(buf), err
}

func writeSector(w io.WriterAt, sector int64, mode TrackMode, s sectorData) error {
	// TODO
	panic("NOT IMPLEMENTED")
}
