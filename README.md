# Castlevania: Symphony of the Night disassembly

Recompilable code that creates 1:1 binaries for the commercial videogame Castlevania: Symphony of the Night for the PlayStation 1. This repository aims to create a full decompilation in C.

## Game revision

| SHA-1 checksum                             | File name | Version    | Progress
|--------------------------------------------|-----------|------------|----------
| `54828d4e44ea9575f2a0917ff63def42a304abff` | main.exe  | SLUS-00067 | N/A 
| `2eac5f7162e77416166c2511c787995488f01c37` | DRA.BIN   | SLUS-00067 | ![progress DRA.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-pages/assets/progress-dra.json)
| `adb3303e1ea707c63dfa978511a88cab4f61970a` | ST/MAD.BIN   | SLUS-00067 | ![progress MAD.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-pages/assets/progress-mad.json)
| `5d06216b895ab5ff892c88b0d9eff67ff16e2bd1` | ST/NO3.BIN   | SLUS-00067 | ![progress NO3.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-pages/assets/progress-no3.json)

## Build

1. You need `gcc-mipsel-linux-gnu` that you can easily install on any Debian-based Linux distribution. On Windows it is highly recommended to just use Ubuntu with WSL
1. Place your `main.exe` from the file `SLUS_000.67` and `DRA.BIN` in the root directory
1. Run `make extract` to generate the assembly files
1. Run `make all` to compile the binaries into the `build/` directory

## Check for function matching

Thanks to [asm-differ](https://github.com/simonlindholm/asm-differ) you can check if a funtion written in C matches its assembly counterpart.

1. Be sure to resolve the submodule with `git submodule update --init`
1. Ensure to create a matching binary with `make clean && make extract && make all && mkdir expected && cp -r build expected/`
1. Choose a function to match (eg. `func_8018E964`), an overlay (eg. `st/mad`) and then invoke `python3 ./tools/asm-differ/diff.py -mwo --overlay st/mad func_8018E964`

## Non-matching build

Some of the functions that do not fully match the original game can be compiled by defining `#define NON_MATCHING` on a header file or by passing `-DNON_MATCHING to the compiler. In theory they might be logically equivalent in-game, but I cannot promise that. Few of them could match by tuning or changing the compiler.

# Notes

* I suspect that GCC 2.7.2 / PSY-Q 3.6 have been used to originally compile `DRA.BIN`
* `main.exe` uses PS-X libraries that might've been created with a different compiler and with `-O1` rather than `-O2`

## To do

The project is very barebone at the moment and there is a massive room of improvement, mostly in the infrastructure:

* The zone overlays (`ST/{ZONE}/{ZONE}.BIN`) are not yet disassembled
* There is no CI/CD pipeline to test the correctness of the compiled code
