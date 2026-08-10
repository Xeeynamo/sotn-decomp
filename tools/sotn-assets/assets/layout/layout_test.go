package layout

import (
	"bytes"
	"encoding/binary"
	"testing"

	"github.com/stretchr/testify/assert"
	"github.com/stretchr/testify/require"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/datarange"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
)

func TestReadEntityLayoutPreservesUnclaimedRanges(t *testing.T) {
	const count = 2
	base := psx.Addr(0x80180000)
	data := make([]byte, 0xA0)

	blockOffsets := []int{0x20, 0x40, 0x60, 0x80}
	for i, off := range blockOffsets {
		binary.LittleEndian.PutUint32(data[i*4:], uint32(base.Sum(off)))
		binary.LittleEndian.PutUint16(data[off:], uint16(0xFFFE))
		binary.LittleEndian.PutUint16(data[off+2:], uint16(0xFFFE))
		binary.LittleEndian.PutUint16(data[off+10:], uint16(0xFFFF))
		binary.LittleEndian.PutUint16(data[off+12:], uint16(0xFFFF))
	}

	layouts, ranges, err := readEntityLayout(
		bytes.NewReader(data), "dummy", base, base, count, true)
	require.NoError(t, err)
	assert.Len(t, layouts.Entities, count)
	assert.Equal(t, []datarange.DataRange{
		datarange.New(base, base.Sum(0x10)),
		datarange.New(base.Sum(0x20), base.Sum(0x34)),
		datarange.New(base.Sum(0x40), base.Sum(0x54)),
		datarange.New(base.Sum(0x60), base.Sum(0x74)),
		datarange.New(base.Sum(0x80), base.Sum(0x94)),
	}, ranges)
}
