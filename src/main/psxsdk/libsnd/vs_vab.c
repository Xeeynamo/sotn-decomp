#include "common.h"
#include "libsnd_internal.h"

void SsVabClose(s16 vabid) {
    if ((vabid < 0x10U) && (svm_vab_used[vabid] == 1)) {
        func_80028FF4(D_80098810[vabid]);
        svm_vab_used[vabid] = 0;
        _svm_vab_count -= 1;
    }
}

s16 SsVabOpen(u8* addr, VabHdr* vab_header) {
    s16 vab_id;

    vab_id = SsVabOpenHead(addr, -1);
    if (vab_id != -1) {
        vab_id = SsVabTransBody(D_80098854[vab_id], vab_id);
    }
    return vab_id;
}
