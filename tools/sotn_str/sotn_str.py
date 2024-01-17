#!/usr/bin/python3

import argparse
import re
import sys
from jp import utf8_to_byte_literals


def parse(filename, str_offset):
    r = ""
    offset = int(str_offset, 16)
    with open(filename, "rb") as f_in:
        f_in.seek(offset)
        while True:
            ch = f_in.read(1)[0]
            if ch == 0xFF:
                break
            r += chr(ch + 0x20)
    print(f'_S("{r}")')


def process_string(match: re.Match[str]):
    s = match.group(1)
    r = ""
    for ch in s.encode("shift_jis"):
        # TODO at the moment this only works well with ASCII, not with Shift-JIS
        r += f"\\x{ch - 0x20:02X}"
    return f'"{r}\\xFF"'


def process_string_jp(match: re.Match[str]):
    s = match.group(1)
    out = utf8_to_byte_literals(s)
    escaped = "".join([f"\\x{val:02X}" for val in out])
    return f'"{escaped}"'


def do_sub(line):
    pattern = r'_S\("([^"]*)"\)'
    # english_str_processed = re.sub(pattern, process_string, line)
    # pattern_jp = r'_SJ\("([^"]+)"\)'
    jp_str_processed = re.sub(pattern, process_string_jp, line)
    jp_str_processed = jp_str_processed.replace("_S(\"\")", "\"\\xFF\"")
    return jp_str_processed


def process(filename):
    if not filename or filename == "-":
        fn = sys.stdin
    else:
        fn = open(filename, "r")

    with fn as f:
        for line in f:
            sys.stdout.write(do_sub(line))


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="string processor to interpret sequence of characters from SOTN"
    )
    subparsers = parser.add_subparsers(dest="command")

    parse_parser = subparsers.add_parser(
        "parse",
        description="Parse a binary and output the correspondent readable C string that can be parsed later",
    )
    parse_parser.add_argument(
        "filename",
        help="File path of the binary to parse",
    )
    parse_parser.add_argument(
        "offset",
        help="Offset in hexadecimal where to start reading the string",
    )

    build_parser = subparsers.add_parser(
        "process",
        description="Process a C file that contains a previously parsed SOTN string",
    )
    build_parser.add_argument(
        "-f",
        "--filename",
        required=False,
        help="File path of the C file to parse. If not specified read from stdin instead",
    )

    args = parser.parse_args()
    if args.command == "parse":
        parse(args.filename, args.offset)
    elif args.command == "process":
        process(args.filename)
