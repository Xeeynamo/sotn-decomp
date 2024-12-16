// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

extern u16 D_us_80180A94[];
extern s16 D_us_80182998[];
extern s16 D_us_801829A8[];
extern u8 D_us_801829B0[];
extern u8 D_us_801829C8[];
extern u8 D_us_801829E0[];
extern u8 D_us_80182A24[];
extern u8 D_us_80182A2C[];
extern u8 D_us_80182A38[];
extern s16 D_80182A4C[];
extern s32 D_us_80182A54[];
extern u8 D_us_80182A60[][2];
extern s16 D_us_80182A68[];

// Bone musket
void func_us_801CEB28(Entity* self) {
    Entity* tempEntity;
    s32 i;
    s32 posX;
    s16* hitboxPtr;

    if ((self->flags & FLAG_DEAD) && (self->step < 8)) {
        SetStep(8);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180A94);
        if (self->params & 0x100) {
            self->facingLeft = 1;
            self->params &= 0xFF;
        }
        self->palette += self->params;
        self->animCurFrame = 1;
        if (self->params == 1) {
            self->animCurFrame = 0x1A;
        }
        self->ext.et_801CEB28.unk88 = self + D_us_80182A54[self->params];
        /* fallthrough */
    case 1:
        if (UnkCollisionFunc3(D_us_80182998) & 1) {
            if (!self->params) {
                for (tempEntity = self + 1, i = 1; i < 3; i++, tempEntity++) {
                    CreateEntityFromEntity(E_ID_46, self, tempEntity);
                    tempEntity->facingLeft = self->facingLeft;
                    if (self->facingLeft) {
                        tempEntity->posX.i.hi -= D_us_80182A4C[i];
                    } else {
                        tempEntity->posX.i.hi += D_us_80182A4C[i];
                    }
                    tempEntity->params = i;
                }
            }
            SetStep(2);
        }
        break;

    case 2:
        if (!self->params) {
            if (GetDistanceToPlayerX() < 0xC0) {
                for (tempEntity = self, i = 0; i < 3; i++, tempEntity++) {
                    tempEntity->step = D_us_80182A60[i][0];
                    tempEntity->step_s = D_us_80182A60[i][1];
                }
            }
        }
        break;

    case 3:
        switch (self->step_s) {
        case 0:
            if (AnimateEntity(D_us_80182A38, self) == 0) {
                self->ext.et_801CEB28.unk8D = 0;
                SetSubStep(1);
            }
            break;

        case 1:
            if (AnimateEntity(D_us_801829B0, self) == 0) {
                SetSubStep(2);
            }
            if (self->animFrameIdx == 6 && !self->animFrameDuration) {
                tempEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(E_ID_47, self, tempEntity);
                    tempEntity->facingLeft = self->facingLeft;
                }
            }
            break;

        case 2:
            if (AnimateEntity(D_us_801829C8, self) == 0) {
                tempEntity = self->ext.et_801CEB28.unk88;
                tempEntity->ext.et_801CEB28.unk8C = 1;
                SetSubStep(3);
            }
            if (self->animFrameIdx == 4 && !self->animFrameDuration) {
                tempEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(E_ID_47, self, tempEntity);
                    tempEntity->facingLeft = self->facingLeft;
                }
            }
            break;

        case 3:
            if (AnimateEntity(D_us_80182A24, self) == 0) {
                SetStep(4);
            }
            break;
        }
        break;
    case 4:
        if (!self->step_s) {
            if (self->facingLeft) {
                self->velocityX = FIX(-0.5);
            } else {
                self->velocityX = FIX(0.5);
            }
            self->ext.et_801CEB28.unk84 =
                g_Tilemap.scrollX.i.hi + self->posX.i.hi;
            self->step_s++;
        }
        UnkCollisionFunc2(D_us_801829A8);
        AnimateEntity(D_us_80182A2C, self);
        posX = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
        if (self->facingLeft) {
            posX = self->ext.et_801CEB28.unk84 - posX;
        } else {
            posX = posX - self->ext.et_801CEB28.unk84;
        }
        if (posX > 0x28) {
            if (self->facingLeft) {
                self->posX.i.hi =
                    (self->ext.et_801CEB28.unk84 - g_Tilemap.scrollX.i.hi) -
                    0x28;
            } else {
                self->posX.i.hi =
                    (self->ext.et_801CEB28.unk84 - g_Tilemap.scrollX.i.hi) +
                    0x28;
            }
            SetStep(5);
        }
        break;
    case 6:
        if (!self->step_s) {
            if (self->facingLeft) {
                self->velocityX = FIX(0.875);
            } else {
                self->velocityX = FIX(-0.875);
            }
            self->ext.et_801CEB28.unk84 =
                g_Tilemap.scrollX.i.hi + self->posX.i.hi;
            self->step_s++;
        }
        UnkCollisionFunc2(D_us_801829A8);
        AnimateEntity(D_us_80182A2C, self);
        posX = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
        if (self->facingLeft) {
            posX = posX - self->ext.et_801CEB28.unk84;
        } else {
            posX = self->ext.et_801CEB28.unk84 - posX;
        }
        if (posX > 0x14) {
            if (self->facingLeft) {
                self->posX.i.hi =
                    (self->ext.et_801CEB28.unk84 - g_Tilemap.scrollX.i.hi) +
                    0x14;
            } else {
                self->posX.i.hi =
                    (self->ext.et_801CEB28.unk84 - g_Tilemap.scrollX.i.hi) -
                    0x14;
            }
            if (self->ext.et_801CEB28.unk8D) {
                SetStep(3);
            } else {
                SetStep(7);
            }
        }
        break;
    case 5:
        switch (self->step_s) {
        case 0:
            if (AnimateEntity(D_us_80182A38, self) == 0) {
                SetSubStep(1);
            }
            break;

        case 1:
            if (AnimateEntity(D_us_801829E0, self) == 0) {
                SetSubStep(2);
            }
            if (!self->animFrameDuration && self->animFrameIdx == 0x1C) {
                PlaySfxPositional(SFX_GRANDFATHER_CLOCK_TICK);
            }
            break;

        case 2:
            if (AnimateEntity(D_us_80182A24, self) == 0) {
                SetStep(6);
                self->ext.et_801CEB28.unk8D = 0;
            }
            break;
        }
        break;
    case 7:
        if (self->ext.et_801CEB28.unk8C) {
            self->ext.et_801CEB28.unk8C = 0;
            SetStep(6);
            self->ext.et_801CEB28.unk8D = 1;
        }
        break;
    case 8:
        PlaySfxPositional(SFX_QUICK_STUTTER_EXPLODE_A);
        tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (tempEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
            tempEntity->params = 2;
        }
        self->animCurFrame = 0;
        self->hitboxState = 0;
        SetStep(9);
        break;
    case 9:
        tempEntity = self->ext.et_801CEB28.unk88;
        if ((tempEntity->entityId != E_ID_46) ||
            (tempEntity->flags & FLAG_DEAD)) {
            DestroyEntity(self);
            return;
        }
        tempEntity->ext.et_801CEB28.unk8C = 1;
        break;
    }
    hitboxPtr = D_us_80182A68;
    if (self->animCurFrame > 23) {
        hitboxPtr += 4;
    }
    if (self->animCurFrame > 26) {
        hitboxPtr += 4;
    }
    self->hitboxOffX = *hitboxPtr++;
    self->hitboxOffY = *hitboxPtr++;
    self->hitboxWidth = *hitboxPtr++;
    self->hitboxHeight = *hitboxPtr++;
}

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
        self->ext.et_801CEB28.unk7C = prim;
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
        prim = self->ext.et_801CEB28.unk7C;
        tempEntity = &PLAYER;
        tempVar = tempEntity->posX.i.hi;
        if (self->facingLeft) {
            if (prim->x0 < tempVar) {
                prim->x1 = tempVar;
            } else {
                prim->x1 = 0x100;
            }
        } else {
            if (tempVar < prim->x0) {
                prim->x1 = tempVar;
            } else {
                prim->x1 = 0;
            }
        }
        tempVar = abs(prim->x1 - prim->x0);
        self->hitboxWidth = tempVar / 2;
        self->hitboxOffX = -self->hitboxWidth - 0x20;
        self->hitboxState = 4;
        self->step++;
        break;

    case 2:
        self->step++;
        prim = self->ext.et_801CEB28.unk7C;
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
        prim = self->ext.et_801CEB28.unk7C;
        prim->drawMode = DRAW_HIDE;
        self->hitboxState = 0;
        break;
    }
    if (AnimateEntity(D_us_80182A40, self) == 0) {
        DestroyEntity(self);
    }
}
