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

        data = self.parse_tiledef(rom_bytes[self.rom_start:self.rom_end])
        print(data)
        with open(path, "w") as f:
            f.write(json.dumps(data, indent=4))

    def parse_tiledef(self, data: bytearray):
        def to_u32(data):
            return ctypes.c_uint32(
                data[0] |
                (data[1] << 8) |
                (data[2] << 16) |
                (data[3] << 24)).value
        
        return {
            "gfxPage": self.get_symbol(to_u32(data[0:])).given_name,
            "gfxIndex": self.get_symbol(to_u32(data[4:])).given_name,
            "clut": self.get_symbol(to_u32(data[8:])).given_name,
            "collision": self.get_symbol(to_u32(data[12:])).given_name,
        }


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
