// SPDX-License-Identifier: AGPL-3.0-or-later
#include "lib.h"

extern PfnEntityUpdate OVL_EXPORT(EntityUpdates)[];
#define PfnEntityUpdates OVL_EXPORT(EntityUpdates)
extern s32 D_us_80181ACC;

static s16 D_us_80182AE0[][4] = {
    {0x0038, 0x0104, 0x0201, 0x0103}, {0x8038, 0x0104, 0x0201, 0x0103}};
static AnimationFrame D_us_80182AF0[] = {
    {2, 12}, {2, 13}, {2, 14}, {2, 15}, {0, 0}};
static AnimationFrame D_us_80182B04[] = {
    {2, 20}, {2, 21}, {2, 22}, {2, 23}, {2, 24}, {2, 25}, {2, 26},
    {2, 27}, {2, 28}, {2, 29}, {2, 30}, {2, 31}, {-1, 0}};
static AnimationFrame D_us_80182B38[] = {
    {2, 16}, {2, 17}, {2, 18}, {2, 19}, {0, 0}};
static AnimationFrame D_us_80182B4C[] = {
    {2, 32}, {2, 33}, {2, 34}, {2, 35}, {2, 36}, {2, 37}, {2, 38},
    {2, 39}, {2, 40}, {2, 41}, {2, 42}, {2, 43}, {-1, 0}};

Entity* func_us_801CCED0(u32 arg0) {
    Entity* tempEntity;

    tempEntity = g_api.GetFreeEntity(0xE0, 0x100);
    if (tempEntity == NULL) {
        return NULL;
    }
    DestroyEntity(tempEntity);
    tempEntity->entityId = E_ID_39;
    tempEntity->pfnUpdate = PfnEntityUpdates[tempEntity->entityId - 1];
    tempEntity->params = arg0;
    tempEntity->ext.ectoplasm.unk8C = g_CurrentEntity;
    tempEntity->posX.val = g_CurrentEntity->posX.val;
    tempEntity->posY.val = g_CurrentEntity->posY.val;
    tempEntity->facingLeft = g_CurrentEntity->facingLeft;
    return tempEntity;
}

void func_us_801CCF6C(Entity* self) {
    Entity* tempEntity;
    s32 i;
    s32 rotate;

    s32 params = self->params;
    if (self->step == 0) {
        InitializeEntity(g_EInitInteractable);
        self->scaleX = D_us_80182AE0[params][0] & 0xFF;
        self->scaleY = D_us_80182AE0[params][1] & 0xFF;
        self->rotate = D_us_80182AE0[params][2] & 0x7F;
        self->rotPivotX = D_us_80182AE0[params][3] & 0x7F;
        if (D_us_80182AE0[params][3] & 0x80) {
            self->attackElement = self->rotPivotX;
        }
        self->hitPoints = D_us_80182AE0[params][3] >> 8;
        self->hitParams = D_us_80182AE0[params][2] >> 8;
        self->entityRoomIndex = (D_us_80182AE0[params][2] >> 7) & 1;
        self->hitEffect = D_us_80182AE0[params][0] & 0xFF00;
        self->hitboxOffX = D_us_80182AE0[params][1] >> 8;
        self->rotPivotY = 0;
        switch (self->hitParams) {
        case 0:
            self->flags |= FLAG_POS_CAMERA_LOCKED;
        case 1:
            break;
        case 2:
            tempEntity = self->ext.ectoplasm.unk8C;
            self->posX.val = tempEntity->posX.val;
            self->posY.val = tempEntity->posY.val;
            break;
        }
    } else {
        switch (self->hitParams) {
        case 0:
        case 1:
            break;
        case 2:
            tempEntity = self->ext.ectoplasm.unk8C;
            self->posX.val = tempEntity->posX.val;
            self->posY.val = tempEntity->posY.val;
            break;
        }
    }
    if (self->attackElement) {
        if (--self->attackElement) {
            return;
        }
        self->attackElement = self->rotPivotX;
    }

    rotate = self->rotate;
    for (i = 0; i < rotate; i++) {
        if (self->hitPoints == 0) {
            tempEntity = g_api.GetFreeEntity(0xA0, 0xC0);
        }
        if (self->hitPoints == 1) {
            tempEntity = g_api.GetFreeEntity(0xE0, 0x100);
        }
        if (tempEntity == NULL) {
            if (self->hitboxOffX == 1) {
                DestroyEntity(self);
            }
            return;
        }
        DestroyEntity(tempEntity);
        tempEntity->entityId = self->scaleX;
        if (self->scaleX == 0) {
            while (true) {
                i++;
            }
        }
        tempEntity->pfnUpdate = PfnEntityUpdates[tempEntity->entityId - 1];
        tempEntity->params = self->hitEffect;
        tempEntity->ext.ectoplasm.unk8C = self->ext.ectoplasm.unk8C;
        tempEntity->posX.val = self->posX.val;
        tempEntity->posY.val = self->posY.val;
        tempEntity->facingLeft = self->facingLeft;
        if (self->entityRoomIndex) {
            tempEntity->params += self->rotPivotY;
        } else {
            tempEntity->params += i;
        }
        self->rotPivotY++;
        if (self->rotPivotY == self->scaleY) {
            DestroyEntity(self);
            return;
        }
    }
    self->attackElement = self->rotPivotX;
}

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
                PlaySfxPositional(SFX_ECTOPLASM_DEATH);
                self->hitboxState = 0;
                self->ext.ectoplasm.unk90 = 0;
                self->ext.ectoplasm.unk96 = 0x100;
                self->drawMode |= DRAW_TPAGE;
                self->step = 4;
                self->ext.ectoplasm.unk82 = 0;
            } else if (self->step != 3) {
                PlaySfxPositional(SFX_ECTOPLASM_BOING);
                self->ext.ectoplasm.unk90 = 0;
                self->step_s = self->step;
                self->step = 3;
            }
        }
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitEctoplasm);
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
        self->drawFlags = FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
        self->scaleY = 0x100;
        self->scaleX = 0x100;
        prim = &g_PrimBuf[self->primIndex];
        prim->x0 = self->posX.i.hi;
        prim->y0 = self->posY.i.hi;
        prim->drawMode = DRAW_HIDE | DRAW_UNK02;
        if (self->params == 0) {
            self->ext.ectoplasm.unk84 = 0x3800;
            self->ext.ectoplasm.unk88 = 0x2000;
            self->ext.ectoplasm.unk92 = 8;
            self->ext.ectoplasm.unk94 = 8;
        } else {
            self->ext.ectoplasm.unk84 = 0x4000;
            self->ext.ectoplasm.unk88 = 0x1800;
            self->ext.ectoplasm.unk92 = -0xA;
            self->ext.ectoplasm.unk94 = 0xA;
        }
        if (self->params & 0x10) {
            self->ext.ectoplasm.unk84 = 0;
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
        self->ext.ectoplasm.unk7C += self->ext.ectoplasm.unk92;
        self->ext.ectoplasm.unk7E += 0x40;
        if (g_pads[0].tapped & PAD_SQUARE) {
            self->step++;
            self->ext.ectoplasm.unk92 = self->ext.ectoplasm.unk92 * 2;
            self->ext.ectoplasm.unk80 = 0;
        }
        angle = abs(self->ext.ectoplasm.unk92);
        if (angle > self->ext.ectoplasm.unk94) {
            if (self->ext.ectoplasm.unk92 > 0) {
                self->ext.ectoplasm.unk92--;
            } else {
                self->ext.ectoplasm.unk92++;
            }
        }
        break;

    case 2:
        self->ext.ectoplasm.unk7C += self->ext.ectoplasm.unk92;
        self->ext.ectoplasm.unk7E += 0x40;
        angle = self->ext.ectoplasm.unk80;
        if (self->ext.ectoplasm.unk80 < 0x1000) {
            self->ext.ectoplasm.unk80 += 0x20;
            self->ext.ectoplasm.unk84 += rsin(angle) >> 4;
            self->ext.ectoplasm.unk88 += rsin(angle) >> 4;
        } else {
            self->ext.ectoplasm.unk80 += 0x40;
            self->ext.ectoplasm.unk84 -= rsin(angle) >> 5;
            self->ext.ectoplasm.unk88 -= rsin(angle) >> 5;
        }
        if (self->ext.ectoplasm.unk80 == 0x2000) {
            self->step--;
            self->ext.ectoplasm.unk92 = self->ext.ectoplasm.unk92 / 2;
        }
        break;

    case 3:
        angle = self->ext.ectoplasm.unk90 & 0x7FF;
        self->scaleY = (rsin(angle) >> 4) + 0x100;
        self->scaleX = 0x100 - (rsin(angle) >> 6);
        self->ext.ectoplasm.unk90 += 0x80;
        if (self->ext.ectoplasm.unk90 == 0x1000) {
            self->scaleY = 0x100;
            self->scaleX = 0x100;
            self->step = self->step_s;
            self->ext.ectoplasm.unk92 = -self->ext.ectoplasm.unk92 * 2;
        }
        break;

    case 4:
        if (self->ext.ectoplasm.unk82 == 0x20) {
            PlaySfxPositional(SFX_NOISE_SWEEP_DOWN_A);
        }
        angle = self->ext.ectoplasm.unk90 & 0x7FF;
        self->scaleY = self->ext.ectoplasm.unk96 + (rsin(angle) >> 4);
        self->scaleX = self->ext.ectoplasm.unk96 - (rsin(angle) >> 6);
        self->ext.ectoplasm.unk90 += 0x80;
        self->posY.val += self->velocityY;
        self->velocityY += 0x400;
        self->ext.ectoplasm.unk96--;
        if (self->ext.ectoplasm.unk96 < 0x60) {
            self->ext.ectoplasm.unk96 = 0x60;
        }
        if ((self->ext.ectoplasm.unk82 & 1) == 0) {
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
    self->ext.ectoplasm.unk82++;
    if ((self->ext.ectoplasm.unk82 & 7) == 0) {
        if (self->params == 0) {
            func_us_801CCED0(0);
        } else {
            func_us_801CCED0(1);
        }
    }
    if (self->step != 4) {
        angle = self->ext.ectoplasm.unk7C;
        xOffset = ((rcos(angle) * self->ext.ectoplasm.unk84) >> 8) << 4;
        yOffset = -((rsin(angle) * self->ext.ectoplasm.unk88) >> 8) << 4;
        yOffset -= (rsin(self->ext.ectoplasm.unk7E) << 1) << 4;
        prim = &g_PrimBuf[self->primIndex];
        self->posX.i.hi = prim->x0 + (xOffset >> 0x10);
        self->posY.i.hi = prim->y0 + (yOffset >> 0x10);
    }
}

void func_us_801CD9EC(Entity* self) {
    Entity* tempEntity;
    s16 rnd;

    tempEntity = self->ext.ectoplasm.unk8C;
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitEctoplasm);
        self->flags |=
            FLAG_DESTROY_IF_OUT_OF_CAMERA | FLAG_UNK_00200000 | FLAG_UNK_2000;
        self->flags &= ~FLAG_UNK_20000000;
        if (self->params < 0x80) {
            self->anim = D_us_80182B04;
        } else {
            self->anim = D_us_80182B4C;
        }
        self->hitboxState = 0;
        self->velocityY = FIX(-1.0);
        rnd = rand() & 0x7FF;
        self->posX.val += (rcos(rnd) << 4) * 0xC;
        self->posY.val -= (rsin(rnd) << 4) * 0xC;
        break;

    case 1:
        self->posY.val += self->velocityY;
        if (self->poseTimer < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    g_api.UpdateAnim(NULL, NULL);
    if (tempEntity->step == 4) {
        if (--self->ext.ectoplasm.unk82 & 1) {
            self->drawMode = DRAW_TPAGE;
        } else {
            self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        }
    }
}
