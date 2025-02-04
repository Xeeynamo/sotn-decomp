#!/usr/bin/env python3

import argparse
import io, hashlib, hmac
import json
import os
import png
import sys
from math import ceil
from typing import Optional
from pathlib import Path
import n64img.image


sys.path.append(f"{os.getcwd()}/tools/splat_ext")
from splat.util import options, log
from splat.segtypes.segment import Segment
import utils

max_width = 256
max_height = 256


# Take account of duplicate sprites, but only when they are consecutive.
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


# Take account of duplicate sprites by analysing all the PNGs to cross-reference
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


def encode_spritesheet(writer, name: str, content: str, optimized: bool) -> str:
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
        if info["planes"] != 1 or (info["bitdepth"] != 8 and info["bitdepth"] != 4):
            return f"'{file_name}' must be an indexed image"
        if len(palette) > 16:
            return f"'{file_name}' palette must be of 16 colors or less but found {len(palette)} colors instead"

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


def read_palette(file_name, offset):
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

    with open(file_name, "rb") as f:
        f.seek(offset, 0)
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


def decode_spritesheet(out_path, data: bytearray, start: int, palette) -> list:
    def extract_sprite(output_file_name, data, w, h, pal):
        img: n64img.image.Image = n64img.image.CI4(data, w, h)
        img.little_endian = True
        img.palette = pal
        img.write(output_file_name)

    # This is hardcoded based on where BIN/RIC.BIN and BIN/ARC_F.BIN are loaded
    vram_start = 0x8013C000

    items = []
    while True:
        raw_off = utils.to_u32(data[start + len(items) * 4 :])
        if raw_off < vram_start:
            break
        off = raw_off - vram_start
        name = os.path.normpath(f"{out_path}_{len(items)}.png")
        sprite_data = data[off:]
        w = sprite_data[0]
        h = sprite_data[1]
        print(f"size: ({w}, {h})")
        item = {"x": sprite_data[2], "y": sprite_data[3], "name": name}

        sprite_byte_count = int((w * h + 1) / 2)
        padding = 4 - (sprite_byte_count & 3)
        if padding == 2:
            padding_data = utils.to_u16(sprite_data[4 + sprite_byte_count :])
            if padding_data != 0:
                item["padding"] = padding_data

        items.append(item)

        extract_sprite(name, sprite_data[4:], w, h, palette)
    return items


class PSXSegSpritesheet(Segment):
    def __init__(self, rom_start, rom_end, type, name, vram_start, args, yaml):
        super().__init__(rom_start, rom_end, type, name, vram_start, args, yaml),

    def out_path(self) -> Optional[Path]:
        return options.opts.asset_path / self.dir / self.name

    def src_path(self) -> Optional[Path]:
        return options.opts.asset_path / self.dir / f"{self.name}.spritesheet.json"

    def split(self, rom_bytes):
        path = self.src_path()
        path.parent.mkdir(parents=True, exist_ok=True)

        pal = read_palette(self.args[0], 0x40000 + self.args[1] * 0x20)
        sprites_def = decode_spritesheet(
            self.out_path(), rom_bytes, self.rom_start, pal
        )
        with open(self.src_path(), "w") as f:
            f.write(json.dumps(sprites_def, indent=4))


if __name__ == "__main__":

    def get_file_name(full_path):
        file_name = os.path.basename(full_path)
        exts = os.path.splitext(file_name)
        if len(exts) > 1 and len(exts[1]) > 0:
            return get_file_name(exts[0])
        return exts[0]

    parser = argparse.ArgumentParser(description="Manipulate a spritesheet for modding")
    subparser = parser.add_subparsers(dest="command")

    encode_parser = subparser.add_parser(
        "encode",
        description="Pack spritesheet by encoding them into a single assemblable file.",
    )
    encode_parser.add_argument(
        "spritesheet_json",
        type=str,
        help="The JSON file that ocntains the spritesheet info (eg. 'assets/ric/richter.spritesheet.json').",
    )
    encode_parser.add_argument(
        "output_path",
        type=str,
        help="File path where to store the assemblable file that will contain just raw binary data.",
    )

    decode_parser = subparser.add_parser(
        "decode",
        description="From a binary file, decode the spritesheet and export it as individual PNGs",
    )
    decode_parser.add_argument(
        "bin_path",
        type=str,
        help="Path of the binary file containing the spritesheet data (e.g. 'BIN/RIC.BIN' or 'BIN/ARC_F.BIN')",
    )
    decode_parser.add_argument(
        "output",
        type=str,
        help="Path where all the data will be extracted. Must be a directory.",
    )
    decode_parser.add_argument(
        "name",
        type=str,
        help="Give a comprehensive name to the unpacked spritesheet",
    )
    decode_parser.add_argument(
        "pal_path",
        type=str,
        help="File path that contains the embedded palette",
    )
    decode_parser.add_argument(
        "pal_idx",
        type=int,
        help="Index of the palette (offset = 0x40000 + pal_idx * 0x20)",
    )

    args = parser.parse_args()
    if args.command == "encode":
        with open(args.spritesheet_json) as f_in:
            data = f_in.read()
        with open(args.output_path, "w") as f_out:
            name = get_file_name(args.spritesheet_json)
            err = encode_spritesheet(f_out, name, data, False)
            if err != None:
                log.error(err)
                raise Exception(err)
    elif args.command == "decode":
        if not Path(args.output).is_dir():
            raise Exception(f"'{args.output}' not a directory")

        with open(args.pal_path, "rb") as f_in:
            pal = read_palette(args.pal_path, 0x40000 + args.pal_idx * 0x20)

        with open(args.bin_path, "rb") as f_in:
            data = f_in.read()
        out_dir = os.path.join(args.output, args.name)
        sprites_def = decode_spritesheet(out_dir, data, 0x20, pal)

        out_file = os.path.join(args.output, f"{args.name}.spritesheet.json")
        with open(out_file, "w") as f:
            f.write(json.dumps(sprites_def, indent=4))
