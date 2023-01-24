package main

import (
	"fmt"
	"os"

	"github.com/xeeynamo/sotn-decomp/tools/sotn-disk/iso9660"
)

type imageAction func(iso9660.File) error

func printHelp() {
	fmt.Printf("Usage: sotn-disc <command> <sotn.cue> [args]\n\n")
	fmt.Printf("Commands:\n")
	fmt.Printf("  list <sotn.cue>\n")
	fmt.Printf("    dump list of files and directories ordered by how they are stored on disc.\n")
	fmt.Printf("  extract <sotn.cue> <output path>\n")
	fmt.Printf("    extract all the files into the specified path\n")
	//fmt.Printf("  make <sotn.cue> <input path> <file list>\n")
	//fmt.Printf("    creates a PlayStation 1 image given an input path where the game files are located and their order")
}

func main() {
	if len(os.Args) < 3 {
		printHelp()
		return
	}

	var err error
	cmd := os.Args[1]
	cuePath := os.Args[2]
	switch cmd {
	case "list":
		err = performCueAction(cuePath, list)
	case "extract":
		if len(os.Args) < 4 {
			printHelp()
			return
		}
		outPath := os.Args[3]
		err = performCueAction(cuePath, func(f iso9660.File) error {
			return extract(f, outPath)
		})
	case "make":
		if len(os.Args) < 5 {
			printHelp()
			return
		}
		inPath := os.Args[3]
		fileListPath := os.Args[4]
		err = makeDisc(cuePath, inPath, fileListPath)
	default:
		fmt.Printf("Invalid command: %s\n\n", cmd)
		printHelp()
	}

	if err != nil {
		panic(err)
	}
}
