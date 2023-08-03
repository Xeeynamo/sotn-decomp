#include "common.h"

void _spu_setInTransfer(s32);
extern u8 svm_vab_used[];

s16 SsVabFakeBody(s16 vabid) {
    if ((vabid < 0x11U) && (svm_vab_used[vabid] == 2)) {
        _spu_setInTransfer(0);
        svm_vab_used[vabid] = 1;
        return vabid;
    }
    return -1;
}
