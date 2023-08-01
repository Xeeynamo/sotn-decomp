#include "common.h"

void ResetCallback();
void SpuInit();
void _SsInit();

void SsInitHot(void) {
    ResetCallback();
    SpuInit();
    _SsInit();
}
