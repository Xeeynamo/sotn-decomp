# Castlevania: Symphony of the Night Decompilation

A work-in-progress decompilation of Castlevania Symphony of the Night for PlayStation 1. It aims to recreate the source code from the existing binaries using static and/or dynamic analysis. The code compiles byte-for-byte to the same binaries of the game, effectively being a matching decompilation. Currently it only supports the US version of the game `SLUS-00067`.

This repo does not include any assets or assembly code necessary for compiling the binaries. A prior copy of the game is required to extract the required assets.

## Bins decomp progress

| File name  | Progress | Description
|------------|----------|-------------
| SLUS_000.67 | N/A | Shared libraries
| DRA.BIN    | ![progress DRA.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-report/assets/progress-dra.json) | Game engine
| BIN/RIC.BIN    | ![progress RIC.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-report/assets/progress-ric.json) | Playable Richter
| ST/CEN/CEN.BIN | ![progress CEN.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-report/assets/progress-cen.json) | Center
| ST/DRE/DRE.BIN | ![progress DRE.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-report/assets/progress-dre.json) | Nightmare
| ST/MAD/MAD.BIN | ![progress MAD.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-report/assets/progress-mad.json) | Debug Room
| ST/NO3/NO3.BIN | ![progress NO3.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-report/assets/progress-no3.json) | Entrance (first visit)
| ST/NP3/NP3.BIN | ![progress NP3.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-report/assets/progress-np3.json) | Entrance
| ST/NZ0/NZ0.BIN | ![progress NZ0.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-report/assets/progress-nz0.json) | Alchemy Laboratory
| ST/SEL.SEL.BIN | ![progress SEL.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-report/assets/progress-sel.json) | Title screen
| ST/ST0/ST0.BIN | ![progress ST0.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-report/assets/progress-st0.json) | Final Stage: Bloodlines
| ST/WRP/WRP.BIN | ![progress WRP.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-report/assets/progress-wrp.json) | Warp Room
| ST/RWRP/RWRP.BIN | ![progress RWRP.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-report/assets/progress-rwrp.json) | Warp Room (reverse)
| SERVANT/TT_000.BIN | ![progress TT_000.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-report/assets/progress-tt_000.json) | Bat Familiar

## Game versions

| ID      | Console | Build date | Notes
|---------|---------|------------|-------
| jp10    | PS1     | 1997-02-20 |
| jp11    | PS1     | 1997-03-06 | same psx.exe as jp10
| usproto | PS1     | 1997-06-17 | same psx.exe as jp10
| us      | PS1     | 1997-09-01 |
| eu      | PS1     | 1997-09-30 |
| hk      | PS1     | 1997-11-30 | same psx.exe as jp10
| jp12    | PS1     | 1998-01-23 | same psx.exe as jp10
| saturn  | Saturn  | 1998-04-27 |
| hd      | PS1     | 2006-10-22 | build found in the PSP game
| pspko   | PSP     | 2007-09-07 |
| pspus   | PSP     | 2007-09-10 |
| pspjp   | PSP     | 2007-09-14 |
| pspeu   | PSP     | 2007-11-21 |

## Game internals

The game is divided into three modules:

* `SLUS_000.67` the main executable. It contains all the hardware API (eg. gamepad, CD, memory card, GPU renderer) of the PlayStation 1 console. It does not contain any game logic.
* `DRA` the game engine. It contains the business logic (eg. gameloop, API to draw maps, entities, load levels, handle entities, animations and collisions) and some data such as Alucard's sprites or the loading/save rooms.
* `ST/` the overlays for each area. An area (eg. Castle's entrance, Alchemy Laboratory, etc.) contains all the unique logic to handle map specific events, cutscenes, enemy AI, collisions and more. It also contains the rooms and entities layout. Each overlay can be considered as its own mini-game. The title screen `SEL.BIN` is an example of how a stage overlay can act very differently.

Even if different overlays are loaded at the same time in memory, like `DRA` and stages, they never communicate each other directly. Instead they share the same memory area where `SLUS_000.67` is located. Each overlay exposes their API as function pointers in the shared memory area, effectively allowing overlays to communicate without directly coupling them. One prime example is `struct GameApi`, which exposes `DRA` APIs to the stages and stage APIs to `DRA`. All the shared area is defined in `game.h`.

## Setup the project

This assumes you have Ubuntu, Debian or WSL in Windows:

```
git clone https://github.com/Xeeynamo/sotn-decomp.git
cd sotn-decomp
sudo apt-get update
sudo apt-get install -y $(cat tools/requirements-debian.txt)
make update-dependencies
```

1. Run `mv disks/*.cue disks/sotn.us.cue`
1. Run `make extract_disk`

## Build

1. Run `make extract` to generate the assembly files for the functions not yet decompiled.
1. Run `make all` to compile the binaries in the `build/` directory.
1. Run `make disk` to create a new CUE/BIN pair based on the new compiled binaries.

In case there are any changes in the `config/` folder, you might need to run `make clean` to reset the extraction.

Some non-matching functions are present in the source preprocessed by the macro `NON_MATCHING`. You can still compile the game binaries by running `CPP_FLAGS=-DNON_MATCHING make`. In theory they might be logically equivalent in-game, but I cannot promise that. Few of them could match by tuning or changing the compiler.

## Start decompilation

1. Run `make clean extract all expected` at least once
1. After setup and build, choose an overlay (eg. `ST/WRP`)
1. Look for one of those functions which hasn't successfully decompiled yet (eg. `INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", func_801873A0);`)
1. Run `./tools/decompile.py func_801873A0` to decompile the function in the C source code where the function is supposed to be located
1. If the function does not compile, try addressing the compilation errors until `make` compiles
1. If the function does not match, invoke `python3 ./tools/asm-differ/diff.py -mwo --overlay st/wrp func_801873A0` and refactor the code until it matches
1. If the function matches, try refactoring to keep the code clean while checking if the function still matches once in a while

There are a few tricks to make the process more streamlined:

1. Use [decomp.me](https://decomp.me/) with PSY-Q 4.0. Be aware that the repo is using GCC 2.6.x, so decomp.me will sometimes give a slightly different output.
1. The “context” section of decomp.me, is provided by the cmd `SOURCE=src/dra/42398.c make context`.
1. Use [decomp-permuter](https://github.com/simonlindholm/decomp-permuter) to solve some mismatches.
1. Use [this](https://github.com/mkst/sssv/wiki/Jump-Tables) and [this](https://github.com/pmret/papermario/wiki/GCC-2.8.1-Tips-and-Tricks) guide to understand how some compiler patterns work.
1. Use the `#ifndef NON_MATCHING` if your code is logically equivalent but you cannot yet fully match it.

## Duplicate functions

Due to how the game is structured, a lot of duplicate code can be found across the different overlays. We [track a live list of possible duplicate functions](https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-duplicates/duplicates.txt) that is useful to avoid trying to decompile functions that have been already decompiled elsewhere.

## Resources

* Project Documentation [Style Guide](https://github.com/Xeeynamo/sotn-decomp/blob/master/docs/STYLE.md)
* List of resource for sotn <https://github.com/TalicZealot/SotN-Utilities> (speedrun oriented, but still very useful).
* PS1’s CPU R3000 instruction [manual](https://cgi.cse.unsw.edu.au/~cs3231/doc/R3000.pdf) and [cheat sheet](https://vhouten.home.xs4all.nl/mipsel/r3000-isa.html)
* [SOTN map viewer written in C](https://github.com/KernelEquinox/SotN-Editor)
* [PCSX emulator with debugger](https://www.romhacking.net/utilities/267/)
* [NO$PSX emulator with debugger](https://problemkaputt.de/psx.htm)
* Beginner friendly MIPS video lectures [1](https://www.youtube.com/watch?v=PlavjNH_RRU&list=PLylNWPMX1lPlmEeeMdbEFQo20eHAJL8hx), [2](https://www.youtube.com/watch?v=qzSdglU0SBc&list=PLylNWPMX1lPnipZzKdCWRj2-un5xvLLdK)

## To do

The project is very barebone at the moment and there is a massive room of improvement, mostly in the infrastructure:

* Not all the zone overlays (`ST/{ZONE}/{ZONE}.BIN`) are disassembled
* Integrate ASPSX instead of GNU AS
* Split binary data (eg. map layout, graphics, other assets) into individual files

## Notes

* The debug room overlay `ST/MAD.BIN` was compiled earlier than the first retail release of the game. All the offsets that refers to DRA.BIN points to invalid portions of data or to the wrong API calls, effectively breaking the majority of its original functionalities. That is why the debug room does not contain any object. By compiling the debug room with make mad_fix you can restore it by redirecting the old pointers to the retail version of the game.
Be aware that not all the offsets have been yet redirected, so it will still be not entirely functional until further update.
* I suspect that GCC 2.6.x / PSY-Q 3.4 have been used to originally compile DRA.BIN
* `main.exe` uses PS-X libraries that might have been created with a different compiler and with `-O1` rather than `-O2`
