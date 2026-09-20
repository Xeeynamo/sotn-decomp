// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno1.h"

INCLUDE_ASM("st/rno1/nonmatchings/unk_268AC", func_us_801A68AC);

INCLUDE_ASM("st/rno1/nonmatchings/unk_268AC", func_us_801A700C);

void func_us_801B7CC4_from_no1(Entity* self) {
    if (!self->step) {
        g_api.PlaySfx(SET_RELEASE_RATE_HIGH_20_21);
        self->step++;
    }
    DestroyEntity(self);
}
