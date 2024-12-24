#!/usr/bin/env python3

import argparse
import png


def get_encoded_image(file_name: str) -> bytearray:
    img = png.Reader(file_name).read()
    width = img[0]
    height = img[1]
    rows = img[2]
    info = img[3]
    palette = info["palette"]
    if width != 256:
        return f"'{file_name}' width must be 256 but found {width} instead"
    if height != 128:
        return f"'{file_name}' height must be 128 but found {height} instead"
    if info["planes"] != 1 or info["bitdepth"] != 8:
        return f"'{file_name}' must be an indexed image"
    if len(palette) != 16:
        return f"'{file_name}' palette must be of 16 colors but found {len(palette)} colors instead"

    data = bytearray((width * height) >> 1)
    idx = 0
    nibble = False
    for row in rows:
        for ch in row:
            if nibble == False:
                nibble = True
                data[idx] = ch
            else:
                nibble = False
                data[idx] |= ch << 4
                idx += 1
    return data


parser = argparse.ArgumentParser(description="convert 4bpp PNGs into binary")
parser.add_argument("input")
parser.add_argument("output")

if __name__ == "__main__":
    args = parser.parse_args()
    data = get_encoded_image(args.input)
    with open(args.output, "wb") as f_out:
        f_out.write(data)
