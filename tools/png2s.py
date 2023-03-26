#!/usr/bin/python3

import argparse
import png


def convert(in_file, out_file_bitmap, name_bitmap, out_file_pal, name_pal, is_append):
    def encode_pal(dst, idx, palette):
        for i in range(0, len(palette)):
            color = palette[i]
            r = color[0]
            g = color[1]
            b = color[2]
            a = 0x8000 if color[3] >= 64 else 0x0000
            c = (r >> 3) | ((g >> 3) << 5) | ((b >> 3) << 10) | a
            dst[idx + i * 2 + 0] = c & 0xFF
            dst[idx + i * 2 + 1] = (c >> 8) & 0xFF

    def encode_bitmap(data):
        out = bytearray(int(len(data) / 2))
        for i in range(0, len(out)):
            out[i] = data[i * 2 + 0]
            out[i] |= data[i * 2 + 1] << 4
        return out

    mode = "a" if is_append else "w"
    img = png.Reader(in_file).read()
    data = encode_bitmap(bytearray().join(img[2]))

    info = img[3]
    if info["planes"] != 1:
        return f"'{in_file}' must be an indexed image"

    palette = info["palette"]
    if len(palette) > 16:
        return f"'{in_file}' palette must be of 16 colors or less but found {len(palette)} colors instead"

    with open(out_file_bitmap, mode) as f_out:
        f_out.write(f".section .data\n")
        f_out.write(f".global {name_bitmap}\n")
        f_out.write(f"{name_bitmap}:\n")
        for x in data:
            f_out.write(f".byte 0x{x:02X}\n")
        f_out.write("\n")

    pal_data = bytearray(0x10 * 2)
    encode_pal(pal_data, 0, palette)
    with open(out_file_pal, mode) as f_out:
        f_out.write(f".section .data\n")
        f_out.write(f".global {name_pal}\n")
        f_out.write(f"{name_pal}:\n")
        f_out.write(f".short 0x{pal_data[0x01]:02X}{pal_data[0x00]:02X}\n")
        f_out.write(f".short 0x{pal_data[0x03]:02X}{pal_data[0x02]:02X}\n")
        f_out.write(f".short 0x{pal_data[0x05]:02X}{pal_data[0x04]:02X}\n")
        f_out.write(f".short 0x{pal_data[0x07]:02X}{pal_data[0x06]:02X}\n")
        f_out.write(f".short 0x{pal_data[0x09]:02X}{pal_data[0x08]:02X}\n")
        f_out.write(f".short 0x{pal_data[0x0B]:02X}{pal_data[0x0A]:02X}\n")
        f_out.write(f".short 0x{pal_data[0x0D]:02X}{pal_data[0x0C]:02X}\n")
        f_out.write(f".short 0x{pal_data[0x0F]:02X}{pal_data[0x0E]:02X}\n")
        f_out.write(f".short 0x{pal_data[0x11]:02X}{pal_data[0x10]:02X}\n")
        f_out.write(f".short 0x{pal_data[0x13]:02X}{pal_data[0x12]:02X}\n")
        f_out.write(f".short 0x{pal_data[0x15]:02X}{pal_data[0x14]:02X}\n")
        f_out.write(f".short 0x{pal_data[0x17]:02X}{pal_data[0x16]:02X}\n")
        f_out.write(f".short 0x{pal_data[0x19]:02X}{pal_data[0x18]:02X}\n")
        f_out.write(f".short 0x{pal_data[0x1B]:02X}{pal_data[0x1A]:02X}\n")
        f_out.write(f".short 0x{pal_data[0x1D]:02X}{pal_data[0x1C]:02X}\n")
        f_out.write(f".short 0x{pal_data[0x1F]:02X}{pal_data[0x1E]:02X}\n")
        f_out.write("\n")

    return None


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="convert a PNG to an assemblable GNU-friendly data file"
    )
    parser.add_argument("input")
    parser.add_argument("output_bmp")
    parser.add_argument("name_bmp")
    parser.add_argument("output_pal")
    parser.add_argument("name_pal")
    args = parser.parse_args()

    err = convert(
        args.input,
        args.output_bmp,
        args.name_bmp,
        args.output_pal,
        args.name_pal,
        False,
    )
    if err:
        raise Exception(err)
