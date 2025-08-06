// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rtop.h"

// Yorick
INCLUDE_ASM("st/rtop/nonmatchings/e_yorick", EntityYorick);

extern EInit D_us_801805E4;
extern u16 D_us_80181480[];

void EntityYorickSkull(Entity* self) {
    Entity* entity;
    s32 offsetX;
    s32 offsetY;
    s32 sfxVol;
    Collider collider;

    // has yorick's skull been destroyed?
    if (self->flags & 0x100) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 0;
        }
        PlaySfxPositional(0x658);
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801805E4);
        self->drawFlags |= 4;
        self->animCurFrame = 0x1E;
        break;

    case 1:
        if (UnkCollisionFunc3(&D_us_80181480) & 1) {
            self->step++;
        }
        break;

    case 2:
        entity = self - 1;
        offsetX = entity->posX.i.hi- self->posX.i.hi;
        if (!self->ext.ILLEGAL.u8[0xC]) {
            if (abs(offsetX) < 4) {
                SetStep(3);
            }
        } else if (abs(offsetX) < 6) {
            self->rotate += offsetX * 128;
        }
        break;

    case 3:
        if (!self->step_s) {
            if (self->ext.ILLEGAL.u8[0xD]) {
                self->velocityX = FIX(4.5);
            } else {
                self->velocityX = FIX(-4.5);
            }
            self->velocityY = -FIX(1.5);
            self->ext.ILLEGAL.u8[0x18] = 0;
            self->step_s++;
        }

        MoveEntity();
        self->velocityY += FIX(0.25);
        self->velocityX -= (self->velocityX / 24);
        self->rotate += self->velocityX >> 8;

        offsetX = self->posX.i.hi;
        offsetY = self->posY.i.hi + 4;
        g_api.CheckCollision(offsetX,
                             offsetY,
                             &collider,
                             0);

        if (collider.effects & 1) {
            sfxVol = 0x7F - (self->ext.ILLEGAL.u8[0x18] * 8);
            if (sfxVol > 0) {
                g_api.PlaySfxVolPan(SFX_SKULL_BONK, sfxVol, 0);
            }
            self->ext.ILLEGAL.u8[0x18]++;
            self->posY.i.hi += collider.unk18;

            if (self->velocityY < FIX(0.5)) {
                self->velocityY = 0;
            } else {
                self->velocityY = -self->velocityY / 2;
            }
        }
        offsetX = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
        offsetX -= self->ext.ILLEGAL.u32[2];

        self->ext.ILLEGAL.u8[0xC] = 0;
        if (offsetX < -0x60) {
            self->velocityX = 0;
            self->ext.ILLEGAL.u8[0xD] = 1;
            self->ext.ILLEGAL.u8[0xC] = 1;
        }
        if (offsetX > 0x60) {
            self->velocityX = 0;
            self->ext.ILLEGAL.u8[0xD] = 0;
            self->ext.ILLEGAL.u8[0xC] = 1;
        }

        if ((abs(self->velocityX) < FIX(0.25)) && (self->velocityY == 0)) {
            self->step--;
        }
        break;
    }

    entity = self - 1;
    if (entity->entityId != E_YORICK) {
        self->flags |= 0xC0000000;
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
    self->flags |= 0xC0202000;
    self->animCurFrame = self->params + 15;
    self->drawFlags = FLAG_DRAW_ROTATE;

    if (self->facingLeft) {
        self->velocityX = -self->velocityX;
    }
}

// TODO: split

