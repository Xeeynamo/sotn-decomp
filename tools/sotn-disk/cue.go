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
	case "MODE2/2352":
		mode = iso9660.TrackMode2_2352
	default:
		return fmt.Errorf("unrecognized TRACK mode '%s'", mainTrack.mode)
	}

	baseDir, _ := path.Split(cuePath)
	binPath := path.Join(baseDir, mainTrack.file)

	f, err := os.OpenFile(binPath, os.O_RDWR, 0)
	if err != nil {
		return err
	}
	defer f.Close()

	image, err := iso9660.OpenImage(f, mode)
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
	var file = ""
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
			file = tokens[1]
		case "TRACK":
			if len(tokens) < 3 {
				return nil, fmt.Errorf("cue line '%s' invalid", line)
			}
			if track != nil {
				tracks = append(tracks, *track)
			}

			track = &cueTrack{}
			track.file = file
			track.id = tokens[1]
			track.mode = tokens[2]
		}
	}

	if track != nil {
		tracks = append(tracks, *track)
	}

	return tracks, nil
}

func tokenizeCueLine(line string) []string {
	tokens := []string{}
	sb := strings.Builder{}
	quotes := false
	for _, ch := range strings.TrimSpace(line) {
		if !quotes && unicode.IsSpace(ch) {
			tokens = append(tokens, sb.String())
			sb.Reset()
		} else if ch == '"' {
			if quotes {
				quotes = false
			} else {
				quotes = true
			}
		} else {
			sb.WriteRune(ch)
		}
	}

	if sb.Len() > 0 {
		tokens = append(tokens, sb.String())
	}

	return tokens
}
