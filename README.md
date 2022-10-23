# Castlevania: Symphony of the Night disassembly

Creates a full decompilation in C, that compiles the same binaries as the commercial video game Castlevania: Symphony of the Night for PS1.

The game is divided in three modules:
`SLUS_000.67` is the game engine of the game. It contains all the necessary logic to interact with the gamepad, CD, memory card, the SPU and to render the sprites on-screen. It appears to not contain any game logic by itself.
`DRA` is the game itself. It contains the gameloop and the necessary API to draw maps, entities, load levels, handle entities, animations and collisions. It also contains some common data such as Alucard's sprites, candle's sprites and the common rooms' (save, loading, teleport) layout.
`ST/` are the overlays for each area. An area (eg. Castle's entrance, Alchemy Laboratory, etc.) contains all the unique logic to handle map's specific events, cutscenes, enemies' AI, collisions and more. It also contains the rooms and entities layout.

All the files refers to the `SLUS-00067` version of the game.


## Bins decomp progress

| SHA-1 checksum                             | File name  | Progress
|--------------------------------------------|------------|----------
| `54828d4e44ea9575f2a0917ff63def42a304abff` | SLUS_000.67 | N/A 
| `2eac5f7162e77416166c2511c787995488f01c37` | DRA.BIN    | ![progress DRA.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-report/assets/progress-dra.json)
| `d076912661e67a38afae0a1b5044ab5f10bcfb39` | RIC.BIN    | ![progress RIC.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-report/assets/progress-ric.json)
| `e42976f45b47d1c4912a198ae486b77ee6d77c9c` | ST/DRE.BIN | ![progress DRE.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-report/assets/progress-dre.json)
| `adb3303e1ea707c63dfa978511a88cab4f61970a` | ST/MAD.BIN | ![progress MAD.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-report/assets/progress-mad.json)
| `5d06216b895ab5ff892c88b0d9eff67ff16e2bd1` | ST/NO3.BIN | ![progress NO3.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-report/assets/progress-no3.json)
| `7c78a2bec6a26acfb62456e7f517915fe0c0e3f5` | ST/NP3.BIN | ![progress NP3.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-report/assets/progress-np3.json)
| `bc2fabbe5ef0d1288490b6f1ddbf11092a2c0c57` | ST/ST0.BIN | ![progress ST0.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-report/assets/progress-st0.json)
| `2ae313f4e394422e4c5f37a2d8e976e92f9e3cda` | ST/WRP.BIN | ![progress WRP.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-report/assets/progress-wrp.json)
| `3bbdd3b73f8f86cf5f6c88652e9e6452a7fb5992` | ST/RWRP.BIN | ![progress RWRP.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-report/assets/progress-rwrp.json)


## How to setup the project (assuming linux ubuntu/debian or windows with WSL)
 * `sudo apt-get install gcc-mipsel-linux-gnu binutils-mips-linux-gnu`
 * `pip install spimdisasm tqdm intervaltree`
 * Inside the folder of your choice `git clone https://github.com/Xeeynamo/sotn-decomp.git`
 * `git submodule update --init`
 * Inside the newly created repo, create a new `iso/` folder, and extract the content of the game disc

## How to build
 * Run `make extract` to generate the assembly files in the `asm/` directory
 * Run `make all` to compile the binaries in the `build/` directory
you don’t need to use it now but note that `make clean` deletes the build directory
Some non-matching functions are present in the source preprocessed by the macro `NON_MATCHING`. You can still compile the game binaries by running `CPP_FLAGS=-DNON_MATCHING make`. In theory they might be logically equivalent in-game, but I cannot promise that. Few of them could match by tuning or changing the compiler.

## How to decompile
* After setup and build, choose an overlay (eg. `ST/WRP`)
* Look for one of those function which hasn't successfully decompiled yet (eg. `INCLUDE_ASM("asm/st/wrp/nonmatchings/6FD0", func_801873A0);`)
* Look for its assembly file (eg. `asm/st/wrp/nonmatchings/6FD0/func_801873A0.s`)
* Run `SOURCE=src/st/wrp/6FD0.c make ctx.c` then `ASSEMBLY=asm/st/wrp/nonmatchings/6FD0/func_801873A0.s make decompile` to dump the decompiled code into ctx.c.m2c
* Replace the `INCLUDE_ASM(...);` you targeted with the content of `ctx.c.m2c`
* run `make expected` and invoke `python3 ./tools/asm-differ/diff.py -mwo --overlay st/wrp func_801873A0`
You will probably have some differences from your compiled code to the original; keep refactoring the code and move variables around until you have a 100% match.

There are a few tricks to make the process more streamlined:
* Use [decomp.me](https://decomp.me/) with GCC 2.7.2 for PS1. Be aware that the repo is using GCC 2.6.x, so decomp.me will sometimes give a slightly different output. 
* The “context” section of decomp.me, is provided by the cmd `SOURCE=src/st/wrp/6FD0.c make ctx.c` as mentionned in the how to decompile.
* Use [decomp-permuter](https://github.com/simonlindholm/decomp-permuter) to solve some mismatches
* Use [this](https://github.com/mkst/sssv/wiki/Jump-Tables) and [this](https://github.com/pmret/papermario/wiki/GCC-2.8.1-Tips-and-Tricks) guide to understand how some compiler patterns work
* Use the `#ifndef NON_MATCHING` if your code is logically equivalent but you cannot yet fully match it


## Resources:
* List of resource for sotn https://github.com/TalicZealot/SotN-Utilities (speedrun oriented, but very useful still). 
* PS1’s CPU R3000 instruction [manual](https://cgi.cse.unsw.edu.au/~cs3231/doc/R3000.pdf) and [cheat sheet](https://vhouten.home.xs4all.nl/mipsel/r3000-isa.html)
* https://github.com/KernelEquinox/SNEER
* Debugging Emulator: https://github.com/grumpycoders/pcsx-redux
* Debugging Emulator with Register Breakpoints: https://www.romhacking.net/utilities/267/
* Beginner friendly MIPS video lectures [1](https://www.youtube.com/watch?v=PlavjNH_RRU&list=PLylNWPMX1lPlmEeeMdbEFQo20eHAJL8hx) and [2](https://www.youtube.com/watch?v=qzSdglU0SBc&list=PLylNWPMX1lPnipZzKdCWRj2-un5xvLLdK)


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

