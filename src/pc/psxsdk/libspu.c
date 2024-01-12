#include <common.h>
#include <psxsdk/libspu.h>
#include <log.h>

#ifndef HAVE_SOUND_REV
void SpuSetVoiceAttr(SpuVoiceAttr* arg) { DEBUGF("SpuSetVoiceAttr"); }
#endif

long SpuMallocWithStartAddr(unsigned long addr, long size) {
    NOT_IMPLEMENTED;
    return -1;
}

SpuIRQCallbackProc SpuSetIRQCallback(SpuIRQCallbackProc in) {
    NOT_IMPLEMENTED;
    return in;
}

#ifndef HAVE_SOUND_REV
long SpuSetTransferMode(long mode) {
    NOT_IMPLEMENTED;
    return 0;
}
#endif

#ifndef HAVE_SOUND_REV
long SpuClearReverbWorkArea(long rev_mode) {
    NOT_IMPLEMENTED;
    return 0;
}
#endif

#ifndef HAVE_SOUND_REV
void SpuSetKey(long on_off, unsigned long voice_bit) {
    DEBUGF("on_off %d voice_bit %08X", on_off, voice_bit);
}
#endif
