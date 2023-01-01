package iso9660

import "encoding/binary"

func (img *WritableImage) getPathTable() []pathTable {
	return append([]pathTable{
		{name: "\x00", loc: img.Pvd.DirectoryRecord.ExtentLocation.LSB, parent: 1},
	}, img.getPathTableNode(&img.root, 1)...)
}

func (img *WritableImage) getPathTableNode(tree *dirTree, parent int) []pathTable {
	data := make([]pathTable, 0)
	for _, v := range tree.children {
		if v.children != nil {
			data = append(data, pathTable{
				name:   v.dirent.FileIdentifier,
				loc:    img.dirMap[v.name].dirent.ExtentLocation.LSB,
				parent: parent,
			})
		}
	}

	// TODO technically wrong, but Castlevania does not have deep dir paths
	idx := parent
	for _, v := range tree.children {
		if v.children != nil {
			idx++
			data = append(data, img.getPathTableNode(v, idx)...)
		}
	}

	return data
}

func serializePathTableLSB(t []pathTable) []byte {
	data := make([]byte, 0)
	for _, p := range t {
		pdata := make([]byte, 8+((len(p.name)+1)/2)*2)
		pdata[0] = byte(len(p.name))
		pdata[1] = 0
		binary.LittleEndian.PutUint32(pdata[2:], p.loc)
		binary.LittleEndian.PutUint16(pdata[6:], uint16(p.parent))
		copy(pdata[8:], []byte(p.name))

		data = append(data, pdata...)
	}

	return data
}

func serializePathTableMSB(t []pathTable) []byte {
	data := make([]byte, 0)
	for _, p := range t {
		pdata := make([]byte, 8+(len(p.name)+1)/2)
		pdata[0] = byte(len(p.name))
		pdata[1] = 0
		binary.BigEndian.PutUint32(pdata[2:], p.loc)
		binary.BigEndian.PutUint16(pdata[6:], uint16(p.parent))
		copy(pdata[8:], []byte(p.name))

		data = append(data, pdata...)
	}

	return data
}
