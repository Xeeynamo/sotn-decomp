// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

// e_plate_lord from no0 is the only place in decompiled code that StepTowards
// is in.  That suggests that this file may be an e_plate_lord variant or
// similar entity.

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

// EntitySpectralSword
INCLUDE_ASM("st/dai/nonmatchings/e_spectral_sword", func_us_801D64A0);

INCLUDE_ASM("st/dai/nonmatchings/e_spectral_sword", func_us_801D6FC8);

INCLUDE_ASM("st/dai/nonmatchings/e_spectral_sword", func_us_801D70A0);
