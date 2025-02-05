#!/usr/bin/env python3

import argparse
import os
import subprocess
import yaml
import struct
import sys

parser = argparse.ArgumentParser(
    description="Make files inside config/ for a PSP overlay"
)
parser.add_argument(
    "input",
    help="path of the overlay to disassemble",
)

def omgpanic(s: str):
    print(f"\033[1;31;m{s}\033[m", file=sys.stderr)
    exit(1)

def align(n: int, alignment: int):
    return int((n + alignment - 1) / alignment) * alignment


def get_ovl_header(input: str):
    """
    Parse and return the Metrowerk overlay header that contains all the
    necessary metadata to successfully parse the binary file
    """

    with open(input, "rb") as file:
        header_data = file.read(48)

    if len(header_data) != 48:
        omgpanic("not a valid overlay")

    unpacked_data = struct.unpack("I I I I I I I I 16s", header_data)
    if unpacked_data[0] != 0x336F574D:
        omgpanic("not a valid overlay")

    header = {
        "name": unpacked_data[8].split(b"\x00", 1)[0].decode("ascii"),
        "vram": unpacked_data[2],
        "text_len": unpacked_data[3],
        "data_len": unpacked_data[4],
        "bss_len": unpacked_data[5],
    }

    return header


def get_splat_config(
    input: str,
    ver: str,
    name: str,
    vram: int,
    text_len: int,
    data_len: int,
    bss_len: int,
):
    filename = input.split("/")[-1]
    is_weapon = filename.startswith("w0_") or filename.startswith("w1_")
    is_servant = filename.startswith("tt_")
    is_base = name == "dra" or name == "ric" or name == "maria"
    is_stage = is_weapon == False and is_servant == False and is_base == False

    if is_weapon:
        path_stuff = f"weapon/{name}"
        file_stuff = name
    elif is_servant:
        path_stuff = f"servant/{name}"
        file_stuff = name
    elif is_stage:
        path_stuff = f"st/{name}"
        file_stuff = f"st{name}"
    else:
        path_stuff = name
        file_stuff = name

    return {
        "options": {
            "platform": "psp",
            "basename": file_stuff,
            "base_path": "..",
            "build_path": f"build/{ver}",
            "target_path": input,
            "asm_path": f"asm/{ver}/{path_stuff}_psp",
            "asset_path": f"assets/{path_stuff}",
            "src_path": f"src/{path_stuff}_psp",
            "ld_script_path": f"build/{ver}/{file_stuff}.ld",
            "compiler": "GCC",
            "symbol_addrs_path": [
                f"config/symbols.{ver}.txt",
                f"config/symbols.{ver}.{file_stuff}.txt",
            ],
            "undefined_funcs_auto_path": f"config/undefined_funcs_auto.{ver}.{file_stuff}.txt",
            "undefined_syms_auto_path": f"config/undefined_syms_auto.{ver}.{file_stuff}.txt",
            "find_file_boundaries": True,
            "use_legacy_include_asm": False,
            "migrate_rodata_to_functions": True,
            "asm_jtbl_label_macro": "jlabel",
            "symbol_name_format": "psp_$VRAM",
            "section_order": [".text", ".data", ".rodata", ".bss"],
            "ld_bss_is_noload": True,
            "disasm_unknown": True,
        },
    }


def estimate_c_file_split(input: str, text_len: int):
    """
    tries to detect a file split by looking for gaps on 0x10 aligned functions
    """
    with open(input, "rb") as f:
        f.seek(0x80)
        data = struct.unpack(f'{text_len>>2}i', f.read(text_len))
    splits = [0x80]
    for i in range(len(data)):
        n = data[i]
        if n != 0x03E00008: # jr $ra
            continue
        # check for a gap of at least two nops
        if (i & 3) > 1:
            continue
        if data[i + 1] != 0: # nop
            continue
        if data[i + 2] != 0: # nop
            continue
        offset = align(0x80 + i * 4, 0x10)
        if offset < text_len:
            splits += [offset]
    return splits

def make_config(input: str, version: str):
    class IndentDumper(yaml.Dumper):
        def increase_indent(self, flow=False, indentless=False):
            return super(IndentDumper, self).increase_indent(flow, False)

    ovl_header = get_ovl_header(input)
    vram = ovl_header["vram"]
    text_len = ovl_header["text_len"]
    data_len = ovl_header["data_len"]
    bss_len = ovl_header["bss_len"]
    data_start = align(text_len, 0x80)
    bss_start = align(vram + data_start + data_len, 0x80)
    file_size = os.stat(input).st_size
    splits = estimate_c_file_split(input, text_len)
    
    config = get_splat_config(
        input,
        version,
        str(ovl_header["name"]).split(".")[0],
        vram,
        ovl_header["text_len"],
        ovl_header["data_len"],
        ovl_header["bss_len"],
    )

    splat_config_path = f"config/splat.{version}.{config['options']['basename']}.yaml"
    with open(splat_config_path, "w") as f:
        f.write(yaml.dump(config, Dumper=IndentDumper, sort_keys=False))
        # now writes the rest manually because the default yaml formatting is horrifying
        text = [
            f'  asm_inc_header: |\n',
            f"    .set noat      /* allow manual use of $at */\n",
            f"    .set noreorder /* don't insert nops after branches */\n",
            f'    .include "macro.inc"\n',
            f'segments:\n',
            f'  - [0x0, bin, mwo_header]\n',
            f'  - name: {config["options"]["basename"]}\n',
            f'    type: code\n',
            f'    start: 0x80\n',
            f'    vram:  0x{vram+0x80:08X}\n',
            f'    bss_size: 0x{bss_len:X}\n',
            f'    align: 128\n',
            f'    subalign: 8\n',
            f'    subsegments:\n',
        ] + [
            f"      - [0x{offset:X}, c]\n" for offset in splits
        ] + [
            f'      - [0x{data_start:X}, data]\n',
            f'      - {{type: bss, vram: 0x{bss_start:X}}}\n',
            f'  - [0x{file_size:X}]\n',
        ]
        f.writelines(text)
    return splat_config_path


def split(splat_config_path):
    with subprocess.Popen(
        [ "splat", "split", splat_config_path],
        stdout=subprocess.PIPE,
        stdin=subprocess.PIPE,
        stderr=subprocess.PIPE,
        env=dict(os.environ)) as p:
        stdout_result, stderr_result = p.communicate()
        print(stdout_result)
        print(stderr_result)
        if p.returncode != 0:
            
            omgpanic("failed to split")
    return None


def adjust_include_asm(c_file, version):
    with open(c_file) as f:
        lines = f.readlines()
    with open(c_file, "w") as f:
        f.writelines([
            line.replace(f'INCLUDE_ASM("asm/{version}/', 'INCLUDE_ASM("')
            for line in lines
        ])
    return None


if __name__ == "__main__":
    print("Starting")
    # os.chdir('sotn-decomp')
    version = "pspeu"
    args = parser.parse_args()
    overlay = args.input
    ovl_input = f"disks/pspeu/PSP_GAME/USRDIR/res/ps/PSPBIN/{overlay}.bin"
    splat_config_path = make_config(ovl_input, version)
    with open(splat_config_path) as f:
        splat_config = yaml.load(f, Loader=yaml.SafeLoader)
    for symbol_path in splat_config["options"]["symbol_addrs_path"]:
        if not os.path.exists(symbol_path):
            with open(symbol_path, 'w') as f:
                f.write("")
    print("Splitting")
    split(splat_config_path)
    print("Splitted")
    # TODO cross-reference symbols
    
    src_path = splat_config["options"]["src_path"]
    for c_file in os.listdir(src_path):
        adjust_include_asm(os.path.join(src_path, c_file), version)
    print("Cleanup splat config")
    # os.remove(splat_config_path)
    # os.remove("src/st/" + overlay + "_psp")
    print("Done")
