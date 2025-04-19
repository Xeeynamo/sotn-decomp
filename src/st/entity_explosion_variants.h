// SPDX-License-Identifier: AGPL-3.0-or-later
static s32 explode_yVel[] = {
    /* 1020 */ FIX(4.0 / 128),
    /* 1024 */ FIX(20.0 / 128),
    /* 1028 */ FIX(36.0 / 128),
    /* 102C */ FIX(56.0 / 128),
    /* 1030 */ FIX(112.0 / 128),
    /* 1034 */ FIX(144.0 / 128),
};

static u8 explode_startFrame[] = {
    /* 1038 */ 1,
    /* 1039 */ 9,
    /* 103A */ 21,
    /* 103B */ 43,
};

static u16 explode_lifetime[] = {
    /* 103C */ 0x0010,
    /* 103E */ 0x0018,
    /* 1040 */ 0x002A,
    /* 1042 */ 0x002F,
};

// ID is 0x14.

// Creates 4 different explosion animations for when objects or enemies are
// destroyed or killed. The animations are more intense as self->params
// increases (from 0 to 3).

void EntityExplosionVariants(Entity* self) {
    if (!self->step) {
        self->velocityY = explode_yVel[self->ext.destructAnim.index];
        self->flags =
            FLAG_UNK_2000 | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_POS_CAMERA_LOCKED;
        self->palette = PAL_OVL(0x195);
        self->animSet = ANIMSET_DRA(2);
        self->animCurFrame = explode_startFrame[self->params];
        self->drawMode = DRAW_TPAGE;
        self->step++;
    } else {
        self->posY.val -= self->velocityY;
        ++self->poseTimer;
        if (!(self->poseTimer % 2)) {
            self->animCurFrame++;
        }

        if (self->poseTimer > explode_lifetime[self->params]) {
            DestroyEntity(self);
        }
    }
}
