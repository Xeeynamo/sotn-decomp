// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "no0.h"

u8 func_us_801D6254(s16 arg0[]) {
    Collider collider;
    s16 xDir;
    u8 ret = 0;
    s32 i;
    s16 posX;
    s16 posX2;
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

    posX = posX2;
    g_api.CheckCollision(posX, posY, &collider, 0);
    if (collider.effects & EFFECT_SOLID) {
        g_CurrentEntity->posY.i.hi += collider.unk18;
        g_CurrentEntity->velocityY = 0;
        ret |= 1;
    }
    posX = posX2;
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

void func_us_801D6474(Primitive* prim) {
    Collider collider;
    Entity* newEntity;
    s16 xVal;
    s16 yVal;

    UnkPrimHelper(prim);
    switch (prim->next->u2) {
    case 0:
        LOW(prim->next->u0) = ((Random() & 31) << 12) - 0x10000;
        LOW(prim->next->r1) = -(Random() & 31) << 12;
        if (LOH(prim->next->r2) + LOH(prim->next->b2) >= 48) {
            prim->next->u2 = 1;
            prim->next->x3 = 256;
        } else {
            prim->next->u2 = 2;
            prim->next->x3 = ((Random() & 15) * 4) + 8;
        }
        // fallthrough
    case 1:
        xVal = prim->next->x1;
        yVal = prim->next->y0 + 4;
        g_api.CheckCollision(xVal, yVal, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            prim->next->y0 += collider.unk18;
            if (LOW(prim->next->r1) < 16384) {
                prim->next->x3 = 1;
            }
            LOW(prim->next->r1) = -LOW(prim->next->r1);
            LOW(prim->next->r1) -= LOW(prim->next->r1) / 2;
        }
        // fallthrough
    case 2:
        if (LOW(prim->next->u0) > 0) {
            HIH(prim->next->u1) -= 32;
        } else {
            HIH(prim->next->u1) += 32;
        }
        LOW(prim->next->r1) += 6144;
        prim->next->x3 -= 1;
        if (!prim->next->x3) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(2, newEntity);
                newEntity->posX.i.hi = prim->next->x1;
                newEntity->posY.i.hi = prim->next->y0;
                newEntity->params = 0;
            }
            UnkPolyFunc0(prim);
        }
        break;
    }
}

INCLUDE_ASM("st/no0/nonmatchings/e_marionette", func_us_801D66F8);
