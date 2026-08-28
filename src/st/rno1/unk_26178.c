// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno1.h"

INCLUDE_ASM("st/rno1/nonmatchings/unk_26178", EntityBreakable);

#include "e_rno1_breakable_debris.h"

INCLUDE_ASM("st/rno1/nonmatchings/unk_26178", RNO1_DebugShowWaitInfo);

INCLUDE_ASM("st/rno1/nonmatchings/unk_26178", RNO1_DebugInputWait);

INCLUDE_ASM("st/rno1/nonmatchings/unk_26178", func_us_801A68AC);

INCLUDE_ASM("st/rno1/nonmatchings/unk_26178", func_us_801A700C);

void func_us_801B7CC4_from_no1(Entity* self) {
    if (!self->step) {
        g_api_PlaySfx(0xA1);
        self->step++;
    }
    DestroyEntity(self);
}

INCLUDE_ASM("st/rno1/nonmatchings/unk_26178", func_us_801B8F50_from_no1);

INCLUDE_ASM("st/rno1/nonmatchings/unk_26178", func_us_801BE880_from_no1);

INCLUDE_ASM("st/rno1/nonmatchings/unk_26178", func_us_801BEB54_from_no1);

INCLUDE_ASM("st/rno1/nonmatchings/unk_26178", func_us_801BEE00_from_no1);

INCLUDE_ASM("st/rno1/nonmatchings/unk_26178", func_us_801BF074_from_no1);

INCLUDE_ASM("st/rno1/nonmatchings/unk_26178", func_us_801A86A8);
