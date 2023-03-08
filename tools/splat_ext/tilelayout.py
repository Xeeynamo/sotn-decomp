import os
import sys
from util import options

sys.path.append(f"{os.getcwd()}/{options.opts.extensions_path}")
from raw import PSXSegRaw

class PSXSegTilelayout(PSXSegRaw):
    pass
