package gfx

import (
	"image"
	"image/color"
)

type ImageInfo struct {
	Img       *image.Paletted
	Partition int
	Clut      int
}

type paletteInfo struct {
	palette color.Palette
	index   int
}

func make4bppPalette() []color.RGBA {
	colors := make([]color.RGBA, 16)
	for i := 0; i < len(colors); i++ {
		colors[i] = color.RGBA{
			byte(i << 3),
			byte(i << 3),
			byte(i << 3),
			255,
		}
	}

	return colors
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
	const w = 256
	const h = 256
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

func partitionData(data []byte) ([][]byte, error) {
	const blockSize = 32768
	const halfBlock = blockSize / 2
	partitions := make([][]byte, len(data)/blockSize)
	for i := 0; i < len(partitions); i++ {
		in := data[i*blockSize:]
		out := make([]byte, blockSize)
		for j := 0; j < 128; j++ {
			copy(out[j*128+0:][:64], in[j*64+0:][:64])
			copy(out[j*128+64:][:64], in[j*64+8192:][:64])
		}
		for j := 0; j < 128; j++ {
			copy(out[halfBlock+j*128+0:][:64], in[halfBlock+j*64+0:][:64])
			copy(out[halfBlock+j*128+64:][:64], in[halfBlock+j*64+8192:][:64])
		}

		partitions[i] = out
	}

	return partitions, nil
}

func GetGfxAsImages(data []byte) ([]ImageInfo, error) {
	const maxPaletteCount = 256
	const paletteSize = 16 * 2
	const palettePerPartition = 4

	partitions, err := partitionData(data)
	if err != nil {
		return nil, err
	}

	clut := make([]paletteInfo, 0)
	clut = append(clut, paletteInfo{
		palette: asPalette(make4bppPalette()),
	})
	for i := 0; i < maxPaletteCount; i++ {
		index := i&3 + (i/16)*palettePerPartition
		partitionIndex := (i / 4) & 3
		palData := partitions[partitionIndex][30720+index*paletteSize:][:paletteSize]
		pal := get4bppPalette(palData)
		if isPaletteNotEmpty(pal) {
			clut = append(clut, paletteInfo{
				palette: asPalette(pal),
				index:   i,
			})
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
