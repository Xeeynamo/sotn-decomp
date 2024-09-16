#!/usr/bin/env python3

import os


def add_custom_arguments(parser):
    parser.add_argument(
        "--version",
        default=None,
        dest="version",
        help="Decide what version of the game to use (us, jp12, pspeu, etc.)",
    )
    parser.add_argument(
        "--overlay",
        default="dra",
        dest="overlay",
        help="Defines which overlay to use for the diff (main, dra, st/mad, etc.)",
    )


def apply_psx_base(config, version, name):
    config["baseimg"] = f"disks/{version}/" + (f"{name}.bin").upper()
    config["myimg"] = f"build/{version}/" + (f"{name}.bin").upper()
    config["mapfile"] = f"build/{version}/{name}.map"
    config["source_directories"] = [f"src/{name}", "include", f"asm/{version}/{name}"]
    config["objdump_executable"] = "mipsel-linux-gnu-objdump"


def apply_psx_bin(config, version, name):
    config["baseimg"] = f"disks/{version}/" + (f"BIN/{name}.BIN").upper()
    config["myimg"] = f"build/{version}/" + (f"{name}.bin").upper()
    config["mapfile"] = f"build/{version}/{name}.map"
    config["source_directories"] = [f"src/{name}", "include", f"asm/{version}/{name}"]
    config["objdump_executable"] = "mipsel-linux-gnu-objdump"


def apply_psx_servant(config, version, name):
    config["baseimg"] = f"disks/{version}/" + (f"SERVANT/{name}.bin").upper()
    config["myimg"] = f"build/{version}/" + (f"{name}.bin").upper()
    config["mapfile"] = f"build/{version}/{name}.map"
    config["source_directories"] = [
        f"src/servant/{name}",
        "include",
        f"asm/{version}/servant/{name}",
    ]
    config["objdump_executable"] = "mipsel-linux-gnu-objdump"


def apply_psx_weapon(config, version, name):
    config["baseimg"] = f"disks/{version}/" + (f"SERVANT/{name}.bin").upper()
    config["myimg"] = f"build/{version}/weapon/w0_{name[2:]}.bin"
    config["mapfile"] = f"build/{version}/weapon/w0_{name[2:]}.map"
    config["source_directories"] = [
        f"src/weapon/{name}",
        "include",
        f"asm/{version}/weapon/{name}",
    ]
    config["objdump_executable"] = "mipsel-linux-gnu-objdump"


def apply_psx_stage(config, version, name):
    config["baseimg"] = f"disks/{version}/" + (f"ST/{name}/{name}.BIN").upper()
    config["myimg"] = f"build/{version}/" + (f"{name}.bin").upper()
    config["mapfile"] = f"build/{version}/st{name}.map"
    config["source_directories"] = [
        f"src/st/{name}",
        f"src/st/{name}_psp",
        "include",
        f"asm/{version}/st/{name}",
    ]
    config["objdump_executable"] = "mipsel-linux-gnu-objdump"


def apply_psx_boss(config, version, name):
    config["baseimg"] = f"disks/{version}/" + (f"BOSS/{name}/{name}.BIN").upper()
    config["myimg"] = f"build/{version}/" + (f"{name}.bin").upper()
    config["mapfile"] = f"build/{version}/bo{name}.map"
    config["source_directories"] = [
        f"src/boss/{name}",
        f"src/boss/{name}_psp",
        "include",
        f"asm/{version}/boss/{name}",
    ]
    config["objdump_executable"] = "mipsel-linux-gnu-objdump"


def apply_saturn(config, name):
    config["arch"] = "sh2"
    config["baseimg"] = f"disks/saturn" + (f"/{name}.PRG").upper()
    config["myimg"] = f"build/saturn" + (f"/{name}.PRG").upper()
    config["mapfile"] = f"build/saturn/{name}.map"
    config["source_directories"] = [f"src/saturn/"]
    config["objdump_executable"] = "sh-elf-objdump"


def apply(config, args):
    version = args.version or os.getenv("VERSION") or "us"
    if version == "saturn":
        apply_saturn(config, args.overlay)
    else:
        name = args.overlay or "dra"
        if name.startswith("st/"):
            apply_psx_stage(config, version, name[3:])
        elif name.startswith("st"):
            apply_psx_stage(config, version, name[2:])
        elif name.startswith("bo/"):
            apply_psx_boss(config, version, name[3:])
        elif name.startswith("bo"):
            apply_psx_boss(config, version, name[2:])
        elif name.startswith("tt_"):
            apply_psx_servant(config, version, name)
        elif name.startswith("w_"):
            apply_psx_weapon(config, version, name)
        elif name == "dra" or name == "main":
            apply_psx_base(config, version, name)
        else:
            apply_psx_bin(config, version, name)
        config["arch"] = "mipsel:4000" if version == "pspeu" else "mipsel"
        config["objdump_executable"] = "mipsel-linux-gnu-objdump"
