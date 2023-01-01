package iso9660

import "encoding/binary"

type XaMode uint16

type XaExtendedMeta struct {
	GroupID uint16
	UserID  uint16
	Flags   uint16
	FileNo  byte
}

type DirectoryEntry struct {
	DirectoryRecordLength byte

	// this field refers to the Extended Attribute Record, which provides
	// additional information about a file to systems that know how to use it.
	// Since few systems use it, we will not discuss it here
	ExtendedAttributeRecordLength byte

	// This is the Logical Block Number of the first Logical Block allocated to
	// the file.
	ExtentLocation Data32

	// Length of the file section in bytes
	DataLength Data32

	// This is recorded in the same format as the Volume Creation Date and Time
	RecordingDateTime Timestamp

	FileFlags byte

	// This field is only valid if the file is recorded in interleave mode.
	// Otherwise this field is (00)
	FileUnitSize byte

	// This field is only valid if the file is recorded in interleave mode.
	// Otherwise this field is (00)
	InterleaveGapSize byte

	// The ordinal number of the volume in the Volume Set on which the file
	// described by the directory record is recorded
	VolumeSequenceNumber Data16

	// Length in bytes for the following section
	FileIdentifierLength byte

	// Depends on the setting of the directory bit in the File Flags
	// If set to ZERO, then
	// The field refers to a File Identifier, as described below
	// If set to ONE, then
	// The field refers to a Directory Identifier, as described below
	FileIdentifier string

	// For CD-XA disks, additional metadata is found after the file identifier
	XaExt *XaExtendedMeta
}

const (
	isDirectoryFlag = 2
)

const (
	// the following flags are used in the CD-XA extension
	// courtesy of https://problemkaputt.de/psx-spx.htm
	XaModeNone       = 0
	XaModeDefault    = XaMode(0x0D55)
	XaModeXa         = XaMode(0x1555)
	XaModeStreaming  = XaMode(0x3D55)
	XaModeAudioTrack = XaMode(0x4555)
	XaModeDirRecord  = XaMode(0x8D55)
)

func parseDirectoryEntry(data []byte) DirectoryEntry {
	de := DirectoryEntry{
		DirectoryRecordLength:         data[0],
		ExtendedAttributeRecordLength: data[1],
		ExtentLocation:                read32(data[2:10]),
		DataLength:                    read32(data[10:18]),
		RecordingDateTime:             parseTimestamp(data[18:25]),
		FileFlags:                     data[25],
		FileUnitSize:                  data[26],
		InterleaveGapSize:             data[27],
		VolumeSequenceNumber:          read16(data[28:32]),
		FileIdentifierLength:          data[32],
	}
	de.FileIdentifier = string(data[33:][:de.FileIdentifierLength])

	xaOff := 33 + de.FileIdentifierLength
	xaLen := 14
	if de.DirectoryRecordLength >= xaOff+byte(xaLen) &&
		data[de.DirectoryRecordLength-8] == 'X' &&
		data[de.DirectoryRecordLength-7] == 'A' {
		xaHeader := data[de.DirectoryRecordLength-byte(xaLen):][:xaLen]
		de.XaExt = &XaExtendedMeta{
			GroupID: binary.BigEndian.Uint16(xaHeader[0:]),
			UserID:  binary.BigEndian.Uint16(xaHeader[2:]),
			Flags:   binary.BigEndian.Uint16(xaHeader[4:]),
			FileNo:  xaHeader[8],
		}
	}

	return de
}

func serializeDirectoryEntry(de DirectoryEntry) []byte {
	data := make([]byte, de.DirectoryRecordLength)

	data[0] = de.DirectoryRecordLength
	data[1] = de.ExtendedAttributeRecordLength
	copy(data[2:10], serialize32(de.ExtentLocation))
	copy(data[10:18], serialize32(de.DataLength))
	copy(data[18:25], serializeTimestamp(de.RecordingDateTime))
	data[25] = de.FileFlags
	data[26] = de.FileUnitSize
	data[27] = de.InterleaveGapSize
	copy(data[28:32], serialize16(de.VolumeSequenceNumber))
	data[32] = de.FileIdentifierLength
	copy(data[33:], []byte(de.FileIdentifier))

	if de.XaExt != nil {
		xaHeader := data[de.DirectoryRecordLength-14:]
		binary.BigEndian.AppendUint16(xaHeader[0:], de.XaExt.GroupID)
		binary.BigEndian.AppendUint16(xaHeader[2:], de.XaExt.UserID)
		binary.BigEndian.AppendUint16(xaHeader[4:], de.XaExt.Flags)
		xaHeader[6] = 0x58
		xaHeader[7] = 0x41
		xaHeader[8] = de.XaExt.FileNo
	}

	return data
}

func (de DirectoryEntry) IsHidden() bool {
	return (de.FileFlags & 1) == 1
}

func (de DirectoryEntry) IsDirectory() bool {
	return (de.FileFlags & isDirectoryFlag) == isDirectoryFlag
}

func (de DirectoryEntry) IsAssociatedFile() bool {
	return (de.FileFlags & 4) == 4
}

func (de DirectoryEntry) HasExtendedRecords() bool {
	return (de.FileFlags & 8) == 8
}

func (de DirectoryEntry) HasExtendedPermissions() bool {
	return (de.FileFlags & 16) == 16
}

func (de DirectoryEntry) HasMoreThanOneRecord() bool {
	return (de.FileFlags & 128) == 128
}

func (de DirectoryEntry) GetOptionalXaMode() XaMode {
	if de.XaExt == nil {
		return XaModeNone
	}

	return XaMode(de.XaExt.Flags)
}
