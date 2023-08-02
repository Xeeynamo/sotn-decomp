#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libsnd/ssstart", _SsStart);

void _SsStart(s32);

void SsStart(void) { _SsStart(1); }

void SsStart2(void) { _SsStart(0); }

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libsnd/ssstart", _SsTrapIntrVSync);

INCLUDE_ASM(
    "asm/us/main/nonmatchings/psxsdk/libsnd/ssstart", _SsSeqCalledTbyT_1per2);
