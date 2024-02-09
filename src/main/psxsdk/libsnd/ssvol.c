#include "libsnd_i.h"

void _SsSndSetVol(s32 arg0, s32 arg1, u16 arg2, u16 arg3) {
    SpuVmSetSeqVol(arg0 | (arg1 << 8), arg2, arg3, 0);
}

void SsSeqSetVol(short arg0, short arg1, short arg2) {
    SpuVmSetSeqVol(arg0, arg1, arg2, 0);
}

void SsSepSetVol(s16 sep_access_num, s16 seq_num, s16 voll, s16 volr) {
    SpuVmSetSeqVol(
        sep_access_num | (seq_num << 8), voll & 0xFFFF, volr & 0xFFFF, 0);
}

void SsSeqGetVol(s16 access_num, s16 seq_num, s16* voll, s16* volr) {
    SpuVmGetSeqVol(access_num | (seq_num << 8), voll, volr);
}
