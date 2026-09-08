// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rcen/rcen.h"

extern s32 g_RcenShaftFlags;
extern s32 E_ID(UNK_1C);

s16 func_us_8019A98C(s16 arg0, s16 arg1, s16 arg2) {
    s16 v_s1;
    s16 v_s0;

    arg1 &= 0xFFF;
    v_s1 = arg2 - arg1;
    v_s0 = v_s1;
    if (v_s1 > ROT(180)) {
        v_s0 = v_s1 - ROT(360);
    }
    if (v_s1 < ROT(-180)) {
        v_s0 = v_s1 + ROT(360);
    }
    if (abs(v_s0) > arg0) {
        if (v_s1 < 0) {
            v_s0 = arg1 - arg0;
        } else {
            v_s0 = arg1 + arg0;
        }
        return v_s0;
    }
    return arg2;
}

#include "../rcen/func_us_8019aa04.h"

INCLUDE_ASM("st/rcen_psp/nonmatchings/rcen_psp/e_shaft", EntityShaft);

#include "../rcen/func_us_8019b5a4.h"

INCLUDE_ASM("st/rcen_psp/nonmatchings/rcen_psp/e_shaft", func_us_8019B6D4);
INCLUDE_ASM("st/rcen_psp/nonmatchings/rcen_psp/e_shaft", func_us_8019B8A8);

#include "../rcen/func_us_8019c4ec.h"
#include "../rcen/func_us_8019c610.h"

INCLUDE_ASM("st/rcen_psp/nonmatchings/rcen_psp/e_shaft", func_us_8019C7B8);

#include "../rcen/func_us_8019cda0.h"

INCLUDE_ASM("st/rcen_psp/nonmatchings/rcen_psp/e_shaft", func_us_8019CDF8);
