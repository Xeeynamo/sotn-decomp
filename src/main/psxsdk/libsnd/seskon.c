// SPDX-License-Identifier: MIT
#include "common.h"
#include "libsnd_i.h"

s32 SsVoKeyOn(s32 vab_pro, s32 pitch, u16 volL, u16 volR) {
    SpuVmSeKeyOn(
        vab_pro >> 8, vab_pro & 0xFF, pitch >> 8, pitch & 0xFF, volL, volR);
}
