#include <common.h>
#include <psxsdk/libspu.h>
#include <log.h>

void SpuSetVoiceAttr(SpuVoiceAttr* arg) { DEBUGF("SpuSetVoiceAttr"); }

long SpuMallocWithStartAddr(unsigned long addr, long size) { NOT_IMPLEMENTED; }

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
