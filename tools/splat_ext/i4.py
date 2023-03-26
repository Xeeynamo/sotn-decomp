import n64img.image

from segtypes.n64.i4 import N64SegI4


class PSXSegI4(N64SegI4):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.n64img.little_endian = True

    def flip_endian(self, src):
        dst = bytearray(src)
        for i in range(0, len(dst)):
            ch = dst[i]
            dst[i] = (ch >> 4) | ((ch & 0xF) << 4)
        return dst

    def split(self, rom_bytes):
        super().split(rom_bytes)
