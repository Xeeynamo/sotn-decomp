package main

import (
	"fmt"
	"os"
	"path"

	"github.com/xeeynamo/sotn-decomp/tools/sotn-disk/iso9660"
)

func extract(f iso9660.File, basePath string) error {
	if _, err := os.Stat(basePath); os.IsNotExist(err) {
		if err := os.Mkdir(basePath, 0744); err != nil {
			return err
		}
	}

	children, err := f.GetChildren()
	if err != nil {
		return err
	}

	for _, child := range children[2:] {
		outPath := path.Join(basePath, child.FileIdentifier)
		if child.IsDirectory() {
			if err = extract(child, outPath); err != nil {
				return err
			}
		} else {
			outFilePath := outPath[:len(outPath)-2]
			fmt.Printf("%s\n", outFilePath)

			f, err := os.Create(outFilePath)
			if err != nil {
				return err
			}
			defer f.Close()

			if err := child.WriteFile(f); err != nil {
				return err
			}
		}
	}

	return nil
}
