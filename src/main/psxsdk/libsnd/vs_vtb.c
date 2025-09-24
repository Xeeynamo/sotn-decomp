// SPDX-License-Identifier: MIT
#include "libsnd_i.h"

s16 SsVabTransBody(u8* addr, s16 vabid) {
    s32 temp_s0;

    if (vabid >= 0 && vabid <= 0x10) {
        if (_svm_vab_used[vabid] == 2) {
            temp_s0 = _svm_vab_start[vabid];
            SpuSetTransferMode(0);
            SpuSetTransferStartAddr(temp_s0);
            SpuWrite(addr, _svm_vab_total[vabid]);
            _svm_vab_used[vabid] = 1;
            return vabid;
        }
    }
    _spu_setInTransfer(0);
    return -1;
}
