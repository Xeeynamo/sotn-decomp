#!/usr/bin/env python3
"""Generates a WEAPON0.PRG slot's header and data as C; --write puts them in src/saturn/weapon/w_NN.c around its code: weapon_data.py SLOT [--write] [--report]"""
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import weapon_layout as wl

ROOT = wl.ROOT
HINTS = {
    60: {0xA80: 'animframes'},
    62: {0xAA0: 'animframes'},
    59: {0xA00: 'u16'},
    61: {0x1244: 'hitboxes', 0x128C: 'animptrs'},
}
BASE = wl.BASE


def be16(d, o):
    return struct.unpack('>H', d[o:o + 2])[0]


def be32(d, o):
    return struct.unpack('>I', d[o:o + 4])[0]


def s16(v):
    return v - 0x10000 if v & 0x8000 else v


def s8(v):
    return v - 0x100 if v & 0x80 else v


class Slot:
    def __init__(self, n):
        self.n = n
        self.d = wl.slot_bytes(n)
        self.L = wl.layout(self.d)
        self.end = self.L['end']
        self.regions = [(self.L['code_end'], self.end)]
        self.kinds = {}
        self.literals = self.code_literals()

    def in_data(self, o):
        return o < 0x60 or any(a <= o < b for a, b in self.regions)

    def ptr(self, o):
        w = be32(self.d, o)
        return w - BASE if BASE <= w < BASE + self.end else None

    def code_literals(self):
        out = set()
        for s in (ROOT / f'asm/saturn/weapon/w_{self.n:02}').glob('f_*/*.s'):
            for m in re.finditer(r'\.long _DAT_060D([0-9A-F]{4})', s.read_text()):
                out.add(int(m.group(1), 16) - 0x6000)
        return out

    def targets(self):
        t = set(self.literals)
        for a, b in [(0, 0x44)] + self.regions:
            for o in range(a, b - 3, 2):
                if o % 4 == 0:
                    p = self.ptr(o)
                    if p is not None and self.in_data(p):
                        t.add(p)
        t |= {a for a, b in self.regions}
        return sorted(x for x in t if self.in_data(x))

    def next_target(self, o, targets):
        nxt = [t for t in targets if t > o] + [b for a, b in self.regions if a <= o < b] + [self.end]
        return min(nxt)

    def classify(self):
        d = self.d
        k = self.kinds
        targets = self.targets()
        reslist = be32(d, 0x40) - BASE
        k[reslist] = ('reslist', None)
        o = reslist
        while o < self.end and self.ptr(o) is not None:
            res = self.ptr(o)
            k[res] = ('resource', None)
            images, palettes = self.ptr(res), self.ptr(res + 4)
            if images is not None:
                k[images] = ('images', None)
            if palettes is not None:
                k[palettes] = ('palette', None)
            o += 4
        for t in targets:
            if t in k or t % 4:
                continue
            ptrs = self.pointer_run(t, targets)
            if not ptrs:
                continue
            if all(self.is_frame(p) for p in ptrs if p is not None) and len(ptrs) > 1:
                k[t] = ('frametable', len(ptrs))
                for p in ptrs:
                    k.setdefault(p, ('frame', None))
        for t in sorted(self.literals):
            if t in k or t % 4 or not self.in_data(t):
                continue
            if self.is_weapon_anims(t, targets):
                n = self.weapon_anim_count(t, targets)
                k[t] = ('weaponanims', n)
                for i in range(n):
                    e = t + 16 * i
                    table, props = self.ptr(e), self.ptr(e + 4)
                    k.setdefault(props, ('hitboxes', None))
                    if table not in k:
                        k[table] = ('animtable', None)
        for t in [x for x in k if k[x][0] == 'animtable']:
            for p in self.pointer_run(t, targets):
                if p is not None:
                    k.setdefault(p, ('poses', None))
        for o, kind in HINTS.get(self.n, {}).items():
            k[o] = (kind, None)
            if kind == 'animptrs':
                for p in self.pointer_run(o, targets) or []:
                    if p is not None:
                        k[p] = ('animframes', None)
        return k

    def pointer_run(self, o, targets):
        end = self.next_target(o, targets)
        if (end - o) % 4:
            return None
        out = []
        for x in range(o, end, 4):
            p = self.ptr(x)
            if p is None:
                return None
            out.append(p)
        return out

    def is_frame(self, o):
        if o % 2 or not self.in_data(o):
            return False
        count = be16(self.d, o) >> 8
        return be16(self.d, o) & 0xFF == 0 and count <= 34

    def is_weapon_anims(self, o, targets):
        return self.weapon_anim_count(o, targets) > 0

    def weapon_anim_count(self, o, targets):
        n = 0
        end = self.next_target(o, targets)
        while o + 16 * (n + 1) <= self.end:
            e = o + 16 * n
            if self.ptr(e) is None or self.ptr(e + 4) is None or self.ptr(e + 8) is not None:
                break
            n += 1
            if e + 16 >= end and n:
                nt = self.next_target(e + 15, targets)
                if nt == e + 16 and self.ptr(e + 16) is not None and self.ptr(e + 20) is not None:
                    end = self.next_target(e + 16, targets)
                    continue
                break
        return n


def name(o):
    return f'DAT_{BASE + o:08X}'


def c_region(slot, o, end, kind, info, emitted_types):
    d = slot.d
    nm = name(o)
    if kind == 'reslist':
        n = (end - o) // 4
        items = ', '.join(f'&{name(slot.ptr(o + 4 * i))}' for i in range(n))
        return f'SaturnSpriteResource* {nm}[{n}] = {{{items}}};\n'
    if kind == 'resource':
        images, palettes = slot.ptr(o), slot.ptr(o + 4)
        text = (f'SaturnSpriteResource {nm} = {{{name(images)}, (u16*)&{name(palettes)}, '
                f'0x{be16(d, o + 8):04X}, 0x{be16(d, o + 10):04X}}};\n')
        return text + raw(slot, o + 12, end, nm + '_tail') if end > o + 12 else text
    if kind == 'images':
        n = (end - o) // 4
        rows = [f'{{{d[o + 4 * i]}, {d[o + 4 * i + 1]}, 0x{be16(d, o + 4 * i + 2):04X}}}' for i in range(n)]
        text = f'SaturnSpriteImage {nm}[{n}] = {{\n' + ''.join(f'    {r},\n' for r in rows) + '};\n'
        rest = o + 4 * n
        return text + (raw(slot, rest, end, nm + '_tail') if end > rest else '')
    if kind == 'palette':
        count = be16(d, o) & 0xFF
        pad = (end - o - 2 - count * 32) // 2
        if pad < 0:
            return raw(slot, o, end, nm)
        colors = ''.join('    {' + ', '.join(f'0x{be16(d, o + 2 + 32 * r + 2 * c):04X}' for c in range(16)) + '},\n'
                         for r in range(count))
        padding = ', '.join(f'0x{be16(d, o + 2 + 32 * count + 2 * i):04X}' for i in range(pad))
        return (f'struct {{\n    u16 countAndFlags;\n    u16 colors[{count}][16];\n' +
                (f'    u16 padding[{pad}];\n' if pad else '') +
                f'}} {nm} = {{\n    0x{be16(d, o):04X},\n    {{\n{colors}    }},\n' +
                (f'    {{{padding}}},\n' if pad else '') + '};\n')
    if kind == 'frame':
        count = be16(d, o) >> 8
        size = 4 + 8 * count
        if o + size > end:
            return raw(slot, o, end, nm)
        if count == 0:
            text = f'SaturnSpriteFrameHeader {nm} = {{0x{be16(d, o):04X}, 0x{be16(d, o + 2):04X}}};\n'
        else:
            parts = ''.join(f'        {{0x{be16(d, p):04X}, {s16(be16(d, p + 2))}, {s16(be16(d, p + 4))}, '
                            f'{be16(d, p + 6)}}},\n' for p in range(o + 4, o + size, 8))
            text = (f'SaturnSpriteFrame{count} {nm} = {{\n    {{0x{be16(d, o):04X}, 0x{be16(d, o + 2):04X}}},\n'
                    f'    {{\n{parts}    }},\n}};\n')
        return text + (raw(slot, o + size, end, nm + '_tail') if end > o + size else '')
    if kind == 'frametable':
        n = (end - o) // 4
        items = ''.join(f'    (SaturnSpriteFrameHeader*)&{name(slot.ptr(o + 4 * i))},\n' for i in range(n))
        return f'SaturnSpriteFrameHeader* {nm}[{n}] = {{\n{items}}};\n'
    if kind == 'weaponanims':
        n = info
        rows = []
        for i in range(n):
            e = o + 16 * i
            rows.append(f'    {{(u16**){name(slot.ptr(e))}, (s8*){name(slot.ptr(e + 4))}, 0x{be16(d, e + 8):04X}, '
                        f'0x{be16(d, e + 10):04X}, 0x{d[e + 12]:02X}, 0x{d[e + 13]:02X}, {s16(be16(d, e + 14))}}},\n')
        text = f'WeaponAnimation {nm}[{n}] = {{\n' + ''.join(rows) + '};\n'
        return text + (raw(slot, o + 16 * n, end, nm + '_tail') if end > o + 16 * n else '')
    if kind == 'animtable':
        n = (end - o) // 4
        items = ', '.join(name(slot.ptr(o + 4 * i)) for i in range(n))
        return f'u16* {nm}[{n}] = {{{items}}};\n'
    if kind == 'poses':
        n = (end - o) // 2
        rows = ', '.join(f'0x{be16(d, o + 2 * i):04X}' for i in range(n))
        text = f'u16 {nm}[{n}] = {{{rows}}};\n'
        return text + (raw(slot, o + 2 * n, end, nm + '_tail', width=1) if end > o + 2 * n else '')
    if kind == 'animptrs':
        n = (end - o) // 4
        items = ', '.join(name(slot.ptr(o + 4 * i)) for i in range(n))
        return f'AnimationFrame* {nm}[{n}] = {{{items}}};\n'
    if kind == 'u16':
        return raw(slot, o, end, nm, width=2)
    if kind == 'animframes':
        n = 0
        while o + 4 * n + 4 <= end:
            n += 1
            if be16(d, o + 4 * (n - 1)) in (0, 0xFFFF, 0xFFFE):
                break
        rows = ', '.join(f'{{0x{be16(d, o + 4 * i):04X}, 0x{be16(d, o + 4 * i + 2):04X}}}' for i in range(n))
        text = f'AnimationFrame {nm}[{n}] = {{{rows}}};\n'
        return text + (raw(slot, o + 4 * n, end, nm + '_tail') if end > o + 4 * n else '')
    if kind == 'hitboxes':
        n = (end - o) // 4
        rows = ', '.join('{' + ', '.join(str(s8(d[o + 4 * i + j])) for j in range(4)) + '}' for i in range(n))
        text = f's8 {nm}[{n}][4] = {{{rows}}};\n'
        return text + (raw(slot, o + 4 * n, end, nm + '_tail', width=1) if end > o + 4 * n else '')
    return raw(slot, o, end, nm)


def raw(slot, o, end, nm, width=None):
    d = slot.d
    size = end - o
    if width is None:
        width = 4 if o % 4 == 0 and size % 4 == 0 else 2 if o % 2 == 0 and size % 2 == 0 else 1
    if width == 4:
        vals = [f'0x{be32(d, x):08X}' for x in range(o, end, 4)]
        t = 'u32'
    elif width == 2:
        vals = [f'0x{be16(d, x):04X}' for x in range(o, end, 2)]
        t = 'u16'
    else:
        vals = [f'0x{d[x]:02X}' for x in range(o, end)]
        t = 'u8'
    lines = ''.join('    ' + ', '.join(vals[i:i + 8]) + ',\n' for i in range(0, len(vals), 8))
    return f'{t} {nm}[{len(vals)}] = {{\n{lines}}};\n'


def generate(n):
    slot = Slot(n)
    k = slot.classify()
    targets = sorted(set(slot.targets()) | set(k))
    sizes = {'resource': 12}
    for o, (kind, info) in list(k.items()):
        size = sizes.get(kind) or (16 * info if kind == 'weaponanims' else
                                   4 + 8 * (be16(slot.d, o) >> 8) if kind == 'frame' else 0)
        inner = [t for t in targets if o < t < o + size]
        for t in inner:
            targets.remove(t)
            k.pop(t, None)
    files = {}
    order = [('header', 0, 0x60)]
    order.append(('data', slot.L['code_end'], slot.end))
    report = []
    for fname, a, b in order:
        if fname == 'header':
            entries = ''.join(f'    func_{be32(slot.d, 4 * i):08X},\n' for i in range(16))
            decls = ''.join(f'void func_{be32(slot.d, 4 * i):08X}();\n' for i in sorted(set(range(16)),
                            key=lambda i: be32(slot.d, 4 * i)) if True)
            decls = ''.join(sorted(set(f'void func_{be32(slot.d, 4 * i):08X}();\n' for i in range(16))))
            files[fname] = (decls + f'extern SaturnSpriteResource* {name(be32(slot.d, 0x40) - BASE)}[];\n\n'
                            f'SaturnWeaponOvl g_WeaponHeader WEAPON_HEADER = {{\n    {{\n' +
                            entries.replace('    func', '        func') +
                            f'    }},\n    {name(be32(slot.d, 0x40) - BASE)},\n}};\n\n'
                            'u32 g_WeaponHeaderJunk[7] WEAPON_HEADER = {' +
                            ', '.join(f'0x{be32(slot.d, 0x44 + 4 * i):08X}' for i in range(7)) + '};\n')
            continue
        cuts = sorted({a, b} | {t for t in targets if a < t < b})
        body = []
        spans = []
        for x, y in zip(cuts, cuts[1:]):
            kind, info = k.get(x, ('raw', None))
            if kind == 'raw' and spans and spans[-1][2] == 'raw':
                spans[-1][1] = y
                continue
            spans.append([x, y, kind, info])
        for x, y, kind, info in spans:
            report.append((x, y, kind))
            body.append(c_region(slot, x, y, kind, info, set()))
        files[fname] = '\n'.join(body)
    return slot, files, report


HEAD = '// SPDX-License-Identifier: AGPL-3.0-or-later\n' \
       '#include "inc_asm.h"\n#include "sattypes.h"\n#include <saturn_sprite.h>\n#include <saturn_weapon.h>\n#include "weapon/weapon.h"\n\n'


def main():
    n = int(sys.argv[1])
    slot, files, report = generate(n)
    if '--report' in sys.argv:
        for x, y, kind in report:
            print(f'{x:04x}-{y:04x} {y - x:5x} {kind}')
    if '--write' in sys.argv:
        defined = {}
        for fname, text in files.items():
            for m in re.finditer(r'^(?:struct \{.*?\}|[\w\*]+(?: \w+)?)\s+\**(DAT_060D[0-9A-F]{4})(\[[^\]]*\])*',
                                 text, re.M | re.S):
                defined[m.group(1)] = fname
        for fname, text in files.items():
            used = sorted(set(re.findall(r'\b(DAT_060D[0-9A-F]{4})\b', text)) - {k for k, v in defined.items()
                                                                               if v == fname})
            if fname == 'header':
                used = []
            elif used:
                raise SystemExit(f'{fname}.c uses {used} without defining them')
        path = ROOT / f'src/saturn/weapon/w_{n:02}.c'
        code = [l for l in path.read_text().splitlines() if l.startswith('INCLUDE_ASM(') and ', d60D' not in l]
        path.write_text(HEAD + files['header'] + '\n' + '\n'.join(code) + '\n\n' + files['data'])
    if not ('--report' in sys.argv or '--write' in sys.argv):
        for fname, text in files.items():
            print(f'// ===== {fname}.c\n{text}')


if __name__ == '__main__':
    main()
