#!/usr/bin/env python3
"""Dump Saturn player sprite images and animations from the disc assets.

The default character profile is Maria. Richter and Alucard are also supported.

Examples:

Render a PNG atlas of Maria's decoded sprite records:

```
python3 tools/saturn_maria_viewer.py \
    dumps/maria-atlas.png
```

Render Maria's animations as individual GIF files:

```
python3 tools/saturn_maria_viewer.py \
    --gif-dir dumps/maria-animations
```

Create a self-contained HTML animation viewer:

```
python3 tools/saturn_maria_viewer.py \
    --html-viewer dumps/maria-viewer.html
```

Generate an atlas, GIF directory, and HTML viewer in one run:

```
python3 tools/saturn_maria_viewer.py \
    dumps/maria-atlas.png \
    --gif-dir dumps/maria-animations \
    --html-viewer dumps/maria-viewer.html
```

Render Richter instead of Maria:

```
python3 tools/saturn_maria_viewer.py \
    --character richter \
    --html-viewer dumps/richter-viewer.html
```

Render Alucard:

```
python3 tools/saturn_maria_viewer.py \
    --character alucard \
    --html-viewer dumps/alucard-viewer.html
```

Choose another palette bank:

```
python3 tools/saturn_maria_viewer.py \
    dumps/maria-palette1.png \
    --palette-bank 1
```

Change atlas layout:

```
python3 tools/saturn_maria_viewer.py \
    dumps/maria-atlas.png \
    --columns 12 \
    --cell-size 96
```

Render a diagnostic direct-color atlas:

```
python3 tools/saturn_maria_viewer.py \
    dumps/maria-rgb16.png \
    --pixel-format rgb16
```

Render a diagnostic indexed-8 atlas:

```
python3 tools/saturn_maria_viewer.py \
    dumps/maria-indexed8.png \
    --pixel-format indexed8
```

Skip per-record LZSS decoding and treat CHR offsets as linear data:

```
python3 tools/saturn_maria_viewer.py \
    dumps/maria-linear.png \
    --linear-chr
```

Override the profile's default PRG and CHR paths:

```
python3 tools/saturn_maria_viewer.py \
    dumps/custom-atlas.png \
    --prg path/to/PLAYER.PRG \
    --chr path/to/PLAYER.CHR \
    --weapon-chr path/to/PLAYER_W.CHR
```

"""

import argparse
import base64
import io
import json
import struct
import zlib
from pathlib import Path

# All three player overlays are linked at 0x060A5000.  Maria's base is visible
# in asm/saturn/maria/data/d60A5000.s; the same mapping is used by the Richter
# and Alucard overlay configurations.  Runtime pointers below therefore become
# PRG offsets by subtracting the selected profile's load_address.
#
# Maria setup: asm/saturn/maria/f_nonmat/f60A5208.s
#   - passes the image/palette configuration to func_0600B344 at
#     0x060A52EA..0x060A5302
#   - stores frame table 0x060C4BB0 at 0x060A530E..0x060A5312
# Richter uses the corresponding f60A5208.s path.  Alucard's related table
# publication is in asm/saturn/alucard/f_nonmat/f60ADDDC.s.
CHARACTER_PROFILES = {
    "maria": {
        "label": "Maria",
        "load_address": 0x060A5000,
        "image_table": 0x060C51A8,
        "palette_table": 0x060C398C,
        "animation_start": 0x060C28D8,
        "animation_end": 0x060C37CC,
        "frame_table": 0x060C4BB0,
        "prg": "disks/saturn/MARIA.PRG",
        "chr": "disks/saturn/MARIA.CHR",
        "weapon_chr": "disks/saturn/MAR_W.CHR",
        # Maria/Richter use virtual character modes 1/2, for which
        # func_0600A490 indexes the stream directory from entry zero.
        "stream_entry_base": 0,
        "animation_format": "pairs16",
        "names": {
            0x060C28E8: "ric_anim_stand",
            0x060C292C: "ric_anim_stand_alt",
            0x060C3788: "D_8015591C",
            0x060C37B8: "D_80155950",
        },
    },
    "richter": {
        "label": "Richter",
        "load_address": 0x060A5000,
        "image_table": 0x060C12EC,
        "palette_table": 0x060C0240,
        "animation_start": 0x060BFC50,
        "animation_end": 0x060C01F8,
        "frame_table": 0x060C0F98,
        "prg": "disks/saturn/RICHTER.PRG",
        "chr": "disks/saturn/RICHTER.CHR",
        "weapon_chr": "disks/saturn/RIC_W.CHR",
        # Maria/Richter use virtual character modes 1/2, for which
        # func_0600A490 indexes the stream directory from entry zero.
        "stream_entry_base": 0,
        "animation_format": "pairs16",
        "names": {
            0x060BFC50: "ric_anim_stand",
            0x060BFD1C: "ric_anim_walk",
        },
    },
    "alucard": {
        "label": "Alucard",
        "load_address": 0x060A5000,
        "image_table": 0x060C9990,
        "palette_table": 0x060C897C,
        "frame_table": 0x060C960C,
        "animation_table": 0x060C85D4,
        "animation_count": 226,
        "prg": "disks/saturn/ALUCARD.PRG",
        "chr": "disks/saturn/ALUCARD.CHR",
        "weapon_chr": None,
        # Alucard reaches func_0600A490's fallback branch, which adds 0x18
        # before indexing the directory (0x0600A4DC..0x0600A4E8).  Three
        # eight-byte mode descriptors therefore precede image stream zero.
        "stream_entry_base": 3,
        "animation_format": "compact3",
        "names": {},
    },
}


def read_u16(data, offset):
    return struct.unpack_from(">H", data, offset)[0]


def prg_offset(address, profile):
    # Player overlay symbols are runtime SH-2 addresses.  For Maria this
    # conversion is also documented by asm/saturn/maria/data/d60A5000.s.
    return address - profile["load_address"]


def decompress_lzss(data):
    """Expand one exact-count Saturn LZSS stream.

    Runtime authority: func_0600F96C in
    asm/saturn/zero/f_nonmat/f600F96C.s.  Its third argument is the compressed
    byte count and it has no end marker, so callers must pass one directory
    entry rather than a whole padded CHR file.
    """
    dictionary = bytearray(0x400)
    cursor = 0x3DE
    output = bytearray()
    source = 0
    flags = 0
    while source < len(data):
        flags >>= 1
        if not flags & 0x100:
            flags = data[source] | 0xFF00
            source += 1
        if flags & 1:
            if source >= len(data):
                break
            value = data[source]
            source += 1
            output.append(value)
            dictionary[cursor] = value
            cursor = (cursor + 1) & 0x3FF
        else:
            if source + 1 >= len(data):
                break
            first, second = data[source : source + 2]
            source += 2
            index = first | ((second & 0xE0) << 3)
            length = (second & 0x1F) + 3
            for i in range(length):
                value = dictionary[(index + i) & 0x3FF]
                output.append(value)
                dictionary[cursor] = value
                cursor = (cursor + 1) & 0x3FF
    return bytes(output)


def read_image_records(prg, profile):
    """Read the profile's four-byte image source/size records.

    Maria's table is 0x060C51A8; Richter's is 0x060C12EC; Alucard's is
    0x060C9990.  Each record is a packed width/storage byte, height byte, and a
    be16 source value in eight-byte units.

    The final raster geometry is derived in func_0600B4C4 at
    0x0600B8C8..0x0600B8DA when it builds VDP1 CMDSIZE: both table dimensions
    are doubled for the compact 4bpp path.  The second word is not a compressed
    stream boundary; read_stream_records() gets those from the PRG directory.
    """
    records = []
    cursor = prg_offset(profile["image_table"], profile)
    previous_offset = -1
    while cursor + 4 <= len(prg):
        dimensions = read_u16(prg, cursor)
        chr_offset_units = read_u16(prg, cursor + 2)
        width, height = dimensions >> 8, dimensions & 0xFF
        if (
            not width
            or not height
            or width > 128
            or height > 128
            or chr_offset_units < previous_offset
        ):
            break
        records.append((width, height, chr_offset_units * 8))
        previous_offset = chr_offset_units
        cursor += 4
    return records


def read_stream_records(prg, count, profile):
    # The authoritative compressed-stream directory is exported at PRG +0x40.
    # For Maria, func_0601AD14 copies that pointer to 0x06064668 at
    # 0x0601AD98..0x0601AD9C.  func_0600A490 then indexes eight-byte entries:
    #   +0 u32 backing-store address
    #   +4 u32 exact compressed byte count
    # Virtual modes 1/2 use base + image_index * 8.  Its fallback branch adds
    # 0x18 first at 0x0600A4DC..0x0600A4E8, which is why Alucard starts at 3.
    directory_address = struct.unpack_from(">I", prg, 0x40)[0]
    directory = prg_offset(directory_address, profile)
    # Directory sources are runtime backing-store addresses (Maria begins at
    # 0x00232000).  Subtract the first entry so they address the offline CHR
    # byte store.  Maria image zero is source 0x00232000, size 0x138; image one
    # begins at 0x00232138, a useful check against accidental entry shifting.
    backing_base = struct.unpack_from(">I", prg, directory)[0]
    records = []
    for index in range(count):
        entry = profile["stream_entry_base"] + index
        address, size = struct.unpack_from(">II", prg, directory + entry * 8)
        records.append((address - backing_base, size))
    return records


def read_animations(prg, profile):
    """Split Maria/Richter pair16 animation blocks at control entries.

    AnimationFrame is the shared big-endian (duration, pose) pair defined by
    POSE_* in src/saturn/sattypes.h.  ServantUpdateAnim in src/saturn/t_bat.c
    is a readable consumer of the same controls: duration 0 is POSE_LOOP,
    0xFFFE is POSE_JUMP, and 0xFFFF is POSE_END.  The logical frame is the low
    nine pose bits; the high seven bits select the hitbox.
    """
    if profile["animation_format"] == "compact3":
        return read_compact_animations(prg, profile)
    animations = []
    cursor = prg_offset(profile["animation_start"], profile)
    end = prg_offset(profile["animation_end"], profile)
    while cursor + 4 <= end:
        start = cursor
        frames = []
        loop_start = None
        while cursor + 4 <= end:
            duration, pose = struct.unpack_from(">HH", prg, cursor)
            cursor += 4
            if duration == 0:
                # POSE_LOOP's second word is an animation-entry index, not an
                # ignored terminator.  The GIF path uses it to trim a one-shot
                # prefix; the HTML viewer keeps it as explicit control flow.
                loop_start = pose
                break
            if duration in (0xFFFE, 0xFFFF):
                # This simple contiguous-block scanner ends the current
                # sequence at POSE_JUMP/POSE_END.  Resolving pair16 jump targets
                # would require the runtime animation pointer selection path.
                break
            frames.append((duration, pose & 0x1FF))
        if frames:
            animations.append(
                (profile["load_address"] + start, frames, loop_start, None)
            )
        if cursor == start:
            break
    return animations


def read_compact_animations(prg, profile):
    # Alucard setup in asm/saturn/alucard/f_nonmat/f60ADDDC.s identifies the
    # pointer table at 0x060C85D4.  Its targets use compact three-byte entries:
    # duration, logical frame, hitbox.  FF FF xx ends; FF anim entry jumps.
    # This correlates with the compact control flow consumed by Alucard's
    # animation code rather than the Maria/Richter pair16 representation.
    table = prg_offset(profile["animation_table"], profile)
    animations = []
    for index in range(profile["animation_count"]):
        address = struct.unpack_from(">I", prg, table + index * 4)[0]
        cursor = prg_offset(address, profile)
        frames = []
        jump = None
        while cursor + 3 <= len(prg):
            duration, frame, hitbox = struct.unpack_from(">BBB", prg, cursor)
            cursor += 3
            if duration == 0xFF:
                if frame != 0xFF:
                    jump = (frame, hitbox)
                break
            frames.append((duration, frame))
        if frames:
            animations.append((address, frames, None, jump))
    return animations


def frame_image_index(prg, logical_frame, profile):
    # Maria initialization stores frame table 0x060C4BB0 into the player object
    # at 0x060A530E..0x060A5312.  The common consumer is func_0600B004 in
    # asm/saturn/zero/f_nonmat/f600B004.s:
    #   descriptor +0x00: header, bits 8..13 = sprite-part count
    #   descriptor +0x04: four u16 words per eight-byte sprite part
    #
    # func_0600B004 copies those words to a sprite node.  func_0600B4C4 later
    # multiplies node word +6 by four at 0x0600B6DC..0x0600B6F2 to index the
    # four-byte image table, proving part word 3 is the image-record index.
    table = prg_offset(profile["frame_table"], profile)
    pointer_offset = table + logical_frame * 4
    if pointer_offset + 4 > len(prg):
        raise ValueError(f"logical frame {logical_frame} is outside frame table")
    frame_address = struct.unpack_from(">I", prg, pointer_offset)[0]
    frame = prg_offset(frame_address, profile)
    header = read_u16(prg, frame)
    part_count = (header >> 8) & 0x3F
    if part_count != 1:
        raise ValueError(
            f"logical frame {logical_frame} has {part_count} sprite parts"
        )
    # One part begins at descriptor +0x04, so its fourth word is at +0x0A.
    return read_u16(prg, frame + 0x0A)


def read_palette(prg, bank, profile):
    # Maria's sprite configuration at 0x060C6D68 points to image table
    # 0x060C51A8 and palette table 0x060C398C.  func_060A5208 passes this
    # configuration to func_0600B344 at 0x060A52EA..0x060A5302.
    #
    # The table itself is a be16 bank count followed by 16-entry RGB555 banks.
    # Runtime CMDCOLR is still dynamic: func_0600B4C4 writes it at
    # 0x0600B8AC..0x0600B8B0 after combining object and node state.  The bank
    # argument here is therefore an explicit offline viewer choice.
    table = prg_offset(profile["palette_table"], profile)
    bank_count = read_u16(prg, table)
    if bank < 0 or bank >= bank_count:
        raise ValueError(f"palette bank must be between 0 and {bank_count - 1}")
    offset = table + 2 + bank * 32
    if offset < 0 or offset + 32 > len(prg):
        raise ValueError(f"palette bank {bank} lies outside MARIA.PRG")
    colors = []
    for value in struct.unpack_from(">16H", prg, offset):
        colors.append(
            (
                (value & 0x1F) * 255 // 31,
                ((value >> 5) & 0x1F) * 255 // 31,
                ((value >> 10) & 0x1F) * 255 // 31,
                255,
            )
        )
    colors[0] = (*colors[0][:3], 0)
    return colors


def decode_image(chr_data, width_field, height, offset, pixel_format, palette):
    # All interpretations consume the same compact record allocation:
    # width_field * height * 2 bytes.  Which interpretation is correct is
    # selected by VDP1 command state, not by the four-byte image table alone.
    #
    # Common command builder func_0600B4C4:
    #   - node word 0 mode bits are isolated at 0x0600B680..0x0600B684
    #   - CMDPMOD is built from 0x0480/0x0488 and written at
    #     0x0600B7D4..0x0600B81E, identifying mode 0 as a 4bpp bank/LUT path
    #   - source state is written around 0x0600B70C..0x0600B74A
    #   - CMDSIZE is written around 0x0600B8B2..0x0600B8DA
    size = width_field * height * 2
    if offset + size > len(chr_data):
        raise ValueError(
            f"image field {width_field}x{height} at {offset:#x} exceeds CHR size"
        )
    source = chr_data[offset : offset + size]
    if pixel_format == "rgb16":
        # Diagnostic direct-color interpretation.  Saturn RGB555 uses bit 15
        # as the visible/direct-color enable; RGB16_COLOR in
        # src/saturn/lib/def.h likewise ORs 0x8000.
        width = width_field
        values = struct.unpack(f">{width * height}H", source)
        colors = [
            (
                (value & 0x1F) * 255 // 31,
                ((value >> 5) & 0x1F) * 255 // 31,
                ((value >> 10) & 0x1F) * 255 // 31,
                255 if value & 0x8000 else 0,
            )
            for value in values
        ]
    elif pixel_format == "indexed8":
        # Diagnostic only.  The confirmed Maria player-part mode is 4bpp,
        # but retaining this view is useful while examining other record groups.
        width = width_field * 2
        colors = [(value, value, value, 255 if value else 0) for value in source]
    else:
        # Confirmed mode-0 4bpp path.  The compact table stores half the final
        # VDP1 raster dimensions.  func_0600B4C4 performs the CMDSIZE packing at
        # 0x0600B8C8..0x0600B8DA, giving
        # (width_field * 2, height * 2).  For example, table value 0x0817
        # becomes CMDSIZE 0x022E: 16 pixels wide and 46 pixels high.
        width = width_field * 2
        height *= 2
        indices = [nibble for value in source for nibble in (value >> 4, value & 15)]
        colors = [palette[value] for value in indices]
    return width, height, bytes(channel for color in colors for channel in color)


def png_chunk(kind, data):
    return (
        struct.pack(">I", len(data))
        + kind
        + data
        + struct.pack(">I", zlib.crc32(kind + data))
    )


def write_png(path, width, height, pixels):
    stride = width * 4
    rows = b"".join(
        b"\0" + pixels[y * stride : (y + 1) * stride] for y in range(height)
    )
    png = b"\x89PNG\r\n\x1a\n"
    png += png_chunk(b"IHDR", struct.pack(">IIBBBBB", width, height, 8, 6, 0, 0, 0))
    png += png_chunk(b"IDAT", zlib.compress(rows, 9))
    png += png_chunk(b"IEND", b"")
    path.write_bytes(png)


def render_atlas(
    prg, chr_data, output, pixel_format, profile, palette_bank=0, columns=16,
    cell_size=0, linear_chr=False,
):
    records = read_image_records(prg, profile)
    # Do not treat image-table source values as compressed boundaries.  The
    # exact slices come from PRG +0x40 / func_0600A490, and each slice resets
    # func_0600F96C's dictionary.  Whole-file CHR decompression is invalid
    # because the codec has no end marker and the disc file is padded.
    streams = read_stream_records(prg, len(records), profile)
    if not records:
        raise ValueError("Maria image table is empty or invalid")
    if not cell_size:
        cell_size = max(
            max(width_field * 2, image_height * 2)
            for width_field, image_height, _ in records
        )
    rows = (len(records) + columns - 1) // columns
    width, height = columns * cell_size, rows * cell_size
    atlas = bytearray(width * height * 4)
    palette = read_palette(prg, palette_bank, profile)
    for image_index, (width_field, image_height, offset) in enumerate(records):
        image_data = chr_data
        image_offset = offset
        if not linear_chr:
            # Normal path: exact compressed address/count pair selected by the
            # runtime virtual-character resolver.  --linear-chr deliberately
            # bypasses this and treats the table offset as raw data for diagnosis.
            stream_offset, stream_size = streams[image_index]
            if stream_offset < 0 or stream_offset + stream_size > len(chr_data):
                continue
            image_data = decompress_lzss(
                chr_data[stream_offset : stream_offset + stream_size]
            )
            image_offset = 0
        try:
            image_width, decoded_height, image = decode_image(
                image_data, width_field, image_height, image_offset,
                pixel_format, palette
            )
        except ValueError:
            continue
        origin_x = (image_index % columns) * cell_size
        origin_y = (image_index // columns) * cell_size
        origin_x += max(0, (cell_size - image_width) // 2)
        origin_y += max(0, (cell_size - decoded_height) // 2)
        copy_width = min(image_width, cell_size)
        copy_height = min(decoded_height, cell_size)
        for y in range(copy_height):
            source = y * image_width * 4
            destination = ((origin_y + y) * width + origin_x) * 4
            atlas[destination : destination + copy_width * 4] = image[
                source : source + copy_width * 4
            ]
    write_png(output, width, height, atlas)
    print(f"rendered {len(records)} {profile['label']} CHR images -> {output}")
    if linear_chr:
        print("warning: atlas treats record offsets as uncompressed linear data")


def decode_record(prg, chr_data, image_index, palette, profile):
    # The same image index selects both the four-byte allocation record and its
    # compressed stream entry.  func_0600A490 establishes that correspondence;
    # profile["stream_entry_base"] accounts for Alucard's +0x18 branch.
    records = read_image_records(prg, profile)
    if image_index >= len(records):
        raise ValueError(f"image index {image_index} is outside image table")
    streams = read_stream_records(prg, len(records), profile)
    width_field, height, _ = records[image_index]
    offset, size = streams[image_index]
    if offset < 0 or offset + size > len(chr_data):
        raise ValueError(f"image {image_index} stream is outside CHR data")
    expanded = decompress_lzss(chr_data[offset : offset + size])
    # Maria's populated player descriptors all use renderer mode 0.  The
    # CMDPMOD construction at 0x0600B7D4..0x0600B81E identifies that as 4bpp,
    # not the superficially plausible RGB16 diagnostic interpretation.
    return decode_image(expanded, width_field, height, 0, "indexed4", palette)


def centered_picture(Image, decoded_record):
    # Alpha-bounds centering is only an offline presentation anchor.  The
    # actual placement/flip meaning of sprite-part words 1 and 2 remains to be
    # derived from func_0600B4C4; this function does not claim to reproduce it.
    width, height, pixels = decoded_record
    picture = Image.new("RGBA", (96, 96))
    sprite = Image.frombytes("RGBA", (width, height), pixels)
    visible = sprite.getchannel("A").getbbox()
    if visible is None:
        return None
    left, top, right, bottom = visible
    origin = (
        (96 - (right - left)) // 2 - left,
        (96 - (bottom - top)) // 2 - top,
    )
    picture.alpha_composite(sprite, origin)
    return picture


def render_animation_gifs(
    prg, chr_data, output_dir, palette_bank, profile, tick_rate=60
):
    try:
        from PIL import Image
    except ImportError as error:
        raise RuntimeError("GIF dumping requires Pillow (`pip install Pillow`)") from error

    output_dir.mkdir(parents=True, exist_ok=True)
    palette = read_palette(prg, palette_bank, profile)
    decoded = {}
    animations = read_animations(prg, profile)
    written = 0
    for animation_index, (address, animation, loop_start, _jump) in enumerate(
        animations
    ):
        # POSE_LOOP's second word is an entry index (see the shared
        # AnimationFrame consumer ServantUpdateAnim), but GIF can only loop the
        # whole image.  Drop a one-shot lead-in so the repeated section is exact.
        # A known check is sequence 0x060C2ADC, which ends in (0, 6).
        if loop_start is not None and 0 <= loop_start < len(animation):
            animation = animation[loop_start:]
        pictures = []
        durations = []
        for ticks, logical_frame in animation:
            try:
                image_index = frame_image_index(prg, logical_frame, profile)
                if image_index not in decoded:
                    decoded[image_index] = decode_record(
                        prg, chr_data, image_index, palette, profile
                    )
                picture = centered_picture(Image, decoded[image_index])
            except ValueError:
                continue
            if picture is None:
                continue
            pictures.append(picture)
            # GIF delays use 10 ms centiseconds.  Quantize explicitly so Pillow
            # does not truncate a 60 Hz four-tick delay from 67 ms to 60 ms.
            durations.append(max(10, round(ticks * 100 / tick_rate) * 10))
        if not pictures:
            continue
        symbol = profile["names"].get(address)
        if symbol is not None:
            name = symbol
        elif profile["animation_format"] == "compact3":
            name = f"anim_{animation_index:03d}_{address:08x}"
        else:
            name = f"anim_{address:08x}"
        pictures[0].save(
            output_dir / f"{name}.gif",
            save_all=True,
            append_images=pictures[1:],
            duration=durations,
            disposal=2,
            loop=0,
            transparency=0,
        )
        written += 1
    print(f"rendered {written} {profile['label']} animations -> {output_dir}")


def render_html_viewer(
    prg, chr_data, output, palette_bank, profile, tick_rate=60
):
    try:
        from PIL import Image
    except ImportError as error:
        raise RuntimeError("HTML viewer generation requires Pillow") from error

    palette = read_palette(prg, palette_bank, profile)
    decoded = {}
    assets = {}
    animations = []
    for animation_index, (address, animation, loop_start, jump) in enumerate(
        read_animations(prg, profile)
    ):
        frames = []
        for ticks, logical_frame in animation:
            try:
                image_index = frame_image_index(prg, logical_frame, profile)
                if image_index not in decoded:
                    decoded[image_index] = decode_record(
                        prg, chr_data, image_index, palette, profile
                    )
                if str(image_index) not in assets:
                    picture = centered_picture(Image, decoded[image_index])
                    if picture is None:
                        continue
                    png = io.BytesIO()
                    picture.save(png, format="PNG", optimize=True)
                    assets[str(image_index)] = (
                        "data:image/png;base64,"
                        + base64.b64encode(png.getvalue()).decode("ascii")
                    )
            except ValueError:
                continue
            frames.append(
                {"image": str(image_index), "ms": ticks * 1000 / tick_rate}
            )
        if not frames:
            continue
        name = profile["names"].get(address)
        if name is None:
            if profile["animation_format"] == "compact3":
                name = f"anim_{animation_index:03d}_{address:08x}"
            else:
                name = f"anim_{address:08x}"
        animations.append(
            {
                "name": name,
                "tableIndex": animation_index,
                "address": f"0x{address:08X}",
                "frames": frames,
                "loopStart": loop_start,
                "jumpAnimation": jump[0] if jump is not None else None,
                "jumpFrame": jump[1] if jump is not None else 0,
            }
        )

    payload = json.dumps(
        {"assets": assets, "animations": animations}, separators=(",", ":")
    )
    # Unlike GIF, the browser player can preserve a one-shot prefix and then
    # follow POSE_LOOP.  It also follows Alucard's compact FF anim/entry jump.
    html = """<!doctype html>
<html lang="en"><head><meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>Saturn """ + profile["label"] + """ animations</title>
<style>
html,body{height:100%;margin:0;background:#111;color:#eee;font:16px system-ui,sans-serif}
body{display:grid;place-items:center}.viewer{text-align:center}
.stage{width:384px;height:384px;background:#080808;border:1px solid #444;
display:grid;place-items:center;margin:1rem auto}.stage img{width:384px;height:384px;
image-rendering:pixelated}.controls{display:flex;gap:1rem;align-items:center;justify-content:center}
button{font:inherit;padding:.5rem 1rem;background:#292929;color:#eee;border:1px solid #666}
.name{font-weight:600}.detail{color:#aaa;margin-top:.35rem}.hint{color:#888;margin-top:1rem}
</style></head><body><main class="viewer">
<div class="name" id="name"></div><div class="detail" id="detail"></div>
<div class="stage"><img id="sprite" alt="Maria animation"></div>
<div class="controls"><button id="previous">← Previous</button><span id="count"></span>
<button id="next">Next →</button></div><div class="hint">Use Left and Right arrow keys</div>
</main><script>const DATA=""" + payload + """;
const sprite=document.querySelector('#sprite');
const nameElement=document.querySelector('#name');
const detail=document.querySelector('#detail');
const count=document.querySelector('#count');
let selectedIndex=0,animationIndex=0,frameIndex=0,timer=null;
function select(delta){
  selectedIndex=(selectedIndex+delta+DATA.animations.length)%DATA.animations.length;
  animationIndex=selectedIndex;frameIndex=0;play();
}
function play(){
  clearTimeout(timer);
  const animation=DATA.animations[animationIndex];
  const frame=animation.frames[frameIndex];
  sprite.src=DATA.assets[frame.image];
  nameElement.textContent=animation.name;
  detail.textContent=animation.address+' · frame '+(frameIndex+1)+'/'+animation.frames.length;
  count.textContent=(selectedIndex+1)+' / '+DATA.animations.length;
  if(frameIndex+1<animation.frames.length){
    timer=setTimeout(()=>{frameIndex++;play()},frame.ms);
  }else if(animation.loopStart!==null&&animation.loopStart<animation.frames.length){
    timer=setTimeout(()=>{frameIndex=animation.loopStart;play()},frame.ms);
  }else if(animation.jumpAnimation!==null){
    const target=DATA.animations.findIndex(item=>item.tableIndex===animation.jumpAnimation);
    if(target>=0){timer=setTimeout(()=>{animationIndex=target;
      frameIndex=Math.min(animation.jumpFrame,DATA.animations[target].frames.length-1);play()},frame.ms)}
  }
}
document.querySelector('#previous').onclick=()=>select(-1);
document.querySelector('#next').onclick=()=>select(1);
addEventListener('keydown',event=>{
  if(event.key==='ArrowLeft')select(-1);
  if(event.key==='ArrowRight')select(1);
});
play();</script></body></html>"""
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(html)
    print(f"rendered {len(animations)} {profile['label']} animations -> {output}")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--character", choices=tuple(CHARACTER_PROFILES), default="maria",
        help="character asset profile (default: maria)",
    )
    parser.add_argument(
        "--prg", type=Path, help="override the selected character PRG"
    )
    parser.add_argument(
        "--chr", type=Path, help="override the selected character CHR"
    )
    parser.add_argument(
        "--weapon-chr", type=Path,
        help="override the secondary CHR loaded after the main graphics",
    )
    parser.add_argument("output", type=Path, nargs="?", help="output atlas PNG")
    parser.add_argument(
        "--gif-dir", type=Path,
        help="write one animated GIF per Maria animation into this directory",
    )
    parser.add_argument(
        "--html-viewer", type=Path,
        help="write a self-contained keyboard-controlled animation viewer",
    )
    parser.add_argument("--columns", type=int, default=16)
    parser.add_argument(
        "--cell-size", type=int, default=0,
        help="square atlas cell size (default: auto-size to the largest pose)",
    )
    parser.add_argument(
        "--palette-bank", type=int, default=0,
        help="16-color bank in Maria's palette table (default: 0)",
    )
    parser.add_argument(
        "--pixel-format", choices=("indexed4", "indexed8", "rgb16"),
        default="indexed4",
        help="diagnostic atlas interpretation (default: indexed4 palette)",
    )
    parser.add_argument(
        "--linear-chr", action="store_true",
        help="skip per-record LZSS decoding (diagnostic only)",
    )
    args = parser.parse_args()
    if args.output is None and args.gif_dir is None and args.html_viewer is None:
        parser.error("provide an atlas output path, --gif-dir, or --html-viewer")
    if args.columns <= 0 or args.cell_size < 0:
        parser.error("--columns must be positive and --cell-size nonnegative")
    profile = CHARACTER_PROFILES[args.character]
    prg_path = args.prg or Path(profile["prg"])
    chr_path = args.chr or Path(profile["chr"])
    weapon_chr_path = args.weapon_chr
    if weapon_chr_path is None and profile["weapon_chr"] is not None:
        weapon_chr_path = Path(profile["weapon_chr"])
    chr_data = chr_path.read_bytes()
    if weapon_chr_path is not None:
        # The image/stream address space continues into the secondary graphics
        # asset (Maria record 305 crosses the MARIA.CHR boundary).  Concatenation
        # builds the viewer's logical backing store.  The runtime loader itself
        # uses separate descriptors in asm/saturn/zero/data/d6030BF4.s and the
        # state machine near func_06006FA8; normal decoding still follows the
        # PRG +0x40 stream directory rather than assuming raw linear placement.
        chr_data += weapon_chr_path.read_bytes()
    prg = prg_path.read_bytes()
    if args.output is not None:
        render_atlas(
            prg, chr_data, args.output, args.pixel_format, profile,
            args.palette_bank, args.columns, args.cell_size, args.linear_chr
        )
    if args.gif_dir is not None:
        render_animation_gifs(
            prg, chr_data, args.gif_dir, args.palette_bank, profile
        )
    if args.html_viewer is not None:
        render_html_viewer(
            prg, chr_data, args.html_viewer, args.palette_bank, profile
        )


if __name__ == "__main__":
    main()
