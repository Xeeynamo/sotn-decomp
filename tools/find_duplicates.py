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
root_directory = script_dir + "/../"
asm_directory = root_directory + "asm"
build_dir = root_directory + "build/"


def read_roms():
    roms = dict()
    roms["MAIN"] = open(root_directory + "iso/SLUS_000.67", "rb").read()
    roms["DRA"] = open(root_directory + "iso/DRA.BIN", "rb").read()
    roms["RIC"] = open(root_directory + "iso/BIN/RIC.BIN", "rb").read()
    roms["CEN"] = open(root_directory + "iso/ST/CEN/CEN.BIN", "rb").read()
    roms["DRE"] = open(root_directory + "iso/ST/DRE/DRE.BIN", "rb").read()
    roms["MAD"] = open(root_directory + "iso/ST/MAD/MAD.BIN", "rb").read()
    roms["NO3"] = open(root_directory + "iso/ST/NO3/NO3.BIN", "rb").read()
    roms["NP3"] = open(root_directory + "iso/ST/NP3/NP3.BIN", "rb").read()
    roms["NZ0"] = open(root_directory + "iso/ST/NZ0/NZ0.BIN", "rb").read()
    roms["ST0"] = open(root_directory + "iso/ST/ST0/ST0.BIN", "rb").read()
    roms["WRP"] = open(root_directory + "iso/ST/WRP/WRP.BIN", "rb").read()
    roms["RWRP"] = open(root_directory + "iso/ST/RWRP/RWRP.BIN", "rb").read()
    return roms


def find_directory(query):
    for root, directories, files in os.walk(asm_directory):
        for directory in directories:
            if directory == query:
                return os.path.join(root, directory)
    return None


# build a list of all non matching functions .s files names
def get_all_s_files():
    s_files = set()
    for root, directories, files in os.walk(asm_directory):
        for file in files:
            if "data." in file or "nonmatchings" not in os.path.join(root, file):
                continue
            elif file.endswith(".s") and not file.endswith("data.s"):
                overlay = root.split("/")[-3].upper()
                if overlay in roms_bytes.keys(): 
                    s_files.add((overlay,file[:-2]))
    return s_files


def get_symbol_length(sym_name):
    offset = map_offsets[sym_name]
    if "end" in offset and "start" in offset:
        return map_offsets[sym_name]["end"] - map_offsets[sym_name]["start"]
    return 0


# read instructions, returns tuple of 1 out of 4 utf8 decoded bytes, raw bits
def get_symbol_bytes(offsets, function):
    if function not in offsets or "start" not in offsets[function] or "end" not in offsets[function]:
        return None
    bin = offsets[function]["bin"]
    start = offsets[function]["start"]
    end = offsets[function]["end"]
    data_type = offsets[function]["data_type"]

    bytes_data = list(roms_bytes[bin][start:end])

    while len(bytes_data) > 0 and bytes_data[-1] == 0: # removing zeros at the end
        bytes_data.pop()

    instructions = bytes_data[3::4] # read one in 4 byte to only consider the mips opcode and immediates and regalloc https://student.cs.uwaterloo.ca/~isg/res/mips/opcodes

    result = []
    for instruction in instructions:
        result.append(instruction >> 2) #we alread read only 1 byte in 4 but in this byte, we need the 6 first bits only, discarding the 2 we dont want with this >> 2

    return bytes(result).decode('utf-8'), bytes_data, data_type

def parse_map(map_files): # returns list of syms[key,fn] = (bin, rom, cur_file, prev_sym, ram, data_type)
    ram_offset = None
    current_file = "<no file>"
    symbols = {}
    previous_symbol = None
    previous_line = ""
    for key in map_files:
        with open(map_files[key]) as file:
            data_type = "unknown"
            for line in file:
                if ".text" in line:
                    data_type = "text"
                elif ".bss" in line:
                    data_type = "bss"
                elif ".rodata" in line:
                    data_type = "rodata"
                elif ".data" in line:
                    data_type = "data"

                if "load address" in line:
                    if "noload" in line or "noload" in previous_line:
                        ram_offset = None
                        continue
                    ram = int(line[16 : 16 + 18], 0)
                    rom = int(line[59 : 59 + 18], 0)
                    ram_offset = ram - rom
                    continue
                previous_line = line

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
                    current_file = fn
                else:
                    symbols[key,fn] = (key, rom, current_file, previous_symbol, ram, data_type)
                    previous_symbol = (key,fn)
    return symbols


def get_map_offsets(symbols):
    offsets = {}
    for symbol in symbols:
        if symbol[1] == "header": 
            a = 0 #TODO delete ??
        previous_symbol = symbols[symbol][3]
        if symbol not in offsets:
            offsets[symbol] = {}
        if previous_symbol not in offsets:
            offsets[previous_symbol] = {}
        offsets[symbol]["bin"] = symbols[symbol][0]
        offsets[symbol]["start"] = symbols[symbol][1]
        offsets[previous_symbol]["end"] = symbols[symbol][1]
        offsets[symbol]["data_type"] = symbols[symbol][5]
    return offsets


def is_zeros(values):
    for value in values:
        if value != 0:
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


#TODO clarify b
def get_pair_score(query_bytes, b):
    b_bytes = get_symbol_bytes(map_offsets, b)

    if query_bytes and b_bytes:
        return diff_syms(query_bytes, b_bytes)
    return 0


def get_matches(query):
    query_bytes = get_symbol_bytes(map_offsets, query)
    if query_bytes is None:
        sys.exit("Symbol '" + query + "' not found")

    result = {}
    for symbol in map_offsets:
        if symbol is not None and query != symbol:
            score = get_pair_score(query_bytes, symbol)
            if score >= args.threshold:
                result[symbol] = score
    return OrderedDict(sorted(result.items(), key=lambda kv: kv[1], reverse=True))


def do_query(query):
    matches = get_matches(query)
    number_matches = len(matches)

    if number_matches == 0:
        print(query + " - found no matches")
        return

    more_message = ":"
    if args.num_out < number_matches:
        more_message = " (showing only " + str(args.num_out) + "):"

    print(query[0] + " - " + query[1]  + " - found " + str(number_matches) + " matches total" + more_message)
    
    counter = 0
    for match in matches:
        if counter == args.num_out:
            break
        match_str = "{:.3f} - {}".format(matches[match], match)
        if match not in s_files:
           match_str += " - (decompiled)"
        print(match_str)
        counter += 1
    print()

def all_matches_comment():
    c_files = list()
    for root, directories, files in os.walk(root_directory + "src"):
                for file in files:
                    if file.endswith(".c"):
                        c_files.append(os.path.join(root, file))

    print("Starting to scan .c files to comment the definitions", end='\n')
    for duplicatesFunctionGroups in parseTxt():
        comment0 = "//(script generated comment, do not edit)Found duplicates:"
        comment1 = ""
        for duplicatesFunctionGroup in duplicatesFunctionGroups:
            score = duplicatesFunctionGroup[0].strip('\n').strip(' ')
            rom = duplicatesFunctionGroup[1].strip('\n').strip(' ')
            function = duplicatesFunctionGroup[2].strip('\n').strip(' ')

            if len(duplicatesFunctionGroup) > 3:
                isDecompiled = duplicatesFunctionGroup[3].strip('\n').strip(' ')
            else: isDecompiled = ""
            comment1 += ", " + score + " - " + rom + " - " + function + " - " + isDecompiled
        comment1 += '\n'

        for duplicatesFunctionGroup in duplicatesFunctionGroups:
            score = duplicatesFunctionGroup[0].strip('\n').strip(' ')
            rom = duplicatesFunctionGroup[1].strip('\n').strip(' ')
            function = duplicatesFunctionGroup[2].strip('\n').strip(' ')

            for c_file in c_files:
                dirty = False
                with open(c_file, 'r') as c_file_content:
                    file_copy = c_file_content.readlines()
                    counter = 0
                    for line in file_copy:
                        if function in line and c_file.split('/')[-2].upper() == rom:
                            # detecting ASM include
                            if line.startswith("INCLUDE_ASM"):
                                dirty = True
                                # detecting already present genereted comment and update it
                                if file_copy[counter - 1].startswith("//(script generated comment"):
                                        file_copy[counter - 1] = comment0 + comment1
                                # no generated comment detected
                                else :
                                    file_copy[counter] = comment0 + comment1 + line
                            # detecting C definition
                            elif (not line.startswith(" ") and not line.startswith("  ") and not line.startswith("/")) and not line.endswith(";\n"):
                                dirty = True
                                # detecting already present genereted comment and update it
                                if file_copy[counter - 1].startswith("//(script generated comment"):
                                    file_copy[counter - 1] = comment0 + comment1
                                # no generated comment detected
                                else :
                                    file_copy[counter] = comment0 + comment1 + line
                            
                        counter += 1
                        if dirty: break # we only want to comment what comes first the ASM include or the C definition, not both

                if dirty :
                    with open(c_file, 'w') as c_file_content:
                        c_file_content.writelines(file_copy)

                print(function + "\n")

def all_matches_uncomment():
    c_files = list()
    for root, directories, files in os.walk(root_directory + "src"):
                for file in files:
                    if file.endswith(".c"):
                        c_files.append(os.path.join(root, file))

    print("Starting to scan .c files to uncomment the definitions", end='\n')
    for c_file in c_files:
        dirty = False
        with open(c_file, 'r') as c_file_content:
            file_copy = c_file_content.readlines()
            counter = 0
            for line in file_copy:
                if line.startswith("//(script generated comment"):
                        dirty = True
                        file_copy[counter] = ""
                counter += 1

        if dirty :
            with open(c_file, 'w') as c_file_content:
                c_file_content.writelines(file_copy)

def all_matches(all_functions_flag):
    match_dict = dict()
    to_match_files = list(s_files.copy())

    # assumption that after half the functions have been matched, nothing of significance is left
    # since duplicates that already have been discovered are removed from tp_match_files
    if all_functions_flag:
        iteration_limit = 0
    else:
        iteration_limit = len(s_files) / 2

    number_decompiled_duplicates = 0
    number_undecompiled_duplicates = 0
    number_perfect_duplicates = 0

    counter = 0
    while len(to_match_files) > iteration_limit:
        file = to_match_files[0]

        counter += 1
        print("File matching progress: {:%}".format(counter / (len(s_files) - iteration_limit)), end='\r')

        if get_symbol_length(file) < 16:
            to_match_files.remove(file)
            continue

        matches = get_matches(file)
        number_matches = len(matches)
        if number_matches == 0:
            to_match_files.remove(file)
            continue

        number_undecompiled_duplicates += 1

        match_list = []
        for match in matches:
            if match in to_match_files:
                counter += 1
                to_match_files.remove(match)

            four_letter_string = match[0] # aligning string for output
            if len(four_letter_string) == 3:
                four_letter_string += " "
            match_string = "{:.2f} - {} - {}".format(matches[match], four_letter_string, match [1]) # 0-1 float, overlay, function name
            if matches[match] >= 0.995:
                number_perfect_duplicates += 1

            if match not in s_files:
                number_decompiled_duplicates += 1
                match_string += " - (decompiled)"
            else:
                number_undecompiled_duplicates += 1

            match_list.append(match_string)

        match_dict.update({file: (number_matches, match_list)})
        to_match_files.remove(file)

    output_match_dict(match_dict, number_decompiled_duplicates, number_undecompiled_duplicates, number_perfect_duplicates, counter)


def output_match_dict(match_dict, number_decompiled_duplicates, number_undecompiled_duplicates, number_perfect_duplicates, number_checked_files):
    out_file = open(datetime.today().strftime('%Y-%m-%d-%H-%M-%S') + "_all_matches.txt", "w+")

    out_file.write("Number of s-files: " + str(len(s_files)) + "\n"
                   "Number of checked s-files: " + str(round(number_checked_files)) + "\n"
                   "Number of decompiled duplicates found: " + str(number_decompiled_duplicates) + "\n"
                   "Number of undecompiled duplicates found: " + str(number_undecompiled_duplicates) + "\n"
                   "Number of overall exact duplicates found: " + str(number_perfect_duplicates) + "\n\n")

    sorted_dict = OrderedDict(sorted(match_dict.items(), key=lambda item: item[1][0], reverse=True))

    print("Creating output file: " + out_file.name, end='\n')
    for file_name, matches in sorted_dict.items():
        four_letter_string = file_name[0] # aligning string for output
        if len(four_letter_string) == 3:
            four_letter_string += " "
        out_file.write("ref. - " + four_letter_string + " - " + file_name[1] + " - found " + str(matches[0]) + " matches total:\n")
        for match in matches[1]:
            out_file.write(match + "\n")
        out_file.write("\n")

    out_file.close()

def is_decompiled(symbol):
    return symbol not in s_files

def do_cross_query():
    countable_dict = Counter()
    clusters = []

    symbol_bytes = {}
    for symbol_name in map_symbols:
        if not symbol_name[1].startswith("D_") and \
           not symbol_name[1].startswith("_binary") and \
           not symbol_name[1].startswith("jtbl_") and \
           not re.match(r"L[0-9A-F]{8}", symbol_name[1]):
            if get_symbol_length(symbol_name) > 16:
                symbol_bytes[symbol_name] = get_symbol_bytes(map_offsets, symbol_name)

    for symbol_name, query_bytes in symbol_bytes.items():
        cluster_match = False
        for cluster in clusters:
            cluster_first = cluster[0]
            cluster_score = diff_syms(query_bytes, symbol_bytes[cluster_first])
            if cluster_score >= args.threshold:
                cluster_match = True
                if is_decompiled(symbol_name) and not is_decompiled(cluster_first):
                    countable_dict[symbol_name] = countable_dict[cluster_first]
                    del countable_dict[cluster_first]
                    cluster_first = symbol_name
                    cluster.insert(0, cluster_first)
                else:
                    cluster.append(symbol_name)

                if not is_decompiled(cluster_first):
                    countable_dict[cluster_first] += len(symbol_bytes[cluster_first][0])

                if len(cluster) % 10 == 0 and len(cluster) >= 10:
                    print(f"Cluster {cluster_first} grew to size {len(cluster)} - {symbol_name}: {str(cluster_score)}")
                break
        if not cluster_match:
            clusters.append([symbol_name])
    print(countable_dict.most_common(100))

def parseTxt(file = "" ):
    #get latest .txt
    if file == "":
        folder_path = root_directory
        file_type = '*all_matches.txt'
        files = glob.glob(folder_path + file_type)
        if len(files) == 0:
            sys.exit("no file of type *all_matches.txt available, aborting \n")
        # redid the parsing of the date since "file = max(files, key=os.path.getctime)" was sometimes wrong if 2 .txt were created the same day ??
        elif len (files) > 1:
            fileDated = OrderedDict()
            recent_file = None
            recent_file_date = datetime(1, 1, 1, 0, 0, 0)
            for file in files:
                files_name = file.split('/')[-1]
                file_year = int(files_name.split('-')[0])
                file_month = int(files_name.split('-')[1])
                file_day = int(files_name.split('-')[2])
                file_hour = int(files_name.split('-')[3])
                file_min = int(files_name.split('-')[4])
                file_sec = int(files_name.split('-')[5][0:1])
                date = datetime(file_year, file_month, file_day, file_hour, file_min, file_sec)
                if date > recent_file_date:
                    recent_file = file

        print("latest file is" + recent_file)

    # rebuild the list of function based on the choosen txt
    duplicates_group_list = []
    group_list = []
    with open(recent_file, 'r') as file:
        line_counter = 0
        for line in file:
            if line_counter < 6: # skipping the first few lines
                line_counter += 1
                continue
            elif len(line) < 3: #if line only contains /n
                duplicates_group_list.append(group_list)
                group_list = []
            else:
                line_split = line.split(" - ")
                if len(line_split) < 4:
                    group_list.append((line.split(" - ")[0],line.split(" - ")[1], line.split(" - ")[2]))
                else :
                    group_list.append((line.split(" - ")[0],line.split(" - ")[1], line.split(" - ")[2], line.split(" - ")[3]))
    return duplicates_group_list


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
                for file in files:
                    if key.lower() + ".map" == file or "st"+ key.lower() + ".map" == file:
                        map_files[key] = os.path.join(root, file)
    
    map_symbols = parse_map(map_files)
    map_offsets = get_map_offsets(map_symbols)

    s_files = get_all_s_files()

    # directory of a file or function
    # TODO: directory feature currently broken, not sure the effort to fix is worth atm
    query_dir = find_directory(args.query)

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
                try:
                    do_query((args.query.split(",")[0],args.query.split(",")[1]))
                except:
                    # same as above but considering any func with the name accross all rom, not only one
                    for rom, function in map_symbols:
                        if args.query == function:
                            do_query((rom, function))
                            break
