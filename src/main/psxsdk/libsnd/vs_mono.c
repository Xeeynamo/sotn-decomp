#include "libsnd_i.h"

void SsSetMono(void) { _svm_stereo_mono = 1; }

void SsSetStereo(void) { _svm_stereo_mono = 0; }
