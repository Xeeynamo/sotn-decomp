#include "common.h"
#include "libsnd_internal.h"

s16 SsVabFakeBody(s16 vabid) {
    if ((vabid < 0x11U) && (svm_vab_used[vabid] == 2)) {
        _spu_setInTransfer(0);
        svm_vab_used[vabid] = 1;
        return vabid;
    }
    return -1;
}
