package main

import (
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"io"
	"os"
	"sort"
)

func info(w io.Writer, filePath string) error {
	data, err := os.ReadFile(filePath)
	if err != nil {
		return fmt.Errorf("unable to read file %q: %s", filePath, err)
	}

	var assetEntries []assets.InfoAssetEntry
	var splatEntries []assets.InfoSplatEntry
	for _, h := range handlers {
		info, err := h.Info(assets.InfoArgs{
			StageFilePath: filePath,
			StageData:     data,
		})
		if err != nil {
			return fmt.Errorf("unable to gather info for file %q: %s", filePath, err)
		}
		assetEntries = append(assetEntries, info.AssetEntries...)
		splatEntries = append(splatEntries, info.SplatEntries...)
	}
	_, _ = fmt.Fprintln(w, "asset config hints:")
	infoAssetEntries(w, assetEntries)
	_, _ = fmt.Fprintln(w, "splat config hints:")
	infoSplatEntries(w, splatEntries)
	return nil
}

func infoAssetEntries(w io.Writer, entries []assets.InfoAssetEntry) {
	if len(entries) == 0 {
		return
	}
	sort.Slice(entries, func(i, j int) bool {
		return entries[i].DataRange.Begin() < entries[j].DataRange.Begin()
	})
	for i, e := range entries {
		_, _ = fmt.Fprintf(w, "  - [0x%X, %s, %s]\n", e.DataRange.Begin().Real(psx.RamStageBegin), e.Kind, e.Name)
		// if there is a gap between the current entry and the next one, mark it as unrecognized data
		if i == len(entries)-1 || e.DataRange.End() != entries[i+1].DataRange.Begin() {
			_, _ = fmt.Fprintf(w, "  - [0x%X, skip]\n", e.DataRange.End().Real(psx.RamStageBegin))
		}
	}
}

func infoSplatEntries(w io.Writer, entries []assets.InfoSplatEntry) {
	if len(entries) == 0 {
		return
	}
	sort.Slice(entries, func(i, j int) bool {
		return entries[i].DataRange.Begin() < entries[j].DataRange.Begin()
	})
	_, _ = fmt.Fprintln(w, "  - [0x0, .data, header]")
	for i, e := range entries {
		kind := ".data"
		if e.Kind != "" {
			kind = e.Kind
		}
		s := fmt.Sprintf("  - [0x%X, %s, %s]", e.DataRange.Begin().Real(psx.RamStageBegin), kind, e.Name)
		if e.Comment != "" {
			s = fmt.Sprintf("%s # %s", s, e.Comment)
		}
		_, _ = fmt.Fprintln(w, s)

		// if there is a gap between the current entry and the next one, mark it as unrecognized data
		if i == len(entries)-1 || e.DataRange.End() != entries[i+1].DataRange.Begin() {
			_, _ = fmt.Fprintf(w, "  - [0x%X, data]\n", e.DataRange.End().Real(psx.RamStageBegin))
		}
	}
}
