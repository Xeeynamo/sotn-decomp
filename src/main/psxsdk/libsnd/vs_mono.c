#include "common.h"
#include "libsnd_internal.h"

void SsSetMono(void) { _svm_stereo_mono = 1; }

void SsSetStereo(void) { _svm_stereo_mono = 0; }
