# usage
# python3 ./tools/builds/build.py && ninja

import ninja_syntax
import os
import shutil

# write out current pwd to open it as a disk
with open('./tools/builds/.dosemurc', 'w') as f:
    f.write(f'$_hdimage = \'+0 {os.getcwd()} +1\'\n')

# copy cygnus into a 8.3 folder
if not os.path.exists('tools/builds/GCCSH'):
    shutil.copytree('bin/cygnus-2.7-96Q3-bin', 'tools/builds/GCCSH')

ninja = ninja_syntax.Writer(open("build.ninja", "w"))

ninja.rule('compile',
           command='sh ./tools/builds/dosemu_wrapper.sh $in $out $args $tmpdir',
           description='Building $out from $in')

ninja.rule(
        'check',
        command='.venv/bin/python3 tools/builds/check.py config/check.saturn.sha',
        description='Checking that $in matches')

ninja.rule('coff2elf',
           command="sh-elf-objcopy -Icoff-sh -Oelf32-sh $in $out",
           description='Converting $out from $in')

SOTN_STR = 'build/sotn_str/release/sotn_str'

ninja.rule('cargo_sotn_str',
           command='CARGO_TARGET_DIR=build/sotn_str cargo build --release '
                   '--manifest-path tools/sotn_str/Cargo.toml',
           description='Building $out')

ninja.build(
    SOTN_STR,
    'cargo_sotn_str',
    inputs=[
        'tools/sotn_str/Cargo.toml',
        'tools/sotn_str/Cargo.lock',
        'tools/sotn_str/src/main.rs',
    ])

ninja.rule(
    'check_saturn_symbol_ownership',
    command='python3 tools/saturn/check_symbol_ownership.py '
            '--output saturn_symbol_ownership.txt && touch $out',
    description='Validating Saturn user-symbol ownership',
)

symbol_ownership_inputs = [
    'tools/saturn/check_symbol_ownership.py',
]
for target, config_name, binary_name in [
    ('zero', 'zero.bin.yaml', '0.BIN'),
    ('game', 'game.prg.yaml', 'GAME.PRG'),
    ('richter', 'richter.prg.yaml', 'RICHTER.PRG'),
    ('maria', 'maria.prg.yaml', 'MARIA.PRG'),
    ('alucard', 'alucard.prg.yaml', 'ALUCARD.PRG'),
    ('stage_02', 'stage_02.prg.yaml', 'STAGE_02.PRG'),
    ('t_bat', 't_bat.prg.yaml', 'T_BAT.PRG'),
    ('warp', 'warp.prg.yaml', 'WARP.PRG'),
]:
    symbol_ownership_inputs.extend([
        f'config/saturn/{target}_user_syms.txt',
        f'config/saturn/{config_name}',
        f'disks/saturn/{binary_name}',
    ])

SYMBOL_OWNERSHIP_STAMP = 'build/saturn/symbol_ownership.ok'
ninja.build(
    SYMBOL_OWNERSHIP_STAMP,
    'check_saturn_symbol_ownership',
    inputs=symbol_ownership_inputs,
)

ninja.rule('link',
           command= 'sh-elf-ld --no-check-sections -nostdlib \
                    -o $out \
                    -Map $out.map \
                    -T config/saturn/$ld_file \
                    $symbol_scripts \
                    $target_aliases \
                    $in',
           description='Linking $out from $in')

ninja.rule('link_multi',
           command= 'sh-elf-ld --no-check-sections -nostdlib \
                    -o $out \
                    -Map $out.map \
                    -T config/saturn/$ld_file \
                    $symbol_scripts \
                    $target_aliases \
                    $in $objs',
           description='Linking $out from $in')

ninja.rule('cpp',
           command='cpp $FLAGS $in > $out',
           description='Running preprocessor on $out from $in')

ninja.rule('sotn_str',
           command=f'{SOTN_STR} process < $in > $out',
           description='Expanding SOTN strings in $out from $in')

ninja.rule('iconv_sjis',
           command='iconv --from-code=UTF-8 --to-code=Shift-JIS < $in > $out',
           description='Encoding Shift-JIS in $out from $in')

ninja.rule('as',
           'sh-elf-as -no-pad-sections -I./src/saturn $in -o $out')

def add_srcs(srcs, output_dir, args):
    for src in srcs:
        filename_without_extension = os.path.splitext(os.path.basename(src))[0]
        relative_path = os.path.relpath(src, 'src/saturn')
        obj_dir = os.path.join(output_dir, os.path.dirname(relative_path))
        obj_name = os.path.join(obj_dir, f"{filename_without_extension}.cof")
        cpp_name = os.path.join(obj_dir, f"{filename_without_extension}.cpp")
        str_name = os.path.join(obj_dir, f"{filename_without_extension}.str")
        pre_name = os.path.join(obj_dir, f"{filename_without_extension}.pre")
        asm_name = os.path.join(obj_dir, f"{filename_without_extension}.s")

        flags = '-lang-c -I./src/saturn -I./src/saturn/lib -undef -D__GNUC__=2 -D__GNUC_MINOR__=7 -D__sh__ -D__sh__ -D__sh2__'

        ninja.build(
            pre_name,
            'cpp',
            inputs=[src],
            variables={'FLAGS': flags})

        ninja.build(
            str_name,
            'sotn_str',
            inputs=[pre_name],
            implicit=[SOTN_STR])

        ninja.build(
            cpp_name,
            'iconv_sjis',
            inputs=[str_name])

        ninja.build(
            asm_name, 
            'compile', 
            inputs=[cpp_name],
            variables={
                'args': args
            })
        
        ninja.build(
            obj_name,
            'as',
            inputs=[asm_name])

snd_srcs = [
    'src/saturn/alucard.c',
    'src/saturn/alucard/header.c',
    'src/saturn/alucard/hdrstub.c',
    'src/saturn/zero.c',
    'src/saturn/lib/snd.c',
    'src/saturn/zero_2.c',
    'src/saturn/zero_3.c',
    'src/saturn/zero/stgfiles.c',
    'src/saturn/zero/snddata.c',
    'src/saturn/zero/adpcm.c',
    'src/saturn/zero/sndlut.c',
    'src/saturn/zero/sndcmd.c',
    'src/saturn/zero/stgspr0.c',
    'src/saturn/zero/stgspr1.c',
    'src/saturn/zero/stgspr2.c',
    'src/saturn/zero/stgspr3.c',
    'src/saturn/zero/stgspr4.c',
    'src/saturn/zero/stgspr5.c',
    'src/saturn/zero/stgspr6.c',
    'src/saturn/zero/stgspr7.c',
    'src/saturn/zero/stgspr8.c',
    'src/saturn/zero/stgspr9.c',
    'src/saturn/zero/stgspr10.c',
    'src/saturn/zero/stgspr11.c',
    'src/saturn/zero/stgspr12.c',
    'src/saturn/zero/stgspr13.c',
    'src/saturn/zero/stgspr14.c',
    'src/saturn/zero/fontmap.c',
    'src/saturn/zero/sysflag.c',
    'src/saturn/lib/spr/spr_data.c',
    'src/saturn/game_0.c',
    'src/saturn/game_1.c',
    'src/saturn/game_3a.c',
    'src/saturn/game/primuv.c',
    'src/saturn/game_3b.c',
    'src/saturn/game.c',
    'src/saturn/game_2a.c',
    'src/saturn/game/statlbl.c',
    'src/saturn/game_2b.c',
    'src/saturn/game/header.c',
    'src/saturn/game/hdrstub.c',
    'src/saturn/game/savemsg.c',
    'src/saturn/game/cfgjp.c',
    'src/saturn/game/cfgstr.c',
    'src/saturn/game/cfgrw1.c',
    'src/saturn/game/cfgrw1b.c',
    'src/saturn/game/cfgrw1c.c',
    'src/saturn/game/cfgrw1d.c',
    'src/saturn/game/jewel.c',
    'src/saturn/game/cfgrw4.c',
    'src/saturn/game/btnmask.c',
    'src/saturn/game/cfgrw2.c',
    'src/saturn/game/lvlhp.c',
    'src/saturn/game/cfgrw3.c',
    'src/saturn/game/mnstate.c',
    'src/saturn/game/cfgrw5.c',
    'src/saturn/game/eqhelp.c',
    'src/saturn/game/mnscroll.c',
    'src/saturn/game/cfgrest.c',
    'src/saturn/game/capetbl.c',
    'src/saturn/game/capepal.c',
    'src/saturn/game/miscend.c',
    'src/saturn/game/sinetbl.c',
    'src/saturn/richter.c',
    'src/saturn/ric/header.c',
    'src/saturn/ric/hdrstub.c',
    'src/saturn/ric/d54568.c',
    'src/saturn/ric/gprolog.c',
    'src/saturn/ric/timers.c',
    'src/saturn/ric/sensors.c',
    'src/saturn/ric/subwdata.c',
    'src/saturn/ric/bpdefs.c',
    'src/saturn/ric/anims.c',
    'src/saturn/ric/hitboxes.c',
    'src/saturn/ric/sprpal1.c',
    'src/saturn/ric/sprfrm1.c',
    'src/saturn/ric/sprimg1.c',
    'src/saturn/ric/sprpkg2.c',
    'src/saturn/ric/sprpkg3.c',
    'src/saturn/ric/sprpkg4.c',
    'src/saturn/ric/sprpkg5.c',
    'src/saturn/ric/sprpkg6.c',
    'src/saturn/ric/sprpkg7.c',
    'src/saturn/ric/sprpkg8.c',
    'src/saturn/ric/sprpkg9.c',
    'src/saturn/ric/sprpkg10.c',
    'src/saturn/ric/sprres.c',
    'src/saturn/ric/gfxloads.c',
    'src/saturn/ric/whipdata.c',
    'src/saturn/ric/whipdat.c',
    'src/saturn/ric/vibanim.c',
    'src/saturn/ric/subwpfx.c',
    'src/saturn/ric/hwdata.c',
    'src/saturn/ric/crossdat.c',
    'src/saturn/ric/castmap.c',
    'src/saturn/ric/mapcmd.c',
    'src/saturn/ric/mapui.c',
    'src/saturn/ric/deathgfx.c',
    'src/saturn/ric/coffres.c',
    'src/saturn/ric/rictail.c',
    'src/saturn/ric/rictl2.c',
    'src/saturn/stage_02.c',
    'src/saturn/stage_02/sthead.c',
    'src/saturn/stage_02/stprolo.c',
    'src/saturn/stage_02/stbrkgfx.c',
    'src/saturn/stage_02/stglobe.c',
    'src/saturn/stage_02/stlife.c',
    'src/saturn/stage_02/stblue.c',
    'src/saturn/stage_02/stsubgfx.c',
    'src/saturn/stage_02/stelevgf.c',
    'src/saturn/stage_02/st74gfx.c',
    'src/saturn/stage_02/stmargfx.c',
    'src/saturn/stage_02/stsprbnk.c',
    'src/saturn/stage_02/stentupd.c',
    'src/saturn/stage_02/sthlay.c',
    'src/saturn/stage_02/stvlay.c',
    'src/saturn/stage_02/stprize.c',
    'src/saturn/stage_02/sthlaydt.c',
    'src/saturn/stage_02/stvlaydt.c',
    'src/saturn/stage_02/stlayer.c',
    'src/saturn/stage_02/strmgfx.c',
    'src/saturn/stage_02/stprops.c',
    'src/saturn/stage_02/strooms.c',
    'src/saturn/stage_02/stbreak.c',
    'src/saturn/stage_02/stent00.c',
    'src/saturn/stage_02/stent08.c',
    'src/saturn/stage_02/stcont.c',
    'src/saturn/stage_02/stpuff.c',
    'src/saturn/stage_02/stent01.c',
    'src/saturn/stage_02/stsubwp.c',
    'src/saturn/stage_02/stent15.c',
    'src/saturn/stage_02/stent20.c',
    'src/saturn/stage_02/stent02.c',
    'src/saturn/stage_02/stwalls.c',
    'src/saturn/stage_02/stent16.c',
    'src/saturn/stage_02/stent21.c',
    'src/saturn/stage_02/stent22.c',
    'src/saturn/stage_02/stcutdat.c',
    'src/saturn/stage_02/stent17.c',
    'src/saturn/stage_02/stcutst.c',
    'src/saturn/stage_02/stcutsc.c',
    'src/saturn/stage_02/stcuttrl.c',
    'src/saturn/stage_02/stent03.c',
    'src/saturn/stage_02/stmaria.c',
    'src/saturn/stage_02/stlookup.c',
    'src/saturn/stage_02/stprcfg.c',
    'src/saturn/stage_02/stgold.c',
    'src/saturn/stage_02/stprzan.c',
    'src/saturn/stage_02/stent04.c',
    'src/saturn/stage_02/stent09.c',
    'src/saturn/stage_02/stexpl.c',
    'src/saturn/stage_02/stent05.c',
    'src/saturn/stage_02/stent06.c',
    'src/saturn/stage_02/stent07.c',
    'src/saturn/stage_02/st3dco.c',
    'src/saturn/stage_02/st3didx.c',
    'src/saturn/stage_02/stent18.c',
    'src/saturn/stage_02/stdata37.c',
    'src/saturn/stage_02/stbank28.c',
    'src/saturn/stage_02/stent19.c',
    'src/saturn/stage_02/stdata38.c',
    'src/saturn/stage_02/stspr37.c',
    'src/saturn/stage_02/stfrm38.c',
    'src/saturn/stage_02/stspr37b.c',
    'src/saturn/stage_02/stanim38.c',
    'src/saturn/stage_02/stdat38.c',
    'src/saturn/stage_02/stbank29.c',
    'src/saturn/stage_02/stent11.c',
    'src/saturn/stage_02/stsa38.c',
    'src/saturn/stage_02/stspr38.c',
    'src/saturn/stage_02/stfrm38a.c',
    'src/saturn/stage_02/stfp38.c',
    'src/saturn/stage_02/stspr38b.c',
    'src/saturn/stage_02/stbank30.c',
    'src/saturn/stage_02/stent14.c',
    'src/saturn/stage_02/stsa40.c',
    'src/saturn/stage_02/stspr40.c',
    'src/saturn/stage_02/stfrm40.c',
    'src/saturn/stage_02/stfp40.c',
    'src/saturn/stage_02/stspr40b.c',
    'src/saturn/stage_02/stbank31.c',
    'src/saturn/stage_02/stent13.c',
    'src/saturn/stage_02/stsa42.c',
    'src/saturn/stage_02/stspr42.c',
    'src/saturn/stage_02/stfrm42.c',
    'src/saturn/stage_02/stfp42.c',
    'src/saturn/stage_02/stspr42b.c',
    'src/saturn/stage_02/stbank32.c',
    'src/saturn/stage_02/stent12.c',
    'src/saturn/stage_02/stsa45.c',
    'src/saturn/stage_02/stspr45.c',
    'src/saturn/stage_02/stfrm45.c',
    'src/saturn/stage_02/stfp45.c',
    'src/saturn/stage_02/stspr45b.c',
    'src/saturn/stage_02/stbank33.c',
    'src/saturn/stage_02/stent10.c',
    'src/saturn/stage_02/stdat48.c',
    'src/saturn/stage_02/stspr48.c',
    'src/saturn/stage_02/stfrm48.c',
    'src/saturn/stage_02/stfp48.c',
    'src/saturn/stage_02/stspr48b.c',
    'src/saturn/t_bat.c',
    'src/saturn/t_bat/bathead.c',
    'src/saturn/t_bat/batmeta.c',
    'src/saturn/t_bat/sprdata.c',
    'src/saturn/t_bat/sprbank.c',
    'src/saturn/t_bat/batgfx.c',
    'src/saturn/t_bat/batanim.c',
    'src/saturn/t_bat/batstat.c',
    'src/saturn/t_bat/batevent.c',
    'src/saturn/t_bat/batbss.c',
    'src/saturn/warp.c',
    'src/saturn/warp/obtain.c',
    'src/saturn/warp/warpmid.c',
    'src/saturn/warp/rockspr.c',
    'src/saturn/warp/roomspr.c',
    'src/saturn/warp/header.c',
    'src/saturn/warp/locbank.c',
    'src/saturn/warp/sprbank.c',
    'src/saturn/warp/entupd.c',
    'src/saturn/warp/laydef.c',
    'src/saturn/warp/hlaydat.c',
    'src/saturn/warp/hempty.c',
    'src/saturn/warp/vlaydat.c',
    'src/saturn/warp/vempty.c',
    'src/saturn/warp/layres.c',
    'src/saturn/warp/roomtbl.c',
    'src/saturn/warp/lookup.c',
    'src/saturn/warp/locent.c',
    'src/saturn/warp/state.c',
    'src/saturn/warp/collect.c',
    'src/saturn/warp/entstd.c',
    'src/saturn/warp/prizecfg.c',
    'src/saturn/warp/relicdat.c',
    'src/saturn/warp/reddoor.c',
    'src/saturn/warp/expldat.c',
    'src/saturn/warp/effect.c',
    'src/saturn/warp/particle.c',
    'src/saturn/maria.c',
    'src/saturn/maria/header.c',
    'src/saturn/maria/hdrstub.c',
    'src/saturn/maria/colpal.c',
    'src/saturn/maria/statefx.c',
    'src/saturn/maria/sensors.c',
    'src/saturn/maria/bpdefs.c',
    'src/saturn/maria/effects.c',
    'src/saturn/maria/blink.c',
    'src/saturn/maria/ring.c',
    'src/saturn/maria/ice.c',
    'src/saturn/maria/light.c',
    'src/saturn/maria/anims.c',
    'src/saturn/maria/hitboxes.c',
    'src/saturn/maria/palette.c',
    'src/saturn/maria/frames.c',
    'src/saturn/maria/images.c',
    'src/saturn/maria/sprpkg1.c',
    'src/saturn/maria/sprpkg2.c',
    'src/saturn/maria/sprpkg3.c',
    'src/saturn/maria/sprpkg4.c',
    'src/saturn/maria/sprpkg5.c',
    'src/saturn/maria/sprpkg6.c',
    'src/saturn/maria/sprpkg7.c',
    'src/saturn/maria/sprpkg8.c',
    'src/saturn/maria/sprpkg9.c',
    'src/saturn/maria/sprpkg10.c',
    'src/saturn/maria/sprpkg11.c',
    'src/saturn/maria/sprpkg12.c',
    'src/saturn/maria/resarray.c',
    'src/saturn/maria/sprbanks.c',
    'src/saturn/maria/gfxloads.c',
    'src/saturn/maria/ent87dat.c',
    'src/saturn/maria/subwpdat.c',
    'src/saturn/maria/entanims.c',
    'src/saturn/maria/enddata.c',
    'src/saturn/maria/castmap.c',
    'src/saturn/maria/mapcmd.c',
    'src/saturn/maria/mapui.c',
    'src/saturn/maria/deathgfx.c',
    'src/saturn/maria/coffsyms.c',
]

lib_srcs = [
    'src/saturn/lib/bup.c',
    'src/saturn/lib/cdc.c',
    'src/saturn/lib/csh.c',
    'src/saturn/lib/dma/dma_cpum.c',
    'src/saturn/lib/dma/dma_scu1.c',
    'src/saturn/lib/dma/dma_scu0.c',
    'src/saturn/lib/dma/dma_cpu0.c',
    'src/saturn/lib/gfs.c',
    'src/saturn/lib/mth.c',
    'src/saturn/lib/int.c',
    'src/saturn/lib/per.c',
    'src/saturn/lib/scl.c',
    'src/saturn/lib/spr/spr_1c.c',
    'src/saturn/lib/spr/spr_2c.c',
    'src/saturn/lib/spr/spr_slv.c',
    'src/saturn/lib/sys.c',
    'src/saturn/lib/sys_bss.c',
    'src/saturn/lib/sys_tail.c',
]

asm_srcs = [
    'src/saturn/lib/mth/mth_fixd.s',
    'src/saturn/lib/mth/mth_mtrx.s',
    'src/saturn/lib/mth/mth_ps2d.s',
    'src/saturn/lib/mth/mth_tri.s',
    'src/saturn/lib/spr/spr_2a.s',
    'src/saturn/lib/sys/sys_mac1.s',
]

# O0 srcs
add_srcs(lib_srcs, "build/saturn", "O0")

add_srcs(snd_srcs, "build/saturn", "O2")

def elf_srcs(srcs, output_dir):
    for src in srcs:
        filename_without_extension = os.path.splitext(os.path.basename(src))[0]
        relative_path = os.path.relpath(src, 'src/saturn')
        obj_dir = os.path.join(output_dir, os.path.dirname(relative_path))
        input_name = os.path.join(obj_dir, f"{filename_without_extension}.cof")
        obj_name = os.path.join(obj_dir, f"{filename_without_extension}.o")
        ninja.build(
            obj_name, 
            'coff2elf', 
            inputs=[input_name])

elf_srcs(snd_srcs, "build/saturn")
elf_srcs(lib_srcs, "build/saturn")

def add_asm_srcs(srcs, output_dir):
    for src in srcs:
        filename_without_extension = os.path.splitext(os.path.basename(src))[0]
        relative_path = os.path.relpath(src, 'src/saturn')
        obj_dir = os.path.join(output_dir, os.path.dirname(relative_path))
        cof_name = os.path.join(obj_dir, f"{filename_without_extension}.cof")
        obj_name = os.path.join(obj_dir, f"{filename_without_extension}.o")
        ninja.build(cof_name, 'as', inputs=[src])
        ninja.build(obj_name, 'coff2elf', inputs=[cof_name])

add_asm_srcs(asm_srcs, "build/saturn")

def inherited_symbol_files(target):
    files = ['config/saturn/zero_syms.txt']
    if target != 'zero':
        files.append('config/saturn/game_syms.txt')
        files.append('config/saturn/game_user_syms.txt')
    files.append('config/saturn/zero_user_syms.txt')
    if target not in {'zero', 'game'}:
        files.append(f'config/saturn/{target}_user_syms.txt')
    return files

def target_alias_options(target):
    aliases = {
        'game': {'_func_80131F68_1': 0x06012DD0},
        'stage_02': {'_AnimateEntity': 0x0607B618},
        't_bat': {'_func_80131F68_2': 0x06012DFC},
    }
    return ' '.join(
        f'--defsym {name}=0x{address:08X}'
        for name, address in aliases.get(target, {}).items()
    )

def link_objs(srcs, output_dir):
    for src in srcs:
        filename_without_extension = os.path.splitext(os.path.basename(src))[0]
        obj_name = f"{output_dir}/{filename_without_extension}.o"
        elf_name = f"{output_dir}/{filename_without_extension}.elf"
        ld_file = f'{filename_without_extension}.ld'
        symbol_files = inherited_symbol_files(filename_without_extension)

        ninja.build(
            elf_name, 
            'link', 
            inputs=[obj_name],
            implicit=[SYMBOL_OWNERSHIP_STAMP,
                      f'config/saturn/{ld_file}'] + symbol_files,
            variables={
                'ld_file': ld_file,
                'symbol_scripts': ' '.join(
                    f'-T {symbol_file}' for symbol_file in symbol_files),
                'target_aliases': target_alias_options(
                    filename_without_extension)})

objs = []

link_objs(objs, 'build/saturn')

def link_multi(multi_objs, output_dir):
    for main_obj, sub_objs in multi_objs.items():
        filename_without_extension = os.path.splitext(os.path.basename(main_obj))[0]
        elf_name = f"{output_dir}/{filename_without_extension}.elf"
        ld_file = f'{filename_without_extension}.ld'
        symbol_files = inherited_symbol_files(filename_without_extension)

        ninja.build(
            elf_name, 
            'link_multi', 
            inputs=[main_obj],
            implicit=[x for x in sub_objs if x] +
                     [SYMBOL_OWNERSHIP_STAMP,
                      f'config/saturn/{ld_file}'] + symbol_files,
            variables={
                'ld_file': ld_file,
                'symbol_scripts': ' '.join(
                    f'-T {symbol_file}' for symbol_file in symbol_files),
                'target_aliases': target_alias_options(
                    filename_without_extension),
                'objs': sub_objs})

multi_objs = {
    'build/saturn/alucard.o' : [
        'build/saturn/alucard/header.o',
        'build/saturn/alucard/hdrstub.o',
    ],
    'build/saturn/maria.o' : [
        'build/saturn/maria/header.o',
        'build/saturn/maria/hdrstub.o',
        'build/saturn/maria/colpal.o',
        'build/saturn/maria/statefx.o',
        'build/saturn/maria/sensors.o',
        'build/saturn/maria/bpdefs.o',
        'build/saturn/maria/effects.o',
        'build/saturn/maria/blink.o',
        'build/saturn/maria/ring.o',
        'build/saturn/maria/ice.o',
        'build/saturn/maria/light.o',
        'build/saturn/maria/anims.o',
        'build/saturn/maria/hitboxes.o',
        'build/saturn/maria/palette.o',
        'build/saturn/maria/frames.o',
        'build/saturn/maria/images.o',
        'build/saturn/maria/sprpkg1.o',
        'build/saturn/maria/sprpkg2.o',
        'build/saturn/maria/sprpkg3.o',
        'build/saturn/maria/sprpkg4.o',
        'build/saturn/maria/sprpkg5.o',
        'build/saturn/maria/sprpkg6.o',
        'build/saturn/maria/sprpkg7.o',
        'build/saturn/maria/sprpkg8.o',
        'build/saturn/maria/sprpkg9.o',
        'build/saturn/maria/sprpkg10.o',
        'build/saturn/maria/sprpkg11.o',
        'build/saturn/maria/sprpkg12.o',
        'build/saturn/maria/resarray.o',
        'build/saturn/maria/sprbanks.o',
        'build/saturn/maria/gfxloads.o',
        'build/saturn/maria/ent87dat.o',
        'build/saturn/maria/subwpdat.o',
        'build/saturn/maria/entanims.o',
        'build/saturn/maria/enddata.o',
        'build/saturn/maria/castmap.o',
        'build/saturn/maria/mapcmd.o',
        'build/saturn/maria/mapui.o',
        'build/saturn/maria/deathgfx.o',
        'build/saturn/maria/coffsyms.o',
    ],
    'build/saturn/stage_02.o' : [
        'build/saturn/stage_02/sthead.o',
        'build/saturn/stage_02/stprolo.o',
        'build/saturn/stage_02/stbrkgfx.o',
        'build/saturn/stage_02/stglobe.o',
        'build/saturn/stage_02/stlife.o',
        'build/saturn/stage_02/stblue.o',
        'build/saturn/stage_02/stsubgfx.o',
        'build/saturn/stage_02/stelevgf.o',
        'build/saturn/stage_02/st74gfx.o',
        'build/saturn/stage_02/stmargfx.o',
        'build/saturn/stage_02/stsprbnk.o',
        'build/saturn/stage_02/stentupd.o',
        'build/saturn/stage_02/sthlay.o',
        'build/saturn/stage_02/stvlay.o',
        'build/saturn/stage_02/stprize.o',
        'build/saturn/stage_02/sthlaydt.o',
        'build/saturn/stage_02/stvlaydt.o',
        'build/saturn/stage_02/stlayer.o',
        'build/saturn/stage_02/strmgfx.o',
        'build/saturn/stage_02/stprops.o',
        'build/saturn/stage_02/strooms.o',
        'build/saturn/stage_02/stbreak.o',
        'build/saturn/stage_02/stent00.o',
        'build/saturn/stage_02/stent08.o',
        'build/saturn/stage_02/stcont.o',
        'build/saturn/stage_02/stpuff.o',
        'build/saturn/stage_02/stent01.o',
        'build/saturn/stage_02/stsubwp.o',
        'build/saturn/stage_02/stent15.o',
        'build/saturn/stage_02/stent20.o',
        'build/saturn/stage_02/stent02.o',
        'build/saturn/stage_02/stwalls.o',
        'build/saturn/stage_02/stent16.o',
        'build/saturn/stage_02/stent21.o',
        'build/saturn/stage_02/stent22.o',
        'build/saturn/stage_02/stcutdat.o',
        'build/saturn/stage_02/stent17.o',
        'build/saturn/stage_02/stcutst.o',
        'build/saturn/stage_02/stcutsc.o',
        'build/saturn/stage_02/stcuttrl.o',
        'build/saturn/stage_02/stent03.o',
        'build/saturn/stage_02/stmaria.o',
        'build/saturn/stage_02/stlookup.o',
        'build/saturn/stage_02/stprcfg.o',
        'build/saturn/stage_02/stgold.o',
        'build/saturn/stage_02/stprzan.o',
        'build/saturn/stage_02/stent04.o',
        'build/saturn/stage_02/stent09.o',
        'build/saturn/stage_02/stexpl.o',
        'build/saturn/stage_02/stent05.o',
        'build/saturn/stage_02/stent06.o',
        'build/saturn/stage_02/stent07.o',
        'build/saturn/stage_02/st3dco.o',
        'build/saturn/stage_02/st3didx.o',
        'build/saturn/stage_02/stent18.o',
        'build/saturn/stage_02/stdata37.o',
        'build/saturn/stage_02/stbank28.o',
        'build/saturn/stage_02/stent19.o',
        'build/saturn/stage_02/stdata38.o',
        'build/saturn/stage_02/stspr37.o',
        'build/saturn/stage_02/stfrm38.o',
        'build/saturn/stage_02/stspr37b.o',
        'build/saturn/stage_02/stanim38.o',
        'build/saturn/stage_02/stdat38.o',
        'build/saturn/stage_02/stbank29.o',
        'build/saturn/stage_02/stent11.o',
        'build/saturn/stage_02/stsa38.o',
        'build/saturn/stage_02/stspr38.o',
        'build/saturn/stage_02/stfrm38a.o',
        'build/saturn/stage_02/stfp38.o',
        'build/saturn/stage_02/stspr38b.o',
        'build/saturn/stage_02/stbank30.o',
        'build/saturn/stage_02/stent14.o',
        'build/saturn/stage_02/stsa40.o',
        'build/saturn/stage_02/stspr40.o',
        'build/saturn/stage_02/stfrm40.o',
        'build/saturn/stage_02/stfp40.o',
        'build/saturn/stage_02/stspr40b.o',
        'build/saturn/stage_02/stbank31.o',
        'build/saturn/stage_02/stent13.o',
        'build/saturn/stage_02/stsa42.o',
        'build/saturn/stage_02/stspr42.o',
        'build/saturn/stage_02/stfrm42.o',
        'build/saturn/stage_02/stfp42.o',
        'build/saturn/stage_02/stspr42b.o',
        'build/saturn/stage_02/stbank32.o',
        'build/saturn/stage_02/stent12.o',
        'build/saturn/stage_02/stsa45.o',
        'build/saturn/stage_02/stspr45.o',
        'build/saturn/stage_02/stfrm45.o',
        'build/saturn/stage_02/stfp45.o',
        'build/saturn/stage_02/stspr45b.o',
        'build/saturn/stage_02/stbank33.o',
        'build/saturn/stage_02/stent10.o',
        'build/saturn/stage_02/stdat48.o',
        'build/saturn/stage_02/stspr48.o',
        'build/saturn/stage_02/stfrm48.o',
        'build/saturn/stage_02/stfp48.o',
        'build/saturn/stage_02/stspr48b.o',
    ],
    'build/saturn/t_bat.o' : [
        'build/saturn/t_bat/bathead.o',
        'build/saturn/t_bat/batmeta.o',
        'build/saturn/t_bat/sprdata.o',
        'build/saturn/t_bat/sprbank.o',
        'build/saturn/t_bat/batgfx.o',
        'build/saturn/t_bat/batanim.o',
        'build/saturn/t_bat/batstat.o',
        'build/saturn/t_bat/batevent.o',
        'build/saturn/t_bat/batbss.o',
    ],
    'build/saturn/richter.o' : [
        'build/saturn/ric/header.o',
        'build/saturn/ric/hdrstub.o',
        'build/saturn/ric/d54568.o',
        'build/saturn/ric/gprolog.o',
        'build/saturn/ric/timers.o',
        'build/saturn/ric/sensors.o',
        'build/saturn/ric/subwdata.o',
        'build/saturn/ric/bpdefs.o',
        'build/saturn/ric/anims.o',
        'build/saturn/ric/hitboxes.o',
        'build/saturn/ric/sprpal1.o',
        'build/saturn/ric/sprfrm1.o',
        'build/saturn/ric/sprimg1.o',
        'build/saturn/ric/sprpkg2.o',
        'build/saturn/ric/sprpkg3.o',
        'build/saturn/ric/sprpkg4.o',
        'build/saturn/ric/sprpkg5.o',
        'build/saturn/ric/sprpkg6.o',
        'build/saturn/ric/sprpkg7.o',
        'build/saturn/ric/sprpkg8.o',
        'build/saturn/ric/sprpkg9.o',
        'build/saturn/ric/sprpkg10.o',
        'build/saturn/ric/sprres.o',
        'build/saturn/ric/gfxloads.o',
        'build/saturn/ric/whipdata.o',
        'build/saturn/ric/whipdat.o',
        'build/saturn/ric/vibanim.o',
        'build/saturn/ric/subwpfx.o',
        'build/saturn/ric/hwdata.o',
        'build/saturn/ric/crossdat.o',
        'build/saturn/ric/castmap.o',
        'build/saturn/ric/mapcmd.o',
        'build/saturn/ric/mapui.o',
        'build/saturn/ric/deathgfx.o',
        'build/saturn/ric/coffres.o',
        'build/saturn/ric/rictail.o',
        'build/saturn/ric/rictl2.o',
    ],
    'build/saturn/game.o' : [
        'build/saturn/game/header.o',
        'build/saturn/game/hdrstub.o',
        'build/saturn/game_2a.o',
        'build/saturn/game/statlbl.o',
        'build/saturn/game_2b.o',
        'build/saturn/game_0.o',
        'build/saturn/game/savemsg.o',
        'build/saturn/game_1.o',
        'build/saturn/game_3a.o',
        'build/saturn/game/primuv.o',
        'build/saturn/game_3b.o',
        'build/saturn/game/cfgjp.o',
        'build/saturn/game/cfgstr.o',
        'build/saturn/game/cfgrw1.o',
        'build/saturn/game/cfgrw1b.o',
        'build/saturn/game/cfgrw1c.o',
        'build/saturn/game/cfgrw1d.o',
        'build/saturn/game/jewel.o',
        'build/saturn/game/cfgrw4.o',
        'build/saturn/game/btnmask.o',
        'build/saturn/game/cfgrw2.o',
        'build/saturn/game/lvlhp.o',
        'build/saturn/game/cfgrw3.o',
        'build/saturn/game/mnstate.o',
        'build/saturn/game/cfgrw5.o',
        'build/saturn/game/eqhelp.o',
        'build/saturn/game/mnscroll.o',
        'build/saturn/game/cfgrest.o',
        'build/saturn/game/capetbl.o',
        'build/saturn/game/capepal.o',
        'build/saturn/game/miscend.o',
        'build/saturn/game/sinetbl.o',
    ],
    'build/saturn/warp.o' : [
        'build/saturn/warp/obtain.o',
        'build/saturn/warp/warpmid.o',
        'build/saturn/warp/rockspr.o',
        'build/saturn/warp/roomspr.o',
        'build/saturn/warp/header.o',
        'build/saturn/warp/locbank.o',
        'build/saturn/warp/sprbank.o',
        'build/saturn/warp/entupd.o',
        'build/saturn/warp/laydef.o',
        'build/saturn/warp/hlaydat.o',
        'build/saturn/warp/hempty.o',
        'build/saturn/warp/vlaydat.o',
        'build/saturn/warp/vempty.o',
        'build/saturn/warp/layres.o',
        'build/saturn/warp/roomtbl.o',
        'build/saturn/warp/lookup.o',
        'build/saturn/warp/locent.o',
        'build/saturn/warp/state.o',
        'build/saturn/warp/collect.o',
        'build/saturn/warp/entstd.o',
        'build/saturn/warp/prizecfg.o',
        'build/saturn/warp/relicdat.o',
        'build/saturn/warp/reddoor.o',
        'build/saturn/warp/expldat.o',
        'build/saturn/warp/effect.o',
        'build/saturn/warp/particle.o',
    ],
    'build/saturn/zero.o' : [
        'build/saturn/lib/snd.o',
        'build/saturn/zero_2.o',
        'build/saturn/zero_3.o',
        'build/saturn/lib/bup.o',
        'build/saturn/lib/cdc.o',
        'build/saturn/lib/csh.o',
        'build/saturn/lib/dma/dma_cpum.o',
        'build/saturn/lib/dma/dma_scu1.o',
        'build/saturn/lib/dma/dma_scu0.o',
        'build/saturn/lib/dma/dma_cpu0.o',
        'build/saturn/lib/gfs.o',
        'build/saturn/lib/mth/mth_fixd.o',
        'build/saturn/lib/mth/mth_mtrx.o',
        'build/saturn/lib/mth/mth_ps2d.o',
        'build/saturn/lib/mth/mth_tri.o',
        'build/saturn/lib/mth.o',
        'build/saturn/lib/int.o',
        'build/saturn/lib/per.o',
        'build/saturn/lib/scl.o',
        'build/saturn/lib/spr/spr_1c.o',
        'build/saturn/lib/spr/spr_2c.o',
        'build/saturn/lib/spr/spr_slv.o',
        'build/saturn/lib/spr/spr_2a.o',
        'build/saturn/lib/sys/sys_mac1.o',
        'build/saturn/lib/sys.o',
        'build/saturn/lib/sys_bss.o',
        'build/saturn/zero/snddata.o',
        'build/saturn/zero/adpcm.o',
        'build/saturn/zero/sndlut.o',
        'build/saturn/zero/sndcmd.o',
        'build/saturn/zero/stgspr0.o',
        'build/saturn/zero/stgspr1.o',
        'build/saturn/zero/stgspr2.o',
        'build/saturn/zero/stgspr3.o',
        'build/saturn/zero/stgspr4.o',
        'build/saturn/zero/stgspr5.o',
        'build/saturn/zero/stgspr6.o',
        'build/saturn/zero/stgspr7.o',
        'build/saturn/zero/stgspr8.o',
        'build/saturn/zero/stgspr9.o',
        'build/saturn/zero/stgspr10.o',
        'build/saturn/zero/stgspr11.o',
        'build/saturn/zero/stgspr12.o',
        'build/saturn/zero/stgspr13.o',
        'build/saturn/zero/stgspr14.o',
        'build/saturn/zero/fontmap.o',
        'build/saturn/zero/stgfiles.o',
        'build/saturn/zero/sysflag.o',
        'build/saturn/lib/spr/spr_data.o',
        'build/saturn/lib/sys_tail.o',
    ]
}

link_multi(multi_objs, 'build/saturn')

ninja.rule('elf2prg',
           command="sh-elf-objcopy -O binary $in $out",
           description='Converting $out from $in')

ninja.rule('elf2prg_fixed',
           command="sh-elf-objcopy -O binary $in $out && truncate -c -s $size $out",
           description='Converting fixed-size $out from $in')

prgs = {
    'zero.elf': '0.BIN',
    'game.elf': 'GAME.PRG',
    'alucard.elf': 'ALUCARD.PRG',
    'richter.elf': 'RICHTER.PRG',
    'stage_02.elf': 'STAGE_02.PRG',
    'warp.elf': 'WARP.PRG',
    't_bat.elf': 'T_BAT.PRG',
    'maria.elf': 'MARIA.PRG'
}

def make_prgs(prgs, output_dir):
    for elf, prg in prgs.items():
        if prg == 'T_BAT.PRG':
            ninja.build(
                f"{output_dir}/{prg}",
                'elf2prg_fixed',
                inputs=[f"{output_dir}/{elf}"],
                variables={'size': 0x7000})
            continue
        ninja.build(
            f"{output_dir}/{prg}",
            'elf2prg',
            inputs=[f"{output_dir}/{elf}"])

make_prgs(prgs, 'build/saturn')

ninja.close()
