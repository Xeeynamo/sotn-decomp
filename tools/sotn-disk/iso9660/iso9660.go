package iso9660

// https://archive.vn/xs9ac

import (
	"errors"
	"fmt"
	"io"
)

type TrackMode int

type ReaderWriterAt interface {
	io.ReaderAt
	io.WriterAt
}

const (
	TrackMode1_2048 = TrackMode(0x800)
	TrackMode2_2352 = TrackMode(0x930)
)

var (
	ErrUnkTrackMode = errors.New("unknown track mode")
)

type Image struct {
	reader ReaderWriterAt
	mode   TrackMode
	Pvd    PrimaryVolumeDescriptor
}

type File struct {
	DirectoryEntry
	handler ReaderWriterAt
	mode    TrackMode
}

func OpenImage(rw ReaderWriterAt, mode TrackMode) (*Image, error) {
	pvdSec, err := readSector(rw, 16, mode, false)
	if err != nil {
		return nil, err
	}

	return &Image{
		reader: rw,
		mode:   mode,
		Pvd:    parsePVD(pvdSec), // TODO assume first volume is always primary
	}, nil
}

func (img *Image) RootDir() File {
	return File{
		DirectoryEntry: img.Pvd.DirectoryRecord,
		handler:        img.reader,
		mode:           img.mode,
	}
}

func (file File) GetChildren() ([]File, error) {
	const secSize = 0x800
	const bufSafe = 0x20

	chloc := file.ExtentLocation.LSB

	files := make([]File, 0)
	offset := secSize
	var data []byte
	for {
		// horrible hack as it can read unnecessary bytes, but it works
		if offset+bufSafe > secSize {
			sec, err := readSector(file.handler, location(chloc), file.mode, false)
			if err != nil {
				return nil, err
			}
			data = []byte(sec)
			offset = 0
			chloc++
		}

		f := File{
			DirectoryEntry: parseDirectoryEntry(data[offset:]),
			handler:        file.handler,
			mode:           file.mode,
		}
		if f.DirectoryRecordLength == 0 {
			return files, nil
		}

		files = append(files, f)
		offset += int(f.DirectoryRecordLength)
	}
}

func (file File) ReadToFile(w io.Writer) error {
	size := file.DataLength.LSB
	sector := location(file.ExtentLocation.LSB)

	useMode2 := false
	if file.XaExt != nil && (file.XaExt.Flags&xaIsMode2) == xaIsMode2 {
		size = (size/sectorSize)*2352 + (size % sectorSize)
		useMode2 = true
	}

	for size > 0 {
		sec, err := readSector(file.handler, sector, file.mode, useMode2)
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

func (file File) WriteFromData(b []byte) error {
	if uint32(len(b)) > file.DataLength.LSB {
		return fmt.Errorf("data too long (%d > %d)", len(b), file.DataLength.LSB)
	}
	for loc := location(file.ExtentLocation.LSB); len(b) > 0; loc++ {
		chunk := b
		if len(b) > sectorSize {
			chunk = b[:sectorSize]
			b = b[sectorSize:]
		} else {
			b = []byte{}
		}
		if err := writeSector(file.handler, loc, file.mode, chunk); err != nil {
			return err
		}
	}
	return nil
}
