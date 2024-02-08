#include "common.h"
#include "libsnd_i.h"

s32 SpuVmSeqKeyOff(s32, s32, struct SeqStruct*, s32);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/stop", _SsSndStop);

void _SsSndStop(s16, s16);

void SsSeqStop(s16 arg0) { _SsSndStop(arg0, 0); }

void SsSepStop(s16 arg0, s16 arg1) { _SsSndStop(arg0, arg1); }
