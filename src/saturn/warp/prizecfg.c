// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

typedef struct {
    s8 values[2];
    u8 padding[2];
} WarpHeartPrizeValues;

typedef struct {
    u16 indices[9];
    u16 padding;
} WarpSubweaponIndices;

WarpHeartPrizeValues g_WarpHeartPrizes = {{1, 5}, {0, 0}};

u32 g_WarpGoldPrizes[10] = {
    1, 25, 50, 100, 250, 400, 700, 1000, 2000, 5000,
};

WarpSubweaponIndices g_WarpAlucardSubweaponIndices = {
    {1, 2, 4, 3, 6, 5, 7, 8, 9},
    0,
};
