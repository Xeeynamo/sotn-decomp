package enemydefs

import (
	"encoding/binary"
	"os"
	"path/filepath"
	"testing"

	"github.com/goccy/go-yaml"
	"github.com/stretchr/testify/require"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/sotn"
)

func TestParseEnemyDefs(t *testing.T) {
	const (
		base        = psx.Addr(0x800A0000)
		tableSize   = defaultEntryCount * entrySize
		emptyString = tableSize
		testString  = emptyString + 2
	)
	data := make([]byte, tableSize+0x10)
	for i := 0; i < defaultEntryCount; i++ {
		binary.LittleEndian.PutUint32(
			data[i*entrySize:], uint32(base+emptyString))
	}
	copy(data[emptyString:], []byte{0xFF, 0})
	copy(data[testString:], []byte{0x34, 0x45, 0x53, 0x54, 0xFF, 0})

	binary.LittleEndian.PutUint32(data[0x00:], uint32(base+testString))
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

	elements := map[int]string{
		0x20:   "ELEMENT_HIT",
		0x40:   "ELEMENT_CUT",
		0x1000: "ELEMENT_HOLY",
		0x8000: "ELEMENT_FIRE",
	}
	items := map[int]string{0x123: "ITEMDROP_TEST"}

	entries, err := parse(
		data,
		0,
		tableSize,
		base,
		sotn.PlatformPSX,
		defaultEntryCount,
		elements,
		items,
	)
	require.NoError(t, err)
	require.Len(t, entries, defaultEntryCount)
	require.Equal(t, enemyModel{
		ID:                   "0x000",
		Name:                 "Test",
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
	require.Equal(t, "0x18F", entries[defaultEntryCount-1].ID)
}

func TestParseEnemyDefsRejectsInvalidRanges(t *testing.T) {
	_, err := parse(
		make([]byte, entrySize-1),
		0,
		entrySize-1,
		psx.Addr(0x800A0000),
		sotn.PlatformPSX,
		defaultEntryCount,
		nil,
		nil,
	)
	require.ErrorContains(t, err, "not a multiple")

	_, err = parse(
		make([]byte, entrySize),
		0,
		entrySize,
		psx.Addr(0x800A0000),
		sotn.PlatformPSX,
		defaultEntryCount,
		nil,
		nil,
	)
	require.ErrorContains(t, err, "expected 400")
}

func TestBuildEnemyDefs(t *testing.T) {
	assetDir := filepath.Join(t.TempDir(), "assets")
	srcDir := filepath.Join(t.TempDir(), "src")
	name := "test/enemydefs"

	entries := make([]enemyModel, defaultEntryCount)
	for i := range entries {
		entries[i] = enemyModel{
			ID:            "0x" + formatIndex(i),
			AttackElement: []string{},
			Weaknesses:    []string{},
			Strengths:     []string{},
			Immunes:       []string{},
			Absorbs:       []string{},
			RareItem:      "0",
			UncommonItem:  "0",
		}
	}
	entries[6] = enemyModel{
		ID:                   "0x006",
		Name:                 "Test",
		HitPoints:            42,
		Attack:               10,
		AttackElement:        []string{"ELEMENT_HIT"},
		Defense:              6,
		HitboxState:          35,
		Weaknesses:           []string{},
		Strengths:            []string{},
		Immunes:              []string{},
		Absorbs:              []string{},
		Level:                9,
		Exp:                  50,
		RareItem:             "ITEMDROP_TEST",
		UncommonItem:         "0",
		RareItemDropRate:     2,
		UncommonItemDropRate: 0,
		HitboxWidth:          8,
		HitboxHeight:         24,
		Flags:                0xAA00D410,
	}
	serialized, err := yaml.Marshal(entries)
	require.NoError(t, err)
	require.NoError(t, os.MkdirAll(
		filepath.Dir(assetPath(assetDir, name)), 0o755))
	require.NoError(t, os.WriteFile(
		assetPath(assetDir, name), serialized, 0o644))

	require.NoError(t, Handler.Build(assets.BuildArgs{
		AssetDir: assetDir,
		SrcDir:   srcDir,
		Name:     name,
	}))
	generated, err := os.ReadFile(sourcePath(srcDir, name))
	require.NoError(t, err)
	require.Contains(
		t,
		string(generated),
		`/* 0x006 */ {_S("Test"), 42, 10, ELEMENT_HIT, 6, 35, 0, 0, 0, 0, 9, 50, ITEMDROP_TEST, 0, 2, 0, 8, 24, 0xAA00D410},`,
	)
}

func TestNormalizeEntriesRejectsInvalidIDs(t *testing.T) {
	entries := make([]enemyModel, defaultEntryCount)
	for i := range entries {
		entries[i].ID = "0x" + formatIndex(i)
	}

	entries[1].ID = entries[0].ID
	_, err := normalizeEntries(entries, defaultEntryCount)
	require.ErrorContains(t, err, "duplicate id")

	_, err = normalizeEntries(entries[:defaultEntryCount-1], defaultEntryCount)
	require.ErrorContains(t, err, "expected 400")
}

func TestEntryCount(t *testing.T) {
	count, err := entryCount(nil)
	require.NoError(t, err)
	require.Equal(t, 400, count)

	count, err = entryCount([]string{"401"})
	require.NoError(t, err)
	require.Equal(t, 401, count)

	_, err = entryCount([]string{"0"})
	require.ErrorContains(t, err, "invalid")
	_, err = entryCount([]string{"400", "401"})
	require.ErrorContains(t, err, "at most one")
}

func TestFormattingAndFallbacks(t *testing.T) {
	require.Equal(t, "0", formatFlags(nil))
	require.Equal(
		t,
		"ELEMENT_HIT | ELEMENT_HOLY",
		formatFlags([]string{"ELEMENT_HIT", "ELEMENT_HOLY"}),
	)
	require.Equal(
		t,
		[]string{"0x0001", "ELEMENT_HIT"},
		decodeFlags(0x21, map[int]string{0x20: "ELEMENT_HIT"}),
	)
	require.Equal(t, "0", decodeItem(0, nil))
	require.Equal(t, "0x0123", decodeItem(0x123, nil))
	require.Equal(
		t,
		`"Test \"Quote\"\\Path"`,
		quoteCString(`Test "Quote"\Path`),
	)
	psxName, err := formatName("Test", sotn.PlatformPSX)
	require.NoError(t, err)
	require.Equal(t, `_S("Test")`, psxName)
	pspName, err := formatName("Aé", sotn.PlatformPSP)
	require.NoError(t, err)
	require.Equal(t, `"\x21\xA0\xFF"`, pspName)
}

func formatIndex(index int) string {
	const digits = "0123456789ABCDEF"
	return string([]byte{
		digits[index>>8&0xF],
		digits[index>>4&0xF],
		digits[index&0xF],
	})
}
