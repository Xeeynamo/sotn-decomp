// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rbo4/rbo4.h"

INCLUDE_ASM("boss/rbo4_psp/nonmatchings/rbo4_psp/unk_E3A0", func_us_80192B38_from_rbo3);

extern EInit D_us_801804E4;

void func_us_80198A18(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801804E4);
        self->drawFlags |= ENTITY_ROTATE;
        if ((self->params & 0xF) % 2) {
            self->rotate = ROT(-90);
        } else {
            self->rotate = 0;
        }
        self->zPriority = (0x40 - self->params) & 0xF;
        if (self->params & 0x100) {
            self->animCurFrame = 0x64;
        } else {
            self->animCurFrame = 0x62;
        }
        self->ext.et_801BDA0C.unk84 = 0;
        self->ext.et_801BDA0C.unk80 = 0;
        return;

    case 1:
        self->palette = PAL_FLAG(0x4F);
        return;
    }
}
