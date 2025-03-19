from jp import *
import unittest
from sotn_str import *


class TestingJp(unittest.TestCase):
    def test_parse_string_to_int_array(self):
        input = "_SJ(\\xBD\\xC3\\xFF\\x9E\\xFF)"
        out = parse_string_to_int_array(input)
        assert out == [0xBD, 0xC3, 0xFF, 0x9E, 0xFF, 0x00]

    def test_convert_dakuten(self):
        input = "_SJ(\\xBD\\xC3\\xFF\\x9E\\xFF)"
        split = parse_string_to_int_array(input)
        converted = convert_j(split)
        assert converted == "すで"

    def test_remove_dakuten_handakuten(self):
        assert remove_dakuten_handakuten("が") == "か"

    def test_dakuten_to_bytes(self):
        bytes = dakuten_to_bytes("で")
        assert bytes == [0xC3, 0xFF, 0x9E]

    def test_utf8_to_byte_literals_escaped_dakuten(self):
        input = "すで"
        out = utf8_to_byte_literals_escaped(input)
        assert out == "\\xBD\\xC3\\xFF\\x9E\\xFF"

    def test_utf8_to_byte_literals_escaped_kanji(self):
        input = "あかつきの剣"
        out = utf8_to_byte_literals_escaped(input)
        assert out == "\\xB1\\xB6\\xC2\\xB7\\xC9\\x3C\\xFF"

    def check_sei():
        assert utf8_to_index["聖"] == 222

    def test_glasses(self):
        input = "聖なるめがね"
        out = utf8_to_byte_literals_escaped(input)
        assert out == "\\xEE\\xC5\\xD9\\xD2\\xB6\\xFF\\x9E\\xC8\\xFF"

    def test_moon(self):
        input = "バルザイのえん月刀"
        out = utf8_to_byte_literals_escaped(input)
        assert (
            out
            == "\\x8A\\xFF\\x9E\\x99\\x7B\\xFF\\x9E\\x72\\xC9\\xB4\\xDD\\xFF\\xFF\\xED\\xFF"
        )

    def test_str_potion(self):
        input = "Str. potion"
        out = utf8_to_byte_literals_escaped(input)
        assert out == "\\x33\\x54\\x52\\x0E\\x00\\x50\\x4F\\x54\\x49\\x4F\\x4E\\xFF"


class TestingSotnStr(unittest.TestCase):
    def test_do_sub_jp(self):
        line = '{_S("すで"), "装備なし（素手）", 0, 0, 0, 3, 255, 0, 0, 36, 42, 0, 5, 128, 0, 0, false, 8, 0, 0, 0, 0, 4, 2, 1, 1, 1, 1, 0},'
        out = do_sub(line)
        expected = '{"\\xBD\\xC3\\xFF\\x9E\\xFF", "装備なし（素手）", 0, 0, 0, 3, 255, 0, 0, 36, 42, 0, 5, 128, 0, 0, false, 8, 0, 0, 0, 0, 4, 2, 1, 1, 1, 1, 0},'
        assert out == expected

    def test_jp_empty(self):
        line = '_S("")'
        out = do_sub(line)
        expected = '"\\xFF"'
        assert out == expected

    def test_jp_symbols_and_quotes(self):
        line = '_S("\\"(\\")")'
        out = do_sub(line)
        expected = '"\\x02\\x08\\x02\\x09\\xFF"'
        assert out == expected, (out, expected)

    def test_s2_us(self):
        line = '_S2("ＡＴＴ")'
        out = do_sub(line)
        assert out == '"\\x00\\x01\\x01\\xFF"'

    def test_s2_empty(self):
        line = '_S2("")'
        out = do_sub(line)
        assert out == '"\\xFF"'

    def test_s2_hd(self):
        line = '_S2_HD("攻撃力")'
        out = do_sub(line)
        assert out == '"\\x0C\\x0D\\x0E\\xFF"'

    def test_s2_empty(self):
        line = '_S2_HD("")'
        out = do_sub(line)
        assert out == '"\\xFF"'


if __name__ == "__main__":
    unittest.main()
