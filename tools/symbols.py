#!/usr/bin/env python3

import argparse
import mapfile_parser
import os
from pathlib import Path
import re
import sys
import yaml
from collections import OrderedDict

parser = argparse.ArgumentParser(description="Perform operations on game symbols")
parser.add_argument("--version", required=False, type=str, help="Game version")
subparsers = parser.add_subparsers(dest="command")

sort_parser = subparsers.add_parser(
    "sort", description="Sort all the symbols of a given GNU LD script by their offset"
)

cross_parser = subparsers.add_parser(
    "cross",
    description="Cross-reference the symbols between two assembly files and print the result to stdout for GNU LD. Useful to cross-reference symbols between different overlays or game revisions. The assemblies must be identical.",
)
cross_parser.add_argument(
    "ref",
    help="Assembly source file to use as a base reference",
)
cross_parser.add_argument(
    "to_cross",
    help="Assembly source file to be cross-referenced to",
)

orphan_parser = subparsers.add_parser(
    "remove-orphans",
    description="Remove all symbols that are not referenced from a specific group of assembly code",
)
orphan_parser.add_argument(
    "config_yaml",
    help="The Splat YAML config of the overlay to remove the orphan symbols from",
)

map_parser = subparsers.add_parser(
    "map",
    description="Print the list of symbols from a map file",
)
map_parser.add_argument(
    "map_file_name",
    help="The map file to extract the symbols from",
)
map_parser.add_argument(
    "--no-default",
    required=False,
    action="store_true",
    help="Do not include Splat default symbols that starts with D_ or func_",
)


def is_splat_symbol_name(name):
    return (
        name.startswith("D_")
        or name.startswith("func_")
        or name.startswith("jpt_")
        or name.startswith("jtbl_")
    )


def add_newline_if_missing(list):
    if len(list) > 0:
        if not list[-1].endswith("\n"):
            list[-1] += "\n"
    return list


def sort_symbols(syms):
    offsets = []
    for line in syms:
        if line.startswith("//"):
            # ignore comments
            continue

        parts = line.strip().split()
        if len(parts) >= 3:
            offset = int(parts[2].rstrip(";"), 16)
            offsets.append((line, offset))
    offsets.sort(key=lambda x: x[1])
    return list(OrderedDict.fromkeys([line[0] for line in offsets]))


# rewrite the same file with an ordered symbol list
def sort_symbols_from_file(symbol_file_name):
    with open(symbol_file_name, "r") as symbol_file:
        sorted_lines = sort_symbols(symbol_file)
    add_newline_if_missing(sorted_lines)
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


# regex helper to match a hexadecimal string without the '0x'
def re_hex(name):
    return f"(?P<{name}>[0-9A-F]+)"


# regex helper to parse splat's disassembler /* LOC VRAM VAL */ comments
def re_splat_line():
    return f"/\\* {re_hex('LOC')} {re_hex('VRAM')} {re_hex('VAL')} \\*/"


# regex helper to match C-style identifiers
def re_ident(name):
    return f"(?P<{name}>[a-zA-Z_][a-zA-Z0-9_]*)"


# regex helper to match assembly registers
def re_reg(name):
    return rf"(?P<{name}>\$[0-9a-z]+)"


# regex helper to match the two %lo and %hi functions
re_func = r"(?P<FUNC>\%(hi|lo))"


# all the regex patterns supported by the MIPS assembly parser
patterns = [
    (
        rf"{re_splat_line()}\s+{re_ident('OP')}\s+{re_reg('DST')},\s+{re_func}\({re_ident('SYM')}\)\({re_reg('IMM')}\)",
        ["LOC", "VRAM", "VAL", "OP", "DST", "FUNC", "SYM", "IMM"],
    ),
    (
        rf"{re_splat_line()}\s+{re_ident('OP')}\s+{re_reg('DST')},\s+{re_func}\({re_ident('SYM')}\)",
        ["LOC", "VRAM", "VAL", "OP", "DST", "FUNC", "SYM"],
    ),
    (
        rf"{re_splat_line()}\s+{re_ident('OP')}\s+{re_reg('DST')},\s+{re_reg('LEFT')},\s+{re_reg('RIGHT')}",
        ["LOC", "VRAM", "VAL", "OP", "DST", "LEFT", "RIGHT"],
    ),
    (
        rf"{re_splat_line()}\s+{re_ident('OP')}\s+{re_reg('DST')},\s+{re_reg('LEFT')},\s+{re_func}\({re_ident('SYM')}\)\({re_reg('IMM')}\)",
        ["LOC", "VRAM", "VAL", "OP", "DST", "LEFT", "FUNC", "SYM", "IMM"],
    ),
    (
        rf"{re_splat_line()}\s+{re_ident('OP')}\s+{re_reg('DST')},\s+{re_reg('LEFT')},\s+{re_func}\({re_ident('SYM')}\)",
        ["LOC", "VRAM", "VAL", "OP", "DST", "LEFT", "FUNC", "SYM"],
    ),
    (
        rf"{re_splat_line()}\s+{re_ident('OP')}\s+{re_reg('DST')},\s+{re_reg('LEFT')}",
        ["LOC", "VRAM", "VAL", "OP", "DST", "LEFT"],
    ),
    (
        rf"{re_splat_line()}\s+{re_ident('OP')}\s+\.{re_ident('LABEL')}",
        ["LOC", "VRAM", "VAL", "OP", "LABEL"],
    ),
    (
        rf"{re_splat_line()}\s+{re_ident('OP')}\s+{re_reg('DST')},\s+\.{re_ident('LABEL')}",
        ["LOC", "VRAM", "VAL", "OP", "DST", "LABEL"],
    ),
    (
        rf"{re_splat_line()}\s+{re_ident('OP')}$",
        ["LOC", "VRAM", "VAL", "OP"],
    ),
    (r"glabel (?P<FUNC_NAME>\w+)", ["FUNC_NAME"]),
]


# tokenize a single line of MIPS assembly code
def asm_tokenize_line(line):
    for pattern, token_names in patterns:
        match = re.match(pattern, line)
        if match:
            tokens = match.groupdict()
            return {key: tokens[key] for key in token_names}
    return None


# get a dictionary of all the non-matching and cross-referenced symbols
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

    # print symbol list in GNU LD style
    for sym in syms:
        print(f"{sym} = 0x{syms[sym]:08X};")


def get_all_file_paths_recursively(path):
    file_list = []
    for root, directories, files in os.walk(path):
        for file in files:
            file_list.append(os.path.join(root, file))
    return file_list


def tokenize_symbols(file_path):
    with open(file_path, "r") as f:
        content = f.read()
    content_without_comments = re.sub(r"/\*.*?\*/", "", content, flags=re.DOTALL)
    content_without_labels = re.sub(r"\bL8\w*", "", content_without_comments)
    content_without_strings = re.sub(r'"[^"]*"', "", content_without_labels)
    return re.findall(r"\b[a-zA-Z_]\w*\b", content_without_strings)


def remove_orphans(symbol_file_name, symbols_set):
    with open(symbol_file_name, "r") as symbol_file_ref:
        symbols_defined = symbol_file_ref.readlines()

    symbols_unorphaned = []
    for sym_def in symbols_defined:
        if sym_def.startswith("//"):
            # ignore comments
            continue

        if len(sym_def) > 4 and sym_def.find("ignore:true") == -1:
            sym_tokenized = sym_def.split("=")
            if len(sym_tokenized) >= 2:
                sym = sym_tokenized[0].strip()
                if sym not in symbols_set:
                    continue
        symbols_unorphaned.append(sym_def)
    add_newline_if_missing(symbols_unorphaned)

    with open(symbol_file_name, "w") as symbol_file_ref:
        symbol_file_ref.writelines(symbols_unorphaned)


def remove_orphans_from_config(config_yaml):
    with open(config_yaml, "r") as config_yaml_ref:
        config = yaml.safe_load(config_yaml_ref)
    symbol_addrs_path = config["options"]["symbol_addrs_path"]
    if isinstance(symbol_addrs_path, str):
        symbol_file_name = symbol_addrs_path
    else:
        symbol_file_name = symbol_addrs_path[-1]  # take last

    asm_path = config["options"]["asm_path"]

    file_list = get_all_file_paths_recursively(asm_path)
    asm_file_list = [file for file in file_list if file.endswith(".s")]

    if len(file_list) == 0:
        print(
            f"WARN: No symbols found for '{symbol_file_name}' in '{asm_path}'. Terminating before making destructive changes.",
            file=sys.stderr,
        )
        exit(0)

    symbols_found = set()
    for asm_file in asm_file_list:
        symbols_found.update(tokenize_symbols(asm_file))

    # The following hack forces to also process symbols from the YAML config itself.
    # This is because tiledef in ST/WRP uses the symbol list to extract the tile definition.
    symbols_found.update(tokenize_symbols(config_yaml))
    remove_orphans(symbol_file_name, symbols_found)


def print_map_symbols(map_file_name, no_default):
    map_file = mapfile_parser.MapFile()
    map_file.readMapFile(Path(map_file_name))

    filter = (
        (lambda name: not is_splat_symbol_name(name))
        if no_default
        else (lambda _: True)
    )

    syms = dict()
    for segment in map_file:
        for file in segment:
            for sym in file:
                if sym.vram not in syms and filter(sym.name):
                    syms[sym.vram] = sym.name
    for vram in syms:
        print(f"{syms[vram]} = 0x{vram:08X}; // allow_duplicated:True")


if __name__ == "__main__":
    args = parser.parse_args()
    if args.version == None:
        args.version = os.getenv("VERSION")
        if args.version == None:
            args.version = "us"
    if args.command == "sort":
        sort("config/")
    elif args.command == "cross":
        cross(args.ref, args.to_cross)
    elif args.command == "remove-orphans":
        remove_orphans_from_config(args.config_yaml)
    elif args.command == "map":
        print_map_symbols(args.map_file_name, args.no_default)
