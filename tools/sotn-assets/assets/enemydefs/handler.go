package enemydefs

import (
	"bytes"
	"encoding/binary"
	"fmt"
	"os"
	"path/filepath"
	"strconv"
	"strings"

	"github.com/goccy/go-yaml"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/assets"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/sotn"
	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/util"
)

const (
	entrySize         = 0x28
	defaultEntryCount = 400
)

type enemyRawEntry struct {
	NameAddr             uint32
	HitPoints            int16
	Attack               int16
	AttackElement        uint16
	Defense              int16
	HitboxState          uint16
	Weaknesses           uint16
	Strengths            uint16
	Immunes              uint16
	Absorbs              uint16
	Level                uint16
	Exp                  uint16
	RareItemId           uint16
	UncommonItemId       uint16
	RareItemDropRate     uint16
	UncommonItemDropRate uint16
	HitboxWidth          uint8
	HitboxHeight         uint8
	Flags                uint32
}

type enemyModel struct {
	ID                   string   `yaml:"id"`
	Name                 string   `yaml:"name"`
	HitPoints            int16    `yaml:"hit_points"`
	Attack               int16    `yaml:"attack"`
	AttackElement        []string `yaml:"attack_element"`
	Defense              int16    `yaml:"defense"`
	HitboxState          uint16   `yaml:"hitbox_state"`
	Weaknesses           []string `yaml:"weaknesses"`
	Strengths            []string `yaml:"strengths"`
	Immunes              []string `yaml:"immunes"`
	Absorbs              []string `yaml:"absorbs"`
	Level                uint16   `yaml:"level"`
	Exp                  uint16   `yaml:"exp"`
	RareItem             string   `yaml:"rare_item"`
	UncommonItem         string   `yaml:"uncommon_item"`
	RareItemDropRate     uint16   `yaml:"rare_item_drop_rate"`
	UncommonItemDropRate uint16   `yaml:"uncommon_item_drop_rate"`
	HitboxWidth          uint8    `yaml:"hitbox_width"`
	HitboxHeight         uint8    `yaml:"hitbox_height"`
	// EnemyDef declares flags as s32, but this is a bitfield. Keep its unsigned
	// representation so YAML and generated hexadecimal literals preserve the
	// original bits without displaying negative decimal values.
	Flags uint32 `yaml:"flags"`
}

type handler struct{}

var Handler = &handler{}

func (h *handler) Name() string { return "enemydefs" }

func (h *handler) Extract(e assets.ExtractArgs) error {
	elementFields, err := sotn.FetchEnum("include", "game", "Elements")
	if err != nil {
		return fmt.Errorf("fetch enum Elements: %w", err)
	}
	if len(elementFields) == 0 {
		return fmt.Errorf("enum Elements has no fields")
	}
	itemFields, err := sotn.FetchEnum("include", "items", "ItemDrops")
	if err != nil {
		return fmt.Errorf("fetch enum ItemDrops: %w", err)
	}
	if len(itemFields) == 0 {
		return fmt.Errorf("enum ItemDrops has no fields")
	}
	expectedCount, err := entryCount(e.Args)
	if err != nil {
		return err
	}

	entries, err := parse(
		e.Data,
		e.Start,
		e.End,
		e.RamBase,
		e.Version.GetPlatform(),
		expectedCount,
		elementFields,
		itemFields,
	)
	if err != nil {
		return fmt.Errorf("parse error: %w", err)
	}
	asYaml, err := yaml.Marshal(entries)
	if err != nil {
		return fmt.Errorf("yaml error: %w", err)
	}
	return util.WriteFile(assetPath(e.AssetDir, e.Name), asYaml)
}

func (h *handler) Build(e assets.BuildArgs) error {
	inFileName := assetPath(e.AssetDir, e.Name)
	data, err := os.ReadFile(inFileName)
	if err != nil {
		return fmt.Errorf("failed to read file: %w", err)
	}
	var serializedEntries []enemyModel
	if err := yaml.Unmarshal(data, &serializedEntries); err != nil {
		return fmt.Errorf("failed to parse %s: %w", inFileName, err)
	}
	expectedCount, err := entryCount(e.Args)
	if err != nil {
		return err
	}
	entries, err := normalizeEntries(serializedEntries, expectedCount)
	if err != nil {
		return fmt.Errorf("invalid enemy definitions in %s: %w", inFileName, err)
	}

	var sb strings.Builder
	sb.WriteString("// clang-format off\n")
	platform := sotn.GetPlatform()
	for i, entry := range entries {
		name, err := formatName(entry.Name, platform)
		if err != nil {
			return fmt.Errorf("enemy %#x name: %w", i, err)
		}
		fmt.Fprintf(
			&sb,
			"/* 0x%03X */ {%s, %d, %d, %s, %d, %d, %s, %s, %s, %s, %d, %d, %s, %s, %d, %d, %d, %d, 0x%08X},\n",
			i,
			name,
			entry.HitPoints,
			entry.Attack,
			formatFlags(entry.AttackElement),
			entry.Defense,
			entry.HitboxState,
			formatFlags(entry.Weaknesses),
			formatFlags(entry.Strengths),
			formatFlags(entry.Immunes),
			formatFlags(entry.Absorbs),
			entry.Level,
			entry.Exp,
			entry.RareItem,
			entry.UncommonItem,
			entry.RareItemDropRate,
			entry.UncommonItemDropRate,
			entry.HitboxWidth,
			entry.HitboxHeight,
			entry.Flags,
		)
	}
	return util.WriteFile(sourcePath(e.SrcDir, e.Name), []byte(sb.String()))
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

func parse(
	data []byte,
	start, end int,
	ramBase psx.Addr,
	platform sotn.Platform,
	expectedCount int,
	elements, items map[int]string,
) ([]enemyModel, error) {
	if size := binary.Size(enemyRawEntry{}); size != entrySize {
		return nil, fmt.Errorf(
			"enemy definition model has size %#x, expected %#x",
			size, entrySize)
	}
	if start < 0 || end < start || end > len(data) {
		return nil, fmt.Errorf(
			"invalid enemy definition range [%#x, %#x) for %#x bytes",
			start, end, len(data))
	}
	if (end-start)%entrySize != 0 {
		return nil, fmt.Errorf(
			"enemy definition range has size %#x, which is not a multiple of %#x",
			end-start, entrySize)
	}

	count := (end - start) / entrySize
	if count != expectedCount {
		return nil, fmt.Errorf(
			"enemy definition range has %d entries, expected %d",
			count, expectedCount)
	}
	rawEntries := make([]enemyRawEntry, count)
	if err := binary.Read(
		bytes.NewReader(data[start:end]), binary.LittleEndian, &rawEntries,
	); err != nil {
		return nil, fmt.Errorf("read enemy definitions: %w", err)
	}

	entries := make([]enemyModel, count)
	for i, raw := range rawEntries {
		name, err := sotn.DecodeString(
			data, psx.Addr(raw.NameAddr), ramBase, platform)
		if err != nil {
			return nil, fmt.Errorf("enemy %#x name: %w", i, err)
		}
		entries[i] = enemyModel{
			ID:                   fmt.Sprintf("0x%03X", i),
			Name:                 name,
			HitPoints:            raw.HitPoints,
			Attack:               raw.Attack,
			AttackElement:        decodeFlags(raw.AttackElement, elements),
			Defense:              raw.Defense,
			HitboxState:          raw.HitboxState,
			Weaknesses:           decodeFlags(raw.Weaknesses, elements),
			Strengths:            decodeFlags(raw.Strengths, elements),
			Immunes:              decodeFlags(raw.Immunes, elements),
			Absorbs:              decodeFlags(raw.Absorbs, elements),
			Level:                raw.Level,
			Exp:                  raw.Exp,
			RareItem:             decodeItem(raw.RareItemId, items),
			UncommonItem:         decodeItem(raw.UncommonItemId, items),
			RareItemDropRate:     raw.RareItemDropRate,
			UncommonItemDropRate: raw.UncommonItemDropRate,
			HitboxWidth:          raw.HitboxWidth,
			HitboxHeight:         raw.HitboxHeight,
			Flags:                raw.Flags,
		}
	}
	return entries, nil
}

func normalizeEntries(
	serialized []enemyModel,
	expectedCount int,
) ([]enemyModel, error) {
	if len(serialized) != expectedCount {
		return nil, fmt.Errorf(
			"got %d entries, expected %d",
			len(serialized), expectedCount)
	}

	entries := make([]enemyModel, expectedCount)
	seen := make([]bool, expectedCount)
	for _, entry := range serialized {
		index, err := strconv.ParseUint(entry.ID, 0, 16)
		if err != nil {
			return nil, fmt.Errorf("invalid id %q: %w", entry.ID, err)
		}
		if index >= uint64(expectedCount) {
			return nil, fmt.Errorf(
				"id %q is outside [0, %#x)", entry.ID, expectedCount)
		}
		if seen[index] {
			return nil, fmt.Errorf("duplicate id %q", entry.ID)
		}
		seen[index] = true
		entries[index] = entry
	}
	for index, present := range seen {
		if !present {
			return nil, fmt.Errorf("missing id 0x%03X", index)
		}
	}
	return entries, nil
}

func entryCount(args []string) (int, error) {
	if len(args) == 0 {
		return defaultEntryCount, nil
	}
	if len(args) != 1 {
		return 0, fmt.Errorf(
			"enemydefs accepts at most one entry-count argument, got %d",
			len(args))
	}
	count, err := strconv.ParseUint(args[0], 0, 16)
	if err != nil || count == 0 {
		return 0, fmt.Errorf("invalid enemydefs entry count %q", args[0])
	}
	return int(count), nil
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

func decodeItem(value uint16, fields map[int]string) string {
	// Zero-valued item slots are normally disabled by a zero drop rate. Emitting
	// ITEMDROP_SMALL_HEART would make those inactive slots appear populated, so
	// preserve zero numerically.
	if value == 0 {
		return "0"
	}
	if name, ok := fields[int(value)]; ok {
		return name
	}
	return fmt.Sprintf("0x%04X", value)
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
	var sb strings.Builder
	sb.WriteByte('"')
	for _, value := range encoded {
		fmt.Fprintf(&sb, "\\x%02X", value)
	}
	sb.WriteByte('"')
	return sb.String(), nil
}
