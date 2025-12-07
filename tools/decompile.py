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
import tempfile
import requests
import m2ctx
import m2c.m2c.main as m2c
from contextlib import redirect_stdout
from pathlib import Path
from typing import Optional


class SotnFunction(object):
    """A representation of a function within sotn-decomp, including paths and code associated with the function"""

    def __init__(self, func_root: Path, function_path: Path, args: argparse.Namespace):
        self.name: str = args.function
        self.version: str = args.version
        self._overlay: str = args.overlay

        # These directories/paths should be considered to be specific to the function
        self.root: Path = func_root
        self.asm_dir: Path = func_root.joinpath("asm", args.version)
        self.src_dir: Path = func_root.joinpath(
            "src", "saturn" if args.version == "saturn" else ""
        )
        self.abspath: Path = function_path.resolve()
        self.relpath: Path = function_path.relative_to(func_root)
        self.src_path: Path = self._infer_src_path()
        if args.version == "saturn":
            self.include_asm: str = (
                f'INCLUDE_ASM("{self.abspath.relative_to(self.root).parent}", {self.relpath.stem}, {self.name});'
            )
        else:
            self.include_asm: str = (
                f'INCLUDE_ASM("{self.abspath.relative_to(self.asm_dir).parent}", {self.relpath.stem});'
            )
        self.asm_code: str = self.abspath.read_text()
        self.c_code: str = ""
        self._context: str = ""

    @property
    def overlay(self) -> str:
        """Attempts to infer the overlay from the asm file path or returns None if one is not found.
        The '_psp' extension will be included if the version is psp because this value is later used
        for identifying the correct overlay asm path"""
        nonmatchings_dir = "f_nonmat" if args.version == "saturn" else "nonmatchings"
        if not self._overlay:
            nonmatching_index = next(
                (
                    i
                    for i, part in enumerate(self.relpath.parts)
                    if part == nonmatchings_dir
                ),
                None,
            )
            self._overlay = (
                self.relpath.parts[nonmatching_index - 1] if nonmatching_index else None
            )
        return self._overlay

    @property
    def asm_differ_command(self) -> str:
        """Constructs the command string the user can enter to run asm-differ against the overlay this function resides in"""
        return f"{Path(sys.executable).name} {self.root.joinpath("tools/asm-differ/diff.py").relative_to(Path.cwd())} -mwo --overlay {self.overlay.replace("_psp", "")} {self.name}"

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
        if self.version != "saturn" and not self.c_code:
            self.c_code = self._guess_unknown_type(self._run_m2c())
        return self.c_code

    def upload_to_decompme(self) -> None:
        """Uploads the decompiled code to decomp.me using the extracted context and SotN decomp.me presets"""
        print("Loading up the catapult...")
        # No current expectation of these changing, so hardcoding instead of retrieving them from the API programmatically is probably fine
        # The preset id's can be found at https://www.decomp.me/api/compilers, searching the page for Castlevania: Symphony of the Night
        preset = (
            21 if self.version == "saturn" else 132 if "psp" in self.version else 14
        )  # 14 is ps1 preset
        payload = {
            "name": self.name,
            "target_asm": self.asm_code,
            "context": self.context,
            "preset": preset,
            "diff_label": self.name,
        }
        if self.decompile():
            payload["source_code"] = self.decompile()

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
                print(
                    "If this function had been previously decompiled, the decompiled code may need to be moved manually from the context tab to the source tab in decomp.me"
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
        inferred_c_name = f"{self.abspath.parent.parent.name if self.version == "saturn" else self.abspath.parent.name}.c"
        inferred_c_files = (
            file
            for file in self.src_dir.rglob(inferred_c_name)
            if self.overlay in file.parts or self.overlay in file.name
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


def get_function_path(asm_dir: Path, args: argparse.Namespace) -> Optional[Path]:
    """Uses the version asm directory and the passed args to find any files matching the function name."""
    file_name = f"{args.function.replace("func_0", "f") if args.version == "saturn" else args.function}.s"
    matchings_dir = "f_match" if args.version == "saturn" else "matchings"
    nonmatchings_dir = "f_nonmat" if args.version == "saturn" else "nonmatchings"

    candidates = tuple(file for file in asm_dir.rglob(file_name))
    matching = tuple(c for c in candidates if matchings_dir in c.parts)
    nonmatching = tuple(
        c
        for c in candidates
        if nonmatchings_dir in c.parts and (not args.overlay or args.overlay in c.parts)
    )

    if not matching and not nonmatching:
        print(
            f"Could not find function {args.function}, are you sure it exists in version {args.version}?"
        )
        return None
    elif matching and not nonmatching:
        print(
            f"It appears that {args.function} has already been decompiled and matched."
        )
        return None

    if len(nonmatching) > 1:
        message = f"{len(nonmatching)} possible files found for {args.function} in the following locations:\n"
        message += f"{"\n".join(f"\t{path.relative_to(asm_dir.parent)}" for path in nonmatching)}"
        message += "Invoke this tool again using the -o/--overlay argument to specify the appropriate overlay."
        print(message)
        return None
    else:
        return nonmatching[0]


def safe_write(file_path: Path, lines: list[str]) -> None:
    """Writes to a temp file, then replaces the original file after the temp file is successfully written"""
    # Since we are using os.replace, the temp file needs to be on the same filesystem as the original.
    with tempfile.NamedTemporaryFile(
        mode="w", encoding="utf-8", dir=file_path.parent
    ) as temp_file:
        temp_file.writelines([l.rstrip("\n") + "\n" for l in lines])
        temp_file.flush()
        os.replace(temp_file.name, file_path)


def inject_decompiled_function(repo_root: Path, sotn_func: SotnFunction) -> None:
    """Replaces the INCLUDE_ASM macro line with the decompiled code, writes it, then returns a status based on the results"""
    lines = sotn_func.src_path.read_text().splitlines()

    # This should be removed when the remaining 4 functions in mad are decompiled
    sotn_func.include_asm = sotn_func.include_asm.replace("st/mad", "asm/us/st/mad")

    if sotn_func.include_asm in lines:
        function_index = lines.index(sotn_func.include_asm)

        # Using copy() so that the lines object is not modified when new_lines is
        new_lines = lines.copy()
        new_lines[function_index] = sotn_func.decompile()
        safe_write(sotn_func.src_path, new_lines)

        print(
            f"{sotn_func.name} was successfully decompiled in {src}, but likely will not compile without adjustments."
        )
    elif [line for line in lines if sotn_func.name in line]:
        print(
            f"{sotn_func.name} seems to have already been decompiled in {sotn_func.src_path.relative_to(repo_root)}"
        )
    else:
        print(
            f"Could not find function {args.function}, are you sure it exists in version {args.version}?"
        )


def main(args: argparse.Namespace) -> None:
    """Executes the decompilation workflow and gives console feedback based on the results"""
    if args.version == "saturn":
        message = f"Local decompilation of saturn overlays is not currently supported"
        if args.upload:
            message += ", the function will only be uploaded to decomp.me"
        else:
            message += ", invoke the tool again with the -u/--upload option"
        print(message)

    repo_root = get_repo_root()
    function_path = get_function_path(repo_root.joinpath("asm", args.version), args)

    if function_path:
        sotn_func = SotnFunction(repo_root, function_path, args)
        if sotn_func.src_path and sotn_func.decompile():
            inject_decompiled_function(repo_root, sotn_func)

        if args.upload:
            sotn_func.upload_to_decompme()


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

    args = parser.parse_args()

    main(args)
