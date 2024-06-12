from splat.segtypes.n64.ci4 import N64SegCi4


class PSXSegCi4(N64SegCi4):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.n64img.little_endian = True
