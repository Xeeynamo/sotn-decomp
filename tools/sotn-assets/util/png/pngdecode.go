package png

import (
	"bytes"
	"compress/zlib"
	"encoding/binary"
	"fmt"
	"hash/crc32"
	"io"
)

type Info struct {
	Width            int
	Height           int
	BitDepth         uint8
	ColorType        uint8
	Interlaced       bool
	NumPaletteColors int
}

// Decode decodes a PNG image into a byte array, ignoring any palette
func Decode(r io.Reader) ([]byte, *Info, error) {
	data, err := io.ReadAll(r)
	if err != nil {
		return nil, nil, fmt.Errorf("failed to read: %w", err)
	}

	signature := []byte{137, 80, 78, 71, 13, 10, 26, 10}
	if len(data) < len(signature) {
		return nil, nil, fmt.Errorf("PNG signature too short")
	}
	if !bytes.Equal(data[:len(signature)], signature) {
		return nil, nil, fmt.Errorf("invalid PNG signature")
	}

	offset := len(signature)
	var ihdr *Info
	var idatData bytes.Buffer
	for offset < len(data) {
		// Each chunk has: 4-byte length, 4-byte type, data, 4-byte CRC
		if offset+8 > len(data) {
			return nil, nil, fmt.Errorf("truncated chunk header")
		}

		chunkLen := binary.BigEndian.Uint32(data[offset : offset+4])
		chunkType := string(data[offset+4 : offset+8])
		offset += 8
		if offset+int(chunkLen)+4 > len(data) {
			return nil, nil, fmt.Errorf("truncated chunk data for %s", chunkType)
		}

		chunkData := data[offset : offset+int(chunkLen)]
		offset += int(chunkLen)

		// Verify CRC
		storedCRC := binary.BigEndian.Uint32(data[offset : offset+4])
		offset += 4

		crc := crc32.NewIEEE()
		_, _ = crc.Write([]byte(chunkType))
		_, _ = crc.Write(chunkData)
		calculatedCRC := crc.Sum32()
		if storedCRC != calculatedCRC {
			return nil, nil, fmt.Errorf("CRC mismatch for %s chunk", chunkType)
		}

		switch chunkType {
		case "IHDR":
			if len(chunkData) != 13 {
				return nil, nil, fmt.Errorf("invalid IHDR length %d", len(chunkData))
			}
			ihdr = &Info{
				Width:      int(binary.BigEndian.Uint32(chunkData[0:4])),
				Height:     int(binary.BigEndian.Uint32(chunkData[4:8])),
				BitDepth:   chunkData[8],
				ColorType:  chunkData[9],
				Interlaced: chunkData[12] == 1,
			}
		case "PLTE":
			if ihdr != nil {
				ihdr.NumPaletteColors = len(chunkData) / 3
			}
		case "IDAT":
			idatData.Write(chunkData)
		case "IEND":
			// End of image, stop parsing
			break
		}
	}

	if ihdr == nil {
		return nil, nil, fmt.Errorf("missing IHDR chunk")
	}
	if idatData.Len() == 0 {
		return nil, nil, fmt.Errorf("missing IDAT chunk")
	}
	if ihdr.Interlaced {
		return nil, nil, fmt.Errorf("interlace format unsupported")
	}
	bitsPerPixel, err := getBitsPerPixel(ihdr.ColorType, ihdr.BitDepth)
	if err != nil {
		return nil, nil, fmt.Errorf("%w", err)
	}
	bytesPerPixel := min(1, bitsPerPixel/8)

	// Decompress the IDAT data
	zr, err := zlib.NewReader(&idatData)
	if err != nil {
		return nil, nil, fmt.Errorf("failed to create zlib reader: %w", err)
	}
	defer zr.Close()
	decompressed, err := io.ReadAll(zr)
	if err != nil {
		return nil, nil, fmt.Errorf("failed to decompress: %w", err)
	}

	// Calculate row stride (filter byte + pixel data)
	rowStride := 1 + ((ihdr.Width*int(ihdr.BitDepth) + 7) / 8)
	expectedLen := ihdr.Height * rowStride
	if len(decompressed) != expectedLen {
		return nil, nil, fmt.Errorf("decompressed data length %d != expected %d", len(decompressed), expectedLen)
	}

	pixelData := make([]byte, 0, ihdr.Width*ihdr.Height*bitsPerPixel/8)
	prevRow := make([]byte, rowStride-1)
	for y := 0; y < ihdr.Height; y++ {
		rowStart := y * rowStride
		filter := decompressed[rowStart]
		rowData := decompressed[rowStart+1 : rowStart+rowStride]
		if err := reverseFilter(filter, rowData, prevRow, int(ihdr.BitDepth), bytesPerPixel); err != nil {
			return nil, nil, fmt.Errorf("row %d: %w", y, err)
		}
		pixelData = append(pixelData, rowData...)
		copy(prevRow, rowData)
	}
	if bitsPerPixel == 1 || ihdr.NumPaletteColors <= 2 {
		out := make([]byte, len(pixelData)/8)
		for i := 0; i < len(pixelData); i += 8 {
			out[i>>3] = ((pixelData[i] & 1) << 7) |
				((pixelData[i+1] & 1) << 6) |
				((pixelData[i+2] & 1) << 5) |
				((pixelData[i+3] & 1) << 4) |
				((pixelData[i+4] & 1) << 3) |
				((pixelData[i+5] & 1) << 2) |
				((pixelData[i+6] & 1) << 1) |
				((pixelData[i+7] & 1) << 0)
		}
		pixelData = out
	} else if bitsPerPixel == 4 || ihdr.NumPaletteColors > 0 && ihdr.NumPaletteColors <= 16 {
		out := make([]byte, len(pixelData)/2)
		for i := 0; i < len(pixelData); i += 2 {
			out[i>>1] = (pixelData[i] & 0xF) | ((pixelData[i+1] & 0xF) << 4)
		}
		pixelData = out
	}

	return pixelData, ihdr, nil
}

// getBitsPerPixel returns the number of bytes per pixel for a given color type and bit depth
func getBitsPerPixel(colorType, bitDepth uint8) (int, error) {
	switch colorType {
	case 0: // Grayscale
		switch bitDepth {
		case 4, 8:
			return int(bitDepth), nil
		default:
			return 0, fmt.Errorf("unsupported bit depth %d for grayscale", bitDepth)
		}
	case 2: // RGB
		return 0, fmt.Errorf("unsupported RGB format")
	case 3: // Indexed color (palette)
		switch bitDepth {
		case 4, 8:
			return int(bitDepth), nil
		default:
			return 0, fmt.Errorf("unsupported bit depth %d for indexed color", bitDepth)
		}
	case 4: // Grayscale + Alpha
		return 0, fmt.Errorf("unsupported Grayscale+Alpha format")
	case 6: // RGBA
		return 0, fmt.Errorf("supported RGBA format")
	default:
		return 0, fmt.Errorf("unknown color type %d", colorType)
	}
}

// reverseFilter applies the inverse of PNG filter to restore original row data
func reverseFilter(filter uint8, row, prevRow []byte, bitDepth, bytesPerPixel int) error {
	switch filter {
	case 0: // None
		return nil
	case 1: // Sub: byte = byte + left_byte
		for i := bytesPerPixel; i < len(row); i++ {
			row[i] += row[i-bytesPerPixel]
		}
		return nil
	case 2: // Up: byte = byte + above_byte
		for i := 0; i < len(row); i++ {
			row[i] += prevRow[i]
		}
		return nil
	case 3: // Average: byte = byte + floor((left + above) / 2)
		for i := 0; i < len(row); i++ {
			left := byte(0)
			if i >= bytesPerPixel {
				left = row[i-bytesPerPixel]
			}
			above := prevRow[i]
			row[i] += (left + above) / 2
		}
		return nil
	case 4: // Paeth: byte = byte + PaethPredictor(left, above, upper_left)
		for i := 0; i < len(row); i++ {
			left := byte(0)
			upperLeft := byte(0)
			if i >= bytesPerPixel {
				left = row[i-bytesPerPixel]
				upperLeft = prevRow[i-bytesPerPixel]
			}
			above := prevRow[i]
			row[i] += paethPredictor(left, above, upperLeft)
		}
		return nil
	default:
		return fmt.Errorf("unknown filter type %d", filter)
	}
}

// paethPredictor implements the PNG Paeth predictor function
func paethPredictor(a, b, c byte) byte {
	// a = left, b = above, c = upper left
	p := int(a) + int(b) - int(c)
	pa := abs(p - int(a))
	pb := abs(p - int(b))
	pc := abs(p - int(c))
	if pa <= pb && pa <= pc {
		return a
	} else if pb <= pc {
		return b
	}
	return c
}

func abs(x int) int {
	if x < 0 {
		return -x
	}
	return x
}
