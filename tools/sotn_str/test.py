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

    def test_utf8_to_byte_literals_wrapped_dakuten(self):
        input = "_SJ(すで)"
        out = utf8_to_byte_literals_wrapped(input)
        assert out == "_SJ(\\xBD\\xC3\\xFF\\x9E\\xFF)"

    def test_utf8_to_byte_literals_wrapped_kanji(self):
        input = "_SJ(あかつきの剣)"
        out = utf8_to_byte_literals_wrapped(input)
        assert out == "_SJ(\\xB1\\xB6\\xC2\\xB7\\xC9\\x3C\\xFF)"

    def check_sei():
        assert(utf8_to_index['聖'] == 222)

    def test_glasses(self):
        input = "_SJ(聖なるめがね)"
        out = utf8_to_byte_literals_wrapped(input)
        assert out == "_SJ(\\xEE\\xC5\\xD9\\xD2\\xB6\\xFF\\x9E\\xC8\\xFF)"

    def test_moon(self):
        input = "_SJ(バルザイのえん月刀)"
        out = utf8_to_byte_literals_wrapped(input)
        assert out == "_SJ(\\x8A\\xFF\\x9E\\x99\\x7B\\xFF\\x9E\\x72\\xC9\\xB4\\xDD\\xFF\\xFF\\xED\\xFF)"

class TestingSotnStr(unittest.TestCase):
    def test_do_sub_jp(self):
        line = '{_SJ("すで"), "装備なし（素手）", 0, 0, 0, 3, 255, 0, 0, 36, 42, 0, 5, 128, 0, 0, false, 8, 0, 0, 0, 0, 4, 2, 1, 1, 1, 1, 0},'
        out = do_sub(line)
        expected = '{"\\xBD\\xC3\\xFF\\x9E\\xFF", "装備なし（素手）", 0, 0, 0, 3, 255, 0, 0, 36, 42, 0, 5, 128, 0, 0, false, 8, 0, 0, 0, 0, 4, 2, 1, 1, 1, 1, 0},'
        assert out == expected

    def test_jp_empty(self):
        line = "_SJ(\"\")"
        out = do_sub(line)
        expected = '\"\\xFF\"'
        assert out == expected


if __name__ == "__main__":
    unittest.main()
