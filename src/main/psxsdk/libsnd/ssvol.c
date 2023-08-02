#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libsnd/ssvol", _SsSndSetVol);

void SpuVmSetSeqVol(s16, u16, u16, s32);

void SsSeqSetVol(s16 arg0, s32 arg1, s32 arg2) {
    SpuVmSetSeqVol(arg0, arg1, arg2, 0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libsnd/ssvol", SsSepSetVol);

s32 SpuVmGetSeqVol(s16, s16*, s16*);

void SsSeqGetVol(s16 access_num, s16 seq_num, s16* voll, s16* volr) {
    SpuVmGetSeqVol(access_num | (seq_num << 8), voll, volr);
}
