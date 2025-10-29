#!/usr/bin/env python3
import re
import sys
import subprocess


def transform_arg(arg: str) -> str:
    if arg == "0":
        return "[0:1]"
    elif arg == "1":
        return "[-1:1]"
    else:
        return arg


def patch(line: str) -> str:
    match = re.match(
        r"^(.*/\*\s*[0-9A-Fa-fX]+\s+[0-9A-Fa-fX]+\s+)([0-9A-Fa-f]{2})([0-9A-Fa-f]{2})([0-9A-Fa-f]{2})([0-9A-Fa-f]{2})(\s+\*/.*?)(vrot|lv|vmov|vone|vzero|vs2i|vi2f|vadd|sv|vcst|vmul|vsin|vcos|vf2id|vf2iz|vf2in|vf2iu|vsub|vdiv|vscl|vtfm4|vmax|vmin|vdot|vcrsp|vfad|vavg|vcmp|vsgn|vrsq|vcmovt|vsqrt|vcmovf|vfim|vocp|vuc2ifs|vi2uc)\..*$",
        line,
    )
    if match:
        comment_prefix, byte1, byte2, byte3, byte4, comment_suffix, opcode = match.groups()
        return f"{comment_prefix}{byte1}{byte2}{byte3}{byte4}{comment_suffix}.word 0x{byte4}{byte3}{byte2}{byte1}"
    match = re.match(
        r"^(.*/\*\s*[0-9A-Fa-fX]+\s+[0-9A-Fa-fX]+\s+)([0-9A-Fa-f]{2})([0-9A-Fa-f]{2})([0-9A-Fa-f]{2})([0-9A-Fa-f]{2})(\s+\*/.*?)(mtv|mfv|vpfxs|vpfxt|bvtl|vpfxd).*$",
        line,
    )
    if match:
        comment_prefix, byte1, byte2, byte3, byte4, comment_suffix, opcode = match.groups()
        return f"{comment_prefix}{byte1}{byte2}{byte3}{byte4}{comment_suffix}.word 0x{byte4}{byte3}{byte2}{byte1}"
    return line


if __name__ == "__main__":
    process = subprocess.Popen(
        ["bin/allegrex-as"] + sys.argv[1:],
        stdin=subprocess.PIPE,
        stdout=sys.stdout,
        stderr=sys.stderr,
        text=True,
    )

    patched_lines = [patch(line) for line in sys.stdin]
    process.stdin.write("\n".join(patched_lines))
    process.stdin.close()
    process.wait()
    sys.exit(process.returncode)
