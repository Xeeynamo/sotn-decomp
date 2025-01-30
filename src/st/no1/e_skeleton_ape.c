// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

static s16 D_us_80183230[] = {0, 24, 0, 4, 8, -4, -16, 0};
static s16 D_us_80183240[] = {0, 24, 8, 0};
static s16 D_us_80183248[] = {6, 8, 16, 0, 7, 11, 4, 6};
static s16 D_us_80183258[] = {-16, -8, -4, -8, 6, 3, 16, 12};
static u8 D_us_80183268[] = {
    13, 1, 6, 2, 6, 3, 6, 4, 6, 5, 13, 6, 6, 5, 6, 4, 6, 3, 6, 2, 6, 1, 0, 0};
static u8 D_us_80183280[] = {
    4, 7, 35, 8, 2, 9, 4, 10, 4, 11, 67, 12, 3, 11, 3, 10, -1, 0, 0, 0};
static u8 D_us_80183294[] = {35, 1, 67, 13, 1, 1, -1, 0};
static u8 D_us_8018329C[] = {18, 15, 9, 16, 9, 17, 9, 18, 9, 19, 18, 20,
                             9,  19, 9, 18, 9, 17, 9, 16, 0, 0,  0,  0};
static u8 D_us_801832B4[] = {
    4, 15, 8, 21, 6, 22, 6, 23, 48, 24, 4, 23, -1, 0, 0, 0};
static u8 D_us_801832C4[] = {
    3,  27, 3, 28, 3, 27, 2, 28, 2, 27, 2, 28, 1, 27, 1, 28, 1,  27,
    14, 28, 5, 29, 5, 30, 5, 31, 5, 32, 5, 33, 5, 34, 5, 35, -1, 0};
static u8 D_us_801832E8[] = {
    2, 1, 2, 38, 4, 37, 5, 36, 15, 25, 3, 36, 3, 37, 2, 38, 2, 1, 0, 0};
static Point16 D_us_801832FC[] = {{0, 0}, {-2, 2}, {-6, 4}, {-8, 4}, {9, 2}};
static Point16 D_us_80183310[] = {
    {0, 0}, {17, 21}, {20, 20}, {20, 20}, {12, 23}};
static u8 D_us_80183324[] = {2, 40, 2, 41, 2, 42, 0, 0};
static s16 D_us_8018332C[] = {0, 16, 0, 4, 8, -4, -16, 0};
static s16 D_us_8018333C[] = {0, 8, 12, 8, 0, -8, -12, -8};
static s32 D_us_8018334C[] = {FIX(2.0), FIX(3.0 / 4), FIX(-1.0), FIX(-7.5 / 4)};
static s32 D_us_8018335C[] = {FIX(-2.25), FIX(-3.25), FIX(-2.75), FIX(-2.0)};
static u16 D_us_8018336C[] = {0x2B, 0x2C, 0x2D, 0x2E};
static u16 D_us_80183374[] = {0x38, 0x45, 0x3C, 0x34};
static s16 D_us_8018337C[] = {0, 4, 0, 4, 8, -4, -16, 0};
static s16 D_us_8018338C[] = {0, 12, 0, 4, 8, -4, -16, 0};
static s16 D_us_8018339C[] = {0, 8, 0, 4, 8, -4, -16, 0};
static s16 D_us_801833AC[] = {0, 16, 0, 4, 8, -4, -16, 0};
static s16* D_us_801833BC[] = {
    D_us_8018337C, D_us_8018338C, D_us_8018339C, D_us_801833AC, NULL};

void EntitySkeletonApe(Entity* self) {
    Entity* tempEntity;
    s16 tempVar;

    if (self->flags & FLAG_DEAD) {
        if (self->step != 7) {
            self->ext.skeletonApe.unk7C = 0;
            self->step = 7;
        }
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSkeletonApe);
        if (self->params == 2) {
            self->flags |= FLAG_UNK_2000;
        }
        self->facingLeft = (GetSideToPlayer() ^ 1) & 1;
        tempEntity = self + 1;
        CreateEntityFromCurrentEntity(E_ID_54, tempEntity);
        if (self->params) {
            tempEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (tempEntity != NULL) {
                CreateEntityFromCurrentEntity(
                    E_SKELETON_APE_BARREL, tempEntity);
                tempEntity->ext.skeletonApe.unkEntity = self;
                tempEntity->zPriority = self->zPriority - 1;
                self->ext.skeletonApe.unkEntity = tempEntity;
                if (self->params == 2) {
                    tempEntity->params = 1;
                    self->hitboxState = 0;
                }
                self->animCurFrame = 0xF;
            } else {
                self->params = 0;
            }
        }
        break;

    case 1:
        if (self->step_s) {
            if (!AnimateEntity(D_us_801832E8, self)) {
                SetStep(2);
            }
        } else if (UnkCollisionFunc3(D_us_80183230) & 1) {
            if (self->params) {
                SetStep(2);
            } else {
                self->step_s++;
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
            }
        }
        break;

    case 2:
        tempVar = GetDistanceToPlayerX();
        if (self->params) {
            AnimateEntity(D_us_8018329C, self);
            tempEntity = self->ext.skeletonApe.unkEntity;
            if (tempEntity == NULL) {
                self->params = 0;
                break;
            } else if ((tempVar < 0x60 && GetDistanceToPlayerY() < 0x50) ||
                       self->params == 2) {
                SetStep(6);
                tempEntity->step++;
                tempEntity->ext.skeletonApe.unk7C = 4;
                if (self->params == 2) {
                    self->hitboxState = 3;
                }
                break;
            }
        } else {
            AnimateEntity(D_us_80183268, self);
            if ((self->facingLeft ^ GetSideToPlayer()) & 1) {
                if (tempVar < 0x22) {
                    SetStep(4);
                    break;
                }
            } else {
                if (tempVar < 0x1C) {
                    SetStep(5);
                    break;
                }
            }
        }
        if (self->facingLeft) {
            self->velocityX = FIX(0.25);
        } else {
            self->velocityX = FIX(-0.25);
        }
        if ((UnkCollisionFunc2(D_us_80183240) & 0x60) == 0x60) {
            self->posX.val -= self->velocityX;
        }
        break;

    case 3:
        if (!AnimateEntity(D_us_801832E8, self)) {
            self->step = 1;
            if (self->facingLeft) {
                self->velocityX = FIX(0.25);
            } else {
                self->velocityX = FIX(-0.25);
            }
            self->velocityY = FIX(-4.0);
        }
        break;

    case 4:
        tempVar = AnimateEntity(D_us_80183280, self);
        if (!tempVar) {
            SetStep(2);
        } else if ((tempVar & 0x80) && self->animFrameIdx == 3) {
            PlaySfxPositional(SFX_WEAPON_STAB_A);
        }
        break;

    case 5:
        tempVar = AnimateEntity(D_us_80183294, self);
        if (!tempVar) {
            SetStep(2);
        } else if ((tempVar & 0x80) && self->animFrameIdx == 2) {
            PlaySfxPositional(SFX_BONE_THROW);
        }
        break;

    case 6:
        if (AnimateEntity(D_us_801832B4, self) == 0) {
            SetStep(2);
            self->params = 0;
        }
        break;

    case 7:
        tempVar = AnimateEntity(D_us_801832C4, self);
        if (!tempVar) {
            EntityExplosionSpawn(2, SFX_FM_THUNDER_EXPLODE);
        } else if ((tempVar & 0x80) && self->animCurFrame > 28) {
            PlaySfxPositional(SFX_EXPLODE_B);
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, tempEntity);
                tempEntity->posY.i.hi +=
                    D_us_80183258[self->ext.skeletonApe.unk7C];
                if (self->facingLeft) {
                    tempEntity->posX.i.hi -=
                        D_us_80183248[self->ext.skeletonApe.unk7C];
                } else {
                    tempEntity->posX.i.hi +=
                        D_us_80183248[self->ext.skeletonApe.unk7C];
                }
            }
            self->ext.skeletonApe.unk7C++;
        }
        break;
    }
}

// Skeleton Ape punch attack
void func_us_801D4F18(Entity* self) {
    Entity* parent;
    u16 animCurFrame;

    if (self->step == 0) {
        InitializeEntity(D_us_80180B3C);
    }

    parent = self - 1;
    animCurFrame = parent->animCurFrame - 9;
    if (animCurFrame >= 6) {
        animCurFrame = 0;
    }

    self->hitboxOffX = D_us_801832FC[animCurFrame].x;
    self->hitboxOffY = D_us_801832FC[animCurFrame].y;
    self->hitboxWidth = D_us_80183310[animCurFrame].x;
    self->hitboxHeight = D_us_80183310[animCurFrame].y;
    self->facingLeft = parent->facingLeft;
    self->hitboxState = parent->hitboxState & 1;
    self->posX.i.hi = parent->posX.i.hi;
    self->posY.i.hi = parent->posY.i.hi;

    if (parent->entityId != E_SKELETON_APE) {
        DestroyEntity(self);
    }
}

// Skeleton Ape barrel helper, positions barrel sprite when held by the ape
// self is the barrel and parent is the ape
// Will likely do a rename pass in the future for the skeleton ape as a whole
void func_us_801D5008(Entity* self, Entity* parent) {
    self->posY.i.hi = parent->posY.i.hi - 28;
    self->posX.i.hi = parent->posX.i.hi;
    if (self->facingLeft != 0) {
        self->posX.i.hi -= 10;
    } else {
        self->posX.i.hi += 10;
    }
}

// Skeleton Ape barrel
void EntitySkeletonApeBarrel(Entity* self) {
    s16 i;
    Collider collider;
    Entity* entity;
    s16 x, y;
    s32 velocityY;
    s16 rand;

    FntPrint("step %x\n", self->step);
    entity = self->ext.skeletonApe.unkEntity;
    if ((self->flags & FLAG_DEAD) && (self->step != 4)) {
        SetStep(4);
    }

    if (self->step < 3) {
        if (entity->step == 7) {
            SetStep(4);
        } else {
            if (entity->entityId != E_SKELETON_APE) {
                DestroyEntity(self);
                return;
            }
        }
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180B30);
        self->facingLeft = entity->facingLeft;
        func_us_801D5008(self, entity);
        if (self->params) {
            self->flags |= FLAG_UNK_2000;
        }
        break;

    case 1:
        func_us_801D5008(self, entity);
        break;

    case 2:
        if (self->ext.skeletonApe.unk7C) {
            self->ext.skeletonApe.unk7C--;
            func_us_801D5008(self, entity);
            return;
        }
        self->velocityY = FIX(-4.0);
        if (self->facingLeft) {
            self->velocityX = FIX(2.0);
        } else {
            self->velocityX = FIX(-2.0);
        }

        if (self->params) {
            self->ext.skeletonApe.unk84 = 3;
        } else {
            self->ext.skeletonApe.unk84 = 0;
        }
        self->step++;
        self->drawFlags = FLAG_DRAW_ROTZ;
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                       FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
        break;

    case 3:
        AnimateEntity(D_us_80183324, self);
        self->rotZ -= 64;
        velocityY = self->velocityY;
        if (UnkCollisionFunc3(D_us_8018332C) & 1) {
            if (velocityY > 0) {
                velocityY = velocityY / 2;
                if (velocityY < FIX(1.0 / 2.0)) {
                    velocityY = 0;
                }
                self->velocityY = -velocityY;

                self->ext.skeletonApe.unk84++;
                if (self->ext.skeletonApe.unk84 > 2) {
                    SetStep(4);
                    return;
                }
            }
        }

        if (self->facingLeft) {
            self->velocityX = FIX(2);
        } else {
            self->velocityX = FIX(-2);
        }
        if (!(self->ext.skeletonApe.unk7C & 7)) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, entity);
                rand = Random() & 7;
                entity->posX.i.hi += D_us_8018333C[rand];
                rand = (rand - 4) & 7;
                entity->posY.i.hi += D_us_8018333C[rand];
            }
        }

        self->ext.skeletonApe.unk7C++;
        x = self->posX.i.hi;
        y = self->posY.i.hi + 8;

        if (!self->params) {

            if (self->facingLeft) {
                x += 16;
            } else {
                x -= 16;
            }

            g_api.CheckCollision(x, y, &collider, 0);

            if (collider.effects & EFFECT_UNK_0002) {
                SetStep(4);
                return;
            }
        }
        break;

    case 4:
        if (self->step_s) {
            EntityExplosionSpawn(3, SFX_FM_EXPLODE_A);
            return;
        }

        entity->ext.skeletonApe.unkEntity = NULL;

        for (i = 0; i < 4; i++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromCurrentEntity(E_ID_56, entity);
                entity->params = i;
                entity->facingLeft = self->facingLeft;
                entity->velocityX = self->velocityX;
            }
        }
        self->step_s++;
        break;
    }
}

// Skeleton Ape barrel explosion
void func_us_801D544C(Entity* self) {
    Collider collider;
    s16 x, y;
    s16 params;
    s32 velocityY;
    s32 velocityX;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180B30);
        self->flags =
            FLAG_DESTROY_IF_OUT_OF_CAMERA |
            FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA | FLAG_POS_CAMERA_LOCKED |
            FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_UNK_2000;
        self->hitboxState = 0;
        params = self->params;
        velocityX = D_us_8018334C[params];
        self->ext.skeletonApeBarrel.unk80 = velocityX;
        if (self->facingLeft != 0) {
            self->ext.skeletonApeBarrel.unk80 = -velocityX;
        }
        self->ext.skeletonApeBarrel.unk80 += self->velocityX;
        self->velocityY = D_us_8018335C[params];
        self->animCurFrame = D_us_8018336C[params];
        self->ext.skeletonApeBarrel.unk7C = D_us_80183374[params];
        return;
    case 1:
        self->velocityX = self->ext.skeletonApeBarrel.unk80;
        velocityY = self->velocityY;
        if (UnkCollisionFunc3(D_us_801833BC[self->params]) & 1) {
            if (velocityY > 0) {
                velocityY /= 2;
                self->ext.skeletonApeBarrel.unk80 /= 2;
                if (velocityY < 0x4000) {
                    velocityY = 0;
                    self->ext.skeletonApeBarrel.unk80 = 0;
                }
                self->velocityY = -velocityY;
                self->velocityX = self->ext.skeletonApeBarrel.unk80;
            } else {
                EntityExplosionSpawn(0, SFX_EXPLODE_B);
            }
        }

        x = self->posX.i.hi;
        y = self->posY.i.hi;
        if (self->facingLeft) {
            x += 0x10;
        } else {
            x -= 0x10;
        }
        g_api.CheckCollision(x, y, &collider, 0);
        if ((collider.effects & EFFECT_UNK_0002) ||
            !--self->ext.skeletonApeBarrel.unk7C) {
            EntityExplosionSpawn(0, SFX_EXPLODE_B);
        }
        return;
    }
}
