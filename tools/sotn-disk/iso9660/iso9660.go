package iso9660

// https://archive.vn/xs9ac

import (
	"errors"
	"io"
)

type TrackMode int
type VolumeType byte

const (
	TrackMode1_2048 = TrackMode(0x800)
	TrackMode2_2352 = TrackMode(0x930)
)

const (
	VolumeTypeBoot = VolumeType(iota)
	VolumeTypePrimary
	VolumeTypeSupplementary
	VolumeTypePartition
	VolumeTypeTerminator = VolumeType(0xFF)
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
	pvdSec, err := readSector(r, 16, mode)
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
			sec, err := readSector(file.reader, int64(chloc), file.mode)
			if err != nil {
				return nil, err
			}
			data = []byte(sec)
			offset = 0
			chloc++
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
	sector := int64(file.ExtentLocation.LSB)

	for size > 0 {
		sec, err := readSector(file.reader, sector, file.mode)
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
