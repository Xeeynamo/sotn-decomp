# Displays animations for entities.
# Uses display_texture.py as dependency, so make sure that is available to it.

# A normal call might look like:
# python3 tools/display_animation.py LIVE 2
# This loads live textures from PCSX, and then displays ANIMSET_DRA(2).
import display_texture as dt
import argparse
import re
import matplotlib.pyplot as plt
from matplotlib.widgets import Button
import numpy as np

from PIL import Image

# holds the list of animsets
MAIN_ANIM_ARRAY_FILE = "src/dra/63ED4.c"
# some day this may have a symbol name
MAIN_ANIM_ARRAY = "D_800A3B70"
# holds the individual animsets
ANIMSET_FILE = "src/dra/d_2F324.c"

def load_array_from_file(filelines, arrayname):
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


def show_animset(anim_num, arg_palette, view_w, view_h):
    with open(MAIN_ANIM_ARRAY_FILE) as f:
        animdata = f.read().splitlines()
        animarray = load_array_from_file(animdata, MAIN_ANIM_ARRAY)
        anim_set_name = animarray[anim_num]
    print(f"Animation set {anim_num} is {anim_set_name}. Loading.")
    with open(ANIMSET_FILE) as f:
        framesdata = f.read().splitlines()
        framearray = load_array_from_file(framesdata, anim_set_name)
    # Now we have an array that tells us the name of all the frames.
    # Start GUI code.
    class AnimationShower:
        def __init__(self):
            self.anim_index = 1
            self.textureDisplayer = dt.textureDisplayer(texture_data)

        def prev(self, event):
            self.anim_index -= 1
            if self.anim_index < 1:
                self.anim_index = len(framearray) - 1
            self.render_frame()

        def next(self, event):
            self.anim_index += 1
            if self.anim_index >= len(framearray):
                self.anim_index = 1
            self.render_frame()

        def render_frame(self):
            print("RENDERING", self.anim_index)
            frame_name = framearray[self.anim_index]
            # prepend the s16 to make sure we get the actual array, not something that
            # points to the array
            frame_params = load_array_from_file(framesdata, "s16 " + frame_name)
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
                # Assume unk5A is zero at least for now.
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
            ax.set_title(f"Frame #{self.anim_index} of {len(framearray)}")
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
parser.add_argument(
    "animset_num", type=int, help="Animset number; 2 for ANIMSET_DRA(2)"
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

args = parser.parse_args()

texture_data = dt.load_raw_dump(args.dump_filename)
show_animset(args.animset_num, args.e_palette, args.view_width, args.view_height)
