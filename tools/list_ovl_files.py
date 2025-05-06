"""
This script is not expected to be user friendly.
It is used during builds by Makefile.psp.mk.
"""

import yaml
import sys

with open(sys.argv[1]) as yaml_file:
    config = yaml.safe_load(yaml_file)
c_subsegments = [
    seg
    for seg in config["segments"][1]["subsegments"]
    if type(seg) == list and (seg[1] == "c" or seg[1] == ".data" or seg[1] == ".bss")
]
merged_functions = []
for seg in c_subsegments:
    func = f"{seg[2]}"
    if "/" in func:
        ovl, func = func.split("/")
        if ovl == sys.argv[2]:
            merged_functions.append(func)
    else:
        merged_functions.append(func)

print(" ".join(merged_functions))
