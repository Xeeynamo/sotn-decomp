// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "no0.h"

u8 func_us_801D6254(s16 arg0[]) {
    Collider collider;
    s16 xDir;
    u8 ret = 0;
    s32 i;
    s16 posX;
    s16 posX2; // Possible !FAKE here
    s16 posY;
    s16 posY2;

    g_CurrentEntity->posX.val += g_CurrentEntity->velocityX;
    g_CurrentEntity->posY.val += g_CurrentEntity->velocityY;
    posX2 = g_CurrentEntity->posX.i.hi;
    posY = g_CurrentEntity->posY.i.hi + *arg0++;
    posY2 = g_CurrentEntity->posY.i.hi + *arg0++;

    if (g_CurrentEntity->velocityX > 0) {
        xDir = *arg0;
    } else {
        xDir = -*arg0;
    }

    posX = posX2; // Possible !FAKE here
    g_api.CheckCollision(posX, posY, &collider, 0);
    if (collider.effects & EFFECT_SOLID) {
        g_CurrentEntity->posY.i.hi += collider.unk18;
        g_CurrentEntity->velocityY = 0;
        ret |= 1;
    }
    posX = posX2; // Possible !FAKE here
    g_api.CheckCollision(posX, posY2, &collider, 0);
    if (collider.effects & EFFECT_SOLID) {
        g_CurrentEntity->posY.i.hi += collider.unk20;
        g_CurrentEntity->velocityY = 0;
        ret |= 2;
    }

    posY2 += 2;
    for (i = 0; i < 5; i++, posY2 += 5) {
        posX = g_CurrentEntity->posX.i.hi + xDir;
        g_api.CheckCollision(posX, posY2, &collider, 0);
        if ((collider.effects & (EFFECT_SOLID | EFFECT_UNK_0002)) &&
            !(collider.effects & EFFECT_UNK_8000)) {
            ret |= 4;
            if (g_CurrentEntity->velocityX > 0) {
                g_CurrentEntity->posX.i.hi += collider.unk14;
            } else {
                g_CurrentEntity->posX.i.hi += collider.unk1C;
            }
            g_CurrentEntity->velocityX = 0;
            break;
        }
    }

    return ret;
}

INCLUDE_ASM("st/no0/nonmatchings/e_marionette", func_us_801D6474);

INCLUDE_ASM("st/no0/nonmatchings/e_marionette", func_us_801D66F8);
