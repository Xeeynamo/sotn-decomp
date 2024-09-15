#!/usr/bin/env python3

import argparse
import concurrent.futures
import hashlib
import os
import re
import shutil
import subprocess
from typing import Callable
import yaml
import struct
import sys

from symbols import sort_symbols_from_file

parser = argparse.ArgumentParser(
    description="Make files inside config/ for a PSP overlay"
)
parser.add_argument(
    "input",
    help="name of the overlay to disassemble",
)
parser.add_argument(
    "--version",
    required=False,
    help="game version",
)

##### GENERIC UTILITIES


def yowarning(s: str):
    print(f"\033[1;33;m{s}\033[m", file=sys.stderr)


def omgpanic(s: str):
    print(f"\033[1;31;m{s}\033[m", file=sys.stderr)
    exit(1)


def align(n: int, alignment: int):
    return int((n + alignment - 1) / alignment) * alignment


##### MIPS PARSING AND PATTERN SEARCH

LW = 0x23
ADDIU = 0x09
LUI = 0x0F
V0 = 0x02
SP = 0x1D
JR_RA = 0x03E00008
NOP = 0x00000000


def parse_mips_instruction(data: bytes):
    """
    Parse a 32-bit MIPS instruction and separate its components.
    Consts: https://github.com/Xeeynamo/mipsdump/blob/master/mipsdump/Instructions.fs
    Format: https://github.com/Xeeynamo/mipsdump/blob/master/mipsdump/Disassembler.fs
    """
    if len(data) < 4:
        omgpanic(f"unable to decompile mips instruction {len(data)} bytes long")
    if len(data) > 4:
        data = data[:4]
    word = int(struct.unpack("<I", data)[0])
    immu = word & 0xFFFF
    imm = immu
    if imm & 0x8000:
        imm -= 0x10000  # signed short
    return {
        "op": (word >> 26) & 0x3F,
        "rs": (word >> 21) & 0x1F,
        "rt": (word >> 16) & 0x1F,
        "rd": (word >> 11) & 0x1F,
        "shamt": (word >> 6) & 0x1F,
        "funct": word & 0x3F,
        "imm": imm,
        "immu": immu,
    }


def match_word(data: bytearray, match: Callable[[bytes], bool], r: range) -> int:
    for i in r:
        if match(data[i : i + 4]):
            return i
    return -1


def match_first_word(data: bytearray, match: Callable[[bytes], bool]) -> int:
    return match_word(data, match, range(0, len(data), 4))


def get_first_word(data: bytearray, word: int) -> int:
    search = struct.pack("<I", word)
    return match_first_word(data, lambda x: x == search)


def match_reverse_first_word(data: bytearray, match: Callable[[bytes], bool]) -> int:
    return match_word(data, match, range(len(data) - 4, -1, -4))


def get_reverse_first_word(data: bytearray, word: int) -> int:
    search = struct.pack("<I", word)
    return match_reverse_first_word(data, lambda x: x == search)


def estimate_gnu_c_function_begin(data: bytearray, reverse: bool):
    """
    Get an estimation of where a function begins within the specified data.
    This works by searching for 'addiu $sp, $sp, XX'.
    NOTE: it does not necessarily mark the beginning of the function.
    Use reverse=True to search from the end of the data array instead from the beginning.
    """

    def match_addiu_sp_sp(data: bytes) -> bool:
        mips = parse_mips_instruction(data)
        return mips["op"] == ADDIU and mips["rt"] == SP and mips["rs"] == SP

    if reverse:
        return match_reverse_first_word(data, match_addiu_sp_sp)
    else:
        return match_first_word(data, match_addiu_sp_sp)


def get_gnu_c_function_end(data: bytearray, reverse: bool):
    """
    Finds the end of a function within the specified data by searchinfg for 'jr $ra'.
    Use reverse=True to search from the end of the data array instead from the beginning.
    """
    if reverse:
        off = get_reverse_first_word(data, JR_RA)
    else:
        off = get_first_word(data, JR_RA)
    if off < 0:
        return off
    return off + 8


def get_gnu_c_first_jtbl_addr(data: bytearray):
    """
    Get the raw address of the first jump table used by the first function found.
    """

    def is_lw_to_v0(x: bytes) -> bool:
        mips = parse_mips_instruction(x)
        return mips["op"] == LW and mips["rt"] == V0

    def is_lui_to_dst(x: bytes, dst_reg: int) -> bool:
        mips = parse_mips_instruction(x)
        return mips["op"] == LUI and mips["rt"] == dst_reg and mips["rs"] == 0

    # search for 'jr $v0'
    off_jr = get_first_word(data, 0x00400008)
    if off_jr == -1:
        return -1
    # restrict search close to the offset found
    # assume the search begins within the previous 10 instructions
    subdata = data[off_jr - 40 : off_jr]
    # search for 'lw $v0, %lo(XXX)(YYY)
    off_lw = match_reverse_first_word(subdata, is_lw_to_v0)
    if off_lw == -1:
        return -1
    mips_lw = parse_mips_instruction(subdata[off_lw:])
    reg_src_lw = mips_lw["rs"]
    # search for 'lui $RS, %hi(ZZZ)
    off_lui = match_reverse_first_word(subdata, lambda x: is_lui_to_dst(x, reg_src_lw))
    if off_lui == -1:
        return -1
    mips_lui = parse_mips_instruction(subdata[off_lui:])
    return (mips_lui["immu"] << 16) + mips_lw["imm"]


def estimate_c_file_split(input: str, text_len: int):
    """
    tries to detect a file split by looking for gaps on 0x10 aligned functions
    PSP ONLY
    """
    with open(input, "rb") as f:
        f.seek(0x80)
        data = struct.unpack(f"{text_len>>2}i", f.read(text_len))
    splits = [0x80]
    for i in range(len(data)):
        n = data[i]
        if n != JR_RA:
            continue
        # check for a gap of at least two nops
        if (i & 3) > 1:
            continue
        if data[i + 1] != NOP:
            continue
        if data[i + 2] != NOP:
            continue
        offset = align(0x80 + i * 4, 0x10)
        if offset < text_len:
            splits += [offset]
    return splits


##### NAMES AND PATH UTILITIES


def is_psp(version: str) -> bool:
    return version.startswith("psp")


def is_weapon(ovl_name: str) -> bool:
    return ovl_name.startswith("w0_") or ovl_name.startswith("w1_")


def is_servant(ovl_name: str) -> bool:
    return ovl_name.startswith("tt_")


def is_base_ovl(ovl_name: str) -> bool:
    return ovl_name == "dra" or ovl_name == "ric" or ovl_name == "maria"


def is_boss(ovl_name: str) -> bool:
    ovl_name = ovl_name.lower()
    return ovl_name.startswith("bo") or ovl_name.startswith("rbo") or ovl_name == "mar"


def is_stage(ovl_name: str) -> bool:
    return (
        is_weapon(ovl_name) == False
        and is_servant(ovl_name) == False
        and is_base_ovl(ovl_name) == False
        and is_boss(ovl_name) == False
    )


def make_ovl_path(ovl_name: str, version: str) -> str:
    if is_psp(version):
        return f"disks/{version}/PSP_GAME/USRDIR/res/ps/PSPBIN/{ovl_name.lower()}.bin"
    elif version == "hd":
        return f"disks/{version}/PSP_GAME/USRDIR/res/ps/hdbin/{ovl_name.lower()}.bin"
    elif version == "saturn":
        omgpanic("saturn version not implemented")
    if is_servant(ovl_name):
        return f"disks/{version}/SERVANT/{ovl_name.upper()}.BIN"
    elif is_weapon(ovl_name):
        omgpanic("weapon overlays for PS1 needs to be manually extracted")
    elif is_boss(ovl_name):
        return f"disks/{version}/BOSS/{ovl_name.upper()}/{ovl_name.upper()}.BIN"
    elif is_stage(ovl_name):
        return f"disks/{version}/ST/{ovl_name.upper()}/{ovl_name.upper()}.BIN"
    elif is_base_ovl(ovl_name):
        return f"disks/{version}/BIN/{ovl_name.upper()}.BIN"
    omgpanic(f"'{ovl_name}' not recognized for '{version}' version")


##### SPLAT CONFIG UTILITIES


def get_metrowerk_ovl_header(input: str):
    """
    Parse and return the Metrowerk overlay header that contains all the
    necessary metadata to successfully parse the binary file.
    PSP ONLY
    """

    with open(input, "rb") as file:
        header_data = file.read(48)

    if len(header_data) != 48:
        omgpanic("not a valid overlay")

    unpacked_data = struct.unpack("I I I I I I I I 16s", header_data)
    if unpacked_data[0] != 0x336F574D:
        omgpanic("not a valid overlay")

    return {
        "name": unpacked_data[8].split(b"\x00", 1)[0].decode("ascii"),
        "vram": unpacked_data[2],
        "text_len": unpacked_data[3],
        "data_len": unpacked_data[4],
        "bss_len": unpacked_data[5],
    }


def get_splat_config_path(ovl_name: str, version: str) -> str:
    return f"config/splat.{version}.{ovl_name}.yaml"


def get_sha1(file_name: str) -> str:
    sha1 = hashlib.sha1()
    with open(file_name, "rb") as f:
        sha1.update(f.read())
    return sha1.hexdigest()


def get_splat_config(
    input: str,
    ver: str,
    name: str,
):
    filename = input.split("/")[-1]
    if is_weapon(name):
        path_stuff = f"weapon/{name}"
        file_stuff = name
    elif is_servant(name):
        path_stuff = f"servant/{name}"
        file_stuff = name
    elif is_boss(name):
        path_stuff = f"boss/{name}"
        file_stuff = f"bo{name}"
    elif is_stage(name):
        path_stuff = f"st/{name}"
        file_stuff = f"st{name}"
    else:
        path_stuff = name
        file_stuff = name

    platform = "psx"
    asm_path = f"asm/{ver}/{path_stuff}"
    bss_is_no_load = False
    section_order = [".data", ".rodata", ".text", ".bss", ".sbss"]
    if is_psp(ver):
        platform = "psp"
        asm_path += "_psp"
        bss_is_no_load = True
        section_order = [".text", ".data", ".rodata", ".bss"]

    return {
        "options": {
            "platform": platform,
            "basename": file_stuff,
            "base_path": "..",
            "build_path": f"build/{ver}",
            "target_path": input,
            "asm_path": asm_path,
            "asset_path": f"assets/{path_stuff}",
            "src_path": f"src/{path_stuff}",
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
            "symbol_name_format": f"{version}_$VRAM",
            "section_order": section_order,
            "ld_bss_is_noload": bss_is_no_load,
            "disasm_unknown": True,
        },
        "sha1": get_sha1(input),
    }


def make_config_psx(ovl_path: str, version: str):
    class IndentDumper(yaml.Dumper):
        def increase_indent(self, flow=False, indentless=False):
            return super(IndentDumper, self).increase_indent(flow, False)

    ovl_name = os.path.basename(ovl_path).split(".")[0].lower()
    if is_stage(ovl_name) or is_boss(ovl_name):
        vram = 0x80180000
    elif is_servant(ovl_name):
        vram = 0x80170000
    elif ovl_name == "dra":
        vram = 0x800A0000
    elif ovl_name == "ric":
        vram = 0x8013C000
    else:
        omgpanic(f"unable to determine vram for '{ovl_name}'")

    with open(ovl_path, "rb") as f:
        ovl_data = f.read()
    data_off = 0
    text_off = estimate_gnu_c_function_begin(ovl_data, False)
    bss_off = get_gnu_c_function_end(ovl_data, True)
    jtbl_addr = get_gnu_c_first_jtbl_addr(ovl_data[text_off:bss_off])
    if jtbl_addr > 0:
        rodata_off = jtbl_addr - vram
    else:
        rodata_off = -1
    file_size = os.stat(ovl_path).st_size
    config = get_splat_config(
        ovl_path,
        version,
        ovl_name,
    )

    subsegments = []
    if data_off >= 0:
        subsegments.append(f"      - [0x{data_off:X}, data]\n")
    if rodata_off >= 0:
        migrate_rodata = config["options"]["migrate_rodata_to_functions"]
        if migrate_rodata:
            subsegments.append(f"      - [0x{rodata_off:X}, .rodata, {version}]\n")
        else:
            subsegments.append(f"      - [0x{rodata_off:X}, rodata]\n")
    if text_off >= 0:
        subsegments.append(f"      - [0x{text_off:X}, c, {version}]\n")
    if bss_off >= 0:
        subsegments.append(f"      - [0x{bss_off:X}, sbss]\n")

    ovl_name = config["options"]["basename"]
    splat_config_path = get_splat_config_path(ovl_name, version)
    with open(splat_config_path, "w") as f:
        f.write(yaml.dump(config, Dumper=IndentDumper, sort_keys=False))
        # now writes the rest manually because the default yaml formatting is horrifying
        text = [
            f"segments:\n",
            f"  - name: {ovl_name}\n",
            f"    type: code\n",
            f"    start: 0\n",
            f"    vram:  0x{vram:08X}\n",
            f"    align: 4\n",
            f"    subalign: 4\n",
            f"    subsegments:\n",
        ]
        text.extend(subsegments)
        text.append(f"  - [0x{file_size:X}]\n")
        f.writelines(text)
    return splat_config_path


def make_config_psp(ovl_path: str, version: str):
    class IndentDumper(yaml.Dumper):
        def increase_indent(self, flow=False, indentless=False):
            return super(IndentDumper, self).increase_indent(flow, False)

    ovl_header = get_metrowerk_ovl_header(ovl_path)
    vram = ovl_header["vram"]
    text_len = ovl_header["text_len"]
    data_len = ovl_header["data_len"]
    bss_len = ovl_header["bss_len"]
    data_start = align(text_len, 0x80) + 0x80
    bss_start = align(vram + data_start + data_len - 0x80, 0x80)
    file_size = os.stat(ovl_path).st_size
    splits = estimate_c_file_split(ovl_path, text_len)
    config = get_splat_config(
        ovl_path,
        version,
        str(ovl_header["name"]).split(".")[0],
    )

    ovl_name = config["options"]["basename"]
    splat_config_path = f"config/splat.{version}.{ovl_name}.yaml"
    with open(splat_config_path, "w") as f:
        f.write(yaml.dump(config, Dumper=IndentDumper, sort_keys=False))
        # now writes the rest manually because the default yaml formatting is horrifying
        text = (
            [
                f"  asm_inc_header: |\n",
                f"    .set noat      /* allow manual use of $at */\n",
                f"    .set noreorder /* don't insert nops after branches */\n",
                f'    .include "macro.inc"\n',
                f"segments:\n",
                f"  - [0x0, bin, mwo_header]\n",
                f'  - name: {config["options"]["basename"]}\n',
                f"    type: code\n",
                f"    start: 0x80\n",
                f"    vram:  0x{vram+0x80:08X}\n",
                f"    bss_size: 0x{bss_len:X}\n",
                f"    align: 128\n",
                f"    subalign: 8\n",
                f"    subsegments:\n",
            ]
            + [f"      - [0x{offset:X}, c]\n" for offset in splits]
            + [
                f"      - [0x{data_start:X}, data]\n",
                f"      - {{type: bss, vram: 0x{bss_start:X}}}\n",
                f"  - [0x{file_size:X}]\n",
            ]
        )
        f.writelines(text)
    return splat_config_path


def exec(cmd: str, *args):
    cmd_args = [cmd]
    cmd_args.extend(args)
    with subprocess.Popen(
        args=cmd_args,
        stdout=subprocess.PIPE,
        stdin=subprocess.PIPE,
        stderr=subprocess.PIPE,
        env=dict(os.environ),
    ) as p:
        stdout_raw, stderr_raw = p.communicate()
        stdout_result = stdout_raw.decode("utf-8")
        stderr_result = stderr_raw.decode("utf-8")
        if p.returncode != 0:
            omgpanic(stdout_result + stderr_result)
    return stdout_result


def git(*args):
    return exec("git", *args)


def make(*args):
    return exec("make", *args)


def cargo_run(*args):
    run_args = ["run", "--release", "--"]
    run_args.extend(args)
    return exec("cargo", *run_args)


def find_dups(threshold, dir1, dir2) -> dict[str, str]:
    os.chdir("tools/dups")
    dir1 = os.path.join("../../", dir1)
    dir2 = os.path.join("../../", dir2)
    output = cargo_run("--threshold", f"{threshold}", "--dir", dir1, "--dir", dir2)
    os.chdir("../..")

    # format the output so it returns just a list of key-value pairs
    separator = "--------------"
    last_separator_index = len(output) - 1 - output[::-1].index(separator)
    lines = output[last_separator_index + 1 :].split("\n")
    pairs = {}
    for line in lines:
        items = line.split("|")
        if len(items) < 2:
            continue
        left = items[0].strip()
        right = items[1].strip()
        if len(left) == 0 or len(right) == 0:
            continue
        if right.find("func_") >= 0:  # ignore unnamed functions
            continue
        pairs[left] = right
    return pairs


def split(splat_config_path: str, disassemble_all: bool):
    if disassemble_all:
        return exec("splat", "split", splat_config_path, "--disassemble-all")
    else:
        return exec("splat", "split", splat_config_path)


def adjust_include_asm(c_file, version):
    with open(c_file) as f:
        lines = f.readlines()
    with open(c_file, "w") as f:
        f.writelines(
            [
                line.replace(f'INCLUDE_ASM("asm/{version}/', 'INCLUDE_ASM("').replace(
                    f'INCLUDE_RODATA("asm/{version}/', 'INCLUDE_RODATA("'
                )
                for line in lines
            ]
        )
    return


def list_all_files(path):
    """
    Return a list of all the files by walking through all subdirectories
    """
    list = []
    for root, dirs, files in os.walk(path):
        for file in files:
            list.append(os.path.join(root, file))
    return list


def get_asm_path(splat_config):
    return splat_config["options"]["asm_path"]


def get_src_path(splat_config):
    return splat_config["options"]["src_path"]


def get_symbol_prefix(splat_config):
    prefix = splat_config["options"]["symbol_name_format"]
    if prefix == None:
        return ""
    return str(prefix).replace("$VRAM", "")


def get_symbol_of_export_table(splat_config):
    asm_path = get_asm_path(splat_config)
    symbol_line = None
    for file in list_all_files(f"{asm_path}/nonmatchings"):
        with open(file) as f:
            while True:
                line = f.readline()
                if line == "":
                    break
                if " 1D09043C " not in line:  # lui   $a0, %hi(D_91CF738)
                    continue
                line = f.readline()
                if " 38F78424 " not in line:  # addiu $a0, $a0, %lo(D_91CF738)
                    continue
                maybe_symbol_line = f.readline()  # lui   $a1, %hi(D_psp_0924B960)
                line = f.readline()  # addiu $a1, $a1, %lo(D_psp_0924B960)
                line = f.readline()  # addiu $a2, $zero, 0x40
                line = f.readline()
                if " E127240E " not in line:  # jal   memcpy
                    continue
                symbol_line = maybe_symbol_line
                break
        if symbol_line != None:
            break
    if symbol_line == None:
        return None
    match = re.search(r"lui\s*\$a1,\s*%hi\(([A-Za-z0-9_]*)\)", symbol_line)
    if not match:
        return None
    return match.group(1)


def get_symbol_of_entity_table(splat_config):
    asm_path = get_asm_path(splat_config)
    symbol_line = None
    for file in list_all_files(f"{asm_path}/nonmatchings"):
        with open(file) as f:
            # get the previous 4 lines and look for the signature
            # at the 4th last line read
            buffer = [
                "",
                f.readline(),
                f.readline(),
                f.readline(),
            ]
            while True:
                buffer[0] = buffer[1]
                buffer[1] = buffer[2]
                buffer[2] = buffer[3]
                buffer[3] = f.readline()
                if buffer[3] == "":
                    break
                if " 30BC43AC " not in buffer[3]:  # sw    $v1, -0x43D0($v0)
                    continue
                if " C708023C " not in buffer[2]:  # lui   $v0, (0x8C70000 >> 16)
                    continue
                symbol_line = buffer[0]  # lui   $v1, %hi(D_psp_09265438)
                break
        if symbol_line != None:
            break
    if symbol_line == None:
        return None
    match = re.search(r"lui\s*\$v1,\s*%hi\(([A-Za-z0-9_]*)\)", symbol_line)
    if not match:
        return None
    return match.group(1)


def get_symbol_table(splat_config, table):
    table_symbol = table
    asm_path = get_asm_path(splat_config)
    table = []
    for file in list_all_files(f"{asm_path}/data"):
        with open(file) as f:
            while True:
                line = f.readline()
                if line == "":
                    break
                if f"glabel {table_symbol}" not in line:
                    continue
                while True:
                    line = f.readline()
                    if f".size {table_symbol}" in line:
                        break
                    table += [line]
                break
        if len(table) > 0:
            break
    if len(table) == 0:
        return None
    # /* 4C388 09283A08 20BE2309 */ .word func_psp_0923BE20
    # extract the '20BE2309' part
    table = [
        re.search(r"\/\* \w* \w* (\w*) \*\/ \.word \w*", line).group(1)
        for line in table
    ]
    # read it from the little-endian format from '20BE2309' to '0923BE20'
    table = [f"{line[6:8]}{line[4:6]}{line[2:4]}{line[0:2]}" for line in table]
    # finally convert it to an int
    return [int(line, 16) for line in table]


def add_symbol(splat_config, name: str, offset: int):
    if offset == 0:
        return

    # add symbol to the overlay symbol list
    symbol_file_name = splat_config["options"]["symbol_addrs_path"][1]
    sym_prefix = get_symbol_prefix(splat_config)
    with open(symbol_file_name, "a") as f:
        f.write(f"{name} = 0x{offset:08X};\n")
    sort_symbols_from_file(symbol_file_name)

    # do a find & replace on the extracted C code
    for c_file in list_all_files(get_src_path(splat_config)):
        adjust_include_asm(c_file, version)
        with open(c_file, "r") as f:
            lines = f.readlines()
        lines = [
            line.replace(f"D_{sym_prefix}{offset:08X}", name).replace(
                f"func_{sym_prefix}{offset:08X}", name
            )
            for line in lines
        ]
        with open(c_file, "w") as f:
            f.writelines(lines)


def hydrate_stage_export_table_symbols(splat_config, export_table):
    add_symbol(splat_config, "UpdateStageEntities", export_table[0])
    add_symbol(splat_config, "TestCollisions", export_table[1])
    add_symbol(splat_config, "UpdateTilemap", export_table[2])
    add_symbol(splat_config, "InitRoomEntities", export_table[3])
    add_symbol(splat_config, "g_Rooms", export_table[4])
    add_symbol(splat_config, "g_SpriteBanks", export_table[5])
    add_symbol(splat_config, "g_Cluts", export_table[6])
    # add_symbol(splat_config, "NULL", export_table[7]) # ??????
    add_symbol(splat_config, "g_TileLayers", export_table[8])
    add_symbol(splat_config, "g_EntityGfxs", export_table[9])
    add_symbol(splat_config, "UpdateStageEntitiesAlt", export_table[10])
    add_symbol(splat_config, "g_SpriteBank1", export_table[11])
    if len(export_table) <= 12:
        return
    add_symbol(splat_config, "g_SpriteBank2", export_table[12])
    # add_symbol(splat_config, "unk34", export_table[13])
    # add_symbol(splat_config, "unk38", export_table[14])
    # add_symbol(splat_config, "unk3C", export_table[15])


def hydrate_stage_entity_table_symbols(splat_config, export_table):
    if len(export_table) > 15 and export_table[14] != export_table[15]:
        yowarning(
            f"cannot make assumption of 'EntityDummy' at 0x{export_table[14]:08X}\n"
            "entity symbols will not be hydrated."
        )
        return
    add_symbol(splat_config, "EntityBreakable", export_table[0])
    add_symbol(splat_config, "EntityExplosion", export_table[1])
    add_symbol(splat_config, "EntityPrizeDrop", export_table[2])
    add_symbol(splat_config, "EntityDamageDisplay", export_table[3])
    add_symbol(splat_config, "EntityRedDoor", export_table[4])
    add_symbol(splat_config, "EntityIntenseExplosion", export_table[5])
    add_symbol(splat_config, "EntitySoulStealOrb", export_table[6])
    add_symbol(splat_config, "EntityRoomForeground", export_table[7])
    add_symbol(splat_config, "EntityStageNamePopup", export_table[8])
    add_symbol(splat_config, "EntityEquipItemDrop", export_table[9])
    add_symbol(splat_config, "EntityRelicOrb", export_table[10])
    add_symbol(splat_config, "EntityHeartDrop", export_table[11])
    add_symbol(splat_config, "EntityEnemyBlood", export_table[12])
    add_symbol(splat_config, "EntityMessageBox", export_table[13])
    add_symbol(splat_config, "EntityDummy", export_table[14])


def hydrate_servant_symbols(splat_config, export_table):
    # TODO give a meaningful name to this stuff
    # add_symbol(splat_config, "Init", export_table[0])
    # add_symbol(splat_config, "Update", export_table[1])
    # add_symbol(splat_config, "Unk08", export_table[2])
    # add_symbol(splat_config, "Unk0C", export_table[3])
    # add_symbol(splat_config, "Unk10", export_table[4])
    # add_symbol(splat_config, "Unk14", export_table[5])
    # add_symbol(splat_config, "Unk18", export_table[6])
    # add_symbol(splat_config, "Unk1C", export_table[7])
    # add_symbol(splat_config, "Unk20", export_table[8])
    # add_symbol(splat_config, "Unk24", export_table[9])
    # add_symbol(splat_config, "Unk28", export_table[10])
    # add_symbol(splat_config, "Unk2C", export_table[11])
    # add_symbol(splat_config, "Unk30", export_table[12])
    # add_symbol(splat_config, "Unk34", export_table[13])
    # add_symbol(splat_config, "Unk38", export_table[14])
    # add_symbol(splat_config, "Unk3C", export_table[15])
    return


def hydrate_weapon_symbols(splat_config, export_table):
    add_symbol(splat_config, "EntityWeaponAttack", export_table[0])
    add_symbol(splat_config, "func_ptr_80170004", export_table[1])
    add_symbol(splat_config, "func_ptr_80170008", export_table[2])
    add_symbol(splat_config, "func_ptr_8017000C", export_table[3])
    add_symbol(splat_config, "func_ptr_80170010", export_table[4])
    add_symbol(splat_config, "func_ptr_80170014", export_table[5])
    add_symbol(splat_config, "GetWeaponId", export_table[6])
    add_symbol(splat_config, "LoadWeaponPalette", export_table[7])
    add_symbol(splat_config, "EntityWeaponShieldSpell", export_table[8])
    add_symbol(splat_config, "func_ptr_80170024", export_table[9])
    add_symbol(splat_config, "func_ptr_80170028", export_table[10])
    add_symbol(splat_config, "WeaponUnused2C", export_table[11])
    add_symbol(splat_config, "WeaponUnused30", export_table[12])
    add_symbol(splat_config, "WeaponUnused34", export_table[13])
    add_symbol(splat_config, "WeaponUnused38", export_table[14])
    add_symbol(splat_config, "WeaponUnused3C", export_table[15])


def hydrate_psp_symbols(splat_config):
    need_to_update_symbols = False
    print("getting the export table...")
    ovl_name = splat_config["options"]["basename"]
    table = get_symbol_table(splat_config, get_symbol_of_export_table(splat_config))
    if table != None:
        if is_stage(ovl_name):
            print("adding stage symbols...")
            hydrate_stage_export_table_symbols(splat_config, table)
        elif is_servant(ovl_name):
            print("adding servant symbols...")
            hydrate_servant_symbols(splat_config, table)
        elif is_weapon(ovl_name):
            print("adding weapon symbols...")
            hydrate_weapon_symbols(splat_config, table)
        need_to_update_symbols = True

    if is_stage(ovl_name):
        print("getting the entity stage table...")
        entity_table_symbol = get_symbol_of_entity_table(splat_config)
        if entity_table_symbol != None:
            entity_table = get_symbol_table(splat_config, entity_table_symbol)
            hydrate_stage_entity_table_symbols(splat_config, entity_table)
            need_to_update_symbols = True

    if need_to_update_symbols == True:
        # disassemble once more to update the symbols
        need_to_update_symbols = False
        print("updating all symbols...")
        split(splat_config_path, True)


def hydrate_psx_duplicate_symbols(splat_config):
    """
    Hydrate the symbol list by comparing the extracted functions with those already detected
    in other overlays.
    This works by invoking `make force_symbols` and `split --disassemble-all` to disassemble
    existing decompiled function with the right names from other overlays and then launching
    the duplicate detection tool to hydrate the targeted overlay symbol list.
    """

    make("force_symbols")
    samples = ["dra", "ric", "stsel", "stdre", "stnp3", "stnz0", "stst0", "stwrp"]
    with concurrent.futures.ThreadPoolExecutor() as executor:
        executor.map(
            lambda name: split(get_splat_config_path(name, "us"), True), samples
        )
    git("checkout", "config/")

    left_asm_path = os.path.join(get_asm_path(splat_config), "nonmatchings")
    sym_prefix = get_symbol_prefix(splat_config)
    t = 0.9
    dups = (
        find_dups(t, left_asm_path, f"asm/us/dra/matchings")
        | find_dups(t, left_asm_path, f"asm/us/ric/matchings")
        | find_dups(t, left_asm_path, f"asm/us/st/sel/matchings")
        | find_dups(t, left_asm_path, f"asm/us/st/dre/matchings")
        | find_dups(t, left_asm_path, f"asm/us/st/np3/matchings")
        | find_dups(t, left_asm_path, f"asm/us/st/nz0/matchings")
        | find_dups(t, left_asm_path, f"asm/us/st/st0/matchings")
        | find_dups(t, left_asm_path, f"asm/us/st/wrp/matchings")
    )
    found = 0
    added = set()
    for left, right in dups.items():
        func_prefix = f"func_{sym_prefix}"
        if left.find(func_prefix) < 0:  # ignore malformed function names
            continue

        # avoid to add the same symbol to different offsets when dups are too similar
        if right in added:
            continue
        added.add(right)

        found += 1
        offset = int(left.split(func_prefix)[1], 16)
        add_symbol(splat_config, right, offset)
    return found


def assert_sotn_decomp_cwd():
    """
    Ensure the tool is running from the sotn-decomp root directory.
    If it does not, it tries to return back up to three directories.
    """
    for _ in range(3):
        cwd = os.getcwd()
        if (
            os.path.isdir(os.path.join(cwd, "tools"))
            and os.path.isdir(os.path.join(cwd, "src"))
            and os.path.isdir(os.path.join(cwd, "disks"))
            and os.path.isfile(os.path.join(cwd, "Makefile"))
        ):
            return
        # retry from directory up
        os.chdir("..")
    omgpanic("re-run this script from sotn-decomp root directory")


if __name__ == "__main__":
    assert_sotn_decomp_cwd()
    args = parser.parse_args()
    if args.version == None:
        args.version = os.getenv("VERSION")
        if args.version == None:
            args.version = "us"
    version = args.version
    overlay = args.input
    ovl_input = make_ovl_path(overlay, version)

    if is_psp(version):
        print("generating psp splat config...")
        splat_config_path = make_config_psp(ovl_input, version)
    else:
        print("generating psx splat config...")
        splat_config_path = make_config_psx(ovl_input, version)
    with open(splat_config_path) as f:
        splat_config = yaml.load(f, Loader=yaml.SafeLoader)
    for symbol_path in splat_config["options"]["symbol_addrs_path"]:
        if not os.path.exists(symbol_path):
            with open(symbol_path, "w") as f:
                f.write("")
    print(f"splitting {splat_config_path}...")
    split(splat_config_path, False)

    src_path = get_src_path(splat_config)
    print(f"adjusting files at {src_path}...")
    for c_file in list_all_files(src_path):
        adjust_include_asm(c_file, version)

    if is_psp(version):
        hydrate_psp_symbols(splat_config)
    else:
        print(f"finding duplicates (will take a while)...")
        found = hydrate_psx_duplicate_symbols(splat_config)
        if found > 0:
            print(f"cross-referenced {found} symbols, splitting again...")
            shutil.rmtree(get_asm_path(splat_config))
            split(splat_config_path, False)
    print("Done! 🫡")
