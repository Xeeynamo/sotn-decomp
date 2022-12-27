package iso9660

type PrimaryVolumeDescriptor struct {
	VolumeDescriptorType        VolumeType
	StandardIdentifier          string
	VolumeDescriptorVersion     byte
	SystemIdentifier            AString
	VolumeIdentifier            DString
	VolumeSpaceSize             Data32
	unused                      []byte
	VolumeSetSize               Data16
	VolumeSequenceNumber        Data16
	LogicalBlockSize            Data16
	PathTableSize               Data32
	PathLTableLocation          Data16
	PathOptionalLTableLocation  Data16
	PathMTableLocation          Data16
	PathOptionalMTableLocation  Data16
	DirectoryRecord             DirectoryEntry
	VolumeSetIdentifier         DString
	PublisherIdentifier         AString
	DataPreparerIdentifier      AString
	ApplicationIdentifier       string
	CopyrightFileIdentifier     string
	AbstractFileIdentifier      string
	BibliographicFileIdentifier string
	VolumeCreationDateTime      VolumeTimestamp
	VolumeModificationDateTime  VolumeTimestamp
	VolumeEffectiveDateTime     VolumeTimestamp
	FileStructureVersion        byte
	ApplicationUse              []byte
	reserved                    []byte
}

func parsePVD(s sectorData) PrimaryVolumeDescriptor {
	data := []byte(s)
	return PrimaryVolumeDescriptor{
		VolumeDescriptorType:        VolumeType(data[0]),
		StandardIdentifier:          string(data[1:6]),
		VolumeDescriptorVersion:     data[6],
		SystemIdentifier:            AString(data[40:72]),
		VolumeIdentifier:            DString(data[72:80]),
		VolumeSpaceSize:             read32(data[80:88]),
		unused:                      data[88:120],
		VolumeSetSize:               read16(data[120:124]),
		VolumeSequenceNumber:        read16(data[124:128]),
		LogicalBlockSize:            read16(data[128:132]),
		PathTableSize:               read32(data[132:140]),
		PathLTableLocation:          read16(data[140:144]),
		PathOptionalLTableLocation:  read16(data[144:148]),
		PathMTableLocation:          read16(data[148:152]),
		PathOptionalMTableLocation:  read16(data[152:156]),
		DirectoryRecord:             parseDirectoryEntry(data[156:190]),
		VolumeSetIdentifier:         DString(data[190:318]),
		PublisherIdentifier:         AString(data[318:446]),
		DataPreparerIdentifier:      AString(data[446:574]),
		ApplicationIdentifier:       string(data[574:702]),
		CopyrightFileIdentifier:     string(data[702:740]),
		AbstractFileIdentifier:      string(data[740:776]),
		BibliographicFileIdentifier: string(data[776:813]),
		VolumeCreationDateTime:      parseVolumeTimestamp(data[813:830]),
		VolumeModificationDateTime:  parseVolumeTimestamp(data[830:847]),
		VolumeEffectiveDateTime:     parseVolumeTimestamp(data[847:864]),
		FileStructureVersion:        data[881],
		ApplicationUse:              data[883:1395],
		reserved:                    data[1395:2048],
	}
}
