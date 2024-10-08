// SPDX-License-Identifier: AGPL-3.0-or-later
#include "servant.h"

// ability stats for level / 10
// 0 - delay counter
// 1 - spell Id
// 2 - make bad attacks (skips enemy hitbox & 8)
s32 AbilityStats[][3] = {
    {120, 17, 1}, {120, 17, 1}, {100, 17, 1}, {100, 17, 1}, {90, 17, 0},
    {90, 17, 0},  {75, 17, 0},  {75, 18, 0},  {60, 18, 0},  {60, 18, 0},
};

// Ghost specific clut
u16 GhostClut[] = {
    0x0000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x7FFF, 0x8000,
    0x8000, 0x8000, 0xFCE7, 0xFDEF, 0xFEF7, 0xFFFF, 0x8000, 0x8000,
};

// x offsets for positioning primitives
u16 D_us_801705A0[4] = {6, 3, 8, 0};

// y offsets for positioning primitives
u16 D_us_801705A8[4] = {-20, -18, -15, 0};
