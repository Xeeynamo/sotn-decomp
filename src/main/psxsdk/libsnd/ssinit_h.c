// SPDX-License-Identifier: MIT
#include "libsnd_i.h"

void SsInitHot(void) {
    ResetCallback();
    SpuInit();
    _SsInit();
}
