// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz1.h"

INCLUDE_ASM("st/nz1/nonmatchings/water_effects", func_801C4144);

INCLUDE_ASM("st/nz1/nonmatchings/water_effects", EntityAlucardWaterEffect);

INCLUDE_ASM("st/nz1/nonmatchings/water_effects", EntitySplashWater);

INCLUDE_ASM("st/nz1/nonmatchings/water_effects", EntitySurfacingWater);

INCLUDE_ASM("st/nz1/nonmatchings/water_effects", EntitySideWaterSplash);

INCLUDE_ASM("st/nz1/nonmatchings/water_effects", EntitySmallWaterDrop);

extern EInit g_EInitCommon;
extern s16 (*g_api_func_800EDB58)(s32 kind, s32 count);

void EntityWaterDrop(Entity* self) {
    s16 x = self->posX.i.hi;
    s16 y = self->posY.i.hi;
    FakePrim* prim;
    s32 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        primIndex = g_api_func_800EDB58(PRIM_TILE_ALT, 0x21);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        self->ext.timer.t = 0x2F;
        prim = (FakePrim*)&g_PrimBuf[primIndex];

        while (1) {
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_UNK02 | DRAW_TRANSP;
            prim->priority = self->zPriority + 2;

            if (prim->next == NULL) {
                prim->drawMode &= ~DRAW_HIDE;
                prim->y0 = prim->x0 = prim->w = 0;
                break;
            }

            prim->posX.i.lo = prim->posY.i.lo = 0;
            prim->velocityY.val = (rand() & PSP_RANDMASK) * 8 + self->velocityY;
            prim->posY.i.hi = y + (rand() & 15);
            prim->posX.i.hi = x + (rand() & 31) - 16;
            prim->delay = (rand() & 15) + 32;
            prim->x0 = prim->posX.i.hi;
            prim->y0 = prim->posY.i.hi;
            prim->r0 = 255;
            prim->g0 = 255;
            prim->b0 = 255;
            prim->w = 2;
            prim->h = 2;
            prim = prim->next;
        }
        break;

    case 1:
        if (--self->ext.timer.t == 0) {
            DestroyEntity(self);
            return;
        }

        prim = (FakePrim*)&g_PrimBuf[self->primIndex];

        while (1) {
            if (prim->next == NULL) {
                prim->drawMode &= ~DRAW_HIDE;
                prim->y0 = prim->x0 = prim->w = 0;
                return;
            }
            prim->posX.i.hi = prim->x0;
            prim->posY.i.hi = prim->y0;
            if (!--prim->delay) {
                prim->drawMode |= DRAW_HIDE;
            }
            prim->posY.val += prim->velocityY.val;
            if (prim->velocityY.val > FIX(0.5)) {
                prim->r0 -= 4;
                prim->g0 -= 4;
                prim->b0 -= 4;
            } else {
                prim->velocityY.val += FIX(28.0 / 128);
            }
            prim->x0 = prim->posX.i.hi;
            prim->y0 = prim->posY.i.hi;
            prim = prim->next;
        }
        break;
    }
}
