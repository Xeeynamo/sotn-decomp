// SPDX-License-Identifier: AGPL-3.0-or-later
extern u16 g_InitializeEntityData0[];

// params: (& 0xF0) Use an alternate set of hardcoded palette and drawMode
//         (& 0xFF00) if non-zero, uses ((& 0xFF00) >> 8) as the zPriority
void EntityIntenseExplosion(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_InitializeEntityData0);
        self->palette = PAL_OVL(0x170);
        self->animSet = ANIMSET_DRA(5);
        self->animCurFrame = 1;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        if (self->params & 0xF0) {
            self->palette = PAL_OVL(0x195);
            self->drawMode = DRAW_TPAGE;
        }

        if (self->params & 0xFF00) {
            self->zPriority = (self->params & 0xFF00) >> 8;
        }
        self->zPriority += 8;
    } else {
        self->animFrameDuration++;
        self->posY.val -= FIX(0.25);
        if ((self->animFrameDuration % 2) == 0) {
            self->animCurFrame++;
        }

        if (self->animFrameDuration > 36) {
            DestroyEntity(self);
        }
    }
}
