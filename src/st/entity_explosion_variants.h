// SPDX-License-Identifier: AGPL-3.0-or-later
extern s32 explode_yVel[];
extern u8 explode_startFrame[];
extern u16 explode_lifetime[];

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
        ++self->animFrameDuration;
        if (!(self->animFrameDuration % 2)) {
            self->animCurFrame++;
        }

        if (self->animFrameDuration > explode_lifetime[self->params]) {
            DestroyEntity(self);
        }
    }
}
