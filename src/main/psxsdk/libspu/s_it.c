#include "common.h"
#include "libspu_internal.h"

void _spu_setInTransfer(s32 arg0) {
    if (arg0 == 1) {
        _spu_inTransfer = 0;
        return;
    }
    _spu_inTransfer = 1;
}

s32 _spu_getInTransfer(void) { return _spu_inTransfer == 0; }
