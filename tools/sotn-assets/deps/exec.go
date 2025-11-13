package deps

import (
	"os"
	"os/exec"
	"path/filepath"
)

func ExecObjdiffCLI(args ...string) error {
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

func ExecObjdiffGUI(args ...string) error {
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
