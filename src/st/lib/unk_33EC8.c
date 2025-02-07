// SPDX-License-Identifier: AGPL-3.0-or-later
#include "lib.h"

INCLUDE_ASM("st/lib/nonmatchings/unk_33EC8", func_us_801B3EC8);

Primitive* func_us_801B3FB4(Primitive* prim, u8* uv, u16 count, s32 arg3) {
    u8 d;
    s32 i;
    u32 max;
    u8* ptr;

    ptr = uv;
    max = 0;
    for (i = 0; i < count; i++) {
#ifdef VERSION_PSP
        if (*ptr == 0xFF) {
            break;
        }
        ptr++;
        max++;
    }
    for (i = 0; i < max; i++) {
#endif
        d = *uv++;
        prim->u0 = (d & 0xF) * 8;
        prim->v0 = (d & 0xF0) >> 1;
        if (arg3 != 0) {
            prim->drawMode = DRAW_DEFAULT;
        }
        prim = prim->next;
    }
#ifdef VERSION_PSP
    for (; i < count; i++) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
#endif
    return prim;
}

INCLUDE_ASM("st/lib/nonmatchings/unk_33EC8", func_us_801B4010);

INCLUDE_ASM("st/lib/nonmatchings/unk_33EC8", func_us_801B4080);

INCLUDE_ASM("st/lib/nonmatchings/unk_33EC8", func_us_801B40F0);

INCLUDE_ASM("st/lib/nonmatchings/unk_33EC8", func_us_801B4194);

INCLUDE_RODATA("st/lib/nonmatchings/unk_33EC8", D_us_801ACF14);

INCLUDE_RODATA("st/lib/nonmatchings/unk_33EC8", D_us_801ACF18);

INCLUDE_RODATA("st/lib/nonmatchings/unk_33EC8", D_us_801ACF1C);

INCLUDE_RODATA("st/lib/nonmatchings/unk_33EC8", D_us_801ACF24);

INCLUDE_RODATA("st/lib/nonmatchings/unk_33EC8", D_us_801ACF34);

INCLUDE_RODATA("st/lib/nonmatchings/unk_33EC8", D_us_801ACF40);
