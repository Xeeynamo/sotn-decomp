#!/usr/bin/env python3

import argparse
import re
import sys
from typing import TextIO

r_lui = r"\s*lui\s*\$(.*),\s\%hi\((.*)\)"
r_lui_addiu_combo = r"\s*addiu\s*\$(.*),\s\$(.*),\s\%lo\((.*)\)"
r_hilo = r"\/\*\s*\w*\s*\w*\s*(\w*)\s*\*\/\s*\w*\s*\$\w*,.*(?:%hi|%lo).*"
r_hi = r"%hi\((.*)\)"
r_lo = r"%lo\((.*)\)\(|%lo\((.*)\)"
r_jalr = r"jalr\s*\$([a-z][a-z0-9])"
r_jlabel = r"jlabel \.(.*)"


def process_asm_line(asm_f: TextIO, line: str) -> str | None:
    if line == "":
        return None

    # skip glabel
    if line.startswith("glabel"):
        return ""

    # skip .size
    if line.startswith(".size"):
        return ""

    match_jlabel = re.search(r_jlabel, line)
    if match_jlabel:
        label_name = match_jlabel.group(1)
        line = f"{label_name}:\n"

    # do not use '.' on label names
    line = line.replace(".L", "L")

    # remove trailing hash comment
    if "#" in line:
        line = line.split("#")[0] + "\n"

    # jalr needs two arguments
    jalr_match = re.search(r_jalr, line)
    if jalr_match:
        reg_name = jalr_match.group(1)
        return line.replace(reg_name, f"ra, ${reg_name}")

    r_hilo_match = re.search(r_hilo, line)
    if r_hilo_match:
        raw_data = r_hilo_match.group(1)
        if len(raw_data) == 8:
            return f".word 0x{raw_data[6:8]}{raw_data[4:6]}{raw_data[2:4]}{raw_data[0:2]}\n"

    # return unpatched assembly line
    return line


def include_asm(c_line: str, out: TextIO, version: str) -> None:
    match = re.search(r'\s*INCLUDE_ASM\(\s*"(.*)",\s*(\w*)\)', c_line)
    if match:
        base_path = match.group(1)
        func_name = match.group(2)
        out.write(f"asm void {func_name}() {{\n")
        with open(f"asm/{version}/{base_path}/{func_name}.s", "r") as f:
            try:
                while True:
                    line = f.readline()
                    patched_line = process_asm_line(f, line)
                    if patched_line == None:
                        break
                    out.write(patched_line)
            except Exception as ex:
                print(f"line {line} caused an exception")
                raise ex
        out.write(f"}}\n")
    else:
        out.write(c_line)


def process_file(file_name_in: str, out: TextIO, version: str) -> None:
    with open(file_name_in, "r") as fin:
        while True:
            line = fin.readline()
            if not line:
                return None
            if line.startswith("INCLUDE_ASM"):
                try:
                    include_asm(line, out, version)
                except Exception as ex:
                    print(f"{line} caused an exception")
                    raise
            else:
                out.write(line)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Pre-process Metrowerks C files to overcome certain compiler limitations"
    )
    parser.add_argument(
        "--version", required=False, type=str, default="pspeu", help="Game version"
    )
    parser.add_argument(
        "input",
        type=str,
        help="Input C file to pre-process",
    )
    parser.add_argument(
        "-o",
        "--output",
        type=str,
        help="Output file, stdout if not specified",
    )
    args = parser.parse_args()
    if args.version == None:
        args.version = "pspeu"
    if args.output:
        with open(args.output, "w") as fout:
            process_file(args.input, fout, args.version)
    else:
        process_file(args.input, sys.stdout, args.version)
