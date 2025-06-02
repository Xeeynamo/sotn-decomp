// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

void func_801961DC(s16 arg0) {
    s16 temp_v0 = arg0 - g_unkGraphicsStruct.unkC;

    if (temp_v0 > 1) {
        g_unkGraphicsStruct.unkC++;
    } else if (temp_v0 < -1) {
        g_unkGraphicsStruct.unkC--;
    } else {
        g_unkGraphicsStruct.unkC = arg0;
    }
}

INCLUDE_ASM("st/dai/nonmatchings/unk_458C4", func_us_801C5920);

INCLUDE_ASM("st/dai/nonmatchings/unk_458C4", func_us_801C5B88);
