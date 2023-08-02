#define INCLUDE_ASM_NEW
#include "common.h"

s16 SsVabOpenHeadWithMode(u8*, s16, s32, u32);

s16 SsVabOpenHead(u8* arg1, s16 vabid) {
    return SsVabOpenHeadWithMode(arg1, vabid, 0, 0);
}

s16 SsVabOpenHeadSticky(u8* addr, s16 vabid, u32 sbaddr) {
    return SsVabOpenHeadWithMode(addr, vabid, 1, sbaddr);
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vs_vh", SsVabFakeHead);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vs_vh", SsVabOpenHeadWithMode);
