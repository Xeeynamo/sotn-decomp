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

import display_texture as dt
import argparse
import re
import matplotlib.pyplot as plt
from matplotlib.widgets import Button
import numpy as np

from PIL import Image

# holds the list of animsets
DRA_ANIM_ARRAY_FILE = "src/dra/63ED4.c"
# some day this may have a symbol name
DRA_ANIM_ARRAY = "D_800A3B70"
# holds the individual animsets
DRA_ANIMSET_FILE = "src/dra/d_2F324.c"


def load_array_from_file(filelines, arrayname):
    print(f"Trying to load {arrayname}")
    arraydata = ""
    inarray = False
    for line in filelines:
        if arrayname in line and "{" in line:
            inarray = True
        if inarray:
            arraydata += line
        if "}" in line:
            inarray = False
    # find the data between the curly braces
    pattern = r"\{([^}]*)\}"
    match = re.search(pattern, arraydata)
    if match:
        array_contents = match.group(1)
        array_contents = array_contents.rstrip(",")  # remove trailing comma if exists
        # strip whitespace and turn into list of members
        array_members = array_contents.replace(" ", "").split(",")
        return array_members
    print("Error loading animation array. Hmm.")
    exit()


def show_animset(ovl_name, anim_num, arg_palette, view_w, view_h, unk5A):

    # Now we have an array that tells us the name of all the frames.
    # Start GUI code.
    class AnimationShower:
        def __init__(self):
            self.anim_index = 1
            self.textureDisplayer = dt.textureDisplayer(texture_data)
            # Need to load the animation's frames now.
            # Depends on if we're an ANIMSET_DRA or ANIMSET_OVL.
            if anim_num & 0x8000:
                print("Overlay animation")
                assert ovl_name != "dra"
                spritebank = anim_num & 0x7FFF
                main_array_file = f"src/st/{ovl_name}/sprite_banks.h"
                main_array = "spriteBanks"
                animset_file = f"src/st/{ovl_name}/sprites.c"

            else:
                print("DRA animation")
                assert ovl_name == "dra"
                main_array_file = DRA_ANIM_ARRAY_FILE
                main_array = DRA_ANIM_ARRAY
                animset_file = DRA_ANIMSET_FILE
                spritebank = anim_num
            with open(main_array_file) as f:
                animdata = f.read().splitlines()
                animarray = load_array_from_file(animdata, main_array)
                anim_set_name = animarray[spritebank]
            print(f"Animation set {spritebank} is {anim_set_name}. Loading.")
            with open(animset_file) as f:
                self.framesdata = f.read().splitlines()
                print("Loading framearray")
                print(animset_file)
                self.framearray = load_array_from_file(self.framesdata, anim_set_name)
                print("Loaded framearray.")

        def prev(self, event):
            self.anim_index -= 1
            if self.anim_index < 1:
                self.anim_index = len(self.framearray) - 1
            self.render_frame()

        def next(self, event):
            self.anim_index += 1
            if self.anim_index >= len(self.framearray):
                self.anim_index = 1
            self.render_frame()

        def render_frame(self):
            print("RENDERING", self.anim_index)
            frame_name = self.framearray[self.anim_index]
            # prepend the s16 to make sure we get the actual array, not something that
            # points to the array
            frame_params = load_array_from_file(self.framesdata, "s16 " + frame_name)
            data_size = 1 + int(frame_params[0]) * 11
            frame_params = frame_params[:data_size]
            frame_params = [int(x) for x in frame_params]
            print(frame_params)
            # Now we follow the logic of RenderEntities.

            # r->spriteSheetIdx = *animFrame++;
            spriteSheetIdx = frame_params[0]
            frame_params = frame_params[1:]

            # Not prepared to handle this case.
            if spriteSheetIdx < 0 or spriteSheetIdx & 0x8000:
                print("I don't know what this is yet, need new program logic")
                exit()
            # Now skip to line 984. We're going to make an image from the individual images.
            overall_image = Image.new("RGBA", (view_w, view_h))
            for i in range(spriteSheetIdx):
                ax.clear()
                print(frame_params)
                frameFlags = frame_params[0]  # line 989
                tpage = frame_params[6]  # line 990
                tpage += unk5A  # line 991
                runk0 = tpage & 3  # 992
                tpage >>= 2  # 993
                xpivot = frame_params[1]  # 994
                ypivot = frame_params[2]  # 995
                width = frame_params[3]  # 996
                height = frame_params[4]  # 997

                # Skip all the logic with positioning and flipping.
                # Pick up at line 1062
                if arg_palette & 0x8000:
                    clut = arg_palette & 0x7FFF
                else:
                    clut = frame_params[5] + arg_palette
                u_0 = frame_params[7]
                v_0 = frame_params[8]
                u_1 = frame_params[9]
                v_1 = frame_params[10]
                assert u_1 - u_0 == width
                assert v_1 - v_0 == height
                print(
                    f"Loading texture: {tpage=}, {clut=}, {u_0=}, {v_0=}, {width=}, {height=}"
                )
                image = self.textureDisplayer.get_image(
                    tpage, clut, u_0, v_0, width, height
                )
                if frameFlags & 2:
                    image = np.flip(image, 1)
                    frameFlags -= 2
                if frameFlags != 0:
                    print("We have frame flags. Ignoring for now.", frameFlags)
                pil_image = Image.fromarray(image)
                # pass pil_image twice to get transparency
                overall_image.paste(
                    pil_image,
                    (view_w // 2 + xpivot, view_h // 2 + ypivot),
                    pil_image,
                )
                frame_params = frame_params[11:]
            ax.set_title(
                f'Frame #{self.anim_index} of {len(self.framearray)}; "{frame_name}"'
            )
            ax.imshow(overall_image)
            plt.draw()

    shower = AnimationShower()
    fig, ax = plt.subplots()
    ax.set_xlim(-32, 32)
    ax.set_ylim(-32, 32)
    plt.subplots_adjust(bottom=0.15)
    prev_button = Button(plt.axes([0.1, 0.025, 0.3, 0.1], facecolor="k"), "Prev Frame")
    prev_button.on_clicked(shower.prev)
    next_button = Button(plt.axes([0.6, 0.025, 0.3, 0.1], facecolor="k"), "Next Frame")
    next_button.on_clicked(shower.next)
    shower.render_frame()
    plt.show()


parser = argparse.ArgumentParser(description="Renders in-game animations from ANIMSET")

parser.add_argument("dump_filename")

parser.add_argument("overlay", help="Overlay name. dra, no3, cen, etc")
parser.add_argument(
    "animset_num", type=lambda x: int(x, 0), help="Animset number; 2 for ANIMSET_DRA(2)"
)
parser.add_argument(
    "e_palette", type=lambda x: int(x, 0), help="Entity's Palette param"
)

parser.add_argument(
    "view_width", type=lambda x: int(x, 0), help="Width of your view window"
)

parser.add_argument(
    "view_height", type=lambda x: int(x, 0), help="Height of your view window"
)

parser.add_argument(
    "--unk5A",
    type=lambda x: int(x, 0),
    default=0,
    help="Entity's unk5A value (optional)",
)

args = parser.parse_args()

texture_data = dt.load_raw_dump(args.dump_filename)
show_animset(
    args.overlay,
    args.animset_num,
    args.e_palette,
    args.view_width,
    args.view_height,
    args.unk5A,
)
