// SPDX-License-Identifier: AGPL-3.0-or-later
extern s16 unk15_rot[];
extern s32 unk15_yVel[];

// looks like a particle of dust fading away
void EntityGreyPuff(Entity* self) {
    if (!self->step) {
        self->flags =
            FLAG_UNK_2000 | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_POS_CAMERA_LOCKED;
        self->palette = PAL_OVL(0x195);
        self->animSet = ANIMSET_DRA(5);
        self->animCurFrame = 1;
        self->drawMode = DRAW_TPAGE;
        self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
        self->rotX = unk15_rot[self->params];
        self->rotY = self->rotX;
        self->velocityY = unk15_yVel[self->params];
        self->step++;
    } else {
        self->posY.val -= self->velocityY;
        self->animFrameDuration++;
        if (!(self->animFrameDuration % 2)) {
            self->animCurFrame++;
        }
        if (self->animFrameDuration > 36) {
            DestroyEntity(self);
        }
    }
}
