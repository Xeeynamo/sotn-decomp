#include "common.h"

extern s16 _svm_damper;

void SpuVmDamperOff(void) { _svm_damper = 0; }
