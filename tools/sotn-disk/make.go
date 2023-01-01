package main

import (
	"bufio"
	"fmt"
	"io/ioutil"
	"os"
	"path"
	"strconv"
	"strings"

	"github.com/xeeynamo/sotn-decomp/tools/sotn-disk/iso9660"
)

var (
	usLicense = "          Licensed  by          Sony Computer Entertainment Amer  ica "
)

type makeFileMeta struct {
	name   string
	time   iso9660.Timestamp
	xaMode iso9660.XaMode
}

func isPathFile(str string) bool {
	return len(str) > 2 &&
		str[len(str)-2] == 0x3B &&
		str[len(str)-1] == 0x31
}

func removePathVersion(str string) string {
	return str[:len(str)-2]
}

func readFileList(fileListPath string) ([]makeFileMeta, error) {
	atoi := func(s string) (byte, error) {
		v, err := strconv.Atoi(s)
		return byte(v), err
	}
	xaModeStr := func(str string) iso9660.XaMode {
		switch str {
		case "_":
			return iso9660.XaModeNone
		case "N":
			return iso9660.XaModeDefault
		case "X":
			return iso9660.XaModeXa
		case "A":
			return iso9660.XaModeAudioTrack
		case "S":
			return iso9660.XaModeStreaming
		case "D":
			return iso9660.XaModeDirRecord
		default:
			panic(fmt.Sprintf("unrecognized XaMode '%s'", str))
		}
	}

	content, err := ioutil.ReadFile(fileListPath)
	if err != nil {
		return nil, err
	}

	metaList := make([]makeFileMeta, 0)
	for _, v := range strings.Split(string(content), "\n") {
		tokens := strings.Split(v, ",")
		meta := makeFileMeta{name: tokens[0]}
		if len(tokens) > 1 {
			meta.xaMode = xaModeStr(tokens[1])
		}
		if len(tokens) > 2 {
			time := tokens[2]
			if len(time) != len("19970901-134500-36") {
				return nil, fmt.Errorf("wrong date time format '%s'", time)
			}

			var err error
			if meta.time.Year, err = atoi(time[2:4]); err != nil {
				return nil, err
			} else if meta.time.Month, err = atoi(time[4:6]); err != nil {
				return nil, err
			} else if meta.time.Day, err = atoi(time[6:8]); err != nil {
				return nil, err
			} else if meta.time.Hour, err = atoi(time[9:11]); err != nil {
				return nil, err
			} else if meta.time.Minute, err = atoi(time[11:13]); err != nil {
				return nil, err
			} else if meta.time.Second, err = atoi(time[13:15]); err != nil {
				return nil, err
			} else if meta.time.Offset, err = atoi(time[16:18]); err != nil {
				return nil, err
			}
		}

		metaList = append(metaList, meta)
	}

	return metaList, nil
}

func validateFileList(metas []makeFileMeta, basePath string) error {
	for _, meta := range metas {
		if isPathFile(meta.name) {
			fullPath := path.Join(basePath, removePathVersion((meta.name)))
			if _, err := os.Stat(fullPath); err != nil {
				return err
			}
		}
	}

	return nil
}

func makeDisc(cuePath string, inputPath string, fileListPath string) error {
	metas, err := readFileList(fileListPath)
	if err != nil {
		return err
	}

	if err := validateFileList(metas, inputPath); err != nil {
		return err
	}

	imgPath := strings.Replace(cuePath, ".cue", ".bin", 1)

	f, err := os.Create(imgPath)
	if err != nil {
		return err
	}
	defer f.Close()

	mode := iso9660.TrackMode2_2352
	img, err := iso9660.CreateImage(f, mode)
	if err != nil {
		return err
	}

	img.Pvd.SystemIdentifier = iso9660.ToAString("PLAYSTATION", 32)
	img.Pvd.VolumeIdentifier = iso9660.ToDString("SLUS_00067", 32)
	img.Pvd.PublisherIdentifier = iso9660.ToAString("KONAMI", 128)
	img.Pvd.DataPreparerIdentifier = iso9660.ToAString("KONAMI", 128)
	img.Pvd.ApplicationIdentifier = iso9660.ToAString("PLAYSTATION", 128)

	// define root timestamp, if present
	if len(metas) > 0 && metas[0].name == "" {
		rootts := metas[0].time
		img.Pvd.VolumeCreationDateTime.Year = fmt.Sprintf("19%02d", rootts.Year)
		img.Pvd.VolumeCreationDateTime.Month = fmt.Sprintf("%02d", rootts.Month)
		img.Pvd.VolumeCreationDateTime.Day = fmt.Sprintf("%02d", rootts.Day)
		img.Pvd.VolumeCreationDateTime.Hour = fmt.Sprintf("%02d", rootts.Hour)
		img.Pvd.VolumeCreationDateTime.Minute = fmt.Sprintf("%02d", rootts.Minute)
		img.Pvd.VolumeCreationDateTime.Second = fmt.Sprintf("%02d", rootts.Second)
		img.Pvd.VolumeCreationDateTime.Hundredth = "00"
		img.Pvd.VolumeCreationDateTime.Offset = rootts.Offset
		img.Pvd.DirectoryRecord.RecordingDateTime = rootts
		metas = metas[1:]
	}

	for _, meta := range metas {
		if err := img.AddFile(meta.name, inputPath, meta.time, meta.xaMode); err != nil {
			return err
		}
	}

	img.WriteData(4, []byte(usLicense))
	img.WriteData(5, playstationLogo)

	// TODO HACK force the image to have a specific length
	if err := img.WriteSector(0x37E9B, iso9660.MakeSector(false)); err != nil {
		return err
	}

	if err := img.FlushChanges(); err != nil {
		return err
	}

	if err := writeCue(cuePath, imgPath, mode); err != nil {
		return err
	}

	return nil
}

func writeCue(cuePath string, imgPath string, mode iso9660.TrackMode) error {
	f, err := os.Create(cuePath)
	if err != nil {
		return err
	}
	defer f.Close()

	w := bufio.NewWriter(f)
	defer w.Flush()

	w.WriteString(fmt.Sprintf("FILE \"%s\" BINARY\n", imgPath))
	switch mode {
	case iso9660.TrackMode1_2048:
		w.WriteString("  TRACK 01 MODE1/2048\n")
	case iso9660.TrackMode2_2352:
		w.WriteString("  TRACK 01 MODE2/2352\n")
	}
	w.WriteString("    FLAGS DCP\n")
	w.WriteString("    INDEX 01 00:00:00\n")

	return nil
}
