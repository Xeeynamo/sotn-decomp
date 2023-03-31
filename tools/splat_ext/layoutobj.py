#!/usr/bin/python3

import json
import os
import sys
from typing import Optional
from pathlib import Path

sys.path.append(f"{os.getcwd()}/tools/n64splat")
sys.path.append(f"{os.getcwd()}/tools/splat_ext")
from util import options, log
from segtypes.n64.segment import N64Segment
import utils

item_size = 0xA  # sizeof(LayoutObject)


def parse_layoutobj(data: bytearray) -> list:
    count = int(len(data) / item_size)
    items = []
    for i in range(0, count):
        item = {
            "x": utils.to_s16(data[i * item_size + 0:]),
            "y": utils.to_s16(data[i * item_size + 2:]),
            "objectId": utils.to_s16(data[i * item_size + 4:]),
            "objectRoomIndex": utils.to_s16(data[i * item_size + 6:]),
            "subId": utils.to_s16(data[i * item_size + 8:]),
        }
        if item["x"] == -1 and item["y"] == -1:
            break
        items.append(item)
    return items


def serialize_layoutobj(content: str) -> bytearray:
    def align(value: int, align: int):
        return value + (value % align)

    def from_16(dst: bytearray, idx, value: int):
        dst[idx + 0] = value & 0xFF
        dst[idx + 1] = (value >> 8) & 0xFF

    obj = json.loads(content)
    item_count = len(obj)
    byte_size = align((item_count + 1) * item_size, 4)
    data = bytearray(byte_size)
    for i in range(0, item_count):
        item = obj[i]
        from_16(data, i * item_size + 0, item["x"])
        from_16(data, i * item_size + 2, item["y"])
        from_16(data, i * item_size + 4, item["objectId"])
        from_16(data, i * item_size + 6, item["objectRoomIndex"])
        from_16(data, i * item_size + 8, item["subId"])
    from_16(data, item_count * item_size + 0, -1)
    from_16(data, item_count * item_size + 2, -1)
    return data


class PSXSegLayoutobj(N64Segment):
    def __init__(self, rom_start, rom_end, type, name, vram_start, args, yaml):
        super().__init__(rom_start, rom_end, type, name, vram_start, args, yaml),

    def out_path(self) -> Optional[Path]:
        return options.opts.asset_path / self.dir / self.name

    def src_path(self) -> Optional[Path]:
        return options.opts.asset_path / self.dir / f"{self.name}.layoutobj.json"

    def split(self, rom_bytes):
        path = self.src_path()
        path.parent.mkdir(parents=True, exist_ok=True)

        data = parse_layoutobj(rom_bytes[self.rom_start:self.rom_end])
        with open(path, "w") as f:
            f.write(json.dumps(data, indent=4))


if __name__ == "__main__":
    input_file_name = sys.argv[1]
    output_file_name = sys.argv[2]

    with open(input_file_name, "r") as f_in:
        data = serialize_layoutobj(f_in.read())
        with open(output_file_name, "wb") as f_out:
            f_out.write(data)
