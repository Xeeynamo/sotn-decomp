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

void func_us_801B4010(u16* arg0) {
    *arg0++ = g_Status.equipment[0];
    *arg0++ = g_Status.equipment[1];
    *arg0++ = g_Status.equipment[2];
    *arg0++ = g_Status.equipment[3];
    *arg0++ = g_Status.equipment[4];
    *arg0++ = g_Status.equipment[5];
    *arg0 = g_Status.equipment[6];
}

void func_us_801B4080(u16* arg0) {
    g_Status.equipment[0] = *arg0++;
    g_Status.equipment[1] = *arg0++;
    g_Status.equipment[2] = *arg0++;
    g_Status.equipment[3] = *arg0++;
    g_Status.equipment[4] = *arg0++;
    g_Status.equipment[5] = *arg0++;
    g_Status.equipment[6] = *arg0;
}

void func_us_801B40F0(u16* arg0) {
    *arg0 = g_Status.attackHands[0];
    arg0 += 2;
    *arg0 = g_Status.attackHands[1];
    arg0 += 2;
    *arg0 = g_Status.defenseEquip;
    arg0 += 2;
    *arg0 = g_Status.statsBase[0] + g_Status.statsEquip[0];
    arg0 += 2;
    *arg0 = g_Status.statsBase[1] + g_Status.statsEquip[1];
    arg0 += 2;
    *arg0 = g_Status.statsBase[2] + g_Status.statsEquip[2];
    arg0 += 2;
    *arg0 = g_Status.statsBase[3] + g_Status.statsEquip[3];
}

extern s32 D_us_80181674;
extern u16 D_us_80181684[];

Primitive* func_us_801B4194(Primitive* prim) {
    Primitive* prim2;
    s32 i;
    u16* ptr;

    prim = func_us_801B1064(prim, 0xAA, 0xB0, D_us_80181674, 0x196);
    prim2 = prim;
    ptr = D_us_80181684;
    for (i = 0; i < 2; i++) {
        prim2->x0 = *ptr++;
        prim2->y0 = *ptr++;
        prim2 = prim2->next;
    }
    return prim;
}

const char D_us_801ACF14[] = "DEF";
const char D_us_801ACF18[] = "ATT";
const char D_us_801ACF1C[] = _S("うれるこすう");
const char D_us_801ACF24[] = _S("Not equipped");
const char D_us_801ACF34[] = _S("Equipped");
const char D_us_801ACF40[] = _S("Number");
