#include "common.h"
#include "libsnd_internal.h"

void SsInitHot(void) {
    ResetCallback();
    SpuInit();
    _SsInit();
}
