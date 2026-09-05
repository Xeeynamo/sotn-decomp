package util

import (
	"fmt"
	"io/fs"
	"os"
	"path/filepath"
)

// MirrorDir makes dst an exact copy of src while touching as little as
// possible: files whose size and mtime already match src are left alone, and
// anything in dst with no counterpart in src is removed.
func MirrorDir(src, dst string) error {
	srcInfo, err := os.Stat(src)
	if err != nil {
		return fmt.Errorf("stat %s: %w", src, err)
	}
	if !srcInfo.IsDir() {
		return fmt.Errorf("%s is not a directory", src)
	}

	wanted := map[string]bool{}
	err = filepath.WalkDir(src, func(path string, d fs.DirEntry, err error) error {
		if err != nil {
			return err
		}
		rel, err := filepath.Rel(src, path)
		if err != nil {
			return err
		}
		if rel != "." {
			wanted[rel] = true
		}
		target := filepath.Join(dst, rel)

		if d.IsDir() {
			return os.MkdirAll(target, 0755)
		}
		info, err := d.Info()
		if err != nil {
			return err
		}
		if !info.Mode().IsRegular() {
			// The build tree holds only directories and regular files.
			return fmt.Errorf("%s is neither a regular file nor a directory", path)
		}
		// Skip anything already mirrored, comparing size and mtime the way
		// rsync does instead of re-reading the contents.
		if cur, err := os.Stat(target); err == nil &&
			cur.Mode().IsRegular() &&
			cur.Size() == info.Size() &&
			cur.ModTime().Equal(info.ModTime()) {
			return nil
		}
		data, err := os.ReadFile(path)
		if err != nil {
			return err
		}
		if err := os.WriteFile(target, data, info.Mode()); err != nil {
			return err
		}
		// Carry the source mtime over so the next run can skip this file.
		return os.Chtimes(target, info.ModTime(), info.ModTime())
	})
	if err != nil {
		return fmt.Errorf("mirror %s to %s: %w", src, dst, err)
	}

	// Delete anything in dst that src no longer has.
	var stale []string
	err = filepath.WalkDir(dst, func(path string, d fs.DirEntry, err error) error {
		if err != nil {
			if os.IsNotExist(err) {
				return nil
			}
			return err
		}
		rel, err := filepath.Rel(dst, path)
		if err != nil {
			return err
		}
		if rel == "." || wanted[rel] {
			return nil
		}
		stale = append(stale, path)
		if d.IsDir() {
			return filepath.SkipDir
		}
		return nil
	})
	if err != nil {
		return fmt.Errorf("scan %s for stale entries: %w", dst, err)
	}
	for _, path := range stale {
		if err := os.RemoveAll(path); err != nil {
			return fmt.Errorf("remove stale %s: %w", path, err)
		}
	}
	return nil
}
