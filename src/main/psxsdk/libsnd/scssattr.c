// SPDX-License-Identifier: MIT
#include "libsnd_i.h"

void SsSetSerialAttr(char arg0, char arg1, char arg2) {
    SpuCommonAttr attr;

    if (arg0 == 0 && arg1 == 0) {
        attr.mask = 0x200;
        attr.cd.mix = arg2;
    }
    if (arg0 == 0 && arg1 == 1) {
        attr.mask = 0x100;
        attr.cd.reverb = arg2;
    }
    if (arg0 == 1 && arg1 == 0) {
        attr.mask = 0x2000;
        attr.ext.mix = arg2;
    }
    if (arg0 == 1 && arg1 == 1) {
        attr.mask = 0x1000;
        attr.ext.reverb = arg2;
    }
    SpuSetCommonAttr(&attr);
}
