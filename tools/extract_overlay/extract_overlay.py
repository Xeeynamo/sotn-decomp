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
from mako.template import Template

sys.path.insert(0, str(Path(__file__).parent.parent))
import sotn_utils
from symbols import sort, extract_dynamic_symbols, Symbol

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
        for i, func in enumerate([symbol.name for symbol in entity_updates]):
            if func == "EntityDummy":
                entity_funcs.append((func, f"E_DUMMY_{i+1:X}"))
            elif func.startswith("Entity") or func.startswith("OVL_EXPORT(Entity"):
                entity_funcs.append(
                    (
                        func,
                        sotn_utils.RE_PATTERNS.camel_case.sub(
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
    ovl_load_name, ovl_load_symbol, ovl_header_symbol, entity_updates_name = (
        None,
        None,
        None,
        None,
    )
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
            if match := sotn_utils.RE_PATTERNS.psp_ovl_header_entity_table_pattern.search(
                file_text
            ):
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


def get_known_starts(ovl_name, segments_path):
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
            sotn_utils.add_initial_symbols(
                ovl_config,
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
            ambiguous_renames, unhandled_renames = sotn_utils.rename_similar_functions(
                ovl_config, parsed_check_files, parsed_ref_files, spinner
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
                sotn_utils.parse_init_room_entities(
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

        known_starts = get_known_starts(ovl_config.name, Path(args.segments))
        ovl_config.subsegments = sotn_utils.find_segments(
            ovl_config, file_header, known_starts
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
        "-s",
        "--segments",
        required=False,
        default=f"{Path(__file__).parent / 'segments.yaml'}",
        help=f"Specify a path to the segments yaml file (default is '{Path(__file__).parent.relative_to(Path.cwd()) / 'segments.yaml'}')",
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
