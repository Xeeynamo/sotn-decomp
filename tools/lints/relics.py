# script to fix relic documentation
# python3 ./tools/lints/relics.py ./src

# example
# -    if (g_Status.relics[27] & 2) {
# +    if (g_Status.relics[RELIC_RIB_OF_VLAD] & 2) {

import re
import os, sys

relics_enum_mapping = {
    0: "RELIC_SOUL_OF_BAT",
    1: "RELIC_FIRE_OF_BAT",
    2: "RELIC_ECHO_OF_BAT",
    3: "RELIC_FORCE_OF_ECHO",
    4: "RELIC_SOUL_OF_WOLF",
    5: "RELIC_POWER_OF_WOLF",
    6: "RELIC_SKILL_OF_WOLF",
    7: "RELIC_FORM_OF_MIST",
    8: "RELIC_POWER_OF_MIST",
    9: "RELIC_GAS_CLOUD",
    10: "RELIC_CUBE_OF_ZOE",
    11: "RELIC_SPIRIT_ORB",
    12: "RELIC_GRAVITY_BOOTS",
    13: "RELIC_LEAP_STONE",
    14: "RELIC_HOLY_SYMBOL",
    15: "RELIC_FAERIE_SCROLL",
    16: "RELIC_JEWEL_OF_OPEN",
    17: "RELIC_MERMAN_STATUE",
    18: "RELIC_BAT_CARD",
    19: "RELIC_GHOST_CARD",
    20: "RELIC_FAERIE_CARD",
    21: "RELIC_DEMON_CARD",
    22: "RELIC_SWORD_CARD",
    23: "RELIC_JP_0",
    24: "RELIC_JP_1",
    25: "RELIC_HEART_OF_VLAD",
    26: "RELIC_TOOTH_OF_VLAD",
    27: "RELIC_RIB_OF_VLAD",
    28: "RELIC_RING_OF_VLAD",
    29: "RELIC_EYE_OF_VLAD",
}

def replace_enum(match):
    relic_index = int(match.group(1))
    if relic_index in relics_enum_mapping:
        return f"g_Status.relics[{relics_enum_mapping[relic_index]}]"
    else:
        return match.group(0)

def replace_relics_enum(input_code):
    pattern = r"g_Status\.relics\[(\d+)\]"
    output_code = re.sub(pattern, replace_enum, input_code)
    return output_code

def process_directory(dir_path):
    for item in os.listdir(dir_path):
        item_path = os.path.join(dir_path, item)
        if os.path.isfile(item_path) and item_path.endswith(".c"):
            print("checking", item_path)

            output_code = []
            with open(item_path, "r") as file:
                lines = file.readlines()

            for i, line in enumerate(lines):
                lines[i] = replace_relics_enum(line)

            with open(item_path, "w") as file:
                for line in lines:
                    file.write(line)
            

        elif os.path.isdir(item_path):
            process_directory(item_path)

if __name__ == "__main__":
    process_directory(sys.argv[1])
