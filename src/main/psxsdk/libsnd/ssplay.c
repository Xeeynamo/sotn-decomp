#include "libsnd_i.h"

void Snd_SetPlayMode(s16 arg0, s16 arg1, u8 arg2, s16 arg3) {
    struct SeqStruct* temp_t2;
    temp_t2 = &_ss_score[arg0][arg1];
    _ss_score[arg0][arg1].unk90 &= ~0x200;
    _ss_score[arg0][arg1].unk90 &= ~4;
    temp_t2->unk46 = arg3;

    if (arg2 == 1) {
        _ss_score[arg0][arg1].unk90 |= 1;
        temp_t2->unk48 = 0;
        temp_t2->unk2b = 1;
        SpuVmSetSeqVol(arg0 | (arg1 << 8), temp_t2->unk74, temp_t2->unk76, 0);
    } else if (arg2 == 0) {
        _ss_score[arg0][arg1].unk90 |= 2;
    }
}

void SsSeqPlay(short seq_access_num, char play_mode, short l_count) {
    Snd_SetPlayMode(seq_access_num, 0, play_mode, l_count);
}

void SsSepPlay(
    short sep_access_num, short seq_num, char play_mode, short l_count) {
    Snd_SetPlayMode(sep_access_num, seq_num, play_mode, l_count);
}
