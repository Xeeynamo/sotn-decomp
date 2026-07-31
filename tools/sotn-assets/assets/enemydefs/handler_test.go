package enemydefs

import (
	"encoding/binary"
	"testing"

	"github.com/stretchr/testify/require"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
)

func TestDecodePSXString(t *testing.T) {
	const base = psx.Addr(0x800A0000)
	tests := []struct {
		name string
		data []byte
		want string
	}{
		{name: "empty", data: []byte{0xFF, 0}, want: ""},
		{
			name: "ascii",
			data: []byte{0x21, 0x58, 0x45, 0x00, 0x2B, 0x4E, 0x49, 0x47, 0x48, 0x54, 0xFF, 0},
			want: "Axe Knight",
		},
		{
			name: "dakuten",
			data: []byte{0x76, 0xFF, 0x9E, 0xFF, 0},
			want: "ガ",
		},
		{
			name: "special moon",
			data: []byte{0xFF, 0xFF, 0xFF, 0},
			want: "月",
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			got, err := decodePSXString(tt.data, base, base)
			require.NoError(t, err)
			require.Equal(t, tt.want, got)
		})
	}
}

func TestDecodePSXStringRejectsInvalidPointersAndStrings(t *testing.T) {
	const base = psx.Addr(0x800A0000)
	_, err := decodePSXString([]byte{0xFF, 0}, base-1, base)
	require.ErrorContains(t, err, "precedes RAM base")

	_, err = decodePSXString([]byte{0xFF, 0}, base+2, base)
	require.ErrorContains(t, err, "resolves outside")

	_, err = decodePSXString([]byte{0x21, 0xFF}, base, base)
	require.ErrorContains(t, err, "unterminated")

	_, err = decodePSXString([]byte{0xFF, 0x01}, base, base)
	require.ErrorContains(t, err, "unknown string escape")
}

func TestParseEnemyDefs(t *testing.T) {
	const (
		base        = psx.Addr(0x800A0000)
		stringStart = 0x40
	)
	data := make([]byte, 0x50)
	binary.LittleEndian.PutUint32(data[0x00:], uint32(base+stringStart))
	binary.LittleEndian.PutUint16(data[0x04:], 42)
	binary.LittleEndian.PutUint16(data[0x06:], 10)
	binary.LittleEndian.PutUint16(data[0x08:], 0x9020)
	binary.LittleEndian.PutUint16(data[0x0A:], 6)
	binary.LittleEndian.PutUint16(data[0x0C:], 35)
	binary.LittleEndian.PutUint16(data[0x0E:], 0x8000)
	binary.LittleEndian.PutUint16(data[0x10:], 0x0040)
	binary.LittleEndian.PutUint16(data[0x12:], 0x1000)
	binary.LittleEndian.PutUint16(data[0x14:], 0x0000)
	binary.LittleEndian.PutUint16(data[0x16:], 9)
	binary.LittleEndian.PutUint16(data[0x18:], 50)
	binary.LittleEndian.PutUint16(data[0x1A:], 0x123)
	binary.LittleEndian.PutUint16(data[0x1C:], 0)
	binary.LittleEndian.PutUint16(data[0x1E:], 2)
	binary.LittleEndian.PutUint16(data[0x20:], 16)
	data[0x22] = 8
	data[0x23] = 24
	binary.LittleEndian.PutUint32(data[0x24:], 0xAA00D410)
	copy(data[stringStart:], []byte{
		0x21, 0x58, 0x45, 0x00, 0x2B, 0x4E, 0x49, 0x47, 0x48, 0x54, 0xFF, 0,
	})

	elements := map[int]string{
		0x20:   "ELEMENT_HIT",
		0x40:   "ELEMENT_CUT",
		0x1000: "ELEMENT_HOLY",
		0x8000: "ELEMENT_FIRE",
	}
	items := map[int]string{0x123: "ITEMDROP_TEST"}

	entries, err := parse(data, 0, entrySize, base, elements, items)
	require.NoError(t, err)
	require.Len(t, entries, 1)
	require.Equal(t, enemyModel{
		Name:                 "Axe Knight",
		HitPoints:            42,
		Attack:               10,
		AttackElement:        []string{"ELEMENT_HIT", "ELEMENT_HOLY", "ELEMENT_FIRE"},
		Defense:              6,
		HitboxState:          35,
		Weaknesses:           []string{"ELEMENT_FIRE"},
		Strengths:            []string{"ELEMENT_CUT"},
		Immunes:              []string{"ELEMENT_HOLY"},
		Absorbs:              []string{},
		Level:                9,
		Exp:                  50,
		RareItem:             "ITEMDROP_TEST",
		UncommonItem:         "0",
		RareItemDropRate:     2,
		UncommonItemDropRate: 16,
		HitboxWidth:          8,
		HitboxHeight:         24,
		Flags:                0xAA00D410,
	}, entries[0])
}

func TestParseEnemyDefsRejectsPartialEntry(t *testing.T) {
	_, err := parse(
		make([]byte, entrySize-1),
		0,
		entrySize-1,
		psx.Addr(0x800A0000),
		nil,
		nil,
	)
	require.ErrorContains(t, err, "not a multiple")
}

func TestFormatting(t *testing.T) {
	require.Equal(t, "0", formatFlags(nil))
	require.Equal(
		t,
		"ELEMENT_HIT | ELEMENT_HOLY",
		formatFlags([]string{"ELEMENT_HIT", "ELEMENT_HOLY"}),
	)
	require.Equal(t, `"Axe \"Knight\"\\Lord"`, quoteCString(`Axe "Knight"\Lord`))
}
