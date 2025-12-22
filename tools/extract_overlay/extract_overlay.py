#!/usr/bin/env python3

import os
import sys
import shutil
import argparse
import hashlib
import time
import re
import multiprocessing
from pathlib import Path
from subprocess import run
from types import SimpleNamespace
from collections import Counter
from mako.template import Template

sys.path.insert(0, str(Path(__file__).parent.parent))
import sotn_utils
from symbols import sort, extract_dynamic_symbols, Symbol

"""
Handles many tasks for adding an overlay:
- Extracts the data necessary to generate an initial config
- Parses known data tables (psx header, EntityUpdates, psp export table)
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


def build(targets=[], plan=True, dynamic_syms=False, build=True, version="us"):
    logger = sotn_utils.get_logger()
    cmds = {}
    env = os.environ.copy()
    # Ensure the correct VERSION is passed
    if version:
        env["VERSION"] = version
    if dynamic_syms:
        env.update({"FORCE_SYMBOLS": ""})
    if plan:
        ret_key = None
        Path(f"build/{version}/").mkdir(parents=True, exist_ok=True)
        cmds[f"python3 tools/builds/gen.py build/{version}/build.ninja"] = ""
    if build:
        ret_key = (
            f"ninja -f build/{version}/build.ninja {' '.join(f"{x}" for x in targets)}"
        )
        cmds[ret_key] = ""

    for cmd in cmds:
        cmds[cmd] = run(cmd.split(), env=env, capture_output=True, text=True)
        if cmds[cmd].returncode != 0:
            logger.error(
                f"Command '{cmd}' returned non-zero exit status {cmds[cmd].returncode}"
            )
            if cmds[cmd].stdout:
                logger.warning(cmds[cmd].stdout.rstrip("\n"))
            if cmds[cmd].stderr:
                logger.error(cmds[cmd].stderr.rstrip("\n"))
            raise SystemExit

    if ret_key:
        return cmds[ret_key]


def add_undefined_symbol(version, symbol, address):
    symbol_line = f"{symbol} = 0x{address:08X};"
    undefined_syms = Path(f"config/undefined_syms.{version}.txt")
    undefined_syms_lines = undefined_syms.read_text().splitlines()
    if symbol_line not in undefined_syms_lines:
        undefined_syms_lines.append(symbol_line)
        undefined_syms.write_text("\n".join(undefined_syms_lines) + "\n")
        sort(undefined_syms)


def ovl_sort(name):
    game = "dra ric maria "
    stage = "are cat cen chi dai dre lib mad no0 no1 no2 no3 no4 np3 nz0 nz1 sel st0 top wrp "
    rstage = (
        "rare rcat rcen rchi rdai rlib rno0 rno1 rno2 rno3 rno4 rnz0 rnz1 rtop rwrp "
    )
    boss = "bo0 bo1 bo2 bo3 bo4 bo5 bo6 bo7 mar rbo0 rbo1 rbo2 rbo3 rbo4 rbo5 rbo6 rbo7 rbo8 "
    servant = "tt_000 tt_001 tt_002 tt_003 tt_004 tt_005 tt_006 "

    name = Path(name).stem.lower()
    basename = name.replace("f_", "")
    if basename == "main":
        group = 0
    elif basename in game and basename != "mar":
        group = 1
    elif basename in stage:
        group = 2
    elif basename in rstage:
        group = 3
    elif basename in boss:
        group = 4
    elif basename in boss and basename.startswith("r"):
        group = 5
    elif name in servant:
        group = 6
    elif "weapon" in name or "w0_" in name or "w1_" in name:
        group = 7
    else:
        group = 8

    return (group, basename, name.startswith("f_"))


def add_sha1_hashes(ovl_config):
    check_file_path = Path(f"config/check.{ovl_config.version}.sha")
    check_file_lines = check_file_path.read_text().splitlines()
    new_lines = check_file_lines.copy()
    bin_line = (
        f"{ovl_config.sha1}  build/{ovl_config.version}/{ovl_config.target_path.name}"
    )
    if bin_line not in new_lines:
        new_lines.append(bin_line)
    fbin_path = ovl_config.target_path.with_name(
        f"{"f" if ovl_config.platform == "psp" else "F"}_{ovl_config.target_path.name}"
    )
    if fbin_path.exists():
        fbin_sha1 = hashlib.sha1(fbin_path.read_bytes()).hexdigest()
        fbin_line = f"{fbin_sha1}  build/{ovl_config.version}/{fbin_path.name}"
        if fbin_line not in new_lines:
            new_lines.append(fbin_line)
    if new_lines != check_file_lines:
        sorted_lines = sorted(new_lines, key=lambda x: ovl_sort(x.split()[-1]))
        check_file_path.write_text(f"{"\n".join(sorted_lines)}\n")


def create_initial_files(ovl_config, spinner=SimpleNamespace(message="")):
    spinner.message = f"creating initial files for overlay {ovl_config.name.upper()}"
    ovl_config.write_config()
    for symbol_path in ovl_config.symbol_addrs_path:
        symbol_path.touch(exist_ok=True)

    ovl_include_path = (
        ovl_config.src_path_full.parent / ovl_config.name / f"{ovl_config.name}.h"
    )
    create_ovl_include(None, ovl_config.name, ovl_config.ovl_type, ovl_include_path)
    spinner.message = f"adding sha1 hashes to check file"
    add_sha1_hashes(ovl_config)
    spinner.message = f"performing initial split using config {ovl_config.config_path}"
    sotn_utils.splat_split(ovl_config.config_path, ovl_config.disassemble_all)
    spinner.message = f"adjusting initial include asm paths"
    src_text = ovl_config.first_src_file.read_text()
    adjusted_text = src_text.replace(f'("asm/{ovl_config.version}/', '("')
    ovl_config.first_src_file.write_text(adjusted_text)
    asm_path = ovl_config.asm_path.joinpath(ovl_config.nonmatchings_path)
    if ovl_config.platform == "psp":
        spinner.message = f"finding and parsing the psp {ovl_config.name.upper()} load function for symbols"
        ovl_load_symbol, ovl_header_symbol, entity_updates, symexport_text = (
            parse_psp_ovl_load(ovl_config.name, ovl_config.path_prefix, asm_path)
        )

        if not ovl_config.symexport_path.exists():
            spinner.message = "creating symexport file"
            ovl_config.symexport_path.write_text(symexport_text)
    else:
        ovl_load_symbol, ovl_header_symbol, entity_updates = None, None, {}

    spinner.message = f"generating new {ovl_config.version} build plan including {ovl_config.name.upper()}"
    build(build=False, version=ovl_config.version)
    spinner.message = (
        f"building initial {ovl_config.ld_script_path.with_suffix('.elf')}"
    )
    build(
        [f"{ovl_config.ld_script_path.with_suffix('.elf')}"], version=ovl_config.version
    )

    return ovl_load_symbol, ovl_header_symbol, entity_updates


def create_ovl_include(entity_updates, ovl_name, ovl_type, ovl_include_path):
    entity_funcs = []
    if entity_updates:
        camel_case_pattern = re.compile(r"([A-Za-z])([A-Z][a-z])")
        for i, func in enumerate([symbol.name for symbol in entity_updates]):
            if func == "EntityDummy":
                entity_funcs.append((func, f"E_DUMMY_{i+1:X}"))
            elif func.startswith("Entity") or func.startswith("OVL_EXPORT(Entity"):
                entity_funcs.append(
                    (
                        func,
                        camel_case_pattern.sub(
                            r"\1_\2", func.replace("OVL_EXPORT(", "").replace(")", "")
                        )
                        .upper()
                        .replace("ENTITY", "E"),
                    )
                )
            elif func == "0x00000000":
                entity_funcs.append((func, f"NULL"))
            else:
                entity_funcs.append((func, f"E_UNK_{i+1:X}"))

    template = Template((Path(__file__).parent / "ovl.h.mako").read_text())
    ovl_header_text = template.render(
        ovl_name=ovl_name,
        ovl_type=ovl_type,
        entity_updates=entity_funcs,
    )

    if not ovl_include_path.exists():
        ovl_include_path.parent.mkdir(parents=True, exist_ok=True)
        ovl_include_path.write_text(ovl_header_text)
    elif entity_funcs and "Entities" not in ovl_include_path.read_text():
        ovl_include_path.write_text(ovl_header_text)


def build_reference_asm(
    ovl_name, version, build_path, spinner=SimpleNamespace(message="")
):
    ref_pattern = re.compile(r"splat\.\w+\.(?P<prefix>st|bo)(?P<ref_ovl>\w+)\.yaml")
    ref_ovls = []
    for file in Path("config").glob(f"splat.{version}.*.yaml"):
        if ovl_name not in file.name and (match := ref_pattern.match(file.name)):
            prefix = match.group("prefix") or ""
            ref_name = match.group("ref_ovl")
            ld_path = build_path.joinpath(prefix + ref_name).with_suffix(".ld")
            ref_ovls.append(
                SimpleNamespace(prefix=prefix, name=ref_name, ld_path=ld_path)
            )

    if ref_ovls:
        ref_lds = tuple(ovl.ld_path for ovl in ref_ovls)
        found_elfs = tuple(build_path.glob("*.elf"))
        missing_elfs = tuple(
            ld.with_suffix(".elf")
            for ld in ref_lds
            if ld.with_suffix(".elf") not in found_elfs
        )
        if missing_elfs:
            spinner.message = (
                f"creating {len(missing_elfs)} missing reference .elf files"
            )
            build(missing_elfs, plan=True, version=version)

        spinner.message = "extracting dynamic symbols"
        for elf_file in (ld.with_suffix(".elf") for ld in ref_lds):
            config_path = f"config/splat.{version}.{elf_file.stem}.yaml"
            dyn_syms_path = f"build/{version}/config/dyn_syms.{elf_file.stem}.txt"
            extract_dynamic_symbols(config_path, dyn_syms_path)

        [ld.unlink(missing_ok=True) for ld in ref_lds]
        spinner.message = f"disassembling {len(ref_ovls)} reference overlays"
        build(ref_lds, dynamic_syms=True, version=version)

    return ref_ovls


def find_files_to_compare(ref_ovls, ovl_name, version):
    ref_files, check_files = [], []
    for dirpath, _, filenames in Path("asm").joinpath(version).walk():
        if any(
            ovl.name in dirpath.parts or f"{ovl.name}_psp" in dirpath.parts
            for ovl in ref_ovls
        ):
            ref_files.extend(dirpath / f for f in filenames)
        if ovl_name in dirpath.parts or f"{ovl_name}_psp" in dirpath.parts:
            check_files.extend(
                dirpath / f
                for f in filenames
                if f.startswith(f"func_{version}_") or f.startswith(f"D_{version}_")
            )
    return check_files, ref_files


# Validate logic and move to sotn-decomp
def parse_psp_ovl_load(ovl_name, path_prefix, asm_path):
    first_address_pattern = re.compile(r"\s+/\*\s+[A-F0-9]{1,5}\s+([A-F0-9]{8})\s")
    psp_entity_updates_pattern = r"""
        \s+/\*\s[A-F0-9]{1,5}(?:\s[A-F0-9]{8}){2}\s\*/\s+lui\s+\$v1,\s+%hi\((?P<entity>[A-Za-z0-9_]+)\)\n
        .*\n
        \s+/\*\s[A-F0-9]{1,5}\s[A-F0-9]{8}\sC708023C\s\*/.*\n
        \s+/\*\s[A-F0-9]{1,5}\s[A-F0-9]{8}\s30BC43AC\s\*/.*\n
    """
    psp_ovl_header_pattern = r"""
        \s+/\*\s[A-F0-9]{1,5}\s[A-F0-9]{8}\s1D09043C\s\*/.*\n
        \s+/\*\s[A-F0-9]{1,5}\s[A-F0-9]{8}\s38F78424\s\*/.*\n
        \s+/\*\s[A-F0-9]{1,5}(?:\s[A-F0-9]{8}){2}\s\*/\s+lui\s+\$a1,\s+%hi\((?P<header>[A-Za-z0-9_]+)\)\n
        (?:.*\n){2}
        \s+/\*\s[A-F0-9]{1,5}\s[A-F0-9]{8}\sE127240E\s\*/.*\n
    """
    psp_ovl_header_entity_table_pattern = re.compile(
        rf"{psp_entity_updates_pattern}(?:.*\n)+{psp_ovl_header_pattern}",
        re.VERBOSE,
    )
    ovl_load_name = None
    ovl_load_symbol = None
    ovl_header_symbol = None
    entity_updates_name = None
    for file in (
        dirpath / f
        for dirpath, _, filenames in asm_path.walk()
        for f in filenames
        if ".data.s" not in f
    ):
        file_text = file.read_text()
        # Todo: Clean up the condition checks
        if (
            " 1D09043C " in file_text
            and " 38F78424 " in file_text
            and " E127240E " in file_text
            and " C708023C " in file_text
            and " 30BC43AC " in file_text
        ):
            if match := psp_ovl_header_entity_table_pattern.search(file_text):
                if ovl_load_address := first_address_pattern.search(file_text):
                    ovl_load_symbol = Symbol(
                        f"{ovl_name.upper()}_Load",
                        int(ovl_load_address.group(1), 16),
                        None,
                    )
                ovl_load_name = file.stem
                ovl_header_symbol = match.group("header")
                entity_updates_name = match.group("entity")

    # build symexport lines, but only write if needed
    template = Template((Path(__file__).parent / "symexport.txt.mako").read_text())
    symexport_text = template.render(
        ovl_name=ovl_name,
        path_prefix=f"{path_prefix}_" if path_prefix else "",
        ovl_load_name=ovl_load_name,
    )

    return (
        ovl_load_symbol,
        ovl_header_symbol,
        {"name": entity_updates_name},
        symexport_text,
    )


def create_header_c(header_items, ovl_name, ovl_type, version, header_path):
    header_syms = [
        (
            f"{symbol.name.replace(f'{ovl_name.upper()}_', 'OVL_EXPORT(')})"
            if f"{ovl_name.upper()}_" in symbol.name
            else "NULL" if not symbol.address else symbol.name
        )
        for symbol in header_items
    ]
    common_syms = [
        "NULL",
        "Update",
        "HitDetection",
        "UpdateRoomPosition",
        "InitRoomEntities",
        "OVL_EXPORT(rooms)",
        "OVL_EXPORT(spriteBanks)",
        "OVL_EXPORT(cluts)",
        "OVL_EXPORT(pStObjLayoutHorizontal)",
        "g_pStObjLayoutHorizontal",
        "OVL_EXPORT(rooms_layers)",
        "OVL_EXPORT(gfxBanks)",
        "UpdateStageEntities",
    ]
    template = Template((Path(__file__).parent / "header.c.mako").read_text())
    new_header = template.render(
        ovl_include_path=f"{ovl_name}.h",
        ovl_type=ovl_type,
        header_syms=header_syms,
        common_syms=common_syms,
    )
    if header_path.is_file():
        existing_header = header_path.read_text()
        if new_header != existing_header:
            new_lines = new_header.rstrip("\n").splitlines()
            license = new_lines[0]
            include = new_lines[1]
            existing_lines = existing_header.rstrip("\n").splitlines()
            existing_lines = existing_lines[2:]
            ifdef = f"#ifdef VERSION_{'PSP' if version=='pspeu' else version.upper()}"
            new_header = f"{license}\n{include}\n{ifdef}\n{"\n".join(new_lines[2:])}\n#else\n{'\n'.join(existing_lines)}\n#endif\n"

    header_path.write_text(new_header)


def create_e_init_c(entity_updates, e_inits, ovl_name, e_init_c_path):
    if entity_updates:
        entity_funcs = [
            (
                f"{symbol.name.replace(f'{ovl_name.upper()}_','OVL_EXPORT(')})"
                if f"{ovl_name.upper()}_" in symbol.name
                else symbol.name
            )
            for symbol in entity_updates
        ]

        template = Template((Path(__file__).parent / "e_init.c.mako").read_text())
        output = template.render(
            ovl_name=ovl_name,
            entity_funcs=entity_funcs,
            e_inits=e_inits,
        )
        e_init_c_path.write_text(output)
        return True
    else:
        return False


def get_known_segments(ovl_name, segments_path):
    segments_config = sotn_utils.yaml.safe_load(segments_path.read_text())
    known_segments = []
    # TODO: Simplify this logic
    for label, values in segments_config.items():
        if not values or "functions" not in values:
            continue

        if "ovl" not in values or ovl_name in values["ovl"]:
            if "start" not in values:
                starts = [values["functions"][0]]
            elif isinstance(values["start"], str):
                starts = [values["start"]]
            elif isinstance(values["start"], list):
                starts = values["start"]
            else:
                continue

            if "end" in values and isinstance(values["end"], str):
                end = values["end"]
            else:
                end = ""

            functions = {
                v.replace("${prefix}", ovl_name.upper())
                for v in values.get("functions", [])
            }
            known_segments.extend(
                SimpleNamespace(
                    name=values.get("name", label).replace(
                        "${prefix}", ovl_name.upper()
                    ),
                    start=start.replace("${prefix}", ovl_name.upper()),
                    end=end.replace("${prefix}", ovl_name.upper()),
                    allow=set(starts) | functions,
                )
                for start in starts
            )
    # TODO: Check if this is an issue for multiple segments with the same start
    return {x.start: x for x in known_segments}


def find_psx_entity_updates(first_data_text, pStObjLayoutHorizontal_address=None):
    # we know that the EntityUpdates is always after the ovl header
    end_of_header = first_data_text.find(".size")
    # use the address of pStObjLayoutHorizontal if it was parsed from the header to reduce the amount of data we're searching through
    if pStObjLayoutHorizontal_address:
        start_index = first_data_text.find(
            f"{pStObjLayoutHorizontal_address:08X}", end_of_header
        )
    else:
        sotn_utils.get_logger().warning(
            "No address found for pStObjLayoutHorizontal, starting at end of header"
        )
        start_index = end_of_header

    # the first entity referenced after the ovl header, which should be the first element of EntityUpdates
    first_entity_index = first_data_text.find(" func_", start_index)
    # the last glabel before the first function pointer should be the EntityUpdates symbol
    entity_updates_index = first_data_text.rfind(
        "glabel", start_index, first_entity_index
    )
    # this is just a convoluted way of extracting the EntityUpdates symbol name
    # get the second word of the first line, which should be the EntityUpdates symbol name
    return {
        "name": first_data_text[entity_updates_index:first_entity_index]
        .splitlines()[0]
        .split()[1]
    }


def get_known_pairs(ovl_name, version):
    # TODO: move to yaml file
    known_pairs = [
        SimpleNamespace(first="func_801CC5A4", last="func_801CF438"),
        SimpleNamespace(first="func_801CC90C", last="func_801CF6D8"),
        SimpleNamespace(
            first="GetAnglePointToEntityShifted", last="GetAnglePointToEntity"
        ),
        SimpleNamespace(
            first="CreateEntityWhenInVerticalRange",
            last="CreateEntityWhenInHorizontalRange",
        ),
        SimpleNamespace(first="FindFirstEntityToTheRight", last="FindFirstEntityAbove"),
        SimpleNamespace(first="FindFirstEntityToTheLeft", last="FindFirstEntityBelow"),
        SimpleNamespace(first="CreateEntitiesToTheRight", last="CreateEntitiesAbove"),
        SimpleNamespace(first="CreateEntitiesToTheLeft", last="CreateEntitiesBelow"),
    ]
    # e_red_door typically comes before e_sealed door, but us rno2 and bo0 have e_sealed_door first
    if version == "us" and ovl_name in ["rno2", "bo0"]:
        known_pairs.append(
            SimpleNamespace(first="SealedDoorIsNearPlayer", last="EntityIsNearPlayer")
        )
    else:
        known_pairs.append(
            SimpleNamespace(first="EntityIsNearPlayer", last="SealedDoorIsNearPlayer")
        )

    return known_pairs


def parse_ovl_header(data_file_text, ovl_name, platform, header_symbol=None):
    ovl_header = [
        "Update",
        "HitDetection",
        "UpdateRoomPosition",
        "InitRoomEntities",
        f"{ovl_name.upper()}_rooms",
        f"{ovl_name.upper()}_spriteBanks",
        f"{ovl_name.upper()}_cluts",
        (
            "g_pStObjLayoutHorizontal"
            if platform == "psp"
            else f"{ovl_name.upper()}_pStObjLayoutHorizontal"
        ),
        f"{ovl_name.upper()}_rooms_layers",
        f"{ovl_name.upper()}_gfxBanks",
        "UpdateStageEntities",
        "unk2C",  # g_SpriteBank1
        "unk30",  # g_SpriteBank2
        "unk34",
        "unk38",
        "StageEndCutScene",
    ]
    header_start = (
        data_file_text.find(f"glabel {header_symbol}")
        if header_symbol
        else data_file_text.find("glabel ")
    )
    header_end = (
        data_file_text.find(f".size {header_symbol}")
        if header_symbol
        else data_file_text.find(".size ")
    )
    if header_start != -1:
        header = data_file_text[header_start:header_end]
        header_address = int(header.splitlines()[0].split("_")[-1], 16)
    else:
        return {}, None
    # Todo: Should this be findall or finditer?
    matches = re.findall(
        r"/\*\s[0-9A-F]{1,5}\s[0-9A-F]{8}\s(?P<address>[0-9A-F]{8})\s\*/\s+\.word\s+(?P<name>\w+)",
        header,
    )
    if matches:
        if len(matches) > 7:
            pStObjLayoutHorizontal_address = int.from_bytes(
                bytes.fromhex(matches[7][0]), "little"
            )
        else:
            pStObjLayoutHorizontal_address = None

        # Todo: Ensure this is doing a 1 for 1 line replacement, whether func, d_ or null
        # Todo: Make the address parsing more straight forward, instead of capturing both address and name
        header_items = tuple(
            Symbol(
                (
                    address[1]
                    if name.startswith("unk")
                    or (
                        not address[1].startswith("func_")
                        and not address[1].startswith("D_")
                        and not address[1].startswith("g_")
                    )
                    else "NULL" if address[0] == "0x00000000" else name
                ),
                int.from_bytes(bytes.fromhex(address[0]), "little"),
                None,
            )
            # Todo: Does this need the filtering, or should it just overwrite the existing regardless?
            for name, address in zip(ovl_header, matches)
        )
        return {
            "address": header_address,
            "size_bytes": len(header_items) * 4,
            "symbols": tuple(symbol for symbol in header_items if symbol.address),
            "items": header_items,
        }, pStObjLayoutHorizontal_address
    else:
        return {}, None


# TODO: Validate logic and move to sotn-decomp
def parse_init_room_entities(ovl_name, platform, init_room_entities_path, vram_start):
    init_room_entities_map = {
        f"{ovl_name.upper()}_pStObjLayoutHorizontal": 14 if platform == "psp" else 9,
        f"{ovl_name.upper()}_pStObjLayoutVertical": 22 if platform == "psp" else 12,
        "g_LayoutObjHorizontal": 18 if platform == "psp" else 17,
        "g_LayoutObjVertical": 26 if platform == "psp" else 19,
        "g_LayoutObjPosHorizontal": (
            138
            if platform == "psp" and ovl_name == "rnz0"
            else 121 if platform == "psp" else 81
        ),
        "g_LayoutObjPosVertical": (
            140
            if platform == "psp" and ovl_name == "rnz0"
            else 123 if platform == "psp" else 83
        ),
    }
    init_room_entities_symbol_pattern = re.compile(
        r"\s+/\*\s[0-9A-F]{1,5}\s[0-9A-F]{8}\s[0-9A-F]{8}\s\*/\s+[a-z]{1,5}[ \t]*\$\w+,\s%hi\(D_(?:\w+_)?(?P<address>[A-F0-9]{8})\)\s*"
    )
    lines = init_room_entities_path.read_text().splitlines()
    init_room_entities_symbols = {
        Symbol(
            name,
            int(
                init_room_entities_symbol_pattern.fullmatch(lines[i]).group("address"),
                16,
            ),
            None,
        )
        for name, i in init_room_entities_map.items()
        if "(D_" in lines[i]
    }

    create_entity_bss_start = (
        min(
            x.address
            for x in init_room_entities_symbols
            if x.name.startswith("g_Layout")
        )
        - vram_start
    )

    return init_room_entities_symbols, create_entity_bss_start


def parse_entity_updates(data_file_text, ovl_name, entity_updates_symbol):
    parsed_entity_updates = None
    known_entity_updates = [
        f"{ovl_name.upper()}_EntityBreakable",
        "EntityExplosion",
        "EntityPrizeDrop",
        "EntityDamageDisplay",
        f"{ovl_name.upper()}_EntityRedDoor",
        "EntityIntenseExplosion",
        "EntitySoulStealOrb",
        "EntityRoomForeground",
        "EntityStageNamePopup",
        "EntityEquipItemDrop",
        "EntityRelicOrb",
        "EntityHeartDrop",
        "EntityEnemyBlood",
        "EntityMessageBox",
        "EntityDummy",
        "EntityDummy",
        f"{ovl_name.upper()}_EntityBackgroundBlock",
        f"{ovl_name.upper()}_EntityLockCamera",
        "EntityUnkId13",
        "EntityExplosionVariants",
        "EntityGreyPuff",
    ]
    entity_updates_start = data_file_text.find(f"glabel {entity_updates_symbol}")
    entity_updates_end = data_file_text.find(f".size {entity_updates_symbol}")
    if entity_updates_start != -1:
        entity_updates_lines = data_file_text[
            entity_updates_start:entity_updates_end
        ].splitlines()

        first_e_init_start = data_file_text.find("glabel ", entity_updates_end)
        first_e_init_end = data_file_text.find("\n", first_e_init_start)
        first_e_init = data_file_text[first_e_init_start:first_e_init_end].split()[1]

        # if the last item is a null address, then it is padding
        if entity_updates_lines[-1].endswith("0x00000000"):
            entity_updates_lines.pop()

        table_start, entity_updates_address = next(
            (
                (i, int(line.split()[2], 16))
                for i, line in enumerate(entity_updates_lines)
                if " func" in line or " Entity" in line
            ),
            (len(entity_updates_lines) - 1, None),
        )
        entity_updates_lines = entity_updates_lines[table_start:]
        if matches := re.findall(
            r"/\*\s[0-9A-F]{1,5}\s[0-9A-F]{8}\s(?P<address>[0-9A-F]{8})\s\*/\s+\.word\s+(?P<name>\w+)",
            "\n".join(entity_updates_lines),
        ):
            entity_dummy_address = Counter([x[0] for x in matches]).most_common(1)[0][0]
            entity_dummy_address = int.from_bytes(
                bytes.fromhex(entity_dummy_address), "little"
            )
            known_symbols = tuple(
                Symbol(
                    address[1] if name == "skip" else name,
                    int.from_bytes(bytes.fromhex(address[0]), "little"),
                    None,
                )
                for name, address in zip(known_entity_updates, matches)
            )
            parsed_entity_updates = known_symbols + tuple(
                Symbol(
                    name.split()[-1],
                    int.from_bytes(bytes.fromhex(address[0]), "little"),
                    None,
                )
                for name, address in zip(
                    entity_updates_lines[len(known_symbols) :],
                    matches[len(known_symbols) :],
                )
            )
            parsed_entity_updates = tuple(
                Symbol(
                    (
                        "EntityDummy"
                        if symbol.address == entity_dummy_address
                        else symbol.name
                    ),
                    symbol.address,
                    None,
                )
                for symbol in parsed_entity_updates
            )
            symbols = tuple(
                symbol
                for symbol in parsed_entity_updates
                if symbol.name.split("_")[-1] != f"{symbol.address:08X}"
            )
        else:
            symbols = tuple()
    # TODO: Why the weird + () ?
    return {
        "address": entity_updates_address,
        "first_e_init": first_e_init,
        "items": parsed_entity_updates,
        "symbols": symbols + (),
    }


def cross_reference_e_init_c(
    check_entity_updates, check_e_inits, ref_e_init_path, ovl_name, map_path
):
    if ref_e_init_path.is_file():
        symbols = []
        file_text = ref_e_init_path.read_text()
        e_init_pattern = re.compile(
            r"""
        \nEInit\s+(?P<name>(?:OVL_EXPORT\()?\w+\)?)\s*=\s*\{(?:\s*|\n?)
        (?P<animSet>(?:ANIMSET_(?:OVL|DRA)\()?(?:0x)?[0-9A-Fa-f]{1,4}\)?)\s*
        ,\s*(?P<animCurFrame>(?:0x)?[0-9A-Fa-f]{1,4})\s*
        ,\s*(?P<unk5A>(?:0x)?[0-9A-Fa-f]{1,4})\s*
        ,\s*(?P<palette>(?:0x)?[0-9A-Fa-f]{1,4}|PAL_[A-Z0-9_]+)\s*
        ,\s*(?P<enemyID>(?:0x)?[0-9A-Fa-f]{1,4})\};
        """,
            re.VERBOSE,
        )

        if check_entity_updates:
            entity_updates_start = file_text.find("EntityUpdates")
            entity_updates_end = file_text.find("};", entity_updates_start)
            ref_entity_updates = [
                item.strip().replace("OVL_EXPORT(", f"{ovl_name.upper()}_").rstrip(",)")
                for item in file_text[
                    entity_updates_start:entity_updates_end
                ].splitlines()[1:]
                if item
            ]
            if len(check_entity_updates) == len(ref_entity_updates):
                symbols.extend(
                    Symbol(to_name, from_symbol.address, None)
                    for from_symbol, to_name in zip(
                        check_entity_updates, ref_entity_updates
                    )
                )

        if check_e_inits:
            ref_e_inits = []
            e_init_idx = file_text.find("EInit")
            while e_init_idx != -1:
                if e_init := e_init_pattern.match(file_text[e_init_idx - 1 :]):
                    name = (
                        e_init.group("name")
                        .replace("OVL_EXPORT(", f"{ovl_name.upper()}_")
                        .rstrip(")")
                    )
                    animSet = e_init.group("animSet")
                    animCurFrame = e_init.group("animCurFrame")
                    animCurFrame = int(animCurFrame, 16 if "0x" in animCurFrame else 10)
                    unk5A = e_init.group("unk5A")
                    unk5A = int(unk5A, 16 if "0x" in unk5A else 10)
                    palette = e_init.group("palette")
                    palette = (
                        palette
                        if "PAL_" in palette
                        else int(palette, 16) if "0x" in palette else int(palette)
                    )
                    enemyID = e_init.group("enemyID")
                    ref_e_inits.append(
                        (name, animSet, animCurFrame, unk5A, palette, enemyID)
                    )
                e_init_idx = file_text.find("EInit", e_init_idx + 1)

            not_matched = 0
            for i, ref_e_init in enumerate(ref_e_inits):
                if i - not_matched < len(check_e_inits):
                    if ref_e_init[1:] != check_e_inits[i - not_matched][1:]:
                        not_matched += 1
                    else:
                        symbols.append(
                            Symbol(
                                ref_e_init[0],
                                sotn_utils.get_symbol_address(
                                    map_path, check_e_inits[i - not_matched][0]
                                ),
                                None,
                            )
                        )

        return symbols, len(ref_e_inits) == len(check_e_inits) + not_matched
    return [], False


def parse_e_inits(data_file_text, first_e_init, ovl_name, platform, config_yaml_dir):
    e_init_pattern = re.compile(
        r"""
    glabel\s+(?P<name>\w+)\n
    \s+/\*\s+(?P<offset>[0-9A-Fa-f]+)\s+(?P<address>[0-9A-Fa-f]{8})\s+[0-9A-Fa-f]{8}\s+\*/\s+\.word\s+0x(?P<animCurFrame>[0-9A-Fa-f]{4})(?P<animSet>[0-9A-Fa-f]{4})\n
    \s+/\*\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]{8}\s+[0-9A-Fa-f]{8}\s+\*/\s+\.word\s+0x(?P<palette>[0-9A-Fa-f]{4})(?P<unk5A>[0-9A-Fa-f]{4})\n
    \s+/\*\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]{8}\s+[0-9A-Fa-f]{8}\s+\*/\s+\.word\s+0x0000(?P<enemyID>[0-9A-Fa-f]{4})\n
    """
        + (
            r"""
    \s+/\*\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]{8}\s+00000000\s+\*/\s+\.word\s+0x00000000\n
    """
            if platform == "psp"
            else ""
        )
        + r"""
    (?P<size>\.size\s+(?P=name),\s+\.\s+-\s+(?P=name)\n?)?
    """,
        re.VERBOSE,
    )
    unused_e_init_pattern = r"""
    \s+/\*\s+(?P<offset>[0-9A-Fa-f]+)\s+(?P<address>[0-9A-Fa-f]{8})\s+[0-9A-Fa-f]{8}\s+\*/\s+\.word\s+0x(?P<animCurFrame>[0-9A-Fa-f]{4})(?P<animSet>[0-9A-Fa-f]{4})\n
    \s+/\*\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]{8}\s+[0-9A-Fa-f]{8}\s+\*/\s+\.word\s+0x(?P<palette>[0-9A-Fa-f]{4})(?P<unk5A>[0-9A-Fa-f]{4})\n
    \s+/\*\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]{8}\s+[0-9A-Fa-f]{8}\s+\*/\s+\.word\s+0x0000(?P<enemyID>[0-9A-Fa-f]{4})\n
    """
    # when e_init[3] is referenced in code
    split_e_init_pattern = re.compile(
        r"""
    glabel\s+(?P<name>\w+)\n
    \s+/\*\s+(?P<offset>[0-9A-Fa-f]+)\s+(?P<address>[0-9A-Fa-f]{8})\s+(?P<raw_val>[0-9A-Fa-f]{8})\s+\*/\s+\.word\s+0x(?P<animCurFrame>[0-9A-Fa-f]{4})(?P<animSet>[0-9A-Fa-f]{4})\n
    \s+/\*\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]{8}\s+\*/\s+\.short\s+0x(?P<unk5A>[0-9A-Fa-f]{4})\n
    \.size\s+(?P=name),\s+\.\s+-\s+(?P=name)\n
    \n
    glabel\s+(?P<pal_sym>\w+)\n
    \s+/\*\s+(?P<pal_offset>[0-9A-Fa-f]+)\s+(?P<pal_address>[0-9A-Fa-f]{8})\s+\*/\s+\.short\s+0x(?P<palette>[0-9A-Fa-f]{4})\n
    \s+/\*\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]{8}\s+[0-9A-Fa-f]{8}\s+\*/\s+\.word\s+0x0000(?P<enemyID>[0-9A-Fa-f]{4})\n
    """
        + (
            r"""
    \s+/\*\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]{8}\s+00000000\s+\*/\s+\.word\s+0x00000000\n
    """
            if platform == "psp"
            else ""
        )
        + r"""
    (?P<size>\.size\s+(?P=pal_sym),\s+\.\s+-\s+(?P=pal_sym)\n?)
    """,
        re.VERBOSE,
    )
    if platform == "psx":
        # when e_init[3] and e_init[5] are referenced in code in us
        short_e_init_pattern = re.compile(
            r"""
        glabel\s+(?P<name>\w+)\n
        \s+/\*\s+(?P<offset>[0-9A-Fa-f]+)\s+(?P<address>[0-9A-Fa-f]{8})\s+[0-9A-Fa-f]{8}\s+\*/\s+\.word\s+0x(?P<animCurFrame>[0-9A-Fa-f]{4})(?P<animSet>[0-9A-Fa-f]{4})\n
        \s+/\*\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]{8}\s+\*/\s+\.short\s+0x(?P<unk5A>[0-9A-Fa-f]{4})\n
        \.size\s+(?P=name),\s+\.\s+-\s+(?P=name)\n
        \n
        glabel\s+(?P<pal_sym>\w+)\n
        \s+/\*\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]{8}\s+\*/\s+\.short\s+0x(?P<palette>[0-9A-Fa-f]{4})\n
        \s+/\*\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]{8}\s+\*/\s+\.short\s+0x(?P<enemyID>[0-9A-Fa-f]{4})\n
        \.size\s+(?P=pal_sym),\s+\.\s+-\s+(?P=pal_sym)\n
        \n
        glabel\s+(?P<unk_sym>\w+)\n
        \s+/\*\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]{8}\s+\*/\s+\.short\s+0x0000\n
        (?P<size>\.size\s+(?P=unk_sym),\s+\.\s+-\s+(?P=unk_sym)\n?)
        """,
            re.VERBOSE,
        )
    if platform == "psp":
        short_e_init_pattern = re.compile(
            r"""
        glabel\s+(?P<name>\w+)\n
        \s+/\*\s+(?P<offset>[0-9A-Fa-f]+)\s+(?P<address>[0-9A-Fa-f]{8})\s+\*/\s+\.short\s+0x(?P<animSet>[0-9A-Fa-f]{4})\n
        \s+/\*\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]{8}\s+\*/\s+\.short\s+0x(?P<animCurFrame>[0-9A-Fa-f]{4})\n
        \s+/\*\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]{8}\s+\*/\s+\.short\s+0x(?P<unk5A>[0-9A-Fa-f]{4})\n
        \s+/\*\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]{8}\s+\*/\s+\.short\s+0x(?P<palette>[0-9A-Fa-f]{4})\n
        \s+/\*\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]{8}\s+\*/\s+\.short\s+0x(?P<enemyID>[0-9A-Fa-f]{4})\n
        \s+/\*\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]{8}\s+\*/\s+\.short\s+0x0000\n
        \s+/\*\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]{8}\s+\*/\s+\.short\s+0x0000\n
        \s+/\*\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]{8}\s+\*/\s+\.short\s+0x0000\n
        (?P<size>\.size\s+(?P=name),\s+\.\s+-\s+(?P=name)\n?)
        """,
            re.VERBOSE,
        )

    known_e_inits = [
        f"{ovl_name.upper()}_EInitBreakable",
        "g_EInitObtainable",
        "g_EInitParticle",
        "g_EInitSpawner",
        "g_EInitInteractable",
        "g_EInitUnkId13",
        "g_EInitLockCamera",
        "g_EInitCommon",
        "g_EInitDamageNum",
    ]

    text = data_file_text[data_file_text.find(f"glabel {first_e_init}") :]
    parsed_e_inits = []
    while not parsed_e_inits or matches:
        matches = (
            re.match(e_init_pattern, text)
            or re.match(split_e_init_pattern, text)
            or re.match(short_e_init_pattern, text)
        )
        if platform != "psp" and matches and not matches.groupdict().get("size"):
            size_name = matches.groupdict().get("name")
            while not matches.groupdict().get("size"):
                address = int(matches.group("address"), 16)
                name = matches.groupdict().get("name") or f"g_EInitUnused{address:08X}"
                animSet = int(matches.group("animSet"), 16)
                parsed_e_inits.append(
                    (
                        Symbol(name, address, None),
                        f"ANIMSET_{'OVL' if animSet & 0x8000 else 'DRA'}({animSet & ~0x8000})",
                        int(matches.group("animCurFrame"), 16),
                        int(matches.group("unk5A"), 16),
                        int(matches.group("palette"), 16),
                        int(matches.group("enemyID"), 16),
                    )
                )
                if matches.groupdict().get("size"):
                    break
                text = text[matches.end() :]
                unused_last_line_pattern = (
                    rf"(?P<size>\.size\s+{size_name},\s+\.\s+-\s+{size_name}\n?)?"
                )
                matches = re.match(
                    unused_e_init_pattern + unused_last_line_pattern, text, re.VERBOSE
                )

        if matches:
            address = int(matches.group("address"), 16)
            name = matches.groupdict().get("name") or f"g_EInitUnused{address:08X}"
            animSet = int(matches.group("animSet"), 16)
            parsed_e_inits.append(
                (
                    Symbol(name, address, None),
                    f"ANIMSET_{'OVL' if animSet & 0x8000 else 'DRA'}({animSet & ~0x8000})",
                    int(matches.group("animCurFrame"), 16),
                    int(matches.group("unk5A"), 16),
                    int(matches.group("palette"), 16),
                    int(matches.group("enemyID"), 16),
                )
            )
            text = text[matches.end() + 1 :]

    enemy_defs = {
        v: k
        for k, v in sotn_utils.yaml.safe_load(
            (Path(config_yaml_dir) / "enemy_defs.yaml").read_text()
        ).items()
    }

    symbols = [
        Symbol(name, e_init[0].address, None)
        for name, e_init in zip(known_e_inits, parsed_e_inits)
        if platform != "psp"
    ]
    added_names = []
    for e_init in parsed_e_inits[len(symbols) :]:
        if e_init[5] in enemy_defs:
            name = f"g_EInit{enemy_defs[e_init[5]]}"
            if name in added_names:
                symbols.append(
                    Symbol(f"{name}{e_init[0].address:X}", e_init[0].address, None)
                )
            else:
                symbols.append(Symbol(name, e_init[0].address, None))
            added_names.append(name)
        else:
            symbols.append(Symbol(e_init[0].name, e_init[0].address, None))

    e_inits = [
        (
            symbol.name if platform != "psp" else e_init[0].name,
            e_init[1],
            e_init[2],
            e_init[3],
            e_init[4],
            f"0x{e_init[5]:03X}",
        )
        for symbol, e_init in zip(symbols, parsed_e_inits)
    ]
    next_offset = re.match(r"glabel\s+\w+\n\s+/\*\s+(?P<offset>[0-9A-Fa-f]+)\s+", text)
    return (
        e_inits,
        int(next_offset.group("offset"), 16) if next_offset else None,
        [x for x in symbols if not x.name.startswith("D_")],
    )


def add_initial_symbols(
    ovl_config,
    config_yaml_dir,
    e_init_c_path,
    ovl_header_symbol,
    parsed_symbols=[],
    entity_updates={},
    spinner=SimpleNamespace(message=""),
):
    subsegments = ovl_config.subsegments.copy()

    ### group change ###
    spinner.message = f"finding the first data file"
    first_data_offset = next(subseg[0] for subseg in subsegments if "data" in subseg)
    first_data_path = ovl_config.asm_path / "data" / f"{first_data_offset:X}.data.s"
    if first_data_path.exists():
        first_data_text = first_data_path.read_text()
        ### group change ###
        spinner.message = f"parsing the overlay header for symbols"
        ovl_header, pStObjLayoutHorizontal_address = parse_ovl_header(
            first_data_text,
            ovl_config.name,
            ovl_config.platform,
            ovl_header_symbol,
        )
        # TODO: Add data segments for follow-on header symbols
        if ovl_config.platform == "psx":
            ### group change ###
            spinner.message = f"finding the entity table"
            entity_updates = find_psx_entity_updates(
                first_data_text, pStObjLayoutHorizontal_address
            )
    else:
        first_data_text = None
        ovl_header, pStObjLayoutHorizontal_address = {}, None
        entity_updates = {}

    ### group change ###
    spinner.message = "gathering initial symbols"
    if entity_updates and first_data_text:
        ### group change ###
        spinner.message = "parsing EntityUpdates"
        entity_updates.update(
            parse_entity_updates(
                first_data_text, ovl_config.name, entity_updates.get("name")
            )
        )
        ### group change ###
        spinner.message = "parsing EInits"
        e_inits, next_offset, symbols = parse_e_inits(
            first_data_text,
            entity_updates.get("first_e_init"),
            ovl_config.name,
            ovl_config.platform,
            config_yaml_dir,
        )
        parsed_symbols.extend(symbols)

        ### group change ###
        if ovl_config.version == "us":
            e_init_success = True
        else:
            spinner.message = "cross-referencing e_init.c"
            e_init_symbols, e_init_success = cross_reference_e_init_c(
                entity_updates.get("items"),
                e_inits,
                e_init_c_path,
                ovl_config.name,
                ovl_config.ld_script_path.with_suffix(".map"),
            )
            parsed_symbols.extend(e_init_symbols)

        entity_updates_offset = (
            entity_updates.get("address", 0) - ovl_config.vram + ovl_config.start
        )
        if entity_updates_offset > 0:
            e_init_subseg = [
                entity_updates_offset,
                f"{'.' if e_init_success else ''}data",
                (
                    f"{ovl_config.name}/e_init"
                    if ovl_config.platform == "psp"
                    else "e_init"
                ),
                next_offset - entity_updates_offset,
            ]
            subsegments.append(e_init_subseg)

    if ovl_header.get("symbols") or entity_updates.get("symbols"):
        parsed_symbols.extend(
            (
                symbol
                for symbols in (
                    ovl_header.get("symbols"),
                    entity_updates.get("symbols"),
                )
                if symbols is not None
                for symbol in symbols
            )
        )
    if entity_updates.get("address"):
        parsed_symbols.append(
            Symbol(
                f"{ovl_config.name.upper()}_EntityUpdates",
                entity_updates.get("address"),
                None,
            )
        )
    if ovl_header.get("address"):
        parsed_symbols.append(
            Symbol(
                f"{ovl_config.name.upper()}_Overlay", ovl_header.get("address"), None
            )
        )

    return subsegments, parsed_symbols, ovl_header, entity_updates, e_inits


def validate_binary(
    basename,
    asm_path,
    ld_script_path,
    build_path,
    target_path,
    version,
    sha1,
    built_bin_path,
):
    logger = sotn_utils.get_logger()
    # TODO: Compare generated offsets to .elf segment offsets
    run(["git", "clean", "-fdx", asm_path], capture_output=True)
    ld_script_path.unlink(missing_ok=True)
    build(
        [
            f"{build_path}/config/splat.{version}.{basename}.yaml.dyn_syms",
            f"{ld_script_path}",
            f"{ld_script_path.with_suffix('.elf')}",
            f"{build_path}/{target_path.name}",
        ],
        version=version,
    )
    if built_bin_path.exists():
        built_sha1 = hashlib.sha1(built_bin_path.read_bytes()).hexdigest()
    else:
        logger.error(f"{built_bin_path} did not build properly")
        raise SystemExit

    if built_sha1 != sha1:
        logger.error(f"{built_bin_path} did not match {target_path}")
        raise SystemExit


def can_extract(overlay):
    stage = "are cat cen chi dai dre lib no0 no1 no2 no3 no4 np3 nz0 nz1 st0 top wrp "
    rstage = (
        "rare rcat rcen rchi rdai rlib rno0 rno1 rno2 rno3 rno4 rnz0 rnz1 rtop rwrp "
    )
    boss = "bo0 bo1 bo2 bo3 bo4 bo5 bo6 bo7 mar rbo0 rbo1 rbo2 rbo3 rbo4 rbo5 rbo6 rbo7 rbo8 "
    return overlay in (stage + rstage + boss).split(" ")


def clean_artifacts(ovl_config, full_clean=False, spinner=SimpleNamespace(message="")):
    if (asm_path := Path(f"asm/{ovl_config.version}")).exists():
        spinner.message = run(["git", "clean", "-fdx", asm_path], capture_output=True)

    spinner.message = f"Removing {ovl_config.ld_script_path}"
    ovl_config.ld_script_path.unlink(missing_ok=True)

    spinner.message = f"Removing {ovl_config.ld_script_path.with_suffix(".elf")}"
    ovl_config.ld_script_path.with_suffix(".elf").unlink(missing_ok=True)

    spinner.message = f"Removing {ovl_config.ld_script_path.with_suffix(".map")}"
    ovl_config.ld_script_path.with_suffix(".map").unlink(missing_ok=True)

    spinner.message = (
        f"Removing {ovl_config.build_path.joinpath(f"{ovl_config.target_path.name}")}"
    )
    ovl_config.build_path.joinpath(f"{ovl_config.target_path.name}").unlink(
        missing_ok=True
    )

    if full_clean:
        if (
            build_src_path := ovl_config.build_path / ovl_config.src_path_full
        ).exists():
            spinner.message = run(
                ["git", "clean", "-fdx", build_src_path], capture_output=True
            )

        spinner.message = f"Removing config/check.{ovl_config.version}.sha"
        sha_check_path = Path(f"config/check.{ovl_config.version}.sha")
        sha_check_lines = (
            line
            for line in sha_check_path.read_text().splitlines()
            if ovl_config.sha1 not in line
        )
        fbin_path = ovl_config.target_path.with_name(
            f"{"f" if ovl_config.platform == "psp" else "F"}_{ovl_config.target_path.name}"
        )
        if fbin_path.exists():
            fbin_sha1 = hashlib.sha1(fbin_path.read_bytes()).hexdigest()
            sha_check_lines = (
                line for line in sha_check_lines if fbin_sha1 not in line
            )
        sha_check_path.write_text("\n".join(sha_check_lines) + "\n")

        spinner.message = f"Removing {ovl_config.ovl_symbol_addrs_path}"
        ovl_config.ovl_symbol_addrs_path.unlink(missing_ok=True)

        if ovl_config.symexport_path:
            spinner.message = f"Removing {ovl_config.symexport_path}"
            ovl_config.symexport_path.unlink(missing_ok=True)

        if ovl_config.version != "hd" and ovl_config.src_path_full.exists():
            spinner.message = f"Removing {ovl_config.src_path_full}"
            shutil.rmtree(ovl_config.src_path_full)

        spinner.message = f"Removing {ovl_config.config_path}"
        ovl_config.config_path.unlink(missing_ok=True)

    spinner.message = f"cleaned {ovl_config.version} overlay {ovl_config.name.upper()} artifacts and configuration"


def remove_overlay(overlay, versions):
    logger = sotn_utils.get_logger()
    with sotn_utils.Spinner(message=f"starting overlay removal") as spinner:
        for version in versions:
            logger.info(
                f"Removing {version} overlay {overlay.upper()} artifacts and configuration"
            )
            spinner.message = f"removing {version} overlay {overlay.upper()} artifacts and configuration"
            ovl_config = sotn_utils.SotnOverlayConfig(overlay, version)
            clean_artifacts(ovl_config, True, spinner)


def extract(args, version):
    logger = sotn_utils.get_logger()
    start_time = time.perf_counter()
    logger.info(
        f"Starting config generation for {version} overlay {args.overlay.upper()}"
    )
    with sotn_utils.Spinner(
        message=f"generating config for {version} overlay {args.overlay.upper()}"
    ) as spinner:
        ovl_config = sotn_utils.SotnOverlayConfig(args.overlay, version)
        if ovl_config.config_path.exists() and not args.clean:
            logger.error(
                f"Configuration {ovl_config.name} already exists.  Use the --clean option to remove all existing overlay artifacts and re-extract the overlay."
            )
            raise SystemExit

        clean_artifacts(ovl_config, args.clean, spinner)
        ovl_load_symbol, ovl_header_symbol, entity_updates = create_initial_files(
            ovl_config, spinner
        )

    with sotn_utils.Spinner(message="gathering initial symbols") as spinner:
        e_init_c_path = ovl_config.src_path_full.with_name(ovl_config.name) / "e_init.c"
        ovl_config.subsegments, parsed_symbols, ovl_header, entity_updates, e_inits = (
            add_initial_symbols(
                ovl_config,
                args.config_dir,
                e_init_c_path,
                ovl_header_symbol,
                [ovl_load_symbol] if ovl_load_symbol else [],
                entity_updates,
                spinner,
            )
        )
        if ovl_header.get("items"):
            spinner.message = f"creating {ovl_config.name}/header.c"
            create_header_c(
                ovl_header.get("items"),
                ovl_config.name,
                ovl_config.ovl_type,
                ovl_config.version,
                ovl_config.src_path_full.parent / ovl_config.name / "header.c",
            )
            spinner.message = f"adding header subsegment"
            header_offset = ovl_header["address"] - ovl_config.vram + ovl_config.start
            header_subseg = [
                header_offset,
                ".data",
                (
                    f"{ovl_config.name}/header"
                    if ovl_config.platform == "psp"
                    else "header"
                ),
                ovl_header.get("size_bytes", 0),
            ]
            ovl_config.subsegments.append(header_subseg)

        if ovl_config.version == "us":
            spinner.message = "creating e_init.c"
            e_init_success = create_e_init_c(
                entity_updates.get("items"), e_inits, ovl_config.name, e_init_c_path
            )
        if parsed_symbols:
            spinner.message = (
                f"adding {len(parsed_symbols)} parsed symbols and splitting again"
            )
            sotn_utils.add_symbols(
                ovl_config.ovl_symbol_addrs_path,
                parsed_symbols,
                ovl_config.name,
                ovl_config.vram,
                ovl_config.symbol_name_format.replace("$VRAM", ""),
                ovl_config.src_path_full,
                ovl_config.symexport_path,
            )
            sotn_utils.shell(f"git clean -fdx {ovl_config.asm_path}")
            sotn_utils.splat_split(ovl_config.config_path)
        ovl_include_path = (
            ovl_config.src_path_full.parent / ovl_config.name / f"{ovl_config.name}.h"
        )
        ovl_include_path = (
            ovl_config.src_path_full.parent / ovl_config.name / f"{ovl_config.name}.h"
        )
        create_ovl_include(
            entity_updates.get("items"),
            ovl_config.name,
            ovl_config.ovl_type,
            ovl_include_path,
        )

    with sotn_utils.Spinner(message="gathering reference overlays") as spinner:
        ref_ovls = build_reference_asm(
            ovl_config.name, ovl_config.version, ovl_config.build_path, spinner
        )
        if ref_ovls:
            spinner.message = f"finding files to compare"
            check_files, ref_files = find_files_to_compare(
                ref_ovls, ovl_config.name, ovl_config.version
            )
            spinner.message = f"parsing instructions from {len(check_files)} new files and {len(ref_files)} reference files"
            parsed_check_files = sotn_utils.parse_asm_files(check_files)
            parsed_ref_files = sotn_utils.parse_asm_files(ref_files)
        else:
            parsed_check_files, parsed_ref_files = None, None
            spinner.message = f"found no reference overlays"

        if parsed_check_files and parsed_ref_files:
            spinner.message = "searching for similar functions"
            known_pairs = get_known_pairs(ovl_config.name, ovl_config.version)
            ambiguous_renames, unhandled_renames = sotn_utils.rename_similar_functions(
                ovl_config, parsed_check_files, parsed_ref_files, known_pairs, spinner
            )
            spinner.message += (
                f" (compared {len(check_files)} new to {len(ref_files)} reference)"
            )
        else:
            ambiguous_renames, unhandled_renames = [], []

    with sotn_utils.Spinner(
        message="parsing symbols from InitRoomEntities.s"
    ) as spinner:
        nonmatchings_path = (
            f"{ovl_config.nonmatchings_path}/{ovl_config.name}_psp"
            if ovl_config.platform == "psp"
            else ovl_config.nonmatchings_path
        )

        init_room_entities_path = (
            ovl_config.asm_path
            / nonmatchings_path
            / f"first_{ovl_config.name}"
            / f"InitRoomEntities.s"
        )

        if init_room_entities_path.exists():
            init_room_entities_symbols, create_entity_bss_start = (
                parse_init_room_entities(
                    ovl_config.name,
                    ovl_config.platform,
                    init_room_entities_path,
                    ovl_config.vram + ovl_config.start,
                )
            )

            create_entity_bss_end = create_entity_bss_start + (
                0x18 if ovl_config.platform == "psp" else 0x10
            )

        spinner.message = "parsing renamed functions for cross referencing"
        parsed_check_files = sotn_utils.parse_asm_files(
            dirpath / f
            for dirpath, _, filenames in ovl_config.asm_path.walk()
            for f in filenames
            if (
                f.startswith(f"func_{ovl_config.version}_")
                and f.split("_")[-2] == "from"
            )
            or (
                not f.startswith(f"func_{ovl_config.version}_")
                and not f.startswith("D_")
            )
        )

        spinner.message = f"cross referencing {len(parsed_check_files)} renamed functions against {len({x.path.name for x in parsed_ref_files})} existing functions"
        cross_ref_symbols = sotn_utils.cross_reference_asm(
            parsed_check_files, parsed_ref_files, ovl_config.name, ovl_config.version
        )
        if init_room_entities_symbols or cross_ref_symbols:
            spinner.message = f"adding {len(init_room_entities_symbols)} parsed symbols and {len(cross_ref_symbols)} cross referenced symbols and splitting again"
            sotn_utils.add_symbols(
                ovl_config.ovl_symbol_addrs_path,
                init_room_entities_symbols | cross_ref_symbols,
                ovl_config.name,
                ovl_config.vram,
                ovl_config.symbol_name_format.replace("$VRAM", ""),
                ovl_config.src_path_full,
                ovl_config.symexport_path,
            )
            run(["git", "clean", "-fdx", ovl_config.asm_path], capture_output=True)
            sotn_utils.splat_split(ovl_config.config_path, ovl_config.disassemble_all)

    with sotn_utils.Spinner(
        message=f"creating {ovl_config.ld_script_path.with_suffix(".elf")}"
    ) as spinner:
        build(
            [f'{ovl_config.ld_script_path.with_suffix(".elf")}'],
            version=ovl_config.version,
        )
        spinner.message = f"finding segments and splitting source files"
        include_path = f"../{ovl_config.name}/" if ovl_config.platform == "psp" else ""
        file_header = f'// SPDX-License-Identifier: AGPL-3.0-or-later\n#include "{include_path}{ovl_config.name}.h"\n\n'

        known_segments = get_known_segments(
            ovl_config.name, Path(args.config_dir) / "segments.yaml"
        )
        ovl_config.subsegments = sotn_utils.find_segments(
            ovl_config, file_header, known_segments
        )
        ovl_config.write_config()

        built_bin_path = ovl_config.build_path / ovl_config.target_path.name
        spinner.message = f"building and validating {built_bin_path}"
        validate_binary(
            ovl_config.basename,
            ovl_config.asm_path,
            ovl_config.ld_script_path,
            ovl_config.build_path,
            ovl_config.target_path,
            version,
            ovl_config.sha1,
            built_bin_path,
        )

    with sotn_utils.Spinner(message=f"cleaning up {ovl_config.name}.h") as spinner:
        # just in case any function got renamed after the files were created
        ovl_header_text = ovl_include_path.read_text()
        ovl_header_text = re.sub(
            rf"{ovl_config.name.upper()}_(\w\w+)\b", r"OVL_EXPORT(\1)", ovl_header_text
        )
        entity_enum_pattern = re.compile(
            r"\s+(?P<e_id>E_[A-Z0-9_]+),\s+//\s+(?:OVL_EXPORT\()?(?P<func>Entity\w+)\)?\b"
        )
        camel_case_pattern = re.compile(r"([A-Za-z])([A-Z][a-z])")
        ovl_header_lines = [
            (
                line.replace(
                    m.group("e_id"),
                    f"{camel_case_pattern.sub(r"\1_\2", m.group("func"))}".upper().replace(
                        "ENTITY", "E"
                    ),
                )
                if (m := entity_enum_pattern.match(line)) and "DUMMY" not in line
                else line
            )
            for line in ovl_header_text.splitlines()
        ]
        e_id_max_length = max(
            [
                len(line.split()[0])
                for line in ovl_header_lines
                if "    E_" in line and "//" in line
            ]
            or [""]
        )
        ovl_header_lines = [
            (
                f"    {line.split()[0]:<{e_id_max_length}} {' '.join(line.split()[1:])}"
                if "    E_" in line and "//" in line
                else line
            )
            for line in ovl_header_lines
        ]
        ovl_include_path.write_text("\n".join(ovl_header_lines) + "\n")

        spinner.message = "cleaning up e_init.c"
        e_init_c_path.write_text(
            re.sub(
                rf"{ovl_config.name.upper()}_(\w+)\b",
                r"OVL_EXPORT(\1)",
                e_init_c_path.read_text(),
            )
        )

        spinner.message = "getting suggested segments"
        suggested_segments = sotn_utils.get_suggested_segments(ovl_config.config_path)

    time_text = sotn_utils.get_run_time(start_time)
    print(f"{sotn_utils.TTY.OK} Extracted {version} {args.overlay} ({time_text})")
    if suggested_segments:
        print(
            f"{sotn_utils.TTY.INFO_CIRCLE} {len(suggested_segments)} additional segments were suggested by Splat:"
        )
        for segment in suggested_segments:
            print(f"    - [{segment[0]}, {segment[1]}, {segment[2]}]")
        logger.info(f"Additional segments suggested by splat: {suggested_segments}")
    if ambiguous_renames:
        print(
            f"{sotn_utils.TTY.WARNING} Found {len(ambiguous_renames)} functions renamed with ambiguous matches:"
        )
        from_width = max(len(x.old_names[0]) for x in ambiguous_renames) + 1
        to_width = max(len(x.new_names[0]) for x in ambiguous_renames) + 1
        print(
            f"  {'from':<{from_width}}{sotn_utils.TTY.BOLD}|{sotn_utils.TTY.RESET} {'to':<{to_width}}{sotn_utils.TTY.BOLD}|{sotn_utils.TTY.RESET} score {sotn_utils.TTY.BOLD}|{sotn_utils.TTY.RESET} other matches"
        )
        for rename in ambiguous_renames:
            print(
                f"  {rename.old_names[0]:<{from_width}}{sotn_utils.TTY.BOLD}|{sotn_utils.TTY.RESET} {rename.new_names[0]:<{to_width}}{sotn_utils.TTY.BOLD}|{sotn_utils.TTY.RESET} {round(rename.score, 2):<6}{sotn_utils.TTY.BOLD}|{sotn_utils.TTY.RESET} {', '.join(rename.all_matches[1:])}"
            )
    if unhandled_renames:
        print(
            f"{sotn_utils.TTY.WARNING} Encountered {len(unhandled_renames)} unhandled matches:"
        )
        from_width = max(len(", ".join(x.old_names)) for x in unhandled_renames) + 1
        to_width = max(len(", ".join(x.new_names)) for x in unhandled_renames) + 1
        print(
            f"  {'functions':<{from_width}}{sotn_utils.TTY.BOLD}|{sotn_utils.TTY.RESET} {'matches':<{to_width}}{sotn_utils.TTY.BOLD}|{sotn_utils.TTY.RESET} score"
        )
        for rename in unhandled_renames:
            print(
                f"  {', '.join(rename.old_names):<{from_width}}{sotn_utils.TTY.BOLD}|{sotn_utils.TTY.RESET} {', '.join(rename.new_names):{to_width}}{sotn_utils.TTY.BOLD}|{sotn_utils.TTY.RESET} {rename.score}"
            )

    # make clean removes new files in the config/ directory, so these need to be staged
    precious_files = [
        f"{ovl_config.config_path}",
        f"config/undefined_syms.{version}.txt",
        f"config/check.{version}.sha",
    ]
    if isinstance(ovl_config.symbol_addrs_path, (list, tuple)):
        precious_files.extend(f"{x}" for x in ovl_config.symbol_addrs_path)
    else:
        precious_files.append(f"{ovl_config.symbol_addrs_path}")
    if ovl_config.platform == "psp":
        precious_files.append(f"{ovl_config.symexport_path}")
    run(["git", "add"] + precious_files, capture_output=True)

    # clean up certain files so the next build uses current symbols
    ovl_config.ld_script_path.unlink(missing_ok=True)
    ovl_config.ld_script_path.with_suffix(".map").unlink(missing_ok=True)
    ovl_config.ld_script_path.with_suffix(".elf").unlink(missing_ok=True)

    if args.make_expected:
        print(f"VERSION={ovl_config.version} make expected")
        env = os.environ.copy()
        env["VERSION"] = ovl_config.version
        run(["make", "expected"], env=env, text=True)


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
        "-c",
        "--config-dir",
        required=False,
        default=f"{Path(__file__).parent}",
        help=f"Specify a path to yaml config files (default is '{Path(__file__).parent.relative_to(Path.cwd())}')",
    )
    parser.add_argument(
        "-t",
        "--templates",
        required=False,
        default=f"{Path(__file__).parent}",
        help=f"Specify a directory where mako templates can be found (default is '{Path(__file__).parent.relative_to(Path.cwd())}')",
    )
    parser.add_argument(
        "-l",
        "--log",
        required=False,
        default=f"{Path(__file__).parent / 'extract_overlay_log.json'}",
        help=f"Specify a path for the log file (default is '{Path(__file__).parent.relative_to(Path.cwd()) / 'extract_overlay_log.json'}')",
    )
    parser.add_argument(
        "-e",
        "--make-expected",
        required=False,
        action="store_true",
        help="Run 'make expected' after successful extraction",
    )
    parser.add_argument(
        "--clean",
        required=False,
        action="store_true",
        help="DESTRUCTIVE: Remove any existing overlay artifacts before re-extracting the overlay from the source binary",
    )
    parser.add_argument(
        "--remove",
        required=False,
        action="store_true",
        help="DESTRUCTIVE: Remove any existing overlay artifacts without re-extracting the overlay",
    )

    args = parser.parse_args()
    sotn_utils.init_logger(filename=args.log)

    if not args.version:
        args.version.append(os.getenv("VERSION"))
    else:
        # split, flatten, and dedup version args
        split_versions = [
            val.split(",") if "," in val else [val] for val in args.version
        ]
        args.version = {
            version.strip() for versions in split_versions for version in versions
        }

    if args.version and None not in args.version:
        unsupported_versions = [
            ver for ver in args.version if ver not in ["us", "pspeu", "hd", "all"]
        ]
        if unsupported_versions:
            parser.error(
                f"argument -v/--version: invalid choice(s): {unsupported_versions} (choose from 'us', 'pspeu', 'hd', 'all')"
            )
    else:
        parser.error(
            f"the following arguments are required: -v/--version (can be via VERSION env or cli)"
        )

    if "all" in args.version:
        args.version = ["us", "pspeu", "hd"]

    if args.remove:
        remove_overlay(args.overlay, args.version)
    else:
        # always build us first
        if "us" in args.version:
            # rchi has data values that get interpreted as global symbols, so those symbols need to be defined for the linker
            if args.overlay == "rchi":
                add_undefined_symbol("us", "PadRead", 0x80015288)
            extract(args, "us")
        if "pspeu" in args.version:
            #  bo4 and rbo5 have data values that get interpreted as global symbols, so those symbols need to be defined for the linker
            if args.overlay == "bo4" or args.overlay == "rbo5":
                add_undefined_symbol("pspeu", "g_Clut", 0x091F5DF8)
            extract(args, "pspeu")
        if "hd" in args.version:
            extract(args, "hd")
