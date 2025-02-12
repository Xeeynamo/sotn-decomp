#!/usr/bin/env python3

# Performs analysis of every function in the asm directory. For each function, finds
# all functions called by this one, and all functions that call this one.
# By default, this will create several thousand SVG files.
# Run with --dry to generate data for all files as testrun, without outputting files.
# Run with --ultradry to just do the function analysis, but skip generating SVG.

# This will print the time taken for each step of the process, which is helpful for
# benchmarking, as well as determining if execution is taking longer as the repo grows.
# On my machine, all steps prior to SVG generation take less than 1 second, and SVG
# generation takes 30 seconds (regardless of dry mode). Note times printed are cumulative
# in the sense that the printed time is not per-step, but is time since execution start.

from pathlib import Path
import os
import re
import graphviz
import time
import multiprocessing

import argparse

parser = argparse.ArgumentParser(description="Generate call diagram SVGs")
parser.add_argument(
    "--dry",
    action="store_true",
    help="Perform a dry run. Generate SVGs, but do not output to file",
)
parser.add_argument(
    "--ultradry",
    action="store_true",
    help="Perform a dry run. Calculate call hierarchy, but skip generating SVGs",
)
parser.add_argument(
    "--output_dir",
    type=str,  # Expecting a string as input
    help="Output directory",
)
output_dir = "function_calls"
# All functions I've found that are used in a 'jalr' instruction in the game
callable_registers = ["$v0", "$v1", "$a0", "$a1", "$t2"]
# Handles drawing in the blobs
graph_colors = {"N/A": "lightblue", "True": "green", "False": "red"}


# Important function. For a given line of assembly including a 'jal' or 'jalr' instruction,
# Make an attempt to identify the function being called. For 'jal' this is usually easy.
# For 'jalr' it tends to require more processing.
def handle_jal_call(full_file, call_index):
    call_line = full_file[call_index]
    call_target = call_line.split(" ")[-1].strip()
    if call_target in function_lookup:  # easy, just a direct function call by name
        return call_target
    # Check if we're calling based on a register's value.
    if call_target in callable_registers:
        # Find what line sets that register.
        searchback = 1
        while (
            call_target not in full_file[call_index - searchback]
            or "beqz" in full_file[call_index - searchback]
            or "jalr" in full_file[call_index - searchback]
        ):
            searchback += 1
        callreg_setline = full_file[call_index - searchback]
        if "g_api" in callreg_setline:
            # regex that will pull out the function being called
            match = re.search(r"%lo\(([^)]+)\)", callreg_setline)
            # Handle members of the g_api Overlay object
            if "g_api_o_" in match.group(1):
                return match.group(1).replace("_", ".")
            # Handle the first element of it, where the symbol gets truncated to just g_api
            if "g_api" == match.group(1):
                return "g_api.o.Update"
            # Handle functions such as AllocPrimBuffers that are referenced indirectly through g_api
            if match.group(1).replace("g_api_", "") in function_lookup:
                return match.group(1).replace("g_api_", "")
            # Handle remaining symbols that are just straight in GameApi
            if match.group(1) in function_lookup:
                return match.group(1)
        # Calling something held in a variable, usually a D_ or a g_
        variable_pattern = r"lw\s+" + "\\" + call_target + r", %lo\(([^)]+)\)"
        if match := re.search(variable_pattern, callreg_setline):
            return match.group(1)
        if "0x28($s0)" in callreg_setline or "-0xC($s0)" in callreg_setline:
            return "UnknownpfnEntityUpdate"
        # happens in NZ0/func_801C1034. v0 is set by dereferencing a register.
        target_setter_pattern = r"lw\s+" + "\\" + call_target + r", 0x.{,2}\((\$\w+)"
        if match := re.search(target_setter_pattern, callreg_setline):
            source_register = match.group(1)
            pattern = r"\s{3,}" + "\\" + source_register
            # Now find where THAT was set. Repeat the same we did for v0.
            searchback += 1
            while not re.search(pattern, full_file[call_index - searchback]):
                searchback += 1
            if "g_api" in full_file[call_index - searchback]:
                # regex that will pull out the function being called
                match = re.search(r"%lo\(([^)]+)\)", full_file[call_index - searchback])
                if match:
                    return match.group(1)
            else:
                match = re.search(
                    r"\(([^)]*)\)", full_file[call_index - searchback]
                )  # use anything in parentheses
                if match:
                    return match.group(1)
        # Special cases that would otherwise fail. Disable any one of these to see where it's needed.
        if (
            "8016B3E4" in callreg_setline
        ):  # weird case in one function with compiler optimizing two calls into one
            return "PlaySfx"
        if "0xB8($a2)" in callreg_setline or "-0x20($s0)" in callreg_setline:
            return "UnknownEntityFunction"
        if "8017B5A8" in callreg_setline:
            return "g_api_CreateEntFactoryFromEntity"

        if any(
            x in callreg_setline for x in ["80015840", "80015E74", "8001923C"]
        ):  # weird sdk stuff
            return "UnknownSDKFunction"
        print("made it out the bottom")
        print(callreg_setline)
    print(call_line)
    print(full_file[3])
    print("Failed to return a value")
    exit(1)


# SDK functions in include/psxsdk/{whatever}.h are not in the decomp, but may be called.
def get_sdk_funcs():
    functions = []
    # weird thing where setjmp is commented out in libc.h; we add it manually here for now.
    functions.append("setjmp")
    for sdkfile in ["libgpu.h", "libc.h", "libcd.h", "libapi.h", "kernel.h"]:
        with open(f"include/psxsdk/{sdkfile}") as f:
            lines = f.readlines()
            for line in lines:
                match = re.search(
                    r"(\w+)\(", line
                )  # Find a word right before an open parenthesis - a function name.
                if match:
                    functions.append(match.group(1))
    return functions


# Many functions in main are not being splatted out yet, so we add them here, like SDK.
def get_main_funcs():
    # hardcode this one in there, it's not in any assembly file
    functions = ["g_MainGame"]
    for file in Path("asm/us/main").rglob("*[!data].s"):
        with open(file) as f:
            lines = f.readlines()
            for line in lines:
                if "glabel" in line:
                    functions.append(line.split()[1])
    return functions


# Functions in gameapi are often strange, especially in the Overlay member.
def get_gapi_funcs():
    found_functions = []
    # Load up symbols for the relative functions loaded into GameApi
    with open("config/symbols.us.txt") as f:
        symbols = f.readlines()
        for symbol in symbols:
            symbolname = symbol.split(" = ")[0]
            if "g_api_" in symbolname:
                found_functions.append(symbolname)
                found_functions.append(symbolname.replace("_", "."))
    # Special case, first element of struct doesn't have a dedicated symbol.
    found_functions.append("g_api.o.Update")
    return found_functions


# Functions which have been identified as handwritten. These will be in splat
# with something like: - [0x3ABA4, asm, handwritten/DecDCTvlc]
def get_handwritten_funcs():
    handwritten = [
        sotn_function(s.stem, str(s))
        for s in Path("asm").rglob("*.s")
        if "handwritten" in str(s)
    ]
    return handwritten


def is_decompiled(srcfile, fname):
    with open(srcfile) as f:
        srclines = f.readlines()
    for line in srclines:
        if fname in line and "INCLUDE_ASM" in line:
            return False
    return True


def get_c_filename(asm_filename):
    assert "asm/us" in asm_filename and "/nonmatchings/" in asm_filename
    # Convert a path in asm/us to a path in src
    srcpath = asm_filename.replace("asm/us", "src")
    # Count the number of paths after "nonmatchings". If there are two directories,
    # then the file must be specifying a path in src. If not, then it's a path in the overlay.
    # Example: specifying wrp/collision should be treated differently than if it was just "collision"
    paths_after_nonmatchings = srcpath.split("/nonmatchings/")[1].count("/")
    # Raw file which goes in the default overlay directory
    if paths_after_nonmatchings == 1 or srcpath.startswith("src/main"):
        no_nonmatchings = srcpath.replace("/nonmatchings/", "/")
    # Has an extra directory, so remove overlay specified before /nonmatchings/
    if paths_after_nonmatchings == 2:
        overlay = srcpath.split("/")[2]
        no_nonmatchings = srcpath.replace("/" + overlay + "/nonmatchings/", "/")
    # Little known rpartition drops the function name to get the last directory, which should be c file name.
    c_filename = no_nonmatchings.rpartition("/")[0] + ".c"
    assert os.path.exists(c_filename)
    return c_filename


# Given a function name called from a caller, find which of a set of candidates is probably the function being called.
# We do this based on their C file paths, assuming that a longer shared path (usually, sharing an overlay) will correspond
# to being the function being called. This logic may need to be improved.
def find_func_match(caller, candidates):
    prefix_lengths = [
        len(os.path.commonprefix([caller.c_filename, candidate.c_filename]))
        for candidate in candidates
    ]
    # Detect ties. If this is 1, there is a single longest match, otherwise, resolve the tie.
    longest_match_count = prefix_lengths.count(max(prefix_lengths))
    if longest_match_count == 1:
        return candidates[prefix_lengths.index(max(prefix_lengths))]
    elif longest_match_count > 1:
        # We have a tie. This happens when there are multiple copies of a function,
        # but neither matches the caller's overlay. For example, UpdateAnim is in both DRA
        # and tt_000, while being called from RIC (and some weapons). CreateEntFactoryFromEntity
        # is in both DRA and RIC, while being called from tt_000. When we run into these situations,
        # we will use the DRA version, since it's the overarching unifier for the rest of the game.
        for candidate in candidates:
            if candidate.unique_name.startswith("dra."):
                return candidate
        # Resolve wrp/rwrp matches by pulling from wrp. This may need to have different logic in future.
        if "wrp" in caller.asm_filename:
            for candidate in candidates:
                if "wrp" in candidate.unique_name:
                    return candidate
        print("Unbreakable tie found, exiting!")
        exit(4)
    else:
        print("No candidates!")
        exit(3)


# Given a sotn_function object, go through and find all its function calls.
# Any function called should be added as a callee for the input_function, and
# the input_function should be added as a caller for the called function.
def analyze(input_function):
    with open(input_function.asm_filename) as f:
        asm_lines = f.read().split("\n")
        for i, line in enumerate(asm_lines):
            if "jal" in line:
                callee_name = handle_jal_call(asm_lines, i)
                # Special case due to a problem with assembly assigning symbols (see PR #1034)
                if "g_PlOvl" in callee_name:
                    input_function.add_callee(fake_function("g_PlOvl"))
                    continue
                if callee_name.startswith("D_"):
                    input_function.add_callee(fake_function(callee_name))
                    continue
                if callee_name.startswith("Unknown"):
                    input_function.add_callee(fake_function(callee_name))
                    continue
                candidate_callees = function_lookup[callee_name]
                assert len(candidate_callees) > 0
                # It's one of the special cases that we establish
                if isinstance(candidate_callees, str):
                    input_function.add_callee(fake_function(callee_name))
                    continue
                # If there is only one candidate (only one function in the codebase by that name), we have it.
                if len(candidate_callees) == 1:
                    callee = candidate_callees[0]
                    input_function.add_callee(callee)
                    callee.add_caller(input_function)
                else:
                    best_match = find_func_match(input_function, candidate_callees)
                    input_function.add_callee(best_match)
                    best_match.add_caller(input_function)


# Create an index.html which lists all functions with their overlays
def generate_html(function_list):
    # Sort all functions into overlays, with the name as tiebreaker to sort within overlays
    sorted_funcs = sorted(
        [f for f in function_list if f.overlay != "mad"],
        key=lambda x: (x.overlay, x.name),
    )
    html = '<html><head><meta charset="UTF-8"></head><body>\n'
    active_overlay = ""
    # Now iterate through all functions, creating links to their SVG files.
    for f in sorted_funcs:
        # When the overlay changes, add a heading.
        if f.overlay != active_overlay:
            # End the previous overlay's list, unless this is the first overlay.
            if active_overlay != "":
                html += "</ul>\n"
            active_overlay = f.overlay
            html += f"<h2>{active_overlay}</h2>\n"
            html += "<ul>\n"
        dec_symbol = "✅" if f.decompile_status == "True" else "❌"
        html += f'<li><a href="{f.unique_name}.svg">{dec_symbol + f.name}</a></li>\n'
    html += "</ul>\n"
    html += "</body></html>"
    return html


# Create a markdown file pointing us toward all the different function graphs
def generate_md(function_list):
    sorted_funcs = sorted(
        [f for f in function_list if f.overlay != "mad"],
        key=lambda x: (x.overlay, x.name),
    )
    md_page = ""
    active_overlay = ""
    # Now iterate through all functions, creating links to their SVG files.
    for f in sorted_funcs:
        # When the overlay changes, add a heading.
        if f.overlay != active_overlay:
            active_overlay = f.overlay
            md_page += f"# {active_overlay}\n"
        dec_symbol = "✅" if f.decompile_status == "True" else "❌"
        md_page += (
            f"- [{dec_symbol} {f.name}]({output_dir}/{f.unique_name}.svg?raw=1)\n"
        )
    return md_page


# This represents calls that we can't connect to a real C function. This includes SDK functions, or calls where
# it is unclear what actual function is being called.
class fake_function:
    def __init__(self, name):
        self.name = name
        self.decompile_status = "N/A"
        self.unique_name = name


class sotn_function:
    def __init__(self, name, asm_filename):
        self.name = name
        self.asm_filename = asm_filename
        # From the asm filename, get the C filename
        if "handwritten" in self.asm_filename:
            self.decompile_status = "N/A"
        else:
            self.c_filename = get_c_filename(self.asm_filename)
            self.decompile_status = str(is_decompiled(self.c_filename, self.name))
        self.callers = {}
        self.callees = {}

        filepath_split = self.asm_filename.split("/")
        self.overlay = filepath_split[2]
        if self.overlay in ["st", "boss", "servant"]:
            self.overlay = filepath_split[3]
        if self.overlay == "weapon":
            self.overlay = filepath_split[4]
        # Name used in SVG files, must be different from any other function
        self.unique_name = ".".join([self.overlay, self.name])

    def __repr__(self):
        return f"{self.name} at {self.asm_filename}\n{self.c_filename}\n{self.callers}\n{self.callees}\n"

    def add_callee(self, other_function):
        if other_function.unique_name in self.callees:
            self.callees[other_function.unique_name][0] += 1
        else:
            self.callees[other_function.unique_name] = [
                1,
                other_function.decompile_status,
            ]

    def add_caller(self, other_function):
        if other_function.unique_name in self.callers:
            self.callers[other_function.unique_name][0] += 1
        else:
            self.callers[other_function.unique_name] = [
                1,
                other_function.decompile_status,
            ]

    def render_svg(self):
        graph = graphviz.Digraph(self.unique_name, graph_attr={"ranksep": "2"})
        graph.node(
            self.unique_name,
            style="filled",
            fillcolor=graph_colors[self.decompile_status],
        )
        # We sort the items so they will be alphabetized. This reduces changes from
        # one run to the next. Any differences should be due to changes in the repo.
        for callee, flags in sorted(self.callees.items()):
            graph.node(
                callee,
                style="filled",
                fillcolor=graph_colors[flags[1]],
                href=callee + ".svg",
            )
            graph.edge(self.unique_name, callee, headlabel=str(flags[0]))
        # Same sorting as above
        for caller, flags in sorted(self.callers.items()):
            graph.node(
                caller,
                style="filled",
                fillcolor=graph_colors[flags[1]],
                href=caller + ".svg",
            )
            graph.edge(caller, self.unique_name, taillabel=str(flags[0]))
        imgbytes = graph.pipe(format="svg")
        return imgbytes

    def create_svg_file(self):
        with open(f"{output_dir}/{self.unique_name}.svg", "wb") as f:
            f.write(self.render_svg())


if __name__ == "__main__":
    timer = time.perf_counter()
    args = parser.parse_args()
    if args.output_dir:
        output_dir = args.output_dir
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)
    # 1: Create baseline function objects for every .s file
    functions = [
        sotn_function(s.stem, str(s))
        for s in Path("asm/us").rglob("*.s")
        if "nonmatchings" in str(s)
    ]
    if len(functions) == 0:
        print("Error! You probably didn't run `make force_extract` first")
        exit(2)
    print(
        f"Initialized {len(functions)} function objects in {time.perf_counter()-timer} seconds"
    )

    # Make sure all the functions really do have a unique name
    assert len(functions) == len(set(f.unique_name for f in functions))

    # This is a "phonebook" that allows you to get all the function objects matching any function name
    # This is needed because functions only call another function by name. Therefore, with the name,
    # this lookup table allows you to find the sotn_function object which is being called.
    function_lookup = {}
    for f in functions:
        if f.name not in function_lookup:
            function_lookup[f.name] = [f]
        else:
            function_lookup[f.name].append(f)
    for f in get_handwritten_funcs():
        if f.name not in function_lookup:
            function_lookup[f.name] = [f]
        else:
            function_lookup[f.name].append(f)
    # Add SDK functions (which don't exist in ASM or C form) as bare entries
    for f in get_sdk_funcs():
        function_lookup[f] = "SDK"
    # Similar for main functions
    for f in get_main_funcs():
        function_lookup[f] = "MAIN"
    for f in get_gapi_funcs():
        function_lookup[f] = "GAPI"

    print(f"Created function lookup table in {time.perf_counter() - timer} seconds")
    # 2: For each function, find what it calls. When finding a callee, also add itself as caller.
    for function in functions:
        if not any(x in function.c_filename for x in ["psxsdk", "mad"]):
            analyze(function)
    print(f"Calculated call relations in {time.perf_counter() - timer} seconds")
    if not args.ultradry:
        print(f"Rendering in {'dry' if args.dry else 'full output'} mode")

        # 3: Render all the functions, either dry or saved to file.
        def worker(function):
            if args.dry:
                function.render_svg()
            else:
                function.create_svg_file()

        with multiprocessing.Pool() as pool:
            pool.map(worker, functions)
        print(f"Completed SVG rendering in {time.perf_counter() - timer} seconds")
        if not args.dry:
            html = generate_html(functions)
            with open(f"{output_dir}/index.html", "w") as f:
                f.write(html)
            markdown = generate_md(functions)
            with open(f"{output_dir}/../function_graphs.md", "w") as f:
                f.write(markdown)
                print("Markdown written to " + os.path.realpath(f.name))
            print(f"Generated HTML in {time.perf_counter() - timer} seconds")
    print("Exiting.")
