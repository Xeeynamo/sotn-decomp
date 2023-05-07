#!/usr/bin/env python3

import argparse
import os

parser = argparse.ArgumentParser(description='Manage game symbols with various operations')
parser.add_argument('--version', required=False, type=str, help='Game version')
subparsers = parser.add_subparsers(dest='command')

sort_parser = subparsers.add_parser('sort', description='Sort all the symbols by their offset')

args = parser.parse_args()
if args.version == None:
    args.version = os.getenv('VERSION')
    if args.version == None:
        args.version = 'us'

def sort_symbol_list(symbol_file_name):
    offsets = []
    with open(symbol_file_name) as symbol_file:
        for line in symbol_file:
            line = line.strip()
            if not line:
                continue
            parts = line.split()
            if len(parts) < 3:
                continue
            offset = parts[2].rstrip(';')
            offsets.append((line, int(offset, 16)))
    offsets.sort(key=lambda x: x[1])
    with open(symbol_file_name, 'w') as symbol_file:
        for line, offset in offsets:
            symbol_file.write(line + '\n')

def sort(base_path):
    files = os.listdir(base_path)

    # Filter the list to include only files that start with 'symbols.us.' and end with '.txt'
    filtered_files = [f for f in files if f.startswith(f'symbols.{args.version}.') and f.endswith('.txt')]

    for symbol_file_name in [os.path.join(base_path, f) for f in filtered_files]:
        sort_symbol_list(symbol_file_name)

if __name__ == "__main__":
    if args.command == 'sort':
        sort("config/")
