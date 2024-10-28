package main

import (
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/util"
	"os"
)

func handlerConfigExtract(args []string) error {
	c, err := readConfig(args[0])
	if err != nil {
		return err
	}
	return extractFromConfig(c)
}

func handlerConfigBuild(args []string) error {
	c, err := readConfig(args[0])
	if err != nil {
		return err
	}
	return buildFromConfig(c)
}

func handlerConfig(args []string) error {
	commands := map[string]func(args []string) error{
		"extract": handlerConfigExtract,
		"build":   handlerConfigBuild,
	}

	if len(args) > 0 {
		command := args[0]
		if f, found := commands[command]; found {
			if err := f(args[1:]); err != nil {
				fmt.Fprintln(os.Stderr, err)
				os.Exit(1)
			}
			return nil
		}
		fmt.Fprintf(os.Stderr, "unknown subcommand %q. Valid subcommand are %s\n", command, util.JoinMapKeys(commands, ", "))
	} else {
		fmt.Fprintf(os.Stderr, "Need a subcommand. Valid subcommand are %s\n", util.JoinMapKeys(commands, ", "))
	}
	os.Exit(1)
	return nil
}

func main() {
	commands := map[string]func(args []string) error{
		"config": handlerConfig,
		"info":   handlerInfo,
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
