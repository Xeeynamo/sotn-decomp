#!/usr/bin/env python3

import os
import re


def add_custom_arguments(parser):
    parser.add_argument(
        "--version",
        default=os.getenv("VERSION") or "us",
        dest="version",
        help="Decide what version of the game to use (us, jp12, pspeu, etc.)",
    )
    parser.add_argument(
        "--overlay",
        default="dra",
        dest="overlay",
        help="Defines which overlay to use for the diff (main, dra, mad, etc.)",
    )


def apply_saturn(config, args):
    name = args.overlay
    config["myimg"] = f"build/saturn/{name}.PRG"
    config["source_directories"] = [f"src/saturn/"]
    config["mapfile"] = f"build/saturn/{name.lower()}.map"
    config["baseimg"] = f"disks/saturn/{name}.PRG"
    config["objdump_executable"] = "sh-elf-objdump"
    config["arch"] = "sh2"


def apply(config, args):
    version = args.version
    if version == "saturn":
        apply_saturn(config, args)
        return
    name = re.sub(
        r"^(?:st|bos?s?)/?(?=[a-z])",
        "",
        f"{args.overlay.lower() if version != 'us' else args.overlay.upper()}",
        flags=re.IGNORECASE,
    )

    baseimgRoot = {
        "us": "disks/us",
        "hd": "disks/pspeu/PSP_GAME/USRDIR/res/ps/hdbin",
        "pspeu": "disks/pspeu/PSP_GAME/USRDIR/res/ps/PSPBIN",
    }
    binaryExt = {"us": "BIN", "hd": "bin", "pspeu": "bin"}
    path_prefix = ""
    name_prefix = ""

    if name.lower().startswith("w_"):
        name = name.lower().replace("w_", "w0_")
        path_prefix = "BIN" if version == "us" else ""
        name_prefix = "weapon/"
        config["myimg"] = os.path.join(f"build/{version}", f"{name_prefix}{name}.bin")
        config["source_directories"] = [
            "include",
            "src/weapon",
            f"asm/{version}/weapon/data",
        ]
    else:
        if name.lower() in os.listdir("src/st"):
            name_prefix = "st"
            path_prefix = f"ST/{name}" if version == "us" else ""
        elif name.lower() in os.listdir("src/boss"):
            name_prefix = "bo"
            path_prefix = f"BOSS/{name}" if version == "us" else ""
        elif version == "us" and name.lower() in os.listdir("src/servant"):
            path_prefix = "SERVANT"
        elif version == "us" and f"{name}.BIN" in os.listdir(f"disks/us/BIN"):
            path_prefix = "BIN"

        config["myimg"] = os.path.join(
            f"build/{version}", f"{name}.{binaryExt[version]}"
        )
        config["source_directories"] = [
            "include",
            os.path.join(
                "src",
                name_prefix.replace("bo", "boss"),
                name.lower().replace("tt_", "servant/tt_"),
            ),
            os.path.join(
                f"asm/{version}",
                name_prefix.replace("bo", "boss").replace("tt_", "servant/tt_"),
                name.lower().replace("tt_", "servant/tt_"),
            ),
        ]
        if version == "pspeu" and not name.startswith("tt_"):
            config["source_directories"].append(
                os.path.join("src", name_prefix.replace("bo", "boss"), f"{name}_psp")
            )

    config["mapfile"] = os.path.join(
        f"build/{version}", f"{name_prefix}{name.lower()}.map"
    )

    if version == "us":
        name = re.sub(r"w0_\d{3}", "WEAPON0", name)

    config["baseimg"] = os.path.join(
        baseimgRoot[version],
        path_prefix,
        f"{name.lower() if version == 'hd' else name}.{binaryExt[version]}",
    )

    config["objdump_executable"] = "mipsel-linux-gnu-objdump"
    config["arch"] = {
        "us": "mipsel",
        "hd": "mipsel",
        "pspeu": "mipsel:4000",
    }[version]
