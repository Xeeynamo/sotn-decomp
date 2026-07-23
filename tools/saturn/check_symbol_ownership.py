#!/usr/bin/env python3
"""Validate that Saturn user-symbol files contain only owned VRAM addresses."""

import argparse
import re
import sys
from dataclasses import dataclass
from pathlib import Path


CONFIG_DIR = Path("config/saturn")
DEFAULT_OUTPUT = Path("saturn_symbol_ownership.txt")
TARGET_CONFIGS = {
    "zero": "zero.bin.yaml",
    "game": "game.prg.yaml",
    "richter": "richter.prg.yaml",
    "maria": "maria.prg.yaml",
    "alucard": "alucard.prg.yaml",
    "stage_02": "stage_02.prg.yaml",
    "t_bat": "t_bat.prg.yaml",
    "warp": "warp.prg.yaml",
}
RESIDENT_TARGETS = {"zero", "game"}
OVERLAY_TAIL_ALLOWANCE = 0x100
EXEMPT_RANGES = (
    ("LWRAM", 0x00200000, 0x00300000),
    ("VDP1 RAM", 0x05C00000, 0x05D00000),
    ("VDP2 RAM", 0x05E00000, 0x05F80000),
    ("VDP1 RAM (cache-through)", 0x25C00000, 0x25D00000),
    ("VDP2 RAM (cache-through)", 0x25E00000, 0x25F80000),
)
DEPENDENCIES = {
    "zero": {"game", "richter", "maria", "alucard", "stage_02", "t_bat", "warp"},
    "game": {"richter", "maria", "alucard", "stage_02", "t_bat", "warp"},
    "t_bat": {"alucard"},
}
TARGET_PATH = re.compile(r"^\s*target_path:\s*(\S+)\s*$")
VRAM = re.compile(r"^\s*vram:\s*(0x[0-9A-Fa-f]+)\s*$")
ASSIGNMENT = re.compile(
    r"^\s*([A-Za-z_.$][A-Za-z0-9_.$]*)\s*=\s*"
    r"(0x[0-9A-Fa-f]+)\s*;\s*(?:/\*.*\*/\s*)?$"
)


@dataclass(frozen=True)
class Ownership:
    target: str
    start: int
    end: int
    binary_path: Path


@dataclass(frozen=True)
class Violation:
    path: Path
    line_number: int
    name: str
    address: int
    owner: str | None


@dataclass(frozen=True)
class Exemption:
    path: Path
    line_number: int
    name: str
    address: int
    region: str


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Check that each Saturn *_user_syms.txt assignment falls inside "
            "the VRAM range owned by that target."
        )
    )
    parser.add_argument(
        "-o",
        "--output",
        type=Path,
        default=DEFAULT_OUTPUT,
        help=f"diagnostic report path (default: {DEFAULT_OUTPUT})",
    )
    parser.add_argument(
        "--report-only",
        action="store_true",
        help="return success even when ownership violations are found",
    )
    return parser.parse_args()


def read_layout(target: str, config_name: str) -> tuple[str, int, Path]:
    config_path = CONFIG_DIR / config_name
    target_path = None
    vram = None

    for line in config_path.read_text(encoding="utf-8").splitlines():
        if target_path is None:
            match = TARGET_PATH.match(line)
            if match:
                target_path = Path(match.group(1))
                continue
        if vram is None:
            match = VRAM.match(line)
            if match:
                vram = int(match.group(1), 16)

    if target_path is None or vram is None:
        raise ValueError(f"{config_path}: missing target_path or vram")
    if not target_path.is_file():
        raise ValueError(f"{config_path}: target binary not found: {target_path}")

    return target, vram, target_path


def read_ownership() -> list[Ownership]:
    layouts = [
        read_layout(target, config_name)
        for target, config_name in TARGET_CONFIGS.items()
    ]
    starts = sorted({vram for _, vram, _ in layouts})
    ownership = []

    for target, start, binary_path in layouts:
        end = start + binary_path.stat().st_size
        if target in RESIDENT_TARGETS:
            end = next(candidate for candidate in starts if candidate > start)
        else:
            end += OVERLAY_TAIL_ALLOWANCE
        ownership.append(Ownership(target, start, end, binary_path))

    return ownership


def find_owner(address: int, ownership: list[Ownership]) -> str | None:
    owners = [
        item.target for item in ownership if item.start <= address < item.end
    ]
    if not owners:
        return None
    return "/".join(owners)


def find_exempt_region(address: int) -> str | None:
    for name, start, end in EXEMPT_RANGES:
        if start <= address < end:
            return name
    return None


def find_dependency(
    target: str, address: int, ownership: list[Ownership]
) -> str | None:
    dependencies = DEPENDENCIES.get(target, set())
    matches = [
        item.target
        for item in ownership
        if item.target in dependencies and item.start <= address < item.end
    ]
    if not matches:
        return None
    return "/".join(matches)


def inspect_file(
    path: Path,
    expected: Ownership,
    ownership: list[Ownership],
) -> tuple[int, list[Violation], list[Exemption], list[str]]:
    assignments = 0
    violations = []
    exemptions = []
    syntax_errors = []

    for line_number, line in enumerate(
        path.read_text(encoding="utf-8").splitlines(), start=1
    ):
        stripped = line.strip()
        if not stripped or stripped.startswith(("/*", "*", "//", "#")):
            continue

        match = ASSIGNMENT.match(line)
        if match is None:
            syntax_errors.append(f"{path}:{line_number}: unparsed line: {stripped}")
            continue

        assignments += 1
        name, address_text = match.groups()
        address = int(address_text, 16)
        exempt_region = find_exempt_region(address)
        dependency = find_dependency(expected.target, address, ownership)
        if (
            exempt_region is None
            and not expected.start <= address < expected.end
            and dependency is not None
        ):
            exempt_region = f"dependency on {dependency}"
        if exempt_region is not None:
            exemptions.append(
                Exemption(path, line_number, name, address, exempt_region)
            )
            continue
        if not expected.start <= address < expected.end:
            violations.append(
                Violation(
                    path,
                    line_number,
                    name,
                    address,
                    find_owner(address, ownership),
                )
            )

    return assignments, violations, exemptions, syntax_errors


def build_report(
    ownership: list[Ownership],
    results: list[
        tuple[Ownership, Path, int, list[Violation], list[Exemption]]
    ],
    syntax_errors: list[str],
) -> str:
    violation_count = sum(
        len(violations) for _, _, _, violations, _ in results
    )
    exemption_count = sum(
        len(exemptions) for _, _, _, _, exemptions in results
    )
    lines = [
        "Saturn user-symbol ownership report",
        "===================================",
        "",
        "Owned ranges are half-open: start <= address < end.",
        "Ranges come from each YAML VRAM base. Overlay ends use original binary",
        f"sizes plus a 0x{OVERLAY_TAIL_ALLOWANCE:X}-byte tail allowance; "
        "resident ZERO and GAME",
        "extend to the next module's VRAM base.",
        "LWRAM and VDP1/VDP2 RAM addresses are exempt from ownership checks.",
        "",
        "Ownership ranges",
        "----------------",
    ]

    for item in ownership:
        lines.append(
            f"{item.target:8}  0x{item.start:08X}-0x{item.end:08X}  "
            f"{item.binary_path}"
        )

    lines.extend(
        [
            "",
            "Summary",
            "-------",
        ]
    )
    for expected, path, assignments, violations, exemptions in results:
        lines.append(
            f"{path}: owner={expected.target}, assignments={assignments}, "
            f"violations={len(violations)}, exemptions={len(exemptions)}"
        )

    lines.extend(
        [
            "",
            f"Total ownership violations: {violation_count}",
            f"Exempt dependency/hardware assignments: {exemption_count}",
            f"Unparsed non-comment lines: {len(syntax_errors)}",
            "",
            "Violations",
            "----------",
        ]
    )

    if violation_count == 0:
        lines.append("(none)")
    else:
        for expected, path, _, violations, _ in results:
            if not violations:
                continue
            lines.extend(["", f"[{path} expects {expected.target}]"])
            for violation in violations:
                actual_owner = violation.owner or "unowned/external"
                lines.append(
                    f"{violation.path}:{violation.line_number}: "
                    f"{violation.name} = 0x{violation.address:08X}; "
                    f"belongs_to={actual_owner}"
                )

    lines.extend(["", "Exemptions", "----------"])
    if exemption_count == 0:
        lines.append("(none)")
    else:
        for _, _, _, _, exemptions in results:
            for exemption in exemptions:
                lines.append(
                    f"{exemption.path}:{exemption.line_number}: "
                    f"{exemption.name} = 0x{exemption.address:08X}; "
                    f"region={exemption.region}"
                )

    lines.extend(["", "Unparsed lines", "--------------"])
    lines.extend(syntax_errors or ["(none)"])
    lines.append("")
    return "\n".join(lines)


def main() -> int:
    args = parse_args()
    try:
        ownership = read_ownership()
        ownership_by_target = {item.target: item for item in ownership}
        results = []
        syntax_errors = []

        for target in TARGET_CONFIGS:
            path = CONFIG_DIR / f"{target}_user_syms.txt"
            assignments, violations, exemptions, file_syntax_errors = inspect_file(
                path, ownership_by_target[target], ownership
            )
            results.append(
                (
                    ownership_by_target[target],
                    path,
                    assignments,
                    violations,
                    exemptions,
                )
            )
            syntax_errors.extend(file_syntax_errors)

        report = build_report(ownership, results, syntax_errors)
        args.output.write_text(report, encoding="utf-8")
    except (OSError, ValueError) as error:
        print(f"error: {error}", file=sys.stderr)
        return 2

    violation_count = sum(
        len(violations) for _, _, _, violations, _ in results
    )
    print(
        f"Wrote {args.output}: {violation_count} ownership violations, "
        f"{len(syntax_errors)} unparsed lines"
    )
    if args.report_only:
        return 0
    return 1 if violation_count or syntax_errors else 0


if __name__ == "__main__":
    raise SystemExit(main())
