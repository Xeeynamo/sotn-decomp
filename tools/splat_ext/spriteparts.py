#!/usr/bin/python3

import json
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


def serialize_spriteparts(content: str) -> bytearray:
    def align(value: int, align: int):
        return value + (value % align)

    def from_16(dst: bytearray, idx, value: int):
        dst[idx + 0] = value & 0xFF
        dst[idx + 1] = (value >> 8) & 0xFF

    obj = json.loads(content)
    item_count = len(obj)
    byte_size = align(item_count * item_size + 2, 4)

    data = bytearray(byte_size)
    from_16(data, 0, item_count)
    for i in range(0, item_count):
        item = obj[i]
        from_16(data, 2 + i * item_size + 0, item["flags"])
        from_16(data, 2 + i * item_size + 2, item["offsetx"])
        from_16(data, 2 + i * item_size + 4, item["offsety"])
        from_16(data, 2 + i * item_size + 6, item["width"])
        from_16(data, 2 + i * item_size + 8, item["height"])
        from_16(data, 2 + i * item_size + 10, item["clut"])
        from_16(data, 2 + i * item_size + 12, item["tileset"])
        from_16(data, 2 + i * item_size + 14, item["left"])
        from_16(data, 2 + i * item_size + 16, item["top"])
        from_16(data, 2 + i * item_size + 18, item["right"])
        from_16(data, 2 + i * item_size + 20, item["bottom"])
    return data


class PSXSegSpriteparts(N64Segment):
    def __init__(self, rom_start, rom_end, type, name, vram_start, args, yaml):
        super().__init__(rom_start, rom_end, type, name, vram_start, args, yaml),

    def out_path(self) -> Optional[Path]:
        return options.opts.asset_path / self.dir / self.name

    def src_path(self) -> Optional[Path]:
        return options.opts.asset_path / self.dir / f"{self.name}.spriteparts.json"

    def split(self, rom_bytes):
        path = self.src_path()
        path.parent.mkdir(parents=True, exist_ok=True)

        data = parse_spriteparts(rom_bytes[self.rom_start : self.rom_end])
        with open(path, "w") as f:
            f.write(json.dumps(data, indent=4))


if __name__ == "__main__":
    input_file_name = sys.argv[1]
    output_file_name = sys.argv[2]

    with open(input_file_name, "r") as f_in:
        data = serialize_spriteparts(f_in.read())
        with open(output_file_name, "wb") as f_out:
            f_out.write(data)
