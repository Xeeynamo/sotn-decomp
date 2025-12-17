// SPDX-License-Identifier: AGPL-3.0-or-later
u32 ServantUpdateAnim(Entity* self, s8* frameProps, AnimationFrame** frames) {
    s32 ret = 0;
    if (self->poseTimer == -1) {
        ret = -1;
    } else if (self->poseTimer == 0) {
        self->poseTimer = ((u16*)self->anim)[self->pose * 2];
        ret = 0;
    } else if (--self->poseTimer == 0) {
        self->pose++;
        // Effectively a switch statement, but breaks if I actually use one.
        if (((u16*)self->anim)[self->pose * 2] == 0) {
            self->pose = ((u16*)self->anim + 1)[self->pose * 2];
            self->poseTimer = ((u16*)self->anim)[self->pose * 2];
            ret = 0;
        } else if (((u16*)self->anim)[self->pose * 2] == 0xFFFF) {
            self->pose -= 1;
            self->poseTimer = -1;
            ret = -1;
        } else if (((u16*)self->anim)[self->pose * 2] == 0xFFFE) {
            self->anim = frames[((u16*)self->anim + 1)[self->pose * 2]];
            self->pose = 0;
            self->poseTimer = ((u16*)self->anim)[self->pose * 2];
            ret = -2;
        } else {
            self->poseTimer = ((u16*)self->anim)[self->pose * 2];
        }
    }
    if (frameProps != NULL) {
        // This is ugly - theoretically the type for frameProps should be
        // FrameProperty* but anything besides this where we assign this big
        // expression fails.
        frameProps =
            &frameProps[((((u16*)self->anim + 1)[self->pose * 2] >> 9) & 0x7F)
                        << 2];
        self->hitboxOffX = *frameProps;
        frameProps++;
        self->hitboxOffY = *frameProps;
        frameProps++;
        self->hitboxWidth = *frameProps;
        frameProps++;
        self->hitboxHeight = *frameProps;
    }
    self->animCurFrame = ((u16*)self->anim + 1)[self->pose * 2] & 0x1FF;
    return ret;
}
