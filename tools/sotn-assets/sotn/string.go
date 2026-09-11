package sotn

import (
	"bytes"
	"fmt"
	"strings"

	"github.com/xeeynamo/sotn-decomp/tools/sotn-assets/psx"
	"golang.org/x/text/encoding/japanese"
	"golang.org/x/text/transform"
)

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

var pspFontTable = []rune(strings.Join([]string{
	` !'#$%&'()男+,-./`,
	`0123456789:人手=玉?`,
	`石ABCDEFGHIJKLMNO`,
	`PQRSTUVWXYZ[剣]盾_`,
	`書abcdefghijklmno`,
	`pqrstuvwxyz炎氷雷~女`,
	`力。「」、・ヲァィゥェォャュョッ`,
	`ーアイウエオカキクケコサシスセソ`,
	`タチツテトナÄヌネノハヒフヘホマ`,
	`ミムÓモÖユヨラリßàáâäﾞè`,
	`éê魔ìíîをñぃóôöùúょü`,
	`金œいうえºかきくけこさしすせそ`,
	`たちつてとなにぬねのはひふへほま`,
	`みむめもやゆよらりるれろわん指輪`,
	`←↖↑↗→↘↓↙○×□△名刀聖血`,
	`✈★☀☁☃♂♀©®§¶∑大光邪月`,
}, ""))

// DecodeString decodes the game's 8x8-font encoding at addr. The PSX and PSP
// use different 256-character tables but share the same control sequences.
func DecodeString(
	data []byte,
	addr, ramBase psx.Addr,
	platform Platform,
) (string, error) {
	table, err := fontTable(platform)
	if err != nil {
		return "", err
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
			decoded = append(decoded, table[value])
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

// EncodeString encodes text for the game's 8x8 font. The returned bytes
// include the 0xFF game-string terminator, but not the C string's trailing NUL.
func EncodeString(value string, platform Platform) ([]byte, error) {
	table, err := fontTable(platform)
	if err != nil {
		return nil, err
	}
	indices := make(map[rune]byte, len(table))
	for i, r := range table {
		// Prefer the last occurrence, matching sotn_str's reverse lookup.
		indices[r] = byte(i)
	}

	encoded := make([]byte, 0, len(value)+1)
	for _, r := range value {
		if r == '月' {
			encoded = append(encoded, 0xFF, 0xFF)
			continue
		}
		if base, ok := removeVoiceMark(r, dakuten); ok {
			index, found := indices[base]
			if !found {
				return nil, fmt.Errorf(
					"character %q requires unavailable base %q on %s",
					r, base, platform)
			}
			encoded = append(encoded, index, 0xFF, 0x9E)
			continue
		}
		if base, ok := removeVoiceMark(r, handakuten); ok {
			index, found := indices[base]
			if !found {
				return nil, fmt.Errorf(
					"character %q requires unavailable base %q on %s",
					r, base, platform)
			}
			encoded = append(encoded, index, 0xFF, 0x9F)
			continue
		}
		index, ok := indices[r]
		if !ok {
			return nil, fmt.Errorf(
				"character %q is not available on %s", r, platform)
		}
		encoded = append(encoded, index)
	}
	return append(encoded, 0xFF), nil
}

// DecodeMenuDescription decodes the Shift-JIS-compatible C string at addr.
// PSP European descriptions replace selected accented characters with
// half-width katakana bytes; those substitutions are reversed for editing.
func DecodeMenuDescription(
	data []byte,
	addr, ramBase psx.Addr,
	platform Platform,
) (string, error) {
	if platform != PlatformPSX && platform != PlatformPSP {
		return "", fmt.Errorf(
			"unsupported menu-description platform %q", platform)
	}
	if addr < ramBase {
		return "", fmt.Errorf("pointer %s precedes RAM base %s", addr, ramBase)
	}
	offset := addr.Real(ramBase)
	if offset >= len(data) {
		return "", fmt.Errorf(
			"pointer %s resolves outside %#x-byte input", addr, len(data))
	}

	end := offset
	for end < len(data) && data[end] != 0 && data[end] != 0xFF {
		end++
	}
	if end == len(data) {
		return "", fmt.Errorf("unterminated menu description at %s", addr)
	}
	raw := data[offset:end]
	decoded, _, err := transform.Bytes(japanese.ShiftJIS.NewDecoder(), raw)
	if err != nil {
		return "", fmt.Errorf(
			"decode Shift-JIS menu description at %s: %w", addr, err)
	}
	value := string(decoded)
	if platform == PlatformPSP {
		value = restoreEuropeanDescription(value)
	}

	roundTrip, err := EncodeMenuDescription(value, platform)
	if err != nil {
		return "", fmt.Errorf(
			"validate menu description at %s: %w", addr, err)
	}
	if !bytes.Equal(roundTrip, raw) {
		return "", fmt.Errorf(
			"menu description at %s does not round-trip through Shift-JIS",
			addr)
	}
	return value, nil
}

// EncodeMenuDescription encodes editable menu text to the bytes used by a C
// string literal. The returned bytes do not include a trailing NUL.
func EncodeMenuDescription(value string, platform Platform) ([]byte, error) {
	if platform != PlatformPSX && platform != PlatformPSP {
		return nil, fmt.Errorf(
			"unsupported menu-description platform %q", platform)
	}
	if platform == PlatformPSP {
		value = substituteEuropeanDescription(value)
	}
	encoded, _, err := transform.Bytes(
		japanese.ShiftJIS.NewEncoder(), []byte(value))
	if err != nil {
		return nil, fmt.Errorf("encode Shift-JIS menu description: %w", err)
	}
	return encoded, nil
}

var europeanDescriptionSubstitutions = map[rune]rune{
	'ù': '\uFF66', 'û': '\uFF67', 'ü': '\uFF68', 'Œ': '\uFF69', 'œ': '\uFF6A',
	'¡': '\uFF72', '¿': '\uFF73', 'À': '\uFF74', 'Ä': '\uFF77', 'Ç': '\uFF78',
	'È': '\uFF79', 'Ö': '\uFF85', 'ß': '\uFF8A', 'à': '\uFF8B', 'á': '\uFF8C',
	'â': '\uFF8D', 'ä': '\uFF8E', 'ç': '\uFF8F', 'è': '\uFF90', 'é': '\uFF91',
	'ê': '\uFF92', 'ì': '\uFF94', 'í': '\uFF95', 'î': '\uFF96', 'ñ': '\uFF98',
	'ò': '\uFF99', 'ó': '\uFF9A', 'ô': '\uFF9B', 'ö': '\uFF9C', 'ú': '\uFF9D',
}

func substituteEuropeanDescription(value string) string {
	return strings.Map(func(r rune) rune {
		if replacement, ok := europeanDescriptionSubstitutions[r]; ok {
			return replacement
		}
		return r
	}, value)
}

func restoreEuropeanDescription(value string) string {
	reversed := make(map[rune]rune, len(europeanDescriptionSubstitutions))
	for original, replacement := range europeanDescriptionSubstitutions {
		reversed[replacement] = original
	}
	return strings.Map(func(r rune) rune {
		if original, ok := reversed[r]; ok {
			return original
		}
		return r
	}, value)
}

func fontTable(platform Platform) ([]rune, error) {
	var table []rune
	switch platform {
	case PlatformPSX:
		table = psxFontTable
	case PlatformPSP:
		table = pspFontTable
	default:
		return nil, fmt.Errorf("unsupported string platform %q", platform)
	}
	if len(table) != 0x100 {
		return nil, fmt.Errorf(
			"%s font table has %#x entries, expected 0x100",
			platform, len(table))
	}
	return table, nil
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

func removeVoiceMark(composed rune, marks map[rune]rune) (rune, bool) {
	for base, candidate := range marks {
		if candidate == composed {
			return base, true
		}
	}
	return 0, false
}
