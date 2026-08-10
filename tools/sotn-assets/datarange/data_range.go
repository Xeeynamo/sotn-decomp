package datarange

import (
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"sort"
)

type DataRange struct {
	begin psx.Addr
	end   psx.Addr
}

func New(begin, end psx.Addr) DataRange {
	return DataRange{
		begin: begin,
		end:   end,
	}
}

func FromAddr(addr psx.Addr, len int) DataRange {
	return New(addr, addr.Sum(len))
}

func FromAlignedAddr(addr psx.Addr, len int, alignment int) DataRange {
	return New(addr, addr.Sum(len).Align(alignment))
}

func (r DataRange) Align4() DataRange {
	return New(r.begin, r.end.Align4())
}

func (r DataRange) Format(f fmt.State, c rune) {
	_, _ = f.Write([]byte(fmt.Sprintf("(%s, %s)", r.begin, r.end)))
}

func (r DataRange) Begin() psx.Addr { return r.begin }

func (r DataRange) End() psx.Addr { return r.end }

func (r DataRange) Empty() bool {
	return r.begin == psx.RamNull && r.end == psx.RamNull
}

func MergeDataRanges(ranges []DataRange) DataRange {
	merged, err := Merge(ranges)
	if err != nil {
		panic(err)
	}
	return merged
}

// Merge is MergeDataRanges for callers that can report a bad range set instead
// of dying on it.
func Merge(ranges []DataRange) (DataRange, error) {
	if len(ranges) == 0 {
		return DataRange{}, fmt.Errorf("no datarange, bug?!")
	}

	sort.Slice(ranges, func(i, j int) bool {
		return ranges[i].begin < ranges[j].begin
	})

	// performs a sanity check before merging everything
	for i := 0; i < len(ranges)-1; i++ {
		if ranges[i].end != ranges[i+1].begin {
			if ranges[i].end < ranges[i+1].begin {
				return DataRange{}, fmt.Errorf("gap between data detected: %s != %s", ranges[i].end, ranges[i+1].begin)
			}
			return DataRange{}, fmt.Errorf("overlap between data detected: %s != %s", ranges[i].end, ranges[i+1].begin)
		}
	}

	return DataRange{
		begin: ranges[0].begin,
		end:   ranges[len(ranges)-1].end,
	}, nil
}

// ConsolidateDataRanges collapses adjacent ranges while preserving gaps.
// Overlapping ranges are rejected instead of being silently combined.
func ConsolidateDataRanges(ranges []DataRange) ([]DataRange, error) {
	if len(ranges) == 0 {
		return nil, fmt.Errorf("no data range to consolidate")
	}

	sorted := append([]DataRange(nil), ranges...)
	sort.Slice(sorted, func(i, j int) bool {
		return sorted[i].begin < sorted[j].begin
	})

	var consolidated []DataRange
	begin := sorted[0].begin
	for i := 0; i < len(sorted)-1; i++ {
		switch {
		case sorted[i].end > sorted[i+1].begin:
			return nil, fmt.Errorf(
				"overlap between data detected: %s > %s",
				sorted[i].end,
				sorted[i+1].begin)
		case sorted[i].end < sorted[i+1].begin:
			consolidated = append(
				consolidated, New(begin, sorted[i].end))
			begin = sorted[i+1].begin
		}
	}

	return append(
		consolidated, New(begin, sorted[len(sorted)-1].end)), nil
}
