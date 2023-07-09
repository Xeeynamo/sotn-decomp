#!/usr/bin/python3

import argparse
import io
import os
import subprocess
import tempfile
from contextlib import redirect_stdout
from enum import Enum
import m2ctx
import m2c.m2c.main as m2c


# gets the root directory of the project
# the way it works is that it looks for the directory 'src'
def get_root_dir():
    def search_root_dir(base_dir):
        for dir in os.listdir(base_dir):
            if os.path.isdir(dir) and dir == "src":
                return os.path.normpath(base_dir)
        return search_root_dir(os.path.join(base_dir, ".."))

    script_dir = os.path.dirname(os.path.realpath(__file__))
    return search_root_dir(base_dir=script_dir)


def get_all_c_files(src_dir):
    c_files_list = list()
    for root, dirs, files in os.walk(src_dir):
        for f in files:
            if f.endswith(".c"):
                c_files_list.append(os.path.join(root, f))
    return c_files_list


# global variables
root_dir = get_root_dir()
asm_dir = os.path.join(root_dir, "asm")
src_dir = os.path.join(root_dir, "src")
src_files = get_all_c_files(src_dir)


class NonMatchingFunc(object):
    def __init__(self, nonmatching_path):
        split = nonmatching_path.split("/")

        self.asm_path = nonmatching_path
        self.name = os.path.splitext(os.path.basename(nonmatching_path))[0]
        self.overlay_name = split[split.index("nonmatchings") - 1]
        self.text_offset = split[split.index("nonmatchings") + 1]

        assumed_path = f"/{self.overlay_name}/{self.text_offset}.c"
        c_paths = [src for src in src_files if src.endswith(assumed_path)]
        assert len(c_paths) == 1
        self.src_path = c_paths[0]


def get_nonmatching_functions(base_path, func_name) -> list:
    function_list = list()
    for root, dirs, files in os.walk(base_path):
        if "/nonmatchings/" in root:
            for f in files:
                if f == f"{func_name}.s":
                    full_path = os.path.join(root, f)
                    function = NonMatchingFunc(full_path)
                    function_list.append(function)
    return function_list


def get_c_context(src_file) -> str:
    return m2ctx.import_c_file(src_file)


def decompile(func: NonMatchingFunc, ctx_str: str):
    with tempfile.NamedTemporaryFile(
        mode="w", encoding="utf-8", suffix=".c"
    ) as tmp_ctx:
        tmp_ctx.writelines(ctx_str)
        tmp_ctx.flush()
        options = m2c.parse_flags(
            [
                "-P",
                "4",
                "--pointer-style",
                "left",
                "--target",
                "mipsel-gcc-c",
                "--context",
                tmp_ctx.name,
                func.asm_path,
            ]
        )

        with redirect_stdout(io.StringIO()) as f:
            m2c.run(options)
        return f.getvalue()


def guess_unknown_type(dec: str) -> str:
    ret = ""
    for line in dec.splitlines():
        if line.find("?") == -1:
            line = line
        elif line.startswith("? func"):
            line = line.replace("? func_", "/*?*/ void func_")
        elif line.startswith("extern ? D_"):
            line = line.replace("extern ? D_", "extern /*?*/s32 D_")
        elif line.startswith("extern ?* D_"):
            line = line.replace("extern ?* D_", "extern /*?*/u8* D_")
        ret += line + "\n"
    return ret


class InjectRes(Enum):
    SUCCESS = 0
    NOT_INJECTED = 1
    NOT_COMPILABLE = 2
    NON_MATCHING = 3
    UNKNOWN_ERROR = -1


# check if the overlay can be compiled
def check_injected_code() -> InjectRes:
    compile_result = subprocess.run(
        f"make {func.overlay_name}",
        cwd=root_dir,
        shell=True,
        check=False,
        capture_output=True,
    )
    if compile_result.returncode == 0:
        # good news, the code was compilable
        # now checking for the checksum...
        check_result = subprocess.run(
            "make check", cwd=root_dir, shell=True, check=False, capture_output=True
        )
        if check_result.returncode == 0:
            # decompilation successful! There is nothing else to do
            return InjectRes.SUCCESS
        else:
            return InjectRes.NON_MATCHING
    else:
        return InjectRes.NOT_COMPILABLE


def inject_decompiled_function_into_file(func: NonMatchingFunc, dec: str) -> InjectRes:
    with open(func.src_path) as file:
        lines = [line.rstrip() for line in file]

    # this portion of code NEEDS to be resiliant; if there is an exception
    # while writing the file content, the original source code where the
    # function is supposed to be injected will be lost.
    try:
        # assume function matches
        found = False
        newcode = ""
        for line in lines:
            if line.startswith("INCLUDE_ASM(") and func.name in line:
                newcode += dec
                found = True
            else:
                newcode += line + "\n"
        with open(func.src_path, "w") as file:
            file.writelines(newcode)

        if not found:
            return InjectRes.NOT_INJECTED
        result = check_injected_code()
        if result == InjectRes.SUCCESS:
            return result

        newcode = ""
        for line in lines:
            if line.startswith("INCLUDE_ASM(") and func.name in line:
                newcode += "//#ifndef NON_MATCHING\n"
                newcode += f"//{line}\n"
                newcode += "//#else\n"
                newcode += dec
                newcode += "//#endif\n"
            else:
                newcode += line + "\n"
        with open(func.src_path, "w") as file:
            file.writelines(newcode)

        return result

    except Exception as e:
        with open(func.src_path, "w") as file:
            for line in lines:
                file.write(line)
                file.write("\n")
        raise e


def show_asm_differ_command(func: NonMatchingFunc):
    isStage = True
    if (
        func.overlay_name == "dra"
        or func.overlay_name == "ric"
        or func.overlay_name.startswith("tt_")
        or func.overlay_name == "main"
    ):
        isStage = False

    tool_path = os.path.join(root_dir, "tools/asm-differ/diff.py")
    tool_path = os.path.relpath(tool_path)
    overlay_name = f"st/{func.overlay_name}" if isStage else func.overlay_name
    print(f"python3 {tool_path} -mwo --overlay {overlay_name} {func.name}")


parser = argparse.ArgumentParser(description="automatically decompiles a function")
parser.add_argument("function", help="function name to decompile")
parser.add_argument(
    "-o",
    "--overlay",
    help="the overlay where the function to decompile is located",
    type=str,
    default=None,
    required=False,
)

args = parser.parse_args()
if __name__ == "__main__":
    funcs = get_nonmatching_functions(asm_dir, args.function)
    if len(funcs) == 0:
        print(f"function {args.function} not found or already decompiled")

    if args.overlay == None:
        if len(funcs) > 1:
            print(
                f"{len(funcs)} occurrences found for '{args.function}' in the following overlays:"
            )
            for func in funcs:
                print(f"{func.overlay_name} at {func.asm_path}")
            print("invoke this decompiler again with the -o OVERLAY_NAME parameter.")
            os._exit(-1)
        func = funcs[0]
    else:
        func = next((x for x in funcs if x.overlay_name == args.overlay), None)
        if func == None:
            print(
                f"No occurrences found for '{args.function}' between the following overlays:"
            )
            for func in funcs:
                print(f"{func.overlay_name} at {func.asm_path}")
            print("no action will be taken.")
            os._exit(-1)

    # print(f"func: {func.name}")
    # print(f"overlay: {func.overlay_name}")
    # print(f"text: {func.text_offset}")
    # print(f"asm: {func.asm_path}")
    # print(f"src: {func.src_path}")

    ctx = get_c_context(func.src_path)
    dec = decompile(func, ctx)
    dec_res = guess_unknown_type(dec)
    inject_res = inject_decompiled_function_into_file(func, dec_res)
    if inject_res == InjectRes.SUCCESS:
        print(f"function '{func.name}' decompiled successfully!")
    elif inject_res == InjectRes.NON_MATCHING:
        print(f"function '{func.name}' decompiled but not matching")
        show_asm_differ_command(func)
    elif inject_res == InjectRes.NOT_COMPILABLE:
        print(f"function '{func.name}' decompiled but cannot be compiled")
        show_asm_differ_command(func)
    elif inject_res == InjectRes.NOT_INJECTED:
        print(f"function '{func.name}' might already be decompiled")
    else:
        print("unhandled error!")
