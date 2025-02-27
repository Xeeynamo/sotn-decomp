#!/usr/bin/env python3
import argparse
import os
import sys
import multiprocessing
import decomp_permuter.src.objdump
import decomp_permuter.src.main as permuter
import importer


# These functions exist solely to overwrite some of the undesirable hardcoded behavior in decomp-permuter import.py
# They intentionally retain as much of the original code and naming as possible to avoid unexpected incompatibility
def sotn_create_directory(func_name: str) -> str:
    os.makedirs(f"tools/sotn_permuter/permute.me/", exist_ok=True)
    ctr = 0
    while True:
        ctr += 1
        dirname = f"{func_name}-{ctr}" if ctr > 1 else func_name
        dirname = f"tools/sotn_permuter/permute.me/{dirname}"
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
    parser.add_argument(
        "action",
        choices=actions,
        type=str,
        help="Whether to import or permute the function",
    )

    # This will keep the loader from choking on args intended for decomp-permuter
    args, unknown = parser.parse_known_args()
    # Removes args intended only for the loader
    sys.argv = [a for a in sys.argv if not a.startswith("--v") and a not in actions]

    # Function overwrites
    importer.create_directory = sotn_create_directory
    importer.finalize_compile_command = sotn_finalize_compile_command

    if args.version == "us":
        if args.action == "import":
            importer.DEFAULT_AS_CMDLINE = [
                "mipsel-linux-gnu-as",
                "-march=r3000",
                "-mabi=32",
            ]
            settingsFile = f"tools/sotn_permuter/permuter_settings.{args.version}.toml"
            defaultArgs = (
                [f"--settings={os.path.join(os.getcwd(),settingsFile)}"]
                if not any(i.startswith("--settings") for i in sys.argv)
                else []
            )
        elif args.action == "permute":
            decomp_permuter.src.objdump.MIPS_SETTINGS.executable = [
                "mipsel-linux-gnu-objdump"
            ]
            decomp_permuter.src.objdump.MIPS_SETTINGS.arguments = [
                "-drz",
                "-m",
                "mips:3000",
            ]
            defaultArgs = ["--no-context-output", "--best-only", "-j"]
    elif args.version == "pspeu":
        if args.action == "import":
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
            defaultArgs = (
                [f"--settings={os.path.join(os.getcwd(),settingsFile)}"]
                if not any(i.startswith("--settings") for i in sys.argv)
                else []
            )
        elif args.action == "permute":
            decomp_permuter.src.objdump.MIPS_SETTINGS.executable = [
                "bin/allegrex-objdump"
            ]
            decomp_permuter.src.objdump.MIPS_SETTINGS.arguments = [
                "-drz",
                "-m",
                "mips:allegrex",
            ]
            defaultArgs = ["--no-context-output", "--best-only", "-j"]
    else:
        print(f"{args.version} is currently unsupported.")
        exit()

    if args.action == "import":
        print(f"Importing ${args.version} function.")
        args = [a for a in defaultArgs]
        sys.argv.extend(args)
        importer.main(sys.argv[1:])
    elif args.action == "permute":
        print(f"Permuting ${args.version} function.")
        args = [a for a in defaultArgs if not any(i.startswith(a) for i in sys.argv)]
        args = [a + f"{multiprocessing.cpu_count()}" if a == "-j" else a for a in args]
        sys.argv.extend(args)
        permuter.main()
