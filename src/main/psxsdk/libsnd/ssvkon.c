#include "common.h"
#include "libsnd_internal.h"

s32 SsVoKeyOn(s32 vab_pro, s32 pitch, u16 volL, u16 volR) {
    SpuVmSeKeyOn(
        (vab_pro << 8) >> 0x10, vab_pro, pitch >> 8, pitch, volL, volR);
}
