#!/usr/bin/env python3
"""Author: ProjectOblivion
This script is intended to address the alterations needed to run decomp-permuter within the context of the sotn-decomp project without
altering the actual decomp-permuter code.
The goal is to make it easier to effectively use decomp-permuter, so feel free to reach out to me with any comments, suggestions, or issues.
For usage instructions, refer to tool/sotn_permuter/README.md
"""

import argparse
import os
import shutil
import sys
import yaml
import multiprocessing
import decomp_permuter.src.objdump
import decomp_permuter.src.main as permuter
import importer

PERMUTE_PATH = os.path.join(os.getcwd(), "tools/sotn_permuter/permute.me/")


# These functions exist solely to overwrite some of the undesirable hardcoded behavior in decomp-permuter import.py
# They intentionally retain as much of the original code and naming as possible to avoid unexpected incompatibility
def sotn_create_directory(func_name: str) -> str:
    os.makedirs(PERMUTE_PATH, exist_ok=True)
    ctr = 0
    while True:
        ctr += 1
        dirname = f"{func_name}-{ctr}" if ctr > 1 else func_name
        dirname = os.path.join(PERMUTE_PATH, dirname)
        try:
            os.mkdir(dirname)
            return dirname
        except FileExistsError:
            pass


def sotn_finalize_compile_command(cmdline: importer.List[str]) -> str:
    quoted = [
        (
            arg
            if arg == "|" or arg == "$INPUT" or arg == "$OUTPUT"
            else importer.shlex.quote(arg)
        )
        for arg in cmdline
    ]
    ind = (quoted + ["|"]).index("|")
    ret_list = quoted[:ind]
    ret_list.extend(['"$INPUT"'] if "$INPUT" not in quoted else [])
    ret_list.extend(quoted[ind:])
    ret_list.extend(["-o", '"$OUTPUT"'] if "$OUTPUT" not in quoted else [])
    return " ".join(ret_list)


if __name__ == "__main__":
    actions = ["import", "permute"]
    parser = argparse.ArgumentParser(
        description="Use decomp-permuter with sotn specific adjustments"
    )
    # sotn-decomp specific args
    parser.add_argument(
        "--version",
        required=False,
        type=str,
        default=os.getenv("VERSION") or "us",
        help="Sets game version and overrides VERSION environment variable",
    )

    subparsers = parser.add_subparsers(
        dest="action", help="Whether to import or permute the function"
    )
    parser_import = subparsers.add_parser(
        "import", help="Import a function to be permuted"
    )
    parser_import.add_argument(
        "source",
        type=str,
        help="The name specified for the splat subsegment or the source filename if not using --overlay",
    )
    parser_import.add_argument(
        "function",
        type=str,
        help="The function to be permuted or the function asm filename if not using --overlay",
    )
    parser_import.add_argument(
        "-o",
        "--overlay",
        required=False,
        type=str,
        help="Specifies the overlay name where the function exists, as it is in the splat config filename, and causes the loader to treat the positional arguments as subsegment and function.",
    )
    parser_import.add_argument(
        "-p",
        "--permute",
        required=False,
        action="store_true",
        help="Begins permuting immediately after the function is imported",
    )
    parser_permute = subparsers.add_parser("permute", help="Permute a function")
    parser_permute.add_argument(
        "function",
        type=str,
        help="The function to be permuted",
    )
    parser_clean = subparsers.add_parser(
        "clean", help="Clean function folders from permuter"
    )
    parser_clean.add_argument(
        "function",
        type=str,
        help='The function to be cleaned, or use "all" to clean all folders',
    )
    # This will keep the loader from choking on args intended for decomp-permuter
    args, unknown = parser.parse_known_args()
    # Removes args intended only for the loader
    if "-o" in sys.argv:
        sys.argv.pop(sys.argv.index("-o") + 1)
    sys.argv = [a for a in sys.argv if a not in ["-o", "-p"] and a not in actions]
    sys.argv = [
        a
        for a in sys.argv
        if not a.startswith("--v")
        and not a.startswith("--o")
        and not a.startswith("--p")
    ]

    # Function overwrites
    importer.create_directory = sotn_create_directory
    importer.finalize_compile_command = sotn_finalize_compile_command

    # Actual loader logic
    if args.version == "us":
        importer.DEFAULT_AS_CMDLINE = [
            "mipsel-linux-gnu-as",
            "-march=r3000",
            "-mabi=32",
        ]
        settingsFile = f"tools/sotn_permuter/permuter_settings.{args.version}.toml"
        importArgs = (
            [f"--settings={os.path.join(os.getcwd(),settingsFile)}"]
            if not any(i.startswith("--settings") for i in sys.argv)
            else []
        )
        decomp_permuter.src.objdump.MIPS_SETTINGS.executable = [
            "mipsel-linux-gnu-objdump"
        ]
        decomp_permuter.src.objdump.MIPS_SETTINGS.arguments = [
            "-drz",
            "-m",
            "mips:3000",
        ]
        permuteArgs = ["--no-context-output", "--best-only", "-j"]
    elif args.version == "pspeu":
        importer.DEFAULT_AS_CMDLINE = [
            "bin/allegrex-as",
            "-march=allegrex",
            "-mabi=eabi",
            "-EL",
            "-G0",
            "-I",
            "include/",
        ]
        settingsFile = f"tools/sotn_permuter/permuter_settings.{args.version}.toml"
        importArgs = (
            [f"--settings={os.path.join(os.getcwd(),settingsFile)}"]
            if not any(i.startswith("--settings") for i in sys.argv)
            else []
        )
        decomp_permuter.src.objdump.MIPS_SETTINGS.executable = ["bin/allegrex-objdump"]
        decomp_permuter.src.objdump.MIPS_SETTINGS.arguments = [
            "-drz",
            "-m",
            "mips:allegrex",
        ]
        permuteArgs = ["--no-context-output", "--best-only", "-j"]
    else:
        print(f"{args.version} is currently unsupported.")
        exit()

    if args.action == "import":
        if args.overlay:
            with open(
                os.path.join(
                    os.getcwd(), f"config/splat.{args.version}.{args.overlay}.yaml"
                )
            ) as yamlFile:
                splatConfig = yaml.safe_load(yamlFile)
            if (
                "options" in splatConfig
                and "nonmatchings_path" in splatConfig["options"]
            ):
                nonmatchingsPath = os.path.join(
                    splatConfig["options"]["nonmatchings_path"],
                )
            else:
                nonmatchingsPath = "nonmatchings"

            segments = splatConfig["segments"]
            subsegments = []
            for segment in segments:
                if "subsegments" in segment:
                    subsegments.extend(
                        [
                            x[-1]
                            for x in segment["subsegments"]
                            if isinstance(x, list)
                            and len(x) > 1
                            and x[1] == "c"
                            and str(x[-1]).endswith(args.source)
                        ]
                    )
            if subsegments and len(subsegments) == 1:
                ssPath = [x for x in subsegments[0].split("/") if x != args.source]
                if ssPath:
                    nonmatchingsPath = os.path.join(nonmatchingsPath, ssPath[0])
                    srcPath = os.path.join(
                        os.getcwd(), splatConfig["options"]["src_path"], ssPath[0]
                    )
                else:
                    srcPath = os.path.join(
                        os.getcwd(), splatConfig["options"]["src_path"]
                    )
            elif len(subsegments) > 1:
                print(f"Multiple subsegments found with {args.source}\n{subsegments}")
                exit(1)
            else:
                print(f"No subsegments were found with {args.source}")
                exit(1)

            cFilename = os.path.join(srcPath, f"{args.source}.c")
            sys.argv = [cFilename if a == args.source else a for a in sys.argv]

            sFilename = os.path.join(
                os.getcwd(),
                splatConfig["options"]["asm_path"],
                nonmatchingsPath,
                args.source,
                f"{args.function}.s",
            )
            sys.argv = [sFilename if a == args.function else a for a in sys.argv]
            funcPath = os.path.join(PERMUTE_PATH, args.function)
            if os.path.isdir(funcPath):
                try:
                    shutil.rmtree(funcPath)
                    print(f"Existing {funcPath} and its contents deleted successfully.")
                except OSError as e:
                    print(f"Error deleting folder {funcPath}: {e}")

        print(f"Importing {args.version} source {args.source} function {args.function}")
        addArgs = [a for a in importArgs]
        sys.argv.extend(addArgs)
        importer.main(sys.argv[1:])
        if args.permute and args.overlay:
            sys.argv = [
                a
                for a in sys.argv
                if not a.startswith("--settings") and not a.endswith(".c")
            ]
            args.function = args.function.split("/")[-1]
            if args.function.endswith(".s"):
                args.function = args.function[-2]
            sys.argv[1] = args.function

    if args.action == "permute" or (
        args.action == "import" and args.permute and args.overlay
    ):
        print(f"Permuting {args.version} function {args.function}")
        sys.argv = [
            os.path.join(PERMUTE_PATH, args.function) if x == args.function else x
            for x in sys.argv
        ]
        addArgs = [a for a in permuteArgs if not any(i.startswith(a) for i in sys.argv)]
        addArgs = [
            a + f"{multiprocessing.cpu_count()}" if a == "-j" else a for a in addArgs
        ]
        sys.argv.extend(addArgs)
        permuter.main()

    if args.action == "clean":
        for dirName in os.listdir(PERMUTE_PATH):
            dirPath = os.path.join(PERMUTE_PATH, dirName)
            if os.path.isdir(dirPath) and (
                dirName.startswith(args.function) or args.function == "all"
            ):
                try:
                    shutil.rmtree(dirPath)
                    print(f"{dirPath} and its contents deleted successfully.")
                except OSError as e:
                    print(f"Error deleting folder {dirPath}: {e}")
