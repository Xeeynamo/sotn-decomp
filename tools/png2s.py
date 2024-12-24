#!/usr/bin/env python3

import argparse
import json
import png
import os


def ensure_dir(file_path: str):
    dir_path = os.path.dirname(file_path)
    if not os.path.exists(dir_path):
        os.makedirs(dir_path)


def get_num(param: int | str | None) -> int:
    if not param:
        return 0
    if isinstance(param, int):
        return int(param)
    elif isinstance(param, str):
        if param.startswith("0x"):
            return int(param[2:], 16)
        else:
            return int(param)
    else:
        raise Exception(f"type '{type(param)}' for '{param}' unhandled")


def encode_from_png(
    in_file, out_file_bitmap, name_bitmap, out_file_pal, name_pal, is_append
):
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


def decode_to_png(bmp_name, png_name, x, y, w, h, bpp, stride, bmp_offset, pal):
    size = int(stride * h)
    with open(bmp_name, "rb") as f_bmp:
        f_bmp.seek(get_num(bmp_offset) + stride * y)
        bmp_data = f_bmp.read(size)

    pixels = []
    if bpp == 4:
        src = bmp_data
        x >>= 1
        for j in range(0, h):
            row = []
            for i in range(0, w >> 1):
                lo = src[x + i] & 15
                hi = src[x + i] >> 4
                row.extend([lo, hi])
            src = src[stride:]
            pixels.append(row)
    else:
        src = bmp_data
        for j in range(0, h):
            pixels.append(src[:w])
            src = src[w:]

    if pal:
        pal_name, pal_offset, alpha = pal
        with open(pal_name, "rb") as f_pal:
            f_pal.seek(get_num(pal_offset))
            pal_data = f_pal.read(0x20 if bpp == 4 else 0x200)
        palette = []
        for i in range(0, int(len(pal_data) / 2)):
            color = pal_data[i * 2] + pal_data[i * 2 + 1] * 256
            r = (color & 31) << 3
            g = ((color >> 5) & 31) << 3
            b = ((color >> 10) & 31) << 3
            r |= r >> 5  # enrich the colors by
            g |= g >> 5  # filling the lowest three bits
            b |= b >> 5  # with the upper bits
            a = 0 if color < 0x8000 and alpha == True else 255
            palette.append((r, g, b, a))
    else:
        if bpp == 4:
            palette = [(i * 16 + i, i * 16 + i, i * 16 + i) for i in range(16)]
        elif bpp == 8:
            palette = [(i, i, i) for i in range(0, 256)]

    with open(png_name, "wb") as f_png:
        writer = png.Writer(width=w, height=h, bitdepth=bpp, palette=palette)
        writer.write(f_png, pixels)
    return None


def decode_batch(input, source_dir, output):
    with open(input, "r") as f:
        config = json.load(f)

    source = os.path.join(source_dir, config["source"])
    clut = get_num(config["clut"])
    stride = get_num(config["stride"])
    for item in config["items"]:
        name = os.path.join(output, item["name"] + ".png")
        ensure_dir(name)

        if "palette" in item and "brute" not in item["palette"]:
            palette = item["palette"]
            if "source" in palette:
                pal_source = os.path.join(source_dir, palette["source"])
                offset = get_num(palette["offset"])
            else:
                pal_source = source
                offset = clut + get_num(palette["offset"]) * 0x20
            use_alpha = "alpha" in palette and palette["alpha"] == True
            pal = (pal_source, offset, use_alpha)
        else:
            pal = None

        err = decode_to_png(
            source,
            name,
            get_num(item["x"]) if "x" in item else 0,
            get_num(item["y"]) if "y" in item else 0,
            item["width"],
            item["height"],
            item["bpp"],
            stride,
            get_num(item["offset"]),
            pal,
        )

        if "palette" in item and "brute" in item["palette"]:
            for i in range(0, 256):
                err = decode_to_png(
                    source,
                    os.path.join(output, item["name"] + f"_{i}" + ".png"),
                    get_num(item["x"]) if "x" in item else 0,
                    get_num(item["y"]) if "y" in item else 0,
                    item["width"],
                    item["height"],
                    item["bpp"],
                    stride,
                    get_num(item["offset"]),
                    (source, clut + i * 0x20, False),
                )

        if err:
            return err
    return None


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="convert a PNG to an assemblable GNU-friendly data file"
    )
    subparsers = parser.add_subparsers(dest="command")

    encode_parser = subparsers.add_parser(
        "encode",
        description="Encode a PNG file and its palette into binary or assemblable data",
    )
    encode_parser.add_argument("input")
    encode_parser.add_argument("output_bmp")
    encode_parser.add_argument("name_bmp")
    encode_parser.add_argument("output_pal")
    encode_parser.add_argument("name_pal")

    decode_parser = subparsers.add_parser(
        "decode",
        description="Decode a binary file into a PNG file",
    )
    decode_parser.add_argument(
        "input",
        type=str,
        help="the binary file that contains the bitmap to decode as PNG",
    )
    decode_parser.add_argument("output", type=str, help="output name of the PNG")
    decode_parser.add_argument(
        "width", type=int, help="width in pixel of the expected PNG output"
    )
    decode_parser.add_argument(
        "height", type=int, help="height in pixel of the expected PNG output"
    )
    decode_parser.add_argument(
        "depth", type=int, choices=[4, 8], help="how many bits per pixel"
    )
    decode_parser.add_argument(
        "offset", help="source of the bitmap image to convert from"
    )
    decode_parser.add_argument(
        "-p",
        "--palette",
        nargs=3,
        metavar=("palette.bin", "offset", "alpha"),
        help="load palette from the specified file and a given offset",
    )

    bdecode_parser = subparsers.add_parser(
        "bdecode",
        description="Decode assets in batch using a configuration file",
    )
    bdecode_parser.add_argument("input", type=str, help="configuration file name")
    bdecode_parser.add_argument("source", type=str, help="location of original assets")
    bdecode_parser.add_argument("output", type=str, help="output directory")

    args = parser.parse_args()
    if args.command == "encode":
        err = encode_from_png(
            args.input,
            args.output_bmp,
            args.name_bmp,
            args.output_pal,
            args.name_pal,
            False,
        )
    elif args.command == "decode":
        stride = args.width
        if args.depth == 4:
            stride >>= 1
        err = decode_to_png(
            args.input,
            args.output,
            0,
            0,
            args.width,
            args.height,
            args.depth,
            stride,
            args.offset,
            args.palette,
        )
    elif args.command == "bdecode":
        err = decode_batch(args.input, args.source, args.output)
    if err:
        raise Exception(err)
