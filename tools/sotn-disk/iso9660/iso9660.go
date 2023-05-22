package iso9660

// https://archive.vn/xs9ac

import (
	"errors"
	"io"
	"fmt"
)

type TrackMode int

const (
	TrackMode1_2048 = TrackMode(0x800)
	TrackMode1_2352 = TrackMode(0x930) // The 2352 bytes consist of 2048 data bytes, 288 bytes of error correction code (ECC), and 16 bytes of sub-channel data.
	TrackMode2_2352 = TrackMode(0x930) 
)

var (
	ErrUnkTrackMode = errors.New("unknown track mode")
)

type Image struct {
	reader io.ReaderAt
	mode   TrackMode
	Pvd    PrimaryVolumeDescriptor
}

type File struct {
	DirectoryEntry
	reader io.ReaderAt
	mode   TrackMode
}

func OpenImage(r io.ReaderAt, mode TrackMode) (*Image, error) {
	pvdSec, err := readSector(r, 16, mode, false)
	if err != nil {
		return nil, err
	}

	return &Image{
		reader: r,
		mode:   mode,
		Pvd:    parsePVD(pvdSec), // TODO assume first volume is always primary
	}, nil
}

func (img *Image) RootDir() File {
	return File{
		DirectoryEntry: img.Pvd.DirectoryRecord,
		reader:         img.reader,
		mode:           img.mode,
	}
}

func assert(condition bool) {
	if !condition {
		panic("mismatch")
	}
}

func (file File) GetChildren() ([]File, error) {
	const secSize = 0x800
	const bufSafe = 0x20

	chloc := file.ExtentLocation.LSB

	assert(file.ExtentLocation.LSB == file.ExtentLocation.MSB)
	assert(file.DataLength.LSB == file.DataLength.MSB)
	assert(file.VolumeSequenceNumber.LSB == file.VolumeSequenceNumber.MSB)

	files := make([]File, 0)
	offset := secSize
	var data []byte
	for {
		// horrible hack as it can read unnecessary bytes, but it works
		if offset+bufSafe > secSize {
			sec, err := readSector(file.reader, location(chloc), file.mode, false)
			if err != nil {
				return nil, err
			}
			data = []byte(sec)
			offset = 0
			chloc++
		} else {
			fmt.Print("rejected sector ", "offset ", offset, " secSize ", secSize, " offset+bufSafe ", offset+bufSafe, " chloc ", chloc, "\n")
		}

		f := File{
			DirectoryEntry: parseDirectoryEntry(data[offset:]),
			reader:         file.reader,
			mode:           file.mode,
		}
		if f.DirectoryRecordLength == 0 {
			return files, nil
		}

		files = append(files, f)
		offset += int(f.DirectoryRecordLength)
	}
}

func (file File) WriteFile(w io.Writer) error {
	size := file.DataLength.LSB
	sector := location(file.ExtentLocation.LSB)

	useMode2 := false
	if file.XaExt != nil && (file.XaExt.Flags&xaIsMode2) == xaIsMode2 {
		size = (size/sectorSize)*2352 + (size % sectorSize)
		useMode2 = true
	}

	for size > 0 {
		sec, err := readSector(file.reader, sector, file.mode, useMode2)
		if err != nil {
			if err == io.EOF {
				return nil
			}
			return err
		}

		data := []byte(sec)
		if size < uint32(len(data)) {
			data = data[:size]
		}

		w.Write(data)
		size -= uint32(len(data))
		sector++
	}

	return nil
}
