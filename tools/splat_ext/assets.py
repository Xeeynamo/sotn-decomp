#!/usr/bin/env python3


# Parses game assets based on a config file. Config file needs to be in tools/splat_ext
# and named {something}_config.json, where {something} is what you're extracting.
# In that file is a member "struct" which is the structure you're extracting, which should
# match the C struct. "fields" holds the names to use for the bits of any bit fields.

# Fields can be defined in two different ways. If a struct entry is purely fields,
# you define the names of each member of the field, least-significant-bit first.
# See enemydefs_config.json for an example.
# The names are ordered as 1 << {i} where i is the index in "fields".
# For things that mix bitfields or pack multiple multi-bit values into a single int,
# define it as a dictionary. These are most-significant-bit first, since usually
# bits packed in with smaller ints will have the bits at the top of the byte.
import json
import os
import sys
from typing import Optional
from pathlib import Path


sys.path.append(f"{os.getcwd()}/tools/splat_ext")
from splat.util import options, log
from splat.segtypes.segment import Segment
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
    raw_json_data = json.loads(content)
    config = json.loads(asset_config)
    symbol_name = raw_json_data["symbol_name"]
    asset_data = raw_json_data["asset_data"]
    item_count = len(asset_data)
    serialized_data = bytearray()
    for i in range(0, item_count):
        item = asset_data[i]
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
            elif type(json_value) is dict:
                field_def = config["fields"][entry]
                packed_bitstring = ""
                bit_index = 0
                for i, field in enumerate(json_value.items()):
                    field_name, subvalue = field
                    field_bitsize = field_def[field_name]
                    # If the field is a bit flag
                    if field_bitsize == 1:
                        if subvalue == True:
                            packed_bitstring += "1"
                        elif subvalue == False:
                            packed_bitstring += "0"
                        else:
                            print("Problem serializing asset")
                            exit(1)
                        bit_index += 1
                    # If the field is an integer
                    else:
                        subvalue_bits = bin(subvalue)[2:].zfill(field_bitsize)
                        packed_bitstring += subvalue_bits
                        bit_index += field_bitsize
                packed_value = int(packed_bitstring, 2)
                serialized_data += serializer(packed_value)
            # Anything else can go straight to serializer
            else:
                serialized_data += serializer(item[entry])
    # Take serialized data (raw bytes) and turn into asm file
    asm_output = ""
    asm_output += ".section .data\n\n"
    asm_output += f".global {symbol_name}\n\n"
    asm_output += f"{symbol_name}:\n"
    for databyte in serialized_data:
        asm_output += f".byte {int(databyte)}\n"
    return asm_output


class PSXSegAssets(Segment):
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
        json_output = {}
        json_output["symbol_name"] = self.args[0]
        json_output["asset_data"] = data
        with open(path, "w") as f:
            f.write(json.dumps(json_output, indent=4))

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

        items = []
        for i in range(0, count):
            item_data = data[i * item_size :][:item_size]
            item = {
                # debugging stuff
                "id": i,
                "id_hex": hex(i)[2:].upper(),
                "ram_addr": hex(self.vram_start + i * item_size)[2:].upper(),
            }
            if "name_addr" in config["struct"]:
                item["name_resolved"] = utils.sotn_menu_name_to_str(
                    get_ptr_data(item_data[0x00:])
                )
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
                    if type(field_def) == list:
                        parsed_fields = []
                        for i, field_name in enumerate(field_def):
                            if parsed_value & (1 << i):
                                parsed_fields.append(field_name)
                        item[entry] = parsed_fields
                    elif type(field_def) == dict:
                        # Take the parsed_value and split it into smaller pieces
                        # according to the field_def. First, get the bits.
                        # Use [2:] to remove the '0b' that comes by default
                        value_bits = bin(parsed_value)[2:]
                        # Pad with zeros on the left, to make us use all the bits
                        value_bits = value_bits.zfill(dataSizeBytes * 8)
                        # Now, iterate through the entries in the field_def.
                        bit_index = 0
                        parsed_fields = {}
                        for i, field in enumerate(field_def.items()):
                            field_name, field_bitcount = field
                            # If the field is a bit flag
                            if field_bitcount == 1:
                                bit_state = (
                                    True if value_bits[bit_index] == "1" else False
                                )
                                parsed_fields[field_name] = bit_state
                                bit_index += 1
                            # If the field is an integer
                            else:
                                sub_value = int(
                                    value_bits[bit_index : bit_index + field_bitcount],
                                    2,
                                )
                                parsed_fields[field_name] = sub_value
                                bit_index += field_bitcount
                        # Make sure we've gone through and used all bits in the field
                        assert bit_index == dataSizeBytes * 8
                        item[entry] = parsed_fields
                else:
                    item[entry] = parsed_value
                data_pointer += dataSizeBytes
            items.append(item)
        return items


if __name__ == "__main__":
    input_file_name = sys.argv[1]
    output_file_name = sys.argv[2]

    pathless_input_filename = input_file_name.split("/")[-1]
    config_file_name = pathless_input_filename.replace(".json", "_config.json")
    config_file_name = "tools/splat_ext/" + config_file_name
    with open(config_file_name, "r") as config_in:
        config_json = config_in.read()

    with open(input_file_name, "r") as f_in:
        data = serialize_asset(f_in.read(), config_json)
        with open(output_file_name, "w") as f_out:
            f_out.write(data)
