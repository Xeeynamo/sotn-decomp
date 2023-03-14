#!/usr/bin/python3

import ctypes
import json
import os
import sys
from typing import Optional
from pathlib import Path

sys.path.append(f"{os.getcwd()}/tools/n64splat")
sys.path.append(f"{os.getcwd()}/tools/splat_ext")
from util import options, log
from segtypes.n64.segment import N64Segment

item_size = 0x8  # sizeof(RoomHeader)


def serialize_roomdef(content: str) -> bytearray:
    obj = json.loads(content)
    item_count = len(obj)
    byte_size = item_count * item_size + 4
    data = bytearray(byte_size)
    for i in range(0, item_count):
        item = obj[i]
        data[i * item_size + 0] = item["left"]
        data[i * item_size + 1] = item["top"]
        data[i * item_size + 2] = item["right"]
        data[i * item_size + 3] = item["bottom"]
        data[i * item_size + 4] = item["tileLayoutId"]
        data[i * item_size + 5] = item["tilesetId"]
        data[i * item_size + 6] = item["objGfxId"]
        data[i * item_size + 7] = item["objLayoutId"]
    data[byte_size - 4] = 0x40  # marks the end of the room array
    return data


class PSXSegRoomdef(N64Segment):
    def __init__(self, rom_start, rom_end, type, name, vram_start, args, yaml):
        super().__init__(rom_start, rom_end, type, name, vram_start, args, yaml),

    def out_path(self) -> Optional[Path]:
        return options.opts.asset_path / self.dir / self.name

    def src_path(self) -> Optional[Path]:
        return options.opts.asset_path / self.dir / f"{self.name}.roomdef.json"

    def split(self, rom_bytes):
        path = self.src_path()
        path.parent.mkdir(parents=True, exist_ok=True)

        data = self.parse_roomdef(rom_bytes[self.rom_start:self.rom_end])
        with open(path, "w") as f:
            f.write(json.dumps(data, indent=4))

    def parse_roomdef(self, data: bytearray) -> list:

        count = int(len(data) / item_size)
        expected_data_size = count * item_size + 4
        if len(data) != expected_data_size:
            log.write(
                f"data for '{self.name}' is {expected_data_size - len(data)} too long. Data might look incorrect.", status="warn")

        items = []
        for i in range(0, count):
            if data[i * item_size + 0] == 64:
                log.write(
                    f"data for '{self.name}' includes the array terminator. Try reducing the size of the subsegment.", status="warn")
            item = {
                "left": data[i * item_size + 0],
                "top": data[i * item_size + 1],
                "right": data[i * item_size + 2],
                "bottom": data[i * item_size + 3],
                "tileLayoutId": data[i * item_size + 4],
                "tilesetId": data[i * item_size + 5],
                "objGfxId": data[i * item_size + 6],
                "objLayoutId": data[i * item_size + 7],
            }
            items.append(item)

        if data[count * item_size] != 64:
            log.write(
                f"data for '{self.name}' does not end with a terminator.", status="warn")

        return items


if __name__ == "__main__":
    input_file_name = sys.argv[1]
    output_file_name = sys.argv[2]

    with open(input_file_name, "r") as f_in:
        data = serialize_roomdef(f_in.read())
        with open(output_file_name, "wb") as f_out:
            f_out.write(data)
