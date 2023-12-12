import n64img.image

from segtypes.n64.i4 import N64SegI4


class PSXSegI4(N64SegI4):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.n64img.little_endian = True
