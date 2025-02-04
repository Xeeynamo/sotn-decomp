from io import BufferedReader
from math import ceil
import os
from pathlib import Path
import sys
from typing import List, Optional, Tuple
import n64img
from splat.segtypes.segment import Segment
from splat.util import options, log

sys.path.append(f"{os.getcwd()}/tools/splat_ext")
from cmp import SOTNDecompress
from utils import log_fatal


class PSXSegCmpgfx(Segment):
    def __init__(self, rom_start, rom_end, type, name, vram_start, args, yaml):
        super().__init__(
            rom_start, rom_end, type, name, vram_start, args=args, yaml=yaml
        )

    # does splat provide this without extracting the symbols for every file?
    # this might become extremely inefficient over time.
    def get_symbol_name(self) -> str:
        expected_addr = f"0x{self.vram_start:X}"
        for symbol_addr_path in options.opts.symbol_addrs_paths:
            with open(symbol_addr_path) as f:
                for line in f:
                    if line.isspace():
                        continue
                    tokens = line.strip().split("=")
                    if len(tokens) < 2:
                        continue
                    addr = tokens[1].replace(";", "").strip()
                    if addr == expected_addr:
                        return tokens[0].strip()
        return None

    def out_path(self) -> Optional[Path]:
        return options.opts.asset_path / self.dir / self.name

    def cmp_path(self) -> Optional[Path]:
        return f"{self.out_path()}.gfxbin"

    def png_path(self) -> Optional[Path]:
        return f"{self.out_path()}.png"

    def split(self, rom_bytes):
        path = self.out_path()
        path.parent.mkdir(parents=True, exist_ok=True)

        # we are forced to also write the compressed file as we do not have
        # a matching compression algorithm to reconstruct the original file
        data = rom_bytes[self.rom_start : self.rom_end]
        with open(self.cmp_path(), "wb") as f:
            f.write(data)

        sotn_dec = SOTNDecompress(data)
        dec = sotn_dec.decompress_data()
        width = 128 if len(self.args) < 1 else self.args[0]
        height = 128 if len(self.args) < 2 else self.args[1]
        bpp = 4 if len(self.args) < 3 else self.args[2]
        pal_offset = 0 if len(self.args) < 4 else self.args[3]
        find_palette = len(self.args) >= 5
        expected_byte_len = width * height * bpp // 8
        if len(dec) != expected_byte_len:
            # the image decoding WILL fail
            # the tool will search for the real start of the compressed image
            # and report it to the user as an error
            actual_start = self.rom_start
            while actual_start < self.rom_end:
                actual_start += 4
                data = data[4:]
                dec = SOTNDecompress(data).decompress_data()
                if len(dec) == expected_byte_len:
                    log_fatal(
                        f"wrong cmpgfx start at 0x{self.rom_start:X}: "
                        + f"the real start is at 0x{actual_start:X}. Fix your YAML."
                    )
            log_fatal(f"cmpgfx at 0x{self.rom_start:X} is invalid")
        if bpp == 4:
            img = n64img.image.CI4(dec, width, height)
        elif bpp == 8:
            img = n64img.image.CI8(dec, width, height)
        else:
            log_fatal("unsupported bpp {bpp}")
        img.little_endian = True
        if find_palette:
            self.out_path().mkdir(parents=True, exist_ok=True)
            test_pal_off = pal_offset
            for i in range(256):
                img.palette = self.get_palette(rom_bytes, 1 << bpp, test_pal_off)
                img.write(os.path.join(self.out_path(), f"0x{test_pal_off:X}.png"))
                test_pal_off += 0x20
        img.palette = self.get_palette(rom_bytes, 1 << bpp, pal_offset)
        img.write(self.png_path())

        unused_data_delta = 0x80  # arbitrary number
        if sotn_dec.unprocessed_length() > unused_data_delta:
            off = self.rom_start + sotn_dec.last_processed_pos()
            off = ((off + 4 - 1) // 4) * 4
            log_fatal(f"unused data after cmpgfx at 0x{off:X}")

    def get_palette(self, rom_bytes, n_colors, pal_offset):
        if pal_offset == 0:
            return self.make_greyscale_palette()  # only 4bpp
        else:
            return self.read_palette(rom_bytes[pal_offset:], n_colors)

    def read_palette(self, data, n_colors) -> List[Tuple[int, int, int, int]]:
        def read_color(s) -> Tuple[int, int, int, int]:
            r = s & 0x1F
            g = (s >> 5) & 0x1F
            b = (s >> 10) & 0x1F
            a = (s >> 15) * 0xFF
            r = ceil(0xFF * (r / 31))
            g = ceil(0xFF * (g / 31))
            b = ceil(0xFF * (b / 31))
            return r, g, b, 255

        colors = []
        for i in range(n_colors):
            colors += [read_color(data[i * 2 + 0] | (data[i * 2 + 1] << 8))]
        return colors

    def make_greyscale_palette(self) -> List[Tuple[int, int, int, int]]:
        def generate_grey_color(intensity: int) -> Tuple[int, int, int, int]:
            return intensity, intensity, intensity, 255

        return [
            generate_grey_color(0x00),
            generate_grey_color(0x11),
            generate_grey_color(0x22),
            generate_grey_color(0x33),
            generate_grey_color(0x44),
            generate_grey_color(0x55),
            generate_grey_color(0x66),
            generate_grey_color(0x77),
            generate_grey_color(0x88),
            generate_grey_color(0x99),
            generate_grey_color(0xAA),
            generate_grey_color(0xBB),
            generate_grey_color(0xCC),
            generate_grey_color(0xDD),
            generate_grey_color(0xEE),
            generate_grey_color(0xFF),
        ]

    def decompress(data):
        return data
