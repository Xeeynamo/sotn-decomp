#!/usr/bin/env python3

import argparse
import json
import os
from PIL import Image
import sys

max_sprite_per_row = 8
max_width = 96
max_height = 96


def is_spritesheet_desc_sane(spritesheet_desc):
    for entry in spritesheet_desc:
        if os.path.isfile(entry["name"]) == False:
            return False, entry["name"]
    return True, None


def merge(spritesheet_desc, out_path):
    # performs an integrity check before committing to the algorithm
    is_sane, missing_file_path = is_spritesheet_desc_sane(spritesheet_desc)
    if is_sane == False:
        raise ValueError(f"one or more files are missing: '{missing_file_path}'")

    sprite_count = len(spritesheet_desc)
    img_width = max_width * max_sprite_per_row
    img_height = (
        (sprite_count + max_sprite_per_row - 1) // max_sprite_per_row * max_height
    )
    spritesheet = Image.new("P", (img_width, img_height))

    with Image.open(spritesheet_desc[0]["name"]) as first_sprite:
        spritesheet.putpalette(first_sprite.palette)
        spritesheet.info["transparency"] = 0

    for n_sprite, entry in enumerate(spritesheet_desc):
        sprite = Image.open(entry["name"])
        width, height = sprite.size
        if width > max_width or height > max_height:
            raise ValueError(
                f"All images must be {max_width}x{max_height} or smaller: '{entry['name']}' is {width}x{height}"
            )
        offset_x = int(n_sprite % max_sprite_per_row) * max_width
        offset_y = n_sprite // max_sprite_per_row * max_height
        center_x = entry["x"]
        center_y = entry["y"]
        if center_x + width > max_width or center_y + height > max_height:
            raise ValueError(
                (
                    f"Sprite '{entry['name']}' is out of bounds:\n"
                    f"cx:{center_x} + w:{width} > mw:{max_width}\n"
                    f"cy:{center_y} + h:{height} > mh:{max_height}"
                )
            )
        spritesheet.paste(sprite, (offset_x + center_x, offset_y + center_y))
        sprite.close()

    spritesheet.save(out_path)
    spritesheet.close()


def align_bbox(bbox):
    sx, sy, ex, ey = bbox
    w = ex - sx
    h = ey - sy

    x_excess = sx & 1
    sx -= x_excess
    w += x_excess
    w = ((w + 3) // 4) * 4

    return (sx, sy, sx + w, sy + h)


def split_sprite(spritesheet, x, y):
    sprite = spritesheet.crop((x, y, x + max_width, y + max_height))
    bbox = sprite.getbbox()
    if bbox == None:
        return (None, 0, 0)
    aligned_bbox = align_bbox(bbox)
    x, y, _, _ = aligned_bbox
    return (sprite.crop(aligned_bbox), x, y)


def split(name, spritesheet, out_path):
    width, height = spritesheet.size
    if width != max_width * max_sprite_per_row:
        raise ValueError(
            f"The spritesheet must have a width of {max_width * max_sprite_per_row} but found {width}"
        )
    if (height % max_height) > 0:
        raise ValueError(
            f"The spritesheet must have a height multiple of {max_height} but found {height}"
        )

    sprite_count = (width // max_width) * (height // max_height)
    spritesheet_desc = []
    for n_sprite in range(0, sprite_count):
        offset_x = int(n_sprite % max_sprite_per_row) * max_width
        offset_y = n_sprite // max_sprite_per_row * max_height
        sprite, x, y = split_sprite(spritesheet, offset_x, offset_y)
        if sprite == None:
            break

        out_sprite_path = os.path.join(out_path, f"{name}_{n_sprite}.png")
        sprite.save(out_sprite_path)

        spritesheet_desc.append(
            {
                "x": x,
                "y": y,
                "name": out_sprite_path,
            }
        )
    with open(os.path.join(out_path, f"{name}.spritesheet.json"), "w") as f:
        json.dump(spritesheet_desc, f, indent=4)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Manipulate a spritesheet for modding")
    subparsers = parser.add_subparsers(dest="command")

    merge_parser = subparsers.add_parser(
        "merge", description="Merge all the individual sprites into a single PNG."
    )
    merge_parser.add_argument(
        "json_file",
        type=argparse.FileType("r"),
        help="The JSON file path that contains the spritesheet info (eg. 'assets/ric/richter.spritesheet.json')",
    )
    merge_parser.add_argument(
        "output_path",
        help="File path where to store the assembled spritesheet",
    )

    split_parser = subparsers.add_parser(
        "split",
        description=(
            "Split a spritesheet PNG back to their individual sprites.\n"
            "The individual sprites will be stored to the same path of "
            "<json_file> and their names will follow the name of the input_path."
            "\ne.g. sat_ric.png as input will produce sat_ric_0.png and so on."
        ),
    )
    split_parser.add_argument(
        "input_file_path",
        help="Spritesheet file path to split",
    )
    split_parser.add_argument(
        "output_path",
        help="Path where to store the JSON descriptor and the spliited sprites",
    )

    args = parser.parse_args()
    if args.command == "merge":
        with args.json_file as file_in:
            merge(json.loads(file_in.read()), args.output_path)
    elif args.command == "split":
        file_name, ext = os.path.splitext(os.path.basename(args.input_file_path))
        with Image.open(args.input_file_path) as spritesheet:
            if os.path.exists(args.output_path) == False:
                os.mkdir(args.output_path)
            split(file_name, spritesheet, args.output_path)
