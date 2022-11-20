#!/usr/bin/env python3

def add_custom_arguments(parser):
    parser.add_argument(
        "--overlay",
        default="dra",
        dest='overlay',
        help="Defines which overlay to use for the diff (main, dra, st/mad, etc.)",
    )

def apply(config, args):
    overlay = args.overlay or 'dra'
    isMapOverlay = overlay.startswith("st/")
    name = overlay[3:] if isMapOverlay else overlay
    longname = f'st{overlay[3:]}' if isMapOverlay else overlay

    if isMapOverlay:
        config['baseimg'] = 'iso/' + (f'ST/{name}/{name}.BIN').upper()
    else:
        config['baseimg'] = 'iso/' + (f'{name}.BIN').upper()

    config["arch"] = "mipsel"
    config['myimg'] = 'build/' + (f'{name}.bin').upper()
    config['mapfile'] = f'build/{longname}.map'
    config['source_directories'] = [f'src/{overlay}', 'include', f'asm/{overlay}']
