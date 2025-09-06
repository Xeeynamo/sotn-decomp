// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cat.h"

INCLUDE_ASM("st/cat/nonmatchings/unk_44C7C", func_us_801C4C7C);

void func_us_801C5600(Primitive* prim)
{
    if ((g_Timer % prim->u3) != 0) {
        return;
    }
    prim->y0 -= 1;

    if (prim->y0 < prim->u2 + 144) {
        prim->r0 -= 8;
        prim->g0 -= 4;
        prim->b0 -= 4;
    }
    if (prim->r0 < 8) {
        prim->p3 = 0;
        prim->drawMode = 8;
    }

}

INCLUDE_ASM("st/cat/nonmatchings/unk_44C7C", func_us_801C56A0);

INCLUDE_ASM("st/cat/nonmatchings/unk_44C7C", func_us_801C589C);

INCLUDE_ASM("st/cat/nonmatchings/unk_44C7C", func_us_801C5DF4);

INCLUDE_ASM("st/cat/nonmatchings/unk_44C7C", func_us_801C6360);

INCLUDE_ASM("st/cat/nonmatchings/unk_44C7C", func_us_801C6F9C);

INCLUDE_ASM("st/cat/nonmatchings/unk_44C7C", func_us_801C7420);

INCLUDE_ASM("st/cat/nonmatchings/unk_44C7C", func_us_801C774C);

INCLUDE_ASM("st/cat/nonmatchings/unk_44C7C", func_us_801C7D98);

INCLUDE_ASM("st/cat/nonmatchings/unk_44C7C", func_us_801C7F84);

INCLUDE_ASM("st/cat/nonmatchings/unk_44C7C", func_us_801C80E0);

INCLUDE_ASM("st/cat/nonmatchings/unk_44C7C", func_us_801C839C);

INCLUDE_ASM("st/cat/nonmatchings/unk_44C7C", func_us_801C8CE0);
