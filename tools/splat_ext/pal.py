from splat.util import options, log
from splat.segtypes.n64.i4 import N64SegI4
from splat.segtypes.n64.rgba16 import N64SegRgba16
from splat.segtypes.segment import Segment
from typing import Optional
from pathlib import Path


class PSXSegPal(Segment):
    def __init__(self, rom_start, rom_end, type, name, vram_start, args, yaml):
        super().__init__(rom_start, rom_end, type, name, vram_start, args, yaml),

    def out_path(self) -> Optional[Path]:
        return options.opts.asset_path / self.dir / self.name

    def src_path(self) -> Optional[Path]:
        return options.opts.asset_path / self.dir / f"{self.name}.palbin"

    def split(self, rom_bytes):
        path = self.src_path()
        path.parent.mkdir(parents=True, exist_ok=True)
        with open(path, "wb") as f:
            f.write(rom_bytes[self.rom_start : self.rom_end])
