# Author: bismurphy. Please feel free to contact with any questions!
# This tool may be non-intuitive and/or buggy to use; I am happy to make
# fixes if anyone requests them.

# Displays animations for entities.
# Uses display_texture.py as dependency, so make sure that is available to it.

# Example use case: We wanted to figure out what entity EntityLightningCloud is
# in NO3/NP3. We can see in its initialization that its Animset is 0x8001
# and its palette is 0. Then, we can do:
# python3 tools/display_animation.py LIVE no3 0x8001 0 150 100
# To review all the frames in that animation.
# LIVE will pull a live vram dump from pcsx. no3 is the overlay to grab sprite
# data from. 0x8001 is that animset, 0 is the clut, and then 150x100 will be our
# viewport size as we click through the entities.

import argparse
import re
import matplotlib.pyplot as plt
from matplotlib.widgets import Button
import numpy as np

from PIL import Image

from play_animation import AnimationShower, load_array_from_file

# holds the list of animsets
DRA_ANIM_ARRAY_FILE = "src/dra/d_37d8.c"
# some day this may have a symbol name
DRA_ANIM_ARRAY = "D_800A3B70"
# holds the individual animsets
DRA_ANIMSET_FILE = "src/dra/d_2F324.c"


def load_init_from_ovl(ovl_name, init_name):
    with open("src/st/" + ovl_name + "/e_init.c") as f:
        initlines = f.readlines()
    for line in initlines:
        if init_name in line:
            line = line.replace("PAL_NULL", "0")
            initSet = re.findall(r"(?<={)[^}]*", line)[0].split(",")

            if "ANIMSET_OVL" in initSet[0]:
                arg = re.findall(r"(?<=\()[^\)]*", initSet[0])[0]
                initSet[0] = hex(0x8000 | int(arg, 0))
            if "ANIMSET_DRA" in initSet[0]:
                arg = re.findall(r"(?<=\()[^\)]*", initSet[0])[0]
                initSet[0] = arg
            found_vals = [int(x, 0) for x in initSet]
            break
    animset, animcurframe, unk5A, palette, enemyId = found_vals
    return animset, palette, unk5A


def show_animset(ovl_name, anim_num, arg_palette, view_w, view_h, unk5A, dump_filename):

    # Now we have an array that tells us the name of all the frames.
    # Start GUI code.
    fig, ax = plt.subplots()
    ax.set_xlim(-32, 32)
    ax.set_ylim(-32, 32)
    plt.subplots_adjust(bottom=0.15)

    class ControllableShower(AnimationShower):
        def __init__(self, dump_filename, anim_num, ovl_name, arg_palette, unk5A):
            super().__init__(dump_filename, anim_num, ovl_name, arg_palette, unk5A)
            # initialize to image 1
            self.anim_index = 1
            self.im = ax.imshow(
                [[]], extent=[-view_w / 2, view_w / 2, -view_h / 2, view_h / 2]
            )
            self.update_image()

        def update_image(self):
            ax.set_title(
                f"Displaying {ovl_name} animation {anim_num}, index {self.anim_index}"
            )
            img = self.render_frame(self.anim_index)
            self.im.set_data(img)
            fig.canvas.draw_idle()

        def prev(self, event):
            self.anim_index -= 1
            if self.anim_index < 1:
                self.anim_index = len(self.framearray) - 1
            self.update_image()

        def next(self, event):
            self.anim_index += 1
            if self.anim_index >= len(self.framearray):
                self.anim_index = 1
            self.update_image()

    shower = ControllableShower(
        dump_filename, anim_num, ovl_name, arg_palette, unk5A
    )  # imported from play_animation.py

    prev_button = Button(plt.axes([0.1, 0.025, 0.3, 0.1], facecolor="k"), "Prev Frame")
    prev_button.on_clicked(shower.prev)
    next_button = Button(plt.axes([0.6, 0.025, 0.3, 0.1], facecolor="k"), "Next Frame")
    next_button.on_clicked(shower.next)
    img = shower.render_frame(1)
    ax.imshow(img)
    plt.show()


parser = argparse.ArgumentParser(description="Renders in-game animations from ANIMSET")

parser.add_argument("dump_filename")

parser.add_argument("overlay", help="Overlay name. dra, no3, cen, etc")

parser.add_argument(
    "view_width", type=lambda x: int(x, 0), help="Width of your view window"
)

parser.add_argument(
    "view_height", type=lambda x: int(x, 0), help="Height of your view window"
)

parser.add_argument(
    "mode",
    help="Select a mode: INIT to choose an EInit from the overlay, or CUST to give custom args",
)

args = parser.parse_args()

if args.mode == "CUST":
    animset_num = int(input("Animset number; 2 for ANIMSET_DRA(2)\n"), 0)
    e_palette = int(input("Entity's Palette param\n"), 0)
    unk5A = input("Entity's unk5A value (optional, leave blank if you want)\n")
    if unk5A == "":
        unk5A = 0
    else:
        unk5A = int(unk5A, 0)
elif args.mode == "INIT":
    initName = input("Give name of the EInit from the overlay's e_init.c file:\n")
    animset_num, e_palette, unk5A = load_init_from_ovl(args.overlay, initName)
else:
    print('Mode is not one of "CUST" or "INIT", exiting')
    exit()

show_animset(
    args.overlay,
    animset_num,
    e_palette,
    args.view_width,
    args.view_height,
    unk5A,
    args.dump_filename,
)
