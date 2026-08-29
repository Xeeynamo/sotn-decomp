// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno2/rno2.h"

extern EInit g_EInitParticle;
extern u8 g_BloodSplatterSmallAnim[];
extern u8 g_BloodSplatterLargeAnim[];

void EntityBloodSplatter(Entity* self) {
    Primitive* prim;
    s32 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        break;

    case 1:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 8);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.bloodSplatter.prim = prim;
        } else {
            DestroyEntity(self);
            return;
        }
        self->step++;
        break;

    case 2:
        prim = self->ext.bloodSplatter.prim;
        prim = FindFirstUnkPrim2(prim, 2);
        if (prim != NULL) {
            self->ext.bloodSplatter.prim2 = prim;
            UnkPolyFunc2(prim);
            prim->tpage = 0x1A;
            prim->clut = PAL_UNK_1B7;
            prim->u0 = 0x50;
            prim->u1 = 0x50;
            prim->u2 = 0x40;
            prim->u3 = 0x40;
            prim->v0 = 0x30;
            prim->v1 = 0x40;
            prim->v2 = 0x30;
            prim->v3 = 0x40;
            prim->next->b3 = 0x60;
            prim->next->x1 = self->posX.i.hi;
            prim->next->y0 = self->posY.i.hi;
            LOH(prim->next->r2) = 0x10;
            LOH(prim->next->b2) = 0x10;
            LOW(prim->next->r1) = -0x6000;

            if (self->facingLeft) {
                LOW(prim->next->u0) = 0xA000;
                LOH(prim->next->tpage) = 0x200;
                prim->next->x1 += 4;
            } else {
                LOW(prim->next->u0) = -0xA000;
                LOH(prim->next->tpage) = -0x200;
                prim->next->x1 -= 4;
            }
            prim->priority = self->zPriority + 2;
            prim->drawMode = DRAW_COLORS | DRAW_UNK02;
        }

        prim = self->ext.bloodSplatter.prim;
        prim = FindFirstUnkPrim2(prim, 2);
        if (prim != NULL) {
            self->ext.bloodSplatter.prim3 = prim;
            UnkPolyFunc2(prim);
            prim->tpage = 0x1A;
            prim->clut = PAL_UNK_1B7;
            prim->u0 = 0x20;
            prim->u1 = 0x20;
            prim->u2 = 0;
            prim->u3 = 0;
            prim->v0 = 0x20;
            prim->v1 = 0x40;
            prim->v2 = 0x20;
            prim->v3 = 0x40;

            prim->next->x1 = self->posX.i.hi;
            prim->next->y0 = self->posY.i.hi;
            LOH(prim->next->r2) = 8;
            LOH(prim->next->b2) = 0x10;
            prim->next->b3 = 0x80;
            LOW(prim->next->r1) = -0x8000;
            if (self->facingLeft) {
                LOW(prim->next->u0) = 0xC000;
                LOH(prim->next->tpage) = 0x200;
            } else {
                LOW(prim->next->u0) = -0xC000;
                LOH(prim->next->tpage) = -0x200;
            }
            prim->priority = self->zPriority + 2;
            prim->drawMode = DRAW_COLORS | DRAW_UNK02;
        }
        self->step++;
        break;

    case 3:
        prim = self->ext.bloodSplatter.prim2;
        UnkPrimHelper(prim);

        if (g_Timer % 2) {
            LOH(prim->next->r2)++;
            LOH(prim->next->b2)++;
            prim->clut = PAL_UNK_1B7;
        } else {
            prim->clut = PAL_CC_RED_EFFECT_B;
        }

        LOW(prim->next->r1) += 0xC00;

        if (self->facingLeft) {
            LOH(prim->next->tpage) += 0x18;
        } else {
            LOH(prim->next->tpage) -= 0x18;
        }

        prim->next->b3 -= 2;
        if (!UpdateAnimation(g_BloodSplatterSmallAnim, prim)) {
            UnkPolyFunc0(prim);
        }

        prim = self->ext.bloodSplatter.prim3;
        UnkPrimHelper(prim);
        LOH(prim->next->r2) += 2;
        LOH(prim->next->b2) += 2;
        if (prim->p1 > 3) {
            LOH(prim->next->b2) = 16;
        }

        prim->next->b3 -= 3;
        if (prim->next->b3 > 240) {
            prim->next->b3 = 0;
        }

        if (!UpdateAnimation(g_BloodSplatterLargeAnim, prim)) {
            UnkPolyFunc0(prim);
        }

        if (self->ext.bloodSplatter.unk80++ > 128) {
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit g_EInitParticle;
extern s16 g_BloodDripsColliders[][2];

void EntityBloodDrips(Entity* self) { // BloodDrips
    Primitive* prim;
    u32 primIndex;
    u32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 1);
        if (primIndex != -1) {
            self->primIndex = primIndex;
            self->flags |= FLAG_HAS_PRIMS;
            self->hitboxState = 0;
            prim = &g_PrimBuf[primIndex];
            self->ext.prim = prim;
            // i iterator here is otherwise unused but needed for PSP match
            for (i = 0; prim != NULL; i++, prim = prim->next) {
                prim->x0 = prim->x1 = self->posX.i.hi;
                prim->y0 = prim->y1 = self->posY.i.hi;
                prim->r0 = 255;
                prim->r1 = 32;
                prim->g0 = 0;
                prim->g1 = 0;
                prim->b0 = 48;
                prim->b1 = 16;
                prim->priority = self->zPriority + 1;
                prim->drawMode |= DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                  DRAW_UNK02 | DRAW_TRANSP;
            }
        } else {
            DestroyEntity(self);
        }
        break;

    case 1:
        prim = self->ext.prim;
        if (CheckColliderOffsets(g_BloodDripsColliders, 0) != 0) {
            prim->y1 += 2;
            if (!self->step_s) {
                self->step_s = 1;
            }
        } else {
            self->velocityY += FIX(0.09375);
            self->posY.val += self->velocityY;
            if ((prim->y0 - prim->y1) > 8) {
                prim->y1 = prim->y0 - 8;
            }
        }
        prim->x0 = self->posX.i.hi;
        prim->x1 = self->posX.i.hi;
        prim->y0 = self->posY.i.hi;
        if (prim->y0 < prim->y1) {
            g_api.FreePrimitives(self->primIndex);
            DestroyEntity(self);
        }
        break;
    }
}
