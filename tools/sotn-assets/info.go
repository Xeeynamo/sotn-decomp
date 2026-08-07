package main

import (
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets/graphics"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/datarange"
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
	var gfx []assets.InfoGraphic
	var palettes []assets.InfoPalette
	boundaries := psx.Addr(0x80000000).Boundaries()
	for _, h := range handlers {
		info, err := h.Info(assets.InfoArgs{
			StageFilePath: filePath,
			StageData:     data,
			Boundaries:    boundaries,
		})
		if err != nil {
			return fmt.Errorf("unable to gather info for file %q: %s", filePath, err)
		}
		assetEntries = append(assetEntries, info.AssetEntries...)
		splatEntries = append(splatEntries, info.SplatEntries...)
		gfx = append(gfx, info.Graphics...)
		palettes = append(palettes, info.Palettes...)
	}

	if len(gfx) > 0 || len(palettes) > 0 {
		// every range another handler explains, so the classifier neither probes
		// it nor anchors its region inside it
		claimed := make([]datarange.DataRange, 0, len(assetEntries)+len(splatEntries))
		var claimedEnd psx.Addr
		for _, e := range assetEntries {
			claimed = append(claimed, e.DataRange)
			if e.DataRange.End() > claimedEnd {
				claimedEnd = e.DataRange.End()
			}
		}
		for _, e := range splatEntries {
			claimed = append(claimed, e.DataRange)
		}
		firstGfx := lowestAddr(gfx, palettes, claimedEnd)
		classified, region, err := graphics.Classify(graphics.Args{
			Data:    data,
			RamBase: boundaries.StageBegin,
			// start at the top of the last claimed range below the first known
			// graphic, so data referenced only from C still falls in a gap
			RegionStart: claimedEndBelow(claimed, firstGfx),
			Graphics:    gfx,
			Palettes:    palettes,
			RegionEnd:   regionEnd(splatEntries, firstGfx, boundaries.StageBegin.Sum(len(data))),
			Claimed:     claimed,
		})
		if err != nil {
			return fmt.Errorf("unable to classify graphics for file %q: %s", filePath, err)
		}
		assetEntries = append(assetEntries, classified...)
		if !region.Empty() {
			// the whole graphics and palette span is one blob to splat
			splatEntries = append(splatEntries, assets.InfoSplatEntry{
				DataRange: region,
				Name:      "stage_data",
			})
		}
	}

	_, _ = fmt.Fprintln(w, "asset config hints:")
	infoAssetEntries(w, assetEntries, boundaries)
	_, _ = fmt.Fprintln(w, "splat config hints:")
	infoSplatEntries(w, splatEntries, boundaries)
	return nil
}

// lowestAddr is the first address the graphics classifier is responsible for:
// the lowest graphic or palette sitting above the header structures other
// handlers describe. Anything below that is a lone palette among the headers,
// which the classifier still emits an entry for but must not use to anchor the
// region it probes.
func lowestAddr(gfx []assets.InfoGraphic, palettes []assets.InfoPalette, above psx.Addr) psx.Addr {
	lowest := psx.Addr(0xFFFFFFFF)
	for _, g := range gfx {
		if g.Addr < lowest && g.Addr >= above {
			lowest = g.Addr
		}
	}
	for _, p := range palettes {
		if p.Addr < lowest && p.Addr >= above {
			lowest = p.Addr
		}
	}
	return lowest
}

// claimedEndBelow is the highest point below limit that another handler already
// explains. Probing from there rather than from limit itself is what exposes
// data no header points at, such as an image only C code references.
func claimedEndBelow(claimed []datarange.DataRange, limit psx.Addr) psx.Addr {
	var end psx.Addr
	for _, c := range claimed {
		if c.End() <= limit && c.End() > end {
			end = c.End()
		}
	}
	return end
}

// regionEnd bounds the graphics region by the next splat entry above it, since
// nothing in the stage header says where the region stops.
func regionEnd(splatEntries []assets.InfoSplatEntry, regionStart, fallback psx.Addr) psx.Addr {
	end := fallback
	for _, e := range splatEntries {
		if b := e.DataRange.Begin(); b > regionStart && b < end {
			end = b
		}
	}
	return end
}

func infoAssetEntries(w io.Writer, entries []assets.InfoAssetEntry, boundaries psx.Offsets) {
	if len(entries) == 0 {
		return
	}
	sort.Slice(entries, func(i, j int) bool {
		return entries[i].DataRange.Begin() < entries[j].DataRange.Begin()
	})
	for i, e := range entries {
		s := fmt.Sprintf("  - [0x%X, %s", e.DataRange.Begin().Real(boundaries.StageBegin), e.Kind)
		if e.Name != "" {
			s = fmt.Sprintf("%s, %s", s, e.Name)
		}
		if e.Args != "" {
			s = fmt.Sprintf("%s, %s", s, e.Args)
		}
		s += "]"
		if e.Comment != "" {
			s = fmt.Sprintf("%s # %s", s, e.Comment)
		}
		_, _ = fmt.Fprintln(w, s)
		// if there is a gap between the current entry and the next one, mark it as unrecognized data
		if i == len(entries)-1 || e.DataRange.End() != entries[i+1].DataRange.Begin() {
			_, _ = fmt.Fprintf(w, "  - [0x%X, skip]\n", e.DataRange.End().Real(boundaries.StageBegin))
		}
	}
}

func infoSplatEntries(w io.Writer, entries []assets.InfoSplatEntry, boundaries psx.Offsets) {
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
		s := fmt.Sprintf("  - [0x%X, %s, %s]", e.DataRange.Begin().Real(boundaries.StageBegin), kind, e.Name)
		if e.Comment != "" {
			s = fmt.Sprintf("%s # %s", s, e.Comment)
		}
		_, _ = fmt.Fprintln(w, s)

		// if there is a gap between the current entry and the next one, mark it as unrecognized data
		if i == len(entries)-1 || e.DataRange.End() != entries[i+1].DataRange.Begin() {
			_, _ = fmt.Fprintf(w, "  - [0x%X, data]\n", e.DataRange.End().Real(boundaries.StageBegin))
		}
	}
}
