from segtypes.n64.palette import N64SegPalette


class PSXSegPalette(N64SegPalette):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
