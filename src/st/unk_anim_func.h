// SPDX-License-Identifier: AGPL-3.0-or-later

// Notably, this is completely unused.
// The use of the 0xBB offset in the entity, which does not match the current
// entity struct, suggests that this was for an older form of Entity.
// When the Entity was changed, this function was already unused, so was never
// updated. This is just a theory though.

#define SELF_BB (*((u8*)&self->unkB8 + 3))

u8 UnkAnimFunc(u8 frames[], Entity* self, u8 arg2) {
    u16 animFrameStart = self->pose * 2;
    u8* var_s1 = &frames[animFrameStart];
    s16 var_a1 = 0;

    if (self->poseTimer == 0) {
        if (*var_s1 != 0) {
            if (*var_s1 == 0xFF) {
                return 0;
            }
            self->poseTimer = *var_s1++ + SELF_BB;
            self->animCurFrame = *var_s1++;
            self->pose++;
            var_a1 = 128;
        } else {
            var_s1 = frames;
            self->pose = 0;
            self->poseTimer = 0;
            SELF_BB = (arg2 * Random()) >> 8;
            self->poseTimer = *var_s1++ + SELF_BB;
            self->animCurFrame = *var_s1;
            self->pose++;
            return 0;
        }
    }
    self->poseTimer--;
    self->animCurFrame = var_s1[-1];
    var_a1 |= 1;
    return var_a1;
}
