#!/usr/bin/python3


# Parses game assets based on a config file. Config file needs to be in tools/splat_ext
# and named {something}_config.json, where {something} is what you're extracting.
# In that file is a member "struct" which is the structure you're extracting, which should
# match the C struct. "fields" holds the names to use for the bits of any bit fields.
# The names are ordered as 1 << {i} where i is the index in "fields".
# Hopefully the existing _config.json files are enough examples.
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


def get_serializer(dataType: str):
    match dataType:
        case "str_ptr":
            return utils.from_ptr_str
        case "bool":
            return utils.from_bool
        case "s8":
            return utils.from_s8
        case "u8":
            return utils.from_u8
        case "s16":
            return utils.from_16
        case "u16":
            return utils.from_16
        case "s32":
            return utils.from_s32
        case "u32":
            return utils.from_u32
        case _:
            print(f"Failed to find serializer for {dataType}")


def get_parser_and_size(dataType: str):
    match dataType:
        case "str_ptr":
            return (utils.to_ptr_str, 4)
        case "bool":
            return (utils.to_bool, 1)
        case "s8":
            return (utils.to_s8, 1)
        case "u8":
            return (utils.to_u8, 1)
        case "s16":
            return (utils.to_s16, 2)
        case "u16":
            return (utils.to_u16, 2)
        case "s32":
            return (utils.to_s32, 4)
        case "u32":
            return (utils.to_u32, 4)
        case _:
            print(f"Failed to find parser for {dataType}")


def serialize_asset(content: str, asset_config: str) -> bytearray:
    obj = json.loads(content)
    config = json.loads(asset_config)
    item_count = len(obj)
    serialized_data = bytearray()
    for i in range(0, item_count):
        item = obj[i]
        for entry, entryType in config["struct"].items():
            serializer = get_serializer(entryType)
            json_value = item[entry]
            # Lists are from fields, so we need to go back to the config to repack the bits from fields
            if type(json_value) is list:
                field_def = config["fields"][entry]
                packed_value = 0
                for i, field_name in enumerate(field_def):
                    if field_name in json_value:
                        packed_value += 1 << i
                serialized_data += serializer(packed_value)
            # Anything else can go straight to serializer
            else:
                serialized_data += serializer(item[entry])

    return serialized_data


class PSXSegAssets(N64Segment):
    def __init__(self, rom_start, rom_end, type, name, vram_start, args, yaml):
        super().__init__(rom_start, rom_end, type, name, vram_start, args, yaml),

    def out_path(self) -> Optional[Path]:
        return options.opts.asset_path / self.dir / self.name

    def src_path(self) -> Optional[Path]:
        return options.opts.asset_path / self.dir / f"{self.name}.json"

    def split(self, rom_bytes):
        path = self.src_path()
        path.parent.mkdir(parents=True, exist_ok=True)

        data = self.parse_asset(rom_bytes[self.rom_start : self.rom_end], rom_bytes)
        with open(path, "w") as f:
            f.write(json.dumps(data, indent=4))

    def parse_asset(self, data: bytearray, rom: bytearray) -> list:
        def get_ptr_data(src_ptr_data):
            return rom[
                utils.to_u32(src_ptr_data) - (self.vram_start - self.rom_start) :
            ]

        config_file_name = f"tools/splat_ext/{self.name}_config.json"
        with open(config_file_name, "r") as config_in:
            config_json = config_in.read()
        config = json.loads(config_json)

        item_size = sum(get_parser_and_size(x)[1] for x in config["struct"].values())
        count = int(len(data) / item_size)
        expected_data_size = count * item_size

        if len(data) != expected_data_size:
            log.write(
                f"data for '{self.name}' is {expected_data_size - len(data)} too long. Data might look incorrect.",
                status="warn",
            )

        items = []
        for i in range(0, count):
            item_data = data[i * item_size :][:item_size]
            item = {
                # debugging stuff
                "id": i,
                "id_hex": hex(i)[2:].upper(),
                "ram_addr": hex(self.vram_start + i * item_size)[2:].upper(),
                "name_resolved": utils.sotn_menu_name_to_str(
                    get_ptr_data(item_data[0x00:])
                ),
            }
            if "desc_addr" in config["struct"]:
                item["desc_resolved"] = utils.sotn_menu_desc_to_str(
                    get_ptr_data(item_data[0x04:])
                )
            data_pointer = 0
            for entry, entryType in config["struct"].items():
                parser, dataSizeBytes = get_parser_and_size(entryType)
                parsed_value = parser(item_data[data_pointer:])
                if entry in config["fields"]:
                    field_def = config["fields"][entry]
                    parsed_fields = []
                    for i, field_name in enumerate(field_def):
                        if parsed_value & (1 << i):
                            parsed_fields.append(field_name)
                    item[entry] = parsed_fields
                else:
                    item[entry] = parsed_value
                data_pointer += dataSizeBytes
            items.append(item)
        return items


if __name__ == "__main__":
    input_file_name = sys.argv[1]
    output_file_name = sys.argv[2]
    config_file_name = input_file_name.replace(".json", "_config.json")
    config_file_name = config_file_name.replace("assets/dra", "tools/splat_ext")
    with open(config_file_name, "r") as config_in:
        config_json = config_in.read()

    with open(input_file_name, "r") as f_in:
        data = serialize_asset(f_in.read(), config_json)
        with open(output_file_name, "wb") as f_out:
            f_out.write(data)
