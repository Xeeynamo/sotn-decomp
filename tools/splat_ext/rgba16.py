import n64img.image

from segtypes.n64.rgba16 import N64SegRgba16


class PSXSegRgba16(N64SegRgba16):
    def __init__(self, *args, **kwargs):
        kwargs["img_cls"] = n64img.image.RGBA16
        super().__init__(*args, **kwargs)
