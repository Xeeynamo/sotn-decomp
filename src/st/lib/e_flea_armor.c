// SPDX-License-Identifier: AGPL-3.0-or-later
#include "lib.h"

// Flea armor
void EntityFleaMan(Entity* self);
extern EInit D_us_801809BC;
extern s32 D_us_80181ACC;
extern u8 D_us_80182D78[];
extern u8 D_us_80182D84[];
extern s16 D_us_80182D8C[];
extern s16 D_us_80182D9C[];
extern Point32 D_us_80182DA4[];

void EntityFleaArmor(Entity* self) {
    Collider collider;
    Entity* entity;
    s32 i;
    s32 posY;
    s32 posX;

    u8 collision;

    if (D_us_80181ACC & 1) {
        self->flags |= FLAG_DEAD;
    }

    if (self->step < 8 && self->flags & FLAG_DEAD) {
        self->step = 8;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801809BC);
        CreateEntityFromEntity(E_ID_4B, self, self + 1);
        self->drawMode |= DRAW_TPAGE2 | DRAW_TPAGE;
        break;

    case 1:
        if (UnkCollisionFunc3(D_us_80182D8C) & 1) {
            self->step++;
        }
        break;

    case 2:
        AnimateEntity(D_us_80182D78, self);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        if (GetDistanceToPlayerX() < 112) {

            if (self->facingLeft) {
                self->velocityX = FIX(2.0);
            } else {
                self->velocityX = FIX(-2.0);
            }
            self->velocityY = FIX(-0.5);
            self->ext.fleaArmor.counter = 0;
            self->animFrameIdx = 0;
            self->animFrameDuration = 0;
            self->step = 3;
        }
        break;

    case 3:
        if (self->velocityY == 0 && self->ext.fleaArmor.counter) {
            AnimateEntity(D_us_80182D84, self);
            collision = UnkCollisionFunc2(D_us_80182D9C);
            self->ext.fleaArmor.counter2++;

            if ((self->ext.fleaArmor.counter2 % 4) == 0) {
                if (self->facingLeft) {
                    EntityExplosionVariantsSpawner(self, 1, 1, 0, 16, 3, -2);
                } else {
                    EntityExplosionVariantsSpawner(self, 1, 1, 0, 16, 3, 2);
                }
                self->ext.fleaArmor.counter2 = 0;
            }

            if (!(Random() & 0x1F)) {
                self->ext.fleaArmor.counter = 0;
                self->velocityY = FIX(-2.0);
            } else if (GetDistanceToPlayerX() < 64) {
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                self->step_s = 0;
                self->step = 4;
            }

            if (collision & 0x80) {
                if (collision & 0xF) {
                    self->facingLeft ^= 1;
                }
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                self->step_s = 0;
                self->step = 4;
            }
        } else if (UnkCollisionFunc3(D_us_80182D8C) & 1) {
            if (self->facingLeft) {
                self->velocityX = FIX(2.0);
            } else {
                self->velocityX = FIX(-2.0);
            }
            self->ext.fleaArmor.counter = 1;
            return;
        }
        break;

    case 4:
        if (!self->step_s) {
            if (self->facingLeft) {
                self->velocityX = FIX(2.0);
            } else {
                self->velocityX = FIX(-2.0);
            }

            if (Random() & 1) {
                self->velocityY = FIX(-3.5);
                self->velocityX = self->velocityX / 4;
                PlaySfxPositional(SFX_STOMP_HARD_E);
            } else {
                self->velocityY = FIX(-7.0);
                PlaySfxPositional(SFX_STOMP_HARD_D);
            }

            self->ext.fleaArmor.flag = 0;
            self->step_s++;
        }

        posX = self->posX.i.hi;
        if (self->velocityX > 0) {
            posX += 16;
        }
        if (self->velocityX < 0) {
            posX -= 16;
        }
        posY = self->posY.i.hi;

        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->velocityX = 0;
        }
        if (self->velocityY < 0) {
            posY -= 16;
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                self->velocityY = 0;
            }
        }

        if (UnkCollisionFunc3(D_us_80182D8C) & 1) {
            self->step_s = 0;
            self->step = 2;
        } else {
            if (self->velocityY < 0) {
                self->animCurFrame = 7;
            }

            if (self->velocityY > FIX(-0.0625)) {
                self->animCurFrame = 8;
                if (!self->ext.fleaArmor.flag) {
                    PlaySfxPositional(SFX_BONE_THROW);
                    self->ext.fleaArmor.flag = 1;
                }
            }
            if (self->velocityY > FIX(0.0625)) {
                self->animCurFrame = 9;
            }
        }
        break;
    case 8:
        PlaySfxPositional(SFX_LOW_SKEL_EXPLODE);

        for (i = 0; i < 6; i++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                DestroyEntity(entity);
                MakeEntityFromId(E_ID_4A, self, entity);
                entity->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                                 FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
                entity->facingLeft = self->facingLeft;
                entity->animCurFrame = i + 10;
                if (self->facingLeft) {
                    entity->velocityX = D_us_80182DA4[i].x;
                } else {
                    entity->velocityX = -D_us_80182DA4[i].x;
                }
                entity->velocityY = D_us_80182DA4[i].y;
                entity->step = 9;
            }
        }

        if (entity != NULL) {
            entity->drawFlags |= FLAG_DRAW_ROTZ;
        }

        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            DestroyEntity(entity);
            CreateEntityFromEntity(2, self, entity);
            entity->params = 1;
        }
        self->velocityX = 0;
        self->flags = FLAG_POS_CAMERA_LOCKED;
        self->drawFlags = FLAG_DRAW_DEFAULT;
        LOHU(self->ext.fleaArmor.counter) = 16;
        self->hitPoints = S16_MAX;
        self->step = 0;
        self->entityId = E_ID_4C;
        self->pfnUpdate = EntityFleaMan;
        break;

    case 9:
        MoveEntity();
        self->rotZ += 256;
        self->velocityY += FIX(0.25);
        break;

    case 16:
        if (g_pads[0].pressed & PAD_SQUARE) {
            if (!self->params) {
                self->animCurFrame++;
                self->params |= 1;
            } else {
                break;
            }
        } else {
            self->params = 0;
        }

        if (g_pads[0].pressed & PAD_CIRCLE) {
            if (!self->step_s) {
                self->animCurFrame--;
                self->step_s |= 1;
            }
        } else {
            self->step_s = 0;
        }
        break;
    }
}

// Flea armor death pieces?
extern Point16 D_us_80182DD4[];
extern Size16 D_us_80182DDC[];
extern EInit D_us_801809C8;

void func_us_801D00C4(Entity* self) {
    Entity* prevEntity;
    u8 animCurFrame;

    if (!self->step) {
        InitializeEntity(D_us_801809C8);
    }

    prevEntity = self - 1;
    animCurFrame = prevEntity->animCurFrame;
    if (animCurFrame == 9) {
        animCurFrame -= 8;
    } else {
        animCurFrame = 0;
    }
    self->hitboxOffX = D_us_80182DD4[animCurFrame].x;
    self->hitboxOffY = D_us_80182DD4[animCurFrame].y;
    self->hitboxWidth = D_us_80182DDC[animCurFrame].width;
    self->hitboxHeight = D_us_80182DDC[animCurFrame].height;
    self->facingLeft = prevEntity->facingLeft;
    self->hitboxState = prevEntity->hitboxState;
    self->posX.i.hi = prevEntity->posX.i.hi;
    self->posY.i.hi = prevEntity->posY.i.hi;
    if (prevEntity->entityId != E_ID_4A) {
        DestroyEntity(self);
    }
}
