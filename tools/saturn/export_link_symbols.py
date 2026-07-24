#!/usr/bin/env python3

"""Export relocatable ELF definitions for dependent Saturn links."""

import argparse
import re
import subprocess
from pathlib import Path


NM_LINE = re.compile(
    r"^(?P<address>[0-9A-Fa-f]+)\s+(?P<type>\S)\s+(?P<name>\S+)$"
)
RELOCATABLE_GLOBAL_TYPES = set("BDGRSTVW")


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("elf", type=Path)
    parser.add_argument("output", type=Path)
    parser.add_argument("--nm", default="sh-elf-nm")
    args = parser.parse_args()

    result = subprocess.run(
        [args.nm, "-n", "--defined-only", str(args.elf)],
        check=True,
        capture_output=True,
        text=True,
    )

    symbols = []
    for line in result.stdout.splitlines():
        match = NM_LINE.fullmatch(line.strip())
        if match is None:
            continue
        if match.group("type") not in RELOCATABLE_GLOBAL_TYPES:
            continue
        name = match.group("name")
        if not name.startswith("_"):
            continue
        symbols.append((int(match.group("address"), 16), name))

    lines = [
        "/* Generated from the current parent ELF; do not commit. */",
    ]
    lines.extend(
        f"{name} = 0x{address:08X};"
        for address, name in sorted(set(symbols))
    )
    lines.append("")

    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text("\n".join(lines), encoding="utf-8")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
