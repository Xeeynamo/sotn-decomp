// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno2/rno2.h"

extern EInit g_EInitEnvironment;
extern Primitive* FindFirstUnkPrim(Primitive* prim);
extern Primitive* FindFirstUnkPrim2(Primitive* prim, u8 index);

static s32 D_us_80180D48[][2] = {
    {FIX(-0.5), FIX(0.0)},      {FIX(-0.0625), FIX(-0.125)},
    {FIX(-0.375), FIX(0.0)},    {FIX(-0.03125), FIX(-0.125)},
    {FIX(-0.125), FIX(0.0625)}, {FIX(0.0), FIX(0.0625)},
    {FIX(0.0), FIX(0.25)},      {FIX(0.0), FIX(0.125)},
    {FIX(1.25), FIX(-1.75)},    {FIX(1.5), FIX(-1.875)},
    {FIX(0.5), FIX(-1.25)},     {FIX(0.75), FIX(-2.25)},
    {FIX(0.0), FIX(0.0)},       {FIX(0.0), FIX(0.125)},
    {FIX(0.0), FIX(0.21875)},   {FIX(0.0), FIX(0.375)},
};
static s16 D_us_80180DC8[] = {
    -0x040, 0x010, -0x030, 0x010, -0x020, 0x008, 0x000,  0x008, 0x060,
    0x100,  0x040, 0x020,  0x020, -0x018, 0x038, -0x030, 0x080, -0x080,
};

static void func_us_801B59C4(Primitive* prim) {
    Collider collider;
    Entity* tempEntity;
    Primitive* prim2;
    s32 i;
    s16 posX;
    s16 posY;

    switch (prim->next->u2) {
    case 0:
        prim->tpage = 0xF;
        prim->clut = 0x33;
        if (prim->next->r3 % 2) {
            prim->u0 = prim->u2 = 0xB8;
            prim->u1 = prim->u3 = 0xA8;
        } else {
            prim->u0 = prim->u2 = 0xA8;
            prim->u1 = prim->u3 = 0xB8;
        }
        if ((prim->next->r3 % 4) < 2) {
            prim->v0 = prim->v1 = 0xC8;
            prim->v2 = prim->v3 = 0xD8;
        } else {
            prim->v0 = prim->v1 = 0xD8;
            prim->v2 = prim->v3 = 0xC8;
        }
        prim->priority = 0x68;
        prim->drawMode = DRAW_UNK02;
        LOW(prim->next->u0) -= D_us_80180D48[prim->next->r3][0];
        LOW(prim->next->r1) = D_us_80180D48[prim->next->r3][1];
        LOH(prim->next->r2) = LOH(prim->next->b2) = 0x10;
        prim->next->u2 = 1;
        if (prim->next->r3 > 7 && prim->next->r3 < 12) {
            LOH(prim->next->r2) = LOH(prim->next->b2) = 8;
            prim->next->u2 = 4;
        }
        break;

    case 1:
        LOW(prim->next->r1) += 0x800;
        if (prim->next->r3 > 11) {
            LOW(prim->next->r1) += 0x1000;
        }
        LOH(prim->next->tpage) += D_us_80180DC8[prim->next->r3];

        posX = prim->next->x1;
        posY = prim->next->y0;
        posY += 4;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID || posY > 0x100) {
            posY += collider.unk18;
            for (i = 0; i < 3; i++) {
                prim2 = g_CurrentEntity->ext.breakableNo2.unk7C;
                prim2 = FindFirstUnkPrim2(prim2, 2);
                if (prim2 != NULL) {
                    UnkPolyFunc2(prim2);
                    prim2->next->u2 = 2;
                    prim2->next->y0 = posY - 8;
                    if (prim->next->r3 < 12) {
                        prim2->next->x1 = posX + i * 4;
                    } else {
                        prim2->next->x1 = posX;
                        prim2->next->u2 = 3;
                    }
                }
            }
            UnkPolyFunc0(prim);
            return;
        }
        break;

    case 2:
        prim->tpage = 0xF;
        prim->clut = 0x33;
        prim->u0 = prim->u2 = 0xB8;
        prim->u1 = prim->u3 = 0xC8;
        prim->v0 = prim->v1 = 0xC8;
        prim->v2 = prim->v3 = 0xD8;
        prim->priority = 0x6A;
        prim->drawMode = DRAW_UNK02;
        LOW(prim->next->u0) = (Random() & 7) * 0x2800;
        LOW(prim->next->r1) = FIX(-1.5) - ((Random() & 7) << 0xD);
        LOH(prim->next->r2) = LOH(prim->next->b2) = ((Random() & 3) * 2) + 8;
        prim->next->u2 = 4;
        break;

    case 3:
        prim->tpage = 0xF;
        prim->clut = 0x33;
        prim->u0 = prim->u2 = 0xB8;
        prim->u1 = prim->u3 = 0xC8;
        prim->v0 = prim->v1 = 0xC8;
        prim->v2 = prim->v3 = 0xD8;
        prim->priority = 0x6A;
        prim->drawMode = DRAW_UNK02;
        LOW(prim->next->u0) = FIX(-7.0/8) - ((Random() & 7) << 0xE);
        LOW(prim->next->r1) = FIX(-1.5) - ((Random() & 7) << 0xD);
        LOH(prim->next->r2) = LOH(prim->next->b2) = ((Random() & 3) * 2) + 8;
        if (LOW(prim->next->u0) < 0) {
            prim->next->r3 = 16;
        } else {
            prim->next->r3 = 17;
        }
        prim->next->u2 = 4;
        break;

    case 4:
        LOW(prim->next->r1) += 0x2000;
        if (prim->next->r3) {
            LOH(prim->next->tpage) += D_us_80180DC8[prim->next->r3];
        } else {
            LOH(prim->next->tpage) -= 0x40;
        }
        posX = prim->next->x1;
        posY = prim->next->y0;
        posY += LOH(prim->next->r2) / 2;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID || posY > 0x100) {
            prim->next->y0 += collider.unk18;
            LOW(prim->next->r1) = -LOW(prim->next->r1) / 2;
            if (LOW(prim->next->r1) > -0x4000) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromCurrentEntity(
                        E_INTENSE_EXPLOSION, tempEntity);
                    tempEntity->posX.i.hi = posX;
                    tempEntity->posY.i.hi = posY;
                    tempEntity->params = 0x10;
                }
                UnkPolyFunc0(prim);
            }
        }
        break;
    }
    UnkPrimHelper(prim);
}

INCLUDE_ASM("st/rno2_psp/nonmatchings/rno2_psp/e_secrets", func_us_801B5FB8_from_no2);

INCLUDE_ASM("st/rno2_psp/nonmatchings/rno2_psp/e_secrets", func_us_801AC54C_from_bo0);

INCLUDE_ASM("st/rno2_psp/nonmatchings/rno2_psp/e_secrets", func_us_801B6794);

INCLUDE_ASM("st/rno2_psp/nonmatchings/rno2_psp/e_secrets", EntityStoneBridgeSecret);
