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

ninja.pool('dosemu_pool', 1)

ninja.rule('compile',
           command='sh ./tools/builds/dosemu_wrapper.sh $in $out $args $tmpdir',
           description='Building $out from $in',
           pool='dosemu_pool')

ninja.rule(
        'check',
        command='.venv/bin/python3 tools/builds/check.py config/check.saturn.sha',
        description='Checking that $in matches')

ninja.rule('coff2elf',
           command="sh-elf-objcopy -Icoff-sh -Oelf32-sh $in $out",
           description='Converting $out from $in')

ninja.rule('cargo_sotn_str',
           command='cargo build --release --manifest-path tools/sotn_str/Cargo.toml',
           description='Building tools/sotn_str/target/release/sotn_str')

ninja.build(
    'tools/sotn_str/target/release/sotn_str',
    'cargo_sotn_str',
    inputs=[
        'tools/sotn_str/Cargo.toml',
        'tools/sotn_str/Cargo.lock',
        'tools/sotn_str/src/main.rs',
    ])

ninja.rule('link',
           command= 'sh-elf-ld -verbose --no-check-sections -nostdlib \
                    -o $out \
                    -Map $out.map \
                    -T config/saturn/$ld_file \
                    -T config/saturn/zero_syms.txt \
                    -T config/saturn/game_syms.txt \
                    -T config/saturn/$syms_file \
                    $in',
           description='Linking $out from $in')

ninja.rule('link_multi',
           command= 'sh-elf-ld -verbose --no-check-sections -nostdlib \
                    -o $out \
                    -Map $out.map \
                    -T config/saturn/$ld_file \
                    -T config/saturn/zero_syms.txt \
                    -T config/saturn/game_syms.txt \
                    -T config/saturn/$syms_file \
                    $in $objs',
           description='Linking $out from $in')

ninja.rule('cpp',
           command='cpp $FLAGS $in > $out',
           description='Running preprocessor on $out from $in')

ninja.rule('sotn_str',
           command='tools/sotn_str/target/release/sotn_str process < $in > $out',
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

        flags = '-lang-c -v -I./src/saturn -I./src/saturn/lib -undef -D__GNUC__=2 -D__GNUC_MINOR__=7 -D__sh__ -D__sh__ -D__sh2__'

        ninja.build(
            pre_name,
            'cpp',
            inputs=[src],
            variables={'FLAGS': flags})

        ninja.build(
            str_name,
            'sotn_str',
            inputs=[pre_name],
            implicit=['tools/sotn_str/target/release/sotn_str'])

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
    'src/saturn/zero.c',
    'src/saturn/lib/snd.c',
    'src/saturn/zero_2.c',
    'src/saturn/game_0.c',
    'src/saturn/game_1.c',
    'src/saturn/game_3.c',
    'src/saturn/game.c',
    'src/saturn/game_2.c',
    'src/saturn/game/header.c',
    'src/saturn/game/hdrstub.c',
    'src/saturn/game/savemsg.c',
    'src/saturn/game/cfgjp.c',
    'src/saturn/game/cfgstr.c',
    'src/saturn/game/cfgrw1.c',
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
    'src/saturn/game/joseph.c',
    'src/saturn/game/capecon.c',
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
    'src/saturn/ric/anims.c',
    'src/saturn/ric/c2f40.c',
    'src/saturn/ric/whipdat.c',
    'src/saturn/ric/globdat.c',
    'src/saturn/ric/savevar.c',
    'src/saturn/ric/ptrtbl.c',
    'src/saturn/ric/rictail.c',
    'src/saturn/ric/rictl2.c',
    'src/saturn/ric/rictl3.c',
    'src/saturn/ric/rictl4.c',
    'src/saturn/ric/rictl6.c',
    'src/saturn/ric/rictl7.c',
    'src/saturn/ric/rictl8.c',
    'src/saturn/ric/rictl9.c',
    'src/saturn/ric/rictl10.c',
    'src/saturn/stage_02.c',
    'src/saturn/t_bat.c',
    'src/saturn/warp.c',
    'src/saturn/maria.c'
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

def link_objs(srcs, output_dir):
    for src in srcs:
        filename_without_extension = os.path.splitext(os.path.basename(src))[0]
        obj_name = f"{output_dir}/{filename_without_extension}.o"
        elf_name = f"{output_dir}/{filename_without_extension}.elf"
        ld_file = f'{filename_without_extension}.ld'
        syms_file = f'{filename_without_extension}_user_syms.txt'

        ninja.build(
            elf_name, 
            'link', 
            inputs=[obj_name],
            variables={
                'ld_file': ld_file,
                'syms_file': syms_file})

objs = [
    'build/saturn/alucard.o',
    'build/saturn/stage_02.o',
    'build/saturn/warp.o',
    'build/saturn/t_bat.o',
    'build/saturn/maria.o'
]

link_objs(objs, 'build/saturn')

def link_multi(multi_objs, output_dir):
    for main_obj, sub_objs in multi_objs.items():
        filename_without_extension = os.path.splitext(os.path.basename(main_obj))[0]
        elf_name = f"{output_dir}/{filename_without_extension}.elf"
        ld_file = f'{filename_without_extension}.ld'
        syms_file = f'{filename_without_extension}_user_syms.txt'

        ninja.build(
            elf_name, 
            'link_multi', 
            inputs=[main_obj],
            implicit=[x for x in sub_objs if x],
            variables={
                'ld_file': ld_file,
                'syms_file': syms_file,
                'objs': sub_objs})

multi_objs = {
    'build/saturn/richter.o' : [
        'build/saturn/ric/header.o',
        'build/saturn/ric/hdrstub.o',
        'build/saturn/ric/d54568.o',
        'build/saturn/ric/gprolog.o',
        'build/saturn/ric/timers.o',
        'build/saturn/ric/sensors.o',
        'build/saturn/ric/anims.o',
        'build/saturn/ric/c2f40.o',
        'build/saturn/ric/whipdat.o',
        'build/saturn/ric/globdat.o',
        'build/saturn/ric/savevar.o',
        'build/saturn/ric/ptrtbl.o',
        'build/saturn/ric/rictail.o',
        'build/saturn/ric/rictl2.o',
        'build/saturn/ric/rictl3.o',
        'build/saturn/ric/rictl4.o',
        'build/saturn/ric/rictl6.o',
        'build/saturn/ric/rictl7.o',
        'build/saturn/ric/rictl8.o',
        'build/saturn/ric/rictl9.o',
        'build/saturn/ric/rictl10.o',
    ],
    'build/saturn/game.o' : [
        'build/saturn/game/header.o',
        'build/saturn/game/hdrstub.o',
        'build/saturn/game_2.o',
        'build/saturn/game_0.o',
        'build/saturn/game/savemsg.o',
        'build/saturn/game_1.o',
        'build/saturn/game_3.o',
        'build/saturn/game/cfgjp.o',
        'build/saturn/game/cfgstr.o',
        'build/saturn/game/cfgrw1.o',
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
        'build/saturn/game/joseph.o',
        'build/saturn/game/capecon.o',
        'build/saturn/game/capepal.o',
        'build/saturn/game/miscend.o',
        'build/saturn/game/sinetbl.o',
    ],
    'build/saturn/zero.o' : [
        'build/saturn/lib/snd.o',
        'build/saturn/zero_2.o',
        'build/saturn/lib/bup.o',
        'build/saturn/lib/cdc.o',
        'build/saturn/lib/csh.o',
        'build/saturn/lib/dma/dma_cpum.o',
        'build/saturn/lib/dma/dma_scu1.o',
        'build/saturn/lib/dma/dma_scu0.o',
        'build/saturn/lib/dma/dma_cpu0.o',
        'build/saturn/lib/gfs.o',
        'build/saturn/lib/mth.o',
        'build/saturn/lib/int.o',
        'build/saturn/lib/per.o',
        'build/saturn/lib/scl.o',
        'build/saturn/lib/spr/spr_1c.o',
        'build/saturn/lib/spr/spr_2c.o',
        'build/saturn/lib/spr/spr_slv.o',
        'build/saturn/lib/sys.o',
    ]
}

link_multi(multi_objs, 'build/saturn')

ninja.rule('elf2prg',
           command="sh-elf-objcopy -O binary $in $out",
           description='Converting $out from $in')

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
        ninja.build(
            f"{output_dir}/{prg}",
            'elf2prg',
            inputs=[f"{output_dir}/{elf}"])

make_prgs(prgs, 'build/saturn')

ninja.close()
