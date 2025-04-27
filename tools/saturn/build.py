# usage
# python3 ./tools/saturn/build.py && ninja -j1

import ninja_syntax
import os
import shutil

# write out current pwd to open it as a disk
with open('./tools/saturn/.dosemurc', 'w') as f:
    f.write(f'$_hdimage = \'+0 {os.getcwd()} +1\'\n')

# copy cygnus into a 8.3 folder
if not os.path.exists('tools/saturn/GCCSH'):
    shutil.copytree('bin/cygnus-2.7-96Q3-bin', 'tools/saturn/GCCSH')

ninja = ninja_syntax.Writer(open("build.ninja", "w"))

ninja.rule('compile',
           command='sh ./tools/saturn/dosemu_wrapper.sh $in $out',
           description='Building $out from $in')

ninja.rule(
        'check',
        command='sha1sum --check config/check.saturn.sha',
        description='Checking that $in matches')

def add_srcs(srcs, output_dir):
    for src in srcs:
        filename_without_extension = os.path.splitext(os.path.basename(src))[0]
        relative_path = os.path.relpath(src, 'src/saturn')
        obj_dir = os.path.join(output_dir, os.path.dirname(relative_path))
        obj_name = os.path.join(obj_dir, f"{filename_without_extension}.cof")
        os.makedirs(os.path.dirname(obj_name), exist_ok=True)

        ninja.build(
            obj_name, 
            'compile', 
            inputs=[src])

ninja.rule('coff2elf',
           command="sh-elf-objcopy -Icoff-sh -Oelf32-sh $in $out",
           description='Converting $out from $in')

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

snd_srcs = [
    # 'src/saturn/alucard.c',
    'src/saturn/zero.c',
    # 'src/saturn/game.c',
    'src/saturn/lib/bup.c',
    'src/saturn/lib/cdc.c',
    'src/saturn/lib/csh.c',
    'src/saturn/lib/dma.c',
    'src/saturn/lib/gfs.c',
    'src/saturn/lib/mth.c',
    'src/saturn/lib/per.c',
    'src/saturn/lib/scl.c',
    'src/saturn/lib/spr.c',
    'src/saturn/lib/sys.c',
    # 'src/saturn/richter.c',
    # 'src/saturn/stage_02.c',
    # 'src/saturn/t_bat.c',
    # 'src/saturn/warp.c',
]

add_srcs(snd_srcs, "build/saturn")

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

# objs = [
#     'build/saturn/game.o',
#     'build/saturn/alucard.o',
#     'build/saturn/richter.o',
#     'build/saturn/stage_02.o',
#     'build/saturn/warp.o',
#     'build/saturn/t_bat.o'
# ]

# link_objs(objs, 'build/saturn')

def link_multi(multi_objs, output_dir):
    for main_obj, sub_objs in multi_objs.items():
        filename_without_extension = os.path.splitext(os.path.basename(main_obj))[0]
        elf_name = f"{output_dir}/{filename_without_extension}.elf"
        ld_file = f'{filename_without_extension}.ld'
        syms_file = f'{filename_without_extension}_user_syms.txt'

        # all_objs = [main_obj] + sub_objs

        # print(all_objs)

        ninja.build(
            elf_name, 
            'link_multi', 
            inputs=[main_obj],
            variables={
                'ld_file': ld_file,
                'syms_file': syms_file,
                'objs': sub_objs})

multi_objs = {
    'build/saturn/zero.o' : [
        'build/saturn/lib/bup.o',
        'build/saturn/lib/cdc.o',
        'build/saturn/lib/csh.o',
        'build/saturn/lib/dma.o',
        'build/saturn/lib/gfs.o',
        'build/saturn/lib/mth.o',
        'build/saturn/lib/per.o',
        'build/saturn/lib/scl.o',
        'build/saturn/lib/spr.o',
        'build/saturn/lib/sys.o',
    ]
}

link_multi(multi_objs, 'build/saturn')

ninja.rule('elf2prg',
           command="sh-elf-objcopy -O binary $in $out",
           description='Converting $out from $in')

prgs = {
    'zero.elf': '0.BIN',
    # 'game.elf': 'GAME.PRG',
    # 'alucard.elf': 'ALUCARD.PRG',
    # 'richter.elf': 'RICHTER.PRG',
    # 'stage_02.elf': 'STAGE_02.PRG',
    # 'warp.elf': 'WARP.PRG',
    # 't_bat.elf': 'T_BAT.PRG'
}

def make_prgs(prgs, output_dir):
    for elf, prg in prgs.items():
        ninja.build(
            f"{output_dir}/{prg}",
            'elf2prg',
            inputs=[f"{output_dir}/{elf}"])

make_prgs(prgs, 'build/saturn')

ninja.close()
