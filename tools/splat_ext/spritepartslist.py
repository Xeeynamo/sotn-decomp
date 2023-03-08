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
from util import options
from segtypes.n64.segment import N64Segment
from util.symbols import spim_context

def generate_assembly_spritepartslist(writer: io.BufferedWriter, name: str, content: str):
    obj = json.loads(content)

    writer.write(".section .data\n")
    writer.write(f".global {name}\n")
    writer.write(f"{name}:\n")
    for sym in obj:
        writer.write(f".word {sym}\n")
    writer.write(f".word 0\n")


class PSXSegSpritepartslist(N64Segment):
    def __init__(self, rom_start, rom_end, type, name, vram_start, args, yaml):
        super().__init__(rom_start, rom_end, type, name, vram_start, args, yaml),

    def out_path(self) -> Optional[Path]:
        return options.opts.asset_path / self.dir / self.name

    def src_path(self) -> Optional[Path]:
        return options.opts.asset_path / self.dir / f"{self.name}.spritepartslist.json"

    def split(self, rom_bytes):
        path = self.src_path()
        path.parent.mkdir(parents=True, exist_ok=True)

        data = self.parse_spritepartslist(rom_bytes[self.rom_start:self.rom_end])
        with open(path, "w") as f:
            f.write(json.dumps(data, indent=4))

    def parse_spritepartslist(self, data: bytearray):
        def to_u32(data):
            return ctypes.c_uint32(
                data[0] |
                (data[1] << 8) |
                (data[2] << 16) |
                (data[3] << 24)).value

        sprite_parts_list = [
            0
        ]
        idx = 1
        while True:
            addr = to_u32(data[idx * 4:])
            idx += 1
            if addr == 0:
                break
            sym = self.get_symbol(addr).given_name
            sprite_parts_list.append(sym)
        return sprite_parts_list


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
            generate_assembly_spritepartslist(f_out, name, f_in.read())
