#include "common.h"
#include "libsnd_internal.h"

void _SsUtResolveADSR(s32 arg0, u32 arg1, struct Unk* arg2) {
    u32 temp_v1;

    arg2->unkA = arg0 & 0x8000;
    arg2->unkC = arg1 & 0x8000;
    arg2->unk10 = arg1 & 0x4000;
    temp_v1 = arg0 & 0xFFFF;
    arg2->unkE = arg1 & 0x20;
    arg2->unk0 = (temp_v1 >> 8) & 0x7F;
    arg2->unk2 = (temp_v1 >> 4) & 0xF;
    arg2->unk4 = arg0 & 0xF;
    arg2->unk6 = (arg1 >> 6) & 0x7F;
    arg2->unk8 = arg1 & 0x1F;
}

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libsnd/ccadsr", _SsUtBuildADSR);
