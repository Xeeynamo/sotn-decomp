// SPDX-License-Identifier: AGPL-3.0-or-later
#include "lib.h"
#include "../pfn_entity_update.h"

INCLUDE_ASM("st/lib/nonmatchings/unk_4C984", func_us_801CCED0);

INCLUDE_ASM("st/lib/nonmatchings/unk_4C984", func_us_801CCF6C);

extern s32 D_us_80181ACC;
extern AnimationFrame D_us_80182AF0[];
extern AnimationFrame D_us_80182B38[];

void func_us_801CD318(Entity* self) {
    Entity* tempEntity;
    Primitive* prim;
    s16 angle;
    s32 xOffset;
    s32 yOffset;

    if ((self->params & 0x10) && (D_us_80181ACC & 2)) {
        self->hitFlags |= 3;
        self->flags |= FLAG_DEAD;
    }
    if (self->hitFlags & 3) {
        if (self->step < 4) {
            if (self->flags & FLAG_DEAD) {
                PlaySfxPositional(0x73B);
                self->hitboxState = 0;
                self->ext.et_801CD318.unk90 = 0;
                self->ext.et_801CD318.unk96 = 0x100;
                self->drawMode |= DRAW_TPAGE;
                self->step = 4;
                self->ext.et_801CD318.unk82 = 0;
            } else if (self->step != 3) {
                PlaySfxPositional(0x73A);
                self->ext.et_801CD318.unk90 = 0;
                self->step_s = self->step;
                self->step = 3;
            }
        }
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801808C0);
        if (self->params == 0) {
            self->anim = D_us_80182AF0;
        } else {
            self->anim = D_us_80182B38;
        }
        self->primIndex = g_api.AllocPrimitives(PRIM_TILE, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->drawFlags = FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
        self->rotY = 0x100;
        self->rotX = 0x100;
        prim = &g_PrimBuf[self->primIndex];
        prim->x0 = self->posX.i.hi;
        prim->y0 = self->posY.i.hi;
        prim->drawMode = DRAW_HIDE | DRAW_UNK02;
        if (self->params == 0) {
            self->ext.et_801CD318.unk84 = 0x3800;
            self->ext.et_801CD318.unk88 = 0x2000;
            self->ext.et_801CD318.unk92 = 8;
            self->ext.et_801CD318.unk94 = 8;
        } else {
            self->ext.et_801CD318.unk84 = 0x4000;
            self->ext.et_801CD318.unk88 = 0x1800;
            self->ext.et_801CD318.unk92 = -0xA;
            self->ext.et_801CD318.unk94 = 0xA;
        }
        if (self->params & 0x10) {
            self->ext.et_801CD318.unk84 = 0;
            self->flags |= FLAG_UNK_2000;
            self->hitboxState = 0;
            self->animCurFrame = 0;
            self->step = 0x20;
        }
        break;

    case 32:
        func_us_801BB8DC(0);
        break;

    case 1:
        self->ext.et_801CD318.unk7C += self->ext.et_801CD318.unk92;
        self->ext.et_801CD318.unk7E += 0x40;
        if (g_pads[0].tapped & PAD_SQUARE) {
            self->step++;
            self->ext.et_801CD318.unk92 = self->ext.et_801CD318.unk92 * 2;
            self->ext.et_801CD318.unk80 = 0;
        }
        angle = abs(self->ext.et_801CD318.unk92);
        if (angle > self->ext.et_801CD318.unk94) {
            if (self->ext.et_801CD318.unk92 > 0) {
                self->ext.et_801CD318.unk92--;
            } else {
                self->ext.et_801CD318.unk92++;
            }
        }
        break;

    case 2:
        self->ext.et_801CD318.unk7C += self->ext.et_801CD318.unk92;
        self->ext.et_801CD318.unk7E += 0x40;
        angle = self->ext.et_801CD318.unk80;
        if (self->ext.et_801CD318.unk80 < 0x1000) {
            self->ext.et_801CD318.unk80 += 0x20;
            self->ext.et_801CD318.unk84 += rsin(angle) >> 4;
            self->ext.et_801CD318.unk88 += rsin(angle) >> 4;
        } else {
            self->ext.et_801CD318.unk80 += 0x40;
            self->ext.et_801CD318.unk84 -= rsin(angle) >> 5;
            self->ext.et_801CD318.unk88 -= rsin(angle) >> 5;
        }
        if (self->ext.et_801CD318.unk80 == 0x2000) {
            self->step--;
            self->ext.et_801CD318.unk92 = self->ext.et_801CD318.unk92 / 2;
        }
        break;

    case 3:
        angle = self->ext.et_801CD318.unk90 & 0x7FF;
        self->rotY = (rsin(angle) >> 4) + 0x100;
        self->rotX = 0x100 - (rsin(angle) >> 6);
        self->ext.et_801CD318.unk90 += 0x80;
        if (self->ext.et_801CD318.unk90 == 0x1000) {
            self->rotY = 0x100;
            self->rotX = 0x100;
            self->step = self->step_s;
            self->ext.et_801CD318.unk92 = -self->ext.et_801CD318.unk92 * 2;
        }
        break;

    case 4:
        if (self->ext.et_801CD318.unk82 == 0x20) {
            PlaySfxPositional(SFX_NOISE_SWEEP_DOWN_A);
        }
        angle = self->ext.et_801CD318.unk90 & 0x7FF;
        self->rotY = self->ext.et_801CD318.unk96 + (rsin(angle) >> 4);
        self->rotX = self->ext.et_801CD318.unk96 - (rsin(angle) >> 6);
        self->ext.et_801CD318.unk90 += 0x80;
        self->posY.val += self->velocityY;
        self->velocityY += 0x400;
        self->ext.et_801CD318.unk96--;
        if (self->ext.et_801CD318.unk96 < 0x60) {
            self->ext.et_801CD318.unk96 = 0x60;
        }
        if ((self->ext.et_801CD318.unk82 & 1) == 0) {
            tempEntity = g_api.GetFreeEntity(0xE0, 0x100);
            if (tempEntity != NULL) {
                DestroyEntity(tempEntity);
                tempEntity->entityId = E_EXPLOSION;
                tempEntity->pfnUpdate =
                    PfnEntityUpdates[tempEntity->entityId - 1];
                tempEntity->params = 0;
                tempEntity->zPriority = self->zPriority + 2;
                tempEntity->posX.i.hi =
                    (self->posX.i.hi + (rand() & 0x1F)) - 0x10;
                tempEntity->posY.i.hi =
                    (self->posY.i.hi + (rand() & 0x1F)) - 0x10;
                tempEntity->drawMode = DRAW_TPAGE;
            }
        }
        if (self->posY.i.hi > 0x100) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    g_api.UpdateAnim(NULL, NULL);
    self->ext.et_801CD318.unk82++;
    if ((self->ext.et_801CD318.unk82 & 7) == 0) {
        if (self->params == 0) {
            func_us_801CCED0(0);
        } else {
            func_us_801CCED0(1);
        }
    }
    if (self->step != 4) {
        angle = self->ext.et_801CD318.unk7C;
        xOffset = ((rcos(angle) * self->ext.et_801CD318.unk84) >> 8) << 4;
        yOffset = -((rsin(angle) * self->ext.et_801CD318.unk88) >> 8) << 4;
        yOffset -= (rsin(self->ext.et_801CD318.unk7E) << 1) << 4;
        prim = &g_PrimBuf[self->primIndex];
        self->posX.i.hi = prim->x0 + (xOffset >> 0x10);
        self->posY.i.hi = prim->y0 + (yOffset >> 0x10);
    }
}

// Ectoplasm
INCLUDE_ASM("st/lib/nonmatchings/unk_4C984", func_us_801CD9EC);
