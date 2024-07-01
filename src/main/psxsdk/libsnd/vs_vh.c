#include "common.h"
#include "libsnd_i.h"

s16 SsVabOpenHeadWithMode(u8* addr, s16 vabid, s16 arg2, u32 sbaddr);

s16 SsVabOpenHead(u8* arg1, s16 vabid) {
    return SsVabOpenHeadWithMode(arg1, vabid, 0, 0);
}

s16 SsVabOpenHeadSticky(u8* addr, s16 vabid, u32 sbaddr) {
    return SsVabOpenHeadWithMode(addr, vabid, 1, sbaddr);
}

s16 SsVabFakeHead(u8* addr, s16 vabid, u32 sbaddr) {
    return SsVabOpenHeadWithMode(addr, vabid, 1, sbaddr);
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vs_vh", SsVabOpenHeadWithMode);
