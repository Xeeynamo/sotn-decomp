// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo1.h"

bool func_801CDC80(s16* value, s16 target, s16 step) {
    if (abs(*value - target) < step) {
        *value = target;
        return true;
    }

    if (*value > target) {
        *value -= step;
    }

    if (*value < target) {
        *value += step;
    }

    return false;
}

INCLUDE_ASM("boss/bo1/nonmatchings/unk_21C80", func_us_801A1878);

INCLUDE_ASM("boss/bo1/nonmatchings/unk_21C80", func_us_801A2774);

INCLUDE_ASM("boss/bo1/nonmatchings/unk_21C80", func_us_801A2BC4);

INCLUDE_ASM("boss/bo1/nonmatchings/unk_21C80", func_us_801A2CC4);

INCLUDE_ASM("boss/bo1/nonmatchings/unk_21C80", func_us_801A2D90);

INCLUDE_ASM("boss/bo1/nonmatchings/unk_21C80", func_us_801A2F2C);

INCLUDE_ASM("boss/bo1/nonmatchings/unk_21C80", func_us_801A3480);

INCLUDE_ASM("boss/bo1/nonmatchings/unk_21C80", func_us_801A38EC);

INCLUDE_ASM("boss/bo1/nonmatchings/unk_21C80", func_us_801A4394);

INCLUDE_ASM("boss/bo1/nonmatchings/unk_21C80", func_us_801A45D0);

INCLUDE_ASM("boss/bo1/nonmatchings/unk_21C80", func_us_801A493C);

INCLUDE_ASM("boss/bo1/nonmatchings/unk_21C80", func_us_801A4AF4);

INCLUDE_ASM("boss/bo1/nonmatchings/unk_21C80", func_us_8019D260_from_rcen);
