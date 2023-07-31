#!/usr/bin/python3

import io, hashlib, hmac
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


# Take account of duplciate sprites, but only when they are consecutive.
# This is the closest to the original algorithm used by the developers.
def make_syms_matching(obj):
    syms = []

    # Generate a list of unique sprites, merging duplicates
    i = 0
    prev_hash = None
    for item in obj:
        file_name = item["name"]
        if not os.path.exists(file_name):
            return syms, f"the file '{file_name}' does not exist"
        with open(file_name, "rb") as f:
            digest = hashlib.sha1(f.read(), usedforsecurity=False).digest()
        if digest == prev_hash:
            symbol_name = prev_symbol
        else:
            symbol_name = f"{name}_{i}"
            prev_hash = digest
            prev_symbol = symbol_name
        syms.append(symbol_name)
        i += 1
    return syms, None


# Take account of duplicate sprites by analising all the PNGs to cross-reference
# all of them. On RIC.BIN it saves around 4.3KB. This algorithm is not slower
# than the original one.
def make_syms_optimized(obj):
    syms = []

    # Generate a list of unique sprites, merging duplicates
    i = 0
    syms_hash = dict()
    for item in obj:
        file_name = item["name"]
        if not os.path.exists(file_name):
            return syms, f"the file '{file_name}' does not exist"
        with open(file_name, "rb") as f:
            digest = hashlib.sha1(f.read(), usedforsecurity=False).digest()
        symbol_name = syms_hash.get(digest)
        if symbol_name == None:
            symbol_name = f"{name}_{i}"
            syms_hash[digest] = symbol_name
        syms.append(symbol_name)
        i += 1
    return syms, None


def serialize_spritesheet(writer, name: str, content: str, optimized: bool) -> str:
    sym_name = f"g_{name}_spritesheet"
    obj = json.loads(content)
    syms, err = (
        make_syms_optimized(obj) if optimized == True else make_syms_matching(obj)
    )
    if err != None:  # check if error
        return err

    # Generate a list of unique sprites, merging duplicates
    i = 0
    syms_hash = dict()
    for item in obj:
        file_name = item["name"]
        if not os.path.exists(file_name):
            return f"the file '{file_name}' does not exist"
        with open(file_name, "rb") as f:
            digest = hashlib.sha1(f.read(), usedforsecurity=False).digest()
        symbol_name = syms_hash.get(digest)
        if symbol_name == None:
            symbol_name = f"{name}_{i}"
            syms_hash[digest] = symbol_name
        syms.append(symbol_name)
        i += 1

    # Create a list of sprites
    writer.write(".section .data\n")
    writer.write(f".global {sym_name}\n")
    writer.write(f"{sym_name}:\n")
    for i in range(0, len(obj)):
        writer.write(f".word {syms[i]}\n")

    # Write sprites
    i = 0
    syms_written = set()
    for item in obj:
        # Do not write duplicate sprites
        symbol_name = syms[i]
        i += 1
        if symbol_name in syms_written:
            continue
        syms_written.add(symbol_name)

        file_name = item["name"]
        xPivot = item["x"]
        yPivot = item["y"]

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
        writer.write(f"{symbol_name}:\n")
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
            if "padding" in item:
                padding_data = item["padding"]
            else:
                padding_data = 0
            writer.write(f".half {padding_data}\n")


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
            rom_bytes[self.rom_start : self.rom_end], rom_bytes
        )
        with open(path, "w") as f:
            f.write(json.dumps(data, indent=4))

    def read_palette(self):
        def read_color(f):
            s = int.from_bytes(f.read(2), byteorder="little")

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
                read_color(f),
                read_color(f),
                read_color(f),
                read_color(f),
                read_color(f),
                read_color(f),
                read_color(f),
                read_color(f),
                read_color(f),
                read_color(f),
                read_color(f),
                read_color(f),
                read_color(f),
                read_color(f),
                read_color(f),
                read_color(f),
            ]

    def extract_sprite(self, output_file_name, data, w, h, pal):
        img: n64img.image.Image = n64img.image.CI4(data, w, h)
        img.little_endian = True
        img.palette = pal
        img.write(output_file_name)

    def parse_spritesheet(self, data: bytearray, rom: bytearray) -> list:
        items = []
        pal = self.read_palette()
        while True:
            raw_off = utils.to_u32(data[len(items) * 4 :])
            if raw_off < self.vram_start:
                break
            off = raw_off - self.vram_start
            name = os.path.normpath(f"{self.out_path()}_{len(items)}.png")
            sprite_data = data[off:]
            w = sprite_data[0]
            h = sprite_data[1]
            item = {"x": sprite_data[2], "y": sprite_data[3], "name": name}

            sprite_byte_count = int((w * h + 1) / 2)
            padding = 4 - (sprite_byte_count & 3)
            if padding == 2:
                padding_data = utils.to_u16(sprite_data[4 + sprite_byte_count :])
                if padding_data != 0:
                    item["padding"] = padding_data

            items.append(item)

            self.extract_sprite(name, sprite_data[4:], w, h, pal)
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
            err = serialize_spritesheet(f_out, name, f_in.read(), False)
            if err != None:
                log.error(err)
                raise Exception(err)
