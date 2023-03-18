import n64img.image

from segtypes.n64.img import N64SegImg


class PSXSegI4(N64SegImg):
    def __init__(self, *args, **kwargs):
        kwargs["img_cls"] = n64img.image.I4
        super().__init__(*args, **kwargs)

    def flip_endian(self, src):
        dst = bytearray(src)
        for i in range(0, len(dst)):
            ch = dst[i]
            dst[i] = (ch >> 4) | ((ch & 0xF) << 4)
        return dst

    def split(self, rom_bytes):
        path = self.out_path()
        path.parent.mkdir(parents=True, exist_ok=True)

        assert isinstance(self.rom_start, int)
        assert isinstance(self.rom_end, int)

        self.n64img.data = self.flip_endian(
            rom_bytes[self.rom_start: self.rom_end])
        self.n64img.write(path)

        self.log(f"Wrote {self.name} to {path}")
