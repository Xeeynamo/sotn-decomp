#!/usr/bin/python3
# tool to detect if a function has duplicates, inspired by https://github.com/pmret/papermario and adapted for sotn decomp

import argparse
from collections import Counter, OrderedDict
from datetime import datetime

from Levenshtein import ratio
import os
import re
import sys
import glob

script_dir = os.path.dirname(os.path.realpath(__file__))
root_dir = script_dir + "/../"
asm_dir = root_dir + "asm"
build_dir = root_dir + "build/"


def read_roms():
    bins = dict()
    bins["MAIN"] = open(root_dir + "iso/SLUS_000.67", "rb").read()
    bins["DRA"] = open(root_dir + "iso/DRA.BIN", "rb").read()
    bins["RIC"] = open(root_dir + "iso/BIN/RIC.BIN", "rb").read()
    bins["CEN"] = open(root_dir + "iso/ST/CEN/CEN.BIN", "rb").read()
    bins["DRE"] = open(root_dir + "iso/ST/DRE/DRE.BIN", "rb").read()
    bins["MAD"] = open(root_dir + "iso/ST/MAD/MAD.BIN", "rb").read()
    bins["NO3"] = open(root_dir + "iso/ST/NO3/NO3.BIN", "rb").read()
    bins["NP3"] = open(root_dir + "iso/ST/NP3/NP3.BIN", "rb").read()
    bins["NZ0"] = open(root_dir + "iso/ST/NZ0/NZ0.BIN", "rb").read()
    bins["ST0"] = open(root_dir + "iso/ST/ST0/ST0.BIN", "rb").read()
    bins["WRP"] = open(root_dir + "iso/ST/WRP/WRP.BIN", "rb").read()
    bins["RWRP"] = open(root_dir + "iso/ST/RWRP/RWRP.BIN", "rb").read()
    return bins


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
                overlay = root.split("/")[-3].upper()
                if overlay in roms_bytes.keys(): 
                    ret.add((overlay,f[:-2]))
    return ret


def get_symbol_length(sym_name):
    offset = map_offsets[sym_name]
    if "end" in offset and "start" in offset:
        return map_offsets[sym_name]["end"] - map_offsets[sym_name]["start"]
    return 0


# read instructions, returns tuple of 1 out of 4 utf8 decoded bytes, raw bits
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

    insns = bs[3::4] # read one in 4 byte to only consider the mips opcode and immediates and regalloc https://student.cs.uwaterloo.ca/~isg/res/mips/opcodes

    ret = []
    for ins in insns:
        ret.append(ins >> 2) #we alread read only 1 byte in 4 but in this byte, we need the 6 first bits only, discarding the 2 we dont want with this >> 2

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
                    syms[key,fn] = (key, rom, cur_file, prev_sym, ram, data_type)
                    prev_sym = (key,fn)
    return syms


def get_map_offsets(syms):
    offsets = {}
    for sym in syms:
        if sym[1] == "header": 
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

    print(query[0] + query[1]  + " - found " + str(num_matches) + " matches total" + more_str)
    for match in matches:
        if i == args.num_out:
            break
        match_str = "{:.3f} - {}".format(matches[match], match)
        if match not in s_files:
           match_str += " - (decompiled)"
        print(match_str)
        i += 1
    print()

def all_matches_comment():
    c_files_list = list()
    for root, dirs, files in os.walk(root_dir + "src"):
                for f in files:
                    if f.endswith(".c"):
                        c_files_list.append(os.path.join(root, f))

    print("Starting to scan .c files to comment the definitions", end='\n')
    for dupesFuncGroups in parseTxt():
        comment0 = "//(script generated comment, do not edit)Found duplicates:"
        comment1 = ""
        for dupesFuncGroup in dupesFuncGroups:
            score = dupesFuncGroup[0].strip('\n').strip(' ')
            rom = dupesFuncGroup[1].strip('\n').strip(' ')
            function = dupesFuncGroup[2].strip('\n').strip(' ')

            if len(dupesFuncGroup) > 3:
                isDecompiled = dupesFuncGroup[3].strip('\n').strip(' ')
            else: isDecompiled = ""
            comment1 += ", " + score + " - " + rom + " - " + function + " - " + isDecompiled
        comment1 += '\n'

        for dupesFuncGroup in dupesFuncGroups:
            score = dupesFuncGroup[0].strip('\n').strip(' ')
            rom = dupesFuncGroup[1].strip('\n').strip(' ')
            function = dupesFuncGroup[2].strip('\n').strip(' ')

            for c_file in c_files_list:
                dirty = False
                with open(c_file, 'r') as c_file_content:
                    copy = c_file_content.readlines()
                    counter = 0
                    for line in copy:
                        if function in line and c_file.split('/')[-2].upper() == rom:
                            # detecting ASM include
                            if line.startswith("INCLUDE_ASM"):
                                dirty = True
                                # detecting already present genereted comment and update it
                                if copy[counter - 1].startswith("//(script generated comment"):
                                        copy[counter - 1] = comment0 + comment1
                                # no generated comment detected
                                else :
                                    copy[counter] = comment0 + comment1 + line
                            # detecting C definition
                            elif (not line.startswith(" ") and not line.startswith("  ") and not line.startswith("/")) and not line.endswith(";\n"):
                                dirty = True
                                # detecting already present genereted comment and update it
                                if copy[counter - 1].startswith("//(script generated comment"):
                                    copy[counter - 1] = comment0 + comment1
                                # no generated comment detected
                                else :
                                    copy[counter] = comment0 + comment1 + line
                            
                        counter += 1
                        if dirty: break # we only want to comment what comes first the ASM include or the C definition, not both

                if dirty :
                    with open(c_file, 'w') as c_file_content:
                        c_file_content.writelines(copy)

                print(function + "\n")

def all_matches_uncomment():
    c_files_list = list()
    for root, dirs, files in os.walk(root_dir + "src"):
                for f in files:
                    if f.endswith(".c"):
                        c_files_list.append(os.path.join(root, f))

    print("Starting to scan .c files to uncomment the definitions", end='\n')
    for c_file in c_files_list:
        dirty = False
        with open(c_file, 'r') as c_file_content:
            copy = c_file_content.readlines()
            counter = 0
            for line in copy:
                if line.startswith("//(script generated comment"):
                        dirty = True
                        copy[counter] = ""
                counter += 1

        if dirty :
            with open(c_file, 'w') as c_file_content:
                c_file_content.writelines(copy)

def all_matches(all_funcs_flag):
    match_dict = dict()
    to_match_files = list(s_files.copy())

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

            fourLetterString = match[0] # aligning string for output
            if len(fourLetterString) == 3:
                fourLetterString += " "
            match_str = "{:.2f} - {} - {}".format(matches[match], fourLetterString, match [1]) # 0-1 float, overlay, function name
            if matches[match] >= 0.995:
                num_perfect_dupes += 1

            if match not in s_files:
                num_decomped_dupes += 1
                match_str += " - (decompiled)"
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
        fourLetterString = file_name[0] # aligning string for output
        if len(fourLetterString) == 3:
            fourLetterString += " "
        out_file.write("ref. - " + fourLetterString + " - " + file_name[1] + " - found " + str(matches[0]) + " matches total:\n")
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
        if not sym_name[1].startswith("D_") and \
           not sym_name[1].startswith("_binary") and \
           not sym_name[1].startswith("jtbl_") and \
           not re.match(r"L[0-9A-F]{8}", sym_name[1]):
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

def parseTxt(file = "" ):
    #get latest .txt
    if file == "":
        folder_path = root_dir
        file_type = '*all_matches.txt'
        files = glob.glob(folder_path + file_type)
        if len(files) == 0:
            sys.exit("no file of type *all_matches.txt available, aborting \n")
        # redid the parsing of the date since "file = max(files, key=os.path.getctime)" was sometimes wrong if 2 .txt were created the same day ??
        elif len (files) > 1:
            fileDated = OrderedDict()
            recentFile = None
            recentFileDate = datetime(1, 1, 1, 0, 0, 0)
            for file in files:
                filesName = file.split('/')[-1]
                fileYear = int(filesName.split('-')[0])
                fileMonth = int(filesName.split('-')[1])
                fileDay = int(filesName.split('-')[2])
                fileHour = int(filesName.split('-')[3])
                fileMin = int(filesName.split('-')[4])
                fileSec = int(filesName.split('-')[5][0:1])
                d = datetime(fileYear, fileMonth, fileDay, fileHour, fileMin, fileSec)
                if d > recentFileDate:
                    recentFile = file

        print("latest file is" + recentFile)

    # rebuild the list of function based on the choosen txt
    dupesGroupList = []
    groupList = []
    with open(recentFile, 'r') as f:
        lineCounter = 0
        for line in f:
            if lineCounter < 6: # skipping the first few lines
                lineCounter += 1
                continue
            elif len(line) < 3: #if line only contains /n
                dupesGroupList.append(groupList)
                groupList = []
            else:
                lineSplit = line.split(" - ")
                if len(lineSplit) < 4:
                    groupList.append((line.split(" - ")[0],line.split(" - ")[1], line.split(" - ")[2]))
                else :
                    groupList.append((line.split(" - ")[0],line.split(" - ")[1], line.split(" - ")[2], line.split(" - ")[3]))
    return dupesGroupList

parser = argparse.ArgumentParser(description="Tool to find duplicates for a specific function or to find all duplicates across the codebase.")
group = parser.add_mutually_exclusive_group()
group.add_argument("-a", "--all", help="find ALL duplicates and output them into a file", action='store_true', required=False)
group.add_argument("-ac", "--allcomment", help="take the output txt file of --all and comment the .c files", action='store_true', required=False)
group.add_argument("-auc", "--alluncomment", help="undo --allcomment", action='store_true', required=False)
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
    # TODO: directory feature currently broken, not sure the effort to fix is worth atm
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
                all_matches_comment()
            else:
                print ("aborted \n")
        elif args.alluncomment:
            all_matches_uncomment()
            
        elif args.short:
            args.threshold = 0.985
            all_matches(False)
        else:
            if args.query is None:
                parser.print_help()
            else:
                do_query((args.query.split(",")[0],args.query.split(",")[1]))