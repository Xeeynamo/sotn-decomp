#include "common.h"

extern s16 _svm_stereo_mono;

void SsSetMono(void) { _svm_stereo_mono = 1; }

void SsSetStereo(void) { _svm_stereo_mono = 0; }
