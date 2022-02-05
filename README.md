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
1. Place your `main.exe` from the file `SLUS_000.67`, `DRA.BIN` and the `ST` folder in the root directory of the repository
1. Run `make extract` to generate the assembly files
1. Run `make all` to compile the binaries into the `build/` directory

## Check for function matching

Thanks to [asm-differ](https://github.com/simonlindholm/asm-differ) you can check if a funtion written in C matches its assembly counterpart.

1. Be sure to resolve the submodule with `git submodule update --init`
1. Ensure to create a matching binary with `make clean && make extract && make all && mkdir expected && cp -r build expected/`
1. Choose a function to match (eg. `func_8018E964`), an overlay (eg. `st/mad`) and then invoke `python3 ./tools/asm-differ/diff.py -mwo --overlay st/mad func_8018E964`

## Non-matching build

Some non-matching functions are present in the source code by disabled by the macro `NON_MATCHING`. You can still compile the game binaries by running ` CPP_FLAGS=-DNON_MATCHING make`. In theory they might be logically equivalent in-game, but I cannot promise that. Few of them could match by tuning or changing the compiler.

## Technical details

The game is divided in three modules:

* `main` is the game engine of the game. It contains all the necessary logic to interact with the gamepad, CD, memory card, the SPU and to render the sprites on-screen. It appears to not contain any game logic by itself.
* `DRA` is the game itself. It contains the gameloop and the necessary API to draw maps, entities, load levels, handle entities, animations and collisions. It also contains some common data such as Alucard's sprites, candle's sprites and the common rooms' (save, loading, teleport) layout.
* `ST/` are the overlays for each area. An area (eg. Castle's entrance, Alchemy Laboratory, etc.) contains all the unique logic to handle map's specific events, cutscenes, enemies' AI, collisions and more. It also contains the rooms and entities layout.

# Notes

* I suspect that GCC 2.7.2 / PSY-Q 3.6 have been used to originally compile `DRA.BIN`
* `main.exe` uses PS-X libraries that might've been created with a different compiler and with `-O1` rather than `-O2`

## To do

The project is very barebone at the moment and there is a massive room of improvement, mostly in the infrastructure:

* Not all the zone overlays (`ST/{ZONE}/{ZONE}.BIN`) are disassembled
* There is no CI/CD pipeline to test the correctness of the compiled code
