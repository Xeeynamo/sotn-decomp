#!/usr/bin/env python

import argparse
import os
import hashlib
import pathlib
import shutil
import subprocess
import sys

PATH_SCRIPT = pathlib.Path(__file__).resolve().parent
REC2_ROOT = PATH_SCRIPT.parent.parent

print(PATH_SCRIPT, REC2_ROOT)
KNOWH_HASHES = (
    "9b896c2cbb170c01b3e9f904ce5e1808db29fe5b51184a5d55a6d19b1799b58d",  # Steam version
)


def main() -> int:
    STAGE_SYMBOLS = "symbols"
    STAGE_SRE_CREATE = "sre_create"
    STAGE_SRE_TYPES = "sre_types"
    STAGE_SRE_SYMBOLS = "sre_symbols"
    stages = [STAGE_SYMBOLS, STAGE_SRE_CREATE, STAGE_SRE_TYPES, STAGE_SRE_SYMBOLS]

    parser = argparse.ArgumentParser(allow_abbrev=False)
    parser.add_argument("--ghidra-root", dest="ghidra_root", type=pathlib.Path, help="Path of ghidra root")
    parser.add_argument("--exe", dest="path_exe", metavar="EXE", type=pathlib.Path, help="Path of CARMA2_HW.EXE")
    parser.add_argument("--project-name", default="c2", help="Ghidra project name (default=c2)")
    parser.add_argument("--project-location", type=pathlib.Path, default=pathlib.Path.cwd(), help="ghidra project location (default=working directory)")
    parser.add_argument("--symbols", type=pathlib.Path, default=pathlib.Path.cwd() / "symbols.json", help="Path of symbols.json")
    parser.add_argument("-Werror", dest="werror", action="store_true", help="Treat warnings as errors")
    parser.add_argument("--stage", default=stages[0], choices=stages, help="Start from what stage (option meant for development)")
    args = parser.parse_args()

    warningHappened = False
    stage = stages.index(args.stage)

    def warn(message: str) -> None:
        print(f"Warning: { message }", file=sys.stderr)
        warningHappened = True

    if not args.ghidra_root:
        default_ghidra = os.getenv("GHIDRA_INSTALL_PATH")
        if default_ghidra:
            args.ghidra_root = pathlib.Path(default_ghidra)
    if not args.ghidra_root:
        path_runGhidra = shutil.which("runGhidra")
        if path_runGhidra:
            args.ghidra_root = pathlib.Path(os.path.dirname(path_runGhidra))

    if not args.ghidra_root:
        parser.error("Ghidra root not configured. This can be done through --ghidra-root or the GHIDRA_INSTALL_PATH environment variable")

    ghidra_headless_ext = ".bat" if sys.platform == "win32" else ""
    ghidra_headless = args.ghidra_root / "support" / ("analyzeHeadless" + ghidra_headless_ext)

    if not ghidra_headless.is_file():
        parser.error(f"{ ghidra_headless } does not exist or is not a file. Is Ghidra installed correctly?")

    if not args.path_exe:
        path_exe = pathlib.Path.cwd() / "CARMA2_HW.EXE"
        if path_exe.exists():
           args.path_exe = path_exe

    if not args.path_exe:
        parser.error("Can't find CARMA2_HW.EXE")

    if not args.path_exe.is_file():
        parser.error(f"{args.path_exe} does not exist or is not a file")

    print(f"ghidra root         = { args.ghidra_root }")
    print(f"ghidra headless     = { ghidra_headless }")
    print(f"exe                 = { args.path_exe }")
    print(f"project name        = { args.project_name }")
    print(f"project location    = { args.project_location }")

    hasher = hashlib.sha256()
    hasher.update(args.path_exe.open("rb").read())
    digest = hasher.hexdigest()
    if digest not in KNOWH_HASHES:
        warn("Unknown hash. If your executable is unmodified and compatible with rec2, consider adding it to the known hashes list")

    if stage <= stages.index(STAGE_SRE_CREATE):
        print("Creating a Ghidra project...")
        result = subprocess.run([
            ghidra_headless,
            args.project_location,
            args.project_name,
            # "-loader", "BinaryLoader",
            # "-loader-baseAddr", "060004080",
            "-processor", "SuperH:BE:32:SH-2",
            "-import", args.path_exe,
        ])
        if result.returncode != 0:
            print("Failed to create a Ghidra project", file=sys.stderr)
            return 1
        print("Ghidra project created!")

    result = subprocess.run([
        ghidra_headless,
        args.project_location,
        args.project_name,
        "-scriptPath", PATH_SCRIPT,
        "-postScript", "apply-mem.py", args.ghidra_root, args.symbols,
        "-process", args.path_exe.name,
        "-noanalysis",
    ])
    if result.returncode != 0:
        print("Failed to apply memory", file=sys.stderr)
        return 1
    print("Memory applied!")

    if stage <= stages.index(STAGE_SRE_TYPES):
        print("Importing types into Ghidra project...")
        result = subprocess.run([
            ghidra_headless,
            args.project_location,
            args.project_name,
            "-scriptPath", PATH_SCRIPT,
            "-postScript", "rec2-ghidra-import-types.py", REC2_ROOT,
            "-process", args.path_exe.name,
            "-noanalysis",
        ])
        if result.returncode != 0:
            print("Failed to import types", file=sys.stderr)
            return 1
        print("Types imported!")

    if stage <= stages.index(STAGE_SRE_SYMBOLS):
        print("Applying symbols to Ghidra project...")
        result = subprocess.run([
            ghidra_headless,
            args.project_location,
            args.project_name,
            "-scriptPath", PATH_SCRIPT,
            "-postScript", "rec2-ghidra-apply-symbols.py", args.ghidra_root, args.symbols,
            "-process", args.path_exe.name,
            "-noanalysis",
        ])
        if result.returncode != 0:
            print("Failed to apply symbols", file=sys.stderr)
            return 1
        print("Symbols applied!")

    if warningHappened:
        print("Warnings treated as error. Exiting.", file=sys.stderr)
        raise SystemExit(1)

    print(f"Ghidra project is ready at {(args.project_location / args.project_name).with_suffix('.gpr') }")

    return 0

if __name__ == "__main__":
    raise SystemExit(main())
