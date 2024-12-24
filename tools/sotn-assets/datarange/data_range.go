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

func FromAlignedAddr(addr psx.Addr, len int) DataRange {
	return New(addr, addr.Sum(len).Align4())
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
	if len(ranges) == 0 {
		err := fmt.Errorf("no datarange, bug?!")
		panic(err)
	}

	sort.Slice(ranges, func(i, j int) bool {
		return ranges[i].begin < ranges[j].begin
	})

	// performs a sanity check before merging everything
	for i := 0; i < len(ranges)-1; i++ {
		if ranges[i].end != ranges[i+1].begin {
			var err error
			if ranges[i].end < ranges[i+1].begin {
				err = fmt.Errorf("gap between data detected: %s != %s", ranges[i].end, ranges[i+1].begin)
			} else {
				err = fmt.Errorf("overlap between data detected: %s != %s", ranges[i].end, ranges[i+1].begin)
			}
			panic(err)
		}
	}

	return DataRange{
		begin: ranges[0].begin,
		end:   ranges[len(ranges)-1].end,
	}
}

func ConsolidateDataRanges(ranges []DataRange) []DataRange {
	if len(ranges) == 0 {
		return []DataRange{}
	}

	sort.Slice(ranges, func(i, j int) bool {
		return ranges[i].begin < ranges[j].begin
	})

	for ranges[0].Empty() {
		ranges = ranges[1:]
	}

	consolidated := []DataRange{}
	first := 0
	for i := 0; i < len(ranges)-1; i++ {
		if ranges[i].end != ranges[i+1].begin {
			consolidated = append(consolidated, DataRange{
				begin: ranges[first].begin,
				end:   ranges[i].end,
			})
			first = i + 1
		}
	}

	return append(consolidated, DataRange{
		begin: ranges[first].begin,
		end:   ranges[len(ranges)-1].end,
	})
}
