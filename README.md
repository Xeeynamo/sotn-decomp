# Castlevania: Symphony of the Night disassembly

Recompilable code that creates 1:1 binaries for the commercial videogame Castlevania: Symphony of the Night for the PlayStation 1. This repository aims to create a full decompilation in C.

## Game revision

All the files refers to the `SLUS-00067` version of the game.

| SHA-1 checksum                             | File name  | Progress
|--------------------------------------------|------------|----------
| `54828d4e44ea9575f2a0917ff63def42a304abff` | main.exe   | N/A 
| `2eac5f7162e77416166c2511c787995488f01c37` | DRA.BIN    | ![progress DRA.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-pages/assets/progress-dra.json)
| `e42976f45b47d1c4912a198ae486b77ee6d77c9c` | ST/DRE.BIN | ![progress DRE.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-pages/assets/progress-dre.json)
| `adb3303e1ea707c63dfa978511a88cab4f61970a` | ST/MAD.BIN | ![progress MAD.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-pages/assets/progress-mad.json)
| `5d06216b895ab5ff892c88b0d9eff67ff16e2bd1` | ST/NO3.BIN | ![progress NO3.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-pages/assets/progress-no3.json)
| `7c78a2bec6a26acfb62456e7f517915fe0c0e3f5` | ST/NP3.BIN | ![progress NP3.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-pages/assets/progress-np3.json)
| `bc2fabbe5ef0d1288490b6f1ddbf11092a2c0c57` | ST/ST0.BIN | ![progress ST0.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-pages/assets/progress-st0.json)
| `2ae313f4e394422e4c5f37a2d8e976e92f9e3cda` | ST/WRP.BIN | ![progress WRP.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-pages/assets/progress-wrp.json)
| `3bbdd3b73f8f86cf5f6c88652e9e6452a7fb5992` | ST/RWRP.BIN | ![progress RWRP.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-pages/assets/progress-rwrp.json)

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

## Restore MAD (debug room)

The debug room overlay `ST/MAD.BIN` was compiled earlier than the first retail release of the game. All the offsets that refers to `DRA.BIN` points to invalid portions of data or to the wrong API calls, effectively breaking the majority of its original functionalities. That is why the debug room does not contain any object. By compiling the debug room with `make mad_fix` you can restore it by redirecting the old pointers to the retail version of the game. 

Be aware that not all the offsets have been yet redirected, so it will still be not entirely functional until further update.

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
