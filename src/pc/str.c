#include "pc.h"
#include <stdlib.h>
#include <string.h>

// Converts UTF-8 strings into a byte sequence that menu.c can render using the
// original game font.
// All these information could be pre-calculated, but the table is solved at
// runtime to add the flexibilty of adding new fonts at any time.

// An UTF-8 will be converted into a 32-bit value that can be easily compared to
typedef unsigned int Key;

// in theory this can be expanded to support other alphabets
typedef struct {
    Key key;
    unsigned char value;
    bool hasDakuten;
    bool hasHandakuten;
} SotnMenuPair;

// Table from tools/sotn_str/jp.py
// Characters are ordered following the 8x8 game font
static const char* ch_table[] = {
    " ",  "!",  "\"", "#",  "$",  "%",  "&",  "'",  "(",  ")",  "男", "+",
    ",",  "-",  ".",  "/",  "0",  "1",  "2",  "3",  "4",  "5",  "6",  "7",
    "8",  "9",  ":",  "人", "手", "=",  "玉", "?",  "石", "A",  "B",  "C",
    "D",  "E",  "F",  "G",  "H",  "I",  "J",  "K",  "L",  "M",  "N",  "O",
    "P",  "Q",  "R",  "S",  "T",  "U",  "V",  "W",  "X",  "Y",  "Z",  "[",
    "剣", "]",  "盾", "_",  "書", "a",  "b",  "c",  "d",  "e",  "f",  "g",
    "h",  "i",  "j",  "k",  "l",  "m",  "n",  "o",  "p",  "q",  "r",  "s",
    "t",  "u",  "v",  "w",  "x",  "y",  "z",  "炎", "氷", "雷", "~",  "女",
    "力", "。", "「", "」", "、", "・", "ヲ", "ァ", "ィ", "ゥ", "ェ", "ォ",
    "ャ", "ュ", "ョ", "ッ", "ー", "ア", "イ", "ウ", "エ", "オ", "カ", "キ",
    "ク", "ケ", "コ", "サ", "シ", "ス", "セ", "ソ", "タ", "チ", "ツ", "テ",
    "ト", "ナ", "ニ", "ヌ", "ネ", "ノ", "ハ", "ヒ", "フ", "ヘ", "ホ", "マ",
    "ミ", "ム", "メ", "モ", "ヤ", "ユ", "ヨ", "ラ", "リ", "ル", "レ", "ロ",
    "ワ", "ン", "ﾞ",  "ﾟ",  "子", "悪", "魔", "人", "妖", "精", "を", "ぁ",
    "ぃ", "ぅ", "ぇ", "ぉ", "ゃ", "ゅ", "ょ", "っ", "金", "あ", "い", "う",
    "え", "お", "か", "き", "く", "け", "こ", "さ", "し", "す", "せ", "そ",
    "た", "ち", "つ", "て", "と", "な", "に", "ぬ", "ね", "の", "は", "ひ",
    "ふ", "へ", "ほ", "ま", "み", "む", "め", "も", "や", "ゆ", "よ", "ら",
    "り", "る", "れ", "ろ", "わ", "ん", "指", "輪", "←",  "↖",  "↑",  "↗",
    "→",  "↘",  "↓",  "↙",  "○",  "×",  "□",  "△",  "名", "刀", "聖", "血",
    "¬",  "¬",  "¬",  "¬",  "¬",  "¬",  "¬",  "¬",  "¬",  "¬",  "¬",  "¬",
    "大", "光", "邪", "月",
};

// dictionary size without considering the special characters
#define DICT_BASE_LEN LEN(ch_table)

// a safe amount of special characters to not overflow from the table
#define DICT_EXTRA_BUFFER 59

#define DICT_MAX_SIZE ((DICT_BASE_LEN) + (DICT_EXTRA_BUFFER))

static Key invalid_key = (Key)~0U;
static int dict_len = 0;
static SotnMenuPair sotn_menu_dict[DICT_MAX_SIZE] = {0};

static int SotnMenuPairComparer(const void* a, const void* b) {
    return ((SotnMenuPair*)a)->key - ((SotnMenuPair*)b)->key;
}

// Get a key from a given string and advance the string
// An UTF-8 rune has a variable amount of characters up to 4
#define POP(str) *(*str)++
static Key ReadKeyFromUtf8(const unsigned char** str) {
    Key key = POP(str);
    if (key & 0x80) {
        if ((key & 0xF0) == 0xC0) {
            key |= POP(str) << 8;
        } else if ((key & 0xF0) == 0xE0) {
            key |= (POP(str) << 8) | (POP(str) << 16);
        } else if ((key & 0xF0) == 0xF0) {
            key |= (POP(str) << 8) | (POP(str) << 16) | (POP(str) << 24);
        } else {
            key = invalid_key;
        }
    }

    return key;
}

// Given a character in the string gets its pair, if found
static struct SotnMenuPair* ReadCharacterInfo(const unsigned char** str) {
    Key key = ReadKeyFromUtf8(str);
    SotnMenuPair* pair = (SotnMenuPair*)bsearch(
        &key, sotn_menu_dict, dict_len, sizeof(SotnMenuPair),
        SotnMenuPairComparer);
    if (!pair) {
        WARNF("key %08X for '%s' not found", key, str);
    }

    return pair;
}

static void AddSpecialCharacter(const char* special, const char* base,
                                bool hasDakuten, bool hasHandakuten) {
    // we do not want to evaluate the extra characters inserted so far
    int realSize = dict_len;
    dict_len = DICT_BASE_LEN;
    SotnMenuPair* basePair = ReadCharacterInfo(&base);
    dict_len = realSize;

    SotnMenuPair* pair = &sotn_menu_dict[dict_len++];
    pair->key = ReadKeyFromUtf8(&special);
    pair->value = basePair->value;
    pair->hasDakuten = hasDakuten;
    pair->hasHandakuten = hasHandakuten;
}

static bool is_initalized = false;
void InitSotnMenuTable() {
    if (is_initalized) {
        return;
    }
    is_initalized = true;

    int i;
    for (i = 0; i < DICT_BASE_LEN; i++) {
        const char* str = ch_table[i];
        sotn_menu_dict[i].key = ReadKeyFromUtf8(&str);
        sotn_menu_dict[i].value = i;
    }

    // order the first time to allow special characters to be inserted
    dict_len = DICT_BASE_LEN;
    qsort(sotn_menu_dict, dict_len, sizeof(SotnMenuPair), SotnMenuPairComparer);

    // insert special characters
    AddSpecialCharacter("が", "か", true, false);
    AddSpecialCharacter("ぎ", "き", true, false);
    AddSpecialCharacter("ぐ", "く", true, false);
    AddSpecialCharacter("げ", "け", true, false);
    AddSpecialCharacter("ご", "こ", true, false);
    AddSpecialCharacter("ざ", "さ", true, false);
    AddSpecialCharacter("じ", "し", true, false);
    AddSpecialCharacter("ず", "す", true, false);
    AddSpecialCharacter("ぜ", "せ", true, false);
    AddSpecialCharacter("ぞ", "そ", true, false);
    AddSpecialCharacter("だ", "た", true, false);
    AddSpecialCharacter("ぢ", "ち", true, false);
    AddSpecialCharacter("づ", "つ", true, false);
    AddSpecialCharacter("で", "て", true, false);
    AddSpecialCharacter("ど", "と", true, false);
    AddSpecialCharacter("ば", "は", true, false);
    AddSpecialCharacter("び", "ひ", true, false);
    AddSpecialCharacter("ぶ", "ふ", true, false);
    AddSpecialCharacter("べ", "へ", true, false);
    AddSpecialCharacter("ぼ", "ほ", true, false);
    AddSpecialCharacter("ぱ", "は", false, true);
    AddSpecialCharacter("ぴ", "ひ", false, true);
    AddSpecialCharacter("ぷ", "ふ", false, true);
    AddSpecialCharacter("ぺ", "へ", false, true);
    AddSpecialCharacter("ぽ", "ほ", false, true);
    AddSpecialCharacter("ガ", "カ", true, false);
    AddSpecialCharacter("ギ", "キ", true, false);
    AddSpecialCharacter("グ", "ク", true, false);
    AddSpecialCharacter("ゲ", "ケ", true, false);
    AddSpecialCharacter("ゴ", "コ", true, false);
    AddSpecialCharacter("ザ", "サ", true, false);
    AddSpecialCharacter("ジ", "シ", true, false);
    AddSpecialCharacter("ズ", "ス", true, false);
    AddSpecialCharacter("ゼ", "セ", true, false);
    AddSpecialCharacter("ゾ", "ソ", true, false);
    AddSpecialCharacter("ダ", "タ", true, false);
    AddSpecialCharacter("ヂ", "チ", true, false);
    AddSpecialCharacter("ヅ", "ツ", true, false);
    AddSpecialCharacter("デ", "テ", true, false);
    AddSpecialCharacter("ド", "ト", true, false);
    AddSpecialCharacter("バ", "ハ", true, false);
    AddSpecialCharacter("ビ", "ヒ", true, false);
    AddSpecialCharacter("ブ", "フ", true, false);
    AddSpecialCharacter("ベ", "ヘ", true, false);
    AddSpecialCharacter("ボ", "ホ", true, false);
    AddSpecialCharacter("パ", "ハ", false, true);
    AddSpecialCharacter("ピ", "ヒ", false, true);
    AddSpecialCharacter("プ", "フ", false, true);
    AddSpecialCharacter("ペ", "ヘ", false, true);
    AddSpecialCharacter("ポ", "ホ", false, true);
    AddSpecialCharacter("ヴ", "ウ", true, false);

    // finalize table by ordering it again
    qsort(sotn_menu_dict, dict_len, sizeof(SotnMenuPair), SotnMenuPairComparer);
}

// placeholder in case the conversion buffer is full
static const char dummy_string[] = "DUMMY\xFF";

// contains all the converted strings
static char str_buffer[0x3000];
static size_t str_buffer_index = 0;

const char* AnsiToSotnMenuString(const char* str) {
    size_t end = strlen(str) + 2 + str_buffer_index;
    if (end >= LEN(str_buffer)) {
        ERRORF("buffer full for '%s' (%d/%d)", str, end, LEN(str_buffer));
        return dummy_string;
    }
    DEBUGF("%s", str);

    char* start = str_buffer + str_buffer_index;
    char* dst = start;
    const unsigned char* src = str;
    struct SotnMenuPair* pair;
    while (*src != '\0') {
        SotnMenuPair* pair = ReadCharacterInfo(&src);
        if (pair) {
            *dst++ = pair->value;
            if (pair->value == 0xFF) {
                *dst++ = 0xFF;
            }
            if (pair->hasDakuten) {
                *dst++ = 0xFF;
                *dst++ = 0x9E;
            }
            if (pair->hasHandakuten) {
                *dst++ = 0xFF;
                *dst++ = 0x9F;
            }
        }
    }

    *dst++ = '\xFF';
    *dst++ = '\0';
    str_buffer_index = end;

    return start;
}
