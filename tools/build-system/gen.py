# usage
# python3 ./tools/build/gen.py && ninja -j1
from pydoc import describe

import ninja_syntax
import os
import shutil
import yaml

# global dictionary that collects all source entries
# useful to avoid adding multiple rules for the same output file
entries = dict()


def is_psp(version: str) -> bool:
    return version.startswith("psp")


def is_hd(version: str) -> bool:
    return version == "hd"


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


def add_c_psx(nw: ninja_syntax.Writer, version: str, file_name: str):
    output = f"build/{version}/{file_name}.o"
    if output in entries:
        return
    entries[output] = {}
    nw.build(
        rule="psx-cc", outputs=output, inputs=file_name, implicit=["include/game.h"]
    )
    return output


def add_s_psx(
    nw: ninja_syntax.Writer, version: str, file_name: str, ld_script_path: str
):
    output = f"build/{version}/{file_name}.o"
    if output in entries:
        return
    entries[output] = {}
    nw.build(
        rule="psx-as",
        outputs=[output],
        inputs=[file_name],
    )
    nw.build(
        rule="phony",
        outputs=[file_name],
        implicit=[ld_script_path],
    )
    return output


def add_copy_psx(
    nw: ninja_syntax.Writer,
    version: str,
    in_file_name: str,
    out_file_name: str,
    ld_script_path: str,
):
    output = f"build/{version}/{out_file_name}.o"
    if output in entries:
        return
    entries[output] = {}
    nw.build(
        rule="psx-copy",
        outputs=[output],
        inputs=[in_file_name],
    )
    nw.build(
        rule="phony",
        outputs=[in_file_name],
        implicit=[ld_script_path],
    )
    return output


def add_c_psp(nw: ninja_syntax.Writer, version: str, file_name: str):
    return None


def add_s_psp(nw: ninja_syntax.Writer, version: str, file_name: str, linker_path: str):
    return None


def add_assets_config(nw: ninja_syntax.Writer, gen_dir: str, asset_config_name: str):
    output = f"{gen_dir}/done"
    if output in entries:
        return
    entries[output] = {}
    nw.build(
        rule="assets-build",
        inputs=asset_config_name,
        outputs=output,
        implicit="bin/sotn-assets",
    )
    return None


def add_gfx_stage(nw: ninja_syntax.Writer, asset_path: str, output_name: str):
    nw.build(
        rule="gfxstage-encode",
        outputs=[output_name],
        # TODO inputs
        variables={
            "path": asset_path,
        },
    )


def add_splat_config(nw: ninja_syntax.Writer, version: str, file_name: str):
    with open(file_name) as f:
        splat_config = yaml.load(f, Loader=yaml.SafeLoader)
    platform = splat_config["options"]["platform"]
    ovl_name = splat_config["options"]["basename"]
    target_path = splat_config["options"]["target_path"]
    asset_path = splat_config["options"]["asset_path"]
    ld_script_path = splat_config["options"]["ld_script_path"]
    symbol_paths = splat_config["options"]["symbol_addrs_path"]
    undefined_funcs_auto_path = splat_config["options"]["undefined_funcs_auto_path"]
    undefined_syms_auto_path = splat_config["options"]["undefined_syms_auto_path"]
    asm_path = splat_config["options"]["asm_path"]
    src_path = splat_config["options"]["src_path"]
    if ovl_name == "stmad":  # TODO currently broken
        return
    if ovl_name == "main":  # TODO currently broken
        return
    if ovl_name == "weapon":  # TODO currently broken
        return
    nw.build(
        rule="splat",
        outputs=[ld_script_path],
        inputs=[entry.path],
        implicit=symbol_paths,
    )
    if platform == "psx":
        add_c = add_c_psx
        add_s = add_s_psx
    elif platform == "psp":
        add_c = add_c_psp
        add_s = add_s_psp
    else:
        raise f"platform {platform} not recognized"
    objs = []
    for segment in splat_config["segments"]:
        if not "subsegments" in segment:
            continue
        for subsegment in segment["subsegments"]:
            if len(subsegment) < 2:  # for subsegment entries without a kind
                continue
            offset = int(subsegment[0])
            kind = str(subsegment[1])
            if len(subsegment) > 2:
                name = str(subsegment[2])
            else:
                name = str.format("{0:X}", offset)
            if kind == "c" or kind == ".data" or kind == ".rodata" or kind == ".bss":
                objs.append(add_c(nw, version, f"{src_path}/{name}.c"))
            elif kind == "data" or kind == "rodata" or kind == "bss":
                objs.append(
                    add_s(
                        nw, version, f"{asm_path}/data/{name}.{kind}.s", ld_script_path
                    )
                )
            elif kind == "raw" or kind == "cmp":
                objs.append(
                    add_copy_psx(
                        nw,
                        version,
                        f"{asset_path}/{name}.bin",
                        f"{asset_path}/{name}",
                        ld_script_path,
                    )
                )
            elif kind == "cmpgfx":
                objs.append(
                    add_copy_psx(
                        nw,
                        version,
                        f"{asset_path}/{name}.gfxbin",
                        f"{asset_path}/{name}",
                        ld_script_path,
                    )
                )
            elif kind == "pal":
                objs.append(
                    add_copy_psx(
                        nw,
                        version,
                        f"{asset_path}/{name}.palbin",
                        f"{asset_path}/{name}",
                        ld_script_path,
                    )
                )
            else:
                # TODO splat_ext assets
                continue
    output_elf = f"build/{version}/{ovl_name}.elf"
    nw.build(
        rule="psx-ld",
        outputs=[output_elf],
        inputs=[ld_script_path],
        implicit=[x for x in objs if x],
        variables={
            "map_out": f"build/{version}/{ovl_name}.map",
            "symbols_arg": str.join(
                " ",
                [
                    f"-T config/undefined_syms.{version}.txt",
                    f"-T {undefined_funcs_auto_path}",
                    f"-T {undefined_syms_auto_path}",
                ],
            ),
        },
    )
    nw.build(
        rule="psx-strip",
        outputs=[f"build/{version}/{os.path.basename(target_path)}"],
        inputs=[output_elf],
    )
    add_assets_config(
        nw, os.path.join(src_path, "gen"), f"config/assets.{version}.yaml"
    )
    if (is_stage(ovl_name) or is_boss(ovl_name)) and ovl_name != "stsel":
        add_gfx_stage(
            nw, asset_path, f"build/{version}/F_{os.path.basename(target_path)}"
        )


def add_checksum(nw: ninja_syntax.Writer, file_name: str):
    with open(file_name) as f:
        lines = f.readlines()
    binaries = [line.split(" ")[2].strip() for line in lines]
    nw.build(
        rule="check",
        outputs=["🆗"],
        inputs=file_name,
        implicit=binaries,
    )


with open("build.ninja", "w") as f:
    nw = ninja_syntax.Writer(f)
    nw.rule(
        "splat",
        # 'touch' circumnavigates a bug where splat would not update the
        # mtime of the linker script if it is already up-to-date.
        command="splat split $in && touch $out",
        description="splat $in",
    )
    nw.rule(
        "psx-cc",
        command="VERSION=us mipsel-linux-gnu-cpp -lang-c -Iinclude -Iinclude/psxsdk -undef -Wall -fno-builtin -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -D__mips__ -D__mips -Dpsx -D__psx__ -D__psx -D_PSYQ -D__EXTENSIONS__ -D_MIPSEL -D_LANGUAGE_C -DLANGUAGE_C -DNO_LOGS -DHACKS -DUSE_INCLUDE_ASM -D_internal_version_us -DSOTN_STR $in | tools/sotn_str/target/release/sotn_str process | iconv --from-code=UTF-8 --to-code=Shift-JIS | bin/cc1-psx-26 -G0 -w -O2 -funsigned-char -fpeephole -ffunction-cse -fpcc-struct-return -fcommon -fverbose-asm -msoft-float -g -quiet -mcpu=3000 -fgnu-linker -mgas -gcoff | python3 tools/maspsx/maspsx.py  --expand-div --aspsx-version=2.34 | mipsel-linux-gnu-as -Iinclude -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0 -o $out",
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
        command="mipsel-linux-gnu-ld -nostdlib --no-check-sections -Map $map_out -T $in $symbols_arg -o $out",
        description="VERSION=us mipsel-linux-gnu-ld -nostdlib --no-check-sections -Map $map_out -T $in $symbols_arg -o $out",
    )
    nw.rule(
        "psx-strip",
        command="mipsel-linux-gnu-objcopy -O binary $in $out",
        description="psx strip $in",
    )
    nw.rule(
        "sotn-assets",
        command="go build -o $out tools/sotn-assets",
        description="build assets-tool",
    )
    nw.rule(
        "assets-extract",
        command="bin/sotn-assets extract $in",
        description="extract $in",
    )
    nw.rule(
        "assets-build",
        command="bin/sotn-assets build $in && mkdir -p $$(dirname $out) && touch $out",
        description="build $in",
    )
    nw.rule(
        "gfxstage-encode",
        command="python3 tools/gfxstage.py e $path $out",
        description="gfxstage encode $in",
    )
    nw.rule("check", command="sha1sum --check $in", description="check $in")

    nw.build(
        rule="sotn-assets",
        outputs=["bin/sotn-assets"],
        implicit="tools/sotn-assets/go.mod",
    )

    for version in ["us"]:
        for entry in os.scandir("config/"):
            if not entry.name.startswith(f"splat.{version}."):
                continue
            add_splat_config(nw, version, entry.path)
        add_checksum(nw, f"config/check.{version}.sha")
    nw.close()
