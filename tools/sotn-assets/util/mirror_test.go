package util

import (
	"os"
	"path/filepath"
	"sort"
	"strings"
	"testing"
	"time"
)

func mustWrite(t *testing.T, path, content string, mode os.FileMode) {
	t.Helper()
	if err := os.MkdirAll(filepath.Dir(path), 0755); err != nil {
		t.Fatal(err)
	}
	if err := os.WriteFile(path, []byte(content), mode); err != nil {
		t.Fatal(err)
	}
}

// treeOf lists every entry under root as "relpath" for directories and
// "relpath=content" for files, so two trees can be compared directly.
func treeOf(t *testing.T, root string) []string {
	t.Helper()
	var out []string
	err := filepath.Walk(root, func(path string, info os.FileInfo, err error) error {
		if err != nil {
			return err
		}
		rel, err := filepath.Rel(root, path)
		if err != nil {
			return err
		}
		if rel == "." {
			return nil
		}
		if info.IsDir() {
			out = append(out, rel+"/")
			return nil
		}
		data, err := os.ReadFile(path)
		if err != nil {
			return err
		}
		out = append(out, rel+"="+string(data))
		return nil
	})
	if err != nil {
		t.Fatalf("walk %s: %v", root, err)
	}
	sort.Strings(out)
	return out
}

func TestMirrorDirCreatesAnExactCopy(t *testing.T) {
	dir := t.TempDir()
	src := filepath.Join(dir, "src")
	dst := filepath.Join(dir, "dst")

	mustWrite(t, filepath.Join(src, "a.bin"), "aaa", 0644)
	mustWrite(t, filepath.Join(src, "sub", "b.bin"), "bbb", 0644)
	mustWrite(t, filepath.Join(src, "sub", "deep", "c.bin"), "ccc", 0755)

	if err := MirrorDir(src, dst); err != nil {
		t.Fatalf("MirrorDir: %v", err)
	}

	got, want := treeOf(t, dst), treeOf(t, src)
	if strings.Join(got, "\n") != strings.Join(want, "\n") {
		t.Fatalf("tree mismatch:\ngot  %v\nwant %v", got, want)
	}
}

// The whole point of the mirror: a second run over an unchanged tree must not
// rewrite anything.
func TestMirrorDirLeavesUnchangedFilesAlone(t *testing.T) {
	dir := t.TempDir()
	src := filepath.Join(dir, "src")
	dst := filepath.Join(dir, "dst")

	mustWrite(t, filepath.Join(src, "a.bin"), "aaa", 0644)
	mustWrite(t, filepath.Join(src, "sub", "b.bin"), "bbb", 0644)
	if err := MirrorDir(src, dst); err != nil {
		t.Fatalf("first MirrorDir: %v", err)
	}

	targets := []string{
		filepath.Join(dst, "a.bin"),
		filepath.Join(dst, "sub", "b.bin"),
	}
	before := map[string]time.Time{}
	for _, p := range targets {
		info, err := os.Stat(p)
		if err != nil {
			t.Fatal(err)
		}
		before[p] = info.ModTime()
	}

	if err := MirrorDir(src, dst); err != nil {
		t.Fatalf("second MirrorDir: %v", err)
	}

	for _, p := range targets {
		info, err := os.Stat(p)
		if err != nil {
			t.Fatal(err)
		}
		if !info.ModTime().Equal(before[p]) {
			t.Fatalf("%s was rewritten despite being up to date", p)
		}
	}
}

func TestMirrorDirUpdatesChangedFiles(t *testing.T) {
	dir := t.TempDir()
	src := filepath.Join(dir, "src")
	dst := filepath.Join(dir, "dst")

	mustWrite(t, filepath.Join(src, "a.bin"), "original", 0644)
	if err := MirrorDir(src, dst); err != nil {
		t.Fatal(err)
	}
	mustWrite(t, filepath.Join(src, "a.bin"), "updated", 0644)
	if err := MirrorDir(src, dst); err != nil {
		t.Fatal(err)
	}

	got, err := os.ReadFile(filepath.Join(dst, "a.bin"))
	if err != nil {
		t.Fatal(err)
	}
	if string(got) != "updated" {
		t.Fatalf("content = %q, want %q", got, "updated")
	}
}

// Same size but different bytes: caught by the mtime half of the check.
func TestMirrorDirDetectsSameSizeDifferentContent(t *testing.T) {
	dir := t.TempDir()
	src := filepath.Join(dir, "src")
	dst := filepath.Join(dir, "dst")

	srcFile := filepath.Join(src, "a.bin")
	mustWrite(t, srcFile, "aaaa", 0644)
	if err := MirrorDir(src, dst); err != nil {
		t.Fatal(err)
	}
	mustWrite(t, srcFile, "aaab", 0644)
	// Rewrites can land inside the same filesystem timestamp tick, so make the
	// mtime difference explicit.
	newer := time.Now().Add(time.Hour)
	if err := os.Chtimes(srcFile, newer, newer); err != nil {
		t.Fatal(err)
	}
	if err := MirrorDir(src, dst); err != nil {
		t.Fatal(err)
	}

	got, err := os.ReadFile(filepath.Join(dst, "a.bin"))
	if err != nil {
		t.Fatal(err)
	}
	if string(got) != "aaab" {
		t.Fatalf("content = %q, want %q", got, "aaab")
	}
}

func TestMirrorDirRemovesStaleEntries(t *testing.T) {
	dir := t.TempDir()
	src := filepath.Join(dir, "src")
	dst := filepath.Join(dir, "dst")

	mustWrite(t, filepath.Join(src, "keep.bin"), "keep", 0644)
	mustWrite(t, filepath.Join(src, "gone.bin"), "gone", 0644)
	mustWrite(t, filepath.Join(src, "olddir", "nested", "x.bin"), "x", 0644)
	if err := MirrorDir(src, dst); err != nil {
		t.Fatal(err)
	}

	if err := os.Remove(filepath.Join(src, "gone.bin")); err != nil {
		t.Fatal(err)
	}
	if err := os.RemoveAll(filepath.Join(src, "olddir")); err != nil {
		t.Fatal(err)
	}
	if err := MirrorDir(src, dst); err != nil {
		t.Fatal(err)
	}

	got, want := treeOf(t, dst), treeOf(t, src)
	if strings.Join(got, "\n") != strings.Join(want, "\n") {
		t.Fatalf("stale entries survived:\ngot  %v\nwant %v", got, want)
	}
	if _, err := os.Stat(filepath.Join(dst, "olddir")); !os.IsNotExist(err) {
		t.Fatal("stale directory olddir was not removed")
	}
}

func TestMirrorDirPreservesMode(t *testing.T) {
	dir := t.TempDir()
	src := filepath.Join(dir, "src")
	dst := filepath.Join(dir, "dst")

	mustWrite(t, filepath.Join(src, "tool"), "#!/bin/sh\n", 0755)
	mustWrite(t, filepath.Join(src, "data"), "data", 0644)
	if err := MirrorDir(src, dst); err != nil {
		t.Fatal(err)
	}

	for name, want := range map[string]os.FileMode{"tool": 0755, "data": 0644} {
		info, err := os.Stat(filepath.Join(dst, name))
		if err != nil {
			t.Fatal(err)
		}
		if info.Mode().Perm() != want {
			t.Fatalf("%s mode = %v, want %v", name, info.Mode().Perm(), want)
		}
	}
}

func TestMirrorDirRejectsMissingSource(t *testing.T) {
	dir := t.TempDir()
	if err := MirrorDir(filepath.Join(dir, "absent"), filepath.Join(dir, "dst")); err == nil {
		t.Fatal("expected an error for a missing source directory")
	}
}
