package main

import (
	"fmt"
	"os"
	"os/exec"
	"path/filepath"
	"runtime"
	"strings"
	"syscall"

	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/dependency"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/util"
)

func handlerConfigExtract(args []string) error {
	if len(args) != 1 {
		return fmt.Errorf("usage: sotn-assets extract <asset_config_path>")
	}
	c, err := readConfig(args[0])
	if err != nil {
		return err
	}
	if c.Version != "" {
		_ = os.Setenv("VERSION", c.Version)
	}
	return extractFromConfig(c)
}

func handlerConfigBuild(args []string) error {
	if len(args) != 1 {
		return fmt.Errorf("usage: sotn-assets build <asset_config_path>")
	}
	c, err := readConfig(args[0])
	if err != nil {
		return err
	}
	if c.Version != "" {
		_ = os.Setenv("VERSION", c.Version)
	}
	return buildFromConfig(c)
}

func handlerInfo(args []string) error {
	if len(args) != 1 {
		return fmt.Errorf("usage: sotn-assets info <stage_file_path>")
	}
	return info(os.Stdout, args[0])
}

func handlerObjdiffGen(_ []string) error {
	if os.Getenv("VERSION") == "" {
		return fmt.Errorf("VERSION not set")
	}
	configPath := fmt.Sprintf("config/assets.%s.yaml", os.Getenv("VERSION"))
	return objdiffgen(configPath)
}

func handlerObjdiffGUI(args []string) error {
	if os.Getenv("VERSION") == "" {
		return fmt.Errorf("VERSION not set")
	}
	configPath := fmt.Sprintf("config/assets.%s.yaml", os.Getenv("VERSION"))
	if err := objdiffgen(configPath); err != nil {
		return err
	}
	path := "bin/objdiff-linux-x86_64"
	if err := dependency.DownloadFromGithubIfNotExists("encounter/objdiff", "v3.3.1", filepath.Base(path), path); err != nil {
		return err
	}
	if runtime.GOOS == "windows" {
		return (&exec.Cmd{
			Path: path,
			Args: []string{path, "--project-dir", "."},
			SysProcAttr: &syscall.SysProcAttr{
				CreationFlags: syscall.CREATE_NEW_PROCESS_GROUP | syscall.DETACHED_PROCESS,
			},
		}).Start()
	} else {
		return (&exec.Cmd{
			Path: path,
			Args: []string{path, "--project-dir", "."},
			SysProcAttr: &syscall.SysProcAttr{
				Setsid: true, // Start a new session (detach from parent)
			},
		}).Start()
	}
}

func handlerObjdiffCLI(args []string) error {
	if os.Getenv("VERSION") == "" {
		return fmt.Errorf("VERSION not set")
	}
	configPath := fmt.Sprintf("config/assets.%s.yaml", os.Getenv("VERSION"))
	if err := objdiffgen(configPath); err != nil {
		return err
	}
	path := "bin/objdiff-cli-linux-x86_64"
	if err := dependency.DownloadFromGithubIfNotExists("encounter/objdiff", "v3.3.1", filepath.Base(path), path); err != nil {
		return err
	}

	if len(args) < 2 {
		return fmt.Errorf("usage: sotn-assets objdiff <src_path> <symbol>\n\t(e.g. objdiff dra/4A538 func_800EAD0C)")
	}
	srcPath := args[0]
	symbol := args[1]
	if !strings.HasSuffix(path, ".c") {
		srcPath += ".c"
	}
	if !strings.HasPrefix(path, "src/") {
		srcPath = "src/" + srcPath
	}
	basePath := filepath.Join("build", "us", srcPath+".o")
	targetPath := filepath.Join("expected", basePath)
	return (&exec.Cmd{
		Path:   path,
		Args:   []string{path, "diff", "-1", basePath, "-2", targetPath, symbol},
		Stdin:  os.Stdin,
		Stdout: os.Stdout,
		Stderr: os.Stderr,
	}).Run()
}

func main() {
	commands := map[string]func(args []string) error{
		"extract":     handlerConfigExtract,
		"build":       handlerConfigBuild,
		"info":        handlerInfo,
		"objdiff-gen": handlerObjdiffGen,
		"objdiff-gui": handlerObjdiffGUI,
		"objdiff":     handlerObjdiffCLI,
	}

	args := os.Args[1:]
	if len(args) > 0 {
		command := args[0]
		if f, found := commands[command]; found {
			if err := f(args[1:]); err != nil {
				_, _ = fmt.Fprintln(os.Stderr, err)
				os.Exit(1)
			}
			return
		}
		fmt.Fprintf(os.Stderr, "unknown command %q. Valid commands are %s\n", command, util.JoinMapKeys(commands, ", "))
	} else {
		fmt.Fprintf(os.Stderr, "Need a command. Valid commands are %s\n", util.JoinMapKeys(commands, ", "))
	}
	os.Exit(1)
}
