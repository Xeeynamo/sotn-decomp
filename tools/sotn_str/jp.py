def dakuten(chr, prev):
    if chr == "ﾞ":
        if prev == "シ":
            return "ジ"
        if prev == "ク":
            return "グ"
        if prev == "て":
            return "で"
        if prev == "ト":
            return "ド"
        if prev == "サ":
            return "ザ"
        if prev == "タ":
            return "ダ"
        if prev == "か":
            return "が"
        if prev == "テ":
            return "デ"
        if prev == "ハ":
            return "バ"
        if prev == "セ":
            return "ゼ"
        if prev == "ホ":
            return "ボ"
        if prev == "ヒ":
            return "ビ"
        if prev == "こ":
            return "ご"
        if prev == "ふ":
            return "ぶ"
        if prev == "と":
            return "ど"
        if prev == "へ":
            return "べ"
        if prev == "ヘ":
            return "ベ"
        if prev == "ス":
            return "ズ"
        if prev == "カ":
            return "ガ"
        if prev == "ケ":
            return "ゲ"
        if prev == "シ":
            return "ジ"
        if prev == "し":
            return "じ"
        if prev == "き":
            return "ぎ"
        if prev == "は":
            return "ば"
        if prev == "フ":
            return "ブ"
        if prev == "ウ":
            return "ヴ"
        if prev == "さ":
            return "ざ"
        if prev == "ひ":
            return "び"
        if prev == "せ":
            return "ぜ"
        if prev == "コ":
            return "ゴ"
        if prev == "ほ":
            return "ぼ"
        if prev == "キ":
            return "ギ"
        if prev == "そ":
            return "ぞ"
        if prev == "た":
            return "だ"
        if prev == "ソ":
            return "ゾ"
        if prev == "く":
            return "ぐ"
        print(chr, prev)
        assert False
    if chr == "ﾟ":
        if prev == "フ":
            return "プ"
        if prev == "ヒ":
            return "ピ"
        if prev == "ハ":
            return "パ"
        if prev == "ヘ":
            return "ペ"
        if prev == "ホ":
            return "ポ"
        print(chr, prev)
        assert False
    print(chr, prev)
    assert False


table = [
    # fmt: off
    # 0      1      2      3      4      5      6      7      8      9      A      B      C      D      E      F
    " ",     "!",  "\"", "#",   "$",   "%", "&", "'", "(", ")", "男", "+", ",", "-", ".", "/",
    "0",     "1",   "2",   "3",   "4", "5", "6", "7", "8", "9", ":", "人", "手", "=", "玉", "?",
    "石",    "A",   "B",   "C",   "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O",
    "P",     "Q",   "R",   "S",   "T", "U", "V", "W", "X", "Y", "Z", "[", "剣", "]", "盾", "_",
    "書",   "a",   "b",   "c",   "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o",
    "p",     "q",   "r",   "s",   "t", "u", "v", "w", "x", "y", "z", "炎", "氷", "雷", "~", "女",
    "力",    "。",   "「",   "」", "、", "・", "ヲ", "ァ", "ィ", "ゥ", "ェ", "ォ", "ャ", "ュ", "ョ", "ッ",
    "ー",    "ア",   "イ",   "ウ", "エ", "オ", "カ", "キ", "ク", "ケ", "コ", "サ", "シ", "ス", "セ", "ソ",
    "タ",    "チ",   "ツ",   "テ", "ト", "ナ", "ニ", "ヌ", "ネ", "ノ", "ハ", "ヒ", "フ", "ヘ", "ホ", "マ",
    "ミ",    "ム",   "メ",   "モ", "ヤ", "ユ", "ヨ", "ラ", "リ", "ル", "レ", "ロ", "ワ", "ン", "ﾞ", "ﾟ", # dakuten and handakuten are lower in the graphic than seen here and get shifted by the code upwards when printing
    "子",    "悪",   "魔",   "人", "妖", "精", "を","ぁ", "ぃ", "ぅ", "ぇ", "ぉ", "ゃ", "ゅ", "ょ", "っ",
    "金",    "あ",   "い",   "う", "え", "お", "か", "き", "く", "け", "こ", "さ", "し", "す", "せ", "そ",
    "た",    "ち",   "つ",  "て",  "と", "な", "に", "ぬ", "ね", "の", "は", "ひ", "ふ", "へ", "ほ", "ま",
    "み",    "む",   "め",  "も",  "や", "ゆ", "よ", "ら", "り", "る", "れ", "ろ", "わ", "ん", "指", "輪",
    "←",     "↖",   "↑",   "↗",   "→", "↘", "↓", "↙", "○", "×", "□", "△", "名", "刀", "聖", "血",
    "i0",    "i1",  "i2" , "i3", "i4", "i5", "i6", "i7", "i8", "i9", "i10", "i11", "大", "光", "邪", "月", 
    # off by one somewhere for バルザイのえん月刀
    "???"
]
# fmt: on

utf8_to_index = {}
for index, value in enumerate(table):
    utf8_to_index[value] = index


def get_chr(chr):
    return table[chr]


alt_utf8_to_index = dict((value, index) for index, value in enumerate("ＡＴＤＥＦ"))

alt_hd_utf8_to_index = dict(
    (value, index)
    for index, value in enumerate(
        "".join(
            [
                # 0 1 2 3 4 5 6 7 8 9 A B C D E F
                "装備技システム短剣必殺使攻撃力防",
                "御魔導器拳こ一覧棒両手食物爆弾盾",
                "投射薬ん右左武兜鎧マントその他い",
            ]
        )
    )
)


def convert_j(f):
    pos = 0
    str = ""
    prev = None
    prev_prev = None
    while True:
        ch = f[pos]
        prev_prev = prev
        prev = ch
        pos += 1
        if int(ch) == 0xFF:
            ch = f[pos]
            pos += 1

            if ch == 0:
                break

            if ch != 0xFF:
                # if we dakuten, erase previous
                str = str[:-1]
                str += dakuten(get_chr(ch), get_chr(prev_prev))
        if ch != 158 and ch != 159:
            str += get_chr(ch)
    return str


def parse_string_to_int_array(input_str):
    # Remove "_SJ(" and ")" from the input string
    clean_str = input_str.replace("_SJ(", "").replace(")", "")

    # Parse each byte and convert to integer
    int_array = [int(byte, 16) for byte in clean_str.split("\\x")[1:]]

    # null termination
    int_array.append(0)

    return int_array


# ten ten
def has_dakuten(utf8_char):
    # fmt: off
    chars = [
        "が", "ぎ", "ぐ", "げ", "ご",
	    "ざ", "じ",	"ず", "ぜ", "ぞ",
	    "だ", "ぢ", "づ", "で",	"ど",
        "ば", "び", "ぶ", "べ", "ぼ",
        "ガ", "ギ", "グ", "ゲ", "ゴ",
	    "ザ", "ジ", "ズ", "ゼ", "ゾ",
	    "ダ", "ヂ", "ヅ", "デ", "ド",
        "バ", "ビ", "ブ", "ベ", "ボ",
        "ヴ"]
    # fmt: on
    return utf8_char in chars


# maru
def has_handakuten(utf8_char):
    # fmt: off
    chars = [
        "ぱ", "ぴ", "ぷ", "ぺ", "ぽ",
        "パ", "ピ", "プ", "ペ", "ポ"
    ]
    # fmt: on
    return utf8_char in chars


def remove_dakuten_handakuten(utf8_char):
    table = {
        "が": "か",
        "ぎ": "き",
        "ぐ": "く",
        "げ": "け",
        "ご": "こ",
        "ざ": "さ",
        "じ": "し",
        "ず": "す",
        "ぜ": "せ",
        "ぞ": "そ",
        "だ": "た",
        "ぢ": "ち",
        "づ": "つ",
        "で": "て",
        "ど": "と",
        "ば": "は",
        "び": "ひ",
        "ぶ": "ふ",
        "べ": "へ",
        "ぼ": "ほ",
        "ぱ": "は",
        "ぴ": "ひ",
        "ぷ": "ふ",
        "ぺ": "へ",
        "ぽ": "ほ",
        "ガ": "カ",
        "ギ": "キ",
        "グ": "ク",
        "ゲ": "ケ",
        "ゴ": "コ",
        "ザ": "サ",
        "ジ": "シ",
        "ズ": "ス",
        "ゼ": "セ",
        "ゾ": "ソ",
        "ダ": "タ",
        "ヂ": "チ",
        "ヅ": "ツ",
        "デ": "テ",
        "ド": "ト",
        "バ": "ハ",
        "ビ": "ヒ",
        "ブ": "フ",
        "ベ": "ヘ",
        "ボ": "ホ",
        "パ": "ハ",
        "ピ": "ヒ",
        "プ": "フ",
        "ペ": "ヘ",
        "ポ": "ホ",
        "ヴ": "ウ",
    }
    return table[utf8_char]


def dakuten_to_bytes(input_chr):
    no_dakuten = remove_dakuten_handakuten(input_chr)
    no_dakuten_bytes = utf8_to_index[no_dakuten]
    byte = 158
    if has_handakuten(input_chr):
        byte = 159

    return [no_dakuten_bytes, 0xFF, byte]


def utf8_to_byte_literals(input_str):
    bytes = []
    for char in input_str:
        if has_dakuten(char) or has_handakuten(char):
            bytes += dakuten_to_bytes(char)
        elif char == "月":
            bytes += [0xFF, 0xFF]
        else:
            bytes.append(utf8_to_index[char])
    bytes.append(0xFF)
    return bytes


def alt_utf8_to_byte_literals(input_str):
    bytes = []
    for char in input_str:
        bytes.append(alt_utf8_to_index[char])
    bytes.append(0xFF)
    return bytes


def alt_hd_utf8_to_byte_literals(input_str):
    bytes = []
    for char in input_str:
        bytes.append(alt_hd_utf8_to_index[char])
    bytes.append(0xFF)
    return bytes


def utf8_to_byte_literals_escaped(input):
    out = utf8_to_byte_literals(input)
    escaped_string = "".join([f"\\x{val:02X}" for val in out])
    return escaped_string
