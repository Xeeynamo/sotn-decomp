#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libsnd/ut_rev", SsUtSetReverbType);

extern s16 D_8003C74C;

s16 SsUtGetReverbType(void) { return D_8003C74C; }
