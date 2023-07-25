#!/usr/bin/python3

import json
import io
import os
import sys
from typing import Optional
from pathlib import Path

sys.path.append(f"{os.getcwd()}/tools/n64splat")
sys.path.append(f"{os.getcwd()}/tools/splat_ext")
from util import options, log
from segtypes.n64.segment import N64Segment
from util.symbols import spim_context
import utils


def raise_err(str):
    sys.stderr.write("\033[91merror: " + str + "\u001b[0m" + "\n")
    raise Exception(str)


def generate_assembly_layers(writer: io.BufferedWriter, name: str, content: str):
    obj = json.loads(content)

    layer_set = {}

    def get_int(myobj, name, min, max):
        value = myobj.get(name)
        if value == None:
            raise_err(f"expect '{name}' but found nothing\ncurrent object: {myobj}")
        if value < min:
            raise_err(f"expect '{name}' to be at least 0\ncurrent object: {myobj}")
        if value > max:
            raise_err(f"expect '{name}' to be less than {max}\ncurrent object: {myobj}")
        return value

    def get_bool(myobj, name):
        value = myobj.get(name)
        if value == None:
            raise_err(f"expect '{name}' but found nothing\ncurrent object: {myobj}")
        return value

    def get_str(myobj, name):
        value = myobj.get(name)
        if value == None:
            raise_err(f"expect '{name}' but found nothing\ncurrent object: {myobj}")
        return value

    def write_layer(layer):
        hash = json.dumps(layer)  # 🤮
        if hash in layer_set:
            return layer_set[hash]
        id = f"DATA_LAYER_{len(layer_set)}"
        layer_set[hash] = id

        writer.write(f".global {id}\n")
        writer.write(f"{id}:\n")
        if layer == None:
            writer.write(f"\t.word 0, 0, 0, 0\n")
        else:
            data = get_str(layer, "data")
            tiledef = get_str(layer, "tiledef")
            flags = (
                get_int(layer, "left", 0, 0x3F)
                | get_int(layer, "top", 0, 0x3F) << 6
                | get_int(layer, "right", 0, 0x3F) << 12
                | get_int(layer, "bottom", 0, 0x3F) << 18
                | get_int(layer, "scrollMode", 0, 15) << 24
                | (1 if get_bool(layer, "isSaveRoom") else 0) << 29
                | (1 if get_bool(layer, "isLoadingRoom") else 0) << 30
            )
            zPriority = get_int(layer, "zPriority", 0, 32768)  # s16 or u16?
            unkE = get_int(layer, "unkE", 0, 255)
            unkF = get_int(layer, "unkF", 0, 255)
            writer.write(f"\t.word {data}, {tiledef}, 0x{flags:08X}\n")
            writer.write(f"\t.short 0x{zPriority:04X}\n")
            writer.write(f"\t.byte 0x{unkE:02X}, 0x{unkF:02X}\n")
        return id

    writer.write(".section .data\n")
    write_layer(None)
    buf = ""
    for room in obj:
        fgSym = write_layer(room.get("fg"))
        bgSym = write_layer(room.get("bg"))
        buf += f".word {fgSym}, {bgSym}\n"
    writer.write(f".global g_TileLayers\n")  # TODO: symbol name hardcoded 🤮
    writer.write(f"g_TileLayers:\n{buf}")


class PSXSegLayers(N64Segment):
    def __init__(self, rom_start, rom_end, type, name, vram_start, args, yaml):
        super().__init__(rom_start, rom_end, type, name, vram_start, args, yaml),

    def out_path(self) -> Optional[Path]:
        return options.opts.asset_path / self.dir / self.name

    def src_path(self) -> Optional[Path]:
        return options.opts.asset_path / self.dir / f"{self.name}.layers.json"

    def split(self, rom_bytes):
        path = self.src_path()
        path.parent.mkdir(parents=True, exist_ok=True)

        data = self.parse_layers(rom_bytes[self.rom_start : self.rom_end])
        with open(path, "w") as f:
            f.write(json.dumps(data, indent=4))

    def get_symbol(self, offset):
        if offset == 0:
            return 0

        symbol = super().get_symbol(offset)
        if symbol == None or symbol.given_name == None:
            return f"D_{offset:08X}"
        return symbol.given_name

    def parse_layers(self, data: bytearray):
        err = Exception(f"unable to decode '{self.name}'")
        roomCount = 0
        ram_start = self.vram_start
        ram_end = self.vram_start + self.rom_end - self.rom_start
        roomOff = len(data) - 8
        if roomOff < 0:
            log.error(f"data for '{self.name}' is to small")

        # Since we do not know beforehand how many rooms there are (we do, but
        # we want it to be automatic), this algo performs validation, room
        # count and defines exactly where is the starting LayerDef and
        # the starting RoomDef. This is possible because the list of LayerDef
        # always comes right before RoomDef and it has a different structure.
        layerDefOffsets = set({})
        roomDefStart = ram_start
        while True:
            fgPtr = utils.to_u32(data[roomOff:])
            bgPtr = utils.to_u32(data[roomOff + 4 :])
            if (
                bgPtr < 0x80180000
                or fgPtr >= 0x801E0000
                or bgPtr < 0x80180000
                or fgPtr >= 0x801E0000
                or bgPtr >= ram_end
                or fgPtr >= ram_end
            ):
                log.error(
                    f"data for '{self.name}' does not describe a set of room layers"
                )
                raise err
            if fgPtr < ram_start or bgPtr < ram_start:
                min_start = min(fgPtr, bgPtr)
                log.error(
                    f"data for '{self.name}' needs to start at least from {min_start}"
                )
                raise err
            layerDefOffsets.add(fgPtr)
            layerDefOffsets.add(bgPtr)
            roomCount += 1

            roomDefStart = max(roomDefStart, max(fgPtr, bgPtr))
            if ram_start + roomOff - 16 == roomDefStart:
                break

            roomOff -= 8
            if roomOff <= 0:
                log.error(
                    f"data for '{self.name}' needs to start at least from {min_start}"
                )
                raise err

        # Creates a dictionary of layers, so we can re-use them when a layer is
        # used by multiple rooms.
        layerPool = {}
        for off in layerDefOffsets:
            layerDefData = data[off - ram_start :]
            dataOff = utils.to_u32(layerDefData[0:])
            tiledefOff = utils.to_u32(layerDefData[4:])
            flags = utils.to_u32(layerDefData[8:])
            if dataOff != 0 or tiledefOff != 0 or flags != 0:
                layerPool[off] = {
                    "data": self.get_symbol(dataOff),
                    "tiledef": self.get_symbol(tiledefOff),
                    "left": flags & 0x3F,
                    "top": (flags >> 6) & 0x3F,
                    "right": (flags >> 12) & 0x3F,
                    "bottom": (flags >> 18) & 0x3F,
                    "scrollMode": (flags >> 24) & 0x1F,
                    "isSaveRoom": ((flags >> 24) & 0x20) != 0,
                    "isLoadingRoom": ((flags >> 24) & 0x40) != 0,
                    "zPriority": utils.to_u16(layerDefData[12:]),
                    "unkE": utils.to_u8(layerDefData[14:]),
                    "unkF": utils.to_u8(layerDefData[15:]),
                }
            else:
                layerPool[off] = None

        # NOTE: I am not sure if LayerDef{0, 0, 0, 0, 0, 0} comes always first
        # or it is just a coincidence due to the fact the first room of the
        # two stage I analalysed always contains an empty bg??
        rooms = []
        for i in range(0, roomCount):
            room = {}
            fg = layerPool[utils.to_u32(data[roomOff:])]
            if fg != None:
                room["fg"] = fg
            bg = layerPool[utils.to_u32(data[roomOff + 4 :])]
            if bg != None:
                room["bg"] = bg
            rooms.append(room)
            roomOff += 8

        return rooms


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
        name = get_file_name(input_file_name)
        with open(output_file_name, "w") as f_out:
            generate_assembly_layers(f_out, name, f_in.read())
