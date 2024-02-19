#include "libsnd_i.h"

void _SsSndNextSep(s16 arg0, s16 arg1) {
    struct SeqStruct* temp_a0;
    temp_a0 = &_ss_score[arg0][arg1];
    _ss_score[arg0][arg1].unk46 = 1;
    temp_a0->unk48 = 0;
    _ss_score[arg0][arg1].unk90 &= ~0x100;
    _ss_score[arg0][arg1].unk90 &= ~0x8;
    _ss_score[arg0][arg1].unk90 &= ~0x2;
    _ss_score[arg0][arg1].unk90 &= ~0x4;
    _ss_score[arg0][arg1].unk90 &= ~0x200;
    temp_a0->unk2b = 1;
    temp_a0->read_pos = temp_a0->next_sep_pos;
    _ss_score[arg0][arg1].unk90 |= 1;
}
