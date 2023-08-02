#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libsnd/ssplay", Snd_SetPlayMode);

void Snd_SetPlayMode(s16, s16, u8, s16);

void SsSeqPlay(s16 seq_access_num, s8 play_mode, s16 l_count) {
    Snd_SetPlayMode(seq_access_num, 0, play_mode, l_count);
}

void SsSepPlay(s16 sep_access_num, s16 seq_num, s8 play_mode, s16 l_count) {
    Snd_SetPlayMode(sep_access_num, seq_num, play_mode, l_count);
}
