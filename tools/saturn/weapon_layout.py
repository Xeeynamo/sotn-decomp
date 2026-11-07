#!/usr/bin/env python3
"""Prints each WEAPON0.PRG slot's code range, used size, function count and data pointer: weapon_layout.py [SLOT...]"""
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
BASE, SLOT = 0x060D6000, 0x3000


def slot_bytes(n, path=ROOT / 'disks/saturn/WEAPON0.PRG'):
    return path.read_bytes()[n * SLOT:(n + 1) * SLOT]


def used_end(d):
    return (len(d.rstrip(b'\0')) + 3) & ~3


def layout(d):
    end = used_end(d)
    header = struct.unpack('>17I', d[:0x44])
    entries = sorted(set(a for a in header[:16] if BASE <= a < BASE + end))
    words = [struct.unpack('>I', d[i:i + 4])[0] for i in range(0, end, 4)]
    pointers = sorted(set(w for w in words if BASE + 0x44 <= w < BASE + end))
    first = BASE + 0x60
    assert struct.unpack('>H', d[0x60:0x62])[0] == 0x2F86
    def after_return(a):
        o = a - BASE
        return o >= 4 and struct.unpack('>H', d[o - 4:o - 2])[0] == 0x000B
    def code_like(a):
        o = a - BASE
        op = struct.unpack('>H', d[o:o + 2])[0]
        return (op & 0xFF0F) == 0x2F06 or op == 0x4F22 or (op & 0xFF00) == 0x7F00 or op == 0x000B
    funcs = sorted(set(entries) | {first} | {p for p in pointers if p > first and p % 2 == 0 and after_return(p) and code_like(p)})
    data = [p for p in pointers if p > funcs[-1] and p not in funcs]
    code_end = min(data) if data else end
    return {'end': end, 'entries': entries, 'funcs': funcs, 'code_start': first - BASE, 'code_end': code_end - BASE,
            'data_ptr': header[16]}


def main():
    slots = [int(a) for a in sys.argv[1:]] or range(64)
    for n in slots:
        L = layout(slot_bytes(n))
        print(f"{n:2} code {L['code_start']:#06x}-{L['code_end']:#06x} used {L['end']:#06x} "
              f"funcs {len(L['funcs'])} data_ptr {L['data_ptr']:#010x}")


if __name__ == '__main__':
    main()
