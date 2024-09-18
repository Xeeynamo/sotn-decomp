#!/usr/bin/env python3

import argparse
import json


def patch(config_file_name):
    with open(config_file_name, "r") as f:
        patches = json.load(f)
    for patch in patches:
        name = patch["name"]
        with open(name, "r+b") as f:
            for str_offset in patch:
                if not str_offset.startswith("0x"):
                    continue
                offset = int(str_offset[2:], base=16)
                value = patch[str_offset]
                f.seek(offset)
                f.write(bytes([value]))


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="given a configuration, patches an existing binary"
    )
    parser.add_argument(
        "config",
        help="File path of the patch configuration",
    )

    args = parser.parse_args()
    patch(args.config)
