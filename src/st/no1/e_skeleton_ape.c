// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

// Skeleton Ape
INCLUDE_ASM("st/no1/nonmatchings/e_skeleton_ape", func_us_801D49E4);

// Skeleton Ape related (barrel spawner?)
INCLUDE_ASM("st/no1/nonmatchings/e_skeleton_ape", func_us_801D4F18);

// Skeleton Ape barrel helper
void func_us_801D5008(Entity*, Entity*);
INCLUDE_ASM("st/no1/nonmatchings/e_skeleton_ape", func_us_801D5008);

// Skeleton Ape barrel
extern u16 D_us_80180B30[];
extern u8 D_us_80183324[];
extern s16 D_us_8018332C[];
extern s16 D_us_8018333C[];

void func_us_801D5040(Entity* self) {
    s16 i;
    Collider collider;
    Entity* entity;
    s16 x, y;
    s32 velocityY;
    s16 rand;

    FntPrint("step %x\n", self->step);
    entity = self->ext.skeletonApeBarrel.unkEntity;
    if ((self->flags & FLAG_DEAD) && (self->step != 4)) {
        SetStep(4U);
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
        if (self->ext.skeletonApeBarrel.unk0) {
            self->ext.skeletonApeBarrel.unk0--;
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
            self->ext.skeletonApeBarrel.unk84 = 3;
        } else {
            self->ext.skeletonApeBarrel.unk84 = 0;
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

                self->ext.skeletonApeBarrel.unk84++;
                if (self->ext.skeletonApeBarrel.unk84 > 2) {
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
        if (!(self->ext.skeletonApeBarrel.unk0 & 7)) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, entity);
                rand = Random() & 7;
                entity->posX.i.hi += D_us_8018333C[rand];
                rand = (rand - 4) & 7;
                entity->posY.i.hi += D_us_8018333C[rand];
            }
        }

        self->ext.skeletonApeBarrel.unk0++;
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

        entity->ext.skeletonApeBarrel.unkEntity = NULL;

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
INCLUDE_ASM("st/no1/nonmatchings/e_skeleton_ape", func_us_801D544C);
