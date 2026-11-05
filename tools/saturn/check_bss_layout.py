#!/usr/bin/env python3

"""Check that every object in a Saturn bss.c lands at its retail address."""

import argparse
import re
import subprocess
import sys
from pathlib import Path

ADDRESS_NAME = re.compile(r"^_(?:DAT|D|func)_([0-9A-Fa-f]{8})(?:_pad)?$")
ASSIGNMENT = re.compile(r"^\s*(_\w+)\s*=\s*(0x[0-9A-Fa-f]+)\s*;")


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("map", type=Path)
    parser.add_argument("object", type=Path)
    parser.add_argument("syms", type=Path, nargs="+")
    parser.add_argument("--nm", default="sh-elf-nm")
    args = parser.parse_args()

    start = None
    lines = args.map.read_text().splitlines()
    for line in lines:
        parts = line.split()
        if len(parts) == 4 and parts[0] == ".bss" and parts[3] == str(args.object):
            start = int(parts[1], 16)
    if start is None:
        print(f"{args.map}: no .bss for {args.object}", file=sys.stderr)
        return 1

    expected = {}
    for path in args.syms:
        for line in path.read_text().splitlines():
            match = ASSIGNMENT.match(line)
            if match:
                expected.setdefault(match.group(1), int(match.group(2), 16))

    result = subprocess.run([args.nm, str(args.object)], check=True,
                            capture_output=True, text=True)
    errors = []
    for line in result.stdout.splitlines():
        parts = line.split()
        if len(parts) != 3 or parts[1] not in "Bb":
            continue
        name, actual = parts[2], start + int(parts[0], 16)
        match = ADDRESS_NAME.match(name)
        want = expected.get(name, int(match.group(1), 16) if match else None)
        if want is None:
            errors.append(f"{name}: no retail address")
        elif want != actual:
            errors.append(f"{name}: at 0x{actual:08X}, retail 0x{want:08X}")
    for error in errors:
        print(f"{args.object}: {error}", file=sys.stderr)
    return 1 if errors else 0


if __name__ == "__main__":
    raise SystemExit(main())
