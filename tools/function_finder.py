#!/usr/bin/python3

# tool to list functions by difficulty and decomp.me WIP links
from pathlib import Path
from tabulate import tabulate
import os
import requests
import json
import time
import concurrent.futures

# search for scratches with the name on decomp.me
def find_scratches(name):
    try:
        response = requests.get(f"https://decomp.me/api/scratch?search={name}")
        response.raise_for_status()
        scratches = json.loads(response.text)
    except requests.exceptions.HTTPError as http_err:
        return None
    except Exception as err:
        return None

    best_result = None
    best_percent = 0

    for result in scratches['results']:
        # seems to give approximate matches, skip these
        if result['name'] != name:
            continue
        if result['platform'] != 'ps1':
            continue

        score = result['score']
        max_score = result['max_score']
        percent = (max_score - score) / max_score

        if percent > best_percent:
            best_percent = percent
            best_result = result

    if best_result:
        return [f"https://decomp.me{best_result['url']}", round(best_percent,3)]

    return None

# look in asm files, read in the text and check for branches and jump tables
def get_asm_files(asm_path):
    files = []
    for path in Path(asm_path).rglob('*.s'):
        # ignore data
        if not 'nonmatchings' in str(path):
            continue
        # ignore main since it's just PSY-Q functions
        if 'asm/us/main' in str(path):
            continue
        f = open(f"{path}", "r")
        text = f.read()

        # check for different mips branch types and count
        branches = 0
        branch_types = [
        "b      ",
        "bczt   ",
        "bczf   ",
        "beq    ",
        "beqz   ",
        "bge    ",
        "bgeu   ",
        "bgez   ",
        "bgezal ",
        "bgt    ",
        "bgtu   ",
        "bgtz   ",
        "ble    ",
        "bleu   ",
        "blez   ",
        "bgezal ",
        "bltzal ",
        "blt    ",
        "bltu   ",
        "bltz   ",
        "bne    ",
        "bnez   ",
        "j      ",
        "jal    ",
        "jalr   ",
        "jr     "
        ]
        for branch in branch_types:
            branches = branches + text.count(branch)

        jump_table = '   '
        if "jpt_" in text or "jtbl_" in text:
            jump_table = 'Yes'

        f = {'name': path, 'text': text, 'branches': branches, 'jump_table': jump_table}

        files.append(f)

    return files

# look in C files for DECOMP_ME_WIP comments and extract function name
# and URL
def get_c_files(c_path):
    files = []
    for path in Path(c_path).rglob('*.c'):
        f = open(f"{path}", "r")
        text = f.readlines()

        for line in text:
            # format is DECOMP_ME_WIP function_name URL
            if "DECOMP_ME_WIP" in line:
                split = line.split(" ")
                func_name = split[2]
                address = split[3]
                files.append([path, func_name.strip(), address.strip()])
    return files

def find_wip(o):
    if o[4] == "":
        name = o[0]
        # look for a WIP on decomp.me
        function_name = os.path.basename(name).split('.')[0]
        result = find_scratches(function_name)

        if result:
            return f"{result[0]} (Scraped {result[1]})"

    return ""

if __name__ == '__main__':
    asm_files = get_asm_files('asm/us')
    c_files = get_c_files('src')

    # sort by name, then number of branches, then length
    asm_files = sorted(asm_files, key=lambda x: (x['name']))
    asm_files = sorted(asm_files, key=lambda x: (x['branches']))
    asm_files = sorted(asm_files, key=lambda x: len(x['text'].split("\n")))

    output = []

    for f in asm_files:
        name = f['name']
        length = len(f['text'].split("\n"))
        branches = f['branches']
        jump_table = f['jump_table']

        # find WIPs
        wip = ""

        # correlate asm folder to C file name
        for c_file in c_files:
            # get asm folder name from C filename
            asm_folder_name = os.path.basename(c_file[0]).split('.')[0]

            # check if the folder name is part of the asm path and the function name
            # is also part of the path
            if asm_folder_name in str(name) and c_file[1] in str(name):
                # found a decomp.me WIP, get the URL
                wip = c_file[2]

        output.append([str(name).replace("asm/", ""), length, branches, jump_table, wip])

    # we are mostly waiting on IO so run in parallel
    with concurrent.futures.ThreadPoolExecutor() as executor:
        futures = [executor.submit(find_wip, o) for o in output]
        results = [f.result() for f in futures]

    # Update output with the results
    for i, o in enumerate(output):
        # keep the in-source results as definitive
        if o[4] == "":
            o[4] = results[i]

    headers = ['Filename', 'Length', 'Branches', 'Jtbl', 'Decomp.me WIP']
    print(tabulate(output, headers=headers))
