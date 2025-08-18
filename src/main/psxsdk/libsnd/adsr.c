// SPDX-License-Identifier: MIT
#include "common.h"
#include "libsnd_i.h"

void _SsUtResolveADSR(u16 arg0, u16 arg1, struct Unk* arg2) {
    arg2->unkA = arg0 & 0x8000;
    arg2->unkC = arg1 & 0x8000;
    arg2->unk10 = arg1 & 0x4000;
    arg2->unkE = arg1 & 0x20;
    arg2->unk0 = (arg0 >> 8) & 0x7F;
    arg2->unk2 = (arg0 >> 4) & 0xF;
    arg2->unk4 = arg0 & 0xF;
    arg2->unk6 = (arg1 >> 6) & 0x7F;
    arg2->unk8 = arg1 & 0x1F;
}

void _SsUtBuildADSR(struct Unk* arg0, s16* arg1, s16* arg2) {
    u16 temp_t1;
    u16 var_v0;
    s16 temp4;
    s16 temp5;
    if (arg0->unkC != 0) {
        temp_t1 = 0x8000;
    } else {
        temp_t1 = 0;
    }

    if (arg0->unkA != 0) {
        var_v0 = 0x8000;
    } else {
        var_v0 = 0;
    }

    if (arg0->unk10 != 0) {
        temp_t1 = temp_t1 | 0x4000;
    }
    temp4 = var_v0 | ((arg0->unk0 << 8) & 0x7F00) | ((arg0->unk2 << 4) & 0xF0) |
            (arg0->unk4 & 0xF);
    temp5 = temp_t1 | ((arg0->unk6 << 6) & 0x1FC0) | (arg0->unk8 & 0x1F);
    temp_t1 = temp5;
    *arg1 = temp4;
    *arg2 = temp_t1;
}
