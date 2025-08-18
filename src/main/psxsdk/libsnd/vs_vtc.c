// SPDX-License-Identifier: MIT
#include "libsnd_i.h"

s16 SsVabTransCompleted(s16 immediateFlag) {
    return SpuIsTransferCompleted(immediateFlag);
}
