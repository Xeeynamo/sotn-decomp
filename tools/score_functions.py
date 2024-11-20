#!/usr/bin/env python3
"""
Score assembly functions by complexity and find the simplest one to decompile.

Usage:
    python3 tools/score_functions.py <folder_path>
    python3 tools/score_functions.py asm/nonmatchings/displaylist
    python3 tools/score_functions.py --exhaustive asm/
    python3 tools/score_functions.py --score-func func_800B6544_1E35F4 asm/
    python3 tools/score_functions.py --min-score 100 --max-score 200 asm/
"""

import sys
import os
import re
import argparse
import numpy as np
from pathlib import Path
from dataclasses import dataclass
from typing import List, Tuple


def decompilation_difficulty_score(instructions, branches, jumps, labels):
    # Standardization parameters (from training)
    means = np.array(
        [
            np.float64(34.27065527065527),
            np.float64(1.6666666666666667),
            np.float64(3.1880341880341883),
            np.float64(1.98005698005698),
        ]
    )
    stds = np.array(
        [
            np.float64(24.763225638334454),
            np.float64(2.047860394102145),
            np.float64(3.200600790997309),
            np.float64(2.3803926026229827),
        ]
    )

    # Model coefficients
    coefficients = np.array(
        [
            np.float64(2.499706543629367),
            np.float64(-0.46648920346754463),
            np.float64(-1.61606926820365),
            np.float64(0.4911494991317799),
        ]
    )
    intercept = -0.5155412977000488

    # Calculate score
    features = np.array([instructions, branches, jumps, labels])
    features_scaled = (features - means) / stds
    logit = np.dot(features_scaled, coefficients) + intercept
    difficulty = 1 / (1 + np.exp(-logit))

    return difficulty


@dataclass
class FunctionScore:
    """Stores complexity metrics for a function."""

    name: str
    file_path: str
    instruction_count: int = 0
    branch_count: int = 0
    jump_count: int = 0
    label_count: int = 0
    stack_size: int = 0

    @property
    def total_score(self) -> float:
        """Calculate decompilation difficulty score using ML model (0=easy, 1=hard)."""
        return decompilation_difficulty_score(
            self.instruction_count, self.branch_count, self.jump_count, self.label_count
        )

    def __str__(self) -> str:
        return (
            f"{self.name:50s} | Difficulty: {self.total_score:5.3f} | "
            f"Instructions: {self.instruction_count:3d} | "
            f"Branches: {self.branch_count:2d} | "
            f"Jumps: {self.jump_count:2d} | "
            f"Labels: {self.label_count:2d} | "
            f"Stack: {self.stack_size:4d}"
        )

    def to_simple_format(self) -> str:
        """Return a simple parseable format without column names."""
        return (
            f"{self.name} | {self.total_score:.3f} | "
            f"{self.instruction_count} | {self.branch_count} | "
            f"{self.jump_count} | {self.label_count} | {self.stack_size}"
        )


def parse_multi_function_file(file_path: str) -> List[FunctionScore]:
    """Parse a file containing multiple functions and return a list of scores."""
    scores = []

    try:
        with open(file_path, "r") as f:
            content = f.read()

        # Find all function blocks using glabel/endlabel markers
        # Pattern: glabel <function_name> ... endlabel <function_name>
        glabel_pattern = r"glabel\s+(\S+)"

        # Find all glabel occurrences
        glabels = list(re.finditer(glabel_pattern, content))

        if len(glabels) == 0:
            # No glabels found, use standard analysis (extracts name from filename)
            score = analyze_function(file_path)
            return [score] if score is not None else []

        # One or more functions found - parse each one
        for i, match in enumerate(glabels):
            func_name = match.group(1)
            start_pos = match.start()

            # Find the end of this function (next glabel or end of file)
            if i + 1 < len(glabels):
                end_pos = glabels[i + 1].start()
            else:
                end_pos = len(content)

            # Extract function content
            func_content = content[start_pos:end_pos]

            # Analyze this function
            score = analyze_function_content(func_name, func_content, file_path)
            if score is not None:
                scores.append(score)

    except Exception as e:
        print(f"Error parsing multi-function file {file_path}: {e}", file=sys.stderr)

    return scores


def analyze_function_content(
    func_name: str, content: str, file_path: str
) -> FunctionScore:
    """Analyze function content and return complexity metrics."""

    # Branch instructions (conditional)
    branch_patterns = [
        r"\b(beq|bne|bnez|beqz|blez|bgtz|bltz|bgez|blt|bgt|ble|bge|bltzal|bgezal)\b"
    ]

    # Jump instructions
    jump_patterns = [
        r"\bjal\b",  # Function calls
        r"\bj\b",  # Unconditional jumps (not jr - that's return)
    ]

    # Local label pattern (e.g., .L800095A8_A1A8:)
    label_pattern = r"^\s*\.L[0-9A-Fa-f_]+:"

    # Instruction pattern (lines with actual assembly)
    instruction_pattern = r"/\*\s*[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s*\*/"

    # Stack allocation pattern (addiu $sp, $sp, -0xNN)
    stack_pattern = r"addiu\s+\$sp,\s*\$sp,\s*-0x([0-9A-Fa-f]+)"

    # Jump table pattern (e.g., jtbl_8009E1D8_9EDD8)
    jumptable_pattern = r"^jtbl_[0-9A-Fa-f_]+$"

    # Data pattern (e.g., D_8009E48C_9F08C)
    data_pattern = r"^D_[0-9A-Fa-f_]+$"

    # Skip non-code sections (data, bss, rodata, header)
    # These typically have .data, .bss, .rodata suffixes or are named "header"
    if (
        re.match(jumptable_pattern, func_name)
        or re.match(data_pattern, func_name)
        or func_name.endswith(".data")
        or func_name.endswith(".bss")
        or func_name.endswith(".rodata")
        or func_name == "header"
    ):
        return None

    # Skip files that only contain rodata (no actual code)
    if ".section .rodata" in content and "glabel" not in content:
        return None

    score = FunctionScore(name=func_name, file_path=file_path)

    for line in content.split("\n"):
        line = line.strip()

        # Skip empty lines, glabel, endlabel, and comments
        if (
            not line
            or line.startswith("glabel")
            or line.startswith("endlabel")
            or line.startswith("nonmatching")
        ):
            continue

        # Count local labels
        if re.match(label_pattern, line):
            score.label_count += 1
            continue

        # Count instructions
        if re.search(instruction_pattern, line):
            score.instruction_count += 1

            # Check for branches
            for pattern in branch_patterns:
                if re.search(pattern, line):
                    score.branch_count += 1
                    break

            # Check for jumps
            for pattern in jump_patterns:
                if re.search(pattern, line):
                    score.jump_count += 1
                    break

            # Check for stack allocation
            stack_match = re.search(stack_pattern, line)
            if stack_match:
                score.stack_size = int(stack_match.group(1), 16)

    return score


def analyze_function(file_path: str) -> FunctionScore:
    """Analyze an assembly file and return complexity metrics."""

    # Branch instructions (conditional)
    branch_patterns = [
        r"\b(beq|bne|bnez|beqz|blez|bgtz|bltz|bgez|blt|bgt|ble|bge|bltzal|bgezal)\b"
    ]

    # Jump instructions
    jump_patterns = [
        r"\bjal\b",  # Function calls
        r"\bj\b",  # Unconditional jumps (not jr - that's return)
    ]

    # Local label pattern (e.g., .L800095A8_A1A8:)
    label_pattern = r"^\s*\.L[0-9A-Fa-f_]+:"

    # Instruction pattern (lines with actual assembly)
    instruction_pattern = r"/\*\s*[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s+\*/"

    # Stack allocation pattern (addiu $sp, $sp, -0xNN)
    stack_pattern = r"addiu\s+\$sp,\s*\$sp,\s*-0x([0-9A-Fa-f]+)"

    # Extract function name from file
    filename = os.path.basename(file_path)
    func_name = filename.replace(".s", "")

    # Jump table pattern (e.g., jtbl_8009E1D8_9EDD8)
    jumptable_pattern = r"^jtbl_[0-9A-Fa-f_]+$"

    # Data pattern (e.g., D_8009E48C_9F08C)
    data_pattern = r"^D_[0-9A-Fa-f_]+$"

    # Skip non-code sections (data, bss, rodata, header)
    # These typically have .data, .bss, .rodata suffixes or are named "header"
    if (
        re.match(jumptable_pattern, func_name)
        or re.match(data_pattern, func_name)
        or func_name.endswith(".data")
        or func_name.endswith(".bss")
        or func_name.endswith(".rodata")
        or func_name == "header"
    ):
        return None

    score = FunctionScore(name=func_name, file_path=file_path)

    try:
        with open(file_path, "r") as f:
            content = f.read()

            # Skip files that only contain rodata (no actual code)
            if ".section .rodata" in content and "glabel" not in content:
                return None

            for line in content.splitlines():
                line = line.strip()

                # Skip empty lines, glabel, endlabel, and comments
                if (
                    not line
                    or line.startswith("glabel")
                    or line.startswith("endlabel")
                    or line.startswith("nonmatching")
                ):
                    continue

                # Count local labels
                if re.match(label_pattern, line):
                    score.label_count += 1
                    continue

                # Count instructions
                if re.search(instruction_pattern, line):
                    score.instruction_count += 1

                    # Check for branches
                    for pattern in branch_patterns:
                        if re.search(pattern, line):
                            score.branch_count += 1
                            break

                    # Check for jumps
                    for pattern in jump_patterns:
                        if re.search(pattern, line):
                            score.jump_count += 1
                            break

                    # Check for stack allocation
                    stack_match = re.search(stack_pattern, line)
                    if stack_match:
                        score.stack_size = int(stack_match.group(1), 16)

    except Exception as e:
        print(f"Error analyzing {file_path}: {e}", file=sys.stderr)

    return score


def score_folder(folder_path: str, exhaustive: bool = False) -> List[FunctionScore]:
    """Score all assembly functions in a folder and its subdirectories.

    Args:
        folder_path: Path to the folder to scan
        exhaustive: If True, parse multi-function .s files individually
    """

    if not os.path.isdir(folder_path):
        print(f"Error: '{folder_path}' is not a valid directory", file=sys.stderr)
        sys.exit(1)

    # Find all .s files recursively
    asm_files = list(Path(folder_path).glob("**/*.s"))

    if not asm_files:
        print(f"Error: No .s files found in '{folder_path}'", file=sys.stderr)
        sys.exit(1)

    # Score each function
    scores = []
    for asm_file in asm_files:
        if exhaustive:
            # Parse multi-function files
            file_scores = parse_multi_function_file(str(asm_file))
            scores.extend(file_scores)
        else:
            # Original behavior - one function per file
            score = analyze_function(str(asm_file))
            if score is not None:  # Skip jump tables
                scores.append(score)

    # Sort by complexity (lowest first)
    scores.sort(key=lambda s: s.total_score)

    return scores


def load_difficult_functions(difficult_file: str) -> set:
    """Load the list of difficult functions to exclude."""
    difficult_functions = set()

    if os.path.exists(difficult_file):
        try:
            with open(difficult_file, "r") as f:
                for line in f:
                    line = line.strip()
                    if line:  # Skip empty lines
                        # Extract only the first value (function name)
                        # Some lines may have additional data like attempt counts
                        func_name = line.split()[0]
                        difficult_functions.add(func_name)
        except Exception as e:
            print(f"Warning: Could not read {difficult_file}: {e}", file=sys.stderr)

    return difficult_functions


def main():
    parser = argparse.ArgumentParser(
        description="Score assembly functions by complexity and find the simplest one to decompile.",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  python3 tools/score_functions.py asm/nonmatchings/displaylist
  python3 tools/score_functions.py --exhaustive asm/
  python3 tools/score_functions.py --score-func func_800B6544_1E35F4 asm/
  python3 tools/score_functions.py --min-score 100 --max-score 200 asm/
  python3 tools/score_functions.py --exhaustive --min-score 50 asm/
        """,
    )
    parser.add_argument(
        "folder_path", help="Path to folder containing .s assembly files"
    )
    parser.add_argument(
        "--exhaustive",
        action="store_true",
        help="Parse multi-function .s files (e.g., asm/1DCF60.s) and score each function individually. Ignores difficult_functions file.",
    )
    parser.add_argument(
        "--score-func",
        metavar="FUNCTION_NAME",
        help="Search for and score a specific function by name (e.g., func_800B6544_1E35F4)",
    )
    parser.add_argument(
        "--min-score",
        type=float,
        metavar="MIN",
        help="Only show functions with complexity score >= MIN",
    )
    parser.add_argument(
        "--max-score",
        type=float,
        metavar="MAX",
        help="Only show functions with complexity score <= MAX",
    )

    args = parser.parse_args()

    # If --score-func is specified, search for that specific function
    if args.score_func:
        scores = score_folder(
            args.folder_path, exhaustive=True
        )  # Always use exhaustive mode for specific function search

        # Find the matching function
        matching_scores = [s for s in scores if s.name == args.score_func]

        if not matching_scores:
            print(
                f"Error: Function '{args.score_func}' not found in '{args.folder_path}'",
                file=sys.stderr,
            )
            sys.exit(1)

        if len(matching_scores) > 1:
            print(
                f"Warning: Found {len(matching_scores)} occurrences of '{args.score_func}'",
                file=sys.stderr,
            )
            sys.exit(1)

        print(matching_scores[0].total_score)

        sys.exit(0)

    scores = score_folder(args.folder_path, exhaustive=args.exhaustive)

    # Load difficult functions to exclude (only in non-exhaustive mode)
    difficult_functions = set()
    if not args.exhaustive:
        script_dir = os.path.dirname(os.path.abspath(__file__))
        difficult_file = os.path.join(script_dir, "difficult_functions")
        difficult_functions = load_difficult_functions(difficult_file)

        # Only print exclusion message in verbose modes
        if difficult_functions and (
            args.exhaustive or args.min_score is not None or args.max_score is not None
        ):
            print(f"Excluding {len(difficult_functions)} difficult function(s)\n")

    # Filter out difficult functions and data sections (functions with 0 instructions)
    filtered_scores = [
        s
        for s in scores
        if s.name not in difficult_functions and s.instruction_count > 0
    ]

    # Apply score range filters if specified
    if args.min_score is not None:
        filtered_scores = [
            s for s in filtered_scores if s.total_score >= args.min_score
        ]
    if args.max_score is not None:
        filtered_scores = [
            s for s in filtered_scores if s.total_score <= args.max_score
        ]

    if not filtered_scores:
        print(
            "Error: All functions are marked as difficult or are data sections!",
            file=sys.stderr,
        )
        sys.exit(1)

    # In exhaustive mode, list all functions
    if args.exhaustive:
        print("ALL FUNCTIONS (sorted by complexity):\n")
        for score in filtered_scores:
            print(score.to_simple_format())
        print(f"\n{'='*80}\n")

    simplest = filtered_scores[0]

    # Simple mode: just print the function name if no special flags
    if not args.exhaustive and args.min_score is None and args.max_score is None:
        print(simplest.name)
    else:
        print(f"SIMPLEST FUNCTION: {simplest.name}")
        print(f"{simplest}")


if __name__ == "__main__":
    main()
