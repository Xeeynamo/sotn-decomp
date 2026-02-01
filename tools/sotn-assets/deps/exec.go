package deps

import (
	"fmt"
	"os"
	"os/exec"
	"path/filepath"
	"runtime"
	"sync"

	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/sotn"
)

func ClangFormat(files ...string) error {
	binPath := "bin/clang-format"
	if err := downloadTarGzFromGithubIfNotExists("xeeynamo/sotn-decomp", "cc1-psx-26", filepath.Base(binPath), binPath); err != nil {
		return err
	}
	if len(files) == 0 {
		return nil
	}

	// splitting files in equal chunks per CPU has the risk where certain
	// chunks might finish much faster than others. Multiplying the workers
	// by 4 times the CPU will ensure higher degree of parallelism at the
	// cost of a higher memory usage
	numWorkers := runtime.NumCPU() * 4
	if numWorkers > len(files) {
		numWorkers = len(files)
	}

	chunkSize := (len(files) + numWorkers - 1) / numWorkers
	var wg sync.WaitGroup
	errCh := make(chan error, numWorkers)

	for i := 0; i < numWorkers; i++ {
		start := i * chunkSize
		end := start + chunkSize
		if end > len(files) {
			end = len(files)
		}
		if start >= end {
			break
		}

		wg.Add(1)
		go func(chunk []string) {
			defer wg.Done()
			err := (&exec.Cmd{
				Path: binPath,
				Args: append([]string{binPath, "-i"}, chunk...),
			}).Run()
			if err != nil {
				errCh <- err
			}
		}(files[start:end])
	}

	wg.Wait()
	close(errCh)

	for err := range errCh {
		return err
	}
	return nil
}

func ObjdiffCLI(args ...string) error {
	binPath := "bin/objdiff-cli-linux-x86_64"
	if err := downloadFromGithubIfNotExists("encounter/objdiff", "v3.3.1", filepath.Base(binPath), binPath); err != nil {
		return err
	}
	return (&exec.Cmd{
		Path:   binPath,
		Args:   append([]string{binPath}, args...),
		Stdin:  os.Stdin,
		Stdout: os.Stdout,
		Stderr: os.Stderr,
	}).Run()
}

func ObjdiffGUI(args ...string) error {
	binPath := "bin/objdiff-linux-x86_64"
	if err := downloadFromGithubIfNotExists("encounter/objdiff", "v3.3.1", filepath.Base(binPath), binPath); err != nil {
		return err
	}
	cmd := &exec.Cmd{
		Path: binPath,
		Args: []string{binPath, "--project-dir", "."},
	}
	cmdSetDetached(cmd)
	return cmd.Start()
}

func GenNinja(args ...string) error {
	binPath, err := venvPython()
	if err != nil {
		return err
	}
	return (&exec.Cmd{
		Path:   binPath,
		Args:   append([]string{binPath, "tools/builds/gen.py"}, args...),
		Stdin:  os.Stdin,
		Stdout: os.Stdout,
		Stderr: os.Stderr,
	}).Run()
}

func Black(args ...string) error {
	binPath, err := venvPython()
	if err != nil {
		return err
	}
	blackPath, err := pipPackagePath("black")
	if err != nil {
		return err
	}
	return (&exec.Cmd{
		Path: binPath,
		Args: append([]string{binPath, blackPath}, args...),
	}).Run()
}

func Ninja(args ...string) error {
	binPath, err := exec.LookPath("ninja")
	if err != nil {
		return err
	}
	return (&exec.Cmd{
		Path:   binPath,
		Args:   append([]string{binPath}, args...),
		Stdin:  os.Stdin,
		Stdout: os.Stdout,
		Stderr: os.Stderr,
	}).Run()
}

func GenAndRunNinja(args ...string) error {
	if err := GenNinja(); err != nil {
		return err
	}
	if err := Ninja(args...); err != nil {
		return fmt.Errorf("ninja build failed: %w", err)
	}
	return nil
}

func CargoRun(manifest string, args ...string) error {
	binPath, err := exec.LookPath("cargo")
	if err != nil {
		return err
	}
	if _, err := os.Stat(manifest); os.IsNotExist(err) {
		return fmt.Errorf("%s not found", manifest)
	}
	return (&exec.Cmd{
		Path: binPath,
		Args: append([]string{binPath, "run", "--release", "--manifest-path", manifest}, args...),
	}).Run()
}

func SotnLint(args ...string) error {
	return CargoRun("tools/lints/sotn-lint/Cargo.toml", args...)
}

func SymbolsSort(version sotn.Version) error {
	binPath, err := venvPython()
	if err != nil {
		return err
	}
	if _, err := pipPackagePath("pyyaml"); err != nil {
		return err
	}
	cmd := &exec.Cmd{
		Path: binPath,
		Args: []string{binPath, "./tools/symbols.py", "sort"},
		Env:  append(os.Environ(), "VERSION="+string(version)),
	}
	return cmd.Run()
}

func SymbolsClean(version sotn.Version, configPath string) error {
	binPath, err := venvPython()
	if err != nil {
		return err
	}
	cmd := &exec.Cmd{
		Path: binPath,
		Args: []string{binPath, "./tools/symbols.py", "clean", configPath},
		Env:  append(os.Environ(), "VERSION="+string(version)),
	}
	return cmd.Run()
}
