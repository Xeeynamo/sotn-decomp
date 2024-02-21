package main

import (
	"errors"
	"fmt"
	"io/ioutil"
	"os"
	"path"
	"strings"
	"unicode"

	"github.com/xeeynamo/sotn-decomp/tools/sotn-disk/iso9660"
)

type cueTrack struct {
	id   string
	file string
	mode string
}

func assert(condition bool, message string) {
	if !condition {
		panic(message)
	}
}

func performCueAction(cuePath string, action imageAction) error {
	tracks, err := parseTracks(cuePath)
	if err != nil {
		return err
	}
	if len(tracks) == 0 {
		return errors.New("CUE do not provide any track")
	}

	mainTrack := getFirstTrack(tracks)
	var mode iso9660.TrackMode
	switch mainTrack.mode {
	case "MODE1/2048":
		mode = iso9660.TrackMode1_2048
	case "MODE1/2352":
		mode = iso9660.TrackMode1_2352
	case "MODE2/2352":
		mode = iso9660.TrackMode2_2352
	default:
		return fmt.Errorf("unrecognized TRACK mode '%s'", mode)
	}

	baseDir, _ := path.Split(cuePath)
	binPath := path.Join(baseDir, mainTrack.file)

	f, err := os.Open(binPath)
	if err != nil {
		return err
	}
	defer f.Close()

	image, err := iso9660.OpenImage(f, mode)

	// 80 	8 	Volume Space Size 	int32_LSB-MSB 	Number of Logical Blocks in which the volume is recorded. 
	// 120 	4 	Volume Set Size 	int16_LSB-MSB 	The size of the set in this logical volume (number of disks).
	// 124 	4 	Volume Sequence Number 	int16_LSB-MSB 	The number of this disk in the Volume Set.
	// 128 	4 	Logical Block Size 	int16_LSB-MSB 	The size in bytes of a logical block. NB: This means that a logical block on a CD could be something other than 2 KiB!
	// 132 	8 	Path Table Size 	int32_LSB-MSB 	The size in bytes of the path table. 
	// 148 	4 	Location of Type-M Path Table 	int32_MSB 	LBA location of the path table. The path table pointed to contains only big-endian values.
	// 152 	4 	Location of Optional Type-M Path Table 	int32_MSB 	LBA location of the optional path table. The path table pointed to contains only big-endian values. Zero means that no optional path table exists. 
	assert(image.Pvd.VolumeSpaceSize.MSB == image.Pvd.VolumeSpaceSize.LSB, "VolumeSpaceSize")
	assert(image.Pvd.VolumeSetSize.MSB == image.Pvd.VolumeSetSize.LSB, "VolumeSetSize")
	assert(image.Pvd.VolumeSequenceNumber.MSB == image.Pvd.VolumeSequenceNumber.LSB, "VolumeSequenceNumber")
	assert(image.Pvd.LogicalBlockSize.MSB == image.Pvd.LogicalBlockSize.LSB, "LogicalBlockSize")
	assert(image.Pvd.PathTableSize.MSB == image.Pvd.PathTableSize.LSB, "PathTableSize")
	fmt.Print(image.Pvd.PathMTableLocation.MSB, " ", image.Pvd.PathMTableLocation.LSB, "\n")

	// this fails
	// assert(image.Pvd.PathMTableLocation.MSB == image.Pvd.PathMTableLocation.LSB, "PathMTableLocation")
	assert(image.Pvd.PathOptionalMTableLocation.MSB == image.Pvd.PathOptionalMTableLocation.LSB, "PathOptionalMTableLocation")

	if err != nil {
		return err
	}

	return action(image.RootDir())
}

func getFirstTrack(tracks []cueTrack) cueTrack {
	cueTrack := tracks[0]
	for _, track := range tracks {
		if track.id == "1" || track.id == "01" {
			cueTrack = track
			break
		}
	}

	return cueTrack
}

func parseTracks(cuePath string) ([]cueTrack, error) {
	content, err := ioutil.ReadFile(cuePath)
	if err != nil {
		return nil, err
	}
	lines := strings.Split(string(content), "\n")

	tracks := make([]cueTrack, 0)
	var track *cueTrack = nil
	for _, line := range lines {
		tokens := tokenizeCueLine(line)
		if len(tokens) < 2 {
			continue
		}

		switch tokens[0] {
		case "FILE":
			if len(tokens) < 3 {
				return nil, fmt.Errorf("cue line '%s' invalid", line)
			}
			if track != nil {
				tracks = append(tracks, *track)
			}

			track = &cueTrack{}
			track.file = tokens[1]
		case "TRACK":
			if len(tokens) < 3 {
				return nil, fmt.Errorf("cue line '%s' invalid", line)
			}

			track.id = tokens[1]
			track.mode = tokens[2]

			// need to append here since there's multiple tracks in the same file
			if track != nil {
				tracks = append(tracks, *track)
			}

		}
	}

	if track != nil {
		tracks = append(tracks, *track)
	}

	return tracks, nil
}

func tokenizeCueLine(line string) []string {
	tokens := []string{}
	str := ""
	quotes := false
	for _, ch := range strings.TrimSpace(line) {
		if !quotes && unicode.IsSpace(ch) {
			tokens = append(tokens, str)
			str = ""
		} else if ch == '"' {
			if quotes {
				quotes = false
			} else {
				quotes = true
			}
		} else {
			str += string(ch)
		}
	}

	if len(str) > 0 {
		tokens = append(tokens, str)
	}

	return tokens
}
