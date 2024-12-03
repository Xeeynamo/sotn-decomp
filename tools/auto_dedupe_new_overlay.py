# Automatically de-duplicates a newly created overlay. The overlay should have its code in src/st/{OVL}/us.c

# Does not work for different versions, does not work for non-stage overlays (familiars, bosses, etc)


import argparse
import re
import os

# functions which appear at the start of our deduplicated files in existing stages.
# If you have "Random": ["st_update"] that means "Random" is the first function in the st_update.c file.
# Optionally, you can include a final function, like this:
# "StageNamePopupHelper"   : ["e_stage_name", "EntityStageNamePopup"],
# Maybe the dictionary should be changed so the file name is the key, but eh.
file_start_funcs = {
    "EntityIsNearPlayer": ["e_red_door"],
    "Random": ["st_update"],
    "HitDetection": ["collision"],
    "CreateEntityFromLayout": ["create_entity"],
    "DestroyEntity": ["st_common"],
    "BlitChar": ["blit_char"],
    "EntityRelicOrb": ["e_misc", "PlaySfxPositional"],
    "StageNamePopupHelper": ["e_stage_name", "EntityStageNamePopup"],
    "EntitySoulStealOrb": ["e_particles"],
    "func_8018CAB0": ["e_collect"],
    "EntityRoomForeground": ["e_room_fg"],
    "BottomCornerText": ["popup", "BottomCornerText"],
    "UnkPrimHelper": ["prim_helpers"],
}


def get_file_splits(overlay_name):
    with open(f"src/st/{overlay_name}/us.c") as f:
        clines = f.readlines()
    with open(f"config/splat.us.st{overlay_name}.yaml") as f:
        splatlines = f.readlines()
    with open(f"config/symbols.us.st{overlay_name}.txt") as f:
        symbollines = f.readlines()
    file_splits = []
    file_last_func = ""
    force_next_func_split = False
    for line in clines:
        match = re.search(r'INCLUDE_ASM\("[^"]+",\s*(\w+)\);', line)
        if match:
            function_name = match.group(1)
            if function_name in file_start_funcs:
                filename = file_start_funcs[function_name][0]
                if len(file_start_funcs[function_name]) == 2:
                    # detect single-function files
                    if file_start_funcs[function_name][1] == function_name:
                        force_next_func_split = True
                    file_last_func = file_start_funcs[function_name][1]
                else:
                    file_last_func = ""
                split_location = get_symbol_addr(function_name, overlay_name)
                file_splits.append([f"0x{split_location}", filename, function_name])
            elif function_name == file_last_func:
                force_next_func_split = True
            elif force_next_func_split:
                split_location = get_symbol_addr(function_name, overlay_name)
                file_splits.append(
                    [f"0x{split_location}", f"unk_{split_location}", function_name]
                )
                force_next_func_split = False
    return file_splits


def write_file_splits_to_yaml(overlay_name, new_segments):
    yaml_filename = f"config/splat.us.st{overlay_name}.yaml"
    # initially open for reading. Then we'll mess with it, and open for writing.
    with open(yaml_filename, "r") as f:
        raw_yaml_lines = f.read().splitlines()
    outlines = []
    for line in raw_yaml_lines:
        if ", c," not in line:
            outlines.append(line)
        else:
            # now we output the lines which list the C segments
            # Start with the first block of C, before our first identified segment.
            first_line = line.replace("us", "first_c_file")
            outlines.append(first_line)
            for seg in new_segments:
                addr, filename, _ = seg
                outlines.append(f"      - [{addr}, c, {filename}]")
    with open(yaml_filename, "w") as f:
        f.write("\n".join(outlines))


def split_c_files(overlay_name, new_segments):
    seg_dict = {s[2]: s[1] for s in new_segments}
    c_file_in = f"src/st/{overlay_name}/us.c"

    with open(c_file_in, "r") as f:
        c_file_lines = f.read().splitlines()

    # output buffer holds the lines that will write to the current file.
    # Once we reach a new C file, we dump the buffer and start a new one.
    file_header = '// SPDX-License-Identifier: AGPL-3.0-or-later\n#include "common.h"\n'
    output_buffer = []
    overlay_dir = f"src/st/{overlay_name}/"
    output_filename = "first_c_file"
    for line in c_file_lines:
        match = re.search(r'INCLUDE_ASM\("[^"]+",\s*(\w+)\);', line)
        if match:
            function_name = match.group(1)
            if function_name in seg_dict:
                dest_file = seg_dict[function_name]
                print(f"got a split on {function_name} to {dest_file}")
                # Now that we have a new destination file, dump the buffer.
                with open(overlay_dir + output_filename + ".c", "w") as f:
                    f.write("\n".join(output_buffer))
                # Create our new file
                output_buffer = [file_header]
                output_filename = dest_file
        output_buffer.append(
            line.replace("nonmatchings/us", f"nonmatchings/{output_filename}")
        )
    # Flush the last one
    with open(overlay_dir + output_filename + ".c", "w") as f:
        f.write("\n".join(output_buffer))
    os.remove(c_file_in)


# Looks in the .map file to find the location of a symbol.
# Returns address as a string, representing hex location in the ROM (not RAM!)
# Might return "4ADC8" for example.
def get_symbol_addr(symbol_name, overlay_name):
    with open("build/us/st" + overlay_name + ".map") as f:
        symlines = f.read().splitlines()
    for line in symlines:
        lineparts = line.split()
        if len(lineparts) != 2:
            continue
        if symbol_name == lineparts[1]:
            address = int(lineparts[0], 16)
            # change from ram offset to rom offset
            address -= 0x80180000
            return f"{address:X}"


def split_rodata(overlay_name, new_segments):
    # Get the rodata and create splat segments
    # Do this by searching for INCLUDE_RODATA in the c files, and make the rodata parse to that file
    overlay_dir = f"src/st/{overlay_name}/"
    yaml_rodata_lines = []
    for seg in new_segments:
        c_file = overlay_dir + seg[1] + ".c"
        with open(c_file) as f:
            c_lines = f.read().splitlines()
        for line in c_lines:
            match = re.search(r'INCLUDE_RODATA\("[^"]+",\s*(\w+)\);', line)
            if match:
                # Found a line. Need to add rodata line to yaml.
                # To do that, we need the rodata address.
                rodata_name = match.group(1)
                addr = get_symbol_addr(rodata_name, overlay_name)
                yaml_rodata_lines.append(f"      - [0x{addr}, .rodata, {seg[1]}]")

            # We have now extracted the rodata from any INCLUDE_RODATA lines. Now also do any jump tables in any functions.
        for line in c_lines:
            match = re.search(r'INCLUDE_ASM\("[^"]+",\s*(\w+)\);', line)
            if match:
                funcname = match.group(1)
                with open(
                    f"asm/us/st/{overlay_name}/nonmatchings/us/{funcname}.s"
                ) as asmfile:
                    asmlines = asmfile.read().splitlines()
                    for i, line in enumerate(asmlines):
                        if "glabel jtbl" in line:
                            nextline = asmlines[i + 1]
                            jtbl_addr = "0x" + nextline.split()[1]
                            yaml_rodata_lines.append(
                                f"      - [{jtbl_addr}, .rodata, {seg[1]}]"
                            )

    # yaml rodata comes from multiple places. Sort the lines to make splat in right order.
    yaml_rodata_lines.sort()
    # We need to have only one rodata segment per file. This was found in testing.
    deduped_yaml_rodata = []
    curr_rodata_seg = ""
    for line in yaml_rodata_lines:
        seg = line.split(",")[-1]
        if seg != curr_rodata_seg:
            deduped_yaml_rodata.append(line)
            curr_rodata_seg = seg
    yaml_rodata_lines = deduped_yaml_rodata

    # Now we have the yaml rodata lines. open the yaml file and write the lines into it.
    yaml_filename = f"config/splat.us.st{overlay_name}.yaml"
    # initially open for reading. Then we'll mess with it, and open for writing.
    with open(yaml_filename, "r") as f:
        raw_yaml_lines = f.read().splitlines()
    outlines = []
    for line in raw_yaml_lines:
        if ".rodata," not in line:
            outlines.append(line)
        else:
            first_line = line.replace("us", "first_c_file")
            outlines.append(first_line)
            for roline in yaml_rodata_lines:
                outlines.append(roline)
    with open(yaml_filename, "w") as f:
        f.write("\n".join(outlines))


parser = argparse.ArgumentParser(
    description="Perform initial splitting out of files for new overlays"
)

parser.add_argument(
    "ovl",
    help="Name of overlay (for example, no0)",
)

if __name__ == "__main__":
    args = parser.parse_args()
    splits = get_file_splits(args.ovl)
    write_file_splits_to_yaml(args.ovl, splits)
    split_c_files(args.ovl, splits)
    split_rodata(args.ovl, splits)
