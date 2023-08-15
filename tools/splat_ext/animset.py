#!/usr/bin/python3

import argparse
import json
import io
import os
import sys
from typing import Optional
from pathlib import Path

sys.path.append(f"{os.getcwd()}/tools/n64splat")
sys.path.append(f"{os.getcwd()}/tools/splat_ext")
from util import options
from segtypes.n64.segment import N64Segment
import utils


item_size = 0x18  # sizeof(SpritePart)


def parse_spriteparts(data: bytearray) -> list:
    count = utils.to_s16(data[0:])
    items = []
    for i in range(0, count):
        items.append(
            {
                "flags": utils.to_s16(data[2 + i * item_size + 0 :]),
                "offsetx": utils.to_s16(data[2 + i * item_size + 2 :]),
                "offsety": utils.to_s16(data[2 + i * item_size + 4 :]),
                "width": utils.to_s16(data[2 + i * item_size + 6 :]),
                "height": utils.to_s16(data[2 + i * item_size + 8 :]),
                "clut": utils.to_s16(data[2 + i * item_size + 10 :]),
                "tileset": utils.to_s16(data[2 + i * item_size + 12 :]),
                "left": utils.to_s16(data[2 + i * item_size + 14 :]),
                "top": utils.to_s16(data[2 + i * item_size + 16 :]),
                "right": utils.to_s16(data[2 + i * item_size + 18 :]),
                "bottom": utils.to_s16(data[2 + i * item_size + 20 :]),
            }
        )
    return items


def parse_animset(start_ptr, data: bytearray) -> list:
    end_ptr = start_ptr + len(data)
    assumed_list_end = len(data)
    spriteparts_offsets = []
    for i in range(0, len(data), 4):
        if i >= assumed_list_end:
            break
        ptr = utils.to_u32(data[i:])
        if ptr != 0:
            if ptr < start_ptr or ptr >= end_ptr:
                utils.log_fatal(
                    f"spriteparts list pointer 0x{ptr:X} is out of bounds (start:{start_ptr:X}, end:{end_ptr:X})"
                )
            offset = ptr - start_ptr
            assumed_list_end = min(assumed_list_end, offset)
            spriteparts_offsets.append(offset)
        else:
            spriteparts_offsets.append(0)

    animset = []
    for offset in spriteparts_offsets:
        if offset != 0:
            animset.append(parse_spriteparts(data[offset:]))
        else:
            animset.append([])
    return animset


def write_animset_list_as_asm(writer: io.BufferedWriter, name: str, content: str):
    obj = json.loads(content)

    writer.write(".section .data\n")
    writer.write(f".global {name}\n")
    writer.write(f"{name}:\n")
    for i, spriteparts in enumerate(obj):
        if len(spriteparts) > 0:
            writer.write(f".word {name}_{i}\n")
        else:
            writer.write(".word 0\n")

    for i, spriteparts in enumerate(obj):
        if len(spriteparts) == 0:
            continue
        n_parts = len(spriteparts)
        writer.write(f".global {name}_{i}\n")
        writer.write(f"{name}_{i}:\n")
        writer.write(f".half {n_parts}\n")
        for i, part in enumerate(spriteparts):
            writer.write(f"# part {i}\n")
            writer.write(f".half {part['flags']}\n")
            writer.write(f".half {part['offsetx']}\n")
            writer.write(f".half {part['offsety']}\n")
            writer.write(f".half {part['width']}\n")
            writer.write(f".half {part['height']}\n")
            writer.write(f".half {part['clut']}\n")
            writer.write(f".half {part['tileset']}\n")
            writer.write(f".half {part['left']}\n")
            writer.write(f".half {part['top']}\n")
            writer.write(f".half {part['right']}\n")
            writer.write(f".half {part['bottom']}\n")
        # now align by 4
        if (n_parts % 2) == 1:
            writer.write(f".word 0 # padding\n")


class PSXSegAnimset(N64Segment):
    def __init__(self, rom_start, rom_end, type, name, vram_start, args, yaml):
        super().__init__(rom_start, rom_end, type, name, vram_start, args, yaml),

    def out_path(self) -> Optional[Path]:
        return options.opts.asset_path / self.dir / self.name

    def src_path(self) -> Optional[Path]:
        return options.opts.asset_path / self.dir / f"{self.name}.animset.json"

    def split(self, rom_bytes):
        path = self.src_path()
        path.parent.mkdir(parents=True, exist_ok=True)

        data = parse_animset(self.vram_start, rom_bytes[self.rom_start : self.rom_end])
        with open(path, "w") as f:
            f.write(json.dumps(data, indent=4))


def get_file_name(full_path):
    file_name = os.path.basename(full_path)
    exts = os.path.splitext(file_name)
    if len(exts) > 1 and len(exts[1]) > 0:
        return get_file_name(exts[0])
    return exts[0]


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="De/serialize a list of animation sets"
    )
    subparsers = parser.add_subparsers(dest="command")

    gen_asm_parser = subparsers.add_parser(
        "gen-asm",
        description="Generate assembly code from an already parsed JSON",
    )
    gen_asm_parser.add_argument(
        "input",
        help="The animset parsed in JSON to convert",
    )
    gen_asm_parser.add_argument(
        "output",
        help="Generates the correspondent assembly code",
    )
    gen_asm_parser.add_argument(
        "-s", "--symbol", required=False, type=str, help="Assign a custom symbol name"
    )

    args = parser.parse_args()
    if args.command == "gen-asm":
        symbol_name = args.symbol
        if symbol_name is None:
            symbol_name = get_file_name(args.input)
        with open(args.input, "r") as f_in:
            with open(args.output, "w") as f_out:
                write_animset_list_as_asm(f_out, symbol_name, f_in.read())
