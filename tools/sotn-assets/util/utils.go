package util

import (
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
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
