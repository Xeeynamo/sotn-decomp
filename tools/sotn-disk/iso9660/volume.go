package iso9660

type VolumeType byte

const (
	VolumeTypeBoot = VolumeType(iota)
	VolumeTypePrimary
	VolumeTypeSupplementary
	VolumeTypePartition
	VolumeTypeTerminator = VolumeType(0xFF)
)

var DefaultTVD = TerminatorVolumeDescriptor{
	VolumeDescriptorType:    VolumeTypeTerminator,
	StandardIdentifier:      ToAString("CD001", 5),
	VolumeDescriptorVersion: 1,
}

type PrimaryVolumeDescriptor struct {
	VolumeDescriptorType        VolumeType
	StandardIdentifier          AString
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
	ApplicationIdentifier       AString
	CopyrightFileIdentifier     DString
	AbstractFileIdentifier      DString
	BibliographicFileIdentifier DString
	VolumeCreationDateTime      VolumeTimestamp
	VolumeModificationDateTime  VolumeTimestamp
	VolumeExpirationDateTime    VolumeTimestamp
	VolumeEffectiveDateTime     VolumeTimestamp
	FileStructureVersion        byte
	ApplicationUse              []byte
	reserved                    []byte
}

type TerminatorVolumeDescriptor struct {
	VolumeDescriptorType    VolumeType
	StandardIdentifier      AString
	VolumeDescriptorVersion byte
}

func parsePVD(s sectorData) PrimaryVolumeDescriptor {
	data := []byte(s)
	return PrimaryVolumeDescriptor{
		VolumeDescriptorType:        VolumeType(data[0]),
		StandardIdentifier:          AString(data[1:6]),
		VolumeDescriptorVersion:     data[6],
		SystemIdentifier:            AString(data[8:40]),
		VolumeIdentifier:            DString(data[40:72]),
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
		ApplicationIdentifier:       AString(data[574:702]),
		CopyrightFileIdentifier:     DString(data[702:740]),
		AbstractFileIdentifier:      DString(data[740:776]),
		BibliographicFileIdentifier: DString(data[776:813]),
		VolumeCreationDateTime:      parseVolumeTimestamp(data[813:830]),
		VolumeModificationDateTime:  parseVolumeTimestamp(data[830:847]),
		VolumeExpirationDateTime:    parseVolumeTimestamp(data[847:864]),
		VolumeEffectiveDateTime:     parseVolumeTimestamp(data[864:881]),
		FileStructureVersion:        data[881],
		ApplicationUse:              data[883:1395],
		reserved:                    data[1395:2048],
	}
}

func serializePVD(pvd PrimaryVolumeDescriptor) sectorData {
	data := MakeSector()

	data[0] = byte(pvd.VolumeDescriptorType)
	copy(data[1:6], []byte(pvd.StandardIdentifier))
	data[6] = byte(pvd.VolumeDescriptorVersion)
	copy(data[8:40], []byte(pvd.SystemIdentifier))
	copy(data[40:72], []byte(pvd.VolumeIdentifier))
	copy(data[80:88], serialize32(pvd.VolumeSpaceSize))
	copy(data[120:124], serialize16(pvd.VolumeSetSize))
	copy(data[124:128], serialize16(pvd.VolumeSequenceNumber))
	copy(data[128:132], serialize16(pvd.LogicalBlockSize))
	copy(data[132:140], serialize32(pvd.PathTableSize))
	copy(data[140:144], serialize16(pvd.PathLTableLocation))
	copy(data[144:148], serialize16(pvd.PathOptionalLTableLocation))
	copy(data[148:152], serialize16(pvd.PathMTableLocation))
	copy(data[152:156], serialize16(pvd.PathOptionalMTableLocation))
	copy(data[156:190], serializeDirectoryEntry(pvd.DirectoryRecord))
	copy(data[190:318], []byte(pvd.VolumeSetIdentifier))
	copy(data[318:446], []byte(pvd.PublisherIdentifier))
	copy(data[446:574], []byte(pvd.DataPreparerIdentifier))
	copy(data[574:702], []byte(pvd.ApplicationIdentifier))
	copy(data[702:740], []byte(pvd.CopyrightFileIdentifier))
	copy(data[740:776], []byte(pvd.AbstractFileIdentifier))
	copy(data[776:813], []byte(pvd.BibliographicFileIdentifier))
	copy(data[813:830], serializeVolumeTimestamp(pvd.VolumeCreationDateTime))
	copy(data[830:847], serializeVolumeTimestamp(pvd.VolumeModificationDateTime))
	copy(data[847:864], serializeVolumeTimestamp(pvd.VolumeExpirationDateTime))
	copy(data[864:881], serializeVolumeTimestamp(pvd.VolumeEffectiveDateTime))
	data[881] = pvd.FileStructureVersion
	copy(data[883:1395], pvd.ApplicationUse)
	copy(data[1395:2048], pvd.reserved)

	return sectorData(data)
}

func serializeTVD(pvd TerminatorVolumeDescriptor) sectorData {
	data := MakeSector()

	data[0] = byte(pvd.VolumeDescriptorType)
	copy(data[1:6], []byte(pvd.StandardIdentifier))
	data[6] = byte(pvd.VolumeDescriptorVersion)

	return sectorData(data)
}
