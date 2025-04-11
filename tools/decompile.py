#!/usr/bin/env python3
"""This script is intended to make it easier for someone to decompile a function within the sotn-decomp project
and optionally upload that function to decomp.me.
Any questions or issues related to running it should be directed to the sotn-decomp discord #tooling channel:
https://sotn-discord.xee.dev/

Use `decompile.py --help` for usage and options"""

import argparse
import io
import os
import sys
import subprocess
import tempfile
import requests
import re
import m2ctx
import m2c.m2c.main as m2c
from contextlib import redirect_stdout
from pathlib import Path
from enum import Enum
from typing import Optional


class Status(Enum):
    NOT_FOUND = 1
    AMBIGUOUS_FUNC = 2
    ALREADY_DECOMPILED = 3
    ALREADY_MATCHED = 4
    DOES_NOT_COMPILE = 5
    NON_MATCHING = 6
    MATCHING = 7
    UNHANDLED_ERROR = -1


class SotnFunction(object):
    """A representation of a function within sotn-decomp, including paths and code associated with the function"""

    def __init__(self, func_root: Path, function_path: Path, args: argparse.Namespace):
        self.name: str = function_path.stem
        self.version: str = args.version
        self._overlay: str = args.overlay

        # These directories/paths should be considered to be specific to the function
        self.root: Path = func_root
        self.asm_dir: Path = func_root.joinpath("asm", args.version)
        self.src_dir: Path = func_root.joinpath("src")
        self.abspath: Path = function_path.resolve()
        self.relpath: Path = function_path.relative_to(func_root)
        self.src_path: Path = self._infer_src_path()
        self.include_asm: str = (
            f'INCLUDE_ASM("{self.abspath.relative_to(self.asm_dir).parent}", {self.relpath.stem});'
        )
        self.asm_code: str = self.abspath.read_text()
        self.c_code: str = ""
        self._context: str = ""

    @property
    def overlay(self) -> str:
        """Attempts to infer the overlay from the asm file path or returns None if one is not found"""
        if not self._overlay:
            nonmatching_index = next(
                (
                    i
                    for i, part in enumerate(self.relpath.parts)
                    if part == "nonmatchings" or part == "psp"
                ),
                None,
            )
            self._overlay = (
                self.relpath.parts[nonmatching_index - 1] if nonmatching_index else None
            )
        return self._overlay

    @property
    def asm_differ_command(self) -> str:
        """Constructs the string to run asm-differ if the decompiled function code can be compiled"""
        return f"{Path(sys.executable).name} {self.root.joinpath("tools/asm-differ/diff.py").relative_to(Path.cwd())} -mwo --overlay {self.overlay} {self.name}"

    @property
    def context(self):
        """Leverages m2ctx to create context text"""
        if not self._context:
            m2ctx.root_dir = self.root
            m2ctx.VERSION_DEF = [f"-D_internal_version_{self.version}"]
            self._context = m2ctx.import_c_file(self.src_path)
        return self._context

    def decompile(self) -> str:
        """Leverages m2c to decompile the function and stores it so that decompilation only needs to run once"""
        if not self.c_code:
            self.c_code = self._guess_unknown_type(self._run_m2c())
        return self.c_code

    def upload_to_decompme(self) -> None:
        """Uploads the decompiled code to decomp.me using the extracted context and SotN decomp.me presets"""
        print("Loading up the catapult...")
        # No current expectation of these changing, so hardcoding is probably fine
        presets = {"us": 14, "pspeu": 132}
        payload = {
            "name": self.name,
            "target_asm": self.asm_code,
            "context": self.context,
            "source_code": self.decompile(),
            "preset": presets[self.version],
            "diff_label": self.name,
        }

        try:
            print("Launching cow...")
            response = requests.post("https://decomp.me/api/scratch", data=payload)
            response_json = response.json()
            if "slug" in response_json:
                self.scratch_link = (
                    f"https://decomp.me/scratch/{response_json["slug"]}/"
                )
                claim_token = response_json.get("claim_token")
                if claim_token:
                    self.scratch_link += f"claim?token={claim_token}"
                print(
                    f"{self.name} successfully uploaded to decomp.me and can be {"claimed" if "claim" in self.scratch_link else "accessed"} at {self.scratch_link}"
                )
            else:
                print(
                    f"Received an error when attempting to upload to decomp.me: {response_json.get("error", response.text)}"
                )
        except Exception as e:
            print(
                f"An unhandled error occurred while attempting to upload to decomp.me: {e}"
            )


    def _run_m2c(self) -> str:
        with tempfile.NamedTemporaryFile(
            mode="w", encoding="utf-8", suffix=".c"
        ) as tmp_ctx:
            tmp_ctx.writelines(self.context)
            tmp_ctx.flush()
            options = m2c.parse_flags(
                [
                    "-P",
                    "4",
                    "--pointer-style",
                    "left",
                    "--knr",
                    "--indent-switch-contents",
                    "--comment-style",
                    "oneline",
                    "--target",
                    "mipsel-gcc-c",
                    "--context",
                    tmp_ctx.name,
                    str(self.abspath),
                ]
            )

            with redirect_stdout(io.StringIO()) as f:
                m2c.run(options)
                return f.getvalue()

    def _guess_unknown_type(self, decompiled_code: str) -> str:
        return (
            decompiled_code.replace("? func_", "/*?*/ void func_")
            .replace("extern ? D_", "extern /*?*/s32 D_")
            .replace("extern ?* D_", "extern /*?*/u8* D_")
        )

    def _infer_src_path(self) -> Optional[Path]:
        inferred_c_files = (
            file
            for file in self.root.joinpath("src").rglob(f"{self.abspath.parent.name}.c")
            if self.overlay in file.parts
        )
        return next(
            (path for path in inferred_c_files if self.name in path.read_text()), None
        )


def get_repo_root(current_dir: Path = Path(__file__).resolve().parent) -> Path:
    """Steps backward from the file location to infer the root of the repo"""
    if next(current_dir.glob("src"), None) or current_dir.name == "/":
        return current_dir
    else:
        return get_repo_root(current_dir.parent)


def get_function_path(
    asm_dir: Path, args: argparse.Namespace
) -> tuple[Optional[Status], Optional[tuple[Path]]]:
    """Uses the repo asm directory and the passed args to find any files matching the function name.
    Always orders the return values with all files for for the specified version, followed by any files found for the
    unspecified version(s) and returning a not found status if no files are found for the specified version.
    """
    candidates = tuple(file for file in asm_dir.rglob(f"{args.function}.s"))
    matching = tuple(c for c in candidates if "matchings" in c.parts)
    nonmatching = tuple(
        c for c in candidates if "nonmatchings" in c.parts or "psp" in c.parts
    )

    function = tuple(
        file
        for file in nonmatching
        if args.version in file.parts
        and (not args.overlay or args.overlay in file.parts)
    )
    siblings = tuple(file for file in nonmatching if not args.version in file.parts)

    if not matching and not function:
        return Status.NOT_FOUND, None
    elif matching and not function:
        return Status.ALREADY_MATCHED, None

    status = Status.AMBIGUOUS_FUNC if len(function) > 1 else None
    return status, function + siblings


def safe_write(file_path: Path, lines: list[str]) -> None:
    """Writes to a temp file, then replaces the original file after the temp file is successfully written"""
    # Since we are using os.replace, the temp file needs to be on the same filesystem as the original.
    with tempfile.NamedTemporaryFile(
        mode="w", encoding="utf-8", dir=file_path.parent
    ) as temp_file:
        temp_file.writelines([l.rstrip("\n") + "\n" for l in lines])
        temp_file.flush()
        os.replace(temp_file.name, file_path)


def inject_decompiled_function(repo_root: Path, sotn_func: SotnFunction) -> Status:
    """Replaces the INCLUDE_ASM macro line with the decompiled code, writes it, then returns a status based on the results"""
    lines = sotn_func.src_path.read_text().splitlines()

    if f"{sotn_func.include_asm}" in lines:
        function_index = lines.index(f"{sotn_func.include_asm}")

        # Using copy() so that the lines object is not modified when new_lines is
        new_lines = lines.copy()
        new_lines[function_index] = sotn_func.decompile()
        safe_write(sotn_func.src_path, new_lines)

        compile_result = check_injected_code(repo_root, sotn_func)
        if compile_result == Status.NON_MATCHING:
            new_lines[function_index] = (
                f"#ifndef NON_MATCHING\n{sotn_func.include_asm}\n#else\n{sotn_func.decompile()}\n#endif"
            )
            safe_write(sotn_func.src_path, new_lines)

        return compile_result
    elif [line for line in lines if sotn_func.name in line]:
        return Status.ALREADY_DECOMPILED
    else:
        return Status.NOT_FOUND


# check if the overlay can be compiled
def check_injected_code(repo_root: Path, sotn_func: SotnFunction) -> Status:
    """Uses the make build pipeline to check the decompiled code and return the relevant status"""
    compile_result = subprocess.run(
        f"make -j {sotn_func.overlay}",
        cwd=repo_root,
        shell=True,
        check=False,
        capture_output=True,
    )
    if compile_result.returncode == 0:
        check_result = subprocess.run(
            "make check", cwd=repo_root, shell=True, check=False, capture_output=True
        )
        return Status.MATCHING if check_result.returncode == 0 else Status.NON_MATCHING
    else:
        return Status.DOES_NOT_COMPILE


def main(args: argparse.Namespace) -> None:
    """Executes the decompilation workflow and gives console feedback based on the results"""
    if args.version != "us":
        sys.exit(
            f"Please specify a different version, {args.version} is not yet implemented"
        )
    if args.find_siblings:
        print(
            "Warning: the -s/--find-siblings option is not yet fully implemented and is ignored"
        )
        args.find_siblings = False

    repo_root = get_repo_root()
    status, function_paths = get_function_path(repo_root.joinpath("asm"), args)

    if not status:
        # We know that if there is no status yet, then function_paths exists and index 0 is the only function matching args.version
        sotn_func = SotnFunction(repo_root, function_paths[0], args)
        if sotn_func.src_path:
            status = inject_decompiled_function(repo_root, sotn_func)

        if args.upload:
            sotn_func.upload_to_decompme()

    match status:
        case Status.NOT_FOUND:
            message = f"Could not find function {args.function}, are you sure it exists in version {args.version}?"
        case Status.ALREADY_MATCHED:
            message = f"It appears that {args.function} has already been decompiled and matched."
        case Status.MATCHING:
            message = f"{sotn_func.name} was successfully decompiled and matches!"
        case Status.NON_MATCHING:
            message = f"{sotn_func.name} was successfully decompiled and can be recompiled, but the resulting binary does not match.\n"
            message += f"The following command can be used to look for the differences:\n\t{sotn_func.asm_differ_command}"
        case Status.DOES_NOT_COMPILE:
            message = f"{sotn_func.name} has been decompiled in {(sotn_func.src_path.relative_to(repo_root))} but contains errors that must be resolved before it can be compiled."
        case Status.ALREADY_DECOMPILED:
            message = f"{sotn_func.name} seems to have already been decompiled in {(sotn_func.src_path.relative_to(repo_root))}"
            if args.upload:
                message += " so the existing decompiled code must be moved manually from the context tab to the source tab in decomp.me"
        case Status.AMBIGUOUS_FUNC:
            message = f"{len(function_paths)} possible files found for {args.function} in the following locations:\n"
            message += f"{"".join(f"\t{path}\n" for path in function_paths if args.version in path.parts)}"
            message += "Invoke this tool again using the -o/--overlay argument to specify the appropriate overlay."
        case Status.UNHANDLED_ERROR | _:
            message = f"The script encountered an unhandled error, please report this in the SOTN Decomp discord #tooling channel: https://sotn-discord.xee.dev/\n"
            message += "Copy and paste the following block, including the ```:\n"
            message += f"\t```{sotn_func.version = } {sotn_func.overlay = } {sotn_func.name = }\n"
            message += f"\t{sotn_func.abspath = }\n"
            message += f"\t{sotn_func.src_path = }```"

    print(message)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Decompile a function locally or upload to decomp.me"
    )
    parser.add_argument("function", help="The name of the function to decompile")
    parser.add_argument(
        "-v",
        "--version",
        required=False,
        type=str,
        default=os.getenv("VERSION") or "us",
        help="Sets the target game version and overrides VERSION environment variable",
    )
    parser.add_argument(
        "-o",
        "--overlay",
        help="The overlay to use if there are multiple asm files that match the provided function name",
        type=str,
        required=False,
    )
    parser.add_argument(
        "-u",
        "--upload",
        help="Upload the function to decomp.me after decompilation",
        action="store_true",
        required=False,
    )
    parser.add_argument(
        "-s",
        "--find-siblings",
        help="Look for the function in all game versions (not yet implemented)",
        action="store_true",
        required=False,
    )

    args = parser.parse_args()

    main(args)
