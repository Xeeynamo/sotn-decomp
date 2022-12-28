package iso9660

const (
	isDirectoryFlag = 2

	// the following flags are used in the CD-XA extension
	isMode2ExFlag       = 0x08
	isMode2Form2ExFlag  = 0x10
	isInterleavedExFlag = 0x20
	isCDDAExFlag        = 0x40
	isDirectoryExFlag   = 0x80
)

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
}

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

	uxaFlag := byte(0xD)
	if (de.FileFlags & isDirectoryFlag) == isDirectoryFlag {
		uxaFlag |= isDirectoryExFlag
	}
	// TODO uxaFlag |= isMode2Form2ExFlag | isInterleavedExFlag
	data[data[0]-10+0] = uxaFlag
	data[data[0]-10+1] = 0x55
	data[data[0]-10+2] = 0x58
	data[data[0]-10+3] = 0x41

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
