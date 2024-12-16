// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

// Bone musket
INCLUDE_ASM("st/no1/nonmatchings/e_bone_musket", func_us_801CEB28);

extern u16 D_us_80180AA0[];
extern u8 D_us_80182A40[];

// Bone musket projectile?
void func_us_801CF298(Entity* self) {
    Primitive* prim;
    Entity* tempEntity;
    s32 primIndex;
    s32 tempVar;

    switch (self->step) {
    case 0:
        tempVar = self->posX.i.hi;
        if (tempVar > 0x160) {
            self->posX.i.hi = 0x160;
        }
        if (tempVar < -0x60) {
            self->posX.i.hi = -0x60;
        }
        InitializeEntity(D_us_80180AA0);
        self->hitboxOffY = -8;
        self->hitboxHeight = 1;
        primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        if (self->facingLeft) {
            prim->x0 = prim->x1 = self->posX.i.hi + 0x20;
        } else {
            prim->x0 = prim->x1 = self->posX.i.hi - 0x20;
        }
        prim->y0 = prim->y1 = self->posY.i.hi - 9;
        prim->r0 = prim->r1 = 0x68;
        prim->g0 = prim->g1 = 0x68;
        prim->b0 = prim->b1 = 0x70;
        prim->priority = self->zPriority;
        prim->drawMode = DRAW_HIDE | DRAW_UNK02;
        PlaySfxPositional(SFX_GUNSHOT_HIGH);
    case 1:
        prim = self->ext.prim;
        tempEntity = &PLAYER;
        tempVar = tempEntity->posX.i.hi;
        if (self->facingLeft) {
            if (prim->x0 < tempVar) {
                prim->x1 = tempVar;
            } else {
                prim->x1 = 0x100;
            }
        } else if (tempVar < prim->x0) {
            prim->x1 = tempVar;
        } else {
            prim->x1 = 0;
        }
        tempVar = abs(prim->x1 - prim->x0);
        self->hitboxWidth = tempVar / 2;
        self->hitboxOffX = -self->hitboxWidth - 0x20;
        self->hitboxState = 4;
        self->step++;
        break;

    case 2:
        self->step++;
        prim = self->ext.prim;
        prim->drawMode = DRAW_UNK02;
        if (self->hitParams) {
            self->hitboxState = 0;
        } else {
            self->hitboxState = 9;
            if (self->facingLeft) {
                prim->x1 = 0x100;
            } else {
                prim->x1 = 0;
            }
            tempVar = abs(prim->x1 - prim->x0);
            self->hitboxWidth = tempVar / 2;
            self->hitboxOffX = -self->hitboxWidth - 0x20;
        }
        break;

    case 3:
        prim = self->ext.prim;
        prim->drawMode = DRAW_HIDE;
        self->hitboxState = 0;
        break;
    }
    if (AnimateEntity(D_us_80182A40, self) == 0) {
        DestroyEntity(self);
    }
}
