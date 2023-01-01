package main

import (
	"fmt"
	"sort"

	"github.com/xeeynamo/sotn-decomp/tools/sotn-disk/iso9660"
)

type fileMeta struct {
	path      string
	size      int
	sector    int
	timestamp iso9660.Timestamp
	xaMode    string
}

func list(f iso9660.File) error {
	meta, err := dumpFileMeta(f)
	if err != nil {
		return err
	}

	sort.SliceStable(meta, func(i, j int) bool {
		return meta[i].sector < meta[j].sector
	})

	roottime := f.RecordingDateTime
	fmt.Printf("%s,%s,%04d%02d%02d-%02d%02d%02d-%02d\n", "", "_",
		1900+int(roottime.Year), roottime.Month, roottime.Day,
		roottime.Hour, roottime.Minute, roottime.Second, roottime.Offset)
	for _, v := range meta {
		fmt.Printf("%s,%s,%04d%02d%02d-%02d%02d%02d-%02d\n", v.path, v.xaMode,
			1900+int(v.timestamp.Year), v.timestamp.Month, v.timestamp.Day,
			v.timestamp.Hour, v.timestamp.Minute, v.timestamp.Second, v.timestamp.Offset)
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
			path:      child.FileIdentifier,
			size:      int(child.DataLength.LSB),
			sector:    int(child.ExtentLocation.LSB),
			xaMode:    strXaMode(child.GetOptionalXaMode()),
			timestamp: child.RecordingDateTime,
		})

		if child.IsDirectory() {
			childMeta, err := dumpFileMeta(child)
			if err != nil {
				return nil, err
			}

			for _, singlemeta := range childMeta {
				meta = append(meta, fileMeta{
					path:      fmt.Sprintf("%s/%s", child.FileIdentifier, singlemeta.path),
					size:      singlemeta.size,
					sector:    singlemeta.sector,
					xaMode:    singlemeta.xaMode,
					timestamp: singlemeta.timestamp,
				})
			}
		}
	}

	return meta, nil
}

func strXaMode(xaMode iso9660.XaMode) string {
	switch xaMode {
	case iso9660.XaModeNone:
		return "_"
	case iso9660.XaModeDefault:
		return "N"
	case iso9660.XaModeXa:
		return "X"
	case iso9660.XaModeAudioTrack:
		return "A"
	case iso9660.XaModeStreaming:
		return "S"
	case iso9660.XaModeDirRecord:
		return "D"
	default:
		panic(fmt.Sprintf("unimplemented XaMode %04X", xaMode))
	}
}
