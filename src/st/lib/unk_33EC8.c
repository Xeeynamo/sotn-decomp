// SPDX-License-Identifier: AGPL-3.0-or-later
#include "lib.h"

Primitive* func_us_801B3EC8(Primitive* prim, u32 number, u16 maxDigits) {
    s32 i;
    s32 currentDigit;

    bool hasADigit = false;
    for (currentDigit = maxDigits - 1; currentDigit >= 0; currentDigit--) {
        u32 digitValue = number;
        for (i = 0; i < currentDigit; i++) {
            digitValue /= 10;
        }
        if (digitValue != 0) {
            if (digitValue < 10) {
                prim->u0 = digitValue * 8;
                prim->v0 = 8;
            } else {
                prim->u0 = 0x28;
                prim->v0 = 0x10;
            }
            for (i = 0; i < currentDigit; i++) {
                digitValue *= 10;
            }
            number -= digitValue;
            hasADigit = true;
            prim->drawMode = DRAW_DEFAULT;
        } else if (hasADigit || currentDigit == 0) {
            prim->u0 = 0;
            prim->v0 = 8;
            prim->drawMode = DRAW_DEFAULT;
        } else {
            prim->drawMode = DRAW_HIDE;
        }
        prim = prim->next;
    }
    return prim;
}

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

const char D_us_801ACF14[] = "DEF";
const char D_us_801ACF18[] = "ATT";
const char D_us_801ACF1C[] = _S("うれるこすう");
const char D_us_801ACF24[] = _S("Not equipped");
const char D_us_801ACF34[] = _S("Equipped");
const char D_us_801ACF40[] = _S("Number");
