// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rdai/rdai.h"

s32 SpearGuardCheckCollision(void) {
    Collider collider;
    s32 x;
    s32 y;

    g_CurrentEntity->posX.val += g_CurrentEntity->velocityX;
    g_CurrentEntity->posY.i.hi -= 3;
    x = g_CurrentEntity->posX.i.hi;
    y = g_CurrentEntity->posY.i.hi - 0x1E;
    g_api.CheckCollision(x, y, &collider, 0);

    if (collider.effects & EFFECT_SOLID) {
        y = (g_CurrentEntity->posY.i.hi += collider.unk20);
    } else {
        return false;
    }

    if (g_CurrentEntity->velocityX == 0) {
        return true;
    }

    if (g_CurrentEntity->velocityX > 0) {
        x += 0x20;
        y -= 0x24;
    } else {
        x -= 0x20;
        y += 0x1C;
    }
    g_api.CheckCollision(x, y, &collider, 0);
    if (!(collider.effects & EFFECT_UNK_8000)) {
        return false;
    }
    return true;
}

#include "../approach_s16.h"

INCLUDE_ASM("st/rdai_psp/nonmatchings/rdai_psp/e_archer", func_us_801BF830);

// Child parts share one implementation; only the fixed EInit address is local.
#include "../e_rdai_unk1f.h"

#include "../e_rdai_archer.h"

INCLUDE_ASM("st/rdai_psp/nonmatchings/rdai_psp/e_archer", func_us_801C0240);

INCLUDE_ASM("st/rdai_psp/nonmatchings/rdai_psp/e_archer", func_us_801C0528);

INCLUDE_ASM("st/rdai_psp/nonmatchings/rdai_psp/e_archer", func_us_801C0898);
