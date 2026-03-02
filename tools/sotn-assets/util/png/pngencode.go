package png

import (
	"bytes"
	"compress/zlib"
	"encoding/binary"
	"fmt"
	"hash/crc32"
	"image/color"
	"io"
)

// Encode encodes a 4-bit or 8-bit indexed-color image whose pixels are in
// row-major order in the 'data' slice (len(data) == width*height).
func Encode(w io.Writer, data []byte, width, height int, palette []color.RGBA) error {
	if width <= 0 || height <= 0 {
		return fmt.Errorf("invalid size %dx%d", width, height)
	}
	if len(palette) <= 2 {
		if len(data) < width*height/8 {
			return fmt.Errorf("data length (%d) < width*height (%d)", len(data), width*height/8)
		}
		// convert 4-bit nibbles to 8-bit data
		convert := make([]byte, len(data)*8)
		for i := 0; i < len(data); i++ {
			convert[i*8+0] = data[i] & 0x80 >> 7
			convert[i*8+1] = data[i] & 0x40 >> 6
			convert[i*8+2] = data[i] & 0x20 >> 5
			convert[i*8+3] = data[i] & 0x10 >> 4
			convert[i*8+4] = data[i] & 0x8 >> 3
			convert[i*8+5] = data[i] & 0x4 >> 2
			convert[i*8+6] = data[i] & 0x2 >> 1
			convert[i*8+7] = data[i] & 0x1 >> 0
		}
		data = convert
	} else if len(palette) <= 16 {
		if len(data) < width*height/2 {
			return fmt.Errorf("data length (%d) < width*height (%d)", len(data), width*height/2)
		}
		// convert 4-bit nibbles to 8-bit data
		convert := make([]byte, len(data)*2)
		for i := 0; i < len(data); i++ {
			convert[i*2+0] = data[i] & 15
			convert[i*2+1] = data[i] >> 4
		}
		data = convert
	} else {
		if len(data) < width*height {
			return fmt.Errorf("data length (%d) < width*height (%d)", len(data), width*height)
		}
	}
	if len(palette) == 0 || len(palette) > 256 {
		return fmt.Errorf("palette size must be 1–256, got %d", len(palette))
	}

	// Helper that writes and propagates I/O errors.
	write := func(b []byte) error {
		_, err := w.Write(b)
		return err
	}

	// PNG signature
	if err := write([]byte{137, 80, 78, 71, 13, 10, 26, 10}); err != nil {
		return fmt.Errorf("%w", err)
	}

	// Header IHDR
	var ihdr [13]byte
	binary.BigEndian.PutUint32(ihdr[0:], uint32(width))
	binary.BigEndian.PutUint32(ihdr[4:], uint32(height))
	ihdr[8] = 8  // bit depth
	ihdr[9] = 3  // indexed color type
	ihdr[10] = 0 // compression
	ihdr[11] = 0 // filter
	ihdr[12] = 0 // interlace
	if err := writeChunk(w, "IHDR", ihdr[:]); err != nil {
		return fmt.Errorf("%w", err)
	}

	// PLTE: RGB palette.
	plte := make([]byte, 3*len(palette))
	for i, c := range palette {
		plte[i*3+0] = c.R
		plte[i*3+1] = c.G
		plte[i*3+2] = c.B
	}
	if err := writeChunk(w, "PLTE", plte); err != nil {
		return fmt.Errorf("%w", err)
	}

	// tRNS: alpha channel for PLTE
	trns := make([]byte, len(palette))
	for i, c := range palette {
		trns[i] = c.A
	}
	if err := writeChunk(w, "tRNS", trns); err != nil {
		return fmt.Errorf("%w", err)
	}

	// Header IDAT
	// Build the uncompressed image: one filter byte (0) before every row.
	raw := make([]byte, height*(width+1))
	for y := 0; y < height; y++ {
		rowStart := y * (width + 1)
		raw[rowStart] = 0 // No filter
		copy(raw[rowStart+1:rowStart+1+width], data[y*width:(y+1)*width])
	}

	var idat bytes.Buffer
	zw, err := zlib.NewWriterLevel(&idat, zlib.BestSpeed)
	if err != nil {
		return fmt.Errorf("%w", err)
	}
	if _, err := zw.Write(raw); err != nil {
		_ = zw.Close()
		return fmt.Errorf("%w", err)
	}
	if err := zw.Close(); err != nil {
		return err
	}
	if err := writeChunk(w, "IDAT", idat.Bytes()); err != nil {
		return fmt.Errorf("%w", err)
	}

	// Header IEND
	if err := writeChunk(w, "IEND", nil); err != nil {
		return fmt.Errorf("%w", err)
	}
	return nil
}

// writeChunk writes a PNG chunk (length|type|data|CRC)
func writeChunk(w io.Writer, kind string, data []byte) error {
	if len(kind) != 4 {
		return fmt.Errorf("chunk type %q must be 4 bytes", kind)
	}

	var lenBuf [4]byte
	binary.BigEndian.PutUint32(lenBuf[:], uint32(len(data)))
	if _, err := w.Write(lenBuf[:]); err != nil {
		return err
	}
	if _, err := w.Write([]byte(kind)); err != nil {
		return err
	}
	if _, err := w.Write(data); err != nil {
		return err
	}

	crc := crc32.NewIEEE()
	if _, err := crc.Write([]byte(kind)); err != nil {
		return err
	}
	if _, err := crc.Write(data); err != nil {
		return err
	}
	var crcBuf [4]byte
	binary.BigEndian.PutUint32(crcBuf[:], crc.Sum32())
	if _, err := w.Write(crcBuf[:]); err != nil {
		return err
	}
	return nil
}
