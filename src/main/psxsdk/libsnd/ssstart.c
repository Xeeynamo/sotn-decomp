#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libsnd/ssstart", _SsStart);

void _SsStart(s32);

void SsStart(void) { _SsStart(1); }

void SsStart2(void) { _SsStart(0); }

extern void (*D_80032EF8)();
extern void (*D_80032EFC)();

void _SsTrapIntrVSync(void) {
    if (D_80032EFC != NULL) {
        D_80032EFC();
    }
    D_80032EF8();
}

INCLUDE_ASM(
    "asm/us/main/nonmatchings/psxsdk/libsnd/ssstart", _SsSeqCalledTbyT_1per2);
