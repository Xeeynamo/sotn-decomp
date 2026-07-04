// SPDX-License-Identifier: AGPL-3.0-or-later

#include "rno3.h"

u16 g_WaterSounds[] = {SFX_WATER_SPLASH_JUMP, SFX_WATER_SPLASH_MOVE};

s16 g_WaterXTbl[] = {
    0,   768, 0, 440, 512, 7,  7, 0,   0,   150, 0, 184,
    256, 7,   7, 0,   48,  68, 0, 468, 512, 7,   7, 0,
};

s16 unused[] = {0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 257};
