// SPDX-License-Identifier: AGPL-3.0-or-later

extern EInit D_us_80180658;
extern s32 D_us_801817CC[];

void func_us_801AE414(Entity* self) {
    switch (self->step_s) {
    case 0:
        InitializeEntity(D_us_80180658);
        self->animCurFrame = self->params + 0x1C;
        /* fall through */
    case 1:
        MoveEntity();
        self->velocityY += (u32)self->ext.et_801AE414.accelY;
        self->ext.et_801AE414.accelY += D_us_801817CC[self->params];
    }
}
