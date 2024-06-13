from pathlib import Path
from typing import Optional
from splat.segtypes.n64.segment import N64Segment
from splat.util import options, log


class PSXSegCmp(N64Segment):
    def __init__(self, rom_start, rom_end, type, name, vram_start, args, yaml):
        super().__init__(
            rom_start, rom_end, type, name, vram_start, args=args, yaml=yaml
        ),
        self.name = self.get_symbol_name()

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
        return f"D_{self.vram_start:X}"

    def out_path(self) -> Optional[Path]:
        return options.opts.asset_path / self.dir / self.name

    def cmp_path(self) -> Optional[Path]:
        return f"{self.out_path()}.bin"

    def dec_path(self) -> Optional[Path]:
        return f"{self.out_path()}.dec"

    def split(self, rom_bytes):
        path = self.out_path()
        path.parent.mkdir(parents=True, exist_ok=True)

        # we are forced to also write the compressed file as we do not have
        # a matching compression algorithm
        data = rom_bytes[self.rom_start : self.rom_end]
        with open(self.cmp_path(), "wb") as f:
            f.write(data)

        dec = SOTNDecompress(data).decompress_data()
        with open(self.dec_path(), "wb") as f:
            f.write(dec)

    def decompress(data):
        return data


class SOTNDecompress:
    def __init__(self, compressed_data):
        self.compressed_data = compressed_data

    def decompress_data(self):
        dictionary = self.compressed_data[0:8]
        self.read_flag = 0
        self.write_flag = 0
        self.src_pos = 8
        self.dst_pos = 0
        self.decompressed_data = []

        while True:
            op = self.read_nibble()
            if op == 0:
                count = self.read_nibble() << 4
                count += self.read_nibble() + 0x13
                while count > 0:
                    self.write_nibble(0)
                    count -= 1
            elif op == 1:
                self.write_nibble(self.read_nibble())
            elif op == 2:
                ch = self.read_nibble()
                self.write_nibble(ch)
                self.write_nibble(ch)
            elif op == 3:
                self.write_nibble(self.read_nibble())
                self.write_nibble(self.read_nibble())
            elif op == 4:
                self.write_nibble(self.read_nibble())
                self.write_nibble(self.read_nibble())
                self.write_nibble(self.read_nibble())
            elif op == 5:
                ch = self.read_nibble()
                count = self.read_nibble() + 3
                while count > 0:
                    self.write_nibble(ch)
                    count -= 1
            elif op == 6:
                count = self.read_nibble() + 3
                while count > 0:
                    self.write_nibble(0)
                    count -= 1
            elif op == 15:
                return bytearray(self.decompressed_data)
            else:
                ch = dictionary[op - 7]
                if ch == 0x10:
                    self.write_nibble(ch & 15)
                elif ch == 0x20:
                    self.write_nibble(ch & 15)
                    self.write_nibble(ch & 15)
                elif ch == 0x60:
                    count = (ch & 15) + 3
                    while count > 0:
                        self.write_nibble(0)
                        count -= 1

    def read_nibble(self):
        if self.read_flag == 0:
            self.read_flag = 1
            ch = (self.compressed_data[self.src_pos] >> 4) & 15
        else:
            self.read_flag = 0
            ch = self.compressed_data[self.src_pos] & 15
            self.src_pos += 1
        return ch

    def write_nibble(self, ch):
        if self.write_flag == 0:
            self.write_flag = 1
            self.decompressed_data.append(ch)
        else:
            self.write_flag = 0
            self.decompressed_data[self.dst_pos] += ch << 4
            self.dst_pos += 1
