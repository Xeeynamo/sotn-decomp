# Written by bismurphy, please contact in case of bugs or feature requests!

# Used for debugging and especially identifying entities based on their primitives.
# If you have a primitive pulling a texture from a Tpage, with a Clut, and
# getting a texture from UV coordinates, this will attempt to show you the texture
# being loaded from those parameters.

# In order to do this, you will need a VRAM dump from the game, in the state
# where the texture pages are configured to include the entry of interest.
# That is, you need to make sure the thing you're looking for is loaded.

# To get the VRAM dump: In PCSX-Redux, activate the web server with the setting in
# Configuration > Emulation > Enable Web Server
# Then, in your browser, go to: http://localhost:8080/api/v1/gpu/vram/raw
# this will download the raw VRAM dump. It should be a megabyte. Put it alongside
# this script, then run this script with the args for the
# filename, tpage, clut, x, y, w, h that you want.

# Example use (while standing on the box in Alchemy Lab):
# python3 display_texture.py vram_on_box.raw 0xF 9 8 200 32 32

# Alternatively, to see the whole tpage, you can run with
# python3 display_texture.py vram_on_box.raw 0xF 9 --whole which will skip the coordinates.

# And to just view the clut, do:
# python3 display_texture.py vram_on_box.raw 0xF 9 --showclut
# which will let you view clut #9. (tpage is ignored in this mode)

import matplotlib.pyplot as plt
import numpy as np
import argparse


# Take a 5-5-5 encoded array and convert to RGB image.
# See PSYQ SDK document LIBOVR46.PDF, figure 8-3.
def convert_rgb555(in_array):
    out_array = []
    for in_row in in_array:
        out_row = []
        for i in range(0, len(in_row), 2):
            two_bytes = in_row[i : i + 2]
            two_bytes = two_bytes[::-1]
            bits = int.from_bytes(two_bytes)
            s = bits >> 15  # semi transparent flag
            b = bits >> 10 & 0b11111  # bits 14-10
            g = (bits >> 5) & 0b11111  # bits 9-5
            r = bits & 0b11111  # bits 4-0
            # Transform 5-bit to 8-bit color
            r = round(r / 31 * 255)
            g = round(g / 31 * 255)
            b = round(b / 31 * 255)
            pixel = [r, g, b]
            out_row.append(pixel)
        out_array.append(out_row)
    return np.array(out_array)


def load_stage_cluts(full_image):
    # Load cluts from row 240 of the dump, starting from the midpoint
    cluts = []
    for i in range(16):
        left = 512 + i * 16
        right = left + 16
        clut = full_image[240:241, left:right]
        cluts.append(clut)
    return cluts


# Load the cluts that come in the big block under the frame buffers. Rows 240-256, from 0 to 256
def load_global_cluts(full_image):
    clut_zone = full_image[240:256, 0:256]
    clut_set = []
    for idx in range(256):
        row_number = idx >> 4
        col_number = idx & 0b1111
        clut = clut_zone[
            row_number : row_number + 1, col_number * 16 : (col_number + 1) * 16
        ]
        clut_set.append(clut)
    return clut_set


# Once we have a tpage and a clut, apply that clut to color the tpage.
def color_tpage(tpage, clut):
    height, width = tpage.shape
    image = []
    for y in range(height):
        img_row = []
        for x in range(width):
            # Load one byte from the tpage.
            px = tpage[y][x]
            # The byte encodes two pixels in its upper and lower halfs.
            # Extract each half.
            px1 = px & 0b1111
            px2 = px >> 4
            # Individually, use the clut as a lookup table to get the real color.
            color1 = clut[px1]
            color2 = clut[px2]
            # Put each of those two rows into the image.
            img_row.append(color1)
            img_row.append(color2)
        image.append(img_row)
    return np.array(image)


# Experimentally determined. For a tpage from 0x00 to 0x1F, get that tpage
# out of VRAM.
def get_tpage_by_number(raw_dump, tpage_num):
    assert 0 < tpage_num < 0x20
    tpage_row = tpage_num >= 0x10  # Row 0 or 1. First 16 are row 0, then row 1
    tpage_top = tpage_row * 256  # rows are 256 pixels tall so this is where it starts
    tpage_bottom = tpage_top + 256
    tpage_left = (
        tpage_num % 16
    ) * 128  # Modulo 16 gets the horizonal coordinate, then they are 128 pixels wide.
    # Note: tpages are actually 256 pixels wide, but at 4 bits per pixel, they appear half as wide in our vram dump.
    tpage_right = tpage_left + 128
    return raw_dump[tpage_top:tpage_bottom, tpage_left:tpage_right]


# Gets the clut from the dumped image. Note: Return type is a 2D numpy array which has height of 1.
# This allows displaying the clut as an image. Do clut[0] to get the 1D clut as an actual lookup.
def get_clut_by_number(colored_dump, clut_number):
    # Stage cluts are swapped out in each stage (this is my own naming)
    stage_cluts = load_stage_cluts(colored_dump)
    # These global cluts are the 256 that sit right below the frame buffers
    global_cluts = load_global_cluts(colored_dump)

    # This heuristic probably needs work, but it functions for now.
    if clut_number < 0x100:
        # note: we use [0] since a CLUT is a 2-d image with a single row. We want it as a 1-d lookup table.
        return stage_cluts[clut_number]
    else:
        return global_cluts[clut_number - 0x100]


# For a given tpage and clut, retrieve the tpage from the raw dump, and apply
# the clut to that tpage.
def retrieve_colored_tpage(raw_dump, tpage_number, clut_number):
    # Load all the data as rgb555, the native format cluts are specified in.
    colored = convert_rgb555(raw_dump)
    tpage_rendering_clut = get_clut_by_number(colored, clut_number)[0]

    # Now we have our tpage rendering clut extracted, get the tpage, and apply that clut.
    tpage = get_tpage_by_number(raw_dump, tpage_number)
    colored_tpage = color_tpage(tpage, tpage_rendering_clut)
    return colored_tpage


def draw_tpage_selection(raw_dump, tpage_number, clut_number, left, top, width, height):
    # Get the tpage with the proper clut applied
    ctp = retrieve_colored_tpage(raw_dump, tpage_number, clut_number)
    # Crop it to match the needed UV coords, and display it
    segment = ctp[top : top + height, left : left + width]
    plt.imshow(segment)
    plt.show()


# For the chosen filename for the vram dump, we load the bytes, convert
# to a numpy array, and transform this to a rectangular layout in vram.
def load_raw_dump(filename):
    with open(filename, "rb") as dumpfile:
        dumpbytes = dumpfile.read()
    datasize = len(dumpbytes)
    bytestring = np.frombuffer(dumpbytes, dtype=np.uint8)
    return np.reshape(bytestring, (512, int(datasize / 512)))


parser = argparse.ArgumentParser(description="Renders textures from VRAM dumps")
parser.add_argument("dump_filename")
# Load the numerical values; the lambda auto-detects decimal or hexadecimal and processes either.
parser.add_argument("tpage_num", type=lambda x: int(x, 0), help="Tpage number")
parser.add_argument("clut_num", type=lambda x: int(x, 0), help="CLUT number")
parser.add_argument("UV_vals", nargs="*", type=lambda x: int(x, 0), help="x, y, w, h")

# Alternate run modes
parser.add_argument("--whole", action="store_true", help="Show the whole tpage+clut")
parser.add_argument(
    "--showclut", action="store_true", help="Just show the 16 colors in the CLUT"
)


args = parser.parse_args()

array = load_raw_dump(args.dump_filename)
if args.showclut:
    colored = convert_rgb555(array)
    clut = get_clut_by_number(colored, args.clut_num)
    plt.imshow(clut)
    plt.show()
elif args.whole:
    draw_tpage_selection(array, args.tpage_num, args.clut_num, 0, 0, 256, 256)
else:
    draw_tpage_selection(array, args.tpage_num, args.clut_num, *args.UV_vals)
