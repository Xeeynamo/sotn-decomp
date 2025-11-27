#!/usr/bin/env python3

import os
import argparse
import multiprocessing
from pathlib import Path
from sotn_utils import init_logger, extract

"""
Handles many tasks for adding an overlay:
- Extracts the data necessary to generate an initial config
- Parses known data tables (psx header, entity table, psp export table)
- Compares newly extracted functions to existing asm files to identify functions
- Adds and renames identified symbols
- Cross references asm with existing asm and matches symbols from identical instruction sequences
- Creates the ovl.h file, header.c, and e_init.c files
- Imports the data for header.c and e_init.c for us version
- Cross-references header.c and e_init.c with existing file for non-us versions
- Splits source files into segments based on function boundaries
- Extracts and assigns .rodata segments to the correct files
- Parses and logs suggestions for segment splits from splat output
- Validates builds by comparing SHA1 hashes and updates check files

Example usage: tools/extract_overlay.py lib -v us,pspeu

Additional notes:
- If a segment has only one function, it is named as that function in snake case.  If the function name starts with Entity, it replaces it with 'e'.
    For example: A segment with the only function being EntityShuttingWindow would be named as e_shutting_window
"""

if __name__ == "__main__":
    # set global multiprocessing options
    multiprocessing.log_to_stderr()
    multiprocessing.set_start_method("spawn")

    parser = argparse.ArgumentParser(
        description="Create initial configuration for new overlays"
    )
    parser.add_argument(
        "overlay",
        help="Name of the overlay to create a configuration for",
    )
    parser.add_argument(
        "-v",
        "--version",
        required=False,
        action="append",
        default=[],
        help="The version of the game to target (-v/--version can be passed multiple times or multiple comma separated versions: i.e. '-v us,pspeu' or '-v us -v pspeu'), use 'all' to extract us, pspeu, and hd",
    )
    parser.add_argument(
        "-l",
        "--log",
        required=False,
        default=f"{Path(__file__).parent / 'sotn_utils' / 'logs' / 'sotn_log.json'}",
        help="Use an alternate path for the log file"
    )
    parser.add_argument(
        "--clean",
        required=False,
        action="store_true",
        help="DESTRUCTIVE: Remove any existing overlay artifacts before re-extracting the overlay from the source binary",
    )

    args = parser.parse_args()
    init_logger(filename=args.log)

    if not args.version:
        args.version.append(os.getenv("VERSION"))
    else:
        # split, flatten, and dedup version args
        split_versions = [val.split(",") if "," in val else [val] for val in args.version]
        args.version = {version.strip() for versions in split_versions for version in versions}

    if args.version and None not in args.version:
        unsupported_versions = [ver for ver in args.version if ver not in ["us", "pspeu", "hd", "all"]]
        if unsupported_versions:
            parser.error(f"argument -v/--version: invalid choice(s): {unsupported_versions} (choose from 'us', 'pspeu', 'hd', 'all')")
    else:
        parser.error(f"the following arguments are required: -v/--version (can be via VERSION env or cli)")

    if "all" in args.version:
        args.version = ["us", "pspeu", "hd"]

    # always build us first
    if "us" in args.version:
        extract(args, "us")
    if "pspeu" in args.version:
        extract(args, "pspeu")
    if "hd" in args.version:
        extract(args, "hd")
