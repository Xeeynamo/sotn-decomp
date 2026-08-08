package spritebanks

import (
	"testing"

	"github.com/stretchr/testify/assert"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/datarange"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
)

func TestFirstGap(t *testing.T) {
	r := func(begin, end uint32) datarange.DataRange {
		return datarange.New(psx.Addr(begin), psx.Addr(end))
	}

	t.Run("no gap between adjacent ranges", func(t *testing.T) {
		_, _, found := firstGap([]datarange.DataRange{
			r(0x80180000, 0x80180100),
			r(0x80180100, 0x80180200),
		})
		assert.False(t, found)
	})

	t.Run("finds the hole between two ranges", func(t *testing.T) {
		begin, end, found := firstGap([]datarange.DataRange{
			r(0x80180000, 0x80180100),
			r(0x80180200, 0x80180300),
		})
		assert.True(t, found)
		assert.Equal(t, psx.Addr(0x80180100), begin)
		assert.Equal(t, psx.Addr(0x80180200), end)
	})

	t.Run("finds the lowest hole regardless of input order", func(t *testing.T) {
		begin, end, found := firstGap([]datarange.DataRange{
			r(0x80180400, 0x80180500),
			r(0x80180000, 0x80180100),
			r(0x80180200, 0x80180300),
		})
		assert.True(t, found)
		assert.Equal(t, psx.Addr(0x80180100), begin)
		assert.Equal(t, psx.Addr(0x80180200), end)
	})

	t.Run("a range enclosed by another leaves no hole", func(t *testing.T) {
		_, _, found := firstGap([]datarange.DataRange{
			r(0x80180000, 0x80180400),
			r(0x80180100, 0x80180200),
		})
		assert.False(t, found)
	})

	t.Run("a single range has no hole", func(t *testing.T) {
		_, _, found := firstGap([]datarange.DataRange{r(0x80180000, 0x80180100)})
		assert.False(t, found)
	})

	t.Run("no ranges have no hole", func(t *testing.T) {
		_, _, found := firstGap(nil)
		assert.False(t, found)
	})
}
