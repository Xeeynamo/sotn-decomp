#include <common.h>
#include <psxsdk/libspu.h>
#include <psxsdk/libsnd.h>
#include "../log.h"

void SpuSetVoiceAttr(SpuVoiceAttr* arg) { DEBUGF("SpuSetVoiceAttr"); }

long SpuMallocWithStartAddr(unsigned long addr, long size) {
    DEBUGF("not implemented");
}

SpuIRQCallbackProc SpuSetIRQCallback(SpuIRQCallbackProc in) {
    DEBUGF("not implemented");
    return in;
}

long SpuSetTransferMode(long mode) {
    DEBUGF("not implemented");
    return 0;
}

long SpuClearReverbWorkArea(long rev_mode) {
    DEBUGF("not implemented");
    return 0;
}

void SpuSetKey(long on_off, unsigned long voice_bit) {
    DEBUGF("on_off %d voice_bit %08X", on_off, voice_bit);
}
