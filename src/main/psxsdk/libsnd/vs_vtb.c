#include "common.h"
#include "libsnd_internal.h"

s16 SsVabTransBody(u8* addr, s16 vabid) {
    s32 temp_s0;

    if (vabid < 0x11U) {
        if (svm_vab_used[vabid] == 2) {
            temp_s0 = D_80098810[vabid];
            func_8002ABF4(0);
            func_8002ABB8(temp_s0);
            func_8002AB58(addr, D_800987CC[vabid]);
            svm_vab_used[vabid] = 1;
            return vabid;
        }
    }
    _spu_setInTransfer(0);
    return -1;
}
