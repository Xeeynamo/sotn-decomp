#include "common.h"
#include "libsnd_internal.h"

s16 SsVabTransCompleted(s16 immediateFlag) {
    return SpuIsTransferCompleted(immediateFlag);
}
