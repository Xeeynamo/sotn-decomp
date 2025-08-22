// SPDX-License-Identifier: MIT
#include "common.h"
#include "libspu_internal.h"

u32 SpuWritePartly(u8* addr, u32 size) {
    s32 temp_s0;

    if (size > 0x7F000) {
        size = 0x7F000;
    }
    temp_s0 = _spu_tsa << _spu_mem_mode_plus;
    _spu_write(addr, size);
    _spu_tsa = _spu_FsetRXXa(-1, temp_s0 + size);
    if (_spu_transferCallback == NULL) {
        _spu_inTransfer = 0;
    }
    return size;
}
