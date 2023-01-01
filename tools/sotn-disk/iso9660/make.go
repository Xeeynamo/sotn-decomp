package iso9660

import (
	"bytes"
	"io"
	"os"
	"path"
	"path/filepath"
	"sort"
	"strings"
)

type dirTree struct {
	name     string
	fullPath string
	dirent   DirectoryEntry
	children []*dirTree
}

type WritableImage struct {
	writer io.WriterAt
	mode   TrackMode
	Pvd    PrimaryVolumeDescriptor
	root   dirTree
	dirMap map[string]*dirTree
	order  []string
}

type pathTable struct {
	name   string
	loc    uint32
	parent int
}

func CreateImage(w io.WriterAt, mode TrackMode) (*WritableImage, error) {
	img := &WritableImage{
		writer: w,
		mode:   mode,
		Pvd: PrimaryVolumeDescriptor{
			VolumeDescriptorType:        1,
			StandardIdentifier:          ToAString("CD001", 5),
			VolumeDescriptorVersion:     1,
			SystemIdentifier:            ToAString("", 32),
			VolumeIdentifier:            ToDString("", 32),
			VolumeSetSize:               make16(1),
			VolumeSequenceNumber:        make16(1),
			LogicalBlockSize:            make16(sectorSize),
			VolumeSetIdentifier:         ToDString("", 128),
			PublisherIdentifier:         ToAString("", 128),
			DataPreparerIdentifier:      ToAString("", 128),
			ApplicationIdentifier:       ToAString("", 128),
			CopyrightFileIdentifier:     ToDString("", 38),
			AbstractFileIdentifier:      ToDString("", 36),
			BibliographicFileIdentifier: ToDString("", 37),
			VolumeCreationDateTime:      DefaultVolumeTimestamp,
			VolumeModificationDateTime:  DefaultVolumeTimestamp,
			VolumeExpirationDateTime:    DefaultVolumeTimestamp,
			VolumeEffectiveDateTime:     DefaultVolumeTimestamp,
			FileStructureVersion:        1,
			ApplicationUse:              makeApplicationUse("CD-XA001"),
		},
		dirMap: map[string]*dirTree{},
	}

	img.root = dirTree{
		dirent: DirectoryEntry{
			DirectoryRecordLength:         34,
			ExtendedAttributeRecordLength: 0,
			ExtentLocation:                Data32{LSB: 0, MSB: 0}, // to be filled
			DataLength:                    Data32{LSB: 2048, MSB: 0},
			RecordingDateTime:             Timestamp{},
			FileFlags:                     2,
			FileUnitSize:                  0,
			InterleaveGapSize:             0,
			VolumeSequenceNumber:          Data16{LSB: 1, MSB: 1},
			FileIdentifierLength:          1,
			FileIdentifier:                "",
		},
		children: make([]*dirTree, 0),
	}
	img.dirMap[""] = &img.root
	img.dirMap["."] = &img.root // alias

	// writes the first reserved 16 sectors
	for i := location(0); i < 16; i++ {
		img.WriteSector(i, MakeSector(false))
	}

	return img, nil
}

func (img *WritableImage) FlushChanges() error {
	const pvdLoc = 16
	const tvdLoc = pvdLoc + 1
	const pathTableLoc = tvdLoc + 1

	// TODO assumes every Path Table takes exactly one sector
	loc := uint16(pathTableLoc)
	img.Pvd.PathLTableLocation.LSB = loc + 0
	img.Pvd.PathLTableLocation.MSB = 0
	img.Pvd.PathOptionalLTableLocation.LSB = loc + 1
	img.Pvd.PathOptionalLTableLocation.MSB = 0
	img.Pvd.PathMTableLocation.LSB = 0
	img.Pvd.PathMTableLocation.MSB = loc + 2
	img.Pvd.PathOptionalMTableLocation.LSB = 0
	img.Pvd.PathOptionalMTableLocation.MSB = loc + 3

	loc += 4

	// TODO precalculate the final location for all the files
	img.Pvd.VolumeSpaceSize = make32(248015) // TODO value currently hardcoded

	if err := calcSizeDirTree(&img.root); err != nil {
		return err
	}
	img.calcLocDirTree(uint32(loc + 1))
	sortDirTree(&img.root)

	pathTable := img.getPathTable()
	pathTableLSB := serializePathTableLSB(pathTable)
	pathTableMSB := serializePathTableMSB(pathTable)
	img.Pvd.PathTableSize.LSB = uint32(len(pathTableLSB))
	img.Pvd.PathTableSize.MSB = uint32(len(pathTableMSB))
	img.root.dirent.ExtentLocation = make32(uint32(0x16)) // TODO hack

	if err := img.writeTree(); err != nil {
		return err
	}
	img.Pvd.DirectoryRecord = img.root.dirent

	writeSector(img.writer, pvdLoc, img.mode, serializePVD(img.Pvd))
	writeSector(img.writer, tvdLoc, img.mode, serializeTVD(DefaultTVD))

	if img.Pvd.PathLTableLocation.LSB > 0 {
		img.WriteData(location(img.Pvd.PathLTableLocation.LSB), pathTableLSB)
	}
	if img.Pvd.PathOptionalLTableLocation.LSB > 0 {
		img.WriteData(location(img.Pvd.PathOptionalLTableLocation.LSB), pathTableLSB)
	}
	if img.Pvd.PathMTableLocation.LSB > 0 {
		img.WriteData(location(img.Pvd.PathMTableLocation.LSB), pathTableMSB)
	}
	if img.Pvd.PathOptionalMTableLocation.LSB > 0 {
		img.WriteData(location(img.Pvd.PathOptionalMTableLocation.LSB), pathTableMSB)
	}

	// TODO start to write all the LBA and files based on the pre-calculated table
	img.Pvd.VolumeSpaceSize.LSB = 248015   // TODO expected 248015
	img.Pvd.VolumeSpaceSize.MSB = 50331651 // TODO expected 50331651 WTF?

	return nil
}

func (img *WritableImage) AddFile(filePath string, basePath string, ts Timestamp, mode XaMode) error {
	var fullPath string
	if isFileName(filePath) {
		fullPath = path.Join(basePath, removePathVersion(filePath))
	} else {
		fullPath = path.Join(basePath, filePath)
	}

	// file must exists
	_, err := os.Stat(fullPath)
	if err != nil {
		return err
	}

	img.addDirEntry(filePath, fullPath, ts, mode)
	img.order = append(img.order, filePath)
	return nil
}

func (img *WritableImage) addDirEntry(name string, fullPath string, ts Timestamp, mode XaMode) {
	parent := &img.root
	localPath := parent.dirent.FileIdentifier
	split := strings.Split(name, "/")
	for _, s := range split {
		localPath = path.Join(localPath, s)
		if isFileName(s) {
			node := &dirTree{
				name:     name,
				fullPath: fullPath,
				dirent:   makeDirectoryEntry(s, mode),
				children: nil,
			}
			node.dirent.RecordingDateTime = ts
			parent.children = append(parent.children, node)
			img.dirMap[name] = node
			return
		} else {
			nextParent, found := img.dirMap[localPath]
			if !found {
				nextParent = &dirTree{
					name:     localPath,
					fullPath: fullPath,
					dirent:   makeDirectoryEntry(s, mode),
					children: make([]*dirTree, 0),
				}
				img.dirMap[localPath] = nextParent
				parent.children = append(parent.children, nextParent)
			}
			parent = nextParent
		}
	}

	// Hack to always ensure to insert the right metadata into the
	// DirectoryEntry there might be a bug where if the name 'ST/NO3/NO3.BIN'
	// is inserted and then 'ST/NO3', then 'ST/NO3' will be created during the
	// first insert but it will not hold any of the metadata.
	// This is only appied for directories and not for files.
	de := &img.dirMap[localPath].dirent
	de.RecordingDateTime = ts
	de.XaExt = makeXaExt(mode)
}

func calcSizeDirTree(dt *dirTree) error {
	if dt.children == nil {
		info, err := os.Stat(dt.fullPath)
		if err != nil {
			return err
		}

		realSize := info.Size()
		if dt.dirent.IsXaStreaming() {
			realSize = (realSize / sectorMode2Size) * sectorSize
		}
		dt.dirent.DataLength = make32(uint32(realSize))
	} else {
		size := uint32(0x30 + 0x30) // assume '.' and '..'
		for _, node := range dt.children {
			chNodeLen := uint32(node.dirent.DirectoryRecordLength)
			if size/sectorSize < (size+chNodeLen)/sectorSize {
				size = (((size + sectorSize - 1) / sectorSize) * sectorSize) + chNodeLen
			} else {
				size += chNodeLen
			}
			calcSizeDirTree(node)
		}
		dt.dirent.DataLength = make32(((size + sectorSize - 1) / sectorSize) * sectorSize)
	}

	return nil
}

func (img *WritableImage) calcLocDirTree(startLoc uint32) {
	loc := startLoc
	for _, name := range img.order {
		node := img.dirMap[name]
		node.dirent.ExtentLocation = make32(loc)
		loc += (node.dirent.DataLength.LSB + sectorSize - 1) / sectorSize
	}
}

func (img *WritableImage) writeTree() error {
	if err := img.writeNode(&img.root); err != nil {
		return err
	}

	for _, name := range img.order {
		if err := img.writeNode(img.dirMap[name]); err != nil {
			return nil
		}
	}

	return nil
}

func (img *WritableImage) writeNode(node *dirTree) error {
	loc := location(node.dirent.ExtentLocation.LSB)
	if node.children != nil {
		parentName := filepath.Base(filepath.Dir(node.name))
		finalData := make([]byte, 0)
		finalData = append(finalData, serializeDirectoryEntry(DirectoryEntry{
			DirectoryRecordLength:         0x30,
			ExtendedAttributeRecordLength: 0,
			ExtentLocation:                make32(uint32(loc)),
			DataLength:                    node.dirent.DataLength,
			RecordingDateTime:             node.dirent.RecordingDateTime,
			FileFlags:                     isDirectoryFlag,
			VolumeSequenceNumber:          make16(1),
			FileIdentifierLength:          1,
			FileIdentifier:                "\x00",
			XaExt:                         &XaExtendedMeta{GroupID: 0, UserID: 0, Flags: uint16(XaModeDirRecord), FileNo: 0},
		})...)
		finalData = append(finalData, serializeDirectoryEntry(DirectoryEntry{
			DirectoryRecordLength:         0x30,
			ExtendedAttributeRecordLength: 0,
			ExtentLocation:                img.dirMap[parentName].dirent.ExtentLocation,
			DataLength:                    img.dirMap[parentName].dirent.DataLength,
			RecordingDateTime:             img.dirMap[parentName].dirent.RecordingDateTime,
			FileFlags:                     isDirectoryFlag,
			VolumeSequenceNumber:          make16(1),
			FileIdentifierLength:          1,
			FileIdentifier:                "\x01",
			XaExt:                         &XaExtendedMeta{GroupID: 0, UserID: 0, Flags: uint16(XaModeDirRecord), FileNo: 0},
		})...)

		offset := 0x30 + 0x30
		for _, child := range node.children {
			data := serializeDirectoryEntry(child.dirent)
			if offset+len(data) > sectorSize { // avoid sector overlapping
				padding := sectorSize - offset
				finalData = append(finalData, make([]byte, padding)...)
				offset = 0
			}
			offset += len(data)
			finalData = append(finalData, data...)
		}
		img.WriteData(loc, finalData)
		return nil
	} else {
		r, err := os.Open(node.fullPath)
		if err != nil {
			return err
		}
		defer r.Close()

		info, err := r.Stat()
		if err != nil {
			return err
		}

		size := info.Size()
		for size > 0 {
			toWrite := int64(sectorSize)
			if toWrite > size {
				toWrite = size
			}
			size -= toWrite

			sec := MakeSector(node.dirent.IsXaStreaming()) // TODO avoid to allocate a new sector every time
			_, err := r.Read(sec[0:toWrite])
			if err != nil {
				return err
			}

			img.WriteSector(loc, sec)
			loc++
		}
	}

	return nil
}

func sortDirTree(dt *dirTree) {
	if dt.children == nil {
		return
	}

	sort.SliceStable(dt.children, func(i, j int) bool {
		return dt.children[i].name < dt.children[j].name
	})

	for _, node := range dt.children {
		sortDirTree(node)
	}
}

func (img *WritableImage) WriteSector(loc location, data sectorData) error {
	return writeSector(img.writer, loc, img.mode, data)
}

func (img *WritableImage) Write(loc location, r io.Reader, size int64) error {
	for size > 0 {
		toWrite := int64(sectorSize)
		if toWrite > size {
			toWrite = size
		}
		size -= toWrite

		sec := MakeSector(false) // TODO avoid to allocate a new sector every time
		_, err := r.Read(sec[0:toWrite])
		if err != nil {
			return err
		}

		img.WriteSector(loc, sec)
		loc++
	}

	return nil
}

func (img *WritableImage) WriteData(loc location, data []byte) error {
	reader := bytes.NewReader(data)
	return img.Write(loc, reader, reader.Size())
}

func makeApplicationUse(name string) []byte {
	data := make([]byte, 0xB12)
	copy(data[0x8D:], []byte(name))
	return data
}

func isFileName(str string) bool {
	return len(str) > 2 &&
		str[len(str)-2] == 0x3B && str[len(str)-1] == 0x31
}

func removePathVersion(str string) string {
	return str[:len(str)-2]
}

func alignWord(v byte) byte {
	return ((v + 1) / 2) * 2
}

func makeDirectoryEntry(name string, mode XaMode) DirectoryEntry {
	fileName := filepath.Base(name)
	fileNameLen := byte(len(fileName))

	var fileFlags byte
	if isFileName(name) {
		fileFlags = 0
	} else {
		fileFlags = isDirectoryFlag
	}

	return DirectoryEntry{
		DirectoryRecordLength:         alignWord(0x30 + fileNameLen - 1),
		ExtendedAttributeRecordLength: 0,
		ExtentLocation:                make32(0),
		DataLength:                    make32(0),
		FileFlags:                     fileFlags,
		FileUnitSize:                  0,
		InterleaveGapSize:             0,
		VolumeSequenceNumber:          make16(1),
		FileIdentifierLength:          fileNameLen,
		FileIdentifier:                fileName,
		XaExt:                         makeXaExt(mode),
	}
}

func makeXaExt(mode XaMode) *XaExtendedMeta {
	if mode == XaModeNone {
		return nil
	}

	fileNo := byte(0)
	if mode == XaModeStreaming {
		fileNo = 1
	}

	return &XaExtendedMeta{
		GroupID: 0,
		UserID:  0,
		Flags:   uint16(mode),
		FileNo:  fileNo,
	}
}
