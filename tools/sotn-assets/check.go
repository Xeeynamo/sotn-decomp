package main

import (
	"bufio"
	"crypto/sha1"
	"encoding/hex"
	"fmt"
	"io"
	"os"
	"path/filepath"
	"strings"
)

var sha1sumCheck = func(path string, expectedSum string) bool {
	f, err := os.Open(path)
	if err != nil {
		return false
	}
	defer f.Close()
	h := sha1.New()
	if _, err := io.Copy(h, f); err != nil {
		return false
	}
	return strings.EqualFold(hex.EncodeToString(h.Sum(nil)), expectedSum)
}

func checkVersions(w io.Writer, versions []string) error {
	type result struct {
		version string
		entries []checkEntry
		allOK   bool
	}
	var results []result
	for _, v := range versions {
		entries, err := readCheckFile(v)
		if err != nil {
			return err
		}
		allOK := true
		for i := range entries {
			entries[i].ok = sha1sumCheck(entries[i].path, entries[i].sum)
			if !entries[i].ok {
				allOK = false
			}
		}
		results = append(results, result{version: v, entries: entries, allOK: allOK})
	}

	var okVersions []string
	var failing []result
	for _, r := range results {
		if r.allOK {
			okVersions = append(okVersions, r.version)
		} else {
			failing = append(failing, r)
		}
	}

	headerWritten := false
	if len(okVersions) > 0 {
		maxLen := 0
		for _, r := range results {
			if len(r.version) > maxLen {
				maxLen = len(r.version)
			}
		}
		parts := make([]string, len(okVersions))
		for i, v := range okVersions {
			if i == len(okVersions)-1 {
				parts[i] = "✅ " + v
			} else {
				parts[i] = "✅ " + v + strings.Repeat(" ", maxLen-len(v))
			}
		}
		if _, err := fmt.Fprint(w, strings.Join(parts, "  ")); err != nil {
			return err
		}
		headerWritten = true
	}
	for i, r := range failing {
		if headerWritten || i > 0 {
			if _, err := fmt.Fprint(w, "\n"); err != nil {
				return err
			}
		}
		if err := writeFailingBlock(w, r.version, r.entries); err != nil {
			return err
		}
	}
	_, _ = w.Write([]byte("\n"))
	return nil
}

type checkEntry struct {
	name string
	path string
	sum  string
	ok   bool
}

func readCheckFile(version string) ([]checkEntry, error) {
	f, err := os.Open(filepath.Join("config", fmt.Sprintf("check.%s.sha", version)))
	if err != nil {
		if os.IsNotExist(err) {
			return nil, nil
		}
		return nil, err
	}
	defer f.Close()
	var entries []checkEntry
	s := bufio.NewScanner(f)
	for s.Scan() {
		line := strings.TrimSpace(s.Text())
		if line == "" || strings.HasPrefix(line, "#") {
			continue
		}
		parts := strings.Fields(line)
		if len(parts) < 2 {
			continue
		}
		sum := parts[0]
		path := strings.Join(parts[1:], " ")
		label := strings.TrimSuffix(filepath.Base(path), filepath.Ext(path))
		entries = append(entries, checkEntry{name: label, path: path, sum: sum})
	}
	return entries, s.Err()
}

func writeFailingBlock(w io.Writer, version string, entries []checkEntry) error {
	const gridWidth = 60
	if _, err := fmt.Fprintf(w, "⚠️ %s\n", version); err != nil {
		return err
	}
	maxLen := 0
	for _, e := range entries {
		if len(e.name) > maxLen {
			maxLen = len(e.name)
		}
	}
	slot := maxLen + 4
	perLine := gridWidth / slot
	if perLine < 1 {
		perLine = 1
	}

	var b strings.Builder
	b.WriteString("  ")
	for i, e := range entries {
		emoji := "✅"
		if !e.ok {
			emoji = "❌"
		}
		b.WriteString(emoji)
		b.WriteString(" ")
		b.WriteString(e.name)
		atLineEnd := (i+1)%perLine == 0
		isLast := i == len(entries)-1
		if atLineEnd && !isLast {
			b.WriteString("\n  ")
		} else {
			b.WriteString(strings.Repeat(" ", maxLen-len(e.name)))
			b.WriteString("  ")
		}
	}
	_, err := fmt.Fprint(w, b.String())
	return err
}
