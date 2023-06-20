package sotn

import (
	"os"
	"path"
	"strings"
)

func GetStageTileset(name string, gfxPath string) ([]string, error) {
	fileNames := make([]string, 0)

	dir, err := os.ReadDir(gfxPath)
	if err != nil {
		return nil, err
	}

	for _, v := range dir {
		if v.IsDir() {
			continue
		}

		fileName := v.Name()
		if strings.HasPrefix(fileName, name) &&
			strings.HasSuffix(fileName, ".png") &&
			!strings.Contains(fileName, "clut") {
			fileNames = append(fileNames, path.Join(gfxPath, fileName))
		}
	}

	return fileNames, nil
}
