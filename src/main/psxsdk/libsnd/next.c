// SPDX-License-Identifier: MIT
#include "libsnd_i.h"

void _SsSndNextSep(s16 arg0, s16 arg1) {
    struct SeqStruct* score = &_ss_score[arg0][arg1];
    score->unk46 = 1;
    score->unk48 = 0;
    _ss_score[arg0][arg1].unk90 &= ~0x100;
    _ss_score[arg0][arg1].unk90 &= ~0x8;
    _ss_score[arg0][arg1].unk90 &= ~0x2;
    _ss_score[arg0][arg1].unk90 &= ~0x4;
    _ss_score[arg0][arg1].unk90 &= ~0x200;
    score->unk2b = 1;
    score->read_pos = score->next_sep_pos;
    _ss_score[arg0][arg1].unk90 |= 1;
}
