// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../bo7/bo7.h"

INCLUDE_ASM("boss/bo7_psp/nonmatchings/bo7_psp/unk_E700", func_us_80195C50);

INCLUDE_ASM("boss/bo7_psp/nonmatchings/bo7_psp/unk_E700", EntityBreakable);

INCLUDE_ASM("boss/bo7_psp/nonmatchings/bo7_psp/unk_E700", EntityBreakableDebris);

// Snaps the boss to the arena floor once it falls low enough. Same routine
// as rbo0's copy, with bo7's higher floor (0xD0 vs 0xE0).
bool func_us_80194338(s16* offsets) {
    s32 posY;

    offsets++;
    posY = g_CurrentEntity->posY.i.hi + *offsets + g_Tilemap.scrollY.i.hi;
    posY = 0xD0 - posY;
    if (posY <= 0) {
        g_CurrentEntity->posY.i.hi += posY;
        g_CurrentEntity->velocityX = 0;
        g_CurrentEntity->velocityY = 0;
        return true;
    }
    return false;
}

INCLUDE_ASM("boss/bo7_psp/nonmatchings/bo7_psp/unk_E700", func_us_80194D3C);

INCLUDE_ASM("boss/bo7_psp/nonmatchings/bo7_psp/unk_E700", func_us_801959E0);

INCLUDE_ASM("boss/bo7_psp/nonmatchings/bo7_psp/unk_E700", func_us_80195AF0);

INCLUDE_ASM("boss/bo7_psp/nonmatchings/bo7_psp/unk_E700", EntityBackgroundBlock);
