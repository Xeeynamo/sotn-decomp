#include "common.h"
#include "psxsdk/libspu.h"
#include "libspu_internal.h"

void SpuSetVoiceAttr(SpuVoiceAttr* arg) { _SpuSetVoiceAttr(arg, 0, 0x17, 0); }

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libspu/s_sva", _SpuSetVoiceAttr);
