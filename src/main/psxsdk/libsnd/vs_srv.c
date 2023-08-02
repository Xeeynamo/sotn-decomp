#include "common.h"

extern u8 spuVmMaxVoice;

u8 SsSetReservedVoice(u8 voices) {
    if ((voices >= 0x19) || (voices == 0)) {
        return -1;
    }
    spuVmMaxVoice = voices;
    return spuVmMaxVoice;
}
