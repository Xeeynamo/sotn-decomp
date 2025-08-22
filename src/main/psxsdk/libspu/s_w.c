// SPDX-License-Identifier: MIT
#include "common.h"
#include "libspu_internal.h"

unsigned long SpuWrite(unsigned char* addr, unsigned long size) {
    if (size > 0x7F000) {
        size = 0x7F000;
    }
    _spu_write(addr, size);
    if (_spu_transferCallback == NULL) {
        _spu_inTransfer = 0;
    }
    return size;
}
