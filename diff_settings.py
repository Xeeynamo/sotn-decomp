#!/usr/bin/env python3

def add_custom_arguments(parser):
    parser.add_argument(
        "--version",
        default="us",
        dest='version',
        help="Decide what version of the game to use (us, jp12, pspeu, etc.)",
    )
    parser.add_argument(
        "--overlay",
        default="dra",
        dest='overlay',
        help="Defines which overlay to use for the diff (main, dra, st/mad, etc.)",
    )


def apply_base(config, version, name):
    config['baseimg'] = f'disks/{version}' + (f'{name}.bin').upper()
    config['myimg'] = f'build/{version}' + (f'{name}.bin').upper()
    config['mapfile'] = f'build/{version}/{name}.map'
    config['source_directories'] = [
        f'src/{name}', 'include', f'asm/{version}/{name}']
    config['objdump_executable'] = 'mipsel-linux-gnu-objdump'


def apply_bin(config, version, name):
    config["arch"] = "mipsel"
    config['baseimg'] = f'disks/{version}' + (f'BIN/{name}.BIN').upper()
    config['myimg'] = f'build/{version}' + (f'{name}.bin').upper()
    config['mapfile'] = f'build/{version}/{name}.map'
    config['source_directories'] = [
        f'src/{name}', 'include', f'asm/{version}/{name}']
    config['objdump_executable'] = 'mipsel-linux-gnu-objdump'


def apply_servant(config, version, name):
    config["arch"] = "mipsel"
    config['baseimg'] = f'disks/{version}' + (f'SERVANT/{name}.bin').upper()
    config['myimg'] = f'build/{version}' + (f'{name}.bin').upper()
    config['mapfile'] = f'build/{version}/{name}.map'
    config['source_directories'] = [
        f'src/servant/{name}', 'include', f'asm/{version}/servant/{name}']
    config['objdump_executable'] = 'mipsel-linux-gnu-objdump'


def apply_stage(config, version, name):
    config["arch"] = "mipsel"
    config['baseimg'] = f'disks/{version}' + (f'ST/{name}/{name}.BIN').upper()
    config['myimg'] = f'build/{version}' + (f'{name}.bin').upper()
    config['mapfile'] = f'build/{version}/st{name}.map'
    config['source_directories'] = [
        f'src/st/{name}', 'include', f'asm/{version}/st/{name}']
    config['objdump_executable'] = 'mipsel-linux-gnu-objdump'


def apply(config, args):
    name = args.overlay or 'dra'
    version = args.version or 'us'
    if name.startswith("st/"):
        apply_stage(config, version, name[3:])
    elif name.startswith("tt_"):
        apply_servant(config, version, name)
    elif name is "dra" or name is "main":
        apply_base(config, version, name)
    else:
        apply_bin(config, version, name)

    config["arch"] = "mipsel"
    config['objdump_executable'] = 'mipsel-linux-gnu-objdump'
