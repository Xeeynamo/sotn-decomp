// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo5.h"

INCLUDE_ASM("boss/bo5/nonmatchings/unk_25F88", func_us_801A5F88);

INCLUDE_ASM("boss/bo5/nonmatchings/unk_25F88", func_us_801A62B4);

void func_us_801A666C(Primitive* prim, s16 arg1) {
    prim->x0 = prim->x2 -= arg1;
    prim->x1 = prim->x3 += arg1;
    prim->y0 = prim->y1 -= arg1;
    prim->y2 = prim->y3 += arg1;
}

INCLUDE_ASM("boss/bo5/nonmatchings/unk_25F88", func_us_801A66B0);

void func_801B1D68(Entity* self) { func_us_801A66B0(self, 0); }

INCLUDE_ASM("boss/bo5/nonmatchings/unk_25F88", BO5_RicSetDeadPrologue);
