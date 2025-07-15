// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../no2/no2.h"

void func_pspeu_092575D8(Entity* self) {
    Primitive* tempPrim;
    s16 offsetX;
    s16 offsetY;
    s32 primIter;

    if (self->params) {
        offsetX = 0x0;
        offsetY = -0x40;
    } else {
        offsetX = 0x0;
        offsetY = 0x58;
    }
    if (!self->step) {
        self->step += 1;
        if (self->params) {
            self->primIndex = (s32)g_api_AllocPrimitives(PRIM_GT4, 0x20);
        } else {
            self->primIndex = (s32)g_api_AllocPrimitives(PRIM_GT4, 8);
        }
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        tempPrim = &g_PrimBuf[self->primIndex];
        primIter = 0;
        while (tempPrim != NULL) {
            tempPrim->x0 = tempPrim->x2 = (primIter & 7) * 0x40 + offsetX;
            tempPrim->x1 = tempPrim->x3 = (s16)tempPrim->x0 + 0x48;
            tempPrim->y1 = tempPrim->y0 = ((primIter >> 3) * 0x64) + offsetY;
            tempPrim->y3 = tempPrim->y2 = (s16)tempPrim->y0 + 0x6C;
            tempPrim->u0 = 0x80;
            tempPrim->v0 = 0;
            tempPrim->u1 = 0xC8;
            tempPrim->v1 = 0;
            tempPrim->u2 = 0x80;
            tempPrim->v2 = 0x68;
            tempPrim->u3 = 0xC8;
            tempPrim->v3 = 0x68;
            tempPrim->tpage = 0xF;
            tempPrim->clut = 0x36;
            tempPrim->priority = 0x10;
            tempPrim->drawMode = DRAW_DEFAULT;
            primIter += 1;
            tempPrim = tempPrim->next;
        }
    }
}

INCLUDE_ASM("st/no2_psp/nonmatchings/no2_psp/1FF58", func_pspeu_09257810);

INCLUDE_ASM("st/no2_psp/nonmatchings/no2_psp/1FF58", func_pspeu_09257B10);

INCLUDE_ASM("st/no2_psp/nonmatchings/no2_psp/1FF58", func_pspeu_09257B78);

INCLUDE_ASM("st/no2_psp/nonmatchings/no2_psp/1FF58", func_pspeu_09257C00);
