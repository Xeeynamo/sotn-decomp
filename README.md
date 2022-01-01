# Castlevania: Symphony of the Night disassembly

Recompilable code that creates 1:1 binaries for the commercial videogame Castlevania: Symphony of the Night. This repository aims to create a full disassembly in C.

## Game revision

| SHA-1 checksum                             | File name | Version
|--------------------------------------------|-----------|---------
| `54828d4e44ea9575f2a0917ff63def42a304abff` | main.exe  | SLUS-00067
| `2eac5f7162e77416166c2511c787995488f01c37` | DRA.BIN   | SLUS-00067

## Build

1. You need `gcc-mipsel-linux-gnu` that you can easily install on any Debian-based Linux distribution. On Windows it is highly recommended to just use Ubuntu with WSL
1. Place your `main.exe` from the file `SLUS_000.67` and `DRA.BIN` in the root directory
1. Run `make extract` to generate the assembly files
1. Run `make all` to compile the binaries into the `build/` directory

Please double-check if the [MD5 matches](#game-revision).

## To do

The project is very barebone at the moment and there is a massive room of improvement, mostly in the infrastructure:

* I am not sure which GCC version is the most suitable and the C compiled code might be different from the original assembly
* There are no utilities to make a diff between the original executable and the current one
* There is no CI/CD pipeline to track the decompilation progress
* It is not known which PS1 SDK version has been used for the game
* The game executable `DRA.BIN` is not yet disassembled
* The zone overlays (`ST/{ZONE}/{ZONE}.BIN`) are not yet disassembled
