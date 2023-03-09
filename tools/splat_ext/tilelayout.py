import os
import sys
from util import options
from typing import Optional
from pathlib import Path

sys.path.append(f"{os.getcwd()}/{options.opts.extensions_path}")
from raw import PSXSegRaw

class PSXSegTilelayout(PSXSegRaw):
    pass

    def src_path(self) -> Optional[Path]:
        return options.opts.asset_path / self.dir / f"{self.name}.tilelayout.bin"
