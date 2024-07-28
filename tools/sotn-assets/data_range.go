package main

import (
	"fmt"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"sort"
)

type dataRange struct {
	begin psx.Addr
	end   psx.Addr
}

func (r dataRange) Format(f fmt.State, c rune) {
	f.Write([]byte(fmt.Sprintf("(%s, %s)", r.begin, r.end)))
}

func (r dataRange) empty() bool {
	return r.begin == psx.RamNull && r.end == psx.RamNull
}

func mergeDataRanges(ranges []dataRange) dataRange {
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

	return dataRange{
		begin: ranges[0].begin,
		end:   ranges[len(ranges)-1].end,
	}
}

func consolidateDataRanges(ranges []dataRange) []dataRange {
	if len(ranges) == 0 {
		return []dataRange{}
	}

	sort.Slice(ranges, func(i, j int) bool {
		return ranges[i].begin < ranges[j].begin
	})

	for ranges[0].empty() {
		ranges = ranges[1:]
	}

	consolidated := []dataRange{}
	first := 0
	for i := 0; i < len(ranges)-1; i++ {
		if ranges[i].end != ranges[i+1].begin {
			consolidated = append(consolidated, dataRange{
				begin: ranges[first].begin,
				end:   ranges[i].end,
			})
			first = i + 1
		}
	}

	return append(consolidated, dataRange{
		begin: ranges[first].begin,
		end:   ranges[len(ranges)-1].end,
	})
}
