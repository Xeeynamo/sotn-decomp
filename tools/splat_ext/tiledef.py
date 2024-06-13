#!/usr/bin/python3

import ctypes
import json
import io
import os
import sys
from typing import Optional
from pathlib import Path


sys.path.append(f"{os.getcwd()}/tools/splat_ext")
from splat.util import options
from splat.segtypes.n64.segment import N64Segment
from splat.util.symbols import spim_context
import utils


def generate_assembly_tiledef(
    writer: io.BufferedWriter, base_dir: str, name: str, content: str
):
    def incbin(writer: io.BufferedWriter, path: str):
        with open(path, "rb") as f:
            for ch in f.read():
                writer.write(f".byte {int(ch)}\n")

    obj = json.loads(content)
    symbol_name = obj["name"]
    gfxPage = obj["gfxPage"]
    gfxIndex = obj["gfxIndex"]
    clut = obj["clut"]
    collision = obj["collision"]

    writer.write(".section .data\n")
    writer.write(f"gfxPage:\n")
    incbin(writer, f"{base_dir}/{gfxPage}")
    writer.write(f"gfxIndex:\n")
    incbin(writer, f"{base_dir}/{gfxIndex}")
    writer.write(f"clut:\n")
    incbin(writer, f"{base_dir}/{clut}")
    writer.write(f"collision:\n")
    incbin(writer, f"{base_dir}/{collision}")

    writer.write(f".global {symbol_name}\n")
    writer.write(f"{symbol_name}:\n")
    writer.write(f".word gfxPage, gfxIndex, clut, collision\n")


class PSXSegTiledef(N64Segment):
    def __init__(self, rom_start, rom_end, type, name, vram_start, args, yaml):
        super().__init__(rom_start, rom_end, type, name, vram_start, args, yaml),

    def out_path(self) -> Optional[Path]:
        return options.opts.asset_path / self.dir / f"{self.name}"

    def src_path(self) -> Optional[Path]:
        return options.opts.asset_path / self.dir / f"{self.name}.tiledef.json"

    def split(self, rom_bytes):
        if len(self.args) != 1:
            utils.log_fatal(f"unable to determine the real symbol name for {self.name}")
        symbol_name = self.args[0]

        out_file_name = self.src_path()
        out_file_name.parent.mkdir(parents=True, exist_ok=True)

        header_data = rom_bytes[self.rom_end - 0x10 : self.rom_end]
        gfxPage = utils.to_u32(header_data[0:]) - self.vram_start
        gfxIndex = utils.to_u32(header_data[4:]) - self.vram_start
        clut = utils.to_u32(header_data[8:]) - self.vram_start
        collision = utils.to_u32(header_data[12:]) - self.vram_start
        header_start = self.rom_end - 0x10 - self.rom_start

        expected_start = min(gfxPage, min(gfxIndex, min(clut, collision)))
        if expected_start != 0:
            expected_start += self.rom_start
            actual_start = self.rom_start
            utils.log_fatal(
                f"{self.name} should start from 0x{expected_start:X} but got 0x{actual_start:X}\n"
                f"- [0x{expected_start:X}, tiledef, {self.name}]"
            )

        descriptor = {
            "name": symbol_name,
            "gfxPage": f"{self.name}.page.bin",
            "gfxIndex": f"{self.name}.tile.bin",
            "clut": f"{self.name}.clut.bin",
            "collision": f"{self.name}.col.bin",
        }

        file_sizes = [
            gfxIndex - gfxPage,
            clut - gfxIndex,
            collision - clut,
            header_start - collision,
        ]

        raw_data = rom_bytes[self.rom_start : self.rom_end]
        out_dir = options.opts.asset_path / self.dir
        with open(out_dir / descriptor["gfxPage"], "wb") as f:
            f.write(raw_data[gfxPage:][: file_sizes[0]])
        with open(out_dir / descriptor["gfxIndex"], "wb") as f:
            f.write(raw_data[gfxIndex:][: file_sizes[1]])
        with open(out_dir / descriptor["clut"], "wb") as f:
            f.write(raw_data[clut:][: file_sizes[2]])
        with open(out_dir / descriptor["collision"], "wb") as f:
            f.write(raw_data[collision:][: file_sizes[3]])

        with open(out_file_name, "w") as f:
            f.write(json.dumps(descriptor, indent=4))


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
        base_path = os.path.dirname(input_file_name)
        name = get_file_name(input_file_name)
        with open(output_file_name, "w") as f_out:
            generate_assembly_tiledef(f_out, base_path, name, f_in.read())
