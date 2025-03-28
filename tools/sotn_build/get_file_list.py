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


def GetConfig(args: argparse.Namespace) -> dict:
    """Uses the supplied parameters to retrieve and return a dict of config values with version and ovl added"""
    configDir = os.path.realpath(CONFIG_BASE_DIR)
    configPattern = re.compile(
        CONFIG_PATTERNS[args.config_type].substitute(version=args.version, ovl=args.ovl)
    )

    # We only care about the first match we find since there shouldn't be multiple matches
    configPath = next(
        (file for file in os.listdir(configDir) if configPattern.match(file)), None
    )

    if configPath:
        configPath = os.path.realpath(os.path.join(configDir, configPath))
        with open(configPath) as configFile:
            config = yaml.safe_load(configFile)

        extraOptions = {
            "version": args.version,
            "ovl": args.ovl,
            "ignore_hidden": args.ignore_hidden,
        }
        config["options"].update(extraOptions)

        return config
    else:  # Raise an exception if no configPath was found
        raise FileNotFoundError(
            f"Could not find a {args.config_type} config for {args.version} {args.ovl} in {configDir}"
        )


def GetFileSegments(segments: list) -> list[list]:
    """Returns a list of file segments from a list of segments"""
    # Extracts segment information
    segs = [seg for seg in segments if isinstance(seg, list)]
    subsegs = [
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


def NormalizeArgs(arg: list[str]) -> list[str]:
    """Takes a list of items that are either a string of comma separated items or an individual item and normalizes it into a list of individual items"""
    if arg:
        return ",".join(arg).split(",")
    else:
        return []


def GetAsmFiles(options: dict, segments: list[list]) -> set[str]:
    """Constructs a list of asm files from a given segment list"""
    asmPath: str = options["asm_path"].rstrip("/")
    dataPath: str = os.path.join(options["asm_path"], "data").rstrip("/")

    asmFiles: set = {
        FILENAME_TEMPLATE.substitute(
            path=asmPath, filename=seg[2] if len(seg) >= 3 else seg[1], ext="s"
        )
        for seg in segments
        if len(seg) >= 2 and seg[1] in SEG_TYPES["asm"]
    }

    # A seg type is added with a leading . for each existing data seg type
    if not options["ignore_hidden"]:
        dataSegTypes = SEG_TYPES["data"] + tuple(
            f".{type}" for type in SEG_TYPES["data"]
        )

    dataFiles: set = {
        FILENAME_TEMPLATE.substitute(
            path=dataPath,
            # If a segment has 3 or more elements, then it has a name
            # If it only has 1 or 2 elements, we use the memory address as the name
            filename=seg[2] if len(seg) >= 3 else f"{seg[0]:X}",
            # If it is only 1 element, then we assume it is bss and that the element is a memory address
            ext=f"{seg[1].lstrip('.')}.s" if len(seg) >= 2 else "bss.s",
        )
        for seg in segments
        if (len(seg) >= 2 and seg[1] in (dataSegTypes)) or len(seg) == 1
    }

    return {file for file in dataFiles | asmFiles if os.path.exists(file)}


def GetSrcFiles(options: dict, segments: list[list]) -> tuple[str]:
    """Constructs a list of source files from splat segments"""
    srcPath = options["src_path"].rstrip("/")

    # We assume that if there is a data file, then there should be a c file for it
    # This is safe since we're using sets and we validate existence on the final set
    extraFiles: set = {
        FILENAME_TEMPLATE.substitute(path=srcPath, filename=seg[2], ext="c")
        for seg in segments
        if len(seg) >= 3 and seg[1].startswith(".")
    }
    cFiles: set = {
        FILENAME_TEMPLATE.substitute(
            path=srcPath,
            filename=seg[2] if len(seg) >= 3 else f"{seg[0]:X}",
            ext=seg[1],
        )
        for seg in segments
        if len(seg) >= 2 and seg[1] in SEG_TYPES["src"]
    }

    return {file for file in cFiles | extraFiles if os.path.exists(file)}


# This function still needs a bit of refinement, but it is serviceable for now
def GetAssetFiles(
    options: dict, segments: list[list], assetFilters: tuple[tuple]
) -> set[str]:
    """Constructs a list of asset files using a directory listing or the segments"""
    assetPath = options["asset_path"].rstrip("/")

    # This conditional needs to be cleaned up and probably relocated for easier code maintenance
    if (
        options["platform"] == "psx"
        and ("st/" in assetPath or "boss/" in assetPath)
        and options["ovl"] != "sel"
        and assetFilters == (("", ""),)
    ):
        assetFilters = tuple(
            tuple(f.split("*"))
            for f in ("D_801*.bin", "*.gfxbin", "*.palbin", "cutscene_*.bin")
        )

    # The file listing is really the only one used currently because some asset segment files are built by splat extensions
    # and the resulting files aren't directly specified in the config
    if os.path.isdir(assetPath):
        assetFiles = {
            os.path.join(assetPath, file)
            for file in os.listdir(assetPath)
            if any(
                file.startswith(sFilter) and file.endswith(eFilter)
                for sFilter, eFilter in assetFilters
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
        assetFiles = {
            FILENAME_TEMPLATE.substitute(
                path=assetPath, filename=seg[2], ext=extension.get(seg[1], seg[1])
            )
            for seg in segments
            if len(seg) >= 3 and seg[1] in SEG_TYPES["asset"]
        }
        # Add a .bin file for each .dec file and supplement assetFiles with a directory listing
        assetFiles.update(
            {file.replace("dec", "bin") for file in assetFiles if ".dec" in file}
        )
    return assetFiles


# Dedicated function for ParseArgs so that this file can be imported in a module and still have the ability to parse out the proper args
def ParseArgs(args: list):
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
    parserList = subparsers.add_parser("list", help="Retrieve a list of files")
    parserList.add_argument("ovl", type=str, help="Overlay to target")
    parserList.add_argument(
        "list_type",
        type=str,
        choices=("src_files", "o_files", "merged"),
        help="What to list",
    )
    parserList.add_argument(
        "-c",
        "--config-type",
        type=str,
        choices=list(CONFIG_PATTERNS.keys()),
        required=True,
        help="Type of config to reference",
    )
    parserList.add_argument(
        "-s",
        "--shared",
        action="store_true",
        required=False,
        help="Get shared src files instead of ovl src files",
    )
    parserList.add_argument(
        "-H",
        "--ignore-hidden",
        action="store_true",
        required=False,
        help='Ignore file types that begin with "dot" in splat configs',
    )
    parserList.add_argument(
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
    args = ParseArgs(args)
    config = GetConfig(args)

    if args.shared:
        srcPath: str = re.sub(
            f"/{config["options"]["ovl"]}", "", config["options"]["src_path"]
        )

        asmFiles: set = set()
        srcFiles: set = {
            os.path.join(srcPath, file)
            for file in os.listdir(srcPath)
            if file.endswith(".c") and os.path.isfile(os.path.join(srcPath, file))
        }
        assetFiles: set = set()
    else:
        assetFilters: tuple = tuple(
            tuple(aFilter.split("*")) for aFilter in NormalizeArgs(args.asset_filter)
        )
        fileSegments: list = GetFileSegments(config["segments"])
        asmFiles: set = GetAsmFiles(config["options"], fileSegments)
        srcFiles: set = GetSrcFiles(config["options"], fileSegments)
        assetFiles: set = GetAssetFiles(config["options"], fileSegments, assetFilters)

        if args.list_type == "merged":
            print(" ".join(sorted(fileSegments)))

    # These are currently sorted for ease of comparison/debugging, but it isn't relevant for actual function
    if args.list_type == "asm_files":
        print(" ".join(sorted(asmFiles)))
    elif args.list_type == "src_files":
        print(" ".join(sorted(srcFiles)))
    elif args.list_type == "o_files":
        print(
            " ".join(sorted(f"{file}.o" for file in asmFiles | srcFiles | assetFiles))
        )


if __name__ == "__main__":
    if len(sys.argv) > 1:
        main(sys.argv[1:])
    else:
        # This is for ensuring proper path and args when running in atypical ways during debugging
        os.chdir(os.path.join(os.getenv("HOME"), "github/sotn-decomp"))
        main(["--version=pspeu", "list", "dra", "o_files", "-c", "splat", "-H"])
