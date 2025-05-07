package palette

import (
	"bufio"
	"fmt"
	"image/color"
	"io"
	"strconv"
	"strings"
)

type paletteJasc struct{}

func (_ *paletteJasc) Export(w io.Writer, colors []color.RGBA) error {
	var sb strings.Builder
	sb.Grow(17 + len(colors)*12)
	sb.WriteString("JASC-PAL\n0100\n")
	sb.WriteString(strconv.Itoa(len(colors)))
	sb.WriteByte('\n')
	for _, c := range colors {
		fmt.Fprintf(&sb, "%d %d %d\n", c.R, c.G, c.B)
	}
	_, err := w.Write([]byte(sb.String()))
	return err
}

func (_ *paletteJasc) Import(r io.Reader) ([]color.RGBA, error) {
	scanner := bufio.NewScanner(r)
	if !scanner.Scan() || scanner.Text() != "JASC-PAL" {
		return nil, fmt.Errorf("invalid JASC-PAL header")
	}
	if !scanner.Scan() || scanner.Text() != "0100" {
		return nil, fmt.Errorf("unsupported JASC-PAL version")
	}
	if !scanner.Scan() {
		return nil, fmt.Errorf("missing color count")
	}
	count, err := strconv.Atoi(scanner.Text())
	if err != nil {
		return nil, fmt.Errorf("invalid color count")
	}
	colors := make([]color.RGBA, 0, count)
	for scanner.Scan() {
		fields := strings.Fields(scanner.Text())
		if len(fields) != 3 {
			return nil, fmt.Errorf("invalid color line")
		}
		r, _ := strconv.Atoi(fields[0])
		g, _ := strconv.Atoi(fields[1])
		b, _ := strconv.Atoi(fields[2])
		colors = append(colors, color.RGBA{R: uint8(r), G: uint8(g), B: uint8(b), A: 255})
	}
	return colors, scanner.Err()
}
