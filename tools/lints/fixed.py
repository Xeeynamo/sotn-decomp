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
    return "{}FIX({:g});".format(group, x)

# generate combinations of the 3 common entity names,
# both velocities, and =, +=, and -=
def gen_patterns(patterns):
    regs = [
        r"(OBJECT->NAME\s*\=\s*)(-?0x[0-9a-fA-F]+);",
        r"(OBJECT->NAME\s*\+=\s*)(-?0x[0-9a-fA-F]+);",
        r"(OBJECT->NAME\s*-=\s*)(-?0x[0-9a-fA-F]+);"
    ]

    objs = [
        "entity",
        "g_CurrentEntity",
        "self"
    ]

    names = [
        "velocityX",
        "velocityY"
    ]
    for obj in objs:
        for name in names:
            for reg in regs:
                temp = reg.replace("OBJECT", obj)
                temp = temp.replace("NAME", name)
                patterns.append(temp)

    for pattern in patterns:
        print(pattern)

def compile_patterns(patterns, compiled):
    for pattern in patterns:
        compiled.append(re.compile(pattern))

def count_digits_after_decimal(number):
    decimal_part = str(number).split('.')[-1]
    return len(decimal_part)

def count_digits_before_decimal(number):
    decimal_part = str(number).split('.')[0]
    return len(decimal_part)
 
def transform(line, regexes):
    for pattern in regexes:

        thing = re.search(pattern, line)

        if thing:
            conv = int(thing.group(2), 16) / 65536.0

            # an improvement here would be checking if it has an exact
            # fixed point representation rather than counting digits
            if count_digits_after_decimal(conv) > 5:
                print("skipping")
                return line
            elif count_digits_before_decimal(conv) > 3:
                print("skipping")
                return line
            else:
                line = re.sub(
                    pattern,
                    lambda match: FIXED(int(match.group(2), 16) / 65536.0, match.group(1)),
                    line,
                )
    return line

def transform_file(file_path, regexes, result):
    lines = []
    original_lines = []
    with open(file_path, "r") as file:
        lines = file.readlines()

    original_lines = copy.deepcopy(lines)
    for i, line in enumerate(lines):
        if "LINT_IGNORE" in line:
            continue
        lines[i] = transform(lines[i], regexes)

        if lines[i] != original_lines[i]:
            result['alterations'] = result['alterations'] + 1
            print(f"{i}: {original_lines[i]} -> {lines[i]}")
    with open(file_path, "w") as file:
        for line in lines:
            file.write(line)

# Function to recursively process C files in a directory
def process_directory(dir_path, regexes, result):
    for item in os.listdir(dir_path):
        item_path = os.path.join(dir_path, item)
        if os.path.isfile(item_path) and item_path.endswith(".c"):
            print("checking", item_path)
            transform_file(item_path, regexes, result)
        elif os.path.isdir(item_path):
            process_directory(item_path, regexes, result)

def test(regexes):
    print(count_digits_after_decimal(1.2345))
    print(transform('entity->velocityX -= 0x1800;', regexes))
    print(transform('g_CurrentEntity->velocityY = -0x28000;', regexes))
    print(transform('self->velocityX -= 0x200;', regexes))

if __name__ == "__main__":
    patterns = []
    gen_patterns(patterns)
    regexes = []
    compile_patterns(patterns, regexes)

    test(regexes)
    result = {'alterations': 0}
    process_directory(sys.argv[1], regexes, result)
    exit(result['alterations'] != 0)


