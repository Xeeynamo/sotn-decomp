#!/usr/bin/env python3
"""Slices WEAPON0.PRG into build/saturn/weapon/W0_NN.PRG and writes any missing slot configs: weapon_configs.py [--slices-only]"""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import weapon_layout

ROOT = weapon_layout.ROOT
SLICES = ROOT / 'build/saturn/weapon'
CONFIGS = ROOT / 'config/saturn/weapon'

TEMPLATE = """options:
  target_path:  build/saturn/weapon/W0_{n:02}.PRG
  asm_path:     asm/saturn/weapon/w_{n:02}
  src_path:     src/saturn/weapon
  obj_path:     build/saturn/weapon
  ld_scripts_path: config/saturn/weapon
  syms_path: config/saturn/weapon
  decomp_empty_funcs: false
  symbol_files:
    - ../game_user_syms.txt
    - ../zero_user_syms.txt
    - ../game_syms.gen.txt
    - ../zero_syms.gen.txt
segments:
  - name: w_{n:02}
    type: code
    start: 0x00000000
    vram:  0x060D6000
    subalign: 2
    subsegments:
      - start: 0x0
        type: .rodata
        file: w_{n:02}
        end: 0x60
      - start: {code_start:#x}
        type: c
        file: w_{n:02}
        end: {code_end:#x}
        function_ranges:
{hints}      - start: {code_end:#x}
        type: .data
        file: w_{n:02}
        end: {end:#x}
"""


def main():
    SLICES.mkdir(parents=True, exist_ok=True)
    CONFIGS.mkdir(parents=True, exist_ok=True)
    whole = (ROOT / 'disks/saturn/WEAPON0.PRG').read_bytes()
    for n in range(64):
        d = whole[n * 0x3000:(n + 1) * 0x3000]
        path = SLICES / f'W0_{n:02}.PRG'
        if not path.exists() or path.read_bytes() != d:
            path.write_bytes(d)
        config = CONFIGS / f'w_{n:02}.prg.yaml'
        if '--slices-only' in sys.argv or config.exists():
            continue
        L = weapon_layout.layout(d)
        hints = ''.join(f'          - [{e:#x}, {e:#x}]\n' for e in sorted({a - weapon_layout.BASE for a in L['entries']} | {0x60}))
        config.write_text(TEMPLATE.format(n=n, hints=hints, code_start=L['code_start'], code_last=L['code_end'] - 1,
                                          code_end=L['code_end'], end=L['end']))


if __name__ == '__main__':
    main()
