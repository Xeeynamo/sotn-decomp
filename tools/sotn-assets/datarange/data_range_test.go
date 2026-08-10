package datarange

import (
	"testing"

	"github.com/stretchr/testify/assert"
	"github.com/stretchr/testify/require"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
)

func TestConsolidateDataRanges(t *testing.T) {
	r := func(begin, end uint32) DataRange {
		return New(psx.Addr(begin), psx.Addr(end))
	}

	t.Run("adjacent ranges collapse", func(t *testing.T) {
		input := []DataRange{r(0x20, 0x30), r(0x10, 0x20)}
		got, err := ConsolidateDataRanges(input)
		require.NoError(t, err)
		assert.Equal(t, []DataRange{r(0x10, 0x30)}, got)
		assert.Equal(t, []DataRange{r(0x20, 0x30), r(0x10, 0x20)}, input)
	})

	t.Run("gap starts a new run", func(t *testing.T) {
		input := []DataRange{r(0x10, 0x20), r(0x30, 0x40)}
		assert.Panics(t, func() {
			MergeDataRanges(append([]DataRange(nil), input...))
		})

		got, err := ConsolidateDataRanges(input)
		require.NoError(t, err)
		assert.Equal(t, input, got)
	})

	t.Run("overlap is rejected", func(t *testing.T) {
		_, err := ConsolidateDataRanges(
			[]DataRange{r(0x10, 0x25), r(0x20, 0x30)})
		assert.ErrorContains(t, err, "overlap")
	})

	t.Run("empty input is rejected", func(t *testing.T) {
		_, err := ConsolidateDataRanges(nil)
		assert.Error(t, err)
	})
}
