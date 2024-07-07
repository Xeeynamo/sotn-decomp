package main

import (
	"fmt"
	"sort"
)

type dataRange struct {
	begin PsxOffset
	end   PsxOffset
}

func (r dataRange) Format(f fmt.State, c rune) {
	f.Write([]byte(fmt.Sprintf("(%s, %s)", r.begin, r.end)))
}

func (r dataRange) empty() bool {
	return r.begin == RamNull && r.end == RamNull
}

func getDataRangeBegin(ranges []dataRange) PsxOffset {
	if len(ranges) == 0 {
		panic(fmt.Errorf("range array cannot be empty"))
	}
	earliest := ranges[0].begin
	for _, rng := range ranges[1:] {
		if earliest > rng.begin {
			earliest = rng.begin
		}
	}
	return earliest
}

func sortDataRanges(ranges []dataRange) {
	sort.Slice(ranges, func(i, j int) bool {
		return ranges[i].begin < ranges[j].begin
	})
}

func mergeDataRanges(ranges []dataRange) dataRange {
	if len(ranges) == 0 {
		err := fmt.Errorf("no datarange, bug?!")
		panic(err)
	}

	sortDataRanges(ranges)

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
