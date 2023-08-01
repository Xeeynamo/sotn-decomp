#include "common.h"

extern s16 _svm_damper;

void SpuVmDamperOn(void) { _svm_damper = 2; }
