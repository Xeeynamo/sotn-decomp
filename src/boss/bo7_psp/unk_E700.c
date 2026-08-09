// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../bo7/bo7.h"

INCLUDE_ASM("boss/bo7_psp/nonmatchings/bo7_psp/unk_E700", func_us_80195C50);

INCLUDE_ASM("boss/bo7_psp/nonmatchings/bo7_psp/unk_E700", EntityBreakable);

INCLUDE_ASM("boss/bo7_psp/nonmatchings/bo7_psp/unk_E700", EntityBreakableDebris);

// bo7 arena floor sits higher than rbo0
#define BOSS_FLOOR_Y 0xD0
#include "../e_boss_floor_snap.h"

INCLUDE_ASM("boss/bo7_psp/nonmatchings/bo7_psp/unk_E700", func_us_80194D3C);

INCLUDE_ASM("boss/bo7_psp/nonmatchings/bo7_psp/unk_E700", func_us_801959E0);

INCLUDE_ASM("boss/bo7_psp/nonmatchings/bo7_psp/unk_E700", func_us_80195AF0);

INCLUDE_ASM("boss/bo7_psp/nonmatchings/bo7_psp/unk_E700", EntityBackgroundBlock);
