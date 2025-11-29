package deps

import (
	"fmt"
	"os"
	"os/exec"
	"path/filepath"
)

func ObjdiffCLI(args ...string) error {
	path := "bin/objdiff-cli-linux-x86_64"
	if err := downloadFromGithubIfNotExists("encounter/objdiff", "v3.3.1", filepath.Base(path), path); err != nil {
		return err
	}
	return (&exec.Cmd{
		Path:   path,
		Args:   append([]string{path}, args...),
		Stdin:  os.Stdin,
		Stdout: os.Stdout,
		Stderr: os.Stderr,
	}).Run()
}

func ObjdiffGUI(args ...string) error {
	path := "bin/objdiff-linux-x86_64"
	if err := downloadFromGithubIfNotExists("encounter/objdiff", "v3.3.1", filepath.Base(path), path); err != nil {
		return err
	}
	cmd := &exec.Cmd{
		Path: path,
		Args: []string{path, "--project-dir", "."},
	}
	cmdSetDetached(cmd)
	return cmd.Start()
}

func GenNinja(args ...string) error {
	bin, err := venvPython()
	if err != nil {
		return err
	}
	return (&exec.Cmd{
		Path:   bin,
		Args:   append([]string{bin, "tools/builds/gen.py"}, args...),
		Stdin:  os.Stdin,
		Stdout: os.Stdout,
		Stderr: os.Stderr,
	}).Run()
}

func Ninja(args ...string) error {
	return (&exec.Cmd{
		Path:   "/usr/bin/ninja",
		Args:   append([]string{"/usr/bin/ninja"}, args...),
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
