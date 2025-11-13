package main

import (
	"fmt"
	"os"

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

func main() {
	commands := map[string]func(args []string) error{
		"extract":     handlerConfigExtract,
		"build":       handlerConfigBuild,
		"info":        handlerInfo,
		"objdiff-gen": handlerObjdiffGen,
		"objdiff-gui": handleObjdiffGUI,
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
