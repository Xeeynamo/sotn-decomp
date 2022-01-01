#!/usr/bin/env python3

def apply(config, args):
    config["arch"] = "mipsel"
    config['baseimg'] = f'dra.bin'
    config['myimg'] = f'build/dra.bin'
    config['mapfile'] = f'build/dra.map'
    config['source_directories'] = ['src/dra', 'include', 'asm/dra']
