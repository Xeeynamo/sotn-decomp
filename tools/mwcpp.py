#!/usr/bin/env python3

import argparse
import re
import sys
from typing import TextIO


def include_asm(line: str, out: TextIO, version: str) -> None:
    hireg = r"%hi\((.*)\)"
    loreg = r"%lo\((.*)\)"
    jalr_fix = r"jalr\s*\$([a-z][a-z0-9])"
    match = re.search(r'\s*INCLUDE_ASM\(\s*"(.*)",\s*(\w*)\)', line)
    if match:
        base_path = match.group(1)
        func_name = match.group(2)
        out.write(f"asm void {func_name}() {{\n")
        with open(f"asm/{version}/{base_path}/{func_name}.s", "r") as f:
            for line in f:
                # skip glabel
                if line.startswith("glabel"):
                    continue
                # skip .size
                if line.startswith(".size"):
                    continue
                # do not use '.' on label names
                line = line.replace(".L", "L")
                # use symbol@h instead of %hi(symbol)
                himatch = re.search(hireg, line)
                if himatch:
                    symbol_name = himatch.group(1)
                    line = line.replace(f"%hi({symbol_name})", f"{symbol_name}@ha")
                # use symbol@l instead of %lo(symbol)
                lomatch = re.search(loreg, line)
                if lomatch:
                    symbol_name = lomatch.group(1)
                    line = line.replace(f"%lo({symbol_name})", f"{symbol_name}@l")
                # jalr needs two arguments
                jalr_match = re.search(jalr_fix, line)
                if jalr_match:
                    reg_name = jalr_match.group(1)
                    line = line.replace(reg_name, f"ra, ${reg_name}")
                # write adjusted assembly line
                out.write(line)
        out.write(f"}}\n")
    else:
        out.write(line)


def process_file(file_name_in: str, out: TextIO, version: str) -> None:
    with open(file_name_in, "r") as fin:
        for line in fin:
            if line.startswith("INCLUDE_ASM"):
                include_asm(line, out, version)
            else:
                out.write(line)
    return None


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
