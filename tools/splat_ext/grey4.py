import n64img.image
from typing import List, Tuple

from segtypes.n64.img import N64SegImg


def generate_grey_palette() -> List[Tuple[int, int, int, int]]:
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


class PSXSegGrey4(N64SegImg):
    def __init__(self, *args, **kwargs):
        kwargs["img_cls"] = n64img.image.CI4
        super().__init__(*args, **kwargs)

    def split(self, rom_bytes):
        path = self.out_path()
        path.parent.mkdir(parents=True, exist_ok=True)

        assert isinstance(self.rom_start, int)
        assert isinstance(self.rom_end, int)

        self.n64img.palette = generate_grey_palette()
        self.n64img.data = rom_bytes[self.rom_start : self.rom_end]
        self.n64img.little_endian = True
        self.n64img.write(path)

        self.log(f"Wrote {self.name} to {path}")
