#!/usr/bin/env python3

import os
import sys
from typing import Optional
from pathlib import Path


sys.path.append(f"{os.getcwd()}/tools/splat_ext")
from splat.util import options
from splat.segtypes.segment import Segment


class PSXSegAnimset(Segment):
    def __init__(self, rom_start, rom_end, type, name, vram_start, args, yaml):
        super().__init__(rom_start, rom_end, type, name, vram_start, args, yaml),

    def out_path(self) -> Optional[Path]:
        return options.opts.asset_path / self.dir / self.name

    def src_path(self) -> Optional[Path]:
        return options.opts.asset_path / self.dir / f"{self.name}.animset.json"

    def split(self, rom_bytes):
        return


if __name__ == "__main__":
    print("dummy")
    exit(1)
