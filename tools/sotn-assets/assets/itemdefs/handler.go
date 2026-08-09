package itemdefs

import (
	"bytes"
	"encoding/binary"
	"fmt"
	"os"
	"path/filepath"
	"strings"

	"github.com/goccy/go-yaml"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/sotn"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/util"
)

const (
	equipmentDeclaredSize = 0x32
	equipmentStride       = 0x34
	equipmentCount        = 217
	accessoryDeclaredSize = 0x1E
	accessoryStride       = 0x20
	accessoryCount        = 90
)

type itemKind int

const (
	kindEquipment itemKind = iota
	kindAccessory
)

type equipmentRawEntry struct {
	NameAddr                 uint32
	DescriptionAddr          uint32
	Attack                   int16
	Defense                  int16
	Element                  uint16
	ItemCategory             uint8
	WeaponID                 uint8
	Palette                  uint8
	Unknown11                uint8
	PlayerAnim               uint8
	Unknown13                uint8
	Unknown14                uint8
	LockDuration             uint8
	ChainLimit               uint8
	Unknown17                uint8
	SpecialMove              uint8
	IsConsumable             uint8
	EnemyInvincibilityFrames uint8
	Unknown1B                uint8
	ComboSub                 uint32
	ComboMain                uint32
	MPUsage                  uint16
	StunFrames               uint16
	HitType                  uint16
	HitEffect                uint16
	Icon                     uint16
	IconPalette              uint16
	CriticalRate             uint16
}

type equipmentModel struct {
	Name                     string   `yaml:"name"`
	Description              string   `yaml:"description"`
	Attack                   int16    `yaml:"attack"`
	Defense                  int16    `yaml:"defense"`
	Element                  []string `yaml:"element"`
	ItemCategory             string   `yaml:"item_category"`
	WeaponID                 uint8    `yaml:"weapon_id"`
	Palette                  uint8    `yaml:"palette"`
	Unknown11                uint8    `yaml:"unknown_11"`
	PlayerAnim               uint8    `yaml:"player_anim"`
	Unknown13                uint8    `yaml:"unknown_13"`
	Unknown14                uint8    `yaml:"unknown_14"`
	LockDuration             uint8    `yaml:"lock_duration"`
	ChainLimit               uint8    `yaml:"chain_limit"`
	Unknown17                uint8    `yaml:"unknown_17"`
	SpecialMove              uint8    `yaml:"special_move"`
	IsConsumable             bool     `yaml:"is_consumable"`
	EnemyInvincibilityFrames uint8    `yaml:"enemy_invincibility_frames"`
	Unknown1B                uint8    `yaml:"unknown_1b"`
	ComboSub                 uint32   `yaml:"combo_sub"`
	ComboMain                uint32   `yaml:"combo_main"`
	MPUsage                  uint16   `yaml:"mp_usage"`
	StunFrames               uint16   `yaml:"stun_frames"`
	HitType                  uint16   `yaml:"hit_type"`
	HitEffect                uint16   `yaml:"hit_effect"`
	Icon                     uint16   `yaml:"icon"`
	IconPalette              uint16   `yaml:"icon_palette"`
	CriticalRate             uint16   `yaml:"critical_rate"`
}

type accessoryRawEntry struct {
	NameAddr        uint32
	DescriptionAddr uint32
	AttackBonus     int16
	DefenseBonus    int16
	StatsBonus      [4]uint8
	WeakToElements  uint16
	ResistElements  uint16
	ImmuneElements  uint16
	AbsorbElements  uint16
	Icon            uint16
	IconPalette     uint16
	EquipType       uint16
}

type accessoryModel struct {
	Name           string   `yaml:"name"`
	Description    string   `yaml:"description"`
	AttackBonus    int16    `yaml:"attack_bonus"`
	DefenseBonus   int16    `yaml:"defense_bonus"`
	StatsBonus     [4]uint8 `yaml:"stats_bonus"`
	WeakToElements []string `yaml:"weak_to_elements"`
	ResistElements []string `yaml:"resist_elements"`
	ImmuneElements []string `yaml:"immune_elements"`
	AbsorbElements []string `yaml:"absorb_elements"`
	Icon           uint16   `yaml:"icon"`
	IconPalette    uint16   `yaml:"icon_palette"`
	EquipType      uint16   `yaml:"equip_type"`
}

type enumFields struct {
	elements   map[int]string
	categories map[int]string
}

type handler struct{}

var Handler = &handler{}

func (h *handler) Name() string { return "itemdefs" }

func (h *handler) Extract(e assets.ExtractArgs) error {
	kind, err := parseKind(e.Args)
	if err != nil {
		return err
	}
	fields, err := fetchEnumFields(kind)
	if err != nil {
		return err
	}

	var entries any
	switch kind {
	case kindEquipment:
		entries, err = parseEquipment(
			e.Data,
			e.Start,
			e.End,
			e.RamBase,
			e.Version.GetPlatform(),
			fields,
		)
	case kindAccessory:
		entries, err = parseAccessories(
			e.Data,
			e.Start,
			e.End,
			e.RamBase,
			e.Version.GetPlatform(),
			fields,
		)
	}
	if err != nil {
		return fmt.Errorf("parse error: %w", err)
	}

	asYAML, err := yaml.Marshal(entries)
	if err != nil {
		return fmt.Errorf("yaml error: %w", err)
	}
	return util.WriteFile(assetPath(e.AssetDir, e.Name), asYAML)
}

func (h *handler) Build(e assets.BuildArgs) error {
	kind, err := parseKind(e.Args)
	if err != nil {
		return err
	}

	inFileName := assetPath(e.AssetDir, e.Name)
	data, err := os.ReadFile(inFileName)
	if err != nil {
		return fmt.Errorf("failed to read file: %w", err)
	}

	var generated string
	switch kind {
	case kindEquipment:
		var serialized []equipmentModel
		if err := yaml.Unmarshal(data, &serialized); err != nil {
			return fmt.Errorf("failed to parse %s: %w", inFileName, err)
		}
		if len(serialized) != equipmentCount {
			return fmt.Errorf(
				"invalid equipment definitions in %s: got %d entries, expected %d",
				inFileName, len(serialized), equipmentCount)
		}
		generated, err = buildEquipment(serialized)
		if err != nil {
			return fmt.Errorf("build equipment definitions: %w", err)
		}
	case kindAccessory:
		var serialized []accessoryModel
		if err := yaml.Unmarshal(data, &serialized); err != nil {
			return fmt.Errorf("failed to parse %s: %w", inFileName, err)
		}
		if len(serialized) != accessoryCount {
			return fmt.Errorf(
				"invalid accessory definitions in %s: got %d entries, expected %d",
				inFileName, len(serialized), accessoryCount)
		}
		generated, err = buildAccessories(serialized)
		if err != nil {
			return fmt.Errorf("build accessory definitions: %w", err)
		}
	}
	return util.WriteFile(sourcePath(e.SrcDir, e.Name), []byte(generated))
}

func (h *handler) Info(a assets.InfoArgs) (assets.InfoResult, error) {
	return assets.InfoResult{}, nil
}

func assetPath(dir, name string) string {
	return filepath.Join(dir, fmt.Sprintf("%s.yaml", name))
}

func sourcePath(dir, name string) string {
	return filepath.Join(dir, fmt.Sprintf("gen/%s.h", name))
}

func parseKind(args []string) (itemKind, error) {
	if len(args) != 1 {
		return 0, fmt.Errorf(
			"itemdefs requires exactly one mode argument, got %d", len(args))
	}
	switch args[0] {
	case "equipment":
		return kindEquipment, nil
	case "accessory":
		return kindAccessory, nil
	default:
		return 0, fmt.Errorf(
			"unsupported itemdefs mode %q; expected equipment or accessory",
			args[0])
	}
}

func fetchEnumFields(kind itemKind) (enumFields, error) {
	var fields enumFields
	var err error
	switch kind {
	case kindEquipment:
		fields.categories, err =
			sotn.FetchEnum("include", "game", "ItemCategory")
		if err != nil {
			return fields, fmt.Errorf("fetch enum ItemCategory: %w", err)
		}
		if len(fields.categories) == 0 {
			return fields, fmt.Errorf("enum ItemCategory has no fields")
		}
	}
	fields.elements, err = sotn.FetchEnum("include", "game", "Elements")
	if err != nil {
		return fields, fmt.Errorf("fetch enum Elements: %w", err)
	}
	if len(fields.elements) == 0 {
		return fields, fmt.Errorf("enum Elements has no fields")
	}
	return fields, nil
}

func parseEquipment(
	data []byte,
	start, end int,
	ramBase psx.Addr,
	platform sotn.Platform,
	fields enumFields,
) ([]equipmentModel, error) {
	if size := binary.Size(equipmentRawEntry{}); size != equipmentDeclaredSize {
		return nil, fmt.Errorf(
			"equipment model has size %#x, expected %#x",
			size, equipmentDeclaredSize)
	}
	if err := validateRange(
		data, start, end, equipmentStride, equipmentCount, "equipment",
	); err != nil {
		return nil, err
	}

	entries := make([]equipmentModel, equipmentCount)
	for i := range entries {
		record := data[start+i*equipmentStride : start+(i+1)*equipmentStride]
		if err := validatePadding(
			record[equipmentDeclaredSize:], "equipment", i,
		); err != nil {
			return nil, err
		}
		var raw equipmentRawEntry
		if err := binary.Read(
			bytes.NewReader(record[:equipmentDeclaredSize]),
			binary.LittleEndian,
			&raw,
		); err != nil {
			return nil, fmt.Errorf("read equipment %#x: %w", i, err)
		}
		if raw.IsConsumable > 1 {
			return nil, fmt.Errorf(
				"equipment %#x has invalid isConsumable value %#x",
				i, raw.IsConsumable)
		}
		name, err := sotn.DecodeString(
			data, psx.Addr(raw.NameAddr), ramBase, platform)
		if err != nil {
			return nil, fmt.Errorf("equipment %#x name: %w", i, err)
		}
		description, err := sotn.DecodeMenuDescription(
			data, psx.Addr(raw.DescriptionAddr), ramBase, platform)
		if err != nil {
			return nil, fmt.Errorf(
				"equipment %#x description: %w", i, err)
		}
		entries[i] = equipmentModel{
			Name:                     name,
			Description:              description,
			Attack:                   raw.Attack,
			Defense:                  raw.Defense,
			Element:                  decodeFlags(raw.Element, fields.elements),
			ItemCategory:             decodeEnum(raw.ItemCategory, fields.categories, 2),
			WeaponID:                 raw.WeaponID,
			Palette:                  raw.Palette,
			Unknown11:                raw.Unknown11,
			PlayerAnim:               raw.PlayerAnim,
			Unknown13:                raw.Unknown13,
			Unknown14:                raw.Unknown14,
			LockDuration:             raw.LockDuration,
			ChainLimit:               raw.ChainLimit,
			Unknown17:                raw.Unknown17,
			SpecialMove:              raw.SpecialMove,
			IsConsumable:             raw.IsConsumable != 0,
			EnemyInvincibilityFrames: raw.EnemyInvincibilityFrames,
			Unknown1B:                raw.Unknown1B,
			ComboSub:                 raw.ComboSub,
			ComboMain:                raw.ComboMain,
			MPUsage:                  raw.MPUsage,
			StunFrames:               raw.StunFrames,
			HitType:                  raw.HitType,
			HitEffect:                raw.HitEffect,
			Icon:                     raw.Icon,
			IconPalette:              raw.IconPalette,
			CriticalRate:             raw.CriticalRate,
		}
	}
	return entries, nil
}

func parseAccessories(
	data []byte,
	start, end int,
	ramBase psx.Addr,
	platform sotn.Platform,
	fields enumFields,
) ([]accessoryModel, error) {
	if size := binary.Size(accessoryRawEntry{}); size != accessoryDeclaredSize {
		return nil, fmt.Errorf(
			"accessory model has size %#x, expected %#x",
			size, accessoryDeclaredSize)
	}
	if err := validateRange(
		data, start, end, accessoryStride, accessoryCount, "accessory",
	); err != nil {
		return nil, err
	}

	entries := make([]accessoryModel, accessoryCount)
	for i := range entries {
		record := data[start+i*accessoryStride : start+(i+1)*accessoryStride]
		if err := validatePadding(
			record[accessoryDeclaredSize:], "accessory", i,
		); err != nil {
			return nil, err
		}
		var raw accessoryRawEntry
		if err := binary.Read(
			bytes.NewReader(record[:accessoryDeclaredSize]),
			binary.LittleEndian,
			&raw,
		); err != nil {
			return nil, fmt.Errorf("read accessory %#x: %w", i, err)
		}
		name, err := sotn.DecodeString(
			data, psx.Addr(raw.NameAddr), ramBase, platform)
		if err != nil {
			return nil, fmt.Errorf("accessory %#x name: %w", i, err)
		}
		description, err := sotn.DecodeMenuDescription(
			data, psx.Addr(raw.DescriptionAddr), ramBase, platform)
		if err != nil {
			return nil, fmt.Errorf("accessory %#x description: %w", i, err)
		}
		entries[i] = accessoryModel{
			Name:           name,
			Description:    description,
			AttackBonus:    raw.AttackBonus,
			DefenseBonus:   raw.DefenseBonus,
			StatsBonus:     raw.StatsBonus,
			WeakToElements: decodeFlags(raw.WeakToElements, fields.elements),
			ResistElements: decodeFlags(raw.ResistElements, fields.elements),
			ImmuneElements: decodeFlags(raw.ImmuneElements, fields.elements),
			AbsorbElements: decodeFlags(raw.AbsorbElements, fields.elements),
			Icon:           raw.Icon,
			IconPalette:    raw.IconPalette,
			EquipType:      raw.EquipType,
		}
	}
	return entries, nil
}

func validateRange(
	data []byte,
	start, end, stride, expectedCount int,
	name string,
) error {
	if start < 0 || end < start || end > len(data) {
		return fmt.Errorf(
			"invalid %s range [%#x, %#x) for %#x bytes",
			name, start, end, len(data))
	}
	if (end-start)%stride != 0 {
		return fmt.Errorf(
			"%s range has size %#x, which is not a multiple of %#x",
			name, end-start, stride)
	}
	count := (end - start) / stride
	if count != expectedCount {
		return fmt.Errorf(
			"%s range has %d entries, expected %d",
			name, count, expectedCount)
	}
	return nil
}

func validatePadding(padding []byte, kind string, index int) error {
	for offset, value := range padding {
		if value != 0 {
			return fmt.Errorf(
				"%s %#x has non-zero compiler padding byte %#x at +%#x",
				kind, index, value, offset)
		}
	}
	return nil
}

func buildEquipment(entries []equipmentModel) (string, error) {
	var sb strings.Builder
	sb.WriteString("// clang-format off\n")
	platform := sotn.GetPlatform()
	for i, entry := range entries {
		name, err := formatName(entry.Name, platform)
		if err != nil {
			return "", fmt.Errorf("equipment %#x name: %w", i, err)
		}
		description, err := formatDescription(entry.Description, platform)
		if err != nil {
			return "", fmt.Errorf("equipment %#x description: %w", i, err)
		}
		fmt.Fprintf(
			&sb,
			"/* 0x%03X */ {%s, %s, %d, %d, %s, %s, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %t, %d, %d, 0x%08X, 0x%08X, %d, %d, %d, %d, %d, %d, %d},\n",
			i,
			name,
			description,
			entry.Attack,
			entry.Defense,
			formatFlags(entry.Element),
			entry.ItemCategory,
			entry.WeaponID,
			entry.Palette,
			entry.Unknown11,
			entry.PlayerAnim,
			entry.Unknown13,
			entry.Unknown14,
			entry.LockDuration,
			entry.ChainLimit,
			entry.Unknown17,
			entry.SpecialMove,
			entry.IsConsumable,
			entry.EnemyInvincibilityFrames,
			entry.Unknown1B,
			entry.ComboSub,
			entry.ComboMain,
			entry.MPUsage,
			entry.StunFrames,
			entry.HitType,
			entry.HitEffect,
			entry.Icon,
			entry.IconPalette,
			entry.CriticalRate,
		)
	}
	return sb.String(), nil
}

func buildAccessories(entries []accessoryModel) (string, error) {
	var sb strings.Builder
	sb.WriteString("// clang-format off\n")
	platform := sotn.GetPlatform()
	for i, entry := range entries {
		name, err := formatName(entry.Name, platform)
		if err != nil {
			return "", fmt.Errorf("accessory %#x name: %w", i, err)
		}
		description, err := formatDescription(entry.Description, platform)
		if err != nil {
			return "", fmt.Errorf("accessory %#x description: %w", i, err)
		}
		fmt.Fprintf(
			&sb,
			"/* 0x%02X */ {%s, %s, %d, %d, %d, %d, %d, %d, %s, %s, %s, %s, %d, %d, %d},\n",
			i,
			name,
			description,
			entry.AttackBonus,
			entry.DefenseBonus,
			entry.StatsBonus[0],
			entry.StatsBonus[1],
			entry.StatsBonus[2],
			entry.StatsBonus[3],
			formatFlags(entry.WeakToElements),
			formatFlags(entry.ResistElements),
			formatFlags(entry.ImmuneElements),
			formatFlags(entry.AbsorbElements),
			entry.Icon,
			entry.IconPalette,
			entry.EquipType,
		)
	}
	return sb.String(), nil
}

func decodeEnum(value uint8, fields map[int]string, width int) string {
	if name, ok := fields[int(value)]; ok {
		return name
	}
	return fmt.Sprintf("0x%0*X", width, value)
}

func decodeFlags(value uint16, fields map[int]string) []string {
	flags := make([]string, 0, 4)
	for flag := 1; flag < 0x10000; flag <<= 1 {
		if value&uint16(flag) == 0 {
			continue
		}
		name, ok := fields[flag]
		if !ok {
			name = fmt.Sprintf("0x%04X", flag)
		}
		flags = append(flags, name)
	}
	return flags
}

func formatFlags(flags []string) string {
	if len(flags) == 0 {
		return "0"
	}
	return strings.Join(flags, " | ")
}

func quoteCString(value string) string {
	var sb strings.Builder
	sb.WriteByte('"')
	for _, r := range value {
		switch r {
		case '\\':
			sb.WriteString(`\\`)
		case '"':
			sb.WriteString(`\"`)
		case '\n':
			sb.WriteString(`\n`)
		case '\r':
			sb.WriteString(`\r`)
		case '\t':
			sb.WriteString(`\t`)
		default:
			sb.WriteRune(r)
		}
	}
	sb.WriteByte('"')
	return sb.String()
}

func quoteHexBytes(value []byte) string {
	var sb strings.Builder
	sb.WriteByte('"')
	for _, b := range value {
		fmt.Fprintf(&sb, "\\x%02X", b)
	}
	sb.WriteByte('"')
	return sb.String()
}

func formatName(value string, platform sotn.Platform) (string, error) {
	// PSX/HD encode _S() after expanding includes; PSP runs sotn_str before
	// includes are expanded, so generated PSP headers must contain encoded bytes.
	if platform != sotn.PlatformPSP {
		return fmt.Sprintf("_S(%s)", quoteCString(value)), nil
	}
	encoded, err := sotn.EncodeString(value, platform)
	if err != nil {
		return "", err
	}
	return quoteHexBytes(encoded), nil
}

func formatDescription(value string, platform sotn.Platform) (string, error) {
	// Generated includes expand after the source-encoding pass on PSP. Byte-safe
	// literals also avoid host iconv differences and the Japanese compiler
	// treating Shift-JIS trail byte 0x5C as a source backslash on PSX/HD.
	encoded, err := sotn.EncodeMenuDescription(value, platform)
	if err != nil {
		return "", err
	}
	return quoteHexBytes(encoded), nil
}
