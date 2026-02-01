package format

import (
	"bufio"
	"fmt"
	"os"
	"path/filepath"
	"regexp"
	"strings"
	"sync"
	"time"

	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/deps"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/sotn"
	"golang.org/x/sync/errgroup"
)

type task struct {
	msg string
	fn  func() error
}

type taskResult struct {
	index    int
	err      error
	duration time.Duration
}

func Format() error {
	tasks := []task{
		{"Formatting C", formatCSource},
		{"Linting C", lintCSource},
		{"Formatting Python", formatPythonTools},
		{"Formatting Splat Symbols", formatSplatSymbols},
		{"Formatting License", formatLicense},
	}
	for _, t := range tasks {
		fmt.Printf("%s...\n", t.msg)
	}
	results := make(chan taskResult, len(tasks))
	var wg sync.WaitGroup
	var mu sync.Mutex

	for i, t := range tasks {
		wg.Add(1)
		go func(idx int, task task) {
			defer wg.Done()
			start := time.Now()
			err := task.fn()
			results <- taskResult{idx, err, time.Since(start)}
		}(i, t)
	}

	go func() {
		wg.Wait()
		close(results)
	}()

	var firstErr error
	for result := range results {
		mu.Lock()
		updateLine(len(tasks), result.index, tasks[result.index].msg, result.err, result.duration)
		if result.err != nil && firstErr == nil {
			firstErr = result.err
		}
		mu.Unlock()
	}

	return firstErr
}

func updateLine(total, index int, message string, err error, duration time.Duration) {
	linesToMoveUp := total - index
	fmt.Printf("\033[%dA\r\033[K", linesToMoveUp) // Move up and clear line

	if err != nil {
		fmt.Printf("%s... Error: %v (%.1fs)", message, err, duration.Seconds())
	} else {
		fmt.Printf("%s... OK (%.1fs)", message, duration.Seconds())
	}

	fmt.Printf("\033[%dB\r", linesToMoveUp) // Move back down
}

func formatCSource() error {
	var files []string
	excludeDirs := map[string]bool{
		"3rd":        true,
		"pspsdk":     true,
		"psxsdk":     true,
		"CMakeFiles": true,
		"gen":        true,
	}
	walkFn := func(path string, d os.DirEntry, err error) error {
		if err != nil {
			return err
		}
		if d.IsDir() {
			if excludeDirs[d.Name()] {
				return filepath.SkipDir
			}
			return nil
		}
		ext := filepath.Ext(path)
		if ext == ".c" || ext == ".h" {
			files = append(files, path)
		}
		return nil
	}
	for _, dir := range []string{"src", "include", "mods"} {
		if err := filepath.WalkDir(dir, walkFn); err != nil {
			if os.IsNotExist(err) {
				continue
			}
			return fmt.Errorf("walking %s: %w", dir, err)
		}
	}
	if len(files) == 0 {
		return nil
	}
	return deps.ClangFormat(files...)
}

func lintCSource() error {
	return deps.SotnLint("src/")
}

func formatPythonTools() error {
	var files []string
	for _, pattern := range []string{
		"tools/*.py",
		"tools/builds/gen.py",
		"tools/splat_ext/*.py",
		"tools/split_jpt_yaml/*.py",
		"tools/sotn_permuter/permuter_loader.py",
		"diff_settings.py",
		"tools/function_finder/*.py",
	} {
		matches, err := filepath.Glob(pattern)
		if err != nil {
			return fmt.Errorf("glob %s: %w", pattern, err)
		}
		files = append(files, matches...)
	}
	if len(files) == 0 {
		return nil
	}
	return deps.Black(files...)
}

func formatSplatSymbols() error {
	eg := errgroup.Group{}
	for _, version := range sotn.VersionsAll {
		ver := version
		eg.Go(func() error {
			if err := deps.SymbolsSort(ver); err != nil {
				return fmt.Errorf("symbols sort for %s: %w", ver, err)
			}
			pattern := fmt.Sprintf("config/splat.%s.*.yaml", ver)
			configs, err := filepath.Glob(pattern)
			if err != nil {
				return fmt.Errorf("glob %s: %w", pattern, err)
			}
			for _, config := range configs {
				if err := deps.SymbolsClean(ver, config); err != nil {
					return fmt.Errorf("symbols clean %s: %w", config, err)
				}
			}
			return nil
		})
	}
	return eg.Wait()
}

func formatLicense() error {
	agplFiles, err := collectLicenseFiles(
		[]string{"src", "mods"},
		[]string{"PsyCross", "mednafen", "psxsdk", "pspsdk", "3rd", "saturn/lib"},
	)
	if err != nil {
		return fmt.Errorf("collecting AGPL files: %w", err)
	}
	for _, f := range agplFiles {
		if err := addSPDXLicense(f, "AGPL-3.0-or-later"); err != nil {
			return err
		}
	}

	mitFiles, err := collectLicenseFiles([]string{"src/main/psxsdk"}, nil)
	if err != nil {
		return fmt.Errorf("collecting MIT files: %w", err)
	}
	for _, f := range mitFiles {
		if err := addSPDXLicense(f, "MIT"); err != nil {
			return err
		}
	}

	includeFiles := []string{
		"include/game.h",
		"include/entity.h",
		"include/items.h",
		"include/lba.h",
		"include/memcard.h",
	}
	for _, f := range includeFiles {
		if _, err := os.Stat(f); err == nil {
			if err := addSPDXLicense(f, "AGPL-3.0-or-later"); err != nil {
				return err
			}
		}
	}

	return nil
}

func collectLicenseFiles(dirs []string, excludePatterns []string) ([]string, error) {
	var files []string
	var excludeRegex *regexp.Regexp
	if len(excludePatterns) > 0 {
		excludeRegex = regexp.MustCompile(strings.Join(excludePatterns, "|"))
	}

	for _, dir := range dirs {
		err := filepath.WalkDir(dir, func(path string, d os.DirEntry, err error) error {
			if err != nil {
				return err
			}
			if d.IsDir() {
				return nil
			}
			ext := filepath.Ext(path)
			if ext != ".c" && ext != ".h" {
				return nil
			}
			if excludeRegex != nil && excludeRegex.MatchString(path) {
				return nil
			}
			files = append(files, path)
			return nil
		})
		if err != nil {
			if os.IsNotExist(err) {
				continue
			}
			return nil, fmt.Errorf("walking %s: %w", dir, err)
		}
	}

	return files, nil
}

func addSPDXLicense(filePath, license string) error {
	spdxLine := fmt.Sprintf("// SPDX-License-Identifier: %s", license)

	file, err := os.Open(filePath)
	if err != nil {
		fmt.Printf("the file %s does not exist\n", filePath)
		return nil
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	var lines []string
	for scanner.Scan() {
		lines = append(lines, scanner.Text())
	}
	if err := scanner.Err(); err != nil {
		return fmt.Errorf("reading %s: %w", filePath, err)
	}

	if len(lines) > 0 && strings.TrimSpace(lines[0]) == spdxLine {
		return nil
	}

	out, err := os.Create(filePath)
	if err != nil {
		return fmt.Errorf("creating %s: %w", filePath, err)
	}
	defer out.Close()

	if _, err := fmt.Fprintln(out, spdxLine); err != nil {
		return fmt.Errorf("writing header to %s: %w", filePath, err)
	}
	for _, line := range lines {
		if _, err := fmt.Fprintln(out, line); err != nil {
			return fmt.Errorf("writing to %s: %w", filePath, err)
		}
	}

	return nil
}
