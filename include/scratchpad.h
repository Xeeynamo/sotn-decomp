// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef SCRATCHPAD_H
#define SCRATCHPAD_H

// Access to the Scratchpad memory. Different on different systems.
#if defined(VERSION_PC)
#define SP_LEN 0x400
#define SP(x) (&sp[x])
#else
#if defined(VERSION_PSP)
#define SCRATCH_PAD 0x00010000
#else
#define SCRATCH_PAD 0x1F800000
#endif
#define SP(x) (SCRATCH_PAD + (x))
#endif

#define SPAD(x) ((s32*)SP((x) * sizeof(s32)))

#endif // SCRATCHPAD_H
