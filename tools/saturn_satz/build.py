#!/usr/bin/env python3
# python3 tools/saturn_satz/build.py [--window] && build/satz_alucard_warp/sotn --output OUT --cue DISC.cue --bios sega_101.bin [--window]
import argparse
import os
from pathlib import Path
import re
import subprocess
import sys

import yaml

ROOT = Path(__file__).resolve().parents[2]
SRC = ROOT / 'src/saturn'
CONFIG = ROOT / 'config/saturn'
PROGRAM_WARNINGS = ['-Wno-implicit-function-declaration', '-Wno-incompatible-pointer-types', '-Wno-discarded-qualifiers',
                    '-Wno-format-security', '-Wno-return-mismatch']
MODULES = ['zero.bin.yaml', 'game.prg.yaml', 'warp.prg.yaml']
STAGES = {
    'stage_15': ('STAGE_15.PRG', 'g_Stage15Data', 0x42, ''),
    'stage_16': ('STAGE_16.PRG', 'g_Stage16Data', 0x43, '0x10 0x88 0'),
    'rstage15': ('RSTAGE15.PRG', 'g_RStage15Data', 0x62, '0x10 0x88 0'),
    'rstage16': ('RSTAGE16.PRG', 'g_RStage16Data', 0x63, '0x10 0x288 0'),
    'stage_14': ('STAGE_14.PRG', 'g_Stage14Data', 0x08, '0x140 0x1c0 0'),
    'warp': ('WARP.PRG', 'g_WarpStageData', 0x0E, '0xa0 0x88 6'),
}
PLAYERS = {
    'alucard': ('ALUCARD.PRG', 'ALUCARD_player', 0, 'alucard.prg.yaml', True),
    'null': ('MARIA.PRG', 'g_NullPlayer', 2, 'maria.prg.yaml', False),
}
SATZ_LIBRARIES = re.compile(r'^lib/(?!sound_driver$)')
SDK_HEADERS = {'XPT_H': 'sega_xpt.h', 'SYS_H': 'sega_sys.h', 'PER_H': 'sega_per.h'}
SDK_NAMES = {'SND_StartSeq_DR': 'SND_StartSeq', 'SND_StopPcm2': 'SND_StopPcm'}
SBL_UNITS = {
    'SCL': ['scl_back', 'scl_fu01', 'scl_fu02', 'scl_fu03', 'scl_fu04', 'scl_fu05', 'scl_func', 'scl_lncl', 'scl_mosa',
            'scl_pr01', 'scl_pr02', 'scl_pr03', 'scl_pr04', 'scl_pr05', 'scl_pr06', 'scl_pr07', 'scl_pr08', 'scl_pr09',
            'scl_pr10', 'scl_pr11', 'scl_pr12', 'scl_pr13', 'scl_pr14', 'scl_pri', 'scl_ro00', 'scl_ro01', 'scl_ro02',
            'scl_ro03', 'scl_ro04', 'scl_ro05', 'scl_ro10', 'scl_vblv', 'scl_win0', 'scl_win1', 'scl_win2', 'scl_win3'],
    'SPR': ['spr_1c', 'spr_2a', 'spr_2c', 'spr_slv'],
    'MTH': ['mth_fixd', 'mth_tri', 'mth_mtrx', 'mth_ps2d', 'mth_curv'],
}
RENAMED = ['rand']
SYM_PREFIX = '_' if sys.platform == 'darwin' else ''
HOST_LIBC = {'memcmp', 'memcpy', 'memmove', 'memset', 'sprintf', 'strcmp', 'strcpy', 'strlen', 'strncmp', 'strncpy',
             'strcat', 'abs', 'labs'}
CODE_KINDS = {'c', 'asm', 'hasm', 'text', '.text'}
INCLUDE_ASM = re.compile(r'^\s*INCLUDE_ASM(?:_NO_ALIGN)?\(\s*"[^"]*"\s*,\s*\w+\s*,\s*(\w+)\s*\)', re.M)


def module_sources(config, data_only=False):
    files = []
    for segment in yaml.safe_load(config.read_text())['segments']:
        if not isinstance(segment, dict):
            continue
        for sub in segment.get('subsegments', []):
            kind, name = (sub[1], sub[2] if len(sub) > 2 else None) if isinstance(sub, list) else (sub['type'], sub.get('file'))
            if not name or kind not in ('c', '.data', '.rodata', '.bss', '.text', 'bss'):
                continue
            if data_only and (kind not in ('.data', '.rodata') or name.endswith('/header')):
                continue
            if SATZ_LIBRARIES.match(name) or not (SRC / f'{name}.c').exists():
                continue
            if re.fullmatch(r'.*/bss(_\d+)?', name):
                continue
            if name not in files:
                files.append(name)
    return files


def module_of(path):
    names = sorted((config.name.split('.')[0] for config in CONFIG.glob('*.yaml')), key=len, reverse=True)
    return next((name for name in names if path.stem == name or path.stem.startswith(name + '_')), None)


def nonmatching_sources():
    built = {module.split('.')[0] for module in MODULES}
    return sorted(path for path in (SRC / 'satz/nonmatching').glob('*.c') if module_of(path) in built | {None})


def weapon_slots():
    return sorted(int(path.stem[2:]) for path in (SRC / 'satz/nonmatching/weapon').glob('w_[0-9][0-9].c'))


def defined_functions(path):
    return set(re.findall(r'^[A-Za-z_][\w \*]*?\b(\w+)\([^;{}]*\)\s*\{', path.read_text(), re.M))


def write_if_changed(path, text):
    if not path.exists() or path.read_text() != text:
        path.write_text(text)


def weapon_sources(output):
    table = output / 'weapon_table.c'
    tags = [(hand, slot, f'w{hand}_{slot:02}') for hand in (0, 1) for slot in weapon_slots()]
    write_if_changed(table, '#include <saturn_weapon.h>\n' +
                     ''.join(f'extern SaturnWeaponOvl {tag}_header;\n' for _, _, tag in tags) +
                     'SaturnWeaponOvl* const sotn_satz_weapon_headers[2][WEAPON_SLOTS] = {\n' +
                     ''.join('    {\n' + ''.join(f'        [{slot}] = &{tag}_header,\n'
                                                 for h, slot, tag in tags if h == hand) + '    },\n'
                             for hand in (0, 1)) + '};\n')
    wrappers = output / 'weapon'
    wrappers.mkdir(exist_ok=True)
    prefixes, labels = {}, []
    for hand, slot, tag in tags:
        paths = [SRC / 'weapon' / f'w_{slot:02}.c', SRC / 'satz/nonmatching/weapon' / f'w_{slot:02}.c']
        text = ''.join(path.read_text(errors='ignore') for path in paths)
        names = sorted(set(re.findall(r'\b((?:func|DAT|D|d|jtbl)_060D[6-8][0-9A-Fa-f]{3}\w*)\b', text)) |
                       {'g_WeaponHeader', 'g_WeaponHeaderJunk'})
        prefix = output / f'weapon_{tag}_names.h'
        write_if_changed(prefix, f'#define WEAPON_HAND {hand}\n' + ''.join(
            f'#define {name} {tag}_{"header" if name == "g_WeaponHeader" else name}\n' for name in names))
        ported = defined_functions(paths[1])
        labels += [f'{tag}_{label}' for label in INCLUDE_ASM.findall(paths[0].read_text(errors='ignore'))
                   if label not in ported]
        for path in paths:
            wrapper = wrappers / f'{tag}_{"port" if "satz" in path.parts else "data"}.c'
            write_if_changed(wrapper, f'#include "{path}"\n')
            prefixes[wrapper] = prefix
    return table, prefixes, labels


def ported_functions():
    names = set()
    for path in nonmatching_sources() + sorted((SRC / 'satz').glob('*.c')):
        text = path.read_text()
        names.update(re.findall(r'^[A-Za-z_][\w \*]*?\b(\w+)\([^;{}]*\)\s*\{', text, re.M))
        names.update(re.findall(r'^#define\s+\w+\s+(func_[0-9A-Fa-f]{8})\s*$', text, re.M))
    return names


def write_stubs(sources, path, extra=()):
    ported = ported_functions()
    known = symbol_addresses()

    def address(name):
        match = re.match(r'^func_([0-9A-Fa-f]{8})$', name)
        return int(match.group(1), 16) if match else known.get(name)
    ported_at = {address(name) for name in ported} - {None}
    labels = []
    for source in sources:
        for label in INCLUDE_ASM.findall(source.read_text(errors='ignore')):
            if label not in labels and label not in ported and address(label) not in ported_at:
                labels.append(label)
    lines = ['/* Generated by tools/saturn_satz/build.py: functions that are still assembly. */',
             'void sotn_satz_unimplemented(const char* name) __attribute__((noreturn));', '']
    lines += [f'void {label}(void) {{ sotn_satz_unimplemented("{label}"); }}' for label in labels + list(extra)]
    text = '\n'.join(lines) + '\n'
    if not path.exists() or path.read_text() != text:
        path.write_text(text)
    return labels


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--stage', choices=sorted(STAGES), default='warp', help='the stage overlay to build')
    parser.add_argument('--player', choices=sorted(PLAYERS), default='alucard', help='the player overlay to build')
    parser.add_argument('--output', type=Path, help='default build/satz_PLAYER_STAGE')
    parser.add_argument('--satz', type=Path, default=Path(os.environ.get('SATZ', ROOT / 'tools/saturn/satz')))
    parser.add_argument('--window', action='store_true', help='link the SDL window')
    parser.add_argument('--no-build', action='store_true', help='only write build.ninja')
    parser.add_argument('--no-video', action='store_true',
                        help='VDP1/VDP2 kept as registers and memory only, nothing drawn (satz video_none): for '
                             'headless runs, which need no picture; its own core (build/satz_core*_novideo)')
    parser.add_argument('--no-sanitize', dest='sanitize', action='store_false',
                        help='build without AddressSanitizer and UndefinedBehaviorSanitizer')
    args = parser.parse_args()
    MODULES[2:] = [PLAYERS[args.player][3], f'{args.stage}.prg.yaml']
    if args.output is None:
        args.output = ROOT / f'build/satz_{args.player}_{args.stage}'
    sys.path.insert(0, str(args.satz.resolve()))
    import satz

    output = args.output.resolve()
    (output / 'obj').mkdir(parents=True, exist_ok=True)
    core_dir = ROOT / (('build/satz_core' if args.sanitize else 'build/satz_core_nosan') +
                       ('_novideo' if args.no_video else ''))
    (core_dir / 'obj').mkdir(parents=True, exist_ok=True)
    core = write_core_ninja(satz, args, core_dir)
    program = write_ninja(satz, args, output, core, fixed=None)
    if args.no_build:
        return
    satz.ninja(core_dir)
    run_ninja(output, program)
    fixed = output / 'fixed_symbols.c'
    count = write_fixed_symbols(core.objects + program, fixed, output / 'fixed_stubs.c')
    write_ninja(satz, args, output, core, fixed=fixed)
    print(f'{count} fixed-address symbols')
    satz.ninja(output)


def generate_headers(sources):
    wanted = sorted({str((source.parent / 'gen' / name).relative_to(ROOT)) for source in sources
                     for name in re.findall(r'^#include "gen/([\w.]+)"', source.read_text(errors='ignore'), re.M)})
    missing = [path for path in wanted if not (ROOT / path).exists()]
    if not missing:
        return
    stamp = ROOT / 'build.ninja.version'
    if not (ROOT / 'build.ninja').exists() or not stamp.exists() or not stamp.read_text().startswith('saturn'):
        sys.exit('satz: build.ninja is not the Saturn one (or is missing); run ./sotn.sh build saturn first')
    subprocess.run(['ninja', *missing], cwd=ROOT, check=True)


def run_ninja(output, targets):
    result = subprocess.run(['ninja', '-f', str(output / 'build.ninja'), '-k', '0', *map(str, targets)])
    if result.returncode:
        raise SystemExit(result.returncode)


def symbol_addresses():
    addresses = {}
    for path in [CONFIG / (module.split('.')[0] + '_user_syms.txt') for module in MODULES]:
        if not path.exists():
            continue
        for line in path.read_text().splitlines():
            match = re.match(r'\s*_?(\w+)\s*=\s*(0x[0-9A-Fa-f]+)', line)
            if match:
                addresses.setdefault(match.group(1), int(match.group(2), 16))
    return addresses


def code_ranges():
    ranges = []
    for config in [CONFIG / module for module in MODULES]:
        for segment in yaml.safe_load(config.read_text()).get('segments', []):
            if not isinstance(segment, dict) or 'vram' not in segment:
                continue
            subs = [(sub[0], sub[1]) if isinstance(sub, list) else (sub['start'], sub['type'])
                    for sub in segment.get('subsegments', [])]
            for (start, kind), following in zip(subs, subs[1:] + [(None, None)]):
                if kind in CODE_KINDS and following[0] is not None:
                    base = segment['vram'] - segment['start']
                    ranges.append((base + start, base + following[0]))
    return ranges


def alias_flag(name, target):
    if sys.platform == 'darwin':
        return f'-Wl,-alias,{SYM_PREFIX}{target},{SYM_PREFIX}{name}'
    return f'-Wl,--defsym={name}={target}'


def write_fixed_symbols(objects, path, stubs_path):
    defined, undefined = set(), set()
    for obj in objects:
        for line in subprocess.run(['nm', str(obj)], capture_output=True, text=True,
                                   check=True).stdout.splitlines():
            parts = line.split()
            if sys.platform == 'darwin' and parts and parts[-1].startswith('_'):
                parts[-1] = parts[-1][1:]
            if len(parts) == 2 and parts[0] == 'U':
                undefined.add(parts[1])
            elif len(parts) >= 3 and parts[-2] in 'TtDdBbRrCcVvWwS':
                defined.add(parts[-1])
    known = symbol_addresses()
    code = code_ranges()
    functions, missing, data, aliases = [], [], {}, []
    defined_at = {}
    for name in sorted(defined):
        if name in known:
            defined_at.setdefault(known[name], name)
        else:
            match = re.match(r'^(?:DAT|D|d|func)_([0-9A-Fa-f]{8})$', name)
            if match:
                defined_at.setdefault(int(match.group(1), 16), name)

    def defined_alias(address):
        return defined_at.get(address)
    for name in sorted(undefined - defined):
        if name in SDK_NAMES:
            aliases.append((name, SDK_NAMES[name]))
            continue
        if name.startswith('_') and name[1:] in defined:
            aliases.append((name, name[1:]))
            continue
        match = re.match(r'^(?:DAT|D|d|func)_([0-9A-Fa-f]{8})$', name)
        address = known.get(name, int(match.group(1), 16) if match else None)
        if address is None or not (0x06000000 <= address < 0x06100000 or 0x00200000 <= address < 0x00300000):
            missing.append(name)
        elif defined_alias(address):
            aliases.append((name, defined_alias(address)))
        elif any(start <= address < end for start, end in code):
            if name not in HOST_LIBC:
                functions.append(name)
        else:
            data.setdefault(address, []).append(name)
    p = SYM_PREFIX
    bounds = sorted(set(known.values()) | set(data))
    lines = ['/* Generated by tools/saturn_satz/build.py: storage for the symbols the retail link places by address. */',
             '#include <stdint.h>', '']
    table = []
    for address, names in sorted(data.items()):
        following = next((b for b in bounds if b > address), address + 0x1000)
        size = max(8, 2 * min(following - address, 0x40000))
        first = names[0]
        lines.append(f'uint8_t {first}[0x{size:X}] __attribute__((aligned(16))); /* 0x{address:08X} */')
        lines += [f'__asm__(".globl {p}{alias}\\n.set {p}{alias}, {p}{first}");' for alias in names[1:]]
        table.append(f'    {{ "{first}", 0x{address:08X}u, {first}, 0x{size // 2:X}u }},')
    lines += ['', 'const struct { const char* name; uint32_t address; uint8_t* data; uint32_t retail_size; } '
              'sotn_fixed_symbols[] = {'] + table + ['    { 0, 0, 0, 0 },', '};']
    if missing:
        lines += ['', '/* Undefined and not at a known work-RAM address: ' + ', '.join(missing) + ' */']
    text = '\n'.join(lines) + '\n'
    if not path.exists() or path.read_text() != text:
        path.write_text(text)
    stub_text = '\n'.join(['/* Generated by tools/saturn_satz/build.py: retail functions with no C. */',
                           'void sotn_satz_unimplemented(const char* name) __attribute__((noreturn));', ''] +
                          [f'void {name}(void) {{ sotn_satz_unimplemented("{name}"); }}' for name in functions]) + '\n'
    if not stubs_path.exists() or stubs_path.read_text() != stub_text:
        stubs_path.write_text(stub_text)
    alias_text = ''.join(alias_flag(name, target) + '\n' for name, target in aliases)
    alias_path = stubs_path.with_name('fixed_aliases.rsp')
    if not alias_path.exists() or alias_path.read_text() != alias_text:
        alias_path.write_text(alias_text)
    return len(lines)


class Core:

    def __init__(self, objects, libs, toolkit, toolkit_headers):
        self.objects, self.libs, self.toolkit, self.toolkit_headers = objects, libs, toolkit, toolkit_headers


def write_core_ninja(satz, args, core_dir):
    sbl = args.satz.resolve() / 'third_party/saturn-sdk/dts-1996-11/fs/LIBRARY/SBL6/SEGALIB'
    gfs = args.satz.resolve() / 'third_party/saturn-sdk/toolkit/iso/pc/SATURN/SEGALIB'
    with (core_dir / 'build.ninja').open('w') as stream:
        build = satz.Build(stream, core_dir, gcc=True, sanitize=args.sanitize,
                           video='none' if args.no_video else 'mednafen')
        includes, headers = build.sdk_units(sbl, SBL_UNITS)
        toolkit, toolkit_headers = build.sdk_units(gfs, {'GFS': ['gfs', 'gfs_buf', 'gfs_cdb', 'gfs_cdc', 'gfs_cdf',
                                                                 'gfs_dir', 'gfs_mmc', 'gfs_trn']}, name='gfs')
        build.core(includes, headers)
        satz.Writer(stream).default(list(build.objects) + list(toolkit_headers))
    return Core(list(build.objects), list(build.libs), toolkit, toolkit_headers)


def write_ninja(satz, args, output, core, fixed):
    program = []
    with (output / 'build.ninja').open('w') as stream:
        build = satz.Build(stream, output, gcc=True, sanitize=args.sanitize)
        n = build.n
        build.libs += core.libs
        toolkit, toolkit_headers = core.toolkit, core.toolkit_headers

        sotn_str = ROOT / 'build/sotn_str/release/sotn_str'
        toolkit_dir = Path(toolkit[0][2:])
        cflags = satz.SATURN + [f'-D{name}=sotn_{name}' for name in RENAMED] + [
            f'-DSYM_PREFIX="{SYM_PREFIX}"', '-I' + str(SRC), '-I' + str(SRC / 'lib'),
            '-I' + str(ROOT / 'include'), '-DSATZ_SOTN=1', '-DSKIP_ASM=1']
        prg, header, stage_id, start = STAGES[args.stage]
        player_prg, player_header, player_id, _, weapons = PLAYERS[args.player]
        if sys.platform == 'darwin':
            cflags.append('-DSCL_DisplayFrame=__wrap_SCL_DisplayFrame')
        cflags += [f'-DSATZ_STAGE_PRG="{prg}"', f'-DSATZ_STAGE_DATA={header}', f'-DSATZ_STAGE_ID=0x{stage_id:02X}', f'-DSATZ_STAGE_START="{start}"',
                   f'-DSATZ_PLAYER_PRG="{player_prg}"', f'-DSATZ_PLAYER_DATA={player_header}',
                   f'-DSATZ_PLAYER_ID={player_id}']
        for guard, header in SDK_HEADERS.items():
            cflags += ['-D' + guard, '-include', str(toolkit_dir / header)]
        n.rule('sotn_cpp', f'{satz.GCC} -E $flags $in -o $out -MMD -MF $out.d', depfile='$out.d', deps='gcc',
               description='cpp $in')
        to_sjis = ("perl -pe 's/\\xe3\\x80\\x9c/\\xef\\xbd\\x9e/g' | iconv -f UTF-8 -t CP932"
                   if sys.platform == 'darwin' else 'iconv --from-code=UTF-8 --to-code=Shift-JIS')
        n.rule('sotn_str', f'{sotn_str} process < $in | {to_sjis} > $out',
               description='sotn_str $in')
        n.rule('sotn_cc', f'{satz.GCC} $flags -fcommon -x cpp-output -c $in -o $out', description='gcc $in')

        program_flags = [f for f in build.saturn_common if f != '-w'] + ['-std=gnu99'] + PROGRAM_WARNINGS
        sources = []
        for module in MODULES:
            data_only = args.player == 'null' and module == PLAYERS['null'][3]
            sources += [SRC / f'{name}.c' for name in module_sources(CONFIG / module, data_only)]
        sources += [path for path in sorted((SRC / 'satz').glob('*.c'))
                    if args.player == 'null' or path.name != 'null_player.c'] + nonmatching_sources()
        weapon_prefixes, weapon_labels = {}, []
        if weapons:
            cflags.append('-DSATZ_WEAPONS=1')
            table, weapon_prefixes, weapon_labels = weapon_sources(output)
            sources.append(table)
        generate_headers(sources)
        stubs = output / 'stubs.c'
        labels = write_stubs(sources, stubs, weapon_labels)
        for source in sources + list(weapon_prefixes) + [stubs]:
            stem = build.object_path(source).with_suffix('')
            pre, expanded, obj = stem.with_suffix('.i'), stem.with_suffix('.sjis.i'), stem.with_suffix('.o')
            flags = cflags + (['-include', str(weapon_prefixes[source])] if source in weapon_prefixes else [])
            n.build(pre, 'sotn_cpp', source, implicit=toolkit_headers, variables={'flags': satz.q(flags)})
            n.build(expanded, 'sotn_str', pre, implicit=[sotn_str])
            n.build(obj, 'sotn_cc', expanded, variables={'flags': satz.q(program_flags)})
            program.append(obj)
        if sys.platform == 'darwin':
            build.libs.append(alias_flag('__real_SCL_DisplayFrame', 'SCL_DisplayFrame'))
        else:
            build.libs.append('-Wl,--wrap=SCL_DisplayFrame')
        binary = output / 'sotn'
        if fixed:
            build.libs.append(f'@{output / "fixed_aliases.rsp"}')
            build.host_cc(fixed)
            build.host_cc(output / 'fixed_stubs.c')
            build.link(binary, extra=program + core.objects, window=args.window)
            satz.Writer(stream).default([binary])
    if not fixed:
        print(f'{len(sources)} sources, {len(labels)} assembly stubs')
    return program


if __name__ == '__main__':
    main()
