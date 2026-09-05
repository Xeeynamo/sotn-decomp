package itemdefs

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

func TestParseEquipment(t *testing.T) {
	const (
		base      = psx.Addr(0x800A0000)
		tableSize = equipmentCount * equipmentStride
		emptyName = tableSize
		emptyDesc = emptyName + 2
		testName  = emptyDesc + 1
		testDesc  = testName + 6
	)
	data := make([]byte, tableSize+0x40)
	for i := 0; i < equipmentCount; i++ {
		offset := i * equipmentStride
		binary.LittleEndian.PutUint32(
			data[offset:], uint32(base+emptyName))
		binary.LittleEndian.PutUint32(
			data[offset+4:], uint32(base+emptyDesc))
	}
	copy(data[emptyName:], []byte{0xFF, 0})
	data[emptyDesc] = 0
	copy(data[testName:], []byte{0x34, 0x45, 0x53, 0x54, 0xFF, 0})
	copy(data[testDesc:], append([]byte(`Test "description"`), 0))

	binary.LittleEndian.PutUint32(data[0x00:], uint32(base+testName))
	binary.LittleEndian.PutUint32(data[0x04:], uint32(base+testDesc))
	binary.LittleEndian.PutUint16(data[0x08:], uint16(42))
	binary.LittleEndian.PutUint16(data[0x0A:], uint16(0xFFFE))
	binary.LittleEndian.PutUint16(data[0x0C:], 0x9020)
	data[0x0E] = 3
	data[0x0F] = 4
	data[0x10] = 5
	data[0x11] = 6
	data[0x12] = 7
	data[0x13] = 8
	data[0x14] = 9
	data[0x15] = 10
	data[0x16] = 11
	data[0x17] = 12
	data[0x18] = 13
	data[0x19] = 1
	data[0x1A] = 14
	data[0x1B] = 15
	binary.LittleEndian.PutUint32(data[0x1C:], 0x12345678)
	binary.LittleEndian.PutUint32(data[0x20:], 0x9ABCDEF0)
	binary.LittleEndian.PutUint16(data[0x24:], 16)
	binary.LittleEndian.PutUint16(data[0x26:], 17)
	binary.LittleEndian.PutUint16(data[0x28:], 18)
	binary.LittleEndian.PutUint16(data[0x2A:], 19)
	binary.LittleEndian.PutUint16(data[0x2C:], 20)
	binary.LittleEndian.PutUint16(data[0x2E:], 21)
	binary.LittleEndian.PutUint16(data[0x30:], 22)

	fields := enumFields{
		elements:   map[int]string{0x20: "ELEMENT_HIT", 0x1000: "ELEMENT_HOLY"},
		categories: map[int]string{3: "ITEM_FIST"},
	}
	entries, err := parseEquipment(
		data, 0, tableSize, base, sotn.PlatformPSX, fields)
	require.NoError(t, err)
	require.Len(t, entries, equipmentCount)
	require.Equal(t, equipmentModel{
		Name:                     "Test",
		Description:              `Test "description"`,
		Attack:                   42,
		Defense:                  -2,
		Element:                  []string{"ELEMENT_HIT", "ELEMENT_HOLY", "0x8000"},
		ItemCategory:             "ITEM_FIST",
		WeaponID:                 4,
		Palette:                  5,
		Unknown11:                6,
		PlayerAnim:               7,
		Unknown13:                8,
		Unknown14:                9,
		LockDuration:             10,
		ChainLimit:               11,
		Unknown17:                12,
		SpecialMove:              13,
		IsConsumable:             true,
		EnemyInvincibilityFrames: 14,
		Unknown1B:                15,
		ComboSub:                 0x12345678,
		ComboMain:                0x9ABCDEF0,
		MPUsage:                  16,
		StunFrames:               17,
		HitType:                  18,
		HitEffect:                19,
		Icon:                     20,
		IconPalette:              21,
		CriticalRate:             22,
	}, entries[0])
}

func TestParseAccessories(t *testing.T) {
	const (
		base      = psx.Addr(0x800A0000)
		tableSize = accessoryCount * accessoryStride
		emptyName = tableSize
		emptyDesc = emptyName + 2
		testName  = emptyDesc + 1
		testDesc  = testName + 6
	)
	data := make([]byte, tableSize+0x40)
	for i := 0; i < accessoryCount; i++ {
		offset := i * accessoryStride
		binary.LittleEndian.PutUint32(
			data[offset:], uint32(base+emptyName))
		binary.LittleEndian.PutUint32(
			data[offset+4:], uint32(base+emptyDesc))
	}
	copy(data[emptyName:], []byte{0xFF, 0})
	data[emptyDesc] = 0
	copy(data[testName:], []byte{0x34, 0x45, 0x53, 0x54, 0xFF, 0})
	copy(data[testDesc:], append([]byte("Accessory"), 0))

	binary.LittleEndian.PutUint32(data[0x00:], uint32(base+testName))
	binary.LittleEndian.PutUint32(data[0x04:], uint32(base+testDesc))
	binary.LittleEndian.PutUint16(data[0x08:], uint16(0xFFFF))
	binary.LittleEndian.PutUint16(data[0x0A:], 2)
	copy(data[0x0C:], []byte{3, 4, 5, 6})
	binary.LittleEndian.PutUint16(data[0x10:], 0x20)
	binary.LittleEndian.PutUint16(data[0x12:], 0x40)
	binary.LittleEndian.PutUint16(data[0x14:], 0x1000)
	binary.LittleEndian.PutUint16(data[0x16:], 0x8000)
	binary.LittleEndian.PutUint16(data[0x18:], 7)
	binary.LittleEndian.PutUint16(data[0x1A:], 8)
	binary.LittleEndian.PutUint16(data[0x1C:], 9)

	fields := enumFields{
		elements: map[int]string{
			0x20: "ELEMENT_HIT", 0x40: "ELEMENT_CUT",
			0x1000: "ELEMENT_HOLY", 0x8000: "ELEMENT_FIRE",
		},
	}
	entries, err := parseAccessories(
		data, 0, tableSize, base, sotn.PlatformPSX, fields)
	require.NoError(t, err)
	require.Len(t, entries, accessoryCount)
	require.Equal(t, accessoryModel{
		Name:           "Test",
		Description:    "Accessory",
		AttackBonus:    -1,
		DefenseBonus:   2,
		StatsBonus:     [4]uint8{3, 4, 5, 6},
		WeakToElements: []string{"ELEMENT_HIT"},
		ResistElements: []string{"ELEMENT_CUT"},
		ImmuneElements: []string{"ELEMENT_HOLY"},
		AbsorbElements: []string{"ELEMENT_FIRE"},
		Icon:           7,
		IconPalette:    8,
		EquipType:      9,
	}, entries[0])
}

func TestParseRejectsInvalidRangesAndPadding(t *testing.T) {
	_, err := parseEquipment(
		make([]byte, equipmentStride-1),
		0,
		equipmentStride-1,
		psx.Addr(0x800A0000),
		sotn.PlatformPSX,
		enumFields{},
	)
	require.ErrorContains(t, err, "not a multiple")

	_, err = parseAccessories(
		make([]byte, accessoryStride),
		0,
		accessoryStride,
		psx.Addr(0x800A0000),
		sotn.PlatformPSX,
		enumFields{},
	)
	require.ErrorContains(t, err, "expected 90")

	equipment := syntheticEquipmentData()
	equipment[equipmentDeclaredSize] = 1
	_, err = parseEquipment(
		equipment,
		0,
		equipmentCount*equipmentStride,
		psx.Addr(0x800A0000),
		sotn.PlatformPSX,
		enumFields{},
	)
	require.ErrorContains(t, err, "non-zero compiler padding")

	accessories := syntheticAccessoryData()
	accessories[accessoryDeclaredSize+1] = 1
	_, err = parseAccessories(
		accessories,
		0,
		accessoryCount*accessoryStride,
		psx.Addr(0x800A0000),
		sotn.PlatformPSX,
		enumFields{},
	)
	require.ErrorContains(t, err, "non-zero compiler padding")
}

func TestParseEquipmentRejectsInvalidBoolean(t *testing.T) {
	data := syntheticEquipmentData()
	data[0x19] = 2
	_, err := parseEquipment(
		data,
		0,
		equipmentCount*equipmentStride,
		psx.Addr(0x800A0000),
		sotn.PlatformPSX,
		enumFields{},
	)
	require.ErrorContains(t, err, "invalid isConsumable")
}

func TestBuildEquipmentAndAccessories(t *testing.T) {
	t.Setenv("VERSION", "us")
	equipment := []equipmentModel{{
		Name:         `Test "name"`,
		Description:  `Test "description"`,
		Attack:       -2,
		Defense:      3,
		Element:      []string{"ELEMENT_HIT", "0x8000"},
		ItemCategory: "ITEM_FIST",
		IsConsumable: true,
		ComboSub:     0x12345678,
		ComboMain:    0x9ABCDEF0,
	}}
	generated, err := buildEquipment(equipment)
	require.NoError(t, err)
	require.Contains(t, generated, `_S("Test \"name\"")`)
	require.Contains(
		t,
		generated,
		`"\x54\x65\x73\x74\x20\x22\x64\x65\x73\x63\x72\x69\x70\x74\x69\x6F\x6E\x22"`,
	)
	require.Contains(t, generated, "ELEMENT_HIT | 0x8000, ITEM_FIST")
	require.Contains(t, generated, "true")
	require.Contains(t, generated, "0x12345678, 0x9ABCDEF0")

	accessories := []accessoryModel{{
		Name:           "Test",
		Description:    "Accessory",
		AttackBonus:    -1,
		DefenseBonus:   2,
		StatsBonus:     [4]uint8{3, 4, 5, 6},
		WeakToElements: []string{},
		ResistElements: []string{"ELEMENT_CUT"},
		ImmuneElements: []string{},
		AbsorbElements: []string{},
		Icon:           7,
		IconPalette:    8,
		EquipType:      9,
	}}
	generated, err = buildAccessories(accessories)
	require.NoError(t, err)
	require.Contains(
		t,
		generated,
		`_S("Test"), "\x41\x63\x63\x65\x73\x73\x6F\x72\x79", -1, 2, 3, 4, 5, 6, 0, ELEMENT_CUT, 0, 0, 7, 8, 9`,
	)
}

func TestBuildPSPPreencodesNamesAndDescriptions(t *testing.T) {
	t.Setenv("VERSION", "pspeu")
	generated, err := buildEquipment([]equipmentModel{{
		Name:         "Aé",
		Description:  "Cadáveres",
		ItemCategory: "ITEM_FIST",
	}})
	require.NoError(t, err)
	require.Contains(t, generated, `"\x21\xA0\xFF"`)
	require.Contains(
		t,
		generated,
		`"\x43\x61\x64\xCC\x76\x65\x72\x65\x73"`,
	)
	require.NotContains(t, generated, "_S(")
	require.NotContains(t, generated, "_SE(")
}

func TestBuildHDUsesByteSafeDescriptions(t *testing.T) {
	t.Setenv("VERSION", "hd")
	generated, err := buildEquipment([]equipmentModel{{
		Name:         "Test",
		Description:  "ソtest",
		ItemCategory: "ITEM_FIST",
	}})
	require.NoError(t, err)
	require.Contains(t, generated, `_S("Test")`)
	require.Contains(t, generated, `"\x83\x5C\x74\x65\x73\x74"`)
}

func TestBuildRejectsWrongEntryCount(t *testing.T) {
	t.Setenv("VERSION", "us")
	assetDir := filepath.Join(t.TempDir(), "assets")
	srcDir := filepath.Join(t.TempDir(), "src")
	name := "dra/equipment"

	serialized, err := yaml.Marshal(make([]equipmentModel, equipmentCount-1))
	require.NoError(t, err)
	require.NoError(t, os.MkdirAll(
		filepath.Dir(assetPath(assetDir, name)), 0o755))
	require.NoError(t, os.WriteFile(
		assetPath(assetDir, name), serialized, 0o644))

	err = Handler.Build(assets.BuildArgs{
		AssetDir: assetDir,
		SrcDir:   srcDir,
		Name:     name,
		Args:     []string{"equipment"},
	})
	require.ErrorContains(t, err, "got 216 entries, expected 217")
}

func TestParseKind(t *testing.T) {
	kind, err := parseKind([]string{"equipment"})
	require.NoError(t, err)
	require.Equal(t, kindEquipment, kind)

	kind, err = parseKind([]string{"accessory"})
	require.NoError(t, err)
	require.Equal(t, kindAccessory, kind)

	_, err = parseKind(nil)
	require.ErrorContains(t, err, "exactly one")
	_, err = parseKind([]string{"unknown"})
	require.ErrorContains(t, err, "unsupported")
}

func TestFormattingAndFallbacks(t *testing.T) {
	require.Equal(t, "0x03", decodeEnum(3, nil, 2))
	require.Equal(
		t,
		[]string{"0x0001", "ELEMENT_HIT"},
		decodeFlags(0x21, map[int]string{0x20: "ELEMENT_HIT"}),
	)
	require.Equal(t, "0", formatFlags(nil))
	require.Equal(t, `"Test \"Quote\"\\Path"`, quoteCString(`Test "Quote"\Path`))
}

func syntheticEquipmentData() []byte {
	const (
		base      = psx.Addr(0x800A0000)
		tableSize = equipmentCount * equipmentStride
		name      = tableSize
		desc      = name + 2
	)
	data := make([]byte, tableSize+3)
	for i := 0; i < equipmentCount; i++ {
		offset := i * equipmentStride
		binary.LittleEndian.PutUint32(data[offset:], uint32(base+name))
		binary.LittleEndian.PutUint32(data[offset+4:], uint32(base+desc))
	}
	copy(data[name:], []byte{0xFF, 0})
	data[desc] = 0
	return data
}

func syntheticAccessoryData() []byte {
	const (
		base      = psx.Addr(0x800A0000)
		tableSize = accessoryCount * accessoryStride
		name      = tableSize
		desc      = name + 2
	)
	data := make([]byte, tableSize+3)
	for i := 0; i < accessoryCount; i++ {
		offset := i * accessoryStride
		binary.LittleEndian.PutUint32(data[offset:], uint32(base+name))
		binary.LittleEndian.PutUint32(data[offset+4:], uint32(base+desc))
	}
	copy(data[name:], []byte{0xFF, 0})
	data[desc] = 0
	return data
}
