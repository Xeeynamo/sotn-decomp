#include "common.h"
#include "libsnd_internal.h"

s16 SsVabTransBodyPartly(u8* addr, u32 bufsize, s16 vabid) {
    s16 new_vabid;
    s32 buff_diff;
    u32 new_bufsize;
    if (vabid < 0 || vabid > 16 || _svm_vab_used[vabid] != 2) {
        _spu_setInTransfer(0);
        return -1;
    }
    if (D_80032F08 == 0) {
        D_80032F0C = vabid;
        D_80032F08 = _svm_vab_total[vabid];
        SpuSetTransferMode(0);
        SpuSetTransferStartAddr(_svm_vab_start[vabid]);
    }
    new_vabid = D_80032F0C;
    if (new_vabid != vabid) {
        _spu_setInTransfer(0);
        return -1;
    }
    new_bufsize = bufsize;
    if (D_80032F08 < new_bufsize) {
        new_bufsize = D_80032F08;
    }
    _spu_setInTransfer(1);
    SpuWritePartly(addr, new_bufsize);
    buff_diff = D_80032F08 - new_bufsize;
    D_80032F08 = buff_diff;
    if (buff_diff == 0) {
        D_80032F0C = -1;
        D_80032F08 = 0;
        _svm_vab_used[new_vabid] = 1;
        return new_vabid;
    }
    return -2;
}
