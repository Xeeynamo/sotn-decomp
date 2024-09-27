#Automatically de-duplicates a newly created overlay. The overlay should have its code in src/st/{OVL}/us.c

# Does not work for different versions, does not work for non-stage overlays (familiars, bosses, etc)


import argparse
import re
import os

# functions which appear at the start of our deduplicated files in existing stages.
# If you have "Random": "st_update" that means "Random" is the first function in the st_update.c file.
file_start_funcs = {"Random"                 : "st_update",
                    "HitDetection"           : "collision",
                    "CreateEntityFromLayout" : "create_entity",
                    "EntityIsNearPlayer"     : "e_red_door",
                    "DestroyEntity"          : "st_common",
                    "func_8018CAB0"          : "e_collect"}

#Given a symbol name and a set of symbol lines, get the numerical value of the symbol
def get_symbol_offset(symname, symbols):
    for sym in symbols:
        name, addr = sym.split(" = ")
        if name == symname:
            return int(addr[2:-2], 16) # trim 0x and ;\n
def get_file_splits(overlay_name):
    print(overlay_name)

    with open(f"src/st/{overlay_name}/us.c") as f:
        clines = f.readlines()
    with open(f"config/splat.us.st{overlay_name}.yaml") as f:
        splatlines = f.readlines()
    with open(f"config/symbols.us.st{overlay_name}.txt") as f:
        symbollines = f.readlines()
    file_splits = []
    for line in clines:
        match = re.search(r'INCLUDE_ASM\("[^"]+",\s*(\w+)\);', line)
        if match:
            function_name = match.group(1)
            if function_name in file_start_funcs:
                split_location = get_symbol_offset(function_name, symbollines)
                # change from ram offset to rom offset
                split_location -= 0x80180000
                filename = file_start_funcs[function_name]
                file_splits.append([f"0x{split_location:X}", filename, function_name])
    return file_splits

def write_file_splits_to_yaml(overlay_name, new_segments, do_overwrite):
    yaml_filename = f"config/splat.us.st{overlay_name}.yaml"
    # initially open for reading. Then we'll mess with it, and open for writing.
    with open(yaml_filename,'r') as f:
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
    out_filename = yaml_filename if do_overwrite else "config/test_splat.yaml"
    with open(out_filename,'w') as f:
        f.write("\n".join(outlines))
def split_c_files(overlay_name, new_segments, do_overwrite):
    seg_dict = {s[2]:s[1] for s in new_segments}
    c_file_in = f"src/st/{overlay_name}/us.c"

    with open(c_file_in,'r') as f:
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
                with open(overlay_dir + output_filename + ".c", 'w') as f:
                    f.write("\n".join(output_buffer))
                # Create our new file
                output_buffer = [file_header]
                output_filename = dest_file
        output_buffer.append(line.replace("nonmatchings/us",f"nonmatchings/{output_filename}"))
    # Flush the last one
    with open(overlay_dir + output_filename + ".c", 'w') as f:
        f.write("\n".join(output_buffer))
    if do_overwrite:
        os.remove(c_file_in)

def get_symbol_addr(symbol_name, overlay_name):
    with open("build/us/st" + overlay_name + ".map") as f:
        symlines = f.read().splitlines()
    for line in symlines:
        if symbol_name in line:
            lineparts = line.split()
            address = int(lineparts[0],16)
            # change from ram offset to rom offset
            address -= 0x80180000
            return f"0x{address:X}"

def split_rodata(overlay_name, new_segments, do_overwrite):
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
                yaml_rodata_lines.append(f"      - [{addr}, .rodata, {seg[1]}]")

            # We have now extracted the rodata from any INCLUDE_RODATA lines. Now also do any jump tables in any functions.
        for line in c_lines:
            match = re.search(r'INCLUDE_ASM\("[^"]+",\s*(\w+)\);', line)
            if match:
                funcname = match.group(1)
                with open(f"asm/us/st/{overlay_name}/nonmatchings/{seg[1]}/{funcname}.s") as asmfile:
                    asmlines = asmfile.read().splitlines()
                    for line in asmlines:
                        if "jtbl" in line:
                            print(line)

    # Now we have the yaml rodata lines. open the yaml file and write the lines into it.
    yaml_filename = f"config/splat.us.st{overlay_name}.yaml"
    # initially open for reading. Then we'll mess with it, and open for writing.
    with open(yaml_filename,'r') as f:
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
    with open(yaml_filename,'w') as f:
        f.write("\n".join(outlines))
parser = argparse.ArgumentParser(description="Perform initial splitting out of files for new overlays")

parser.add_argument(
    "ovl",
    help="Name of overlay (for example, no0)",
)
parser.add_argument(
    "--cowabunga",
    action="store_true",
    help="Actually overwrite/delete files",
)

if __name__ == "__main__":
    args = parser.parse_args()
    splits = get_file_splits(args.ovl)
    write_file_splits_to_yaml(args.ovl, splits, args.cowabunga)
    split_c_files(args.ovl, splits, args.cowabunga)
    split_rodata(args.ovl, splits, args.cowabunga)