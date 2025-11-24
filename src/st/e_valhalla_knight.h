// SPDX-License-Identifier: AGPL-3.0-or-later
extern EInit g_EInitValhallaKnight;
extern EInit g_EInitValhallaKnightUnk1;
extern EInit g_EInitValhallaKnightUnk2;
extern EInit g_EInitValhallaKnightUnk3;

static s16 D_us_80182028[] = {0x00, 0x28, 0x00, 0x04, 0x10, -0x04, -0x20, 0x00};
static s16 D_us_80182038[] = {0x00, 0x28, 0x08, 0x00};
static u8 D_us_80182040[] = {6, 1, 6, 2, 6, 3, 6, 4, 6, 5, 0, 0};
static u8 D_us_8018204C[] = {6, 6, 6, 7, 6, 8, 6, 9, 6, 10, 0, 0};
static u8 D_us_80182058[] = {4, 11, 4, 12, 4, 13, 8, 14, -1, 0};
static u8 D_us_80182064[] = {3, 4, 3, 5, 4, 1, 4, 2, 5, 3, 5, 4, 6, 5, -1, 0};
static s8 D_us_80182074[] = {
    0xFF, 0xF5, 0x11, 0x14, 0x01, 0xF3, 0x08, 0x17, 0xFD, 0xEF, 0x0A, 0x18,
};
static u8 D_us_80182080[] = {
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 3, 3, 1, 1, 1, 0, 0,
};
static s8 D_us_80182094[] = {
    0x00, 0x00, 0x00, 0x00, 0xF3, 0x18, 0x07, 0x0F, 0x01, 0x14, 0x0A, 0x0B,
    0x08, 0x13, 0x0A, 0x0A, 0x03, 0x18, 0x08, 0x0F, 0x05, 0x18, 0x04, 0x0D,
    0x06, 0x17, 0x05, 0x0F, 0x00, 0x11, 0x0B, 0x08, 0x08, 0x11, 0x0B, 0x08,
};
static u8 D_us_801820B8[] = {
    0, 1, 2, 3, 4, 4, 1, 2, 3, 4, 4, 5, 5, 6, 6, 1, 7, 8, 0, 0,
};
static s8 D_us_801820CC[] = {
    0x00, 0x00, 0x00, 0x00, 0x2C, 0xEB, 0x0A, 0x02, 0x16, 0x11,
    0x06, 0x06, 0x2C, 0x04, 0x0A, 0x04, 0x29, 0x02, 0x0A, 0x05,
};
static u8 D_us_801820E0[] = {
    0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 4, 4, 0, 0,
};
static Point16 D_us_801820F4[] = {{0x00, 0x08}, {0x18, -0x08}, {-0x08, 0x20}};
static unkStr_80182100 D_us_80182100[] = {
    {0x6000, 0x0000, 0x20},    {0x8000, -0x5000, 0x18},
    {0x2000, 0x0000, 0x0C},    {0x0000, -0x2000, 0x04},
    {-0x4000, -0xC000, -0x40}, {0x3000, -0x4000, 0x30},
    {0xC000, 0x0000, 0x20},    {0x0000, -0x3000, 0x10},
    {0xE000, -0x8000, 0x40},   {-0x1000, 0x0000, 0x04},
    {0x5000, -0xF000, 0x08},   {-0x2000, 0x0000, 0x20},
    {-0x6000, -0x6000, 0x08},
};

void EntityValhallaKnight(Entity* self) {
    Entity* tempEntity;
    Entity* tempEntity2;
    s32 i;
    s32 posX;
    s8* hitboxPtr;
    s32 temp_a0_2;

    if (self->flags & FLAG_DEAD) {
        SetStep(6);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitValhallaKnight);
        self->animCurFrame = 1;
        self->ext.valhallaKnight.unk84 =
            g_Tilemap.scrollX.i.hi + self->posX.i.hi;
        tempEntity = self + 1;
        CreateEntityFromCurrentEntity(E_VALHALLA_KNIGHT_UNK1, tempEntity);
        tempEntity->params = 0;
        self->unk60 = tempEntity;
        self->unk5C = NULL;
        tempEntity = self + 2;
        CreateEntityFromCurrentEntity(E_VALHALLA_KNIGHT_UNK1, tempEntity);
        tempEntity->params = 1;
        /* fallthrough */
    case 1:
        if (UnkCollisionFunc3(D_us_80182028) & 1) {
            self->facingLeft = GetSideToPlayer() & 1;
#ifdef STAGE_IS_ARE
            self->facingLeft = self->params & 1;
#endif
            SetStep(2);
        }
        break;

    case 2:
        if (!self->step_s) {
            self->ext.valhallaKnight.unk80 = 0x80;
            self->step_s++;
        }
        if (!AnimateEntity(D_us_8018204C, self)) {
            PlaySfxPositional(SFX_VALHALLA_KNIGHT_GALLOP);
        }
        temp_a0_2 = UnkCollisionFunc2(D_us_80182038);
        if (self->facingLeft) {
            self->velocityX = FIX(-2.5);
        } else {
            self->velocityX = FIX(2.5);
        }
        if (temp_a0_2 == 0x80) {
            SetStep(5);
            self->step_s = 2;
        }
        posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (self->facingLeft) {
            posX = self->ext.valhallaKnight.unk84 - posX;
        } else {
            posX = posX - self->ext.valhallaKnight.unk84;
        }
#ifdef STAGE_IS_ARE
        if (posX > 0x70) {
#else
        if (posX > 0x60) {
#endif
            SetStep(3);
        }
        break;

    case 3:
        if (!self->step_s) {
            PlaySfxPositional(SFX_VALHALLA_KNIGHT_NEIGH);
            self->step_s++;
        }
        UnkCollisionFunc2(D_us_80182038);
        self->velocityX -= self->velocityX / 0x20;
        if (!self->poseTimer) {
            if (self->facingLeft) {
                EntityGreyPuffSpawner(self, 5, 3, -4, 40, 0, 4);
            } else {
                EntityGreyPuffSpawner(self, 5, 3, 4, 40, 0, -4);
            }
        }
        if (!AnimateEntity(D_us_80182058, self)) {
            self->facingLeft ^= 1;
            tempEntity2 = &PLAYER;
            if (tempEntity2->velocityY != 0 && GetDistanceToPlayerX() < 0x80) {
                self->animCurFrame = 1;
                SetStep(5);
            } else {
                self->animCurFrame = 6;
                SetStep(2);
            }
        }
        break;

    case 5:
        switch (self->step_s) {
        case 0:
            if (self->facingLeft) {
                self->velocityX = FIX(-2.5);
            } else {
                self->velocityX = FIX(2.5);
            }
            self->ext.valhallaKnight.unk80 = 0x10;
            self->step_s++;
            /* fallthrough */
        case 1:
            if (!AnimateEntity(D_us_80182040, self)) {
                PlaySfxPositional(SFX_VALHALLA_KNIGHT_GALLOP);
            }
            UnkCollisionFunc2(D_us_80182038);
            if (!self->ext.valhallaKnight.unk80) {
                if (GetDistanceToPlayerX() < 0x50) {
                    self->step_s = 2;
                }
            } else {
                self->ext.valhallaKnight.unk80--;
            }
            posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            if (self->facingLeft) {
                posX = self->ext.valhallaKnight.unk84 - posX;
            } else {
                posX = posX - self->ext.valhallaKnight.unk84;
            }
#ifdef STAGE_IS_ARE
            if (posX > 0x70) {
#else
            if (posX > 0x60) {
#endif
                SetStep(3);
            }
            break;

        case 2:
            self->velocityY = FIX(-3.0);
            if (self->facingLeft) {
                self->velocityX = FIX(-3.5);
            } else {
                self->velocityX = FIX(3.5);
            }
            self->animCurFrame = 15;
            self->step_s++;
            /* fallthrough */
        case 3:
            UnkCollisionFunc3(D_us_80182028);
            self->velocityY -= FIX(5.0 / 32);
            if (self->velocityY > FIX(-0.75)) {
                self->animCurFrame = 16;
            }
            if (self->velocityY > FIX(0.75)) {
                self->animCurFrame = 17;
                self->step_s++;
            }
            break;
        case 4:
            if (UnkCollisionFunc3(D_us_80182028) & 1) {
                g_api.PlaySfx(SFX_STOMP_HARD_B);
                if (self->facingLeft) {
                    EntityGreyPuffSpawner(self, 5, 3, -4, 40, 0, 4);
                } else {
                    EntityGreyPuffSpawner(self, 5, 3, 4, 40, 0, -4);
                }
                if (self->facingLeft) {
                    self->velocityX = FIX(-2.5);
                } else {
                    self->velocityX = FIX(2.5);
                }
                SetSubStep(5);
            }
            break;
        case 5:
            UnkCollisionFunc2(D_us_80182038);
            if (!AnimateEntity(D_us_80182064, self)) {
                SetStep(2);
            }
            break;
        }
        break;

    case 6:
        for (i = 0; i < 3; i++) {
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
                if (self->facingLeft) {
                    tempEntity->posX.i.hi -= D_us_801820F4[i].x;
                } else {
                    tempEntity->posX.i.hi += D_us_801820F4[i].x;
                }
                tempEntity->posY.i.hi += D_us_801820F4[i].y;
                tempEntity->params = 3;
            }
        }
        for (i = 0; i < 13; i++) {
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(
                    E_VALHALLA_KNIGHT_UNK2, self, tempEntity);
                tempEntity->params = i;
                tempEntity->facingLeft = self->facingLeft;
                tempEntity->velocityX = self->velocityX;
                tempEntity->velocityY = self->velocityY;
            }
        }
        g_api.PlaySfx(SFX_EXPLODE_A);
        DestroyEntity(self);
        return;

    case 0xFF:
#include "pad2_anim_debug.h"
    }
    hitboxPtr = D_us_80182074;
    if (self->animCurFrame == 11 || self->animCurFrame == 12) {
        hitboxPtr += 4;
    }
    if (self->animCurFrame == 13 || self->animCurFrame == 14) {
        hitboxPtr += 8;
    }
    self->hitboxOffX = *hitboxPtr++;
    self->hitboxOffY = *hitboxPtr++;
    self->hitboxWidth = *hitboxPtr++;
    self->hitboxHeight = *hitboxPtr++;
}

void func_us_801C8954(Entity* self) {
    Entity* tempEntity;
    s32 curFrame;
    s8* hitboxPtr;

    if (!self->step) {
        if (self->params) {
            InitializeEntity(g_EInitValhallaKnightUnk3);
        } else {
            InitializeEntity(g_EInitValhallaKnightUnk2);
            self->unk5C = self - 1;
            self->unk60 = self - 1;
        }
    }
    tempEntity = self - self->params - 1;
    if (tempEntity->entityId != E_VALHALLA_KNIGHT) {
        DestroyEntity(self);
        return;
    }
    curFrame = tempEntity->animCurFrame;
    self->facingLeft = tempEntity->facingLeft;
    self->posX.val = tempEntity->posX.val;
    self->posY.val = tempEntity->posY.val;
    if (self->params) {
        hitboxPtr = D_us_801820CC;
        hitboxPtr += D_us_801820E0[curFrame] * 4;
    } else {
        hitboxPtr = D_us_80182094;
        hitboxPtr += D_us_801820B8[curFrame] * 4;
    }
    self->hitboxOffX = *hitboxPtr++;
    self->hitboxOffY = *hitboxPtr++;
    self->hitboxWidth = *hitboxPtr++;
    self->hitboxHeight = *hitboxPtr++;
}

void func_us_801C8AAC(Entity* self) {
    Entity* tempEntity;
    unkStr_80182100* ptr;
    s32 delay;

    if (!self->step) {
        InitializeEntity(g_EInitValhallaKnightUnk1);
        self->animCurFrame = self->params + 18;
        self->zPriority += self->params;
        self->flags |= FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
        self->drawFlags |= FLAG_DRAW_ROTATE;
        ptr = D_us_80182100;
        ptr += self->params;
        if (self->facingLeft) {
            self->velocityX -= ptr->velocityX;
        } else {
            self->velocityX += ptr->velocityX;
        }
        self->velocityY += ptr->velocityY;
    }
    MoveEntity();
    self->velocityY += FIX(0.0625);
    ptr = D_us_80182100;
    ptr += self->params;
    self->rotate += ptr->rotate;
    if ((self->params & 3) == 0) {
        delay = g_Timer - (self->params >> 2);
        if ((delay & 7) == 0) {
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
                tempEntity->params = Random() & 1;
                tempEntity->zPriority = self->zPriority + 1;
            }
        }
    }
    if (!self->params && (g_Timer & 7) == 0) {
        g_api.PlaySfx(SFX_EXPLODE_FAST_B);
    }
}
