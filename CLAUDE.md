# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Repository Overview

This is a matching decompilation project for Castlevania: Symphony of the Night for PlayStation 1 and PlayStation Portable. The goal is to create C code that, when compiled, produces the exact same assembly as the original game ROM.

## Project naming

- `version` refers to different game builds, or game ROMs, such as `us`, `hd` or `pspeu`
- `overlay` a small programmable unit that can be loaded and unloaded in memory at a specific address
- `base` object files or linked binary from the decompiled source
- `target` object files or linked binary that are known to be matching

## Project Structure

- `src` decompiled (or partially decompiled) C code
- `include` common headers included in all C and/or assembly code
- `include/psxsdk` headers for the PlayStation 1 SDK
- `include/pspsdk` headers for the PlayStation Portable SDK
- `asm/{version}/{overlay}/nonmatchings` unmatched asm code extracted from the rom. Each file contains a separate function.
- `asm/{version}/{overlay}/matchings` decompiled assembly code for already matched C functions. We optionally keep this around as it's sometimes convenient to inspect.
- `asm/{version}/{overlay}/data` rough representation of the overlay data.
- `assets` binary asset blobs extracted from the rom
- `build/{version}/` is where all the built decompiled code is stored, and used as a base
- `expected/build/{version}/` the last known successful build, used as a target
- `build/{version}/*.elf` the overlays built as ELF files from the GNU linker
- `build/{version}/*.map` the generated map file from GNU linker, often containing useful information to know whenever the base symbols shifted compared to target.
- `build/{version}/*.bin` stripped elf file, and what it is actually used to verify if the final binary matches the original game binaries.
- `config/splat.{version}.{overlay}.yaml` contains the configuration used to generate the disassembled code.
- `config/symbols.{version}.txt` all shared symbols from a given version for all overlays.
- `config/symbols.{version}.{overlay}.txt` renamed symbols for the targeted overlay.

## The `INCLUDE_ASM` macro

It represents a function that has not yet been decompiled.

The macro format is `INCLUDE_ASM(path, function_name)`.

An example of the macro is `INCLUDE_ASM("servant/fname/nonmatchings/fname", func_80170914)`. This means inside the folder `asm/{version}/servant/fname/nonmatchings/fname` there is the function `func_80170914.s` not yet decompiled.

To decompile the function, the tool `.venv/bin/python3 ./tools/decompile.py {function_name}` needs to be called. The tool performs some math to create an approximation of the intended function to replace the `INCLUDE_ASM` macro.

Functions that are too difficult to match are not discarded, but also ignored during compilation time. The following pattern is used for functions that are not matching:

```c
#ifndef NON_MATCHING
INCLUDE_ASM(path, function_name);
#else
function_name() {
   ...
}
#endif
```

## Tasks

### Add a new symbol

Sometimes there are symbols that need to be renamed. Especially if the offset of a certain symbol overlaps with an earlier struct or array. These are the steps to add a new symbol:

1. Stash all work with `git stash`
2. Ensure a successful build with `make build`
3. Add the symbol to `config/symbols*` based on the appropriate version and overlay
4. Ensure successful build with `make build`
5. Regenerate disassembled code with `make clean && make build`
6. Regnerate target with `make expected`
7. Sort symbols by offset with `./tools/symbols.py sort config/<symbols_file_name>`
8. Unstash the changes with `git stash pop` and continue
9. Stage symbol with `git add config/<symbols_file_name>`

If step 3, 4 or 5 fails, iterate for a maximum of five times to try obtaining a successful build. If no successful build is made within the allowed maximum tries then:

1. Revert symbol changes with `git checkout config/`
2. Ensure successful build with `make clean && make build`
3. Unstash the changes with `git stash pop`, stop decompiling and notify me about the failure.

### Find function to decompile

It's easier to start from the easiest functions first. Target an overlay, search for source files that have the `INCLUDE_ASM` macro without the `#ifndef NON_MATCHING` on the line right before that. Verify the existence of the correspondent `asm/{version}/` path, then run `.venv/bin/python3 tools/score_functions.py --exhaustive <nonmatchings_dir>` to output a table with all the functions ordered by complexity. A complexity of 0.1 means the function is easy, while 1.0 is hard.

### Test if code is matching

`make build` builds all overlays and check whenever they're all matching their original code. It compiles the whole game source code for a targeted `version`. Matching overlays will have the ✅ emoji, while those that do not match will have a ❌ emoji.

`diff.py` shows the difference between base and target assembly code. Calling `.venv/bin/python3 tools/asm-differ/diff.py -mo --overlay <overlay> <function_name>` will show such differences, with the line of code where the assembly code lines are used. This tool is essential to know where to massage the code when trying to match new disassembled code.

### When the function is decompiled successfully

Great news. Make a checkpoint with `make expected && git add .`. The `make expected` re-generates the target, while `git add .` ensures all matching work is staged.

### Step by step decompilation guide

1. Always ensure we have a working build with `make build`.
2. Find the easiest function to decompile.
3. Decompile the function using the provided python tool.
4. Run `make build` to check whenever the code is matching. If it is, make a checkpoint and restart from step 1.
5. If the code does not build, resolve the C compilation errors to have a working build. Test with `make build`
6. If the code build but does not match, diff between target and base with the provided pythont tool to check where the mis-match happens.
7. Massage the code using the Code Quality Standars and reperat step 6 to check for improvements. If there are no improvements on the diff, then undo the change. If step 7 is repeated for over thirty times then move to step 8.
8. Add the `NON_MATCHING` decorator with the original `INCLUDE_ASM` restored, verify that `make build` generates a successful build and move on to the next function to decompile. If `make build` fails, make maximum three attempts to fix the issue. If it can be fixed, discard changes by restoring the previous checkpoint with `git checkout .` and move on to the next function to decompile.

## Validation Checklist

Before declaring any changes to C code complete (including decompiling functions), verify:

- [ ] No pointer arithmetic with manual offset calculations
- [ ] All struct field accesses use `->` or `.` operators
- [ ] No `void*` parameters that should be typed structs
- [ ] Attempt to re-use existing structs if fields match or makes logically sense given the context.
- [ ] Struct sizes match the assembly access patterns
- [ ] Array and structs do not overlap
- [ ] `make build` succeeds
- [ ] If build succeeds, code is properly formatted with `make ff`
- [ ] All `g_Entities->` or `g_Entities[0].` should be replaced with `PLAYER.`

## Code Quality Standards

### Avoid Pointer Arithmetic

When you see pointer arithmetic patterns like `*(type*)((u8*)ptr + offset)`:

1. **Identify the access pattern:**

   - What offset is being accessed? (e.g., `0xC` means field at offset 12)
   - Is it accessing an array element? (e.g., `arg1 * 36` means 36-byte elements)
   - What field within the element? (e.g., `+ 0xA` means field at offset 10)

2. **Create appropriate structs:**

   - Define the element struct with correct size and field offsets
   - Define the container struct with pointer at correct offset
   - Use meaningful names or `unk[Offset]` naming convention

3. **Verify struct sizes:**

   - Calculate total size to ensure it matches the multiplier in pointer arithmetic
   - Example: `arg1 * 36` means struct must be exactly 36 (0x24) bytes

### Naming conventions

Entity functions always have the signature `void f(Entity* self)`. Entity functions always use the state machine `self->step`, which is very often just a big `switch` where `case 0` always initializes the entity.

Some symbols such as `g_api` or `g_Tilemap` might be decompiled as `g_api_AllocPrimitives`. But the real symbol is `g_api.AllocPrimitives`. Use neighbour functions or neighbour sources as a reference to know which struct fields are real.

### Struct Modification and Extension

When modifying struct definitions:

- Search the entire codebase for other references to the same struct
- Check if other functions access fields at nearby offsets
- Verify ALL affected functions still match after struct changes
- Example: If you add a field at offset 0x14, search for all functions accessing that struct and verify they still compile to the correct offsets

### Avoid Redundent Declarations

After adding your decompiled function, check for any redundant extern declarations:

1. **Search for existing declarations**: For each extern function you used, search the codebase to see if it's already declared in a header file:

   - Use `grep -r "void functionName" include/` to search headers
   - Use `grep -r "void functionName" src/*.h` to search source headers

2. **Remove redundant externs**: If a function is already declared in an included header file, remove your extern declaration to avoid duplication

3. **Verify the build still works** after removing redundant externs

Example: If you added `extern void setCallback(void *);` but `task_scheduler.h` (which is already included) declares it, remove your extern declaration.
