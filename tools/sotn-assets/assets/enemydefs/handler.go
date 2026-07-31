package enemydefs

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

const entrySize = 0x28

type enemyRawEntry struct {
	NameAddr             uint32
	HitPoints            int16
	Attack               uint16
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
	Name                 string   `yaml:"name"`
	HitPoints            int16    `yaml:"hit_points"`
	Attack               uint16   `yaml:"attack"`
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
	Flags                uint32   `yaml:"flags"`
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

	entries, err := parse(
		e.Data, e.Start, e.End, e.RamBase, elementFields, itemFields)
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
	var entries []enemyModel
	if err := yaml.Unmarshal(data, &entries); err != nil {
		return fmt.Errorf("failed to parse %s: %w", inFileName, err)
	}

	var sb strings.Builder
	sb.WriteString("// clang-format off\n")
	for i, entry := range entries {
		fmt.Fprintf(
			&sb,
			"/* 0x%03X */ {_S(%s), %d, %d, %s, %d, %d, %s, %s, %s, %s, %d, %d, %s, %s, %d, %d, %d, %d, 0x%08X},\n",
			i,
			quoteCString(entry.Name),
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
	rawEntries := make([]enemyRawEntry, count)
	if err := binary.Read(
		bytes.NewReader(data[start:end]), binary.LittleEndian, &rawEntries,
	); err != nil {
		return nil, fmt.Errorf("read enemy definitions: %w", err)
	}

	entries := make([]enemyModel, count)
	for i, raw := range rawEntries {
		name, err := decodePSXString(data, psx.Addr(raw.NameAddr), ramBase)
		if err != nil {
			return nil, fmt.Errorf("enemy %#x name: %w", i, err)
		}
		entries[i] = enemyModel{
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
	// Enemy definitions use zero as "no drop", while ItemDrops assigns zero to
	// ITEMDROP_SMALL_HEART. Preserve the table's semantics instead of emitting
	// a misleading enum name.
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

var psxFontTable = []rune(strings.Join([]string{
	` !'#$%&'()男+,-./`,
	`0123456789:人手=玉?`,
	`石ABCDEFGHIJKLMNO`,
	`PQRSTUVWXYZ[剣]盾_`,
	`書abcdefghijklmno`,
	`pqrstuvwxyz炎氷雷~女`,
	`力。「」、・ヲァィゥェォャュョッ`,
	`ーアイウエオカキクケコサシスセソ`,
	`タチツテトナニヌネノハヒフヘホマ`,
	`ミムメモヤユヨラリルレロワンﾞﾟ`,
	`子悪魔人妖精をぁぃぅぇぉゃゅょっ`,
	`金あいうえおかきくけこさしすせそ`,
	`たちつてとなにぬねのはひふへほま`,
	`みむめもやゆよらりるれろわん指輪`,
	`←↖↑↗→↘↓↙○×□△名刀聖血`,
	`✈★☀☁☃♂♀©®§¶∑大光邪月`,
}, ""))

func decodePSXString(data []byte, addr, ramBase psx.Addr) (string, error) {
	if len(psxFontTable) != 0x100 {
		return "", fmt.Errorf(
			"PSX font table has %#x entries, expected 0x100",
			len(psxFontTable))
	}
	if addr < ramBase {
		return "", fmt.Errorf("pointer %s precedes RAM base %s", addr, ramBase)
	}
	offset := addr.Real(ramBase)
	if offset >= len(data) {
		return "", fmt.Errorf(
			"pointer %s resolves outside %#x-byte input", addr, len(data))
	}

	decoded := make([]rune, 0, 16)
	for offset < len(data) {
		value := data[offset]
		offset++
		if value != 0xFF {
			decoded = append(decoded, psxFontTable[value])
			continue
		}
		if offset >= len(data) {
			return "", fmt.Errorf("unterminated string at %s", addr)
		}

		escaped := data[offset]
		offset++
		switch escaped {
		case 0:
			return string(decoded), nil
		case 0xFF:
			decoded = append(decoded, '月')
		case 0x9E, 0x9F:
			if len(decoded) == 0 {
				return "", fmt.Errorf(
					"voice mark %#x has no preceding character at %s",
					escaped, addr)
			}
			base := decoded[len(decoded)-1]
			composed, ok := composeVoiceMark(base, escaped)
			if !ok {
				return "", fmt.Errorf(
					"cannot apply voice mark %#x to %q at %s",
					escaped, base, addr)
			}
			decoded[len(decoded)-1] = composed
		default:
			return "", fmt.Errorf(
				"unknown string escape 0xFF 0x%02X at %s", escaped, addr)
		}
	}
	return "", fmt.Errorf("unterminated string at %s", addr)
}

var dakuten = map[rune]rune{
	'か': 'が', 'き': 'ぎ', 'く': 'ぐ', 'け': 'げ', 'こ': 'ご',
	'さ': 'ざ', 'し': 'じ', 'す': 'ず', 'せ': 'ぜ', 'そ': 'ぞ',
	'た': 'だ', 'ち': 'ぢ', 'つ': 'づ', 'て': 'で', 'と': 'ど',
	'は': 'ば', 'ひ': 'び', 'ふ': 'ぶ', 'へ': 'べ', 'ほ': 'ぼ',
	'カ': 'ガ', 'キ': 'ギ', 'ク': 'グ', 'ケ': 'ゲ', 'コ': 'ゴ',
	'サ': 'ザ', 'シ': 'ジ', 'ス': 'ズ', 'セ': 'ゼ', 'ソ': 'ゾ',
	'タ': 'ダ', 'チ': 'ヂ', 'ツ': 'ヅ', 'テ': 'デ', 'ト': 'ド',
	'ハ': 'バ', 'ヒ': 'ビ', 'フ': 'ブ', 'ヘ': 'ベ', 'ホ': 'ボ',
	'ウ': 'ヴ',
}

var handakuten = map[rune]rune{
	'は': 'ぱ', 'ひ': 'ぴ', 'ふ': 'ぷ', 'へ': 'ぺ', 'ほ': 'ぽ',
	'ハ': 'パ', 'ヒ': 'ピ', 'フ': 'プ', 'ヘ': 'ペ', 'ホ': 'ポ',
}

func composeVoiceMark(base rune, mark byte) (rune, bool) {
	if mark == 0x9E {
		value, ok := dakuten[base]
		return value, ok
	}
	value, ok := handakuten[base]
	return value, ok
}
