// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno0/rno0.h"

static s16 func_us_801C1F98(Primitive* prim, s16 dx) {
    prim->drawMode = DRAW_UNK02;
    prim->v0 = prim->v1 = 0x50;
    prim->v2 = prim->v3 = 0x50 + 0x10;
    prim->y0 = prim->y1 = 0xBC;
    prim->y2 = prim->y3 = 0xBC + 0x10;
    prim->u0 = prim->u2 = 2;
    prim->x0 = prim->x2 = dx;
    dx -= 0x20;

    if (dx < 0x50) {
        dx = 0x50 - dx;
        prim->u1 = prim->u3 = 0x22 - dx;
        prim->x1 = prim->x3 = 0x50;
        dx = 0;
    } else {
        prim->u1 = prim->u3 = 0x22;
        prim->x1 = prim->x3 = dx;
    }
    return dx;
}

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_25FF0", func_us_801C2044);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_25FF0", func_us_801C2184_from_no0);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_25FF0", EntityUnkId1B);
