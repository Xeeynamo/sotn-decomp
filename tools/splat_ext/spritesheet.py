#!/usr/bin/python3

import json
import os
import png
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

max_width = 256
max_height = 256

def serialize_spritesheet(writer, name: str, content: str) -> str:
    obj = json.loads(content)
    
    writer.write(".section .data\n")
    writer.write(f".global D_8013C020\n") # TODO: symbol name hardcoded 🤮
    writer.write(f"D_8013C020:\n")
    for i in range(0, len(obj)):
        writer.write(f".word {name}_{i}\n")

    i = 0
    for item in obj:
        file_name = item["name"]
        xPivot = item["x"]
        yPivot = item["y"]
        if not os.path.exists(file_name):
            return f"the file '{file_name}' does not exist"
        img = png.Reader(file_name).read()
        width = img[0]
        height = img[1]
        rows = img[2]
        info = img[3]
        palette = info["palette"]
        if width >= max_width or height >= max_height:
            return f"size for '{file_name}' is {width}x{height} but it must be less than {max_width}x{max_height}"
        if (width & 3) != 0:
            return f"size for '{file_name}' is {width}x{height} but the width must be a multiple of 4"
        if info["planes"] != 1 or info["bitdepth"] != 8:
            return f"'{file_name}' must be an indexed image"
        if len(palette) != 16:
            return f"'{file_name}' palette must be of 16 colors but found {len(palette)} colors instead"

        bytes_per_row = int(width / 2)
        padding = 4 - (int((width * height + 1) / 2) & 3)
        writer.write(f"{name}_{i}:\n")
        writer.write(f".byte {width}\n")
        writer.write(f".byte {height}\n")
        writer.write(f".byte {xPivot}\n")
        writer.write(f".byte {yPivot}\n")
        for row in rows:
            line = ""
            for x in range(0, bytes_per_row):
                c = (row[x * 2 + 0] & 0xF) | ((row[x * 2 + 1] & 0xF) << 4)
                line += f",{c}"
            writer.write(f".byte {line[1:]}\n")
        if padding == 2:
            writer.write(f".half 0\n")
        i += 1

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
    def get_file_name(full_path):
        file_name = os.path.basename(full_path)
        exts = os.path.splitext(file_name)
        if len(exts) > 1 and len(exts[1]) > 0:
            return get_file_name(exts[0])
        return exts[0]
    
    input_file_name = sys.argv[1]
    output_file_name = sys.argv[2]

    with open(input_file_name, "r") as f_in:
        with open(output_file_name, "w") as f_out:
            name = get_file_name(input_file_name)
            err = serialize_spritesheet(f_out, name, f_in.read())
            if err != None:
                log.error(err)
                raise Exception(err)
