package util

import (
	"os"
	"path/filepath"
	"testing"
	"time"
)

func writeAtomically(t *testing.T, path, content string) {
	t.Helper()
	w, err := CreateAtomicWriter(path)
	if err != nil {
		t.Fatalf("CreateAtomicWriter: %v", err)
	}
	if _, err := w.WriteString(content); err != nil {
		t.Fatalf("WriteString: %v", err)
	}
	if err := w.Close(); err != nil {
		t.Fatalf("Close: %v", err)
	}
}

func mtimeOf(t *testing.T, path string) time.Time {
	t.Helper()
	info, err := os.Stat(path)
	if err != nil {
		t.Fatalf("stat %s: %v", path, err)
	}
	return info.ModTime()
}

func TestAtomicWriterCreatesFile(t *testing.T) {
	path := filepath.Join(t.TempDir(), "nested", "asset.bin")
	writeAtomically(t, path, "hello")

	got, err := os.ReadFile(path)
	if err != nil {
		t.Fatalf("read: %v", err)
	}
	if string(got) != "hello" {
		t.Fatalf("content = %q, want %q", got, "hello")
	}
}

func TestAtomicWriterKeepsMtimeWhenContentIsUnchanged(t *testing.T) {
	path := filepath.Join(t.TempDir(), "asset.bin")
	writeAtomically(t, path, "unchanged payload")

	// Backdate the file so any rewrite is unmistakable.
	old := time.Now().Add(-time.Hour).Truncate(time.Second)
	if err := os.Chtimes(path, old, old); err != nil {
		t.Fatalf("chtimes: %v", err)
	}

	writeAtomically(t, path, "unchanged payload")

	if got := mtimeOf(t, path); !got.Equal(old) {
		t.Fatalf("mtime changed for identical content: %v -> %v", old, got)
	}
	got, err := os.ReadFile(path)
	if err != nil {
		t.Fatalf("read: %v", err)
	}
	if string(got) != "unchanged payload" {
		t.Fatalf("content = %q", got)
	}
}

func TestAtomicWriterRewritesWhenContentDiffers(t *testing.T) {
	dir := t.TempDir()
	for _, tc := range []struct {
		name  string
		first string
		next  string
	}{
		{"same length", "aaaa", "aaab"},
		{"longer", "aaaa", "aaaaa"},
		{"shorter", "aaaa", "aaa"},
		{"emptied", "aaaa", ""},
	} {
		t.Run(tc.name, func(t *testing.T) {
			path := filepath.Join(dir, tc.name)
			writeAtomically(t, path, tc.first)
			old := time.Now().Add(-time.Hour).Truncate(time.Second)
			if err := os.Chtimes(path, old, old); err != nil {
				t.Fatalf("chtimes: %v", err)
			}

			writeAtomically(t, path, tc.next)

			got, err := os.ReadFile(path)
			if err != nil {
				t.Fatalf("read: %v", err)
			}
			if string(got) != tc.next {
				t.Fatalf("content = %q, want %q", got, tc.next)
			}
			if mtimeOf(t, path).Equal(old) {
				t.Fatal("mtime was not updated even though content changed")
			}
		})
	}
}

func TestAtomicWriterHandlesLargeFiles(t *testing.T) {
	path := filepath.Join(t.TempDir(), "large.bin")
	payload := make([]byte, 64*1024*3+7)
	for i := range payload {
		payload[i] = byte(i)
	}

	writeAtomically(t, path, string(payload))
	old := time.Now().Add(-time.Hour).Truncate(time.Second)
	if err := os.Chtimes(path, old, old); err != nil {
		t.Fatalf("chtimes: %v", err)
	}

	writeAtomically(t, path, string(payload))
	if got := mtimeOf(t, path); !got.Equal(old) {
		t.Fatalf("large identical file was rewritten: %v -> %v", old, got)
	}

	// A difference in the final partial chunk must still be detected.
	payload[len(payload)-1] ^= 0xff
	writeAtomically(t, path, string(payload))
	if mtimeOf(t, path).Equal(old) {
		t.Fatal("difference in the trailing chunk was missed")
	}
}

func TestAtomicWriterLeavesNoTempFiles(t *testing.T) {
	dir := t.TempDir()
	path := filepath.Join(dir, "asset.bin")
	writeAtomically(t, path, "payload")
	writeAtomically(t, path, "payload") // identical, takes the skip path
	writeAtomically(t, path, "other")   // different, takes the rename path

	entries, err := os.ReadDir(dir)
	if err != nil {
		t.Fatalf("readdir: %v", err)
	}
	if len(entries) != 1 || entries[0].Name() != "asset.bin" {
		names := make([]string, len(entries))
		for i, e := range entries {
			names[i] = e.Name()
		}
		t.Fatalf("temp files left behind: %v", names)
	}
}
