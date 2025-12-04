package deps

import (
	"fmt"
	"os"
	"os/exec"
	"path/filepath"
)

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
