package util

import (
	"encoding/json"
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"golang.org/x/exp/constraints"
	"image/color"
    "io"
	"os"
	"path/filepath"
	"slices"
	"sort"
	"strconv"
	"strings"
)

func JoinMapKeys[T any](m map[string]T, sep string) string {
	keys := make([]string, 0, len(m))
	for k := range m {
		keys = append(keys, k)
	}
	return strings.Join(keys, sep)
}

func ReverseMap[K comparable, V comparable](m map[K]V) map[V]K {
	reversed := make(map[V]K, len(m))
	for k, v := range m {
		reversed[v] = k
	}
	return reversed
}

func MergeMaps[K comparable, V any](map1, map2 map[K]V) map[K]V {
	merged := make(map[K]V, len(map1)+len(map2))
	for k, v := range map1 {
		merged[k] = v
	}
	for k, v := range map2 {
		merged[k] = v
	}
	return merged
}

func SortedIndexMap[K constraints.Ordered, V any](set map[K]V) map[K]int {
	keys := make([]K, 0, len(set))
	for k := range set {
		keys = append(keys, k)
	}
	sort.Slice(keys, func(i, j int) bool {
		return keys[i] < keys[j]
	})
	indexMap := make(map[K]int, len(keys))
	for i, k := range keys {
		indexMap[k] = i
	}
	return indexMap
}

func MinBy[T any](slice []T, getter func(T) int) (max int) {
	if len(slice) == 0 {
		return max
	}
	max = getter(slice[0])
	for _, item := range slice[1:] {
		val := getter(item)
		if val < max {
			max = val
		}
	}
	return max
}

func MaxBy[T any](slice []T, getter func(T) int) (max int) {
	if len(slice) == 0 {
		return max
	}
	max = getter(slice[0])
	for _, item := range slice[1:] {
		val := getter(item)
		if val > max {
			max = val
		}
	}
	return max
}

func Btoi(b bool) int {
	if b {
		return 1
	}
	return 0
}

// if the number starts with 0x, it parses it as a hexadecimal value, otherwise decimal
func ParseCNumber(s string) (int, error) {
	base := 10
	if strings.HasPrefix(s, "0x") {
		s = s[2:]
		base = 16
	}
	value, err := strconv.ParseInt(s, base, 32)
	if err != nil {
		return 0, err
	}
	return int(value), nil
}

func SortUniqueOffsets(slice []psx.Addr) []psx.Addr {
	unique := map[psx.Addr]struct{}{}
	for _, v := range slice {
		unique[v] = struct{}{}
	}
	newSlice := make([]psx.Addr, 0, len(unique))
	for offset := range unique {
		newSlice = append(newSlice, offset)
	}

	slices.SortFunc(newSlice, func(a, b psx.Addr) int {
		if a < b {
			return -1
		} else if a > b {
			return 1
		}
		return 0
	})
	return newSlice
}

// Simple wrapper for SortUniqueOffsets to also filter null addresses
func SortAndFilterOffsets(slice []psx.Addr) []psx.Addr {
	newSlice := SortUniqueOffsets(slice)
	if newSlice[0] == psx.RamNull {
		newSlice = newSlice[1:]
	}
	return newSlice
}

// WriteFile ensures the directory of the file to create exists
func WriteFile(name string, content []byte) error {
	dir := filepath.Dir(name)
	if err := os.MkdirAll(dir, 0755); err != nil {
		return fmt.Errorf("failed to create directory %q: %v\n", dir, err)
	}
    return WriteFileAtomic(name, content)
}

func WriteFileAtomic(name string, content []byte) error {
    w, err := CreateAtomicWriter(name)
    if err != nil {
        return fmt.Errorf("could not create writer for %q: %v\n", name, err)
    }
    defer w.Close()
    if _, err := w.Write(content); err != nil {
        return fmt.Errorf("could not write  %q: %v\n", name, err)
    }
    return nil
}

// WriteJsonFile converts the passed object as a JSON and internally calls WriteFile
func WriteJsonFile(name string, v any) error {
	content, err := json.MarshalIndent(v, "", "  ")
	if err != nil {
		return err
	}
	return WriteFile(name, content)
}

func RemoveFileNameExt(name string) string {
	return strings.TrimSuffix(name, filepath.Ext(name))
}

func WriteBytesAsHex(sb *strings.Builder, content []byte) {
	const hex = "0123456789ABCDEF"
	sb.Grow(len(content)*5 + (len(content) >> 4) + 2)
	for i, b := range content {
		sb.WriteString("0x")
		sb.WriteByte(hex[b>>4])
		sb.WriteByte(hex[b&15])
		sb.WriteByte(',')
		if (i & 15) == 15 {
			sb.WriteByte('\n')
		}
	}
	sb.WriteByte('\n')
}

func WriteWordsAsHex(sb *strings.Builder, content []uint16) {
	const hex = "0123456789ABCDEF"
	sb.Grow(len(content)*5 + (len(content) >> 4) + 2)
	for i, b := range content {
		sb.WriteString("0x")
		sb.WriteByte(hex[(b>>12)&15])
		sb.WriteByte(hex[(b>>8)&15])
		sb.WriteByte(hex[(b>>4)&15])
		sb.WriteByte(hex[(b>>0)&15])
		sb.WriteByte(',')
		if (i & 15) == 15 {
			sb.WriteByte('\n')
		}
	}
	sb.WriteByte('\n')
}

func MakePaletteFromR5G5B5A1(data []byte, invertAlpha bool) []color.RGBA {
	colors := make([]color.RGBA, len(data)/2)
	for i := 0; i < len(colors); i++ {
		c := uint16(data[2*i]) | uint16(data[2*i+1])<<8
		a := uint8(255)
		if invertAlpha {
			a = 127
		}
		if c&0x8000 != 0 {
			a = 127
			if invertAlpha {
				a = 255
			}
		}
		colors[i] = color.RGBA{
			R: uint8(((c >> 0) & 0x1F) * 255 / 31),
			G: uint8(((c >> 5) & 0x1F) * 255 / 31),
			B: uint8(((c >> 10) & 0x1F) * 255 / 31),
			A: a,
		}
	}
	return colors
}

func MakeGreyPalette(bpp int) []color.RGBA {
	switch bpp {
	case 1:
		colors := make([]color.RGBA, 2)
		colors[0] = color.RGBA{R: 0, G: 0, B: 0, A: 255}
		colors[1] = color.RGBA{R: 255, G: 255, B: 255, A: 255}
		return colors
	case 4:
		colors := make([]color.RGBA, 16)
		for i := range colors {
			c := uint8(i << 4)
			colors[i] = color.RGBA{R: c, G: c, B: c, A: 255}
		}
		return colors
	case 8:
		colors := make([]color.RGBA, 256)
		for i := range colors {
			c := uint8(i)
			colors[i] = color.RGBA{R: c, G: c, B: c, A: 255}
		}
		return colors
	default:
		return nil
	}
}

// ensure the returned bitmap is a 8bpp
func MakeBitmap(data []byte, bpp int) ([]byte, error) {
	switch bpp {
	case 1:
		out := make([]byte, len(data)*8)
		for i := 0; i < len(data); i++ {
			out[i*8+0] = data[i] & 0x80 >> 7
			out[i*8+1] = data[i] & 0x40 >> 6
			out[i*8+2] = data[i] & 0x20 >> 5
			out[i*8+3] = data[i] & 0x10 >> 4
			out[i*8+4] = data[i] & 0x8 >> 3
			out[i*8+5] = data[i] & 0x4 >> 2
			out[i*8+6] = data[i] & 0x2 >> 1
			out[i*8+7] = data[i] & 0x1 >> 0
		}
		return out, nil
	case 4:
		out := make([]byte, len(data)*2)
		for i := 0; i < len(data); i++ {
			out[i*2+0] = data[i] & 15
			out[i*2+1] = data[i] >> 4
		}
		return out, nil
	case 8:
		return data, nil
	default:
		return nil, fmt.Errorf("bpp %d invalid or not supported", bpp)
	}
}

func Make1bppFromBitmap(data []byte) []byte {
	out := make([]byte, len(data)/8)
	for i := 0; i < len(data); i += 8 {
		out[i>>3] = ((data[i] & 1) << 7) | ((data[i+1] & 1) << 6) | ((data[i+2] & 1) << 5) | ((data[i+3] & 1) << 4) | ((data[i+4] & 1) << 3) | ((data[i+5] & 1) << 2) | ((data[i+6] & 1) << 1) | ((data[i+7] & 1) << 0)
	}
	return out
}

func Make4bppFromBitmap(data []byte) []byte {
	out := make([]byte, len(data)/2)
	for i := 0; i < len(data); i += 2 {
		out[i>>1] = (data[i] & 0xF) | ((data[i+1] & 0xF) << 4)
	}
	return out
}

type StringWriteCloser interface {
    io.WriteCloser
    io.StringWriter

    Name() string
}

type AtomicWriter struct {
    name string
    f *os.File
}

func CreateAtomicWriter(name string) (StringWriteCloser, error) {
    base := filepath.Base(name)
    dir := filepath.Dir(name)
    f, err := os.CreateTemp(dir, base)
    if err != nil {
        return nil, fmt.Errorf("failed to create temp file for %q: %v\n", name, err)
    }

    a := AtomicWriter { name: name, f: f }

    return a, nil
}

func (a AtomicWriter) Close() error {
    a.f.Close()
    if err := os.Rename(a.f.Name(), a.name); err != nil {
        // in the common case, a.f will already be renamed
        // in case it isn't remove the temp file
        os.Remove(a.f.Name())
        return fmt.Errorf("failed to move temp file to destination %q: %v\n", a.name, err)
    }

    return nil
}

func (a AtomicWriter) Write(p []byte) (int, error) {
    return a.f.Write(p)
}

func (a AtomicWriter) WriteString(s string) (int, error) {
    return a.f.WriteString(s)
}

func (a AtomicWriter) Name() string {
    return a.f.Name()
}
