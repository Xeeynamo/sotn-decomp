// SPDX-License-Identifier: MIT
#include "libsnd_i.h"

void SsSetSerialVol(char s_num, short voll, short volr) {
    SpuCommonAttr attr;
    if (s_num == 0) {
        attr.mask = 0xC0;
        if (voll > 127) {
            voll = 127;
        }
        if (volr > 127) {
            volr = 127;
        }
        attr.cd.volume.left = voll * 258;
        attr.cd.volume.right = volr * 258;
    }
    if (s_num == 1) {
        attr.mask = 0xC00;
        if (voll > 127) {
            voll = 127;
        }
        if (volr > 127) {
            volr = 127;
        }
        attr.ext.volume.left = voll * 258;
        attr.ext.volume.right = volr * 258;
    }
    SpuSetCommonAttr(&attr);
}
