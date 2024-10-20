// SPDX-License-Identifier: AGPL-3.0-or-later
extern s32 unk14_yVel[];
extern u8 unk14_startFrame[];
extern u16 unk14_lifetime[];

// Appears to be related to some sort of explosion or puff of smoke.
// ID is 0x14.
void EntityUnkId14(Entity* self) {
    if (!self->step) {
        self->velocityY = unk14_yVel[self->ext.generic.unk94];
        self->flags =
            FLAG_UNK_2000 | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_POS_CAMERA_LOCKED;
        self->palette = PAL_OVL(0x195);
        self->animSet = ANIMSET_DRA(2);
        self->animCurFrame = unk14_startFrame[self->params];
        self->drawMode = DRAW_TPAGE;
        self->step++;
    } else {
        self->posY.val -= self->velocityY;
        ++self->animFrameDuration;
        if (!(self->animFrameDuration % 2)) {
            self->animCurFrame++;
        }

        if (self->animFrameDuration > unk14_lifetime[self->params]) {
            DestroyEntity(self);
        }
    }
}
