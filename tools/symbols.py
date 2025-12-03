#!/usr/bin/env python3

import argparse
import os
import re
import sys
from pathlib import Path
from yaml import safe_load
from subprocess import CalledProcessError, run
from collections import defaultdict, namedtuple

Symbol = namedtuple("Symbol", ["name", "address", "comment"])


def get_symbol_files(symbols_paths):
    symbol_files = []
    for symbols_path in symbols_paths:
        if symbols_path.is_dir():
            symbol_files.extend(
                file
                for file in symbols_path.iterdir()
                if args.version in file.name
                and (
                    file.name.startswith("symbols.")
                    or file.name.startswith("undefined_syms.")
                )
                and file.suffix == ".txt"
            )
        elif symbols_path.is_file():
            symbol_files.append(symbols_path)
        else:
            print(f"{args.symbols_path} does not exist")
            continue

    if symbol_files:
        return symbol_files
    else:
        raise FileNotFoundError


def sort(symbols_paths):
    if isinstance(symbols_paths, (str, Path)):
        symbols_paths = (symbols_paths,)

    symbol_files = get_symbol_files(Path(path) for path in symbols_paths)

    for symbol_file in symbol_files:
        sorted_symbols = get_symbols(symbol_file)
        new_lines = (
            "\n".join(
                f"{symbol.name} = 0x{symbol.address:08X};{f' // {symbol.comment}' if symbol.comment else ''}"
                for symbol in sorted_symbols
            )
            + "\n"
        )
        if new_lines != Path(symbol_file).read_text():
            symbol_file.write_text(new_lines.lstrip("\n"))


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

    syms = dict()
    ref_line_count = len(asm_ref)
    cross_line_count = len(asm_cross)
    if ref_line_count != cross_line_count:
        return "fail", syms

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
            return "fail", syms  # token mis-match, functions are different
        if is_value_equal(tokens_ref, tokens_cross, "OP") == False:
            return "fail", syms  # if op code is not the same, functions are different
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


def get_nonmatchings_asm(config):
    asm_path = Path(config["options"]["asm_path"])
    data_parts = []
    for segment in config["segments"]:
        if (
            not "type" in segment or segment["type"] == "code"
        ) and "subsegments" in segment:
            for subsegment in segment["subsegments"]:
                if isinstance(subsegment, list) and len(subsegment) > 2:
                    data_parts.append([subsegment[2], subsegment[1]])
                elif isinstance(subsegment, list) and len(subsegment) == 2:
                    data_parts.append([f"{subsegment[0]:X}", subsegment[1]])
                elif (
                    isinstance(subsegment, dict)
                    and "name" in subsegment
                    and "type" in subsegment
                ):
                    data_parts.append([subsegment["name"], subsegment["type"]])
                elif (
                    isinstance(subsegment, dict)
                    and "start" in subsegment
                    and "type" in subsegment
                ):
                    data_parts.append([f"{subsegment['start']:X}", subsegment["type"]])
        elif "name" in segment and "type" in segment:
            data_parts.append([segment["name"], segment["type"]])

    data_files = [
        Path(f"{parts[0]}.{parts[1]}.s").name
        for parts in data_parts
        if not parts[1].startswith(".")
        and (parts[1].endswith("data") or parts[1].endswith("bss"))
    ]
    asm_files = [
        dirpath / f
        for dirpath, _, filenames in asm_path.walk()
        for f in filenames
        if "matchings" not in dirpath.parts
        and ("data" not in dirpath.parts or f in data_files)
    ]
    return asm_files


def clean_conflicts(
    elf_path, symbols_by_file, remove_conflicts=False, print_conflicts=False
):
    # skip finding conflicts for weapons since the .elf file structure is different
    if "weapon" in f"{elf_path}":
        return []

    defined_syms_by_address = {
        symbol.address: symbol.name
        for file in symbols_by_file
        for symbol in symbols_by_file[file]
        if "ignore:true" not in symbol.comment
    }

    # if old asm files still exist it can cause a large number of erroneus conflicts to be detected
    conflicts = [
        symbol
        for symbol in get_symbols(elf_path, excluded_ends=[".NON_MATCHING"])
        if symbol.address in defined_syms_by_address
        and defined_syms_by_address[symbol.address] != symbol.name
    ]

    if len(conflicts) > 5:
        print(
            "Found more than 5 conflicts (no changes made), did you start with a clean build?"
        )
        return

    for symbol in conflicts:
        if print_conflicts:
            conflict = defined_syms_by_address[symbol.address]
            print(
                f"{elf_path.name}: 0x{symbol.address:08X}: {symbol.name} in elf conflicts with {conflict} in symbol file"
            )

        if remove_conflicts:
            for symbol_file in symbols_by_file:
                new_lines = (
                    f"{symbol.name} = 0x{symbol.address:08X};{f' // {symbol.comment}' if symbol.comment else ''}"
                    for symbol in symbols_by_file[symbol_file]
                    if symbol.name not in conflicts
                )
                symbol_file.write_text("\n".join(new_lines) + "\n")


def clean_orphans(
    asm_files,
    symbols_by_file,
    remove_orphans=False,
    print_summary=False,
    print_orphans=False,
):
    symbols_by_name = {}
    for file, symbols in symbols_by_file.items():
        symbols_by_name[file] = {symbol.name: symbol for symbol in symbols}

    # filter and flatten so that it is just a set of symbols without the file association
    orphans = {
        symbol.name
        for file in symbols_by_file
        for symbol in symbols_by_file[file]
        if not (comment := symbols_by_name[file][symbol.name].comment)
        or (
            "used:true" not in comment
            and "ignore:true" not in comment
            and "allow_duplicated:true" not in comment
        )
    }

    # matches on patterns that start with 'glabel ', '.word ', 'jal ', 'j ', '%hi(', or '%lo('
    # and followed by 2 or more word characters, limiting the first character to A-Z, a-z, or _
    symbol_pattern = re.compile(
        r"(?:glabel\s+|\.word\s+|jal\s+|j\s+|%(?:hi|lo)\()(?P<name>[A-Z_a-z]\w+)"
    )
    for asm_file in asm_files:
        asm_text = asm_file.read_text()
        orphans -= {match.group("name") for match in symbol_pattern.finditer(asm_text)}
        # stop processing files if we've found all defined symbols
        if not orphans:
            break

    for symbol_file, symbols in symbols_by_file.items():
        if symbols and (asm_files or orphans):
            new_lines = [
                f"{symbol.name} = 0x{symbol.address:08X};{f' // {symbol.comment}' if symbol.comment else ''}"
                for symbol in symbols
                if symbol.name not in orphans
            ]
            # only write to the file if lines were removed
            if (removed := len(symbols) - len(new_lines)) and remove_orphans:
                symbol_file.write_text("\n".join(new_lines) + "\n")

        if (print_summary or print_orphans) and not symbols:
            print(f"{symbol_file.name + ':':<25} empty symbol file")
        elif print_summary or print_orphans:
            print(
                f"{symbol_file.name + ':':<25} {'removed' if remove_orphans else 'found'}: {removed:<4} remaining: {len(symbols)-removed:<4} (searched {len(asm_files):<3} files)"
            )
        if print_orphans:
            for orphan in orphans:
                print(f"orphan: {orphan}")

    # update the symbols to account for any removed orphans
    symbols_by_file = {
        Path(file): [
            symbol
            for symbol in symbols_by_file[file]
            if symbol.name not in orphans or not remove_orphans
        ]
        for file in symbols_by_file
    }
    return symbols_by_file


def clean(config_files):
    for config_file in config_files:
        # no need to load the config, the necessary fields are in the file name
        splat, version, basename, ext = config_file.split(".")
        config = safe_load(Path(config_file).read_text())
        basename = config["options"]["basename"]
        ld_script_path = Path(config["options"]["ld_script_path"])
        elf_path = Path(
            config["options"].get("elf_path", ld_script_path.with_suffix(".elf"))
        )
        symbol_addrs_path = config["options"]["symbol_addrs_path"]
        if isinstance(symbol_addrs_path, str):
            symbol_files = [
                (Path(symbol_addrs_path),) if basename in symbol_addrs_path else ()
            ]
        else:
            symbol_files = [
                Path(path) for path in symbol_addrs_path if basename in path
            ]
        symbols_by_file = {file: get_symbols(file) for file in symbol_files}

        if not ld_script_path.exists():
            print(
                f"{version} version may be missing asm for {basename}, skipping orphans"
            )
        else:
            # if we didn't get --warn-orphans, then assume we want to remove them
            remove_orphans = not args.warn_orphans
            asm_files = get_nonmatchings_asm(config)
            symbols_by_file = clean_orphans(
                asm_files,
                symbols_by_file,
                remove_orphans,
                args.print_summary,
                args.print_orphans,
            )

        # weapons use a different path for their .elf files
        if "weapon" in config_file:
            continue
        if not elf_path.exists():
            print(f"{elf_path} missing for {basename}, skipping conflicts")
        else:
            clean_conflicts(
                elf_path,
                symbols_by_file,
                args.remove_conflicts,
                args.print_conflicts,
            )


def get_symbols(file_path, excluded_starts=[], excluded_ends=[], excluded_comments=[]):
    file_path = Path(file_path)
    if file_path.suffix in [".map", ".elf"]:
        excluded_starts = {"LM", "__pad", "_binary_assets"} | set(excluded_starts)
        excluded_ends = {"_START", "_END", "_VRAM", "_s", "_c"} | set(excluded_ends)
    match file_path.suffix:
        case ".map":
            text = file_path.read_text()
            # matches format '                0x8018098c                g_EInitCommon'
            matches = re.finditer(
                r"\s+0x(?P<address>[A-Fa-f0-9]{8})\s+(?P<name>[A-Z_a-z]\w+)\n", text
            )
        case ".elf":
            cmd_output = run(["nm", "-U", file_path], capture_output=True)
            if cmd_output.returncode != 0:
                print(cmd_output.stdout, file=sys.stdout)
                print(cmd_output.stderr, file=sys.stderr)
                raise CalledProcessError(
                    cmd_output.returncode, f"nm -U {file_path}", cmd_output.stderr
                )
            # matches format '8018098c T g_EInitCommon', excluding A types
            matches = re.finditer(
                r"(?P<address>[A-Fa-f0-9]{8})\s+[^A]\s+(?P<name>[A-Z_a-z][\w\.]+)",
                cmd_output.stdout.decode(),
            )
        case ".txt" | _ if ".txt" in file_path.suffixes:
            text = file_path.read_text()
            # matches format 'D_801B0934 = 0x801C0D3C; // comment'
            matches = re.finditer(
                r"(?P<name>[A-Z_a-z]\w+)\s+=\s+0x(?P<address>[A-Fa-f0-9]{1,});(?:\s+//(?P<comment>.+))?",
                text,
            )
        case _:
            raise SystemError(
                f"File to extract symbols from must be .elf, .map, or a symbols file, got {file_path.suffix}"
            )

    parsed = set()
    comments = defaultdict(list)
    for match in matches:
        symbol_name = match.groupdict().get("name", "")
        symbol_address = int(match.group("address"), 16)
        symbol_comment = f"{match.groupdict().get('comment') or ''}".lower()
        if (
            "_compiled" not in symbol_name
            and not any(symbol_name.startswith(x) for x in excluded_starts)
            and not any(symbol_name.endswith(x) for x in excluded_ends)
            and not any(x in symbol_comment for x in excluded_comments)
        ):
            # normalize comments
            if symbol_comment:
                new_comments = []
                for item in symbol_comment.split():
                    if ":0x" in item:
                        key, val = item.split(":")
                        item = f"{key}:0x{int(val.strip(), 16):X}"
                    new_comments.append(item)

                comments[symbol_address].extend(
                    x for x in new_comments if x not in comments[symbol_address]
                )

            parsed.add((symbol_name, symbol_address))

    symbols = (Symbol(x[0], x[1], " ".join(comments[x[1]])) for x in parsed)
    return sorted(symbols, key=lambda symbol: (symbol.address, symbol.name))


def parse(file_name, no_default=False, output_file=False):
    excluded_starts = ["D_", "func_", "jpt_", "jtbl_"] if no_default else []
    symbols = get_symbols(Path(file_name), excluded_starts)

    lines = (
        f"{symbol.name} = 0x{symbol.address:08X}; // allow_duplicated:true"
        for symbol in symbols
    )
    if output_file:
        Path(output_file).write_text("\n".join(lines) + "\n")
    else:
        [print(line) for line in lines]


def extract_dynamic_symbols(config_path, output):
    config = safe_load(Path(config_path).read_text())

    symbol_addrs_path = config["options"]["symbol_addrs_path"]
    if isinstance(symbol_addrs_path, str):
        symbol_addrs_path = (symbol_addrs_path,)

    ld_script_path = config["options"]["ld_script_path"]
    elf_path = config["options"].get(
        "elf_path", Path(ld_script_path).with_suffix(".elf")
    )

    defined_symbols = []
    for symbol_file in symbol_addrs_path:
        defined_symbols.extend(
            get_symbols(
                symbol_file,
                excluded_comments=["ignore:true", "allow_duplicated:true", "used:true"],
            )
        )
    defined_names = {symbol.name for symbol in defined_symbols}
    defined_addrs = {symbol.address for symbol in defined_symbols}

    elf_symbols = get_symbols(elf_path)
    dynamic_symbols = {
        symbol
        for symbol in elf_symbols
        if symbol.name not in defined_names
        and symbol.address not in defined_addrs
        and not symbol.name.endswith("NON_MATCHING")
        and Symbol(f"{symbol.name}.NON_MATCHING", symbol.address, "") not in elf_symbols
    }
    lines = (
        f"{symbol.name} = 0x{symbol.address:08X}; // allow_duplicated:true"
        for symbol in sorted(
            dynamic_symbols, key=lambda symbol: (symbol.address, symbol.name)
        )
    )
    if isinstance(output, (str, Path)):
        output = Path(output)
        output.parent.mkdir(parents=True, exist_ok=True)
        output.write_text("\n".join(lines) + "\n")
    else:
        print("\n".join(lines))


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Perform operations on game symbols")
    parser.add_argument(
        "-v",
        "--version",
        required=False,
        type=str,
        default=os.getenv("VERSION") or "us",
        help="Sets game version and overrides VERSION environment variable",
    )
    subparsers = parser.add_subparsers(dest="command")

    sort_parser = subparsers.add_parser(
        "sort",
        description="Sort all the symbols of a given GNU LD script by their offsets",
    )
    sort_parser.add_argument(
        "symbols_path",
        nargs="*",
        default=["config/"],
        help="Any number of directories containing symbol files or specific symbol files to sort",
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

    clean_syms_parser = subparsers.add_parser("clean", description="Clean symbol files")
    clean_syms_parser.add_argument(
        "config_file",
        nargs="+",
        help="The config file for the overlay to clean the symbols file(s) for",
    )
    clean_syms_parser.add_argument(
        "--warn-orphans",
        action="store_true",
        help="Remove all symbols that are not referenced (default)",
    )
    clean_syms_parser.add_argument(
        "--remove-conflicts",
        action="store_true",
        help="Remove all symbols that are built with one name, but defined as a different name",
    )
    clean_syms_parser.add_argument(
        "-s",
        "--print-summary",
        action="store_true",
        help="Print summary of orphans to stdout",
    )
    clean_syms_parser.add_argument(
        "-o",
        "--print-orphans",
        action="store_true",
        help="Show warnings for all symbols that are not referenced",
    )
    clean_syms_parser.add_argument(
        "-c",
        "--print-conflicts",
        action="store_true",
        help="Show warnings for all symbols that are built with one name, but defined as a different name (default)",
    )

    parse_parser = subparsers.add_parser(
        "parse",
        description="Parse the symbols from an elf or map file",
    )
    parse_parser.add_argument(
        "file_name",
        help="The file to parse symbols from",
    )
    parse_parser.add_argument(
        "-o",
        "--output",
        type=str,
        help="Output parsed symbols to specified file, rather than stdout",
        required=False,
    )
    parse_parser.add_argument(
        "--no-default",
        required=False,
        action="store_true",
        help="Do not include symbols that start with D_, func_, jpt_, or jtbl_",
    )

    dynamic_parser = subparsers.add_parser(
        "dynamic",
        description="Print the list of dynamic symbols from an elf file that are not included in static symbol tables.",
    )
    dynamic_parser.add_argument(
        "config_file",
        help="The Splat YAML config of the overlay to generate the dynamic symbol list from",
    )
    dynamic_parser.add_argument(
        "-o",
        "--output",
        default=sys.stdout,
        required=False,
        help="The output for the dynamic symbols",
    )

    args = parser.parse_args()
    match args.command:
        case "sort":
            sort(args.symbols_path)
        case "cross":
            cross(args.ref, args.to_cross)
        case "clean":
            clean(args.config_file)
        case "parse":
            parse(args.file_name, args.no_default, args.output)
        case "dynamic":
            extract_dynamic_symbols(args.config_file, args.output)
