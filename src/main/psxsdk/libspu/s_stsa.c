#include "common.h"
#include "libspu_internal.h"

s32 SpuSetTransferStartAddr(s32 arg0) {
    _spu_tsa = _spu_FsetRXXa(-1, arg0);
    return arg0;
}
