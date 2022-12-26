package main

import (
	"fmt"
	"sort"

	"github.com/xeeynamo/sotn-decomp/tools/sotn-disk/iso9660"
)

type fileMeta struct {
	path   string
	size   int
	sector int
}

func list(f iso9660.File) error {
	meta, err := dumpFileMeta(f)
	if err != nil {
		return err
	}

	sort.SliceStable(meta, func(i, j int) bool {
		return meta[i].sector < meta[j].sector
	})

	for _, v := range meta {
		fmt.Printf("%s\n", v.path)
	}

	return nil
}

func dumpFileMeta(f iso9660.File) ([]fileMeta, error) {
	children, err := f.GetChildren()
	if err != nil {
		return nil, err
	}

	meta := make([]fileMeta, 0)
	for _, child := range children[2:] {
		meta = append(meta, fileMeta{
			path:   child.FileIdentifier,
			size:   int(child.DataLength.LSB),
			sector: int(child.ExtentLocation.LSB),
		})

		if child.IsDirectory() {
			childMeta, err := dumpFileMeta(child)
			if err != nil {
				return nil, err
			}

			for _, singlemeta := range childMeta {
				meta = append(meta, fileMeta{
					path:   fmt.Sprintf("%s/%s", child.FileIdentifier, singlemeta.path),
					size:   singlemeta.size,
					sector: singlemeta.sector,
				})
			}
		}
	}

	return meta, nil
}
