#!/usr/bin/env python3

import argparse
import yaml
import sys
import os
import re
from string import Template
from pathlib import Path

# I intend things like this to be stored in a conf file when this functionality is more established in the project
# Since it has a high likelihood of changing and isn't very complex, keeping it here is easier for now
CONFIG_BASE_DIR: str = "config"
CONFIG_PATTERNS: dict[Template] = {
    "splat": Template("splat.$version.(?:st|bo)?$ovl.yaml"),
    "saturn": Template("$ovl.(?:prg|bin).yaml"),
    "sotn": Template(
        "sotn.$version.(?:st|bo)?$ovl.yaml"
    ),  # For when an overlay is fully decompiled
}
SEG_TYPES: dict[tuple] = {
    "asm": ("asm", "header"),
    "data": ("data", "rodata", "bss", "sbss"),
    "src": ("c"),
    "asset": (
        "cmp",
        "ci4",
        "palette",
        "raw",
        "assets",
        "bin",
    ),
}


# This cannot handle returning only shared src files, but since there aren't any currently it isn't really worth putting time into it.
# Shared source files seem to be an artifact in make that is no longer needed. Shared src files are now handled by includes in ovl src files.
def get_config(args: argparse.Namespace) -> dict:
    """Uses the supplied parameters to retrieve and return a dict of config values with version and ovl added"""
    config_dir = Path(CONFIG_BASE_DIR)
    config_pattern = re.compile(
        CONFIG_PATTERNS[args.config_type].substitute(version=args.version, ovl=args.ovl)
    )

    # We only care about the first match we find since there shouldn't be multiple matches
    config_path = next(
        (
            file
            for file in config_dir.iterdir()
            if config_pattern.match(file.name)
        ),
        None,
    )

    if config_path:
        with open(config_path) as config_file:
            config = yaml.safe_load(config_file)

        # So that only one object needs to be passed around
        extra_options = {
            "version": args.version,
            "ovl": args.ovl,
            "ignore_hidden": args.ignore_hidden,
            "include_shared": args.include_shared,
        }
        config["options"].update(extra_options)

        return config
    else:  # Raise an exception if no config_path was found
        raise FileNotFoundError(
            f"Could not find a {args.config_type} config for {args.version} {args.ovl} in {config_dir}/"
        )


def get_file_segments(segments: list) -> list[list]:
    """Returns a list of file segments from a list of segments"""
    # Extracts segment information
    segs: list = [seg for seg in segments if isinstance(seg, list)]
    subsegs: list = [
        sub
        for seg in segments
        if isinstance(seg, dict) and "subsegments" in seg
        for sub in seg["subsegments"]
    ]
    # Converts dicts that contain segment information into lists
    segs.extend(
        [seg.get("start", 0x0), seg["type"].replace("code", "c"), seg["name"]]
        for seg in segments + subsegs
        if isinstance(seg, dict) and "name" in seg and "type" in seg
    )
    # Only returns segment elements that are lists
    return [seg for seg in segs + subsegs if isinstance(seg, list)]


def get_asm_files(options: dict, segments: list[list]) -> set[str]:
    """Constructs a list of asm files from a given segment list"""
    asm_path = Path(options["asm_path"])
    data_path = asm_path.joinpath("data")

    asm_files = {
        asm_path.joinpath(f"{seg[2]}" if len(seg) >= 3 else seg[1]).with_suffix(".s")
        for seg in segments
        if len(seg) >= 2 and seg[1] in SEG_TYPES["asm"]
    }

    data_seg_types = SEG_TYPES["data"]
    # A seg type is added with a leading . for each existing data seg type if ignore_hidden is not set
    if not options["ignore_hidden"]:
        data_seg_types += tuple(f".{type}" for type in SEG_TYPES["data"])

    data_files: set = {
        data_path.joinpath(f"{seg[2]}" if len(seg) >= 3 else f"{seg[0]:X}").with_suffix(
            f".{seg[1].lstrip('.')}.s" if len(seg) >= 2 else ".bss.s"
        )
        for seg in segments
        if (len(seg) >= 2 and seg[1] in (data_seg_types)) or len(seg) == 1
    }

    return {file for file in data_files | asm_files if file.exists()}


def get_src_files(options: dict, segments: list[list]) -> set[str]:
    """Constructs a list of source files from splat segments"""
    src_path = Path(options["src_path"])

    # We assume that if there is a data file, then there should be a c file for it
    # This is safe since we're using sets and we validate existence on the final set
    extra_files: set = {
        src_path.joinpath(f"{seg[2]}").with_suffix(".c")
        for seg in segments
        if len(seg) >= 3 and seg[1].startswith(".")
    }

    c_files: set = {
        src_path.joinpath(f"{seg[2]}" if len(seg) >= 3 else f"{seg[0]:X}").with_suffix(
            ".c"
        )
        for seg in segments
        if len(seg) >= 2 and seg[1] in SEG_TYPES["src"]
    }

    if options["include_shared"]:
        if options["ovl"] in src_path.parts:
            c_files.update(src_path.parent.glob(".c"))
        else:
            c_files.update(src_path.glob(".c"))

    return {file for file in c_files | extra_files if file.exists()}


# This function still needs a bit of refinement, but it is serviceable for now
def get_asset_files(
    options: dict, segments: list[list], asset_filters: tuple[tuple]
) -> set[str]:
    """Constructs a list of asset files using a directory listing or the segments"""
    asset_path = Path(options["asset_path"])

    # Stages and bosses, excluding sel, use these as default glob patterns instead of *
    if (("st" in asset_path.parts or "boss" in asset_path.parts)
        and options["ovl"] != "sel"
    ):
        asset_filters = tuple(("D_801*.bin", "*.gfxbin", "*.palbin", "cutscene_*.bin"))
        if options["version"] == "pspeu":
            asset_filters += tuple(("mwo_header.bin",))

    # The file listing is really the only one used currently because some asset segment files are built by splat extensions
    # and the resulting files aren't directly specified in the config
    if asset_path.exists():
        asset_files = {
            path
            for asset_filter in asset_filters
            for path in asset_path.glob(asset_filter)
        }
    else:  # This method is included as something of a proof of concept/work in progress
        # Splat configs have different segment type names than what these files are saved as, so we translate them with this dict
        # dict.get() can have a default value specified, so we use extension.get(seg_type,seg_type) to get the translation
        # If there is no translation in the dict, then it just uses seg_type
        extension = {
            "cmp": ".dec",
            "raw": ".bin",
            "ci4": ".png",
            "palette": ".png",
            "assets": ".json",
        }
        asset_files = {
            asset_path.joinpath(f"{seg[2]}").with_suffix(
                extension.get(seg[1], f".{seg[1]}")
            )
            for seg in segments
            if len(seg) >= 3 and seg[1] in SEG_TYPES["asset"]
        }
        # Add a .bin file for each .dec file
        asset_files.update(
            {file.with_suffix(".bin") for file in asset_files if file.suffix == ".dec"}
        )
    return asset_files


# Dedicated function for parsing args so that this file can be imported in a module and still have the ability to parse out the proper args
def parse_args(args: list):
    parser = argparse.ArgumentParser(
        description="For gathering information in more complex ways than Make is meant to do"
    )
    parser.add_argument(
        "--version",
        required=False,
        type=str,
        default=os.getenv("VERSION") or "us",
        help="Sets game version and overrides VERSION environment variable",
    )
    subparsers = parser.add_subparsers(dest="action", help="The action to perform")
    parser_list = subparsers.add_parser("list", help="Retrieve a list of files")
    parser_list.add_argument("ovl", type=str, help="Overlay to target")
    parser_list.add_argument(
        "list_type",
        type=str,
        choices=("src_files", "o_files", "merged"),
        help="What to list",
    )
    parser_list.add_argument(
        "-c",
        "--config-type",
        type=str,
        choices=list(CONFIG_PATTERNS.keys()),
        required=True,
        help="Type of config to reference",
    )
    parser_list.add_argument(
        "-s",
        "--include-shared",
        action="store_true",
        required=False,
        help="Include shared src files with ovl src files",
    )
    parser_list.add_argument(
        "-H",
        "--ignore-hidden",
        action="store_true",
        required=False,
        help='Ignore file types that begin with "dot" in splat configs',
    )
    parser_list.add_argument(
        "-f",
        "--asset-filter",
        action="append",
        type=str,
        default="*",
        required=False,
        help="A glob pattern to apply to asset_path files, specify multiple by repeating the option",
    )

    return parser.parse_args(args)


# This logic is expected to be contained elsewhere if this file is imported as a module
def main(args: list) -> None:
    args = parse_args(args)
    config = get_config(args)

    file_segments = get_file_segments(config["segments"])
    asm_files: set = get_asm_files(config["options"], file_segments)
    src_files: set = get_src_files(config["options"], file_segments)
    asset_files: set = get_asset_files(
        config["options"], file_segments, tuple(args.asset_filter)
    )

    # These are currently sorted for ease of comparison/debugging, but it isn't relevant for actual function
    match args.list_type:
        case "merged":
            print(" ".join(sorted(file_segments)))
        case "asm_files":
            print(" ".join(sorted(asm_files)))
        case "src_files":
            print(" ".join(sorted(src_files)))
        case "o_files":
            print(
                " ".join(
                    sorted(f"{file}.o" for file in asm_files | src_files | asset_files)
                )
            )


def get_repo_root(current_dir: Path = Path(__file__).resolve().parent) -> Path:
    """Steps backward from the file location to infer the root of the repo"""
    if next(current_dir.glob("src"), None) or current_dir.name == "/":
        return current_dir
    else:
        return get_repo_root(current_dir.parent)


if __name__ == "__main__":
    if len(sys.argv) > 1:
        main(sys.argv[1:])
    else:
        # This is for development and debugging purposes and isn't intended to be used in the final tool
        os.chdir(get_repo_root())
        main(["--version=pspeu", "list", "lib", "o_files", "-c", "splat", "-H", "-s"])
