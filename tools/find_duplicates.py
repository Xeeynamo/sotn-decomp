#!/usr/bin/python3
# tool to detect if a function has duplicates, adapted from https://github.com/pmret/papermario

import argparse
from collections import Counter, OrderedDict
from datetime import datetime

from Levenshtein import ratio
import os
import re
import sys

script_dir = os.path.dirname(os.path.realpath(__file__))
root_dir = script_dir + "/../"
asm_dir = root_dir + "asm"
build_dir = root_dir + "build/"


def read_roms():
    roms = dict()
    roms["MAIN"] = open(root_directory + "build/main.exe", "rb").read()
    roms["DRA"] = open(root_directory + "build/DRA.BIN", "rb").read()
    roms["RIC"] = open(root_directory + "build/RIC.BIN", "rb").read()
    roms["CEN"] = open(root_directory + "build/CEN.BIN", "rb").read()
    roms["DRE"] = open(root_directory + "build/DRE.BIN", "rb").read()
    roms["MAD"] = open(root_directory + "build/MAD.BIN", "rb").read()
    roms["NO3"] = open(root_directory + "build/NO3.BIN", "rb").read()
    roms["NP3"] = open(root_directory + "build/NP3.BIN", "rb").read()
    roms["NZ0"] = open(root_directory + "build/NZ0.BIN", "rb").read()
    roms["ST0"] = open(root_directory + "build/ST0.BIN", "rb").read()
    roms["WRP"] = open(root_directory + "build//WRP.BIN", "rb").read()
    roms["RWRP"] = open(root_directory + "build/RWRP.BIN", "rb").read()
    return roms


def find_dir(query):
    for root, dirs, files in os.walk(asm_dir):
        for d in dirs:
            if d == query:
                return os.path.join(root, d)
    return None


# build a list of all non matching functions .s files names
def get_all_s_files():
    ret = set()
    for root, dirs, files in os.walk(asm_dir):
        for f in files:
            if "data." in f or "nonmatchings" not in os.path.join(root, f):
                continue
            elif f.endswith(".s") and not f.endswith("data.s"):    
                ret.add(f[:-2])
    return ret


def get_symbol_length(sym_name):
    offset = map_offsets[sym_name]
    if "end" in offset and "start" in offset:
        return map_offsets[sym_name]["end"] - map_offsets[sym_name]["start"]
    return 0


# read instructions ? returns tuple of 1 out of 4 utf8 decoded bytes, raw bits
def get_symbol_bytes(offsets, func):
    if func not in offsets or "start" not in offsets[func] or "end" not in offsets[func]:
        return None
    bin = offsets[func]["bin"]
    start = offsets[func]["start"]
    end = offsets[func]["end"]
    data_type = offsets[func]["data_type"]

    bs = list(roms_bytes[bin][start:end])

    while len(bs) > 0 and bs[-1] == 0: # removing zeros at the end
        bs.pop()

    insns = bs[0::4] # read one in 4 byte, why ?

    ret = []
    for ins in insns:
        ret.append(ins >> 2) ## why ?

    result = bytes(ret).decode('utf-8'), bs, data_type
    return result


def parse_map(map_files): # returns list of syms[fn] = (bin, rom, cur_file, prev_sym, ram, data_type)
    ram_offset = None
    cur_file = "<no file>"
    syms = {}
    prev_sym = None
    prev_line = ""
    for key in map_files:
        with open(map_files[key]) as f:
            data_type = "unknown"
            for line in f:
                if ".text" in line:
                    data_type = "text"
                elif ".bss" in line:
                    data_type = "bss"
                elif ".rodata" in line:
                    data_type = "rodata"
                elif ".data" in line:
                    data_type = "data"

                if "load address" in line:
                    if "noload" in line or "noload" in prev_line:
                        ram_offset = None
                        continue
                    ram = int(line[16 : 16 + 18], 0)
                    rom = int(line[59 : 59 + 18], 0)
                    ram_offset = ram - rom
                    continue
                prev_line = line

                if (
                    ram_offset is None
                    or "=" in line
                    or "*fill*" in line
                    or " 0x" not in line
                ):
                    continue
                ram = int(line[16 : 16 + 18], 0)
                rom = ram - ram_offset
                fn = line.split()[-1]
                if "0x" in fn:
                    ram_offset = None
                elif "/" in fn:
                    cur_file = fn
                else:
                    syms[fn] = (key, rom, cur_file, prev_sym, ram, data_type)
                    prev_sym = fn
    return syms


def get_map_offsets(syms):
    offsets = {}
    for sym in syms:
        if sym == "header": 
            a = 0
        prev_sym = syms[sym][3]
        if sym not in offsets:
            offsets[sym] = {}
        if prev_sym not in offsets:
            offsets[prev_sym] = {}
        offsets[sym]["bin"] = syms[sym][0]
        offsets[sym]["start"] = syms[sym][1]
        offsets[prev_sym]["end"] = syms[sym][1]
        offsets[sym]["data_type"] = syms[sym][5]
    return offsets


def is_zeros(vals):
    for val in vals:
        if val != 0:
            return False
    return True


def diff_syms(qb, tb):
    if len(tb[1]) < 8:
        return 0

    # The minimum edit distance for two strings of different lengths is `abs(l1 - l2)`
    # Quickly check if it's impossible to beat the threshold. If it is, then return 0
    l1, l2 = len(qb[0]), len(tb[0])
    if abs(l1 - l2) / (l1 + l2) > 1.0 - args.threshold:
        return 0
    r = ratio(qb[0], tb[0])

    if r == 1.0 and qb[1] != tb[1]:
        r = 0.99

    # if not of the same data type (text, data, rodata, bss) then we ignore
    if qb[2] != tb[2]:
        r = 0
    return r


def get_pair_score(query_bytes, b):
    b_bytes = get_symbol_bytes(map_offsets, b)

    if query_bytes and b_bytes:
        return diff_syms(query_bytes, b_bytes)
    return 0


def get_matches(query):
    query_bytes = get_symbol_bytes(map_offsets, query)
    if query_bytes is None:
        sys.exit("Symbol '" + query + "' not found")

    ret = {}
    for symbol in map_offsets:
        if symbol is not None and query != symbol:
            score = get_pair_score(query_bytes, symbol)
            if score >= args.threshold:
                ret[symbol] = score
    return OrderedDict(sorted(ret.items(), key=lambda kv: kv[1], reverse=True))


def do_query(query):
    matches = get_matches(query)
    num_matches = len(matches)

    if num_matches == 0:
        print(query + " - found no matches")
        return

    i = 0
    more_str = ":"
    if args.num_out < num_matches:
        more_str = " (showing only " + str(args.num_out) + "):"

    print(query + " - found " + str(num_matches) + " matches total" + more_str)
    for match in matches:
        if i == args.num_out:
            break
        match_str = "{:.3f} - {}".format(matches[match], match)
        if match not in s_files:
           match_str += " (decompiled)"
        print(match_str)
        i += 1
    print()

# this does the same as def all_matches but comment the actual C files instead of outputing a .txt file
def all_matches_comment(all_funcs_flag):
    match_dict = dict()
    to_match_files = list(s_files.copy())
    c_files_list = list()
    for root, dirs, files in os.walk(root_dir + "src"):
                for f in files:
                    if f.endswith(".c"):
                        c_files_list.append(os.path.join(root, f))


    # the following comment was already present in the papermario version, not sure to understand it...

    # assumption that after half the functions have been matched, nothing of significance is left
    # since duplicates that already have been discovered are removed from tp_match_files
    if all_funcs_flag:
        iter_limit = 0
    else:
        iter_limit = len(s_files) / 2

    num_decomped_dupes = 0
    num_undecomped_dupes = 0
    num_perfect_dupes = 0

    i = 0
    while len(to_match_files) > iter_limit:
        file = to_match_files[0]

        i += 1
        print("File matching progress: {:%}".format(i / (len(s_files) - iter_limit)), end='\r')

        if get_symbol_length(file) < 16:
            to_match_files.remove(file)
            continue

        matches = get_matches(file)
        num_matches = len(matches)
        if num_matches == 0:
            to_match_files.remove(file)
            continue

        num_undecomped_dupes += 1

        match_list = []
        for match in matches:
            if match in to_match_files:
                i += 1
                to_match_files.remove(match)

            match_str = "{:.2f} - {}".format(matches[match], match)
            if matches[match] >= 0.995:
                num_perfect_dupes += 1

            if match not in s_files:
                num_decomped_dupes += 1
                match_str += " (decompiled)"
            else:
                num_undecomped_dupes += 1

            match_list.append(match_str)

        match_dict.update({file: (num_matches, match_list)})
        to_match_files.remove(file)

    sorted_dict = OrderedDict(sorted(match_dict.items(), key=lambda item: item[1][0], reverse=True))

    print("Starting to scan .c files to comment the definitions", end='\n')
    for file_name, matches in sorted_dict.items():
        whole_matches = matches[1]
        whole_matches.append("ref. - " + file_name)
        for match in whole_matches:
            for c_file in c_files_list:
                dirty = False
                with open(c_file, 'r') as c_file_content:
                    copy = c_file_content.readlines()
                    counter = 0
                    for line in copy:
                        if match[7:] in line:
                            # ASM include
                            if line.startswith("INCLUDE_ASM"):
                                dirty = True
                                # detecting already present genereted comment and update it
                                if copy[counter - 2].startswith("//Found duplicates"):
                                        copy[counter - 1] = "//" + ',' + ','.join(whole_matches) + "\n"
                                # no generated comment detected
                                else :
                                    copy[counter] = "//Found duplicates (script generated comment, do not edit):\n" + "//" + ','.join(whole_matches) + "\n" + line
                            # C definition
                            elif (not line.startswith(" ") and not line.startswith("  ") and not line.startswith("/")) and not line.endswith(";\n"):
                                dirty = True
                                # detecting already present genereted comment and update it
                                if copy[counter - 2].startswith("//Found duplicates"):
                                    copy[counter - 1] = "//" + ','.join(whole_matches) + "\n"
                                # no generated comment detected
                                else :
                                    copy[counter] = "//Found duplicates (script generated comment, do not edit):\n" + "//" + ','.join(whole_matches) + "\n" + line
                            # C definition
                            
                        counter += 1

                if dirty :
                    with open(c_file, 'w') as c_file_content:
                        c_file_content.writelines(copy)

            print(match + "\n")


def all_matches(all_funcs_flag):
    match_dict = dict()
    to_match_files = list(s_files.copy())

    # the following comment was already present in the papermario version, not sure to understand it...

    # assumption that after half the functions have been matched, nothing of significance is left
    # since duplicates that already have been discovered are removed from tp_match_files
    if all_funcs_flag:
        iter_limit = 0
    else:
        iter_limit = len(s_files) / 2

    num_decomped_dupes = 0
    num_undecomped_dupes = 0
    num_perfect_dupes = 0

    i = 0
    while len(to_match_files) > iter_limit:
        file = to_match_files[0]

        i += 1
        print("File matching progress: {:%}".format(i / (len(s_files) - iter_limit)), end='\r')

        if get_symbol_length(file) < 16:
            to_match_files.remove(file)
            continue

        matches = get_matches(file)
        num_matches = len(matches)
        if num_matches == 0:
            to_match_files.remove(file)
            continue

        num_undecomped_dupes += 1

        match_list = []
        for match in matches:
            if match in to_match_files:
                i += 1
                to_match_files.remove(match)

            match_str = "{:.2f} - {}".format(matches[match], match)
            if matches[match] >= 0.995:
                num_perfect_dupes += 1

            if match not in s_files:
                num_decomped_dupes += 1
                match_str += " (decompiled)"
            else:
                num_undecomped_dupes += 1

            match_list.append(match_str)

        match_dict.update({file: (num_matches, match_list)})
        to_match_files.remove(file)

    output_match_dict(match_dict, num_decomped_dupes, num_undecomped_dupes, num_perfect_dupes, i)


def output_match_dict(match_dict, num_decomped_dupes, num_undecomped_dupes, num_perfect_dupes, num_checked_files):
    out_file = open(datetime.today().strftime('%Y-%m-%d-%H-%M-%S') + "_all_matches.txt", "w+")

    out_file.write("Number of s-files: " + str(len(s_files)) + "\n"
                   "Number of checked s-files: " + str(round(num_checked_files)) + "\n"
                   "Number of decompiled duplicates found: " + str(num_decomped_dupes) + "\n"
                   "Number of undecompiled duplicates found: " + str(num_undecomped_dupes) + "\n"
                   "Number of overall exact duplicates found: " + str(num_perfect_dupes) + "\n\n")

    sorted_dict = OrderedDict(sorted(match_dict.items(), key=lambda item: item[1][0], reverse=True))

    print("Creating output file: " + out_file.name, end='\n')
    for file_name, matches in sorted_dict.items():
        out_file.write(file_name + " - found " + str(matches[0]) + " matches total:\n")
        for match in matches[1]:
            out_file.write(match + "\n")
        out_file.write("\n")

    out_file.close()

def is_decompiled(sym):
    return sym not in s_files

def do_cross_query():
    ccount = Counter()
    clusters = []

    sym_bytes = {}
    for sym_name in map_syms:
        if not sym_name.startswith("D_") and \
           not sym_name.startswith("_binary") and \
           not sym_name.startswith("jtbl_") and \
           not re.match(r"L[0-9A-F]{8}", sym_name):
            if get_symbol_length(sym_name) > 16:
                sym_bytes[sym_name] = get_symbol_bytes(map_offsets, sym_name)

    for sym_name, query_bytes in sym_bytes.items():
        cluster_match = False
        for cluster in clusters:
            cluster_first = cluster[0]
            cluster_score = diff_syms(query_bytes, sym_bytes[cluster_first])
            if cluster_score >= args.threshold:
                cluster_match = True
                if is_decompiled(sym_name) and not is_decompiled(cluster_first):
                    ccount[sym_name] = ccount[cluster_first]
                    del ccount[cluster_first]
                    cluster_first = sym_name
                    cluster.insert(0, cluster_first)
                else:
                    cluster.append(sym_name)

                if not is_decompiled(cluster_first):
                    ccount[cluster_first] += len(sym_bytes[cluster_first][0])

                if len(cluster) % 10 == 0 and len(cluster) >= 10:
                    print(f"Cluster {cluster_first} grew to size {len(cluster)} - {sym_name}: {str(cluster_score)}")
                break
        if not cluster_match:
            clusters.append([sym_name])
    print(ccount.most_common(100))


parser = argparse.ArgumentParser(description="Tool to find duplicates for a specific function or to find all duplicates across the codebase.")
group = parser.add_mutually_exclusive_group()
group.add_argument("-a", "--all", help="find ALL duplicates and output them into a file", action='store_true', required=False)
group.add_argument("-ac", "--allcomment", help="same as --all but comment the .c files instead of outputing a txt file", action='store_true', required=False)
group.add_argument("-c", "--cross", help="do a cross query over the codebase", action='store_true', required=False)
group.add_argument("-s", "--short", help="find MOST duplicates besides some very small duplicates. Cuts the runtime in half with minimal loss", action='store_true', required=False)
parser.add_argument("query", help="function or file", nargs='?', default=None)
parser.add_argument("-t", "--threshold", help="score threshold between 0 and 1 (higher is more restrictive)", type=float, default=0.9, required=False)
parser.add_argument("-n", "--num-out", help="number of functions to display", type=int, default=100, required=False)

args = parser.parse_args()

if __name__ == "__main__":
    roms_bytes = read_roms()

    map_files = dict()
    for key in roms_bytes :
        for root, dirs, files in os.walk(build_dir):
                for f in files:
                    if key.lower() + ".map" == f or "st"+ key.lower() + ".map" == f:
                        map_files[key] = os.path.join(root, f)
    
    map_syms = parse_map(map_files)
    map_offsets = get_map_offsets(map_syms)

    s_files = get_all_s_files()

    # directory of a file or function
    query_dir = find_dir(args.query)

    if query_dir is not None:
        files = os.listdir(query_dir)
        for f_name in files:
            do_query(f_name[:-2])
    else:
        if args.cross:
            args.threshold = 0.985
            do_cross_query()
        elif args.all:
            args.threshold = 0.985
            all_matches(True)
        elif args.allcomment:
            answer = input("This will comment and saves 2 lines before duplicated functions in all .c files, \nare you sure you want to continue ? (y/n) \n")
            if answer.lower() in ["y","yes"]:
                args.threshold = 0.985
                all_matches_comment(True)
            else:
                print ("aborted \n")

            
        elif args.short:
            args.threshold = 0.985
            all_matches(False)
        else:
            if args.query is None:
                parser.print_help()
            else:
                do_query(args.query)