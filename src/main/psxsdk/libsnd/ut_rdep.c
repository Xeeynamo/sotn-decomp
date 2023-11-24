#include "common.h"
#include "psxsdk/libspu.h"

extern s16 D_8003C750;
extern s16 D_8003C752;
extern SpuReverbAttr _svm_rattr;

void SsUtSetReverbDepth(s16 ldepth, s16 rdepth) {
    _svm_rattr.mask = 6;
    D_8003C750 = (ldepth * 0x7FFF) / 127;
    D_8003C752 = (rdepth * 0x7FFF) / 127;
    SpuSetReverbModeParam(&_svm_rattr);
}
