// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "no0.h"

extern void func_us_801CC8F8(Entity*);
extern u16 D_us_80180A88[];

void func_us_801CC750(Entity* self) {
    Entity* entityPtr;
    s16 i;
    Primitive* prim;
    s32 primIndex;

    if (self->step != 0) {
        return;
    }

    InitializeEntity(D_us_80180A88);
    primIndex = g_api.AllocPrimitives(PRIM_GT4, 9);
    if (primIndex != -1) {
        prim = &g_PrimBuf[primIndex];
        i = -0x10;
        self->primIndex = primIndex;
        self->flags |= FLAG_HAS_PRIMS;
        while (prim != NULL) {
            prim->tpage = 0xF;
            prim->clut = 0x2A;
            prim->u0 = prim->u2 = 0xC0;
            prim->u1 = prim->u3 = 0xE0;
            prim->v0 = prim->v1 = 0x80;
            prim->v2 = prim->v3 = 0xB0;
            prim->x0 = prim->x2 = i;
            prim->x1 = prim->x3 = i + 0x20;
            prim->y0 = prim->y1 = 0x91;
            prim->y2 = prim->y3 = 0xC1;
            prim->priority = 0;
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
            i += 0x1E;
        }
    }

    entityPtr = &self[1];

    for (i = -0x10; i < 0x130; i += 0x60) {
        DestroyEntity(entityPtr);
        entityPtr->entityId = 0x16;
        entityPtr->pfnUpdate = func_us_801CC8F8;
        entityPtr->posY.i.hi = 0x8E;
        entityPtr->posX.i.hi = i;

        entityPtr++;
    }
}

extern s32 D_80097408[];

void func_us_801CC8F8(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 3;
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 0x54;
        self->unk68 = 0xC0;
        self->flags &= ~FLAG_UNK_20000000;
        return;
    }

    if (self->posX.i.hi < -0x40) {
        self->posX.i.hi += 0x180;
    }

    if (self->posX.i.hi >= 0x141) {
        self->posX.i.hi -= 0x180;
    }
}

INCLUDE_ASM("st/no0/nonmatchings/4C750", func_us_801CC9B4);

INCLUDE_ASM("st/no0/nonmatchings/4C750", func_us_801CCAAC);

INCLUDE_ASM("st/no0/nonmatchings/4C750", func_us_801CCBE4);

INCLUDE_ASM("st/no0/nonmatchings/4C750", func_us_801CCC2C);

INCLUDE_ASM("st/no0/nonmatchings/4C750", func_us_801CCC74);

INCLUDE_ASM("st/no0/nonmatchings/4C750", func_us_801CD750);

INCLUDE_ASM("st/no0/nonmatchings/4C750", func_us_801CD864);

void UpdateStatueTiles(s32 tilePos, s32 tile) {
    u32 i;

    for (i = 0; i < 6; i++) {
        g_Tilemap.fg[tilePos] = tile;
        tilePos++;
        g_Tilemap.fg[tilePos] = tile;
        tilePos += 15;
    }
}

INCLUDE_ASM("st/no0/nonmatchings/4C750", func_us_801CDB20);

INCLUDE_ASM("st/no0/nonmatchings/4C750", func_us_801CDE48);

INCLUDE_ASM("st/no0/nonmatchings/4C750", func_us_801CE058);

INCLUDE_ASM("st/no0/nonmatchings/4C750", func_us_801CE0F8);

void func_us_801CE2D8(void) {}

INCLUDE_ASM("st/no0/nonmatchings/4C750", func_us_801CE2E0);

INCLUDE_RODATA("st/no0/nonmatchings/4C750", D_us_801C14A8);
