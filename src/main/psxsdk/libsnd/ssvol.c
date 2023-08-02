#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libsnd/ssvol", _SsSndSetVol);

void SpuVmSetSeqVol(s16, u16, u16, s32);

void SsSeqSetVol(s16 arg0, s32 arg1, s32 arg2) {
    SpuVmSetSeqVol(arg0, arg1, arg2, 0);
}

void SsSepSetVol(s16 sep_access_num, s16 seq_num, s16 voll, s16 volr) {
    SpuVmSetSeqVol(
        sep_access_num | (seq_num << 8), voll & 0xFFFF, volr & 0xFFFF, 0);
}

s32 SpuVmGetSeqVol(s16, s16*, s16*);

void SsSeqGetVol(s16 access_num, s16 seq_num, s16* voll, s16* volr) {
    SpuVmGetSeqVol(access_num | (seq_num << 8), voll, volr);
}
