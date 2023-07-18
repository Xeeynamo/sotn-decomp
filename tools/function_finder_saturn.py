#!/usr/bin/python3

# tool to list functions by difficulty and decomp.me WIP links
from pathlib import Path
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
        if not 'name' in result:
            continue
        # seems to give approximate matches, skip these
        if result['name'] != name:
            continue
        if result['platform'] != 'saturn':
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
        if not 'f_nonmat' in str(path):
            continue
        # ignore 0.BIN library functions
        if 'zero' in str(path):
            filename = os.path.basename(path)
            addr = int(filename.split('.')[0][1:], 16)
            if addr >= 0x0601B2B4: # GFS_Init
                continue

        f = open(f"{path}", "r")
        text = f.read()

        function_name = text.split('\n')[0].split(' ')[1]

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

        jump_table = '   '
        if "jpt_" in text or "jtbl_" in text:
            jump_table = 'Yes'

        f = {'filename': path,
             'length': len(text.split("\n")),
             'function_name': function_name, 
             'text': text, 
             'branches': branches, 
             'jump_table': jump_table}

        files.append(f)

    return files

def find_wip(function):
    # look for a WIP on decomp.me
    result = find_scratches(function['function_name'])

    if result:
        return {'link': result[0], 'percent': result[1]}

    return None

def print_github_flavored_table(data):
    headers = list(data[0].keys())  # Get the headers from the first row's keys

    # Print the table header
    table = "| " + " | ".join(headers) + " |"
    separator = "|-" + "-|".join(["-" * len(header) for header in headers]) + "-|"

    print(table)
    print(separator)

    # Print the table rows
    for row in data:
        row_values = [str(value) for value in row.values()]
        table_row = "| " + " | ".join(row_values) + " |"
        print(table_row)

if __name__ == '__main__':
    asm_files = get_asm_files('asm/saturn')

    # sort by name, then number of branches, then length
    asm_files = sorted(asm_files, key=lambda x: (x['filename']))
    asm_files = sorted(asm_files, key=lambda x: (x['branches']))
    asm_files = sorted(asm_files, key=lambda x: len(x['text'].split("\n")))

    output = asm_files

    # we are mostly waiting on IO so run in parallel
    with concurrent.futures.ThreadPoolExecutor() as executor:
        futures = [executor.submit(find_wip, o) for o in output]
        results = [f.result() for f in futures]

    to_print = []

    for i, o in enumerate(output):
        obj = {'Filename': str(o['filename']).replace("asm/saturn/", ""),
                'Function Name': o['function_name'],
                'Length': o['length'],
                'Branches': o['branches']}
        
        if results[i]:
            obj['WIP'] = results[i]['link']
            obj['%'] = results[i]['percent']
        else:
            obj['WIP'] = ""
            obj['%'] = ""

        to_print.append(obj)

    print_github_flavored_table(to_print)

