#include "common.h"
#include "libspu_internal.h"

u32 SpuRead(u8* arg0, u32 size) {
    if (size > 0x7F000U) {
        size = 0x7F000;
    }
    _spu_read(arg0, size);
    if (_spu_transferCallback == 0) {
        _spu_inTransfer = 0;
    }
    return size;
}
