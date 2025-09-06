// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cat.h"

INCLUDE_ASM("st/cat/nonmatchings/unk_44C7C", func_us_801C4C7C);

void func_us_801C5600(Primitive* arg0)
{
    if ((g_Timer % arg0->u3) != 0) {
        return;
    }
    arg0->y0 -= 1;

    if (arg0->y0 < arg0->u2 + 0x90) {
        arg0->r0 -= 8;
        arg0->g0 -= 4;
        arg0->b0 -= 4;
    }
    if (arg0->r0 < 8) {
        arg0->p3 = 0;
        arg0->drawMode = 8;
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
