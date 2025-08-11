// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rtop.h"

// Yorick
extern u8 D_us_80181490[];
extern u8 D_us_801814A0[];
extern u8 D_us_801814BC[];
extern s32 D_us_801814C4[];
extern s32 D_us_801814E0[];
extern s16 D_us_801814FC[];
extern s16 D_us_8018150C[];
extern EInit g_EInitSkeletonPieces;
extern s16 D_us_80181468[];
extern s16 D_us_80181478[];

void EntityYorick(Entity* self) {
    Entity* entity;
    s32 i;
    s32 offsetX;

    if (self->flags & FLAG_DEAD) {
        SetStep(8);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSkeletonPieces);
        self->animCurFrame = 0x18;
        self->hitboxOffX = -1;
        self->hitboxOffY = 2;

        // fallthrough
    case 1:
        if (UnkCollisionFunc3(D_us_80181468) & 1) {
            self->ext.yorick.unk84 = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
            entity = self + 1;
            CreateEntityFromEntity(E_YORICK_SKULL, self, entity);
            entity->ext.yorickSkull.unk84 = self->ext.yorick.unk84;
            entity->posX.i.hi += 4;
            self->step++;
        }
        break;

    case 2:
        entity = self + 1;
        offsetX = self->posX.i.hi - entity->posX.i.hi;
        if (entity->ext.yorickSkull.unk88) {
            SetStep(3);
        }
        if (offsetX > 0) {
            self->facingLeft = 0;
        } else {
            self->facingLeft = 1;
        }

        if (self->facingLeft) {
            self->velocityX = FIX(1.0);
        } else {
            self->velocityX = FIX(-1.0);
        }

        UnkCollisionFunc2(D_us_80181478);
        AnimateEntity(D_us_80181490, self);
        if (entity->entityId != E_YORICK_SKULL) {
            self->ext.yorick.timer = 0;
            SetStep(4);
        }
        break;

    case 3:
        entity = self + 1;
        if (entity->entityId != E_YORICK_SKULL) {
            self->ext.yorick.timer = 0;
            SetStep(4);
            break;
        }

        switch (self->step_s) {
        case 0:
            UnkCollisionFunc2(D_us_80181478);
            AnimateEntity(D_us_80181490, self);
            offsetX = self->posX.i.hi - entity->posX.i.hi;
            if (self->facingLeft) {
                offsetX = -offsetX;
            }

            if (offsetX < -0x18) {
                self->animCurFrame = 0x18;
                entity->ext.yorickSkull.unk88 = false;
                self->ext.yorick.timer = 0x10;
                SetSubStep(1);
            }
            break;
        case 1:
            if (!--self->ext.yorick.timer) {
                self->velocityY = FIX(-2.0);
                self->velocityX = 0;
                self->step_s++;
            }
            break;
        case 2:
            if (UnkCollisionFunc3(D_us_80181468) & 1) {
                self->ext.yorick.timer = 0x10;
                self->step_s++;
            }
            break;
        case 3:
            if (!--self->ext.yorick.timer) {
                SetStep(2);
            }
        }
        break;

    case 4:
        switch (self->step_s) {
        case 0:
            self->velocityY = -FIX(4);
            self->velocityX = 0;
            self->step_s++;
            break;
        case 1:
            AnimateEntity(D_us_801814A0, self);
            if (UnkCollisionFunc3(D_us_80181468) & 1) {
                PlaySfxPositional(SFX_STOMP_HARD_C);
                ++self->ext.yorick.timer;
                if (self->ext.yorick.timer > 2) {
                    SetStep(5);
                    return;
                }
                self->step_s--;
                return;
            }
            break;
        }
        break;

    case 5:
        if (!self->step_s) {
            self->ext.yorick.timer = (Random() & 0x3F) + 0x40;
            self->facingLeft = Random() & 1;
            self->step_s++;
        }
        if (self->facingLeft) {
            self->velocityX = FIX(1.0);
        } else {
            self->velocityX = FIX(-1.0);
        }
        UnkCollisionFunc2(D_us_80181478);
        AnimateEntity(D_us_80181490, self);

        if (!--self->ext.yorick.timer) {
            self->step_s = 0;
        }
        break;

    case 8:
        for (i = 1; i < 6; i++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity == NULL) {
                break;
            }
            CreateEntityFromCurrentEntity(E_SKELETON_PARTS, entity);
            entity->facingLeft = self->facingLeft;
            entity->params = i;
            entity->ext.skeleton.explosionTimer2 = D_us_801814BC[i];
            if (self->facingLeft) {
                entity->posX.i.hi -= D_us_801814FC[i];
            } else {
                entity->posX.i.hi += D_us_801814FC[i];
            }
            entity->posY.i.hi += D_us_8018150C[i];
            entity->velocityX = D_us_801814C4[i];
            entity->velocityY = D_us_801814E0[i];
        }
        PlaySfxPositional(SFX_SKELETON_DEATH_C);
        DestroyEntity(self);
        break;
    }
}

extern EInit D_us_801805E4;
extern u16 D_us_80181480[];

void EntityYorickSkull(Entity* self) {
    Entity* entity;
    s32 offsetX;
    s32 offsetY;
    s32 sfxVol;
    Collider collider;

    // has yorick's skull been destroyed?
    if (self->flags & FLAG_DEAD) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 0;
        }
        PlaySfxPositional(SFX_EXPLODE_E);
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801805E4);
        self->drawFlags |= FLAG_DRAW_ROTATE;
        self->animCurFrame = 0x1E;
        break;

    case 1:
        if (UnkCollisionFunc3(&D_us_80181480) & 1) {
            self->step++;
        }
        break;

    case 2:
        entity = self - 1;
        offsetX = entity->posX.i.hi - self->posX.i.hi;
        if (!self->ext.yorickSkull.unk88) {
            if (abs(offsetX) < 4) {
                SetStep(3);
            }
        } else if (abs(offsetX) < 6) {
            self->rotate += offsetX * 128;
        }
        break;

    case 3:
        if (!self->step_s) {
            if (self->ext.yorickSkull.unk89) {
                self->velocityX = FIX(4.5);
            } else {
                self->velocityX = FIX(-4.5);
            }
            self->velocityY = -FIX(1.5);
            self->ext.yorickSkull.unk94 = 0;
            self->step_s++;
        }

        MoveEntity();
        self->velocityY += FIX(0.25);
        self->velocityX -= (self->velocityX / 24);
        self->rotate += self->velocityX >> 8;

        offsetX = self->posX.i.hi;
        offsetY = self->posY.i.hi + 4;
        g_api.CheckCollision(offsetX, offsetY, &collider, 0);

        if (collider.effects & EFFECT_SOLID) {
            sfxVol = 0x7F - (self->ext.yorickSkull.unk94 * 8);
            if (sfxVol > 0) {
                g_api.PlaySfxVolPan(SFX_SKULL_BONK, sfxVol, 0);
            }
            self->ext.yorickSkull.unk94++;
            self->posY.i.hi += collider.unk18;

            if (self->velocityY < FIX(0.5)) {
                self->velocityY = 0;
            } else {
                self->velocityY = -self->velocityY / 2;
            }
        }
        offsetX = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
        offsetX -= self->ext.yorickSkull.unk84;

        self->ext.yorickSkull.unk88 = 0;
        if (offsetX < -0x60) {
            self->velocityX = 0;
            self->ext.yorickSkull.unk89 = true;
            self->ext.yorickSkull.unk88 = true;
        }
        if (offsetX > 0x60) {
            self->velocityX = 0;
            self->ext.yorickSkull.unk89 = false;
            self->ext.yorickSkull.unk88 = true;
        }

        if ((abs(self->velocityX) < FIX(0.25)) && (self->velocityY == 0)) {
            self->step--;
        }
        break;
    }

    entity = self - 1;
    if (entity->entityId != E_YORICK) {
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                       FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
    }
}

extern u16 anim_bone_rot[];
extern EInit g_EInitSkeletonPieces;

void EntitySkeletonPieces(Entity* self) { // From skeleton death explosion
    if (self->step) {
        if (--self->ext.skeleton.explosionTimer2) {
            self->rotate += anim_bone_rot[self->params];
            FallEntity();
            MoveEntity();
            return;
        }

        self->entityId = E_EXPLOSION;
        self->pfnUpdate = (PfnEntityUpdate)EntityExplosion;
        self->params = 0;
        self->step = 0;
        return;
    }

    InitializeEntity(g_EInitSkeletonPieces);
    self->flags |=
        FLAG_DESTROY_IF_OUT_OF_CAMERA | FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
        FLAG_UNK_00200000 | FLAG_UNK_2000;
    self->animCurFrame = self->params + 15;
    self->drawFlags = FLAG_DRAW_ROTATE;

    if (self->facingLeft) {
        self->velocityX = -self->velocityX;
    }
}
