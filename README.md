# Castlevania: Symphony of the Night Decompilation

A work-in-progress decompilation of Castlevania Symphony of the Night for PlayStation 1. It aims to recreate the source code from the existing binaries using static and/or dynamic analysis. The code compiles byte-for-byte to the same binaries of the game, effectively being a matching decompilation. Currently it only supports the US version of the game `SLUS-00067`.

This repo does not include any assets or assembly code necessary for compiling the binaries. A prior copy of the game is required to extract the required assets.

## Bins decomp progress

| File name  | Code coverage | Decomp functions | Description
|------------|----------|-----------|-------------
| SLUS_000.67 | N/A | N/A | Shared libraries
| DRA.BIN    | ![code coverage DRA.BIN](https://img.shields.io/endpoint?label=DRA%20code&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Fcode%2F%3Fmode%3Dshield%26measure%3Ddra) | ![decompiled functions](https://img.shields.io/endpoint?label=DRA%20funcs&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Ffunctions%2F%3Fmode%3Dshield%26measure%3Ddra) | Game engine
| BIN/RIC.BIN    | ![code coverage RIC.BIN](https://img.shields.io/endpoint?label=RIC%20code&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Fcode%2F%3Fmode%3Dshield%26measure%3Dric) | ![decompiled functions](https://img.shields.io/endpoint?label=RIC%20funcs&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Ffunctions%2F%3Fmode%3Dshield%26measure%3Dric) | Playable Richter
| ST/CEN/CEN.BIN | ![code coverage CEN.BIN](https://img.shields.io/endpoint?label=CEN%20code&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Fcode%2F%3Fmode%3Dshield%26measure%3Dstcen) | ![decompiled functions](https://img.shields.io/endpoint?label=CEN%20funcs&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Ffunctions%2F%3Fmode%3Dshield%26measure%3Dstcen) | Center
| ST/DRE/DRE.BIN | ![code coverage DRE.BIN](https://img.shields.io/endpoint?label=DRE%20code&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Fcode%2F%3Fmode%3Dshield%26measure%3Dstdre) | ![decompiled functions](https://img.shields.io/endpoint?label=DRE%20funcs&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Ffunctions%2F%3Fmode%3Dshield%26measure%3Dstdre) | Nightmare
| ST/MAD/MAD.BIN | ![code coverage MAD.BIN](https://img.shields.io/endpoint?label=MAD%20code&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Fcode%2F%3Fmode%3Dshield%26measure%3Dstmad) | ![decompiled functions](https://img.shields.io/endpoint?label=MAD%20funcs&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Ffunctions%2F%3Fmode%3Dshield%26measure%3Dstmad) | Debug Room
| ST/NO3/NO3.BIN | ![code coverage NO3.BIN](https://img.shields.io/endpoint?label=NO3%20code&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Fcode%2F%3Fmode%3Dshield%26measure%3Dstno3) | ![decompiled functions](https://img.shields.io/endpoint?label=NO3%20funcs&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Ffunctions%2F%3Fmode%3Dshield%26measure%3Dstno3) | Entrance (first visit)
| ST/NP3/NP3.BIN | ![code coverage NP3.BIN](https://img.shields.io/endpoint?label=NP3%20code&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Fcode%2F%3Fmode%3Dshield%26measure%3Dstnp3) | ![decompiled functions](https://img.shields.io/endpoint?label=NP3%20funcs&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Ffunctions%2F%3Fmode%3Dshield%26measure%3Dstnp3) | Entrance
| ST/NZ0/NZ0.BIN | ![code coverage NZ0.BIN](https://img.shields.io/endpoint?label=NZ0%20code&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Fcode%2F%3Fmode%3Dshield%26measure%3Dstnz0) | ![decompiled functions](https://img.shields.io/endpoint?label=NZ0%20funcs&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Ffunctions%2F%3Fmode%3Dshield%26measure%3Dstnz0) | Alchemy Laboratory
| ST/SEL/SEL.BIN | ![code coverage SEL.BIN](https://img.shields.io/endpoint?label=SEL%20code&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Fcode%2F%3Fmode%3Dshield%26measure%3Dstsel) | ![decompiled functions](https://img.shields.io/endpoint?label=SEL%20funcs&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Ffunctions%2F%3Fmode%3Dshield%26measure%3Dstsel) | Title screen
| ST/ST0/ST0.BIN | ![code coverage ST0.BIN](https://img.shields.io/endpoint?label=ST0%20code&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Fcode%2F%3Fmode%3Dshield%26measure%3Dstst0) | ![decompiled functions](https://img.shields.io/endpoint?label=ST0%20funcs&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Ffunctions%2F%3Fmode%3Dshield%26measure%3Dstst0) | Final Stage: Bloodlines
| ST/WRP/WRP.BIN | ![code coverage WRP.BIN](https://img.shields.io/endpoint?label=WRP%20code&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Fcode%2F%3Fmode%3Dshield%26measure%3Dstwrp) | ![decompiled functions](https://img.shields.io/endpoint?label=WRP%20funcs&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Ffunctions%2F%3Fmode%3Dshield%26measure%3Dstwrp) | Warp Room
| ST/RWRP/RWRP.BIN | ![code coverage RWRP.BIN](https://img.shields.io/endpoint?label=RWRP%20code&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Fcode%2F%3Fmode%3Dshield%26measure%3Dstrwrp) | ![decompiled functions](https://img.shields.io/endpoint?label=RWRP%20funcs&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Ffunctions%2F%3Fmode%3Dshield%26measure%3Dstrwrp) | Warp Room (reverse)
| SERVANT/TT_000.BIN | ![code coverage TT_000.BIN](https://img.shields.io/endpoint?label=TT_000%20code&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Fcode%2F%3Fmode%3Dshield%26measure%3Dtt_000) | ![decompiled functions](https://img.shields.io/endpoint?label=TT_000%20funcs&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Ffunctions%2F%3Fmode%3Dshield%26measure%3Dtt_000) | Bat Familiar

Code coverage means how many bytes of code have been successfully converted from assembly into C code, while decomp function is how many functions have been succesfully decompiled.

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

1. Use [decomp.me](https://decomp.me/) with PSY-Q 3.5. Be aware that the repo is using GCC 2.6.x, therefore the local output might be slightly wrong.
1. The “context” section of decomp.me, is provided by the cmd `SOURCE=src/dra/42398.c make context`.
1. Use [decomp-permuter](https://github.com/simonlindholm/decomp-permuter) to solve some mismatches.
1. Use [this](https://github.com/mkst/sssv/wiki/Jump-Tables) and [this](https://github.com/pmret/papermario/wiki/GCC-2.8.1-Tips-and-Tricks) guide to understand how some compiler patterns work.
1. Use the `#ifndef NON_MATCHING` if your code is logically equivalent but you cannot yet fully match it.

## Decompiling functions with jump tables
* Functions with jump tables will load an address named `jpt_XXXXXXXX` or `jtbl_XXXXXXXX` and jump to it using `jr`.
### Creating a scratch on decomp.me
* Copy the function assembly into the "Target Assembly" field.
* Copy the jump tables below the function assembly. Make sure you have `.section .rodata` before the jump tables.
* The result should look similar to the following:
```
.set noat      /* allow manual use of $at */
.set noreorder /* don't insert nops after branches */

glabel MyFunction
... (function asm continues here)

.section .rodata

glabel jtbl_801A7B40
... (jump table continues)

glabel jtbl_801A7B58
... (jump table continues)
```
* The jump tables will not be visible in the Target/Current panes of the editor, but if the decompilation shows one or more switches then it worked.
### Adding to the repo
* When decompilation is complete these functions need to have the `.rodata` where the jump table is located ignored. The new jump table from the decompiled function will be used instead.
* This is done by modifying the splat yaml. The jump table needs to be extracted to its own file like this:
```
      - [0x3B560, rodata] # jpt_800E55C4
      - [0x3B720, rodata]
```
* We have a tool, `tools/split_jpt_yaml/split_jpt_yaml.py` to automate part of this process.
* It splits all of the jump tables into their own files. Usage is like this:
* It's possible the tool has already been run on the overlay you are looking at, in that case, you don't need to run it again.
```
# split DRA (uses jpt_ prefix)
# python3 tools/split_jpt_yaml/split_jpt_yaml.py config/splat.us.dra.yaml asm/us/dra/data/ jpt_

# split NO3 (uses jtbl_ prefix)
# python3 tools/split_jpt_yaml/split_jpt_yaml.py config/splat.us.stno3.yaml asm/us/st/no3/data/ jtbl_
```
* Look for the `Cut below this line:` print and copy the output below that.
* Paste the resulting output back into the yaml. For example in `DRA`:
```
segments:
  - name: dra
    type: code
    start: 0x00000000
    vram:  0x800A0000
    subalign: 4
    subsegments:
      (paste output here)
```
* The new function needs to be split into a new file. For example if our original C file is the following, and we want to decompile `func_80133BDC`, `func_80133BDC` needs to be at the start of the new file.
```
INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80133960);
INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80133BDC);
INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80133FCC);
```
* So we will have:
```
// 75F54.c
INCLUDE_ASM("asm/us/dra/nonmatchings/75F54", func_80133960);

// 93BDC.c
INCLUDE_ASM("asm/us/dra/nonmatchings/93BDC", func_80133BDC);
INCLUDE_ASM("asm/us/dra/nonmatchings/93BDC", func_80133FCC);
```
* The function contains `jpt_80133C10` as the jump table. So we will modify the yaml like this:

```
# before
      - [0x4208C, rodata] # jpt_80133C10
      - [0x420B4, rodata] # jpt_80135058

# after
      - [0x4208C, .rodata, 93BDC] # jpt_80133C10
      - [0x420B4, rodata] # jpt_80135058
```

* The `.` in `.rodata` indicates that the segment should be ignored in the final compilation and the table from `93BDC.c` should be used instead.

* Make sure to change the file paths for the `INCLUDE_ASM`s.

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
* I suspect that PSY-Q 3.5 have been used to originally compile the game
* `main.exe` uses PS-X libraries that might have been created with a different compiler and with `-O1` rather than `-O2`

## Special thanks

This project is possible thanks to the hard work of tools provided by the Decompilation community:

* [mips2c](https://github.com/matt-kempster/m2c) from @matt-kempster to decompile MIPS assembly into C. This proven to be more accurate than Hexrays IDA and Ghidra.
* [splat](https://github.com/ethteck/splat) from @ethteck to disassemble code and extract data with a symbol map. This tool provides the fundamental of the SOTN decomp.
* [asm-differ](https://github.com/simonlindholm/asm-differ) from @simonlindholm to know how the decompiled code compares to the original binary.
* [decomp-permuter](https://github.com/simonlindholm/decomp-permuter) from @simonlindholm to pick different versions of the same code that better matches the original binary.
* [decomp.me](https://github.com/decompme/decomp.me/) by @ethteck, @nanaian and @mkst to provide a collaborative decompilation site to share and contribute to work-in-progress decompiled functions.
* [frogress](https://github.com/decompals/frogress) by @ethteck to store and retrieve progression data.
* [esa-new](https://github.com/mkst/esa-new) by @mkst as an inspiration on how to set-up a PS1 decompilation project.
* [oot](https://github.com/zeldaret/oot) as an inspiration of what it is possible to achieve with a complete decompiled video game.
