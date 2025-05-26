package util

import (
	"bytes"
	"compress/zlib"
	"encoding/binary"
	"fmt"
	"hash/crc32"
	"image/color"
	"io"
)

// PngEncode encodes an 8-bit indexed-colour image whose pixels are in
// row-major order in the 'data' slice (len(data) == width*height).
func PngEncode(w io.Writer, data []byte, width, height int, palette []color.RGBA) error {
	if width <= 0 || height <= 0 {
		return fmt.Errorf("invalid size %dx%d", width, height)
	}
	if len(data) < width*height {
		return fmt.Errorf("data length (%d) < width*height (%d)", len(data), width*height)
	}
	if len(palette) == 0 || len(palette) > 256 {
		return fmt.Errorf("palette size must be 1–256, got %d", len(palette))
	}

	// Helper that writes and propagates I/O errors.
	write := func(b []byte) error {
		_, err := w.Write(b)
		return err
	}

	// ───────── PNG signature ─────────
	if err := write([]byte{137, 80, 78, 71, 13, 10, 26, 10}); err != nil {
		return err
	}

	// ───────── IHDR ─────────
	var ihdr [13]byte
	binary.BigEndian.PutUint32(ihdr[0:], uint32(width))
	binary.BigEndian.PutUint32(ihdr[4:], uint32(height))
	ihdr[8] = 8  // bit depth
	ihdr[9] = 3  // indexed color type
	ihdr[10] = 0 // compression
	ihdr[11] = 0 // filter
	ihdr[12] = 0 // interlace
	if err := writeChunk(w, "IHDR", ihdr[:]); err != nil {
		return err
	}

	// PLTE: RGB palette.
	plte := make([]byte, 3*len(palette))
	for i, c := range palette {
		plte[i*3+0] = c.R
		plte[i*3+1] = c.G
		plte[i*3+2] = c.B
	}
	if err := writeChunk(w, "PLTE", plte); err != nil {
		return err
	}

	// tRNS: alpha channel for PLTE
	trns := make([]byte, len(palette))
	for i, c := range palette {
		trns[i] = c.A
	}
	if err := writeChunk(w, "tRNS", trns); err != nil {
		return err
	}

	// ───────── IDAT ─────────
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
		return err
	}
	if _, err := zw.Write(raw); err != nil {
		return err
	}
	if err := zw.Close(); err != nil {
		return err
	}
	if err := writeChunk(w, "IDAT", idat.Bytes()); err != nil {
		return err
	}

	// ───────── IEND ─────────
	return writeChunk(w, "IEND", nil)
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
	crc.Write([]byte(kind))
	crc.Write(data)
	var crcBuf [4]byte
	binary.BigEndian.PutUint32(crcBuf[:], crc.Sum32())
	_, err := w.Write(crcBuf[:])
	return err
}
