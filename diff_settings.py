#!/usr/bin/env python3

def add_custom_arguments(parser):
    parser.add_argument(
        "--overlay",
        default="dra",
        dest='overlay',
        help="Defines which overlay to use for the diff (main, dra, st/mad, etc.)",
    )


def apply_base(config, name):
    config['baseimg'] = 'iso/' + (f'{name}.bin').upper()
    config['myimg'] = 'build/' + (f'{name}.bin').upper()
    config['mapfile'] = f'build/{name}.map'
    config['source_directories'] = [
        f'src/{name}', 'include', f'asm/{name}']
    config['objdump_executable'] = 'mipsel-linux-gnu-objdump'


def apply_bin(config, name):
    config["arch"] = "mipsel"
    config['baseimg'] = 'iso/' + (f'BIN/{name}.BIN').upper()
    config['myimg'] = 'build/' + (f'{name}.bin').upper()
    config['mapfile'] = f'build/{name}.map'
    config['source_directories'] = [
        f'src/{name}', 'include', f'asm/{name}']
    config['objdump_executable'] = 'mipsel-linux-gnu-objdump'


def apply_servant(config, name):
    config["arch"] = "mipsel"
    config['baseimg'] = 'iso/' + (f'SERVANT/{name}.bin').upper()
    config['myimg'] = 'build/' + (f'{name}.bin').upper()
    config['mapfile'] = f'build/{name}.map'
    config['source_directories'] = [
        f'src/servant/{name}', 'include', f'asm/servant/{name}']
    config['objdump_executable'] = 'mipsel-linux-gnu-objdump'


def apply_stage(config, name):
    config["arch"] = "mipsel"
    config['baseimg'] = 'iso/' + (f'ST/{name}/{name}.BIN').upper()
    config['myimg'] = 'build/' + (f'{name}.bin').upper()
    config['mapfile'] = f'build/st{name}.map'
    config['source_directories'] = [
        f'src/st/{name}', 'include', f'asm/st/{name}']
    config['objdump_executable'] = 'mipsel-linux-gnu-objdump'


def apply(config, args):
    name = args.overlay or 'dra'
    if name.startswith("st/"):
        apply_stage(config, name[3:])
    elif name.startswith("tt_"):
        apply_servant(config, name)
    elif name is "dra" or name is "main":
        apply_base(config, name)
    else:
        apply_bin(config, name)

    config["arch"] = "mipsel"
    config['objdump_executable'] = 'mipsel-linux-gnu-objdump'
