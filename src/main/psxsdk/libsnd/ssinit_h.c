#include "common.h"
#include "libsnd_i.h"

void SsInitHot(void) {
    ResetCallback();
    SpuInit();
    _SsInit();
}
