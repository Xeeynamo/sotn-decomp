#!/usr/bin/env python3

import argparse
import os
import sys

parser = argparse.ArgumentParser(
    description="Converts a binary file into C-compatible data"
)
group_size = parser.add_mutually_exclusive_group()
group_size.add_argument(
    "-1",
    "--byte",
    help="write as a 8-bit array (default)",
    action="store_true",
    required=False,
)
group_size.add_argument(
    "-2", "--word", help="write as a 16-bit array", action="store_true", required=False
)
group_size.add_argument(
    "-4", "--dword", help="write as a 32-bit array", action="store_true", required=False
)
group_sign = parser.add_mutually_exclusive_group()
group_sign.add_argument(
    "-u",
    "--unsigned",
    help="write values as unsigned (default)",
    action="store_true",
    required=False,
)
group_sign.add_argument(
    "-s", "--signed", help="write values as signed", action="store_true", required=False
)
parser.add_argument("filein", help="binary file name to convert", nargs=1, default=None)
parser.add_argument("name", help="variable name", nargs=1, default=None)
args = parser.parse_args()


def get_array_size(args):
    if args.word == True:
        return 2
    if args.dword == True:
        return 4
    return 1


def is_signed(args):
    if args.signed == True:
        return True
    return False


def as_byte(bytes):
    return f"0x{chunk[0]:x}, "


def as_word(bytes):
    return f"0x{chunk[1]:x}{chunk[0]:x}, "


def as_dword(bytes):
    return f"0x{chunk[3]:x}{chunk[2]:x}{chunk[1]:x}{chunk[0]:x}, "


if __name__ == "__main__":
    array_size = get_array_size(args)
    is_signed = is_signed(args)
    file_name = args.filein[0]
    name = args.name[0]
    data_size = os.stat(file_name).st_size
    if data_size % array_size != 0:
        sys.stderr.write(f"{file_name} size not aligend by {array_size}\n")

    line = ""
    if is_signed:
        line += "signed "
    else:
        line += "unsigned "

    if array_size == 1:
        line += "char "
        str_func = as_byte
    if array_size == 2:
        line += "short "
        str_func = as_word
    if array_size == 4:
        line += "int "
        str_func = as_dword
    sys.stdout.write(f"{line}{name}[] = {{\n")

    with open(file_name, "rb") as file:
        while file.tell() < data_size:
            chunk = file.read(array_size)
            sys.stdout.write(str_func(chunk))
    sys.stdout.write("\n};")
