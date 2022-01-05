# Castlevania: Symphony of the Night disassembly

Recompilable code that creates 1:1 binaries for the commercial videogame Castlevania: Symphony of the Night for the PlayStation 1. This repository aims to create a full decompilation in C.

## Game revision

| SHA-1 checksum                             | File name | Version    | Progress
|--------------------------------------------|-----------|------------|----------
| `54828d4e44ea9575f2a0917ff63def42a304abff` | main.exe  | SLUS-00067 | N/A 
| `2eac5f7162e77416166c2511c787995488f01c37` | DRA.BIN   | SLUS-00067 | ![progress DRA.BIN](https://img.shields.io/endpoint?url=https://raw.githubusercontent.com/Xeeynamo/sotn-decomp/gh-pages/assets/progress-dra.json)

## Build

1. You need `gcc-mipsel-linux-gnu` that you can easily install on any Debian-based Linux distribution. On Windows it is highly recommended to just use Ubuntu with WSL
1. Place your `main.exe` from the file `SLUS_000.67` and `DRA.BIN` in the root directory
1. Run `make extract` to generate the assembly files
1. Run `make all` to compile the binaries into the `build/` directory

# Notes

* I suspect that GCC 2.7.2 / PSY-Q 3.6 have been used to originally compile `DRA.BIN`
* `main.exe` uses PS-X libraries that might've been created with a different compiler and with `-O1` rather than `-O2`

## To do

The project is very barebone at the moment and there is a massive room of improvement, mostly in the infrastructure:

* The zone overlays (`ST/{ZONE}/{ZONE}.BIN`) are not yet disassembled
* There is no CI/CD pipeline to test the correctness of the compiled code
