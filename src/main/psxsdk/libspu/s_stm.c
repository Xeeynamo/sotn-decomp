#include "common.h"
#include "libspu_internal.h"

long SpuSetTransferMode(long mode) {
    s32 transMode;

    switch (mode) {
    case SPU_TRANSFER_BY_DMA:
        transMode = 0;
        break;
    case SPU_TRANSFER_BY_IO:
        transMode = 1;
        break;
    default:
        transMode = 0;
    }
    D_8003309C = mode;
    _spu_transMode = transMode;
    return transMode;
}
