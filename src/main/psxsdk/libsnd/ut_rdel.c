#include "libsnd_i.h"

void SsUtSetReverbDelay(short delay) {
    _svm_rattr.mask = SPU_REV_DELAYTIME;
    _svm_rattr.delay = delay;
    SpuSetReverbModeParam(&_svm_rattr);
}
