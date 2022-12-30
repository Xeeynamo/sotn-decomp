package main

import (
	"bufio"
	"fmt"
	"io/ioutil"
	"os"
	"path"
	"strings"

	"github.com/xeeynamo/sotn-decomp/tools/sotn-disk/iso9660"
)

var (
	usLicense = "          Licensed  by          Sony Computer Entertainment Amer  ica "
)

func isPathFile(str string) bool {
	return len(str) > 2 &&
		str[len(str)-2] == 0x3B &&
		str[len(str)-1] == 0x31
}

func removePathVersion(str string) string {
	return str[:len(str)-2]
}

func readFileList(fileListPath string) ([]string, error) {
	content, err := ioutil.ReadFile(fileListPath)
	if err != nil {
		return nil, err
	}

	return strings.Split(string(content), "\n"), nil
}

func validateFileList(filePaths []string, basePath string) error {
	for _, filePath := range filePaths {
		if isPathFile(filePath) {
			fullPath := path.Join(basePath, removePathVersion((filePath)))
			if _, err := os.Stat(fullPath); err != nil {
				return err
			}
		}
	}

	return nil
}

func makeDisc(cuePath string, inputPath string, fileListPath string) error {
	filePaths, err := readFileList(fileListPath)
	if err != nil {
		return err
	}

	if err := validateFileList(filePaths, inputPath); err != nil {
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
	img.Pvd.VolumeCreationDateTime.Year = "1997"
	img.Pvd.VolumeCreationDateTime.Month = "09"
	img.Pvd.VolumeCreationDateTime.Day = "01"
	img.Pvd.VolumeCreationDateTime.Hour = "13"
	img.Pvd.VolumeCreationDateTime.Minute = "45"
	img.Pvd.VolumeCreationDateTime.Second = "00"
	img.Pvd.VolumeCreationDateTime.Hundredth = "00"
	img.Pvd.VolumeCreationDateTime.Offset = 36
	img.Pvd.DirectoryRecord.RecordingDateTime = iso9660.Timestamp{
		Year:   97,
		Month:  9,
		Day:    1,
		Hour:   13,
		Minute: 45,
		Second: 0,
		Offset: 36,
	}

	for _, filePath := range filePaths {
		if err := img.AddFile(filePath, inputPath); err != nil {
			return err
		}
	}

	img.WriteData(4, []byte(usLicense))
	img.WriteData(5, playstationLogo)

	// TODO HACK force the image to have a specific length
	if err := img.WriteSector(0x37E9B, iso9660.MakeSector()); err != nil {
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
