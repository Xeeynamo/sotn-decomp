#include "common.h"
#include "libsnd_internal.h"

void _SsUtResolveADSR(u16 arg0, u16 arg1, struct Unk* arg2) {
    arg2->unkA = arg0 & 0x8000;
    arg2->unkC = arg1 & 0x8000;
    arg2->unk10 = arg1 & 0x4000;
    arg2->unkE = arg1 & 0x20;
    arg2->unk0 = (arg0 >> 8) & 0x7F;
    arg2->unk2 = (arg0 >> 4) & 0xF;
    arg2->unk4 = arg0 & 0xF;
    arg2->unk6 = (arg1 >> 6) & 0x7F;
    arg2->unk8 = arg1 & 0x1F;
}

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libsnd/ccadsr", _SsUtBuildADSR);
