from itertools import zip_longest
from math import ceil
from typing import List, Tuple
from segtypes.n64.palette import N64SegPalette


# ABBBBBGG GGGRRRRR
def unpack_color(data):
    s = int.from_bytes(data[0:2], byteorder="little")

    r = s & 0x1F
    g = (s >> 5) & 0x1F
    b = (s >> 10) & 0x1F
    a = (s >> 15) * 0xFF

    r = ceil(0xFF * (r / 31))
    g = ceil(0xFF * (g / 31))
    b = ceil(0xFF * (b / 31))

    return r, g, b, a


def iter_in_groups(iterable, n, fillvalue=None):
    args = [iter(iterable)] * n
    return zip_longest(*args, fillvalue=fillvalue)


class PSXSegPalette(N64SegPalette):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

    def parse_palette(self, rom_bytes) -> List[Tuple[int, int, int, int]]:
        assert isinstance(self.rom_start, int)
        assert isinstance(self.rom_end, int)

        data = rom_bytes[self.rom_start : self.rom_end]
        palette = []

        for a, b in iter_in_groups(data, 2):
            palette.append(unpack_color([a, b]))

        return palette
