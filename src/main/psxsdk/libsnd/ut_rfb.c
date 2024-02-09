#include "libsnd_i.h"

void SsUtSetReverbFeedback(s16 feedback) {
    _svm_rattr.mask = SPU_REV_FEEDBACK;
    _svm_rattr.feedback = feedback;
    SpuSetReverbModeParam(&_svm_rattr);
}
