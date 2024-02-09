#include "libsnd_i.h"

void SsVabClose(s16 vabid) {
    if ((vabid >= 0 && vabid < 0x10) && (_svm_vab_used[vabid] == 1)) {
        SpuFree(_svm_vab_start[vabid]);
        _svm_vab_used[vabid] = 0;
        _svm_vab_count -= 1;
    }
}

s16 SsVabOpen(u8* addr, VabHdr* vab_header) {
    s16 vab_id;

    vab_id = SsVabOpenHead(addr, -1);
    if (vab_id != -1) {
        vab_id = SsVabTransBody(_svm_brr_start_addr[vab_id], vab_id);
    }
    return vab_id;
}
