// SPDX-License-Identifier: AGPL-3.0-or-later
extern u8 LionLampAnim[];
extern EInit STAGE_EINIT_COMMON;

void EntityLionLamp(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(STAGE_EINIT_COMMON);
        self->zPriority = 0x58;
        // fallthrough

    case 1:
        AnimateEntity(LionLampAnim, self);
        if (g_Timer & 1) {
            self->palette = 0;
        } else {
            self->palette = 1;
        }
        break;

    case 0xFF:
        FntPrint("charal %x\n", self->animCurFrame);
        if (g_pads[1].pressed & PAD_SQUARE) {
            if (self->params) {
                return;
            }
            self->animCurFrame++;
            self->params |= 1;
        } else {
            self->params = 0;
        }

        if (g_pads[1].pressed & PAD_CIRCLE) {
            if (self->step_s == 0) {
                self->animCurFrame--;
                self->step_s |= 1;
            }
        } else {
            self->step_s = 0;
        }
        break;
    }
}
