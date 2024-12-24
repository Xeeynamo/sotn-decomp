#!/usr/bin/env python3

import argparse
from typing import List, Tuple
import n64img.image
import os
import png
import sys
from pathlib import Path

clut_indices = [
    0x8000 * 0 + 0x5C00 + 0x20 * 0,
    0x8000 * 0 + 0x5C00 + 0x20 * 1,
    0x8000 * 0 + 0x7C00 + 0x20 * 0,
    0x8000 * 0 + 0x7C00 + 0x20 * 1,
    0x8000 * 1 + 0x5C00 + 0x20 * 0,
    0x8000 * 1 + 0x5C00 + 0x20 * 1,
    0x8000 * 1 + 0x7C00 + 0x20 * 0,
    0x8000 * 1 + 0x7C00 + 0x20 * 1,
    0x8000 * 2 + 0x5C00 + 0x20 * 0,
    0x8000 * 2 + 0x5C00 + 0x20 * 1,
    0x8000 * 2 + 0x7C00 + 0x20 * 0,
    0x8000 * 2 + 0x7C00 + 0x20 * 1,
    0x8000 * 3 + 0x5C00 + 0x20 * 0,
    0x8000 * 3 + 0x5C00 + 0x20 * 1,
    0x8000 * 3 + 0x7C00 + 0x20 * 0,
    0x8000 * 3 + 0x7C00 + 0x20 * 1,
]


def get_clut_pos_start(pal_index: int):
    return clut_indices[int(pal_index % 16)] + 0x40 * int(pal_index / 16)


def ensure_dir_exists(file_path):
    path = Path(os.path.dirname(file_path))
    path.mkdir(parents=True, exist_ok=True)


def encode(input_base: str, output_file: str):
    def unroll_rows(rows):
        list_of_rows = []
        for row in rows:
            list_of_rows.append(row)
        return list_of_rows

    def encode_quadrant(dst: bytearray, start: int, rows, quad: int):
        assert quad >= 0 and quad < 4
        start_row = 128 if (quad & 2) == 2 else 0
        start_col = 128 if (quad & 1) == 1 else 0

        y = 0
        for row in rows[start_row:]:
            row = row[start_col:]
            for x in range(0, 64):
                c = (row[x * 2 + 0] & 0xF) | ((row[x * 2 + 1] & 0xF) << 4)
                dst[start + y * 0x40 + x] = c
            y += 1

    def encode_image(dst: bytearray, idx: int, file_name: str):
        img = png.Reader(file_name).read()
        width = img[0]
        height = img[1]
        rows = img[2]
        info = img[3]
        palette = info["palette"]
        if width != 256:
            return f"'{file_name}' width must be 256 but found {width} instead"
        if height != 240 and height != 256:
            return f"'{file_name}' height must be 240 or 256 but found {height} instead"
        if info["planes"] != 1 or info["bitdepth"] != 8:
            return f"'{file_name}' must be an indexed image"
        if len(palette) != 16:
            return f"'{file_name}' palette must be of 16 colors but found {len(palette)} colors instead"

        row_list = unroll_rows(rows)
        encode_quadrant(dst, (idx * 4 + 0) * 0x2000, row_list, 0)
        encode_quadrant(dst, (idx * 4 + 1) * 0x2000, row_list, 1)
        encode_quadrant(dst, (idx * 4 + 2) * 0x2000, row_list, 2)
        encode_quadrant(dst, (idx * 4 + 3) * 0x2000, row_list, 3)
        return None

    def encode_pal(dst, idx, palette):
        for i in range(0, 16):
            r = palette[i * 4 + 0]
            g = palette[i * 4 + 1]
            b = palette[i * 4 + 2]
            a = 0 if palette[i * 4 + 3] >= 64 else 0x8000
            c = (r >> 3) | ((g >> 3) << 5) | ((b >> 3) << 10) | a
            dst[idx + i * 2 + 0] = c & 0xFF
            dst[idx + i * 2 + 1] = (c >> 8) & 0xFF

    def encode_clut(dst: bytearray, file_name: str):
        img = png.Reader(file_name).read()
        width = img[0]
        height = img[1]
        rows = img[2]
        info = img[3]
        if width != 16:
            return f"'{file_name}' width must be 16 but found {width} instead"
        if height != 256:
            return f"'{file_name}' width must be 256 but found {height} instead"
        if info["planes"] != 4 or info["bitdepth"] != 8:
            return f"'{file_name}' must be a 32-bit RGBA image"

        row_list = unroll_rows(rows)
        for i in range(0, 16):
            encode_pal(dst, clut_indices[0x0] + 0x40 * i, row_list[i * 16 + 0x0])
            encode_pal(dst, clut_indices[0x1] + 0x40 * i, row_list[i * 16 + 0x1])
            encode_pal(dst, clut_indices[0x2] + 0x40 * i, row_list[i * 16 + 0x2])
            encode_pal(dst, clut_indices[0x3] + 0x40 * i, row_list[i * 16 + 0x3])
            encode_pal(dst, clut_indices[0x4] + 0x40 * i, row_list[i * 16 + 0x4])
            encode_pal(dst, clut_indices[0x5] + 0x40 * i, row_list[i * 16 + 0x5])
            encode_pal(dst, clut_indices[0x6] + 0x40 * i, row_list[i * 16 + 0x6])
            encode_pal(dst, clut_indices[0x7] + 0x40 * i, row_list[i * 16 + 0x7])
            encode_pal(dst, clut_indices[0x8] + 0x40 * i, row_list[i * 16 + 0x8])
            encode_pal(dst, clut_indices[0x9] + 0x40 * i, row_list[i * 16 + 0x9])
            encode_pal(dst, clut_indices[0xA] + 0x40 * i, row_list[i * 16 + 0xA])
            encode_pal(dst, clut_indices[0xB] + 0x40 * i, row_list[i * 16 + 0xB])
            encode_pal(dst, clut_indices[0xC] + 0x40 * i, row_list[i * 16 + 0xC])
            encode_pal(dst, clut_indices[0xD] + 0x40 * i, row_list[i * 16 + 0xD])
            encode_pal(dst, clut_indices[0xE] + 0x40 * i, row_list[i * 16 + 0xE])
            encode_pal(dst, clut_indices[0xF] + 0x40 * i, row_list[i * 16 + 0xF])

        return None

    data = bytearray(0x40000)
    for i in range(0, 8):
        err = encode_image(data, i, f"{input_base}_{i}.png")
        if err != None:
            return err

    err = encode_clut(data, f"{input_base}_clut.png")
    if err != None:
        return err

    with open(output_file, "wb") as f_out:
        f_out.write(data)
    return None


def decode(input_file: str, output_base: str, pal_idx: int):
    def copy_quadrant(dst: bytearray, src: bytes, h: int, src_idx: int, dst_quad: int):
        src = src[src_idx * 128 * 64 :][: 128 * 64]
        dst_idx = (dst_quad & 1) * 64 + int(dst_quad / 2) * 128 * 128
        for y in range(0, h):
            for x in range(0, 64):
                ch = src[y * 0x40 + x]
                dst[dst_idx + y * 128 + x] = ((ch & 0xF) << 4) | (ch >> 4)

    def generate_grey_palette() -> List[Tuple[int, int, int, int]]:
        def generate_grey_color(intensity: int) -> Tuple[int, int, int, int]:
            return intensity, intensity, intensity, 255

        return [
            generate_grey_color(0x00),
            generate_grey_color(0x11),
            generate_grey_color(0x22),
            generate_grey_color(0x33),
            generate_grey_color(0x44),
            generate_grey_color(0x55),
            generate_grey_color(0x66),
            generate_grey_color(0x77),
            generate_grey_color(0x88),
            generate_grey_color(0x99),
            generate_grey_color(0xAA),
            generate_grey_color(0xBB),
            generate_grey_color(0xCC),
            generate_grey_color(0xDD),
            generate_grey_color(0xEE),
            generate_grey_color(0xFF),
        ]

    def generate_tileset(output_file: str, src: bytes, idx: int, pal, has_clut: bool):
        img: n64img.image.Image = n64img.image.CI4(None, 0, 0)
        img.width = 256
        img.height = 240 if has_clut else 256
        img.palette = pal
        img.data = bytearray(img.size())
        hhh = 112 if has_clut else 128
        copy_quadrant(img.data, src, 128, idx * 4 + 0, 0)
        copy_quadrant(img.data, src, 128, idx * 4 + 1, 1)
        copy_quadrant(img.data, src, hhh, idx * 4 + 2, 2)
        copy_quadrant(img.data, src, hhh, idx * 4 + 3, 3)
        ensure_dir_exists(output_file)
        img.write(output_file)

    def copy_pal(dst: bytearray, pal_idx: int, src: bytes):
        start = pal_idx * 32
        for i in range(0, 16):
            c = src[i * 2 + 0] | (src[i * 2 + 1] << 8)
            c = (
                ((c & 0x1F) << 11)
                | ((c & 0x3E0) << 1)
                | ((c & 0x7C00) >> 9)
                | ((c ^ 0x8000) >> 15)
            )
            dst[start + i * 2 + 1] = c & 0xFF
            dst[start + i * 2 + 0] = (c >> 8) & 0xFF

    def decode_color(data: bytearray) -> Tuple[int, int, int, int]:
        c = data[0] | (data[1] << 8)
        a = ((c ^ 0x8000) >> 15) * 255
        return (c & 0x1F) << 3, ((c >> 5) & 0x1F) << 3, ((c >> 10) & 0x1F) << 3, a

    def decode_palette(data: bytearray) -> List[Tuple[int, int, int, int]]:
        palette = []
        for i in range(0, 16):
            palette.append(decode_color(data[i * 2 :]))
        return palette

    def generate_clut(output_file: str, src: bytes):
        img: n64img.image.Image = n64img.image.RGBA16(None, 16, 256)
        img.data = bytearray(img.size())
        for i in range(0, 16):
            copy_pal(img.data, i * 0x10 + 0x0, src[clut_indices[0x0] + 0x40 * i :])
            copy_pal(img.data, i * 0x10 + 0x1, src[clut_indices[0x1] + 0x40 * i :])
            copy_pal(img.data, i * 0x10 + 0x2, src[clut_indices[0x2] + 0x40 * i :])
            copy_pal(img.data, i * 0x10 + 0x3, src[clut_indices[0x3] + 0x40 * i :])
            copy_pal(img.data, i * 0x10 + 0x4, src[clut_indices[0x4] + 0x40 * i :])
            copy_pal(img.data, i * 0x10 + 0x5, src[clut_indices[0x5] + 0x40 * i :])
            copy_pal(img.data, i * 0x10 + 0x6, src[clut_indices[0x6] + 0x40 * i :])
            copy_pal(img.data, i * 0x10 + 0x7, src[clut_indices[0x7] + 0x40 * i :])
            copy_pal(img.data, i * 0x10 + 0x8, src[clut_indices[0x8] + 0x40 * i :])
            copy_pal(img.data, i * 0x10 + 0x9, src[clut_indices[0x9] + 0x40 * i :])
            copy_pal(img.data, i * 0x10 + 0xA, src[clut_indices[0xA] + 0x40 * i :])
            copy_pal(img.data, i * 0x10 + 0xB, src[clut_indices[0xB] + 0x40 * i :])
            copy_pal(img.data, i * 0x10 + 0xC, src[clut_indices[0xC] + 0x40 * i :])
            copy_pal(img.data, i * 0x10 + 0xD, src[clut_indices[0xD] + 0x40 * i :])
            copy_pal(img.data, i * 0x10 + 0xE, src[clut_indices[0xE] + 0x40 * i :])
            copy_pal(img.data, i * 0x10 + 0xF, src[clut_indices[0xF] + 0x40 * i :])
        img.write(output_file)

    with open(input_file, "rb") as f_in:
        src_data = f_in.read()

    max_tilesets = 8 if len(src_data) == 0x40000 else 6

    if pal_idx is None or pal_idx < 0:
        pal = generate_grey_palette()
    else:
        pal = decode_palette(src_data[get_clut_pos_start(pal_idx) :])

    for i in range(0, 4):
        generate_tileset(f"{output_base}_{i}.png", src_data, i, pal, True)
    for i in range(4, max_tilesets):
        generate_tileset(f"{output_base}_{i}.png", src_data, i, pal, False)
    generate_clut(f"{output_base}_clut.png", src_data)


parser = argparse.ArgumentParser(description="convert stage graphics")
parser.add_argument(
    "mode",
    choices=["e", "d"],
    help="(e)ncode PNG to stage graphics or (d)ecode stage graphics to PNG",
)
parser.add_argument("input")
parser.add_argument("output")
parser.add_argument(
    "--pal",
    type=int,
    required=False,
    default=-1,
    dest="pal",
    help="export to PNG using a specific palette index",
)

if __name__ == "__main__":
    args = parser.parse_args()
    if args.mode == "e":
        err = encode(args.input, args.output)
        if err != None:
            sys.stderr.write(f"ERROR: {err}")
    elif args.mode == "d":
        decode(args.input, args.output, args.pal)
