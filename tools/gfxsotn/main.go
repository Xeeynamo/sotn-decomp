package main

import (
	"fmt"
	"image/png"
	"os"
	"sync"

	"github.com/xeeynamo/sotn-decomp/tools/gfxsotn/gfx"
)

func main() {
	args := os.Args
	if len(args) != 3 {
		printHelp()
		return
	}

	fileName := args[1]
	baseOutput := args[2]
	err := convertGfxToPng(fileName, baseOutput)
	if err != nil {
		panic(err)
	}
}

func printHelp() {
	fmt.Printf("Usage: gfxsotn iso/ST/NO3/F_NO3.BIN no3\n")
	fmt.Printf("Convert a stage graphics file into a bunch of PNGs.")
}

func convertGfxToPng(inGfx string, outBase string) error {
	gfxData, err := os.ReadFile(inGfx)
	if err != nil {
		return err
	}

	images, err := gfx.GetGfxAsImages(gfxData)
	if err != nil {
		return err
	}

	wc := sync.WaitGroup{}
	wc.Add(len(images))
	var lastErr error = nil
	for i := 0; i < len(images); i++ {
		go func(index int) {
			defer wc.Done()
			imgInfo := images[index]
			fileName := fmt.Sprintf("%s_%d_%d.png", outBase, imgInfo.Clut, imgInfo.Partition)
			outFile, err := os.Create(fileName)
			if err != nil {
				lastErr = err // hack-y way to check errors in go routines
				return
			}
			defer outFile.Close()
			png.Encode(outFile, imgInfo.Img)
		}(i)
	}
	wc.Wait()

	return lastErr
}
