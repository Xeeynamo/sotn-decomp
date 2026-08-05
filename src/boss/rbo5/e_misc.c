// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo5.h"

#if defined(VERSION_PSP)
#include "../../st/pfn_entity_update.h"

extern EInit g_EInitUnkId13;
extern EInit g_EInitParticle;

extern void EntityExplosionVariants(Entity* entity);
extern void EntityGreyPuff(Entity* entity);

void EntityUnkId13(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitUnkId13);
        self->ext.ent13.parentId = self->ext.ent13.parent->entityId;
    case 1:
        if (self->ext.ent13.fiveFrameCounter++ > 4) {
            Entity* newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->entityId = E_EXPLOSION;
                newEntity->pfnUpdate = EntityExplosion;
                newEntity->params = self->params;
            }
            self->ext.ent13.fiveFrameCounter = 0;
        }
        self->posX.i.hi = self->ext.ent13.parent->posX.i.hi;
        self->posY.i.hi = self->ext.ent13.parent->posY.i.hi;
        if (self->ext.ent13.parent->entityId != self->ext.ent13.parentId) {
            DestroyEntity(self);
        }
        break;
    }
}

static s16 greyPuff_rot[] = {
    0x030, 0x050, 0x080, 0x0B0, 0x0D0, 0x100, 0x100, 0x000,
};

static s32 greyPuff_yVel[] = {
    FIX(2.0 / 128),  FIX(18.0 / 128), FIX(30.0 / 128),
    FIX(48.0 / 128), FIX(60.0 / 128), FIX(96.0 / 128),
};

static s32 explode_yVel[] = {
    FIX(4.0 / 128),  FIX(20.0 / 128),  FIX(36.0 / 128),
    FIX(56.0 / 128), FIX(112.0 / 128), FIX(144.0 / 128),
};

static u8 explode_startFrame[] = {1, 9, 21, 43};
static u16 explode_lifetime[] = {16, 24, 42, 47};

void EntityExplosionVariants(Entity* self) {
    if (!self->step) {
        self->velocityY = explode_yVel[self->ext.destructAnim.index];
        self->flags =
            FLAG_UNK_2000 | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_POS_CAMERA_LOCKED;
        self->palette = PAL_FLAG(PAL_UNK_195);
        self->animSet = ANIMSET_DRA(2);
        self->animCurFrame = explode_startFrame[self->params];
        self->blendMode = BLEND_TRANSP;
        self->step++;
    } else {
        self->posY.val -= self->velocityY;
        ++self->poseTimer;
        if ((self->poseTimer % 2) == 0) {
            self->animCurFrame++;
        }
        if (self->poseTimer > explode_lifetime[self->params]) {
            DestroyEntity(self);
        }
    }
}

void EntityGreyPuff(Entity* self) {
    if (!self->step) {
        self->flags =
            FLAG_UNK_2000 | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_POS_CAMERA_LOCKED;
        self->palette = PAL_FLAG(PAL_UNK_195);
        self->animSet = ANIMSET_DRA(5);
        self->animCurFrame = 1;
        self->blendMode = BLEND_TRANSP;
        self->drawFlags = ENTITY_SCALEX | ENTITY_SCALEY;
        self->scaleX = greyPuff_rot[self->params];
        self->scaleY = self->scaleX;
        self->velocityY = greyPuff_yVel[self->params];
        self->step++;
    } else {
        self->posY.val -= self->velocityY;
        self->poseTimer++;
        if ((self->poseTimer % 2) == 0) {
            self->animCurFrame++;
        }
        if (self->poseTimer > 36) {
            DestroyEntity(self);
        }
    }
}

void EntityIntenseExplosion(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitParticle);
        self->palette = PAL_FLAG(PAL_UNK_170);
        self->animSet = ANIMSET_DRA(5);
        self->animCurFrame = 1;
        self->blendMode = BLEND_TRANSP | BLEND_ADD;
        if (self->params & 0xF0) {
            self->palette = PAL_FLAG(PAL_UNK_195);
            self->blendMode = BLEND_TRANSP;
        }
        if (self->params & 0xFF00) {
            self->zPriority = (self->params & 0xFF00) >> 8;
        }
        self->zPriority += 8;
    } else {
        self->poseTimer++;
        self->posY.val -= FIX(0.25);
        if ((self->poseTimer % 2) == 0) {
            self->animCurFrame++;
        }
        if (self->poseTimer > 36) {
            DestroyEntity(self);
        }
    }
}
#else
void EntityUnkId13(Entity* self);
void EntityExplosionVariants(Entity* self);
void EntityGreyPuff(Entity* self);

#include "../../st/e_misc.h"
#endif
