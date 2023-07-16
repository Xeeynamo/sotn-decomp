#!/usr/bin/python3

#Note: This file was created by bismurphy. It is effectively the same as
#equipment.py, just with the current best-known state of the accessory
#struct subbed into the two locations where it comes up.
#Longer term, would be cool if equipment and accessories could be parsed
#by the same Python script, rather than tons of duplicate code.
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

item_size = 0x20  # sizeof(Accessory)


def serialize_accessory(content: str) -> bytearray:
    obj = json.loads(content)
    item_count = len(obj)
    serialized_data = bytearray()
    for i in range(0, item_count):
        item = obj[i]
        serialized_data += utils.from_ptr_str(item["name_addr"])
        serialized_data += utils.from_ptr_str(item["desc_addr"])
        serialized_data += utils.from_16(item["attBonus"])
        serialized_data += utils.from_16(item["defBonus"])
        serialized_data += utils.from_s8(item["strBonus"])
        serialized_data += utils.from_s8(item["conBonus"])
        serialized_data += utils.from_s8(item["intBonus"])
        serialized_data += utils.from_s8(item["lckBonus"])
        serialized_data += utils.from_u32(item["unk10"])
        serialized_data += utils.from_u32(item["unk14"])
        serialized_data += utils.from_16(item["menuIcon"])
        serialized_data += utils.from_16(item["menuPalette"])
        serialized_data += utils.from_u32(item["unk1C"])

    expected_data_size = item_count * item_size
    assert (len(serialized_data) == expected_data_size)

    return serialized_data


class PSXSegAccessory(N64Segment):
    def __init__(self, rom_start, rom_end, type, name, vram_start, args, yaml):
        super().__init__(rom_start, rom_end, type, name, vram_start, args, yaml),

    def out_path(self) -> Optional[Path]:
        return options.opts.asset_path / self.dir / self.name

    def src_path(self) -> Optional[Path]:
        return options.opts.asset_path / self.dir / f"{self.name}.accessory.json"

    def split(self, rom_bytes):
        path = self.src_path()
        path.parent.mkdir(parents=True, exist_ok=True)

        data = self.parse_accessory(
            rom_bytes[self.rom_start:self.rom_end], rom_bytes)
        with open(path, "w") as f:
            f.write(json.dumps(data, indent=4))

    def parse_accessory(self, data: bytearray, rom: bytearray) -> list:
        def get_ptr_data(src_ptr_data):
            return rom[utils.to_u32(src_ptr_data) - (self.vram_start - self.rom_start):]

        count = int(len(data) / item_size)
        expected_data_size = count * item_size
        if len(data) != expected_data_size:
            log.write(
                f"data for '{self.name}' is {expected_data_size - len(data)} too long. Data might look incorrect.", status="warn")

        items = []
        for i in range(0, count):
            item_data = data[i * item_size:][:item_size]
            item = {
                # debugging stuff
                "id": i,
                "id_hex": hex(i)[2:].upper(),
                "ram_addr": hex(self.vram_start + i * item_size)[2:].upper(),
                "name_resolved": utils.sotn_menu_name_to_str(get_ptr_data(item_data[0x00:])),
                "desc_resolved": utils.sotn_menu_desc_to_str(get_ptr_data(item_data[0x04:])),
                # debugging stuff ends

                "name_addr": utils.to_ptr_str(item_data[0x00:]),
                "desc_addr": utils.to_ptr_str(item_data[0x04:]),
                "attBonus": utils.to_s16(item_data[0x08:]),
                "defBonus": utils.to_s16(item_data[0x0A:]),
                "strBonus": utils.to_s8(item_data[0x0C:]),
                "conBonus": utils.to_s8(item_data[0x0D:]),
                "intBonus": utils.to_s8(item_data[0x0E:]),
                "lckBonus": utils.to_s8(item_data[0x0F:]),
                "unk10": utils.to_u32(item_data[0x10:]),
                "unk14": utils.to_u32(item_data[0x14:]),
                "menuIcon": utils.to_u16(item_data[0x18:]),
                "menuPalette": utils.to_u16(item_data[0x1A:]),
                "unk1C": utils.to_u32(item_data[0x1C:]),
            }
            items.append(item)
        return items


if __name__ == "__main__":
    input_file_name = sys.argv[1]
    output_file_name = sys.argv[2]

    with open(input_file_name, "r") as f_in:
        data = serialize_accessory(f_in.read())
        with open(output_file_name, "wb") as f_out:
            f_out.write(data)
