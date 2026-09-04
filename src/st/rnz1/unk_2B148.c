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

typedef struct{
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s16 unkC;
    s16 unkE;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
} batWingStruct;

void func_us_801AB198(batWingStruct* arg0) {
    s32 var_s2;
    s32 var_s1;
    s32 var_s0;

    var_s2 = arg0->unk8 * 0x50 / 0x100;
    var_s1 = arg0->unk0;
    arg0->unk4 = (var_s2 * rcos(arg0->unkE) / 0x1000) + (((arg0->unk18 * rcos(arg0->unk28 / 0x100)) / 0x1000) * 0x3E) / 0x100;
    var_s0 = var_s1 - arg0->unk4;
    arg0->unk8 += var_s0;
    arg0->unk10 += arg0->unk8;
    var_s2 = (arg0->unk1C + arg0->unk8) * 0x90 / 0x100;
    var_s1 = arg0->unk14;
    arg0->unk18 = var_s2 * rcos(arg0->unk24) / 0x1000;
    var_s0 = var_s1 - arg0->unk18;
    arg0->unk1C += var_s0;
    arg0->unk28 += arg0->unk1C;
    if (arg0->unk10 > FIX(3.5)) {
        arg0->unk10 = FIX(3.5);
        arg0->unk8 = 0;
    }
    if (arg0->unk10 < FIX(-2.5)) {
        arg0->unk10 = FIX(-2.5);
        arg0->unk8 = 0;
    }
    if ((arg0->unk28 - arg0->unk10) > FIX(5)) {
        arg0->unk28 = (arg0->unk10 + FIX(5));
        arg0->unk1C = 0;
    }
    if ((arg0->unk28 - arg0->unk10) < FIX(-2.5)) {
        arg0->unk28 = (arg0->unk10 + FIX(-2.5));
        arg0->unk1C = 0;
    }
}


INCLUDE_ASM("st/rnz1/nonmatchings/unk_2B148", func_us_801AB380);

INCLUDE_ASM("st/rnz1/nonmatchings/unk_2B148", func_us_801AB768);

INCLUDE_ASM("st/rnz1/nonmatchings/unk_2B148", func_us_801ABA38);

INCLUDE_ASM("st/rnz1/nonmatchings/unk_2B148", func_us_801ABB58);

void RNZ1_Unused801ABDC0(void) {}

INCLUDE_ASM("st/rnz1/nonmatchings/unk_2B148", func_us_801ABDC8);

INCLUDE_RODATA("st/rnz1/nonmatchings/unk_2B148", D_us_801A6050);

INCLUDE_ASM("st/rnz1/nonmatchings/unk_2B148", func_us_801ABDE4);
