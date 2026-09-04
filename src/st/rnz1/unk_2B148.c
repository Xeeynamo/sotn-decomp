// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rnz1.h"

void func_801B2CF8(s32* arg0) {
    s32* ptr = arg0;
    s32 bound = 13;
    s32 i;

    for(i = 0; i < bound; i++) {
        *ptr++ = 0;
    }
}

void func_us_801AB16C(s32* arg0, s32* arg1) {
    s32 bound = 13;
    s32 i;

    for(i = 0; i < bound; i++) {
        *arg1++ = *arg0++;
    }
}

INCLUDE_ASM("st/rnz1/nonmatchings/unk_2B148", func_us_801AB198);

INCLUDE_ASM("st/rnz1/nonmatchings/unk_2B148", func_us_801AB380);

INCLUDE_ASM("st/rnz1/nonmatchings/unk_2B148", func_us_801AB768);

INCLUDE_ASM("st/rnz1/nonmatchings/unk_2B148", func_us_801ABA38);

INCLUDE_ASM("st/rnz1/nonmatchings/unk_2B148", func_us_801ABB58);

void RNZ1_Unused801ABDC0(void) {}

INCLUDE_ASM("st/rnz1/nonmatchings/unk_2B148", func_us_801ABDC8);

INCLUDE_RODATA("st/rnz1/nonmatchings/unk_2B148", D_us_801A6050);

INCLUDE_ASM("st/rnz1/nonmatchings/unk_2B148", func_us_801ABDE4);
