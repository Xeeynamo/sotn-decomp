#include <common.h>
#include <psxsdk/libspu.h>
#include <log.h>

#ifndef WANT_LIBSND_LLE
void SpuSetVoiceAttr(SpuVoiceAttr* arg) { DEBUGF("SpuSetVoiceAttr"); }

long SpuMallocWithStartAddr(unsigned long addr, long size) {
    NOT_IMPLEMENTED;
    return -1;
}

SpuIRQCallbackProc SpuSetIRQCallback(SpuIRQCallbackProc in) {
    NOT_IMPLEMENTED;
    return in;
}

long SpuSetTransferMode(long mode) {
    NOT_IMPLEMENTED;
    return 0;
}

long SpuClearReverbWorkArea(long rev_mode) {
    NOT_IMPLEMENTED;
    return 0;
}

void SpuSetKey(long on_off, unsigned long voice_bit) {
    DEBUGF("on_off %d voice_bit %08X", on_off, voice_bit);
}

#else
long SpuMallocWithStartAddr(unsigned long addr, long size) {
    NOT_IMPLEMENTED;
    return -1;
}

void _SpuSetVoiceAttr(SpuVoiceAttr* arg, s32, s32, s32) {}
#endif
