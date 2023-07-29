# script to document fixed point numbers:
# -            self->velocityX = 0x80000;
# +            self->velocityX = FIX(8.0000);

# usage
# python3 tools/fix_fixed.py ./src/st/nz0

import os
import re
import sys
import copy

def FIXED(x, group):
    return "{}FIX({:g})".format(group, x)

patterns = [
    re.compile(r"(self->velocityX\s*=\s*)(-?0x[0-9a-fA-F]+)"),
    re.compile(r"(self->velocityY\s*=\s*)(-?0x[0-9a-fA-F]+)")
]

def transform_file(file_path, result):
    lines = []
    original_lines = []
    with open(file_path, "r") as file:
        lines = file.readlines()

    original_lines = copy.deepcopy(lines)
    for i, line in enumerate(lines):
        if "LINT_IGNORE" in line:
            continue
        for pattern in patterns:
            lines[i] = re.sub(
                pattern,
                lambda match: FIXED(int(match.group(2), 16) / 65536.0, match.group(1)),
                line,
            )

        if lines[i] != original_lines[i]:
            result['alterations'] = result['alterations'] + 1
            print(f"{i}: {original_lines[i]} -> {lines[i]}")

    with open(file_path, "w") as file:
        for line in lines:
            file.write(line)

# Function to recursively process C files in a directory
def process_directory(dir_path, result):
    for item in os.listdir(dir_path):
        item_path = os.path.join(dir_path, item)
        if os.path.isfile(item_path) and item_path.endswith(".c"):
            print("checking", item_path)
            transform_file(item_path, result)
        elif os.path.isdir(item_path):
            process_directory(item_path, result)

if __name__ == "__main__":
    result = {'alterations': 0}
    process_directory(sys.argv[1], result)
    exit(result['alterations'] != 0)
