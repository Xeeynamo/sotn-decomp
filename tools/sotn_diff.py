#!/usr/bin/env python3

import argparse
import os
from pathlib import Path

try:
    import rabbitizer
except ImportError:
    print(
        "Missing dependency rabbitizer, install it with `python3 -m pip install 'rabbitizer>=1.0.0,<2.0.0'`"
    )
    exit(1)

try:
    import mapfile_parser
except ImportError:
    print(
        "Missing dependency mapfile_parser, install it with `python3 -m pip install 'mapfile-parser>=1.2.1,<2.0.0'`"
    )
    exit(1)


def decodeInstruction(bytesDiff: bytes, mapFile: mapfile_parser.MapFile) -> str:
    word = (
        (bytesDiff[0] << 24)
        | (bytesDiff[1] << 16)
        | (bytesDiff[2] << 8)
        | (bytesDiff[3] << 0)
    )
    instr = rabbitizer.Instruction(word)
    immOverride = None

    if instr.isJumpWithAddress():
        # Instruction is a function call (jal)

        # Get the embedded address of the function call
        symAddress = instr.getInstrIndexAsVram()

        # Search for the address in the mapfile
        symInfo = mapFile.findSymbolByVramOrVrom(symAddress)
        if symInfo is not None:
            # Use the symbol from the mapfile instead of a raw value
            immOverride = symInfo.symbol.name

    return instr.disassemble(immOverride=immOverride, extraLJust=-20)


def firstDiffOvl():
    parser = argparse.ArgumentParser(
        description="Find the first difference(s) between the built ROM and the base ROM."
    )

    parser.add_argument(
        "-c",
        "--count",
        type=int,
        default=5,
        help="find up to this many instruction difference(s)",
    )
    parser.add_argument(
        "-v",
        "--version",
        help="Which version should be processed",
        default=os.getenv("VERSION") or "us",
    )
    parser.add_argument(
        "-b", "--binfile", help="Which .bin file should be processed (filename only)", required=True
    )
    parser.add_argument(
        "-m", "--mapfile", help="Which .map file should be used (filename only)", required=True
    )
    parser.add_argument(
        "-a", "--add-colons", action="store_true", help="Add colon between bytes"
    )

    args = parser.parse_args()

    buildFolder = Path(f"./build/{args.version}")

    BUILTROM = Path(f"./build/{args.version}/{args.binfile}")
    BUILTMAP = Path(f"{buildFolder}/{args.mapfile}")

    EXPECTEDROM = Path(f"./expected/{BUILTROM}")
    EXPECTEDMAP = Path(f"./expected/{BUILTMAP}")

    print(BUILTROM, BUILTMAP, EXPECTEDROM, EXPECTEDMAP)

    mapfile_parser.frontends.first_diff.doFirstDiff(
        BUILTMAP, EXPECTEDMAP, BUILTROM, EXPECTEDROM, args.count, mismatchSize=True
    )


if __name__ == "__main__":
    firstDiffOvl()
