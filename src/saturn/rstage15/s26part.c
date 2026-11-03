// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

struct {
    u8 animation[10];
    s16 offset[2];
    u16 padding;
} g_RStage15CopperArmorWeaponData = {
    {4, 3, 4, 4, 4, 5, 4, 6, 0, 0},
    {0, 28},
    0,
};
