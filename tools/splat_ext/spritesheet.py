#!/usr/bin/python3

import json
import os
import sys
from math import ceil
from typing import Optional
from pathlib import Path
import n64img.image

sys.path.append(f"{os.getcwd()}/tools/n64splat")
sys.path.append(f"{os.getcwd()}/tools/splat_ext")
from util import options, log
from segtypes.n64.segment import N64Segment
import utils

def serialize_spritesheet(content: str) -> bytearray:
    raise Exception("to-do")


class PSXSegSpritesheet(N64Segment):
    def __init__(self, rom_start, rom_end, type, name, vram_start, args, yaml):
        super().__init__(rom_start, rom_end, type, name, vram_start, args, yaml),

    def out_path(self) -> Optional[Path]:
        return options.opts.asset_path / self.dir / self.name

    def src_path(self) -> Optional[Path]:
        return options.opts.asset_path / self.dir / f"{self.name}.spritesheet.json"
    
    def split(self, rom_bytes):
        path = self.src_path()
        path.parent.mkdir(parents=True, exist_ok=True)

        data = self.parse_spritesheet(
            rom_bytes[self.rom_start:self.rom_end], rom_bytes)
        with open(path, "w") as f:
            f.write(json.dumps(data, indent=4))

    def read_palette(self):
        def read_color(f):
            s = int.from_bytes(f.read(2), byteorder='little')

            r = s & 0x1F
            g = (s >> 5) & 0x1F
            b = (s >> 10) & 0x1F
            a = (s >> 15) * 0xFF
            
            r = ceil(0xFF * (r / 31))
            g = ceil(0xFF * (g / 31))
            b = ceil(0xFF * (b / 31))

            return r, g, b, a
        
        src = self.args[0]
        off = self.args[1]
        with open(src, "rb") as f:
            f.seek(off, 0)
            return [
                read_color(f), read_color(f), read_color(f), read_color(f),
                read_color(f), read_color(f), read_color(f), read_color(f),
                read_color(f), read_color(f), read_color(f), read_color(f),
                read_color(f), read_color(f), read_color(f), read_color(f),
            ]

    def extract_sprite(self, output_file_name, data, w, h, pal):
        img: n64img.image.Image = n64img.image.CI4(data, w, h)
        img.little_endian = True
        img.palette = pal
        img.write(output_file_name)

    def parse_spritesheet(self, data: bytearray, rom: bytearray) -> list:
        i = 0
        items = []
        pal = self.read_palette()
        while True:
            raw_off = utils.to_u32(data[i * 4:])
            if raw_off < self.vram_start:
                break
            off = raw_off - self.vram_start
            name = os.path.normpath(f"{self.out_path()}_{i}.png")
            sprite_data = data[off:]
            items.append({
                "x": sprite_data[2],
                "y": sprite_data[3],
                "name": name
            })
            i += 1

            self.extract_sprite(name, sprite_data[4:], sprite_data[0], sprite_data[1], pal)
        return items


if __name__ == "__main__":
    input_file_name = sys.argv[1]
    output_file_name = sys.argv[2]

    with open(input_file_name, "r") as f_in:
        data = serialize_spritesheet(f_in.read())
        with open(output_file_name, "wb") as f_out:
            f_out.write(data)
