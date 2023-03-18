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

item_size = 0x34  # sizeof(Equipment)


def serialize_equipment(content: str) -> bytearray:
    obj = json.loads(content)
    item_count = len(obj)
    serialized_data = bytearray()
    for i in range(0, item_count):
        item = obj[i]
        serialized_data += utils.from_ptr_str(item["name_addr"])
        serialized_data += utils.from_ptr_str(item["desc_addr"])
        serialized_data += utils.from_16(item["attack"])
        serialized_data += utils.from_16(item["defense"])
        serialized_data += utils.from_16(item["element"])
        serialized_data += utils.from_u8(item["damageScale"])
        serialized_data += utils.from_u8(item["weaponId"])
        serialized_data += utils.from_16(item["unk10"])
        serialized_data += utils.from_u8(item["playerAnim"])
        serialized_data += utils.from_u8(item["unk13"])
        serialized_data += utils.from_u8(item["unk14"])
        serialized_data += utils.from_u8(item["lockDuration"])
        serialized_data += utils.from_16(item["chainable"])
        serialized_data += utils.from_u8(item["specialMove"])
        serialized_data += utils.from_bool(item["isConsumable"])
        serialized_data += utils.from_u8(item["enemyInvincibilityFrames"])
        serialized_data += utils.from_u8(item["unk1B"])
        serialized_data += utils.from_16(item["unk1C"])
        serialized_data += utils.from_16(item["unk1E"])
        serialized_data += utils.from_16(item["unk20"])
        serialized_data += utils.from_16(item["unk22"])
        serialized_data += utils.from_16(item["mpUsage"])
        serialized_data += utils.from_16(item["stunFrames"])
        serialized_data += utils.from_16(item["hitType"])
        serialized_data += utils.from_16(item["hitEffect"])
        serialized_data += utils.from_16(item["menuIcon"])
        serialized_data += utils.from_16(item["menuPalette"])
        serialized_data += utils.from_16(item["criticalRate"])
        serialized_data += utils.from_16(item["unk32"])

    expected_data_size = item_count * item_size
    assert (len(serialized_data) == expected_data_size)

    return serialized_data


class PSXSegEquipment(N64Segment):
    def __init__(self, rom_start, rom_end, type, name, vram_start, args, yaml):
        super().__init__(rom_start, rom_end, type, name, vram_start, args, yaml),

    def out_path(self) -> Optional[Path]:
        return options.opts.asset_path / self.dir / self.name

    def src_path(self) -> Optional[Path]:
        return options.opts.asset_path / self.dir / f"{self.name}.equipment.json"

    def split(self, rom_bytes):
        path = self.src_path()
        path.parent.mkdir(parents=True, exist_ok=True)

        data = self.parse_equipment(
            rom_bytes[self.rom_start:self.rom_end], rom_bytes)
        with open(path, "w") as f:
            f.write(json.dumps(data, indent=4))

    def parse_equipment(self, data: bytearray, rom: bytearray) -> list:
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
                "attack": utils.to_s16(item_data[0x08:]),
                "defense": utils.to_s16(item_data[0x0A:]),
                "element": utils.to_u16(item_data[0x0C:]),
                "damageScale": utils.to_u8(item_data[0x0E:]),
                "weaponId": utils.to_u8(item_data[0x0F:]),
                "unk10": utils.to_u16(item_data[0x10:]),
                "playerAnim": utils.to_u8(item_data[0x12:]),
                "unk13": utils.to_u8(item_data[0x13:]),
                "unk14": utils.to_u8(item_data[0x14:]),
                "lockDuration": utils.to_u8(item_data[0x15:]),
                "chainable": utils.to_u16(item_data[0x16:]),
                "specialMove": utils.to_u8(item_data[0x18:]),
                "isConsumable": utils.to_bool(item_data[0x19:]),
                "enemyInvincibilityFrames": utils.to_u8(item_data[0x1A:]),
                "unk1B": utils.to_u8(item_data[0x1B:]),
                "unk1C": utils.to_u16(item_data[0x1C:]),
                "unk1E": utils.to_u16(item_data[0x1E:]),
                "unk20": utils.to_u16(item_data[0x20:]),
                "unk22": utils.to_u16(item_data[0x22:]),
                "mpUsage": utils.to_u16(item_data[0x24:]),
                "stunFrames": utils.to_u16(item_data[0x26:]),
                "hitType": utils.to_u16(item_data[0x28:]),
                "hitEffect": utils.to_u16(item_data[0x2A:]),
                "menuIcon": utils.to_u16(item_data[0x2C:]),
                "menuPalette": utils.to_u16(item_data[0x2E:]),
                "criticalRate": utils.to_u16(item_data[0x30:]),
                "unk32": utils.to_u16(item_data[0x32:]),
            }
            items.append(item)
        return items


if __name__ == "__main__":
    input_file_name = sys.argv[1]
    output_file_name = sys.argv[2]

    with open(input_file_name, "r") as f_in:
        data = serialize_equipment(f_in.read())
        with open(output_file_name, "wb") as f_out:
            f_out.write(data)
