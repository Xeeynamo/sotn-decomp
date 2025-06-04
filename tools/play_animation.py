# Author: bismurphy

# Renders the animations declared in a .c file (or .h file). Requires that:
# 1. There exists a u8 array in the specified file, which...
# 2. Has been fully declared as static, with all values pulled into the function as .data and ...
# 3. Is called in an entity updating function. Further...
# 4. The function be decompiled, and ...
# 5. The function contain a call to AnimateEntity
# 6. The argument to AnimateEntity must be an array declared in the overlay's e_init.c

# As with other texture/animation viewing tools, can hook into PCSX
# Example usage: python3 tools/play_animation.py LIVE no3 src/st/no3/e_warg.c
import display_texture as dt

import argparse
import re
import matplotlib.pyplot as plt
from matplotlib.widgets import Button
from PIL import Image
import numpy as np
import matplotlib.animation as animation
import time

PRINT_DEBUG = False


def print_debug(s):
    if PRINT_DEBUG:
        print(s)


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


# Get every array of u8's and return as a Python dictionary
def load_anims(src_file):
    with open(src_file) as f:
        file_lines = f.read().split("\n")
    loaded_anims = {}
    for i, line in enumerate(file_lines):
        if line.startswith("static u8"):
            # handle the potential of multi-line animations
            anim = ""
            line_idx = 0
            while ";" not in anim:
                anim += file_lines[i + line_idx]
                line_idx += 1
            # got full animation line. Strip spaces especially since line spacing might be weird.
            anim = anim.replace(" ", "")
            # Now use regex to find name and the data between the curly brackets
            anim_name = re.findall(r"(?<=staticu8)[^\[]*", anim)[0]
            anim_data = re.findall(r"(?<={)[^}]*", anim)[0]
            # Turn the data into a Python list of numbers
            anim_data = [int(x, 0) for x in anim_data.split(",")]
            loaded_anims[anim_name] = anim_data
    return loaded_anims


def get_initializer_for_ent(anim_name, src_file, overlay):
    initName = None
    print(f"Getting animset for animation {anim_name} in {src_file}, part of {overlay}")
    with open(src_file) as f:
        filelines = f.readlines()
    for i, line in enumerate(filelines):
        if anim_name in line and "static u8" not in line:
            # Now we've found a line where it's used. Search backward for
            # a call to InitializeEntity.
            print(f"Anim used in line {i}:")
            print(line)
            for lookback in range(i, 0, -1):
                lbline = filelines[lookback]
                if "InitializeEntity" in lbline:
                    print("Best guess entity initializer:", lbline)
                    initName = re.findall(r"(?<=\()[^\)]*", lbline)[0]
    if initName is None:
        # if we reach this point, we didn't find an automatic initializer
        # Prompt the user.
        options = []
        for line in filelines:
            if "InitializeEntity" in line:
                option = re.findall(r"(?<=\()[^\)]*", line)[0]
                if option not in options:
                    options.append(option)
        for i, it in enumerate(options):
            print(f" [{i}]: {it}")
        initializer_idx = int(input("Select argument above for InitializeEntity: "))
        initName = options[initializer_idx]
    # Now we know the name of the entity initializer.
    # Fetch the value of it from the overlay e_init file.
    with open("src/st/" + overlay + "/e_init.c") as f:
        initlines = f.readlines()
    for line in initlines:
        if initName in line:
            initSet = re.findall(r"(?<={)[^}]*", line)[0].split(",")
            print(initSet)
            return [int(x, 0) for x in initSet]


class AnimationShower:
    def __init__(self, anim_num, overlay, palette, unk5A):
        self.palette = palette
        self.unk5A = unk5A
        self.textureDisplayer = dt.textureDisplayer(texture_data)
        # Need to load the animation's frames now.
        # Depends on if we're an ANIMSET_DRA or ANIMSET_OVL.
        if anim_num & 0x8000:
            print("Overlay animation")
            assert overlay != "dra"
            spritebank = anim_num & 0x7FFF
            main_array_file = f"src/st/{overlay}/gen/sprite_banks.h"
            main_array = "spriteBanks"
            animset_file = f"src/st/{overlay}/gen/sprites.c"

        else:
            print(
                "DRA animation. Not supported as of now. Bug bismurphy to implement it :)"
            )
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

    def render_frame(self, anim_index):
        print_debug(f"RENDERING {anim_index}")
        frame_name = self.framearray[anim_index]
        # prepend the s16 to make sure we get the actual array, not something that
        # points to the array
        frame_params = load_array_from_file(self.framesdata, "s16 " + frame_name)
        data_size = 1 + int(frame_params[0]) * 11
        frame_params = frame_params[:data_size]
        frame_params = [int(x) for x in frame_params]
        print_debug("Loaded frame params:")
        print_debug(frame_params)
        # Now we follow the logic of RenderEntities.
        # r->spriteSheetIdx = *animFrame++;
        spriteSheetIdx = frame_params[0]
        frame_params = frame_params[1:]

        # Not prepared to handle this case.
        if spriteSheetIdx < 0 or spriteSheetIdx & 0x8000:
            print("I don't know what this is yet, need new program logic")
            exit()
        # Now skip to line 984. We're going to make an image from the individual images.
        overall_image = Image.new("RGBA", (256, 256))
        for i in range(spriteSheetIdx):
            print_debug(frame_params)
            frameFlags = frame_params[0]  # line 989
            tpage = frame_params[6]  # line 990
            tpage += self.unk5A  # line 991
            runk0 = tpage & 3  # 992
            tpage >>= 2  # 993
            xpivot = frame_params[1]  # 994
            ypivot = frame_params[2]  # 995
            width = frame_params[3]  # 996
            height = frame_params[4]  # 997

            # Skip all the logic with positioning and flipping.
            # Pick up at line 1062
            if self.palette & 0x8000:
                clut = self.palette & 0x7FFF
            else:
                clut = frame_params[5] + self.palette
            u_0 = frame_params[7]
            v_0 = frame_params[8]
            u_1 = frame_params[9]
            v_1 = frame_params[10]
            if runk0 & 1:
                u_0 += 0x80
                u_1 += 0x80
            if runk0 & 2:
                v_0 += 0x80
                v_1 += 0x80
            assert u_1 - u_0 == width
            assert v_1 - v_0 == height
            print_debug(
                f"Loading texture: {tpage=}, {clut=}, {u_0=}, {v_0=}, {width=}, {height=}"
            )
            image = self.textureDisplayer.get_image(
                tpage, clut, u_0, v_0, width, height
            )
            if frameFlags & 2:
                frameFlags -= 2
                image = np.flip(image, 1)
            if frameFlags & 8:
                frameFlags -= 8
                height -= 1
                if frameFlags & 1:
                    frameFlags -= 1
                    yPivot += 1
            if frameFlags != 0:
                print_debug(f"Ignoring frameFlags {frameFlags}")
            pil_image = Image.fromarray(image)
            view_w = 256
            view_h = 256
            print_debug(f"image all good, now pasting at {xpivot}, {ypivot}")
            # pass pil_image twice to get transparency
            overall_image.paste(
                pil_image,
                (view_w // 2 + xpivot, view_h // 2 + ypivot),
                pil_image,
            )
            frame_params = frame_params[11:]
        return overall_image

    def play_anim(self, animation_bytes, mpl_fig, mpl_ax):
        print("Playing animation:", animation_bytes)
        mpl_ax.clear()
        images = []
        for i in range(0, len(animation_bytes), 2):
            if animation_bytes[i] == 0 or animation_bytes[i] == 255:
                continue
            duration, anim_idx = animation_bytes[i : i + 2]
            picture = self.render_frame(anim_idx)
            for _ in range(duration):
                images.append([mpl_ax.imshow(picture)])
        self.activeAnimation = animation.ArtistAnimation(
            mpl_fig, images, interval=17, blit=True
        )


def main(overlay, src_file):
    anims = load_anims(src_file)
    print("Loaded animations:")
    for i, it in enumerate(anims.items()):
        print(f" [{i}]: {it}")
    anim_idx = int(input("Select number above: "))
    active_anim = list(anims.items())[anim_idx]
    # To render an animation, we need to know the entity's animation set.
    # That comes from InitializeEntity. Get the entity's initializer.
    initializer = get_initializer_for_ent(active_anim[0], src_file, overlay)
    anim_num, initframe, unk5A, palette, enemyNum = initializer
    print(anim_num, palette)

    shower = AnimationShower(anim_num, overlay, palette=palette, unk5A=unk5A)
    fig, ax = plt.subplots()
    ax.set_xlim(0, 256)
    ax.set_ylim(0, 256)
    plt.title(f"Displaying {overlay} animation {active_anim[0]} from {src_file}")
    plt.gca().invert_yaxis()
    shower.play_anim(active_anim[1], fig, ax)
    plt.show()


parser = argparse.ArgumentParser(description="Renders in-game animations from ANIMSET")

parser.add_argument("dump_filename")

parser.add_argument("overlay", help="Overlay name. dra, no3, cen, etc")

parser.add_argument(
    "filename",
    help="File name (potentially with path) to relevant source file. Could be .c or .h. Starts in src. Example: st/no3/e_warg.c",
)

args = parser.parse_args()
texture_data = dt.load_raw_dump(args.dump_filename)

main(
    args.overlay,
    args.filename,
)
