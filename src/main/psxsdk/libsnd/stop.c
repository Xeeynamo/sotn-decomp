// SPDX-License-Identifier: MIT
#include "common.h"
#include "libsnd_i.h"

// seems to require wrong prototype
void SpuVmSeqKeyOff(s32 arg0);

void _SsSndStop(s16 arg0, s16 arg1) {
    struct SeqStruct* score = &_ss_score[arg0][arg1];
    int i;

    _ss_score[arg0][arg1].unk90 &= ~1;
    _ss_score[arg0][arg1].unk90 &= ~2;
    _ss_score[arg0][arg1].unk90 &= ~8;
    _ss_score[arg0][arg1].unk90 |= 4;
    SpuVmSeqKeyOff(arg1 << 8 | arg0);
    score->unk2b = 0;
    score->unk80 = 0;
    score->unk27 = 0;
    score->unk13 = 0;
    score->unk14 = 0;
    score->unk29 = 0;
    score->unk15 = 0;
    score->unk16 = 0;
    score->unk2a = 0;
    score->channel = 0;
    score->unk48 = 0;
    score->unk27 = 0;
    score->unk28 = 0;
    score->unk10 = 0;
    score->unk11 = 0;
    score->delta_value = score->unk7c;
    score->unk8c = score->unk84;
    score->unk70 = score->unk72;
    score->read_pos = score->next_sep_pos;
    score->loop_pos = score->next_sep_pos;
    for (i = 0; i < 16; i++) {
        score->programs[i] = i;
        score->panpot[i] = 0x40;
        score->vol[i] = 127;
    }

    score->unk78 = 0x7F;
    score->unk7A = 0x7F;
}

void SsSeqStop(s16 arg0) { _SsSndStop(arg0, 0); }

void SsSepStop(s16 arg0, s16 arg1) { _SsSndStop(arg0, arg1); }
