// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno4.h"

extern EInit g_EInitParticle;

// Unused here
static s16 explosionVariantSizes[] = {
    0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x00};

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
        return;
    }

    self->posY.val -= self->velocityY;
    ++self->poseTimer;
    if ((self->poseTimer % 2) == 0) {
        self->animCurFrame++;
    }
    if (self->poseTimer > explode_lifetime[self->params]) {
        DestroyEntity(self);
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
        self->animSet = 5;
        self->animCurFrame = 1;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        if (self->params & 0xF0) {
            self->palette = PAL_FLAG(PAL_UNK_195);
            self->blendMode = BLEND_TRANSP;
        }
        if (self->params & 0xFF00) {
            self->zPriority = (u16)((self->params & 0xFF00) >> 8);
        }
        self->zPriority += 8;
        return;
    }

    self->poseTimer++;
    self->posY.val -= FIX(0.25);

    if ((self->poseTimer % 2) == 0) {
        self->animCurFrame++;
    }

    if (self->poseTimer > 36) {
        DestroyEntity(self);
    }
}

void PlaySfxPositional(s16 sfxId) {
    s32 posX, posY;
    s16 sfxPan;
    s16 sfxVol;

    posX = g_CurrentEntity->posX.i.hi - 128;
    sfxPan = (abs(posX) - 32) >> 5;
    if (sfxPan > 8) {
        sfxPan = 8;
    } else if (sfxPan < 0) {
        sfxPan = 0;
    }
    if (posX < 0) {
        sfxPan = -sfxPan;
    }
    sfxVol = abs(posX) - 96;
    posY = abs(g_CurrentEntity->posY.i.hi - 128) - 112;
    if (posY > 0) {
        sfxVol += posY;
    }
    if (sfxVol < 0) {
        sfxVol = 0;
    }
    sfxVol = 127 - (sfxVol >> 1);
    if (sfxVol > 0) {
        g_api.PlaySfxVolPan(sfxId, sfxVol, sfxPan);
    }
}
