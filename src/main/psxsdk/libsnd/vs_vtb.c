#include "common.h"
#include "libsnd_internal.h"

s16 SsVabTransBody(u8* addr, s16 vabid) {
    s32 temp_s0;

    if (vabid >= 0 && vabid < 0x11) {
        if (svm_vab_used[vabid] == 2) {
            temp_s0 = D_80098810[vabid];
            SpuSetTransferMode(0);
            SpuSetTransferStartAddr(temp_s0);
            SpuWrite(addr, D_800987CC[vabid]);
            svm_vab_used[vabid] = 1;
            return vabid;
        }
    }
    _spu_setInTransfer(0);
    return -1;
}
