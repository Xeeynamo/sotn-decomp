package mods

import (
	"fmt"
	"io"
	"os"
	"path/filepath"
	"strings"
	"time"

	"github.com/xeeynamo/sotn-decomp/tools/sotn-disk/discs"
	"golang.org/x/exp/rand"
)

func cp(dst, src string) error {
	if err := os.MkdirAll(filepath.Dir(dst), 0755); err != nil {
		return err
	}
	in, err := os.Open(src)
	if err != nil {
		return err
	}
	defer in.Close()
	out, err := os.Create(dst)
	if err != nil {
		return err
	}
	_, err = io.Copy(out, in)
	if err != nil {
		out.Close()
		return err
	}
	return out.Close()

}

func prepareDisk(newDiskPath, originDiskPath, buildPath string, fileListPath string) error {
	meta, err := discs.ReadFileList(fileListPath)
	if err != nil {
		return err
	}
	overrides := map[string]string{
		"SLUS_000.67": "main.exe",
	}
	for _, entry := range meta {
		if len(entry.Name) == 0 {
			continue
		}
		entryName := entry.Name
		if strings.HasSuffix(entryName, ";1") {
			entryName = entryName[:len(entryName)-2]
		}
		destPath := filepath.Join(newDiskPath, entryName)
		baseName := filepath.Base(entryName)
		if mappedName, ok := overrides[baseName]; ok {
			baseName = mappedName
		}

		found := false
		for _, src := range []string{
			filepath.Join(buildPath, baseName),
			filepath.Join(originDiskPath, entryName),
		} {
			if s, err := os.Stat(src); err == nil {
				if s.IsDir() {
					found = true
					break
				}
				if err := cp(destPath, src); err != nil {
					return fmt.Errorf("failed to copy %s: %w", src, err)
				}
				found = true
				break
			}
		}
		if !found {
			return fmt.Errorf("file %s not found", entryName)
		}
	}
	return nil
}

func MakeDisk(outputFileName, buildPath, originPath, fileListPath string, dryrun bool) error {
	rand.Seed(uint64(time.Now().Unix()))
	newDiskPath := filepath.Join(os.TempDir(), fmt.Sprintf("sotn-disk-%d", rand.Int()))
	if err := os.Mkdir(newDiskPath, 0770); err != nil {
		return err
	}
	defer os.RemoveAll(newDiskPath)
	if err := prepareDisk(newDiskPath, originPath, buildPath, fileListPath); err != nil {
		return err
	}

	if dryrun {
		img, err := discs.MakeDiskDryRun(newDiskPath, fileListPath)
		if err != nil {
			return err
		}
		return GenerateLbaHeader(img, os.Stdout)
	}

	if !strings.HasSuffix(outputFileName, ".cue") {
		return fmt.Errorf("output file name must end with .cue")
	}
	if err := discs.MakeDisk(outputFileName, newDiskPath, fileListPath); err != nil {
		return err
	}
	return nil
}
