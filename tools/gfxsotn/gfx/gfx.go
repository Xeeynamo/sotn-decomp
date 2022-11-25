package gfx

import (
	"fmt"
	"image"
	"image/color"
)

var DefaultConfig = []int{3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 8}

type ImageInfo struct {
	Img       *image.Paletted
	Partition int
	Clut      int
}

type paletteInfo struct {
	palette color.Palette
	index   int
}

// format is RGB555
func get4bppPalette(data []byte) []color.RGBA {
	colors := make([]color.RGBA, 16)
	for i := 0; i < len(colors); i++ {
		c := uint16(data[i*2+0]) | (uint16(data[i*2+1]) << 8)
		colors[i] = color.RGBA{
			uint8((c >> 0) << 3),
			uint8((c >> 5) << 3),
			uint8((c >> 10) << 3),
			255,
		}
	}

	return colors
}

// sometimes golang is derp
func asPalette(rgbaPalette []color.RGBA) color.Palette {
	c := make([]color.Color, len(rgbaPalette))
	for i := 0; i < len(rgbaPalette); i++ {
		c[i] = rgbaPalette[i]
	}

	return color.Palette(c)
}

// useful to not export images that are completely black
func isPaletteNotEmpty(p []color.RGBA) bool {
	for i := 0; i < len(p); i++ {
		if p[i].R != 0 || p[i].G != 0 || p[i].B != 0 {
			return true
		}
	}
	return false
}

func getGfxAsImage(data []byte, p color.Palette) *image.Paletted {
	const w = 128
	const h = 128
	const blockSize = w * h / 2
	nBlock := len(data) / blockSize
	hImg := h * nBlock

	r := image.Rectangle{image.Point{0, 0}, image.Point{w, hImg}}
	img := image.NewPaletted(r, p)
	for i := 0; i < len(img.Pix)/2; i++ {
		img.Pix[i*2+0] = uint8(data[i] & 15)
		img.Pix[i*2+1] = uint8(data[i] >> 4)
	}

	return img
}

func partitionData(data []byte, config []int) ([][]byte, error) {
	const w = 128
	const h = 128
	const blockSize = w * h / 2
	const maxBlockCount = 32
	partitions := make([][]byte, len(config))

	blockPtr := 0
	for i := 0; i < len(config); i++ {
		nBlock := config[i]
		if nBlock >= maxBlockCount {
			return nil, fmt.Errorf("exceeded max block count (%d>=%d)", nBlock, maxBlockCount)
		}

		start := blockPtr * blockSize
		end := (blockPtr + nBlock) * blockSize
		partitions[i] = data[start:end]
		blockPtr += nBlock
	}

	return partitions, nil
}

func GetGfxAsImages(data []byte, config []int) ([]ImageInfo, error) {
	const paletteCountPerPartition = 16
	const paletteSize = 16 * 2
	const partitionCountForPalette = 12

	if len(config) < partitionCountForPalette {
		return nil, fmt.Errorf("not enough data in config array (%d<%d)",
			len(config), paletteCountPerPartition)
	}

	partitions, err := partitionData(data, config)
	if err != nil {
		return nil, err
	}

	clut := make([]paletteInfo, 0)
	for i := 0; i < partitionCountForPalette; i++ {
		part := partitions[i]
		clutData := part[len(part)-0x400:]
		for j := 0; j < paletteCountPerPartition; j++ {
			palData := clutData[paletteSize*j:]
			pal := get4bppPalette(palData)
			if isPaletteNotEmpty(pal) {
				clut = append(clut, paletteInfo{
					palette: asPalette(pal),
					index:   i*paletteCountPerPartition + j,
				})
			}
		}

	}

	imgs := make([]ImageInfo, 0)
	for i := 0; i < len(partitions); i++ {
		for j := 0; j < len(clut); j++ {
			imgs = append(imgs, ImageInfo{
				Img:       getGfxAsImage(partitions[i], clut[j].palette),
				Partition: i,
				Clut:      clut[j].index,
			})
		}
	}

	return imgs, nil
}
