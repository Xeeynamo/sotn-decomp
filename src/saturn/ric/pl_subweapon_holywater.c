// SPDX-License-Identifier: AGPL-3.0-or-later
#include "richter.h"

void RicEntityNotImplemented3() {}

// RicEntitySubwpnHolyWaterBreakGlass
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B9668, func_060B9668);

INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B9978, func_060B9978);

// RicEntityCrashHydroStorm
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B9A50, func_060B9A50);

// RicCheckHolyWaterCollision
s32 RicCheckHolyWaterCollision(s32 baseY, s32 baseX) {
    Collider res1;
    Collider res2;
    s32 newY;
    s32 x;
    s32 y;
    s32 collEffs;
    const u32 colFullSet = 0xF801;
    const u32 colSetNo800 = 0xF001;
    const u32 colSet1 = 0x8801;
    const u32 colSet2 = 0x8001;

    x = g_CurrentEntity->posX.val + baseX;
    y = g_CurrentEntity->posY.val + baseY;
    CheckCollision(x, y, &res1, 0);
    collEffs = res1.effects & colFullSet;
    y = y - FIX(1) + res1.unk18;
    CheckCollision(x, y, &res2, 0);
    newY = g_CurrentEntity->posY.val + res1.unk18 + baseY;

    if ((collEffs & colSet1) == EFFECT_SOLID ||
        (collEffs & colSet1) == (EFFECT_UNK_0800 | EFFECT_SOLID)) {
        collEffs = res2.effects & colSetNo800;
        if (!(collEffs & EFFECT_SOLID)) {
            g_CurrentEntity->posY.val = newY;
            return 1;
        }
        if ((res2.effects & colSet2) == colSet2) {
            g_CurrentEntity->posY.val = newY - FIX(1) + res2.unk18;
            return collEffs;
        }
        return 0;
    } else if ((collEffs & colSet2) == colSet2) {
        g_CurrentEntity->posY.val = newY;
        return collEffs & colSetNo800;
    }
    return 0;
}

// SAT func_060B9E40
// Equivalent to DRA func_80125B6C
s32 func_8016840C(s32 y, s32 x) {
    Collider collider;
    s32 xShift;
    if (g_CurrentEntity->velocityX == 0) {
        return 0;
    }
    CheckCollision(g_CurrentEntity->posX.val + x, g_CurrentEntity->posY.val + y,
                   &collider, 0);
    if (g_CurrentEntity->velocityX > 0) {
        xShift = collider.unk14;
    } else {
        xShift = collider.unk1C;
    }
    if (collider.effects & EFFECT_SIDE) {
        g_CurrentEntity->posX.val += xShift;
        return 2;
    }
    return 0;
}

// RicEntitySubwpnHolyWater
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60B9EA0, func_060B9EA0);

// RicEntitySubwpnHolyWaterFlame
INCLUDE_ASM("asm/saturn/richter/f_nonmat", f60BA3DC, func_060BA3DC);
