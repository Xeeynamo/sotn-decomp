#!/usr/bin/env python3

import argparse
import yaml
import sys
import os
import re
from string import Template

# I intend things like this to be stored in a conf file when this functionality is more established in the project
# Since it has a high likelihood of changing and isn't very complex, keeping it here is easier for now
CONFIG_BASE_DIR: str = "config"
CONFIG_PATTERNS: dict[Template] = {
    "splat": Template("splat.$version.(?:st|bo)?$ovl.yaml")
}
# I would prefer os.path.join(path,filename.ext) because it is the safer method, but it
# further muddies set comprehensions that are already difficult to read in some cases
FILENAME_TEMPLATE: Template = Template("$path/$filename.$ext")
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
    config_dir: str = os.path.realpath(CONFIG_BASE_DIR)
    config_pattern: re.Pattern = re.compile(
        CONFIG_PATTERNS[args.config_type].substitute(version=args.version, ovl=args.ovl)
    )

    # We only care about the first match we find since there shouldn't be multiple matches
    config_path: str = next(
        (file for file in os.listdir(config_dir) if config_pattern.match(file)), None
    )

    if config_path:
        config_path = os.path.realpath(os.path.join(config_dir, config_path))
        with open(config_path) as config_file:
            config: dict = yaml.safe_load(config_file)

        extra_options: dict = {
            "version": args.version,
            "ovl": args.ovl,
            "ignore_hidden": args.ignore_hidden,
            "include_shared": args.include_shared,
        }
        config["options"].update(extra_options)

        return config
    else:  # Raise an exception if no config_path was found
        raise FileNotFoundError(
            f"Could not find a {args.config_type} config for {args.version} {args.ovl} in {config_dir}"
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
    # Converts docts that contain segment information into lists
    segs.extend(
        [seg.get("start", 0x0), seg["type"].replace("code", "c"), seg["name"]]
        for seg in segments + subsegs
        if isinstance(seg, dict) and "name" in seg and "type" in seg
    )
    # Only returns segment elements that are lists
    return [seg for seg in segs + subsegs if isinstance(seg, list)]


def normalize_args(arg: list[str]) -> list[str]:
    """Takes a list of items that are either a string of comma separated items or an individual item and normalizes it into a list of individual items"""
    if arg:
        return ",".join(arg).split(",")
    else:
        return []


def get_asm_files(options: dict, segments: list[list]) -> set[str]:
    """Constructs a list of asm files from a given segment list"""
    asm_path: str = options["asm_path"].rstrip("/")
    data_path: str = os.path.join(options["asm_path"], "data").rstrip("/")

    asm_files: set = {
        FILENAME_TEMPLATE.substitute(
            path=asm_path, filename=seg[2] if len(seg) >= 3 else seg[1], ext="s"
        )
        for seg in segments
        if len(seg) >= 2 and seg[1] in SEG_TYPES["asm"]
    }

    # A seg type is added with a leading . for each existing data seg type
    if not options["ignore_hidden"]:
        data_seg_types = SEG_TYPES["data"] + tuple(
            f".{type}" for type in SEG_TYPES["data"]
        )

    data_files: set = {
        FILENAME_TEMPLATE.substitute(
            path=data_path,
            # If a segment has 3 or more elements, then it has a name
            # If it only has 1 or 2 elements, we use the memory address as the name
            filename=seg[2] if len(seg) >= 3 else f"{seg[0]:X}",
            # If it is only 1 element, then we assume it is bss and that the element is a memory address
            ext=f"{seg[1].lstrip('.')}.s" if len(seg) >= 2 else "bss.s",
        )
        for seg in segments
        if (len(seg) >= 2 and seg[1] in (data_seg_types)) or len(seg) == 1
    }

    return {file for file in data_files | asm_files if os.path.exists(file)}


def get_src_files(options: dict, segments: list[list]) -> set[str]:
    """Constructs a list of source files from splat segments"""
    src_path: str = options["src_path"].rstrip("/")

    # We assume that if there is a data file, then there should be a c file for it
    # This is safe since we're using sets and we validate existence on the final set
    extra_files: set = {
        FILENAME_TEMPLATE.substitute(path=src_path, filename=seg[2], ext="c")
        for seg in segments
        if len(seg) >= 3 and seg[1].startswith(".")
    }

    c_files: set = {
        FILENAME_TEMPLATE.substitute(
            path=src_path,
            filename=seg[2] if len(seg) >= 3 else f"{seg[0]:X}",
            ext=seg[1],
        )
        for seg in segments
        if len(seg) >= 2 and seg[1] in SEG_TYPES["src"]
    }

    if options["include_shared"]:
        src_path = src_path.replace(f"/{options["ovl"]}", "")
        c_files.update(
            {
                os.path.join(src_path, file)
                for file in os.listdir(src_path)
                if file.endswith(".c")
            }
        )

    return {file for file in c_files | extra_files if os.path.exists(file)}


# This function still needs a bit of refinement, but it is serviceable for now
def get_asset_files(
    options: dict, segments: list[list], asset_filters: tuple[tuple]
) -> set[str]:
    """Constructs a list of asset files using a directory listing or the segments"""
    asset_path = options["asset_path"].rstrip("/")

    # This conditional needs to be cleaned up and probably relocated for easier code maintenance
    if (
        options["platform"] == "psx"
        and ("st/" in asset_path or "boss/" in asset_path)
        and options["ovl"] != "sel"
        and asset_filters == (("", ""),)
    ):
        asset_filters = tuple(
            tuple(f.split("*"))
            for f in ("D_801*.bin", "*.gfxbin", "*.palbin", "cutscene_*.bin")
        )

    # The file listing is really the only one used currently because some asset segment files are built by splat extensions
    # and the resulting files aren't directly specified in the config
    if os.path.isdir(asset_path):
        asset_files = {
            os.path.join(asset_path, file)
            for file in os.listdir(asset_path)
            if any(
                file.startswith(start_filter) and file.endswith(end_filter)
                for start_filter, end_filter in asset_filters
            )
        }
    else:  # This method is included as something of a proof of concept/work in progress
        # Splat configs have different segment type names than what these files are saved as, so we translate them with this dict
        # dict.get() can have a default value specified, so we use extension.get(seg_type,seg_type) to get the translation
        # If there is no translation in the dict, then it just uses seg_type
        extension = {
            "cmp": "dec",
            "raw": "bin",
            "ci4": "png",
            "palette": "png",
            "assets": "json",
        }
        asset_files = {
            FILENAME_TEMPLATE.substitute(
                path=asset_path, filename=seg[2], ext=extension.get(seg[1], seg[1])
            )
            for seg in segments
            if len(seg) >= 3 and seg[1] in SEG_TYPES["asset"]
        }
        # Add a .bin file for each .dec file and supplement asset_files with a directory listing
        asset_files.update(
            {file.replace("dec", "bin") for file in asset_files if ".dec" in file}
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
        help="Filters to apply to asset_path files",
    )

    return parser.parse_args(args)


# This logic is expected to be contained elsewhere if this file is imported as a module
def main(args: list) -> None:
    args = parse_args(args)
    config = get_config(args)

    asset_filters: tuple = tuple(
        tuple(filter.split("*")) for filter in normalize_args(args.asset_filter)
    )
    file_segments: list = get_file_segments(config["segments"])
    asm_files: set = get_asm_files(config["options"], file_segments)
    src_files: set = get_src_files(config["options"], file_segments)
    asset_files: set = get_asset_files(config["options"], file_segments, asset_filters)

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


if __name__ == "__main__":
    if len(sys.argv) > 1:
        main(sys.argv[1:])
    else:
        # This is for ensuring proper path and args when running in atypical ways during debugging
        os.chdir(os.path.join(os.getenv("HOME"), "github/sotn-decomp"))
        main(["--version=pspeu", "list", "dra", "o_files", "-c", "splat", "-H"])
