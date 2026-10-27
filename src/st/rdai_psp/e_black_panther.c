// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rdai/rdai.h"

void func_us_801C4B2C() {
    s32 i;
    s32 xVar2;
    s32 yVar2;
    s32 xVar1;
    s32 yVar1;
    Primitive* prim2;
    Primitive* prim;

    prim = g_CurrentEntity->ext.prim;
    for(i = 0; i < 7; i++) {
        prim2 = prim->next;
        xVar1 = prim2->x2 + prim->x0;
        xVar1 /= 2;
        yVar1 = prim2->y2 + prim->y0;
        yVar1 /= 2;
        xVar2 = prim->x2 - xVar1;
        yVar2 = prim->y2 - yVar1;
        
        xVar2 = xVar2 / 8 + xVar1;
        yVar2 = yVar2 / 8 + yVar1;
        prim2->x0 = prim->x2 = xVar2;
        prim2->y0 = prim->y2 = yVar2;
        
        xVar1 = prim2->x3 + prim->x1;
        xVar1 /= 2;
        yVar1 = prim2->y3 + prim->y1;
        yVar1 /= 2;
        xVar2 = prim->x3 - xVar1;
        yVar2 = prim->y3 - yVar1;
        
        xVar2 = xVar2 / 8 + xVar1;
        yVar2 = yVar2 / 8 + yVar1;
        prim2->x1 = prim->x3 = xVar2;
        prim2->y1 = prim->y3 = yVar2;
        prim = prim2;
    }
}

INCLUDE_ASM("st/rdai_psp/nonmatchings/rdai_psp/e_black_panther", func_us_801C4C4C);

INCLUDE_ASM("st/rdai_psp/nonmatchings/rdai_psp/e_black_panther", func_us_801C5AA0);

INCLUDE_ASM("st/rdai_psp/nonmatchings/rdai_psp/e_black_panther", EntityBlackPanther);
