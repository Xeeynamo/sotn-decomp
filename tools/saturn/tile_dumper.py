#!/usr/bin/env python3
"""Extract and render Saturn SOTN stage backgrounds.

Examples:

Dump every supported stage as a composite PNG:

```
python3 tools/saturn/tile_dumper.py --batch
```

Choose input/output directories:

```
python3 tools/saturn/tile_dumper.py \
    --batch \
    --input-dir disks/saturn \
    --output-dir dumps
```

Render stages in parallel, replacing existing PNGs:

```
python3 tools/saturn/tile_dumper.py \
    --batch \
    --jobs 8 \
    --force
```

Stop batch rendering after the first failure:

```
python3 tools/saturn/tile_dumper.py \
    --batch \
    --fail-fast
```

Render one room and one layer:

```
python3 tools/saturn/tile_dumper.py \
    disks/saturn/STAGE_02.PRG \
    disks/saturn/STAGE_02.MAP \
    /tmp/stage02_room0_layer0.png \
    --room 0 \
    --layer 0
```

Render one layer across the whole stage:

```
python3 tools/saturn/tile_dumper.py \
    disks/saturn/STAGE_02.PRG \
    disks/saturn/STAGE_02.MAP \
    /tmp/stage02_layer2.png \
    --whole-stage \
    --layer 2
```

Render a whole-stage composite using each room's VDP2 priorities:

```
python3 tools/saturn/tile_dumper.py \
    disks/saturn/STAGE_15.PRG \
    disks/saturn/STAGE_15.MAP \
    /tmp/stage15_composite.png \
    --composite
```

Render STAGE_07 part A:

```
python3 tools/saturn/tile_dumper.py \
    disks/saturn/STAGE_07.PRG \
    disks/saturn/STAGE_7A.MAP \
    /tmp/stage7a.png \
    --composite \
    --descriptor-set 0
```

Render STAGE_07 part B:

```
python3 tools/saturn/tile_dumper.py \
    disks/saturn/STAGE_07.PRG \
    disks/saturn/STAGE_7B.MAP \
    /tmp/stage7b.png \
    --composite \
    --descriptor-set 1
```

Render BOSS_R14 manually. Its background descriptors refer to
RSTAGE14.MAP rather than BOSS_R14.MAP:

```
python3 tools/saturn/tile_dumper.py \
    disks/saturn/BOSS_R14.PRG \
    disks/saturn/RSTAGE14.MAP \
    /tmp/boss_r14.png \
    --composite
```

"""

import argparse
import os
import struct
import zlib
from concurrent.futures import ProcessPoolExecutor, as_completed
from pathlib import Path


# Stage overlays are linked at 0x060DC000, so pointers exported through the
# PRG header become file offsets after subtracting this base. The exports are
# published by func_0601AC48 (asm/saturn/zero/f_nonmat/f601AC48.s) and consumed
# by the ordinary room setup in func_0606C774
# (asm/saturn/game/f_nonmat/f606C774.s).
STAGE_LOAD_ADDRESS = 0x060DC000


# PRG tables, MAP headers, palette words, and pattern-name entries are
# all big-endian.
def read_u32(data, offset):
    return struct.unpack_from(">I", data, offset)[0]


# Decoder used independently for each character/palette/map stream.
# Derived from the complete runtime decoder func_0600F96C in
# asm/saturn/zero/f_nonmat/f600F96C.s. Its callers pass the compressed byte
# count in func_06008588 (src/saturn/zero.c, around line 535).
def decompress_lzss(data):
    # 0x400-byte zeroed ring buffer, with the same initial write position
    # used by the Saturn decoder.
    dictionary = bytearray(0x400)
    cursor = 0x3DE
    output = bytearray()
    source = 0
    flags = 0

    # There is no decompressed-size header. The compressed byte count from
    # the PRG table is the input boundary.
    while source < len(data):
        # Flag bits are consumed least-significant bit first. The 0xFF00
        # sentinel causes a new flag byte to be loaded after eight items.
        flags >>= 1
        if not flags & 0x100:
            flags = data[source] | 0xFF00
            source += 1

        # Set flag bit: one literal byte.
        if flags & 1:
            if source >= len(data):
                break
            value = data[source]
            source += 1
            output.append(value)
            dictionary[cursor] = value
            cursor = (cursor + 1) & 0x3FF
        # Clear flag bit: two-byte backreference. Copy one byte at a time
        # because source and destination can overlap in the ring.
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


# Ordinary stages use the five export fields at PRG +0x14..+0x24.
# STAGE_07 has a second set 0x14 bytes later. This matches the special-stage
# branch of func_0601AC48, which multiplies the active substage index by
# 20 bytes before publishing counts/offsets/setup/next/priority pointers
# (asm/saturn/zero/f_nonmat/f601AC48.s).
def export_offset(descriptor_set, field):
    if descriptor_set not in (0, 1):
        raise ValueError("descriptor set must be 0 or 1")
    return field + descriptor_set * 0x14


# Return the decompressed character, palette, and map streams for one
# room/layer. func_0606C774 constructs three 0x30-byte runtime descriptors in
# this same order at 0x0606C7B0..0x0606C902. func_06008588 later dispatches the
# decompression/DMA work for those descriptor streams.
def stage_streams(prg, map_data, room, layer, descriptor_set=0):
    if room < 0 or layer not in range(3):
        raise ValueError("room must be nonnegative and layer must be 0, 1, or 2")

    # PRG +0x14 points to compressed byte counts and +0x18 to raw MAP-file
    # offsets. These globals are loaded near the start of func_0606C774; the
    # header pointers themselves are published by func_0601AC48.
    counts = read_u32(prg, export_offset(descriptor_set, 0x14)) - STAGE_LOAD_ADDRESS
    offsets = read_u32(prg, export_offset(descriptor_set, 0x18)) - STAGE_LOAD_ADDRESS
    # Each room owns 36 bytes: 3 layers * 3 streams * 4-byte entries. The
    # room-index multiplication and descriptor selection are visible at
    # 0x0606C7A4..0x0606C7CE in f606C774.s.
    descriptor = room * 36 + layer * 12
    if counts + descriptor + 12 > len(prg) or offsets + descriptor + 12 > len(prg):
        raise ValueError("room descriptor lies outside the stage PRG")

    # stream 0: packed 4bpp 8x8 characters
    # stream 1: RGB555 palette banks
    # stream 2: map dimensions and u16 pattern-name entries
    #
    # func_06008588 copies stream 0 to descriptor->dst0 and stream 1 to
    # descriptor->dst4, then sends the map stream through the name-table path.
    streams = []
    for i in range(3):
        offset = read_u32(prg, offsets + descriptor + i * 4)
        size = read_u32(prg, counts + descriptor + i * 4)
        # A zero compressed count marks an absent room/layer descriptor.
        if not size:
            raise ValueError(f"room {room} layer {layer} is empty")
        if offset + size > len(map_data):
            raise ValueError(
                f"stream {i} range {offset:#x}+{size:#x} exceeds MAP size"
            )
        # Each stream is a separate LZSS unit. Do not concatenate them
        # before decompression.
        streams.append(decompress_lzss(map_data[offset : offset + size]))
    return streams


# Decode consecutive 16-color CRAM banks. One bank is 16 big-endian RGB555
# words, or 32 bytes. The palette stream is descriptor stream 1, DMA-copied to
# descriptor->dst4 by func_06008588. Its destination setup is visible around
# 0x0606C814..0x0606C83C in f606C774.s.
def decode_palette(data):
    if len(data) < 32 or len(data) % 32:
        raise ValueError(
            f"palette stream size {len(data)} is not a whole number of 16-color banks"
        )
    colors = []
    # Saturn color words store red in bits 0..4, green in 5..9, and blue
    # in 10..14. Bit 15 is ignored here.
    for value in struct.unpack(f">{len(data) // 2}H", data):
        red = (value & 0x1F) * 255 // 31
        green = ((value >> 5) & 0x1F) * 255 // 31
        blue = ((value >> 10) & 0x1F) * 255 // 31
        colors.append((red, green, blue))
    return colors


# Render one decompressed pattern-name plane to packed RGB/RGBA pixels.
# The runtime equivalent converts source entries into the VDP2 name table in
# func_0600871C (asm/saturn/zero/f_nonmat/f600871C.s); the fixed-plane path is
# also readable as func_060089F0 in src/saturn/zero.c around line 600.
def render_layer(
    characters, palette_data, map_data, transparent_zero=False,
    retained_palette_data=()
):
    # The map stream starts with be16 width and height in 8x8 tiles, then
    # width * height big-endian u16 entries in row-major order.
    if len(map_data) < 4:
        raise ValueError("map stream has no width/height header")
    width, height = struct.unpack_from(">HH", map_data)
    expected = 4 + width * height * 2
    # STAGE_01 room 18 layer 0 is shipped with a 720-tile header but 1280
    # complete columns. func_0600871C checks stage ID 0x41, room 0x12, and
    # layer 0, then stores 0x0500 into descriptor width +0x28. The comparisons
    # and store are at 0x06008740..0x0600875E in f600871C.s.
    if (
        len(map_data) > expected
        and height
        and (len(map_data) - 4) % (height * 2) == 0
    ):
        payload_width = (len(map_data) - 4) // (height * 2)
        if payload_width == 0x500 and width == 720:
            width = payload_width
            expected = len(map_data)
    # STAGE_03 room 10 has small real truncations. Runtime reads from a
    # scratch buffer, so match it by zero-filling shortages up to 32 bytes.
    if len(map_data) < expected:
        missing = expected - len(map_data)
        if missing > 32:
            raise ValueError(
                f"map is {width}x{height}, needs {expected} bytes, "
                f"got {len(map_data)}"
            )
        map_data += bytes(missing)
    # Each 8x8 4bpp character is 32 bytes: four packed bytes per row.
    if len(characters) % 32:
        raise ValueError("4bpp character stream size is not divisible by 32")

    # Palette uploads can be partial. func_06008588 DMA-copies only the current
    # stream's byte count and does not clear later CRAM banks. If this layer
    # references a bank it did not upload, fall back through earlier room
    # layers in reverse order to model the retained CRAM contents.
    palette = decode_palette(palette_data)
    retained_palettes = [decode_palette(data) for data in retained_palette_data]
    tile_count = len(characters) // 32
    # One-word VDP2 pattern name:
    #   bits 0..9 tile, bit 10 H flip, bit 11 V flip, bits 12..15 bank.
    # func_0600871C reads each source u16 at 0x060088BC and applies the
    # descriptor palette-bank adjustment (unk24 << 12) at
    # 0x06008840..0x06008852. func_060089F0 performs the same adjustment in C.
    entries = struct.unpack_from(f">{width * height}H", map_data, 4)
    channels = 4 if transparent_zero else 3
    pixels = bytearray(width * 8 * height * 8 * channels)
    stride = width * 8 * channels

    for map_y in range(height):
        for map_x in range(width):
            entry = entries[map_y * width + map_x]
            tile = entry & 0x03FF
            palette_bank = entry >> 12
            if tile >= tile_count:
                raise ValueError(
                    f"tile {tile} at ({map_x}, {map_y}) exceeds {tile_count} characters"
                )
            flip_x = bool(entry & 0x0400)
            flip_y = bool(entry & 0x0800)
            # Tile indices address 32-byte character records directly.
            tile_data = characters[tile * 32 : tile * 32 + 32]
            for y in range(8):
                source_y = 7 - y if flip_y else y
                for x in range(8):
                    source_x = 7 - x if flip_x else x
                    # High nibble is the left/even pixel; low nibble is
                    # the right/odd pixel.
                    packed = tile_data[source_y * 4 + source_x // 2]
                    color_index = packed >> 4 if source_x % 2 == 0 else packed & 0xF
                    palette_index = palette_bank * 16 + color_index
                    selected_palette = palette
                    if palette_index >= len(selected_palette):
                        selected_palette = next(
                            (p for p in retained_palettes if palette_index < len(p)),
                            selected_palette,
                        )
                    if palette_index >= len(selected_palette):
                        raise ValueError(
                            f"palette bank {palette_bank} at ({map_x}, {map_y}) "
                            f"exceeds {len(palette) // 16} decoded banks"
                        )
                    color = selected_palette[palette_index]
                    # Color index zero is transparent for compositing.
                    # Standalone layer 0 stays opaque unless requested.
                    if transparent_zero:
                        color += (0 if color_index == 0 else 255,)
                    output = (
                        (map_y * 8 + y) * stride + (map_x * 8 + x) * channels
                    )
                    pixels[output : output + channels] = bytes(color)

    return width * 8, height * 8, bytes(pixels), tile_count


# Render every populated room for one layer and place the rooms on the
# stage's 320x256 screen-cell grid. Room bounds are used by InitRoom
# (src/saturn/game.c, around line 93), while func_0606C774 selects the matching
# layer descriptors for the current room.
def render_stage(prg, map_data, layer, extent=None, transparent_zero=None, descriptor_set=0):
    # PRG +0x10 is the shared six-byte room-bounds table. The selected export
    # set supplies counts, setup bytes, and the table after counts. These are
    # the same header globals loaded by func_0606C774.
    bounds_offset = read_u32(prg, 0x10) - STAGE_LOAD_ADDRESS
    counts_offset = read_u32(prg, export_offset(descriptor_set, 0x14)) - STAGE_LOAD_ADDRESS
    setup_offset = read_u32(prg, export_offset(descriptor_set, 0x1C)) - STAGE_LOAD_ADDRESS
    next_table = read_u32(prg, export_offset(descriptor_set, 0x20)) - STAGE_LOAD_ADDRESS
    # Count and offset tables use 36 bytes per room. In ordinary overlays,
    # the +0x20 export follows the count table, so their span gives the
    # room count. This also rejects non-stage headers such as TITLE.PRG.
    table_size = next_table - counts_offset
    if table_size <= 0 or table_size % 36:
        raise ValueError("cannot derive room count from stage export tables")
    room_count = table_size // 36

    # Keep decoded room images until the overall stage extent is known.
    rooms = []
    for room in range(room_count):
        record = bounds_offset + room * 6
        if record + 6 > len(prg):
            raise ValueError("room bounds table lies outside the stage PRG")
        # Bounds are inclusive screen coordinates. Bytes 4 and 5 in the
        # record are transition/room metadata and are not needed here.
        left, top, right, bottom = prg[record : record + 4]
        if left == 0xFF or right < left or bottom < top:
            continue
        try:
            streams = stage_streams(prg, map_data, room, layer, descriptor_set)
        except ValueError as error:
            if "is empty" in str(error):
                continue
            raise
        # By default layer 0 is opaque for a standalone layer dump and
        # layers 1/2 use color-zero transparency.
        use_transparency = layer != 0 if transparent_zero is None else transparent_zero
        # Earlier layers are the possible source of higher palette banks
        # left in CRAM after a short upload by the current layer.
        retained_palettes = []
        for previous_layer in range(layer - 1, -1, -1):
            try:
                retained_palettes.append(
                    stage_streams(
                        prg, map_data, room, previous_layer, descriptor_set
                    )[1]
                )
            except ValueError as error:
                if "is empty" not in str(error):
                    raise
        width, height, pixels, _ = render_layer(
            *streams, transparent_zero=use_transparency,
            retained_palette_data=retained_palettes
        )
        channels = 4 if use_transparency else 3
        # One room-grid cell is 320x256 pixels, or 40x32 tiles.
        expected_width = (right - left + 1) * 320
        expected_height = (bottom - top + 1) * 256
        # Setup records are nine bytes per room, three per layer: horizontal
        # divisor, vertical divisor, and wrap flags. func_0600871C reads the
        # divisors from descriptor +0x2C/+0x2E at 0x06008760..0x0600878A and
        # tests flag bits 0/1 at 0x060087DA..0x06008822. Its clamp/wrap source
        # stepping continues through 0x060089CA. A zero divisor fixes that axis.
        if (width, height) != (expected_width, expected_height):
            setup = setup_offset + room * 9 + layer * 3
            divisor_x, divisor_y, flags = prg[setup : setup + 3]
            wrap_x = bool(flags & 1) or divisor_x == 0
            wrap_y = bool(flags & 2) or divisor_y == 0
            # Whole-stage rendering uses phase zero at the room origin.
            # Wrapped/fixed axes repeat; nonwrapping oversized axes crop;
            # nonwrapping undersized axes remain transparent/black.
            source = pixels
            source_width = width
            source_height = height
            width = expected_width
            height = expected_height
            pixels = bytearray(width * height * channels)
            for y in range(height):
                source_y = y % source_height if wrap_y else y
                for x in range(width):
                    source_x = x % source_width if wrap_x else x
                    if source_x >= source_width or source_y >= source_height:
                        continue
                    source_pixel = (source_y * source_width + source_x) * channels
                    output_pixel = (y * width + x) * channels
                    pixels[output_pixel : output_pixel + channels] = source[
                        source_pixel : source_pixel + channels
                    ]
            pixels = bytes(pixels)
        rooms.append((left, top, right, bottom, width, height, pixels))

    if not rooms:
        raise ValueError(f"stage has no populated rooms on layer {layer}")
    # A caller-provided extent keeps all composite layers on the same
    # canvas even when a layer has fewer populated rooms.
    if extent is None:
        min_x = min(room[0] for room in rooms)
        min_y = min(room[1] for room in rooms)
        max_x = max(room[2] for room in rooms)
        max_y = max(room[3] for room in rooms)
    else:
        min_x, min_y, max_x, max_y = extent
    width = (max_x - min_x + 1) * 320
    height = (max_y - min_y + 1) * 256
    use_transparency = layer != 0 if transparent_zero is None else transparent_zero
    channels = 4 if use_transparency else 3
    pixels = bytearray(width * height * channels)
    destination_stride = width * channels

    # Translate room screen coordinates into pixels relative to the
    # minimum populated stage coordinate.
    for left, top, _, _, room_width, room_height, room_pixels in rooms:
        x = (left - min_x) * 320
        y = (top - min_y) * 256
        source_stride = room_width * channels
        for row in range(room_height):
            source = row * source_stride
            destination = (y + row) * destination_stride + x * channels
            pixels[destination : destination + source_stride] = room_pixels[
                source : source + source_stride
            ]

    return width, height, bytes(pixels), len(rooms), (min_x, min_y, max_x, max_y)


# Composite the three MAP layers room by room. func_0606C774 configures dumped
# layers 0/1/2 as VDP2 NBG1/NBG2/NBG3, so numeric layer order is not necessarily
# back-to-front. Priority records eventually feed the Sega SCL priority setup;
# see SCL_SetPriority / SetDefaultSCLPriority in that setup path.
def composite_stage(prg, map_data, descriptor_set=0):
    # Composite inputs are all RGBA, including layer 0, so empty pixels do
    # not overwrite another layer or an unoccupied room-grid cell.
    width, height, base, _, extent = render_stage(
        prg, map_data, 0, transparent_zero=True, descriptor_set=descriptor_set
    )
    layers = {0: base}
    # Boss and other overlays may omit a whole layer. Treat that layer as
    # a transparent plane in composite mode.
    for layer in (1, 2):
        try:
            layer_width, layer_height, pixels, _, _ = render_stage(
                prg, map_data, layer, extent=extent, transparent_zero=True,
                descriptor_set=descriptor_set
            )
        except ValueError as error:
            if str(error) != f"stage has no populated rooms on layer {layer}":
                raise
            layer_width, layer_height = width, height
            pixels = bytes(width * height * 4)
        if (layer_width, layer_height) != (width, height):
            raise ValueError("composite layers have inconsistent dimensions")
        layers[layer] = pixels

    # PRG +0x24 points to 12-byte priority records: NBG0..NBG3 followed by
    # sprite types 0..7. The NBG mapping comes from the three layer setups in
    # func_0606C774; use bytes 1, 2, and 3 for dumped layers 0, 1, and 2.
    min_x, min_y, max_x, max_y = extent
    bounds_offset = read_u32(prg, 0x10) - STAGE_LOAD_ADDRESS
    counts_offset = read_u32(prg, export_offset(descriptor_set, 0x14)) - STAGE_LOAD_ADDRESS
    next_table = read_u32(prg, export_offset(descriptor_set, 0x20)) - STAGE_LOAD_ADDRESS
    priority_offset = read_u32(prg, export_offset(descriptor_set, 0x24)) - STAGE_LOAD_ADDRESS
    room_count = (next_table - counts_offset) // 36
    output = bytearray(width * height * 4)

    # Priorities are room-specific, so sorting must happen inside this
    # loop rather than once for the whole stage.
    for room in range(room_count):
        record = bounds_offset + room * 6
        left, top, right, bottom = prg[record : record + 4]
        if (
            left == 0xFF
            or right < left
            or bottom < top
            or left < min_x
            or top < min_y
            or right > max_x
            or bottom > max_y
        ):
            continue
        priorities = prg[priority_offset + room * 12 : priority_offset + room * 12 + 12]
        if len(priorities) != 12:
            raise ValueError("room priority table lies outside the stage PRG")
        # Lower priority is farther back. Preserve numeric layer order for
        # ties through Python's stable sort. Dumped layers 0, 1, and 2
        # are configured as NBG1, NBG2, and NBG3. STAGE_15 room 1 is the
        # useful verification case: priorities 4, 2, 3 require stream
        # order layer 1, layer 2, layer 0 rather than numeric order.
        layer_order = sorted(range(3), key=lambda layer: priorities[layer + 1])
        start_x = (left - min_x) * 320
        start_y = (top - min_y) * 256
        room_width = (right - left + 1) * 320
        room_height = (bottom - top + 1) * 256
        # Alpha-over is simple replacement because decoded source pixels
        # have alpha 0 or 255 only.
        for layer in layer_order:
            source = layers[layer]
            for y in range(start_y, start_y + room_height):
                row_start = (y * width + start_x) * 4
                row_end = row_start + room_width * 4
                for offset in range(row_start, row_end, 4):
                    if source[offset + 3]:
                        output[offset : offset + 4] = source[offset : offset + 4]
    return width, height, bytes(output)


# Minimal PNG writer helpers. The renderer produces raw RGB or RGBA rows;
# no image-library dependency is needed.
def png_chunk(kind, data):
    return struct.pack(">I", len(data)) + kind + data + struct.pack(">I", zlib.crc32(kind + data))


def write_png(path, width, height, pixels):
    # Infer PNG truecolor vs truecolor-with-alpha from the pixel buffer.
    channels = len(pixels) // (width * height)
    if channels not in (3, 4):
        raise ValueError(f"unsupported PNG channel count {channels}")
    stride = width * channels
    # Prefix each scanline with filter type 0 (no filtering).
    rows = b"".join(b"\0" + pixels[y * stride : (y + 1) * stride] for y in range(height))
    color_type = 6 if channels == 4 else 2
    header = struct.pack(">IIBBBBB", width, height, 8, color_type, 0, 0, 0)
    png = b"\x89PNG\r\n\x1a\n"
    png += png_chunk(b"IHDR", header)
    png += png_chunk(b"IDAT", zlib.compress(rows, 9))
    png += png_chunk(b"IEND", b"")
    path.write_bytes(png)


# Build the same batch job list that used to live in dump_saturn_stages.py.
# A job is (output name, PRG path, MAP path, descriptor-set index).
def discover_batch_jobs(input_dir):
    pairs = sorted(
        prg
        for prg in input_dir.glob("*.PRG")
        if prg.with_suffix(".MAP").is_file()
    )

    # TITLE.PRG is a UI module, not a stage overlay. Its header does not contain
    # the room/count/offset/setup/priority exports published by func_0601AC48.
    jobs = [
        (prg.stem, prg, prg.with_suffix(".MAP"), 0)
        for prg in pairs
        if prg.stem != "TITLE"
    ]

    boss_r14 = input_dir / "BOSS_R14.PRG"
    if boss_r14 in pairs:
        jobs = [job for job in jobs if job[1] != boss_r14]
        # BOSS_R14.MAP is a 22-byte palette payload. The PRG's background
        # descriptors retain offsets into RSTAGE14.MAP, which contains the
        # reverse-stage boss arena source streams.
        jobs.append(("BOSS_R14", boss_r14, input_dir / "RSTAGE14.MAP", 0))

    stage07 = input_dir / "STAGE_07.PRG"
    if stage07 in pairs:
        jobs = [job for job in jobs if job[1] != stage07]
        # func_0601AC48 selects these five export pointers in 20-byte strides.
        # Set 0 describes STAGE_7A.MAP and set 1 describes STAGE_7B.MAP; the
        # same bounds table at PRG +0x10 is shared by both parts.
        jobs.extend(
            [
                ("STAGE_7A", stage07, input_dir / "STAGE_7A.MAP", 0),
                ("STAGE_7B", stage07, input_dir / "STAGE_7B.MAP", 1),
            ]
        )

    jobs.sort(key=lambda job: job[0])
    return pairs, jobs


# ProcessPoolExecutor calls this top-level function in a separate interpreter.
# Parallelism is intentionally outside the format code: each worker runs the
# same ordinary composite_stage path used by direct mode.
def render_batch_job(name, prg_path, map_path, output, descriptor_set):
    prg = prg_path.read_bytes()
    map_data = map_path.read_bytes()
    width, height, pixels = composite_stage(prg, map_data, descriptor_set)
    write_png(output, width, height, pixels)
    return name, width, height


def run_batch(input_dir, output_dir, force, fail_fast, jobs):
    pairs, discovered = discover_batch_jobs(input_dir)
    if not pairs:
        raise ValueError(f"no matching PRG/MAP pairs found in {input_dir}")

    output_dir.mkdir(parents=True, exist_ok=True)
    pending = []
    skipped = 0
    for index, (name, prg, map_path, descriptor_set) in enumerate(discovered, 1):
        output = output_dir / f"{name}.png"
        prefix = f"[{index:02}/{len(discovered):02}] {name}"
        if output.exists() and not force:
            print(f"{prefix}: skipped (already exists)", flush=True)
            skipped += 1
            continue
        pending.append((index, name, prg, map_path, output, descriptor_set))

    if not pending:
        print(
            f"completed: 0 rendered, {skipped} skipped, 0 failed; "
            f"output: {output_dir}"
        )
        return

    failures = []
    rendered = 0
    worker_count = min(jobs, len(pending))
    with ProcessPoolExecutor(max_workers=worker_count) as executor:
        future_jobs = {}
        for index, name, prg, map_path, output, descriptor_set in pending:
            prefix = f"[{index:02}/{len(discovered):02}] {name}"
            print(f"{prefix}: rendering", flush=True)
            future = executor.submit(
                render_batch_job,
                name,
                prg,
                map_path,
                output,
                descriptor_set,
            )
            future_jobs[future] = (index, name)

        for future in as_completed(future_jobs):
            index, name = future_jobs[future]
            prefix = f"[{index:02}/{len(discovered):02}] {name}"
            try:
                _, width, height = future.result()
            except Exception as error:
                detail = str(error).strip().splitlines()
                detail = detail[-1] if detail else type(error).__name__
                print(f"{prefix}: FAILED: {detail}", flush=True)
                failures.append((name, detail))
                if fail_fast:
                    # Already-running workers cannot be stopped safely, but
                    # futures that have not started are cancelled.
                    for other in future_jobs:
                        other.cancel()
                    break
            else:
                print(f"{prefix}: done ({width}x{height})", flush=True)
                rendered += 1

    print(
        f"completed: {rendered} rendered, {skipped} skipped, "
        f"{len(failures)} failed; output: {output_dir}"
    )
    if failures:
        print("failures:")
        for name, detail in failures:
            print(f"  {name}: {detail}")
        raise SystemExit(1)


# CLI supports direct room/layer rendering and the former wrapper's batch mode.
def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("prg", type=Path, nargs="?", help="stage PRG, such as STAGE_02.PRG")
    parser.add_argument("map", type=Path, nargs="?", help="matching stage MAP")
    parser.add_argument("output", type=Path, nargs="?", help="output PNG")
    parser.add_argument("--room", type=int, default=0)
    parser.add_argument("--layer", type=int, choices=range(3), default=0)
    output_mode = parser.add_mutually_exclusive_group()
    output_mode.add_argument(
        "--whole-stage", action="store_true", help="place every populated room"
    )
    parser.add_argument(
        "--descriptor-set", type=int, choices=(0, 1), default=0,
        help="alternate 20-byte stage export set (used by multi-part stages)",
    )
    output_mode.add_argument(
        "--composite",
        action="store_true",
        help="composite the whole stage using each room's VDP2 priorities",
    )

    batch = parser.add_argument_group("batch mode")
    batch.add_argument(
        "--batch", action="store_true", help="render every supported stage composite"
    )
    batch.add_argument(
        "--input-dir", type=Path, default=Path("disks/saturn"), help="disc files"
    )
    batch.add_argument(
        "--output-dir", type=Path, default=Path("dumps"), help="PNG destination"
    )
    batch.add_argument(
        "--force", action="store_true", help="replace PNGs that already exist"
    )
    batch.add_argument(
        "--fail-fast", action="store_true", help="stop reporting after the first failure"
    )
    batch.add_argument(
        "--jobs",
        type=int,
        default=max(1, min(4, os.cpu_count() or 1)),
        help="parallel stage processes (default: up to 4)",
    )
    args = parser.parse_args()

    if args.jobs < 1:
        parser.error("--jobs must be at least 1")

    if args.batch:
        if any(value is not None for value in (args.prg, args.map, args.output)):
            parser.error("--batch does not accept PRG, MAP, or output positionals")
        run_batch(
            args.input_dir,
            args.output_dir,
            args.force,
            args.fail_fast,
            args.jobs,
        )
        return

    if None in (args.prg, args.map, args.output):
        parser.error("direct mode requires PRG, MAP, and output paths")

    # MAP bytes stay compressed until stage_streams selects the exact
    # offset/count slices from the PRG tables.
    prg = args.prg.read_bytes()
    map_data = args.map.read_bytes()
    if args.composite:
        width, height, pixels = composite_stage(prg, map_data, args.descriptor_set)
        description = "whole stage composite (per-room VDP2 priorities)"
    elif args.whole_stage:
        width, height, pixels, room_count, _ = render_stage(
            prg, map_data, args.layer, descriptor_set=args.descriptor_set
        )
        description = f"whole stage layer {args.layer}: {room_count} rooms"
    else:
        streams = stage_streams(
            prg, map_data, args.room, args.layer, args.descriptor_set
        )

        # Match runtime CRAM retention in direct room mode too. A short palette
        # upload replaces low banks without clearing higher banks left by an
        # earlier layer. This is needed by cases such as STAGE_7A room 7 layer 2.
        retained_palettes = []
        for previous_layer in range(args.layer - 1, -1, -1):
            try:
                retained_palettes.append(
                    stage_streams(
                        prg,
                        map_data,
                        args.room,
                        previous_layer,
                        args.descriptor_set,
                    )[1]
                )
            except ValueError as error:
                if "is empty" not in str(error):
                    raise

        width, height, pixels, tile_count = render_layer(
            *streams,
            transparent_zero=args.layer != 0,
            retained_palette_data=retained_palettes,
        )
        description = f"room {args.room} layer {args.layer}: {tile_count} characters"

    write_png(args.output, width, height, pixels)
    print(f"rendered {description}, {width}x{height} -> {args.output}")


if __name__ == "__main__":
    main()
