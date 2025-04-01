#!/usr/bin/env python3

# tool to list functions by difficulty and decomp.me WIP links
from pathlib import Path
from tabulate import tabulate
import os
import concurrent.futures
import argparse

from helpers import find_scratches


# look in asm files, read in the text and check for branches and jump tables
def get_asm_files(asm_path, overlay):
    files = []
    for path in Path(asm_path).rglob("*.s"):
        # skip if not the right overlay
        if overlay is not None and len(overlay) and not overlay in str(path):
            continue
        # ignore data
        if not "f_nonmat" in str(path):
            continue
        # ignore 0.BIN library functions
        if "zero" in str(path):
            filename = os.path.basename(path)
            addr = int(filename.split(".")[0][1:], 16)
            if addr >= 0x0601B2B4:  # GFS_Init
                continue

        f = open(f"{path}", "r")
        text = f.read()

        function_name = text.split("\n")[0].split(" ")[1]

        branches = 0
        branch_types = [
            "*/ bf ",
            "*/ bf.s ",
            "*/ bt ",
            "*/ bt.s ",
            "*/ bra ",
            "*/ braf ",
            "*/ bsr ",
            "*/ bsrf ",
            "*/ jmp ",
            "*/ jsr ",
        ]
        for branch in branch_types:
            branches = branches + text.count(branch)

        jump_table = "   "
        if "jpt_" in text or "jtbl_" in text:
            jump_table = "Yes"

        f = {
            "filename": path,
            "length": len(text.split("\n")),
            "function_name": function_name,
            "text": text,
            "branches": branches,
            "jump_table": jump_table,
        }

        files.append(f)

    return files


def find_wip(function):
    # look for a WIP on decomp.me
    result = find_scratches(function["function_name"], "saturn")

    if result:
        return {"link": result[0], "percent": result[1]}

    return None


if __name__ == "__main__":
    # Create the argument parser
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--no-fetch", action="store_true", help="Disable fetching from decomp.me"
    )
    parser.add_argument("--overlay", type=str, help="Specify a overlay name")

    # Parse the command-line arguments
    args = parser.parse_args()

    asm_files = get_asm_files("asm/saturn", args.overlay)

    # sort by name, then number of branches, then length
    asm_files = sorted(asm_files, key=lambda x: (x["filename"]))
    asm_files = sorted(asm_files, key=lambda x: (x["branches"]))
    asm_files = sorted(asm_files, key=lambda x: len(x["text"].split("\n")))

    output = asm_files

    results = []

    if not args.no_fetch:
        # we are mostly waiting on IO so run in parallel
        with concurrent.futures.ThreadPoolExecutor() as executor:
            futures = [executor.submit(find_wip, o) for o in output]
            results = [f.result() for f in futures]

    to_print = []
    for i, o in enumerate(output):
        row = [
            str(o["filename"]).replace("asm/saturn/", ""),
            o["function_name"],
            o["length"],
            o["branches"],
            "",
            "",
        ]

        if len(results) and results[i]:
            row[4] = results[i]["link"]
            row[5] = results[i]["percent"]

        to_print.append(row)

    headers = ["Filename", "Function Name", "Length", "Branches", "WIP", "%"]
    print(tabulate(to_print, headers=headers, tablefmt="github"))
