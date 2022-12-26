package iso9660

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

func (de DirectoryEntry) IsHidden() bool {
	return (de.FileFlags & 1) == 1
}

func (de DirectoryEntry) IsDirectory() bool {
	return (de.FileFlags & 2) == 2
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
