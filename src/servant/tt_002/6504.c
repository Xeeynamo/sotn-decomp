// SPDX-License-Identifier: AGPL-3.0-or-later
#include "faerie.h"

INCLUDE_ASM("servant/tt_002/nonmatchings/6504", func_us_80176504);

void func_us_80176B6C(Entity* self) {
    s32 temp_unk0;
    s32 temp_unk2;
    s32 i;
#ifdef VERSION_PSP
    s32 temp_zPriority;
#else
    s16 temp_zPriority;
#endif

    if (!self->step) {
        func_us_801739D0(self);
        self->ext.faerie.unk7C = &thisFamiliar;
        self->step += 1;
    }
    self->posX.val = self->ext.faerie.unk7C->posX.val;
    self->posY.val = self->ext.faerie.unk7C->posY.val;
    self->facingLeft = self->ext.faerie.unk7C->facingLeft;

    for (i = 6; i <= 0x2D; i++) {
        if (self->ext.faerie.unk7C->anim == D_us_80172B14[i])
            break;
    }

    temp_unk0 = abs(D_us_80172368[i - 6].unk0);
    temp_unk2 = D_us_80172368[i - 6].unk2;

    func_us_80173994(self, temp_unk0);

    if (temp_unk2) {
        temp_zPriority = s_zPriority - 1;
    } else {
        temp_zPriority = s_zPriority + 1;
    }

    self->zPriority = temp_zPriority;

    ServantUpdateAnim(self, 0, D_us_80172B14);
}
