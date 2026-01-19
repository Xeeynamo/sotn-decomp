# usage
# python3 ./tools/build/gen.py && ninja
import base64
import pathlib
from dataclasses import dataclass
import ninja_syntax
import os
from pathlib import Path
import sys
import yaml

# global dictionary that collects all source entries
# useful to avoid adding multiple rules for the same output file
entries = dict()
linker_scripts = set()

extra_cpp_defs = ""
sotn_progress_report = os.environ.get("SOTN_PROGRESS_REPORT") == "1"
dummy_object = bytes()
if sotn_progress_report:
    # https://decomp.wiki/en/tools/decomp-dev
    extra_cpp_defs += " -DSKIP_ASM=1"
    dummy_object = base64.b64decode(
        "f0VMRgEBAQAAAAAAAAAAAAEACAABAAAAAAAAAAAAAABYAAAAABAAADQAAAAAACgABgAFAAAuc2hz"
        "dHJ0YWIALnRleHQALmRhdGEALmJzcwAucGRyAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
        "AAAAAAAAAAAAAAAAAAALAAAAAQAAAAYAAAAAAAAANAAAAAAAAAAAAAAAAAAAABAAAAAAAAAAEQAA"
        "AAEAAAADAAAAAAAAADQAAAAAAAAAAAAAAAAAAAAQAAAAAAAAABcAAAAIAAAAAwAAAAAAAAA0AAAA"
        "AAAAAAAAAAAAAAAAEAAAAAAAAAAcAAAAAQAAAAAAAAAAAAAANAAAAAAAAAAAAAAAAAAAAAQAAAAA"
        "AAAAAQAAAAMAAAAAAAAAAAAAADQAAAAhAAAAAAAAAAAAAAABAAAAAAAAAA=="
    )  # minimal stripped object file generated from an empty assembly file


def is_psp(ver: str) -> bool:
    return ver.startswith("psp")


def is_hd(ver: str) -> bool:
    return ver == "hd"


def is_weapon(ovl_name: str) -> bool:
    return ovl_name == "weapon"


def is_servant(ovl_name: str) -> bool:
    return ovl_name.startswith("tt_")


def is_base_ovl(ovl_name: str) -> bool:
    return (
        ovl_name == "main"
        or ovl_name == "dra"
        or ovl_name == "ric"
        or ovl_name == "maria"
        or ovl_name == "sd"
        or ovl_name == "fname"
        or ovl_name == "tek"
    )


def build_path(ver: str, base_path: str) -> str:
    complete_path = os.path.join("build", ver, base_path)
    if sotn_progress_report:
        return os.path.join("expected", "report", complete_path)
    return complete_path


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


def add_s_dummy(nw: ninja_syntax.Writer, ver: str, file_name: str, ld_path: str):
    output = build_path(ver, f"{file_name}.o")
    if output in entries:
        return output
    entries[output] = {}
    output_path = pathlib.Path(output)
    output_path.parent.mkdir(parents=True, exist_ok=True)
    output_path.write_bytes(dummy_object)
    return output


@dataclass
class CompilerParams:
    cc_opt: str = "-O2"
    mwcc_opt: str = "-Op"
    aspsx_ver: str = "2.34"
    encoding: str = "sjis"


def get_compiler_params(source_file_path: str) -> CompilerParams:
    """
    Parses optional compiler overrides from the source file header.

    The function scans the first two lines of the file. If a line starts
    with `//!`, it parses space-separated `KEY=VALUE` pairs to override
    default build settings.

    Supported Flags:
        PSYQ: Overrides the ASPSX assembler version.
        O:    Overrides the PS1 C Compiler optimization level.
        PSPO: Overrides the PSP C Compiler optimization flags.
        ENCODING: Overrides file encoding.

    Example Header:
        //! PSYQ=3.3 O=1 PSPO=4,p
    """
    c = CompilerParams()
    if not os.path.exists(source_file_path):
        return c
    compiler_params = None
    with open(source_file_path, "r") as file:
        for _ in range(2):
            line = file.readline()
            if line.startswith("//!"):
                compiler_params = line
                break
    if not compiler_params:
        return c
    for param in compiler_params[3:].strip().split():
        pair = param.split("=")
        if len(pair) == 2:
            key, value = pair[0].strip(), pair[1].strip()
        elif len(pair) == 1:
            key, value = pair[0].strip(), ""
        else:
            raise ValueError(f"Compiler override parameter '{param}' is not recognized")
        if key == "PSYQ":
            if value == "3.3":
                c.aspsx_ver = "2.21"
            elif value == "3.5":
                c.aspsx_ver = "2.34"
            else:
                raise ValueError(f"PSYQ version '{value}' is not recognized")
        elif key == "O":
            c.cc_opt = f"-O{value}"
        elif key == "PSPO":
            c.mwcc_opt = f"-O{value}"
        elif key == "ENCODING":
            c.encoding = value
        else:
            raise ValueError(f"Compiler override flag '{key}' is not recognized")
    return c


def add_c_psx(
    nw: ninja_syntax.Writer, ver: str, file_name: str, ld_path: str, cpp_flags: str
):
    output = build_path(ver, f"{file_name}.o")
    if output in entries:
        return output
    entries[output] = {}
    c_params = get_compiler_params(file_name)
    nw.build(
        rule="psx-cc",
        outputs=output,
        inputs=file_name,
        implicit=[
            f"src/.assets_build_done_{ver}",
            ld_path,
        ],
        variables={
            "version": ver,
            "cpp_flags": cpp_flags,
            "cc_flags": c_params.cc_opt,
            "aspsx_ver": c_params.aspsx_ver,
        },
    )

    # this file may be generated by a different
    # version of the game, but the content will
    # be identical.
    if file_name in entries:
        return output
    entries[file_name] = {"reason": "generated"}
    nw.build(
        rule="phony",
        outputs=file_name,
        implicit=[f"src/.assets_build_done_{ver}"],
    )

    return output


def add_s_psx(nw: ninja_syntax.Writer, ver: str, file_name: str, ld_path: str):
    output = build_path(ver, f"{file_name}.o")
    if output in entries:
        return output
    entries[output] = {}
    nw.build(
        rule="psx-as",
        outputs=[output],
        inputs=[file_name],
    )
    nw.build(
        rule="phony",
        outputs=[file_name],
        implicit=[ld_path],
    )
    return output


def add_copy_psx(
    nw: ninja_syntax.Writer,
    ver: str,
    in_file_name: str,
    out_file_name: str,
    ld_script_path: str,
):
    output = build_path(ver, f"{out_file_name}.o")
    if output in entries:
        return output
    entries[output] = {}
    nw.build(
        rule="psx-copy",
        outputs=[output],
        inputs=[in_file_name],
    )
    if in_file_name in entries:
        return output
    entries[in_file_name] = {"reason": "copied"}
    nw.build(
        rule="phony",
        outputs=[in_file_name],
        implicit=[ld_script_path],
    )
    return output


def add_memcard_img_psx(
    nw: ninja_syntax.Writer,
    ver: str,
    in_file_name: str,
    out_file_name: str,
    ld_script_path: str,
):
    output_gfx = build_path(ver, f"{out_file_name}.png")
    output_pal = build_path(ver, f"{out_file_name}.pal")
    if output_gfx in entries or output_pal in entries:
        return [f"{output_gfx}.o", f"{output_pal}.o"]
    entries[output_gfx] = {}
    entries[output_pal] = {}
    slot_id = out_file_name.split("memcard_")[1]
    nw.build(
        rule="psx-as",
        outputs=[f"{output_gfx}.o"],
        inputs=[f"{output_gfx}.s"],
    )
    nw.build(
        rule="psx-as",
        outputs=[f"{output_pal}.o"],
        inputs=[f"{output_pal}.s"],
    )
    nw.build(
        rule="memcard-encode",
        outputs=[f"{output_gfx}.s", f"{output_pal}.s"],
        inputs=[in_file_name],
        variables={
            "out_gfx": f"{output_gfx}.s",
            "out_pal": f"{output_pal}.s",
            "sym_gfx": f"g_saveIcon{slot_id}",
            "sym_pal": f"g_saveIconPal{slot_id}",
        },
    )
    nw.build(
        rule="phony",
        outputs=[in_file_name],
        implicit=[ld_script_path],
    )
    return [f"{output_gfx}.o", f"{output_pal}.o"]


def add_c_psp(
    nw: ninja_syntax.Writer, ver: str, file_name: str, ld_path: str, cpp_flags: str
):
    output = build_path(ver, f"{file_name}.o")
    if output in entries:
        return output
    entries[output] = {}
    c_params = get_compiler_params(file_name)
    nw.build(
        rule="psp-cc",
        outputs=output,
        inputs=file_name,
        implicit=[
            f"src/.assets_build_done_{ver}",
            ld_path,
            "include/types.h",
            "include/common.h",
            "include/game.h",
            "include/entity.h",
            "include/sfx.h",
        ],
        variables={
            "version": ver,
            "cpp_flags": cpp_flags,
            "opt_level": c_params.mwcc_opt,
            "src_dir": os.path.dirname(file_name),
            "encoding": c_params.encoding,
        },
    )

    # this file may be generated by a different
    # version of the game, but the content will
    # be identical.
    if file_name in entries:
        return output
    entries[file_name] = {"reason": "generated"}
    nw.build(
        rule="phony",
        outputs=file_name,
        implicit=[f"src/.assets_build_done_{ver}"],
    )
    return output


def add_s_psp(nw: ninja_syntax.Writer, ver: str, file_name: str, ld_path: str):
    output = build_path(ver, f"{file_name}.o")
    if output in entries:
        return output
    entries[output] = {}
    nw.build(
        rule="psp-as",
        outputs=[output],
        inputs=[file_name],
    )
    nw.build(
        rule="phony",
        outputs=[file_name],
        implicit=[ld_path],
    )
    return output


def add_assets_config(nw: ninja_syntax.Writer, ver: str):
    nw.build(
        rule="assets-build",
        inputs=f"config/assets.{ver}.yaml",
        outputs=f"src/.assets_build_done_{ver}",
        implicit=f"assets/done_{ver}",
    )


def add_gfx_stage(
    nw: ninja_syntax.Writer, target_path: str, asset_path: str, output_name: str
):
    input_name = f"{asset_path}_0.png"
    if input_name not in entries:
        entries[input_name] = {"reason": "gfxtage decoding"}
        nw.build(
            rule="gfxstage-decode",
            outputs=input_name,
            inputs=target_path,
            variables={
                "path": asset_path,
            },
        )
    nw.build(
        rule="gfxstage-encode",
        outputs=[output_name],
        inputs=[input_name],
        variables={
            "path": asset_path,
        },
    )


def add_gfx_weapon(nw: ninja_syntax, ver: str, base_file: str, linker_path: str):
    ovl_id = os.path.basename(base_file).strip("f_")
    in_file = f"{base_file}.png"
    step_raw = build_path(ver, f"{base_file}.bin")
    step_elf = build_path(ver, f"weapon/f0_{ovl_id}.elf")
    step_bin = build_path(ver, f"weapon/f0_{ovl_id}.bin")
    nw.build(
        rule="psx-strip",
        outputs=step_bin,
        inputs=step_elf,
    )
    nw.build(
        rule="psx-copy",
        outputs=step_elf,
        inputs=step_raw,
    )
    nw.build(
        rule="gfxweapon-encode",
        outputs=step_raw,
        inputs=in_file,
    )
    nw.build(
        rule="phony",
        outputs=in_file,
        implicit=linker_path,
    )
    return step_bin


def add_weapon_splat_config(nw: ninja_syntax.Writer, ver: str, splat_config):
    hand_id = 0  # hardcoded for the time being
    platform = str(splat_config["options"]["platform"])
    asset_path = str(splat_config["options"]["asset_path"])
    ld_path = str(splat_config["options"]["ld_script_path"])
    symbol_paths = list[str](splat_config["options"]["symbol_addrs_path"])
    undefined_funcs_auto_path = str(
        splat_config["options"]["undefined_funcs_auto_path"]
    )
    undefined_syms_auto_path = str(splat_config["options"]["undefined_syms_auto_path"])
    asm_path = str(splat_config["options"]["asm_path"])
    src_path = str(splat_config["options"]["src_path"])
    ovl_name = str(splat_config["options"]["basename"])

    nw.build(
        rule="splat",
        outputs=[ld_path],
        inputs=[entry.path],
        implicit=symbol_paths,
        variables={
            "version": ver,
            "dynamic_symbols": "",
        },
    )
    if platform == "psx":
        add_c = add_c_psx
        add_s = add_s_psx
    elif platform == "psp":
        add_c = add_c_psp
        add_s = add_s_psp
    else:
        raise Exception(f"platform {platform} not recognized")
    if sotn_progress_report:
        add_s = add_s_dummy

    weapons = []
    weapon_gfx = ""  # horrible hack as code segments for weapon do not have a name
    for segment in splat_config["segments"]:
        if not "type" in segment:
            continue
        if segment["type"] == "grey4":
            weapon_gfx = segment["name"]
            if not sotn_progress_report:
                weapons.append(
                    add_gfx_weapon(
                        nw, ver, os.path.join(asset_path, weapon_gfx), ld_path
                    )
                )
            continue
        if segment["type"] != "code":
            continue
        weapon_id = weapon_gfx[2:]
        cpp_flags = f"-DW_{weapon_id} -DWEAPON{hand_id}"
        objs = []
        for subsegment in segment["subsegments"]:
            kind = subsegment[1]
            if kind == "data":
                obj = add_s(nw, ver, f"{asm_path}/data/w_{weapon_id}.data.s", ld_path)
                objs.append(obj)
            elif kind == "sbss":
                obj = add_s(nw, ver, f"{asm_path}/data/w_{weapon_id}.sbss.s", ld_path)
                objs.append(obj)
            elif kind == "c":
                obj = add_c(nw, ver, f"{src_path}/w_{weapon_id}.c", ld_path, cpp_flags)
                objs.insert(0, obj)  # the C file needs to always be linked first
            elif kind == ".data":
                continue
            elif kind == ".rodata":
                continue
            elif kind == ".bss":
                continue
            elif kind == "animset":
                continue
            else:
                raise Exception(f"unknown subsegment type {kind}")
        if sotn_progress_report:
            continue
        step_elf = build_path(ver, f"weapon/w{hand_id}_{weapon_id}.elf")
        symbols_lists = [
            f"-T config/undefined_syms.{ver}.txt",
            f"-T {undefined_funcs_auto_path}",
            f"-T {undefined_syms_auto_path}",
        ]
        nw.build(
            rule="psx-ld",
            outputs=step_elf,
            inputs=f"weapon{hand_id}.ld",
            implicit=objs,
            variables={
                "version": ver,
                "obj_files": objs,
                "ld_flags": "--gc-sections" if platform == "psp" else "",
                "map_out": build_path(ver, f"weapon/w{hand_id}_{weapon_id}.map"),
                "symbols_arg": str.join(" ", symbols_lists),
            },
        )
        step_bin = build_path(ver, f"weapon/w{hand_id}_{weapon_id}.bin")
        nw.build(
            rule="psx-strip-weapon",
            outputs=step_bin,
            inputs=step_elf,
        )
        weapons.append(step_bin)
    if sotn_progress_report:
        return
    nw.build(
        rule="concat",
        outputs=build_path(ver, f"WEAPON0.BIN"),
        inputs=weapons,
    )

    dyn_symbols_file = build_path(ver, f"config/dyn_syms.{ovl_name}.txt")
    nw.build(
        rule="export-dynamic-symbols-dummy",
        outputs=[dyn_symbols_file],
        inputs=[f"config/splat.{ver}.weapon.yaml"],
    )


def add_splat_config(nw: ninja_syntax.Writer, ver: str, file_name: str):
    with open(file_name) as f:
        splat_config = yaml.load(f, Loader=yaml.SafeLoader)
    platform = str(splat_config["options"]["platform"])
    ovl_name = str(splat_config["options"]["basename"])
    ld_path = str(splat_config["options"]["ld_script_path"])

    if not sotn_progress_report:
        dyn_symbols_file = build_path(ver, f"config/dyn_syms.{ovl_name}.txt")
        dyn_syms_splat_config = build_path(
            ver, f"config/splat.{ver}.{ovl_name}.yaml.dyn_syms"
        )
        linker_scripts.add(ld_path)
        nw.build(
            rule="dynamic-splat-config",
            inputs=dyn_symbols_file,
            outputs=dyn_syms_splat_config,
        )

    if is_weapon(ovl_name):
        add_weapon_splat_config(nw, ver, splat_config)
        return
    target_path = str(splat_config["options"]["target_path"])
    asset_path = str(splat_config["options"]["asset_path"])
    symbol_paths = list[str](splat_config["options"]["symbol_addrs_path"])
    undefined_funcs_auto_path = str(
        splat_config["options"]["undefined_funcs_auto_path"]
    )
    undefined_syms_auto_path = str(splat_config["options"]["undefined_syms_auto_path"])
    asm_path = str(splat_config["options"]["asm_path"])
    src_path = str(splat_config["options"]["src_path"])

    dynamic_symbols = ""
    if "FORCE_SYMBOLS" in os.environ and Path(dyn_symbols_file).exists():
        dynamic_symbols = dyn_syms_splat_config

    nw.build(
        rule="splat",
        outputs=[ld_path],
        inputs=[entry.path],
        implicit=symbol_paths,
        variables={"version": ver, "dynamic_symbols": dynamic_symbols},
    )
    if platform == "psx":
        add_c = add_c_psx
        add_s = add_s_psx
    elif platform == "psp":
        add_c = add_c_psp
        add_s = add_s_psp
    else:
        raise Exception(f"platform {platform} not recognized")
    if sotn_progress_report:
        add_s = add_s_dummy
    objs = []
    if ovl_name == "main" and platform != "psp":
        objs.append(add_s(nw, ver, f"{asm_path}/header.s", ld_path))
    if ovl_name == "main" and platform == "psp":
        obj = add_copy_psx(
            nw,
            ver,
            f"{asset_path}/elf_header.bin",
            f"{asset_path}/elf_header.bin",
            ld_path,
        )
        objs.append(obj)
        obj = add_copy_psx(
            nw,
            ver,
            f"{asset_path}/elf_footer.bin",
            f"{asset_path}/elf_footer.bin",
            ld_path,
        )
        objs.append(obj)
    for segment in splat_config["segments"]:
        if not "type" in segment:
            continue
        if segment["type"] == "data":
            asm_name = f"{asm_path}/data/{segment["name"]}.data.s"
            objs.append(add_s(nw, ver, asm_name, ld_path))
            continue
        for subsegment in segment["subsegments"]:
            if isinstance(subsegment, dict):  # handle PSP BSS
                if not "start" in subsegment:  # skip malformed BSS
                    continue
                subsegment_as_obj = subsegment
                subsegment = [  # normalize subsegment
                    subsegment["start"],
                    subsegment["type"],
                ]
                if "name" in subsegment_as_obj:
                    subsegment.append(subsegment_as_obj["name"])
            offset = int(subsegment[0])
            if len(subsegment) < 2:  # for subsegment entries without a kind
                kind = "data"
                name = segment["name"]
            else:
                kind = str(subsegment[1])
                if len(subsegment) > 2:
                    name = str(subsegment[2])
                else:
                    name = str.format("{0:X}", offset)
            if kind == "c" or kind == ".data" or kind == ".rodata" or kind == ".bss":
                objs.append(add_c(nw, ver, f"{src_path}/{name}.c", ld_path, ""))
            elif kind == "data" or kind == "rodata" or kind == "bss" or kind == "sbss":
                obj = add_s(nw, ver, f"{asm_path}/data/{name}.{kind}.s", ld_path)
                objs.append(obj)
            elif kind == "textbin":
                objs.append(add_s(nw, ver, f"{asm_path}/data/{name}.s", ld_path))
            elif kind == "asm":
                objs.append(add_s(nw, ver, f"{asm_path}/{name}.s", ld_path))
            elif kind == "raw" or kind == "cmp":
                objs.append(
                    add_copy_psx(
                        nw,
                        ver,
                        f"{asset_path}/{name}.bin",
                        f"{asset_path}/{name}",
                        ld_path,
                    )
                )
            elif kind == "cmpgfx":
                objs.append(
                    add_copy_psx(
                        nw,
                        ver,
                        f"{asset_path}/{name}.gfxbin",
                        f"{asset_path}/{name}",
                        ld_path,
                    )
                )
            elif kind == "pal":
                objs.append(
                    add_copy_psx(
                        nw,
                        ver,
                        f"{asset_path}/{name}.palbin",
                        f"{asset_path}/{name}",
                        ld_path,
                    )
                )
            elif kind == "palette":
                objs_memcard = add_memcard_img_psx(
                    nw,
                    ver,
                    f"{asset_path}/{name}.png",
                    f"{asset_path}/{name}",
                    ld_path,
                )
                objs += objs_memcard
            else:
                continue
    if sotn_progress_report:
        return
    if platform == "psp" and ovl_name != "main":
        mwo = os.path.join(asset_path, "mwo_header.bin")
        objs.append(add_copy_psx(nw, ver, mwo, mwo, ld_path))
    output_elf = build_path(ver, f"{ovl_name}.elf")
    sym_version = ver
    if ovl_name == "stmad":
        sym_version = "beta"
    if ovl_name == "sd":
        sym_version = "sd"
    if ovl_name == "fname":
        sym_version = "beta_fname"
    symbols_lists = [
        f"-T config/undefined_syms.{sym_version}.txt",
    ]
    ld_flags_extra = ""
    if platform == "psp":
        # used to force the linker to not garbage-collect specific user-defined symbols
        symbols_lists.append(f"-T config/symexport.{ver}.{ovl_name}.txt")
        main_export_script = build_path(ver, "main.symexport.ld")
        if ovl_name == "main":
            symbols_lists.append(f"-T {undefined_funcs_auto_path}")
            symbols_lists.append(f"-T {undefined_syms_auto_path}")
            # Make `main` symbols available to other overlays
            nw.build(
                rule="export-symbols",
                outputs=[main_export_script],
                inputs=[output_elf],
            )
        else:
            # force DRA to be linked with the exported `main` symbols, allowing
            # for the linker to fail if symbols are not correctly synchronized.
            if ovl_name != "dra":
                # TODO this should also be removed for all other overlays. But
                # this would require DRA to also export its own symbols.
                symbols_lists.append(f"-T {undefined_funcs_auto_path}")
                symbols_lists.append(f"-T {undefined_syms_auto_path}")

            # allow unused symbols in overlays to be garbage-collected
            ld_flags_extra = "--gc-sections"

            # allow overlays to use symbols exported from `main`
            symbols_lists.append(f"-T {main_export_script}")

            # tell Ninja to wait `main.elf` for generate the linker script
            # before linking any overlay
            objs.append(main_export_script)
    elif platform == "psx":
        if ovl_name != "main":
            symbols_lists.append(f"-T {undefined_funcs_auto_path}")
        symbols_lists.append(f"-T {undefined_syms_auto_path}")
    nw.build(
        rule="psx-ld",
        outputs=[output_elf],
        inputs=[ld_path],
        implicit=[x for x in objs if x],
        variables={
            "ld_flags": ld_flags_extra,
            "map_out": build_path(ver, f"{ovl_name}.map"),
            "symbols_arg": str.join(" ", symbols_lists),
        },
    )
    strip_rule = "psx-strip"
    if platform != "psp" and not is_hd(ver) and is_servant(ovl_name):
        strip_rule = "psx-strip-servant"
    output_name = os.path.basename(target_path)
    if ovl_name == "main":
        output_name = "main.exe"
    nw.build(
        rule=strip_rule,
        outputs=build_path(ver, output_name),
        inputs=[output_elf],
    )
    if platform == "psx":
        if (is_stage(ovl_name) or is_boss(ovl_name)) and ovl_name != "stsel":
            gfx_name = f"F_{os.path.basename(target_path)}"
            if is_hd(ver):
                gfx_name = f"f_{os.path.basename(target_path)}"
            stage_gfx_path = build_path(ver, gfx_name)
            target_f_path = os.path.join(os.path.dirname(target_path), gfx_name)
            add_gfx_stage(nw, target_f_path, asset_path, stage_gfx_path)

    nw.build(
        rule="export-dynamic-symbols",
        outputs=[dyn_symbols_file],
        inputs=[file_name],
        implicit=[output_elf],
    )


def add_checksum(nw: ninja_syntax.Writer, ver: str, file_name: str):
    with open(file_name) as f:
        lines = f.readlines()
    binaries = [line.split(" ")[2].strip() for line in lines]
    if ver == "us":
        dirt = build_path(ver, "dra.dirt.done")
        binaries.append(dirt)
        nw.build(
            rule="dirt",
            outputs=dirt,
            inputs=f"config/dirt.{ver}.json",
            implicit=build_path(ver, "DRA.BIN"),
        )
    nw.build(
        rule="check",
        outputs=[f"{ver} 🆗"],
        inputs=file_name,
        implicit=binaries,
    )


build_ninja = "build.ninja"
if len(sys.argv) > 1:
    build_ninja = str(sys.argv[1])
    os.makedirs(os.path.dirname(build_ninja), exist_ok=True)

with open(build_ninja, "w") as f:
    nw = ninja_syntax.Writer(f)

    nw.rule(
        "splat",
        # 'touch' circumnavigates a bug where splat would not update the
        # mtime of the linker script if it is already up-to-date.
        command=f".venv/bin/splat split $in $dynamic_symbols > /dev/null && touch $out",
        description="splat $in",
    )
    nw.rule(
        "concat",
        command="cat $in > $out",
        description="concat to $out",
    )
    cpp_defs = f"-Dmips -D__GNUC__=2 -D__OPTIMIZE__ -D__mips__ -D__mips -Dpsx -D__psx__ -D__psx -D_PSYQ -D__EXTENSIONS__ -D_MIPSEL -D_LANGUAGE_C -DLANGUAGE_C -DNO_LOGS -DHACKS -DUSE_INCLUDE_ASM -D_internal_version_$version -DSOTN_STR"
    cc_command = (
        "VERSION=$version"
        f" mipsel-linux-gnu-cpp $cpp_flags -MMD -MF $out.d -lang-c -Iinclude -Iinclude/psxsdk -undef -Wall -fno-builtin {cpp_defs} {extra_cpp_defs} $in"
        " | tools/sotn_str/target/release/sotn_str process"
        " | iconv --from-code=UTF-8 --to-code=Shift-JIS"
        " | bin/cc1-psx-26 -G0 -w -funsigned-char -fpeephole -ffunction-cse -fpcc-struct-return -fcommon -fverbose-asm -msoft-float -g -quiet -mcpu=3000 -fgnu-linker -mgas -gcoff $cc_flags"
        " | python3 tools/maspsx/maspsx.py --expand-div --aspsx-version=$aspsx_ver"
        " | mipsel-linux-gnu-as -Iinclude -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0 -o $out"
    )
    nw.rule(
        "psx-cc",
        depfile="$out.d",
        deps="gcc",
        command=cc_command,
        description="psx cc $in",
    )
    nw.rule(
        "psx-as",
        command="mipsel-linux-gnu-as -Iinclude -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0 -o $out $in",
        description="psx as $in",
    )
    nw.rule(
        "psx-copy",
        command="mipsel-linux-gnu-ld -r -b binary -o $out $in",
        description="psx copy $in",
    )
    nw.rule(
        "psx-ld",
        command="mipsel-linux-gnu-ld -nostdlib --no-check-sections $ld_flags -Map $map_out -T $in $symbols_arg -o $out $obj_files",
        description="mipsel-linux-gnu-ld -nostdlib --no-check-sections -Map $map_out -T $in $symbols_arg -o $out",
    )
    nw.rule(
        "psx-strip",
        command="mipsel-linux-gnu-objcopy -O binary $in $out",
        description="psx strip $in",
    )
    nw.rule(
        "psx-strip-servant",
        command="mipsel-linux-gnu-objcopy -O binary $in $out && truncate -c -s 40960 $out",
        description="psx strip $in",
    )
    nw.rule(
        "psx-strip-weapon",
        command="mipsel-linux-gnu-objcopy -O binary $in $out && truncate -c -s 12288 $out",
        description="psx strip $in",
    )
    nw.rule(
        "psp-cc",
        command=(
            "VERSION=$version"
            " tools/sotn_str/target/release/sotn_str process -p -f $in"
            " | .venv/bin/python3 tools/mwccgap/mwccgap.py $out --src-dir $src_dir"
            " --mwcc-path bin/mwccpsp.exe --use-wibo --wibo-path bin/wibo --as-path tools/pspas/target/release/pspas"
            " --asm-dir-prefix asm/pspeu --target-encoding $encoding --macro-inc-path include/macro.inc"
            f" -gccinc -Iinclude -Iinclude/pspsdk -D_internal_version_$version -DSOTN_STR {extra_cpp_defs} -c -lang c -sdatathreshold 0 -char unsigned -fl divbyzerocheck"
            " $opt_level -opt nointrinsics"
        ),
        description="psp cc $in",
    )
    nw.rule(
        "psp-as",
        command="bin/allegrex-as -EL -I include/ -G0 -march=allegrex -mabi=eabi -o $out $in",
        description="psp as $in",
    )
    nw.rule(
        "dirt",
        command=".venv/bin/python3 tools/dirt_patcher.py $in && touch $out",
        description="dirt $in",
    )
    nw.rule(
        "assets-extract",
        command="bin/sotn-assets extract $in && touch $out",
        description="extract $in",
    )
    nw.rule(
        "assets-build",
        command="bin/sotn-assets build $in && mkdir -p $$(dirname $out) && touch $out",
        description="build $in",
    )
    nw.rule(
        "gfxstage-decode",
        command=".venv/bin/python3 tools/gfxstage.py d $in $path",
        description="gfxstage decode $in",
    )
    nw.rule(
        "gfxstage-encode",
        command=".venv/bin/python3 tools/gfxstage.py e $path $out",
        description="gfxstage encode $in",
    )
    nw.rule(
        "gfxweapon-encode",
        command=".venv/bin/python3 tools/png2bin.py $in $out",
        description="gfxweapon encode $in",
    )
    nw.rule(
        "memcard-encode",
        command=".venv/bin/python3 tools/png2s.py encode $in $out_gfx $sym_gfx $out_pal $sym_pal",
        description="memcard icon encode $in",
    )
    nw.rule(
        "export-symbols",
        command=".venv/bin/python3 tools/symbols.py parse $in > $out",
        description="export symbols $in",
    )
    nw.rule(
        "export-dynamic-symbols",
        command=".venv/bin/python3 tools/symbols.py dynamic $in > $out",
        description="export dynamic symbols $in",
    )
    nw.rule(
        "export-dynamic-symbols-dummy",
        command="touch $out",
        description="export fake dynamic symbols $in",
    )
    nw.rule(
        "dynamic-splat-config",
        command="echo '{options: { symbol_addrs_path: [ '$in']}}' > $out",
        description="create dynamic splat $out",
    )
    nw.rule(
        "check",
        command=".venv/bin/python3 tools/builds/check.py $in",
        description="check $in",
    )

    actual_version = os.getenv("VERSION")
    if not actual_version:
        actual_version = "us,hd,pspeu"
    for version in actual_version.split(","):
        nw.build(
            rule="assets-extract",
            outputs=f"assets/done_{version}",
            inputs=f"config/assets.{version}.yaml",
            implicit="bin/sotn-assets",
        )
        for entry in os.scandir("config/"):
            if not entry.name.startswith(f"splat.{version}."):
                continue
            add_splat_config(nw, version, entry.path)
        add_assets_config(nw, version)
        if not sotn_progress_report:
            add_checksum(nw, version, f"config/check.{version}.sha")

    nw.build(
        rule="phony",
        outputs="split",
        implicit=list(linker_scripts),
    )

    nw.close()
