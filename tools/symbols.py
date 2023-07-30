#!/usr/bin/env python3

import argparse
import os
from pydoc import describe
import re
import sys

parser = argparse.ArgumentParser(
    description="Manage game symbols with various operations"
)
parser.add_argument("--version", required=False, type=str, help="Game version")
subparsers = parser.add_subparsers(dest="command")

sort_parser = subparsers.add_parser(
    "sort", description="Sort all the symbols by their offset"
)
cross_parser = subparsers.add_parser(
    "cross",
    description="Cross-reference the symbols between two assembly files and print the result to stdout",
)
cross_parser.add_argument(
    "ref",
    help="Assembly source file to use as a base reference",
)
cross_parser.add_argument(
    "to_cross",
    help="Assembly source file to be cross-referenced to",
)

args = parser.parse_args()
if args.version == None:
    args.version = os.getenv("VERSION")
    if args.version == None:
        args.version = "us"


def sort_symbols(syms):
    offsets = []
    for line in syms:
        parts = line.strip().split()
        if len(parts) >= 3:
            offset = int(parts[2].rstrip(";"), 16)
            offsets.append((line, offset))
    offsets.sort(key=lambda x: x[1])
    return [line[0] for line in offsets]


def sort_symbols_from_file(symbol_file_name):
    with open(symbol_file_name, "r") as symbol_file:
        sorted_lines = sort_symbols(symbol_file)
    with open(symbol_file_name, "w") as symbol_file:
        symbol_file.writelines(sorted_lines)


def sort(base_path):
    files = os.listdir(base_path)

    # Filter the list to include only files that start with 'symbols.us.' and end with '.txt'
    filtered_files = [
        f
        for f in files
        if f.startswith(f"symbols.{args.version}.") and f.endswith(".txt")
    ]

    for symbol_file_name in [os.path.join(base_path, f) for f in filtered_files]:
        sort_symbols_from_file(symbol_file_name)


def re_hex(name):
    return f"(?P<{name}>[0-9A-F]+)"


def re_splat_line():
    return f"/\\* {re_hex('LOC')} {re_hex('VRAM')} {re_hex('VAL')} \\*/"


def re_ident(name):
    return f"(?P<{name}>[a-zA-Z_][a-zA-Z0-9_]*)"


def re_reg(name):
    return f"(?P<{name}>\$[a-z][0-9a-z])"


re_func = r"(?P<FUNC>\%(hi|lo))"


patterns = [
    (
        f"{re_splat_line()}\\s+{re_ident('OP')}\\s+{re_reg('DST')},\\s+{re_func}\({re_ident('SYM')}\)\({re_reg('IMM')}\)",
        ["LOC", "VRAM", "VAL", "OP", "DST", "FUNC", "SYM", "IMM"],
    ),
    (
        f"{re_splat_line()}\\s+{re_ident('OP')}\\s+{re_reg('DST')},\\s+{re_func}\({re_ident('SYM')}\)",
        ["LOC", "VRAM", "VAL", "OP", "DST", "FUNC", "SYM"],
    ),
    (
        f"{re_splat_line()}\\s+{re_ident('OP')}\\s+{re_reg('DST')},\\s+{re_reg('LEFT')},\\s+{re_reg('RIGHT')}",
        ["LOC", "VRAM", "VAL", "OP", "DST", "LEFT", "RIGHT"],
    ),
    (
        f"{re_splat_line()}\\s+{re_ident('OP')}\\s+{re_reg('DST')},\\s+{re_reg('LEFT')},\\s+{re_func}\({re_ident('SYM')}\)\({re_reg('IMM')}\)",
        ["LOC", "VRAM", "VAL", "OP", "DST", "LEFT", "FUNC", "SYM", "IMM"],
    ),
    (
        f"{re_splat_line()}\\s+{re_ident('OP')}\\s+{re_reg('DST')},\\s+{re_reg('LEFT')},\\s+{re_func}\({re_ident('SYM')}\)",
        ["LOC", "VRAM", "VAL", "OP", "DST", "LEFT", "FUNC", "SYM"],
    ),
    (
        f"{re_splat_line()}\\s+{re_ident('OP')}\\s+{re_reg('DST')},\\s+{re_reg('LEFT')}",
        ["LOC", "VRAM", "VAL", "OP", "DST", "LEFT"],
    ),
    (
        f"{re_splat_line()}\\s+{re_ident('OP')}\\s+\.{re_ident('LABEL')}",
        ["LOC", "VRAM", "VAL", "OP", "LABEL"],
    ),
    (
        f"{re_splat_line()}\\s+{re_ident('OP')}\\s+{re_reg('DST')},\\s+\.{re_ident('LABEL')}",
        ["LOC", "VRAM", "VAL", "OP", "DST", "LABEL"],
    ),
    (
        f"{re_splat_line()}\\s+{re_ident('OP')}$",
        ["LOC", "VRAM", "VAL", "OP"],
    ),
    (r"glabel (?P<FUNC_NAME>\w+)", ["FUNC_NAME"]),
]


def asm_tokenize_line(line):
    for pattern, token_names in patterns:
        match = re.match(pattern, line)
        if match:
            tokens = match.groupdict()
            return {key: tokens[key] for key in token_names}
    return None


def get_non_matching_symbols(asm_ref, asm_cross):
    def is_value_equal(a, b, key):
        if key not in a and key not in b:
            return True
        if key not in a or key not in b:
            return False
        return a[key] == b[key]

    def get_imm_addr(raw_val):
        return int(raw_val[2:4] + raw_val[0:2], 16)

    def get_hi_addr(op, raw_val):
        if op == "lui":
            return get_imm_addr(raw_val) << 16
        else:
            print(
                f"CROSS-REFERENCING ERROR: %hi did not expect op '{op}'.",
                file=sys.stderr,
            )
            print(f"affected line: {line_cross}'.", file=sys.stderr)
            assert op == "lui"

    def get_lo_addr(op, raw_val):
        imm = get_imm_addr(raw_val)
        if imm < 32767:
            return imm
        return imm - 0x10000

    ref_line_count = len(asm_ref)
    cross_line_count = len(asm_cross)
    if ref_line_count != cross_line_count:
        return "fail", []

    syms = dict()
    prev_instr_hi = False
    cross_off = 0
    for i in range(0, ref_line_count):
        line_ref = asm_ref[i]
        line_cross = asm_cross[i]
        if line_ref == line_cross:
            continue  # if lines are identical, skip and continue
        tokens_ref = asm_tokenize_line(line_ref)
        tokens_cross = asm_tokenize_line(line_cross)
        if tokens_ref == tokens_cross:
            continue  # if tokens are identical, skip and continue
        if tokens_ref == None or tokens_cross == None:
            return "fail", []  # token mis-match, functions are different
        if is_value_equal(tokens_ref, tokens_cross, "OP") == False:
            return "fail", []  # if op code is not the same, functions are different
        if is_value_equal(tokens_ref, tokens_cross, "SYM") == True:
            continue  # if a symbol is found and it is the same then continue
        if "SYM" not in tokens_ref:
            continue  # instruction do not use any symbol, skip and continue

        # If arriving here it should be the only case where cross-referencing
        # between two symbols should happen.
        sym = tokens_ref["SYM"]
        if sym.startswith("jpt_"):
            continue  # actively ignore jump tables

        op = tokens_cross["OP"]
        func = tokens_cross["FUNC"]
        raw_val = tokens_cross["VAL"]
        if prev_instr_hi and func == "%lo":
            prev_instr_hi = False
            cross_off += get_lo_addr(op, raw_val)
            syms[sym] = cross_off
        elif func == "%hi":
            prev_instr_hi = True
            cross_off = get_hi_addr(op, raw_val)
        else:
            # Do nothing. There are instances where between a %hi and a %lo
            # some instructions can be found.
            continue
    return "ok", syms


def cross(asm_reference_file_name, asm_to_cross_file_name):
    with open(asm_reference_file_name, "r") as asm_ref_file:
        with open(asm_to_cross_file_name, "r") as asm_cross_file:
            err, syms = get_non_matching_symbols(
                asm_ref_file.readlines(), asm_cross_file.readlines()
            )
    if err != "ok":
        print(
            "assemblies too different to be cross-referenced automatically",
            file=sys.stderr,
        )
        return

    for sym in syms:
        print(f"{sym} = 0x{syms[sym]:08X};")


if __name__ == "__main__":
    if args.command == "sort":
        sort("config/")
    elif args.command == "cross":
        cross(args.ref, args.to_cross)
