#!/usr/bin/env python3
# tool to split jump tables into individual entries in splat yaml

from pathlib import Path
from itertools import groupby
import yaml
import sys

def check_file(text, table_prefix, segments, names):
    newlines = text.split("\n")

    jpt_start = None
    jpt_end = None
    is_jpt = False
    jpt_name = None

    for line in newlines:

        # is this the start of a jump table?
        if line.find(table_prefix) > 0:

            # split line and get the name
            jpt = line.split(" ")
            jpt_name = jpt[1]
            is_jpt = True
            print(f"-----{jpt_name}-----")

        # if we have entered a jump table and there is an .word entry
        if is_jpt and line.find(".word") > 0:
            blocks = line.split(" ")

            # if it's the first .word line, it's the start
            # otherwise keep updating the end every line
            if len(blocks) >= 2:
                if not jpt_start:
                    jpt_start = blocks[1]
                else:
                    jpt_end = blocks[1]

        # if there's a newline it's the end of the jump table
        elif len(line) == 0:
            is_jpt = False

            if jpt_end:
                value = int(jpt_end,16) + 4
                hex_str = "0x{:X}".format(value)

                # keep track of the jump table names to add a comment
                names[int(jpt_start, 16)] = jpt_name

                # check if the start already exists, otherwise add it
                found = False
                for s in segments:
                    if int(jpt_start, 16) == int(s[0]):
                        found = True

                if not found:
                    segments.append([int(jpt_start, 16), 'rodata'])
                    print(f"    added jpt_start {jpt_start}")

                # check if the end already exists, otherwise add it
                found = False
                for s in segments:
                    if int(jpt_end,16) == int(s[0]):
                        found = True 
                
                if not found:
                    the_end = int(jpt_end, 16) + 4
                    segments.append([the_end, 'rodata'])
                    print(f"    added jpt_end   {the_end:X}")

            jpt_start = None
            jpt_end = None

def execute(asm_files, jump_prefix, segments, names):
    for text in asm_files:
        check_file(text, jump_prefix, segments, names)

    # deduplicate and sort
    key_function = lambda x : x[0]
    segments.sort(key=key_function)
    segments = [ list(values) [0] for _,values in groupby(segments,key=key_function) ]
    segments = sorted(segments, key=lambda x: x[0])

    print("Cut below this line:")
    print("------------------------------------------------------------------")

    # print out the result
    for segment in segments:
        hex_str = "0x{:X}".format(segment[0])

        # if we have a name for the jump table, add that as a comment
        if segment[0] in names:
            name = names[segment[0]]
        else:
            name = ""

        # check if there's 2 or 3 entries in the line and print appropriately
        if len(name):
            if len(segment) == 2:
                print(f"      - [{hex_str}, {segment[1]}] # {name}")
            elif len(segment) == 3:
                print(f"      - [{hex_str}, {segment[1]}, {segment[2]}] # {name}")
        else:
            if len(segment) == 2:
                print(f"      - [{hex_str}, {segment[1]}]")
            elif len(segment) == 3:
                print(f"      - [{hex_str}, {segment[1]}, {segment[2]}]")


def get_yaml_segments(yaml_path):
    # load the yaml
    with open(yaml_path, "r") as stream:
        try:
            loaded = yaml.safe_load(stream)
            print(loaded['segments'][0]['subsegments'])
            return loaded['segments'][0]['subsegments']
        except yaml.YAMLError as exc:
            print(exc)
    return None

def get_asm_files(asm_path):
    files = []
    # look for rodata.s files
    for path in Path(asm_path).rglob('*.s'):
        print(path)
        f = open(f"{path}", "r")
        text = f.read()
        files.append(text)

    return files

def run_cli(yaml_path, asm_path, table_prefix):
    names = {}
    segments = get_yaml_segments(yaml_path)
    files = get_asm_files(asm_path)
    execute(files, table_prefix, segments, names)

# example usage

# split DRA (uses jpt_ prefix)
# python3 tools/split_jpt_yaml/split_jpt_yaml.py config/splat.us.dra.yaml asm/us/dra/data/ jpt_

# split NO3 (uses jtbl_ prefix)
# python3 tools/split_jpt_yaml/split_jpt_yaml.py config/splat.us.stno3.yaml asm/us/st/no3/data/ jtbl_

# run unit tests
# python3 tools/split_jpt_yaml/test.py

if __name__ == '__main__':
    run_cli(sys.argv[1], sys.argv[2], sys.argv[3])
