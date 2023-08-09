#include "common.h"
#include "libsnd_internal.h"

void SsSetMVol(short voll, short volr) {
    SpuCommonAttr attr;
    attr.mask = SPU_COMMON_MVOLL | SPU_COMMON_MVOLR;
    attr.mvol.left = 129 * voll;
    attr.mvol.right = 129 * volr;
    SpuSetCommonAttr(&attr);
}
