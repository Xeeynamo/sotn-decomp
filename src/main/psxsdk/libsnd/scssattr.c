// SPDX-License-Identifier: MIT
#include "libsnd_i.h"

void SsSetSerialAttr(char arg0, char arg1, char arg2) {
    SpuCommonAttr attr;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_v1;

    if (!(arg0 & 0xFF)) {
        temp_v1 = arg1 & 0xFF;
        if (temp_v1 == 0) {
            attr.mask = 0x200;
            attr.cd.mix = arg2 & 0xFF;
        }
        if (temp_v1 == 1) {
            attr.mask = 0x100;
            attr.cd.reverb = arg2 & 0xFF;
        }
    }
    temp_a0 = arg0 & 0xFF;
    temp_a1 = arg1 & 0xFF;
    if (temp_a0 == 1) {
        if (temp_a1 == 0) {
            attr.mask = 0x2000;
            attr.ext.mix = arg2 & 0xFF;
        }
        if (temp_a1 == temp_a0) {
            attr.mask = 0x1000;
            attr.ext.reverb = arg2 & 0xFF;
        }
    }
    SpuSetCommonAttr(&attr);
}
