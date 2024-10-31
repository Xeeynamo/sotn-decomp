package util

import (
	"encoding/json"
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"os"
	"path/filepath"
	"slices"
	"strings"
)

func JoinMapKeys[T any](m map[string]T, sep string) string {
	keys := make([]string, 0, len(m))
	for k := range m {
		keys = append(keys, k)
	}
	return strings.Join(keys, sep)
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

// WriteFile ensures the directory of the file to create exists
func WriteFile(name string, content []byte) error {
	dir := filepath.Dir(name)
	if err := os.MkdirAll(dir, 0755); err != nil {
		return fmt.Errorf("failed to create directory %q: %v\n", dir, err)
	}
	return os.WriteFile(name, content, 0644)
}

// WriteJsonFile converts the passed object as a JSON and internally calls WriteFile
func WriteJsonFile(name string, v any) error {
	content, err := json.MarshalIndent(v, "", "  ")
	if err != nil {
		return err
	}
	return WriteFile(name, content)
}
