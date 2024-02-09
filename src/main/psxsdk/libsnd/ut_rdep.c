#include "libsnd_i.h"

void SsUtSetReverbDepth(s16 ldepth, s16 rdepth) {
    _svm_rattr.mask = 6;
    _svm_rattr.depth.left = (ldepth * 0x7FFF) / 127;
    _svm_rattr.depth.right = (rdepth * 0x7FFF) / 127;
    SpuSetReverbModeParam(&_svm_rattr);
}
