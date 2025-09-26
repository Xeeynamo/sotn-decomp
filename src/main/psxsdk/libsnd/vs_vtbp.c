// SPDX-License-Identifier: MIT
#include "common.h"
#include "libsnd_i.h"

static s32 D_80032F08 = 0;
static s16 D_80032F0C = -1;

short SsVabTransBodyPartly(
    unsigned char* addr, unsigned long bufsize, short vabid) {
    u32 new_bufsize;

    if (vabid < 0 || vabid > 0x10 || _svm_vab_used[vabid] != 2) {
        _spu_setInTransfer(0);
        return -1;
    }
    if (D_80032F08 == 0) {
        D_80032F0C = vabid;
        D_80032F08 = _svm_vab_total[vabid];
        SpuSetTransferMode(0);
        SpuSetTransferStartAddr(_svm_vab_start[vabid]);
    }
    if (D_80032F0C != vabid) {
        _spu_setInTransfer(0);
        return -1;
    }

    new_bufsize = (D_80032F08 < bufsize) ? D_80032F08 : bufsize;

    _spu_setInTransfer(1);
    SpuWritePartly(addr, new_bufsize);

    D_80032F08 -= new_bufsize;
    if (D_80032F08 != 0) {
        return -2;
    }
    D_80032F0C = -1;
    D_80032F08 = 0;
    _svm_vab_used[vabid] = 1;
    return vabid;
}
