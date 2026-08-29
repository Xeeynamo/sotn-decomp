// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno1/rno1.h"

INCLUDE_ASM("st/rno1_psp/nonmatchings/rno1_psp/unk_14688", func_us_801A9BEC);

INCLUDE_ASM("st/rno1_psp/nonmatchings/rno1_psp/unk_14688", func_us_801A68AC);

INCLUDE_ASM("st/rno1_psp/nonmatchings/rno1_psp/unk_14688", func_us_801A700C);

void func_us_801B7CC4_from_no1(Entity* self) {
    if (self->step == 0) {
        g_api_PlaySfx(0xA1);
        self->step += 1;
    }
    DestroyEntity(self);
}
