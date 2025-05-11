package palette

import (
	"bytes"
	"encoding/binary"
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/util"
	"image/color"
	"io"
)

type palettePng struct{}

func (_ *palettePng) Export(w io.Writer, colors []color.RGBA) error {
	width := 16
	height := max(len(colors)>>4, 1)
	data := make([]byte, len(colors))
	for i := 0; i < len(colors); i++ {
		data[i] = byte(i)
	}
	return util.PngEncode(w, data, width, height, colors)
}

func (_ *palettePng) Import(r io.Reader) ([]color.RGBA, error) {
	var palette []color.RGBA
	var alpha []byte
	var width, height int

	var pngHeader = []byte{137, 80, 78, 71, 13, 10, 26, 10}
	header := make([]byte, 8)
	if _, err := io.ReadFull(r, header); err != nil || !bytes.Equal(header, pngHeader) {
		return nil, fmt.Errorf("invalid PNG header")
	}
	for {
		var lengthBuf [4]byte
		if _, err := io.ReadFull(r, lengthBuf[:]); err != nil {
			break // End of chunks
		}
		length := binary.BigEndian.Uint32(lengthBuf[:])
		chunkType := make([]byte, 4)
		if _, err := io.ReadFull(r, chunkType); err != nil {
			return nil, err
		}
		chunkData := make([]byte, length)
		if _, err := io.ReadFull(r, chunkData); err != nil {
			return nil, err
		}
		if _, err := io.CopyN(io.Discard, r, 4); err != nil {
			return nil, err
		}
		switch string(chunkType) {
		case "IHDR":
			if len(chunkData) < 8 {
				return nil, fmt.Errorf("IHDR chunk too short")
			}
			width = int(binary.BigEndian.Uint32(chunkData[0:4]))
			height = int(binary.BigEndian.Uint32(chunkData[4:8]))
		case "PLTE":
			for i := 0; i < len(chunkData); i += 3 {
				palette = append(palette, color.RGBA{
					R: chunkData[i],
					G: chunkData[i+1],
					B: chunkData[i+2],
					A: 255,
				})
			}
		case "tRNS":
			alpha = chunkData
		case "IEND":
			break
		}
	}
	for i := 0; i < len(palette) && i < len(alpha); i++ {
		palette[i].A = alpha[i]
	}
	// this is needed as some tools re-export a PNG as 8bpp, so we need to rely on width and height
	colorCount := width * height
	if colorCount > len(palette) {
		return nil, fmt.Errorf("PNG contains more colors than the palette")
	}
	return palette[:colorCount], nil
}
