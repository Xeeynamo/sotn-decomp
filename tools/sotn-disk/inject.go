package main

import (
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-disk/iso9660"
	"os"
	"strings"
)

func findFile(f *iso9660.File, basePath, dst, name string) (*iso9660.File, error) {
	if basePath == dst {
		return f, nil
	}
	if f.IsDirectory() {
		children, err := f.GetChildren()
		if err != nil {
			return nil, err
		}
		for _, child := range children[2:] {
			childPath := basePath + "/" + strings.ToLower(child.FileIdentifier)
			if basePath == "/" {
				childPath = "/"
			}
			if f2, err := findFile(&child, childPath, dst, name); err == nil {
				return f2, nil
			}
		}
	}
	return nil, &os.PathError{Op: "find", Path: name, Err: fmt.Errorf("file not found")}
}

func inject(cuePath string, destination string, inputPath string) error {
	return performCueAction(cuePath, func(f iso9660.File) error {
		destination := "/" + strings.ToLower(destination) + ";1"
		found, err := findFile(&f, "", destination, inputPath)
		if err != nil {
			return err
		}
		data, err := os.ReadFile(inputPath)
		if err != nil {
			return err
		}
		return found.WriteFromData(data)
	})
}
