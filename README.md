# Castlevania: Symphony of the Night Decompilation

A work-in-progress decompilation of Castlevania Symphony of the Night for PlayStation 1. It aims to recreate the source code from the existing binaries using static and/or dynamic analysis. The code compiles the same binaries of the game, byte-for-byte to the same binaries of the game, effectively being a matching decompilation. Currently it only supports the US version of the game `SLUS-00067`.

The game is divided into three modules:

* `SLUS_000.67` the main executable. It contains all the hardware API (eg. gamepad, CD, memory card, GPU renderer) of the PlayStation 1 console. It does not contain any game logic.
* `DRA` the game engine. It contains the business logic (eg. gameloop, API to draw maps, entities, load levels, handle entities, animations and collisions) and some data such as Alucard's sprites or the loading/save rooms.
* `ST/` the overlays for each area. An area (eg. Castle's entrance, Alchemy Laboratory, etc.) contains all the unique logic to handle map specific events, cutscenes, enemy AI, collisions and more. It also contains the rooms and entities layout. Each overlay can be considered as its own mini-game. The title screen `SEL.BIN` is an example of how a stage overlay can act very differently.

This repo does not include any assets or assembly code necessary for compiling the binaries. A prior copy of the game is required to extract the required assets.

## Bins decomp progress

| SHA-1 checksum                             | File name  | Progress
|--------------------------------------------|------------|----------
| `54828d4e44ea9575f2a0917ff63def42a304abff` | SLUS_000.67 | N/A 
| `2eac5f7162e77416166c2511c787995488f01c37` | DRA.BIN    | ![progress DRA.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-report/assets/progress-dra.json)
| `d076912661e67a38afae0a1b5044ab5f10bcfb39` | RIC.BIN    | ![progress RIC.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-report/assets/progress-ric.json)
| `42226b6d9ed24448eed61b3c6cd2949e96bebab6` | ST/CEN.BIN | ![progress CEN.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-report/assets/progress-cen.json)
| `e42976f45b47d1c4912a198ae486b77ee6d77c9c` | ST/DRE.BIN | ![progress DRE.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-report/assets/progress-dre.json)
| `adb3303e1ea707c63dfa978511a88cab4f61970a` | ST/MAD.BIN | ![progress MAD.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-report/assets/progress-mad.json)
| `5d06216b895ab5ff892c88b0d9eff67ff16e2bd1` | ST/NO3.BIN | ![progress NO3.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-report/assets/progress-no3.json)
| `7c78a2bec6a26acfb62456e7f517915fe0c0e3f5` | ST/NP3.BIN | ![progress NP3.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-report/assets/progress-np3.json)
| `b10b9c2be721cf9cbed3aa94be468ba9e23bc68b` | ST/NZ0.BIN | ![progress NZ0.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-report/assets/progress-nz0.json)
| `a919a53a760107972049bfdeadde33376428eace` | ST/SEL.BIN | ![progress SEL.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-report/assets/progress-sel.json)
| `bc2fabbe5ef0d1288490b6f1ddbf11092a2c0c57` | ST/ST0.BIN | ![progress ST0.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-report/assets/progress-st0.json)
| `2ae313f4e394422e4c5f37a2d8e976e92f9e3cda` | ST/WRP.BIN | ![progress WRP.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-report/assets/progress-wrp.json)
| `3bbdd3b73f8f86cf5f6c88652e9e6452a7fb5992` | ST/RWRP.BIN | ![progress RWRP.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-report/assets/progress-rwrp.json)


## Setup the project

This assumes you have Ubuntu 20.04 or Debian 11, either as a primary OS or within WSL in Windows.

1. Inside the folder of your choice `git clone https://github.com/Xeeynamo/sotn-decomp.git`
1. Run `sudo apt-get install -y $(cat tools/requirements-debian.txt)`
1. Run `make update-dependencies`
1. Inside the newly created repo, create a new `iso/` folder, and extract the contents of the game disc

## Build

1. Run `make extract` to generate the assembly files for the functions not yet decompiled.
1. Run `make all` to compile the binaries in the `build/` directory.

In case there are any changes in the `config/` folder, you might need to run `make clean` to reset the extraction.

Some non-matching functions are present in the source preprocessed by the macro `NON_MATCHING`. You can still compile the game binaries by running `CPP_FLAGS=-DNON_MATCHING make`. In theory they might be logically equivalent in-game, but I cannot promise that. Few of them could match by tuning or changing the compiler.

## Start decompilation

1. Run `make clean extract all expected` at least once
1. After setup and build, choose an overlay (eg. `ST/WRP`)
1. Look for one of those functions which hasn't successfully decompiled yet (eg. `INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_801873A0);`)
1. Run `./tools/decompile.py func_801873A0` to decompile the function in the C source code where the function is supposed to be located
1. If the function does not compile, try addressing the compilation errors until `make` compiles
1. If the function does not match, invoke `python3 ./tools/asm-differ/diff.py -mwo --overlay st/wrp func_801873A0` and refactor the code until it matches
1. If the function matches, try refactoring to keep the code clean while checking if the function still matches once in a while

There are a few tricks to make the process more streamlined:

1. Use [decomp.me](https://decomp.me/) with PSY-Q 4.0. Be aware that the repo is using GCC 2.6.x, so decomp.me will sometimes give a slightly different output. 
1. The “context” section of decomp.me, is provided by the cmd `SOURCE=src/wrp/6FD0.c make context` as mentioned in the how to decompile.
1. Use [decomp-permuter](https://github.com/simonlindholm/decomp-permuter) to solve some mismatches.
1. Use [this](https://github.com/mkst/sssv/wiki/Jump-Tables) and [this](https://github.com/pmret/papermario/wiki/GCC-2.8.1-Tips-and-Tricks) guide to understand how some compiler patterns work.
1. Use the `#ifndef NON_MATCHING` if your code is logically equivalent but you cannot yet fully match it.


## Resources:

* List of resource for sotn https://github.com/TalicZealot/SotN-Utilities (speedrun oriented, but still very useful). 
* PS1’s CPU R3000 instruction [manual](https://cgi.cse.unsw.edu.au/~cs3231/doc/R3000.pdf) and [cheat sheet](https://vhouten.home.xs4all.nl/mipsel/r3000-isa.html)
* [SOTN map viewer written in C](https://github.com/KernelEquinox/SotN-Editor)
* [PCSX emulator with debugger](https://www.romhacking.net/utilities/267/)
* [NO$PSX emulator with debugger](https://problemkaputt.de/psx.htm)
* Beginner friendly MIPS video lectures [1](https://www.youtube.com/watch?v=PlavjNH_RRU&list=PLylNWPMX1lPlmEeeMdbEFQo20eHAJL8hx), [2](https://www.youtube.com/watch?v=qzSdglU0SBc&list=PLylNWPMX1lPnipZzKdCWRj2-un5xvLLdK)

## To do:

The project is very barebone at the moment and there is a massive room of improvement, mostly in the infrastructure:

* Not all the zone overlays (`ST/{ZONE}/{ZONE}.BIN`) are disassembled
* Integrate ASPSX instead of GNU AS
* Split binary data (eg. map layout, graphics, other assets) into individual files

## Notes

* The debug room overlay `ST/MAD.BIN` was compiled earlier than the first retail release of the game. All the offsets that refers to DRA.BIN points to invalid portions of data or to the wrong API calls, effectively breaking the majority of its original functionalities. That is why the debug room does not contain any object. By compiling the debug room with make mad_fix you can restore it by redirecting the old pointers to the retail version of the game.
Be aware that not all the offsets have been yet redirected, so it will still be not entirely functional until further update.
* I suspect that GCC 2.6.x / PSY-Q 3.4 have been used to originally compile DRA.BIN
* `main.exe` uses PS-X libraries that might have been created with a different compiler and with `-O1` rather than `-O2`

## Troubleshooting

### Not getting an "OK" on Ubuntu 22.04

Debian>=12 and Ubuntu>=22.04 uses `binutils-mipsel-linux-gnu`>=2.38 which, for some unknown reasons, it generates broken binaries. You need to downgrade to 2.34 or 2.35 with the following:

```shell
curl -L -o binutils-mipsel-linux-gnu_2.35.2-2cross2_amd64.deb http://ftp.de.debian.org/debian/pool/main/b/binutils-mipsen/binutils-mipsel-linux-gnu_2.35.2-2cross2_amd64.deb
dpkg -i binutils-mipsel-linux-gnu_2.35.2-2cross2_amd64.deb
rm binutils-mipsel-linux-gnu_2.35.2-2cross2_amd64.deb
```
