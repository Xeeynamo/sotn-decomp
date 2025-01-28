// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

extern s16 D_us_80183230[];
extern s16 D_us_80183240[];
extern s16 D_us_80183248[];
extern s16 D_us_80183258[];
extern u8 D_us_80183268[];
extern u8 D_us_80183280[];
extern u8 D_us_80183294[];
extern u8 D_us_8018329C[];
extern u8 D_us_801832B4[];
extern u8 D_us_801832C4[];
extern u8 D_us_801832E8[];

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
                CreateEntityFromCurrentEntity(E_ID_55, tempEntity);
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
extern Point16 D_us_801832FC[];
extern Point16 D_us_80183310[];

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

    if (parent->entityId != E_ID_53) {
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
extern u8 D_us_80183324[];
extern s16 D_us_8018332C[];
extern s16 D_us_8018333C[];

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
            if (entity->entityId != E_ID_53) {
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
extern s32 D_us_8018334C[];
extern s32 D_us_8018335C[];
extern u16 D_us_8018336C[];
extern u16 D_us_80183374[];
extern s16* D_us_801833BC[];

void func_us_801D544C(Entity* self) {
    Collider collider;
    s16 x, y;
    s16 params;
    s32 velocityY;
    s32 posX;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180B30);
        self->flags =
            FLAG_DESTROY_IF_OUT_OF_CAMERA |
            FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA | FLAG_POS_CAMERA_LOCKED |
            FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_UNK_2000;
        self->hitboxState = 0;
        params = self->params;
        posX = D_us_8018334C[params];
        self->ext.skeletonApeBarrel.unk80 = posX;
        if (self->facingLeft != 0) {
            self->ext.skeletonApeBarrel.unk80 = -posX;
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
