# Castlevania: Symphony of the Night Decompilation

A work-in-progress decompilation of Castlevania Symphony of the Night for Sony PlayStation 1, Sony PlayStation Portable and Sega Saturn. It aims to recreate the source code from the existing binaries using static and/or dynamic analysis. The code compiles byte-for-byte to the same binaries of the game, effectively being a matching decompilation.

It currently supports the following versions of the game:

* `us` the reference build with the serial number SLUS-00067
* `hd` an unreleased PS1 Japanese build found in Castlevania: Dracula X Chronicles game data
* `pspeu` European build from Castlevania: Dracula X Chronicles
* `saturn` the port created by an external development team

This repo does not include any assets or assembly code necessary for compiling the binaries. A prior copy of the game is required to extract the required assets.

## Bins decomp progress

| File name  | Code coverage | Decomp functions | Description
|------------|----------|-----------|-------------
| SLUS_000.67   | ![code coverage SLUS_000.67](https://img.shields.io/endpoint?label=SLUS_000.67%20code&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Fcode%2F%3Fmode%3Dshield%26measure%3Dmain) | ![decompiled functions](https://img.shields.io/endpoint?label=SLUS_000.67%20funcs&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Ffunctions%2F%3Fmode%3Dshield%26measure%3Dmain) | Shared libraries
| DRA.BIN    | ![code coverage DRA.BIN](https://img.shields.io/endpoint?label=DRA%20code&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Fcode%2F%3Fmode%3Dshield%26measure%3Ddra) | ![decompiled functions](https://img.shields.io/endpoint?label=DRA%20funcs&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Ffunctions%2F%3Fmode%3Dshield%26measure%3Ddra) | Game engine
| BIN/RIC.BIN    | ![code coverage RIC.BIN](https://img.shields.io/endpoint?label=RIC%20code&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Fcode%2F%3Fmode%3Dshield%26measure%3Dric) | ![decompiled functions](https://img.shields.io/endpoint?label=RIC%20funcs&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Ffunctions%2F%3Fmode%3Dshield%26measure%3Dric) | Playable Richter
| BIN/WEAPON0.BIN    | ![code coverage WEAPON0.BIN](https://img.shields.io/endpoint?label=WEAPON0%20code&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Fcode%2F%3Fmode%3Dshield%26measure%3Dweapon) | ![decompiled functions](https://img.shields.io/endpoint?label=WEAPON0%20funcs&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Ffunctions%2F%3Fmode%3Dshield%26measure%3Dweapon) | Equippables
| ST/CEN/CEN.BIN | ![code coverage CEN.BIN](https://img.shields.io/endpoint?label=CEN%20code&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Fcode%2F%3Fmode%3Dshield%26measure%3Dstcen) | ![decompiled functions](https://img.shields.io/endpoint?label=CEN%20funcs&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Ffunctions%2F%3Fmode%3Dshield%26measure%3Dstcen) | Center
| ST/DRE/DRE.BIN | ![code coverage DRE.BIN](https://img.shields.io/endpoint?label=DRE%20code&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Fcode%2F%3Fmode%3Dshield%26measure%3Dstdre) | ![decompiled functions](https://img.shields.io/endpoint?label=DRE%20funcs&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Ffunctions%2F%3Fmode%3Dshield%26measure%3Dstdre) | Nightmare
| ST/MAD/MAD.BIN | ![code coverage MAD.BIN](https://img.shields.io/endpoint?label=MAD%20code&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Fcode%2F%3Fmode%3Dshield%26measure%3Dstmad) | ![decompiled functions](https://img.shields.io/endpoint?label=MAD%20funcs&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Ffunctions%2F%3Fmode%3Dshield%26measure%3Dstmad) | Debug Room
| ST/NO0/NO0.BIN | ![code coverage NO0.BIN](https://img.shields.io/endpoint?label=NO0%20code&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Fcode%2F%3Fmode%3Dshield%26measure%3Dstno0) | ![decompiled functions](https://img.shields.io/endpoint?label=NO0%20funcs&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Ffunctions%2F%3Fmode%3Dshield%26measure%3Dstno0) | Marble Gallery
| ST/NO3/NO3.BIN | ![code coverage NO3.BIN](https://img.shields.io/endpoint?label=NO3%20code&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Fcode%2F%3Fmode%3Dshield%26measure%3Dstno3) | ![decompiled functions](https://img.shields.io/endpoint?label=NO3%20funcs&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Ffunctions%2F%3Fmode%3Dshield%26measure%3Dstno3) | Entrance (first visit)
| ST/NP3/NP3.BIN | ![code coverage NP3.BIN](https://img.shields.io/endpoint?label=NP3%20code&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Fcode%2F%3Fmode%3Dshield%26measure%3Dstnp3) | ![decompiled functions](https://img.shields.io/endpoint?label=NP3%20funcs&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Ffunctions%2F%3Fmode%3Dshield%26measure%3Dstnp3) | Entrance
| ST/NZ0/NZ0.BIN | ![code coverage NZ0.BIN](https://img.shields.io/endpoint?label=NZ0%20code&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Fcode%2F%3Fmode%3Dshield%26measure%3Dstnz0) | ![decompiled functions](https://img.shields.io/endpoint?label=NZ0%20funcs&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Ffunctions%2F%3Fmode%3Dshield%26measure%3Dstnz0) | Alchemy Laboratory
| ST/SEL/SEL.BIN | ![code coverage SEL.BIN](https://img.shields.io/endpoint?label=SEL%20code&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Fcode%2F%3Fmode%3Dshield%26measure%3Dstsel) | ![decompiled functions](https://img.shields.io/endpoint?label=SEL%20funcs&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Ffunctions%2F%3Fmode%3Dshield%26measure%3Dstsel) | Title screen
| ST/ST0/ST0.BIN | ![code coverage ST0.BIN](https://img.shields.io/endpoint?label=ST0%20code&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Fcode%2F%3Fmode%3Dshield%26measure%3Dstst0) | ![decompiled functions](https://img.shields.io/endpoint?label=ST0%20funcs&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Ffunctions%2F%3Fmode%3Dshield%26measure%3Dstst0) | Final Stage: Bloodlines
| ST/WRP/WRP.BIN | ![code coverage WRP.BIN](https://img.shields.io/endpoint?label=WRP%20code&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Fcode%2F%3Fmode%3Dshield%26measure%3Dstwrp) | ![decompiled functions](https://img.shields.io/endpoint?label=WRP%20funcs&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Ffunctions%2F%3Fmode%3Dshield%26measure%3Dstwrp) | Warp Room
| ST/RWRP/RWRP.BIN | ![code coverage RWRP.BIN](https://img.shields.io/endpoint?label=RWRP%20code&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Fcode%2F%3Fmode%3Dshield%26measure%3Dstrwrp) | ![decompiled functions](https://img.shields.io/endpoint?label=RWRP%20funcs&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Ffunctions%2F%3Fmode%3Dshield%26measure%3Dstrwrp) | Warp Room (reverse)
| BOSS/MAR/MAR.BIN | ![code coverage MAR.BIN](https://img.shields.io/endpoint?label=MAR%20code&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Fcode%2F%3Fmode%3Dshield%26measure%3Dbomar) | ![decompiled functions](https://img.shields.io/endpoint?label=MAR%20funcs&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Ffunctions%2F%3Fmode%3Dshield%26measure%3Dbomar) | Maria cutscene
| BOSS/RBO3/RBO3.BIN | ![code coverage RBO3.BIN](https://img.shields.io/endpoint?label=RBO3%20code&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Fcode%2F%3Fmode%3Dshield%26measure%3Dborbo3) | ![decompiled functions](https://img.shields.io/endpoint?label=RBO3%20funcs&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Ffunctions%2F%3Fmode%3Dshield%26measure%3Dborbo3) | Medusa boss
| SERVANT/TT_000.BIN | ![code coverage TT_000.BIN](https://img.shields.io/endpoint?label=TT_000%20code&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Fcode%2F%3Fmode%3Dshield%26measure%3Dtt_000) | ![decompiled functions](https://img.shields.io/endpoint?label=TT_000%20funcs&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Ffunctions%2F%3Fmode%3Dshield%26measure%3Dtt_000) | Bat Familiar
| SERVANT/TT_001.BIN | ![code coverage TT_001.BIN](https://img.shields.io/endpoint?label=TT_001%20code&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Fcode%2F%3Fmode%3Dshield%26measure%3Dtt_001) | ![decompiled functions](https://img.shields.io/endpoint?label=TT_001%20funcs&url=https%3A%2F%2Fprogress.deco.mp%2Fdata%2Fsotn%2Fus%2Ffunctions%2F%3Fmode%3Dshield%26measure%3Dtt_001) | Ghost Familiar

Code coverage means how many bytes of code have been successfully converted from assembly into C code, while decomp function is how many functions have been successfully decompiled.

## Useful links

* [Build guide](https://github.com/Xeeynamo/sotn-decomp/wiki/Build)
* [Decompilation guide](https://github.com/Xeeynamo/sotn-decomp/wiki/Decompilation)
* [Progress report](https://sotn.xee.dev/)

Decompiling a game is a mastodontic task. If you have some basic programming skills, please join us in this journey. Any contribution will be very appreciated!

[![Join to our Discord server](https://discord.com/api/guilds/1079389589950705684/widget.png?style=banner2)](https://sotn-discord.xee.dev/)

## Special thanks

This project is possible thanks to the hard work of tools provided by the Decompilation community:

* [mips2c](https://github.com/matt-kempster/m2c) from @matt-kempster to decompile MIPS assembly into C. This has proven to be more accurate than Hexrays IDA and Ghidra.
* [splat](https://github.com/ethteck/splat) from @ethteck to disassemble code and extract data with a symbol map. This tool provides the fundamentals of the SOTN decomp.
* [asm-differ](https://github.com/simonlindholm/asm-differ) from @simonlindholm to know how the decompiled code compares to the original binary.
* [decomp-permuter](https://github.com/simonlindholm/decomp-permuter) from @simonlindholm to pick different versions of the same code that better matches the original binary.
* [maspsx](https://github.com/mkst/maspsx) by @mkst to replicate the customized assembler used in the official PSX SDK.
* [decomp.me](https://github.com/decompme/decomp.me/) by @ethteck, @nanaian and @mkst to provide a collaborative decompilation site to share and contribute to work-in-progress decompiled functions.
* [frogress](https://github.com/decompals/frogress) by @ethteck to store and retrieve progression data.
* [esa-new](https://github.com/mkst/esa-new) by @mkst as an inspiration on how to set-up a PS1 decompilation project.
* [oot](https://github.com/zeldaret/oot) as an inspiration of what it is possible to achieve with a complete decompiled video game.
