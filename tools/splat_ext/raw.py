print("RAWRAWRAWRAW")

import subprocess

from pathlib import Path
from typing import Optional

from segtypes.n64.segment import N64Segment
from segtypes.n64.rgba16 import N64SegRgba16
from segtypes.n64.i4 import N64SegI4

from pathlib import Path
from typing import Optional
from segtypes.n64.segment import N64Segment
from util import options, log


class PSXSegRaw(N64Segment):
    def __init__(self, rom_start, rom_end, type, name, vram_start, args, yaml):
        super().__init__(rom_start, rom_end, type, name, vram_start, args, yaml),

    def out_path(self) -> Optional[Path]:
        return options.opts.asset_path / self.dir / f"{self.name}"

    def split(self, rom_bytes):
        path = self.out_path()
        print(f"PATH: {path}")
        path.parent.mkdir(parents=True, exist_ok=True)

        with open(path, "wb") as f:
            f.write(rom_bytes[self.rom_start:self.rom_end])
