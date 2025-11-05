// SPDX-License-Identifier: MIT
#include "libsnd_i.h"

void SsUtSetReverbDepth(short ldepth, short rdepth) {
    _svm_rattr.mask = 6;
    _svm_rattr.depth.left = (ldepth * 0x7FFF) / 127;
    _svm_rattr.depth.right = (rdepth * 0x7FFF) / 127;
    SpuSetReverbModeParam(&_svm_rattr);
}
