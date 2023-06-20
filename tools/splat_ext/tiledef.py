#!/usr/bin/python3

import ctypes
import json
import io
import os
import sys
from typing import Optional
from pathlib import Path

sys.path.append(f"{os.getcwd()}/tools/n64splat")
sys.path.append(f"{os.getcwd()}/tools/splat_ext")
from util import options, log
from segtypes.n64.segment import N64Segment
from util.symbols import spim_context
import utils


def generate_assembly_tiledef(writer: io.BufferedWriter, name: str, content: str):
    obj = json.loads(content)
    gfxPage = obj["gfxPage"]
    gfxIndex = obj["gfxIndex"]
    clut = obj["clut"]
    collision = obj["collision"]

    writer.write(".section .data\n")
    writer.write(f".global {name}\n")
    writer.write(f"{name}:\n")
    writer.write(f".word {gfxPage}, {gfxIndex}, {clut}, {collision}\n")


class PSXSegTiledef(N64Segment):
    def __init__(self, rom_start, rom_end, type, name, vram_start, args, yaml):
        super().__init__(rom_start, rom_end, type, name, vram_start, args, yaml),

    def out_path(self) -> Optional[Path]:
        return options.opts.asset_path / self.dir / self.name

    def src_path(self) -> Optional[Path]:
        return options.opts.asset_path / self.dir / f"{self.name}.tiledef.json"

    def split(self, rom_bytes):
        path = self.src_path()
        path.parent.mkdir(parents=True, exist_ok=True)

        data, err = self.parse_tiledef(rom_bytes[self.rom_start : self.rom_end])
        if err != None:
            log.error(err)
            raise Exception(err)

        with open(path, "w") as f:
            f.write(json.dumps(data, indent=4))

    def parse_tiledef(self, data: bytearray):
        def get_sym(offset):
            defined_sym = self.get_symbol(utils.to_u32(data[0:]))
            return defined_sym.given_name if defined_sym != None else f"D_{offset:08X}"

        base_addr = self.vram_start
        header_len = 0x10
        header_off = len(data) - header_len
        page_addr = utils.to_u32(data[header_off + 0 :])
        index_addr = utils.to_u32(data[header_off + 4 :])
        clut_addr = utils.to_u32(data[header_off + 8 :])
        col_addr = utils.to_u32(data[header_off + 12 :])

        if page_addr >= index_addr:
            return None, f"Page >= Index ({page_addr:08X} >= {index_addr:08X})."
        if index_addr >= clut_addr:
            return None, f"Index >= CLUT ({index_addr:08X} >= {clut_addr:08X})."
        if clut_addr >= col_addr:
            return None, f"CLUT >=  Col ({clut_addr:08X} >= {col_addr:08X})."
        if page_addr != base_addr:
            exp_start = page_addr - (self.vram_start - self.rom_start)
            exp_sym = self.vram_start + header_off
            msg = (
                f"Page != start ({page_addr:08X} != {base_addr:08X}).\n"
                + f"- [0x{exp_start:X}, tiledef, D_{exp_sym:X}]"
            )
            return None, msg

        page_off = page_addr - base_addr
        index_off = index_addr - base_addr
        clut_off = clut_addr - base_addr
        col_off = col_addr - base_addr
        return {
            "gfxPage": [int(x) for x in data[page_off:index_off]],
            "gfxIndex": [int(x) for x in data[index_off:clut_off]],
            "clut": [int(x) for x in data[clut_off:col_off]],
            "collision": [int(x) for x in data[col_off:header_off]],
        }, None


if __name__ == "__main__":

    def get_file_name(full_path):
        file_name = os.path.basename(full_path)
        exts = os.path.splitext(file_name)
        if len(exts) > 1 and len(exts[1]) > 0:
            return get_file_name(exts[0])
        return exts[0]

    input_file_name = sys.argv[1]
    output_file_name = sys.argv[2]

    with open(input_file_name, "r") as f_in:
        name = get_file_name(input_file_name)
        with open(output_file_name, "w") as f_out:
            generate_assembly_tiledef(f_out, name, f_in.read())
