// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"
// e_plate_lord from no0 is the only place in decompiled code that StepTowards
// is in.  That suggests that this file may be an e_plate_lord variant or
// similar entity.
INCLUDE_ASM("st/dai/nonmatchings/unk_550E4", func_us_801D50E4);

INCLUDE_ASM("st/dai/nonmatchings/unk_550E4", func_us_801D5458);

INCLUDE_ASM("st/dai/nonmatchings/unk_550E4", func_us_801D56C0);

INCLUDE_ASM("st/dai/nonmatchings/unk_550E4", func_us_801D56F4);

INCLUDE_ASM("st/dai/nonmatchings/unk_550E4", func_us_801D636C);

bool StepTowards(s16* val, s32 target, s32 step) {
    if (abs(*val - target) < step) {
        *val = target;
        return true;
    }

    if (target < *val) {
        *val -= step;
    }

    if (*val < target) {
        *val += step;
    }

    return false;
}

INCLUDE_ASM("st/dai/nonmatchings/unk_550E4", func_us_801D64A0);

INCLUDE_ASM("st/dai/nonmatchings/unk_550E4", func_us_801D6FC8);

INCLUDE_ASM("st/dai/nonmatchings/unk_550E4", func_us_801D70A0);
