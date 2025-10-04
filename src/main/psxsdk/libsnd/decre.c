// SPDX-License-Identifier: MIT
#include "common.h"
#include "libsnd_i.h"

void _SsSndDecrescendo(s16 arg0, s16 arg1) {
    struct SeqStruct* score = &_ss_score[arg0][arg1];
    u16 voll, volr;

    score->unk98--;

    if (score->unk42 > 0) {
        if ((score->unk98 % score->unk42) == 0) {
            score->unk40--;
            if (score->unk40 > 0) {
                SpuVmGetSeqVol(arg0 | (arg1 << 8), &voll, &volr);
                if (((voll - score->unk40) > 0) &&
                    ((volr - score->unk40) > 0) && voll != 1) {
                    SpuVmSetSeqVol(arg0 | (arg1 << 8), voll - 1, volr - 1, 0);
                } else {
                    SpuVmSetSeqVol(arg0 | (arg1 << 8), 1, 1, 0);
                }
            } else {
                _ss_score[arg0][arg1].unk90 &= ~0x20;
            }
            if ((score->unk98 == 0) || (score->unk40 == 0)) {
                _ss_score[arg0][arg1].unk90 &= ~0x20;
            }
        }
    } else {
        score->unk40 += score->unk42;
        if (score->unk40 > 0) {
            SpuVmGetSeqVol(arg0 | (arg1 << 8), &voll, &volr);
            if ((score->unk3E >=
                 ((score->unk94 - score->unk98) * -score->unk42)) &&
                -score->unk42 < voll) {
                SpuVmSetSeqVol(arg0 | (arg1 << 8), voll + score->unk42,
                               volr + score->unk42, 0);
            } else {
                SpuVmSetSeqVol(arg0 | (arg1 << 8), 1, 1, 0);
            }
        } else {
            _ss_score[arg0][arg1].unk90 &= ~0x20;
        }
        if ((score->unk98 == 0) || (score->unk40 == 0)) {
            _ss_score[arg0][arg1].unk90 &= ~0x20;
        }
    }
    SpuVmGetSeqVol(arg0 | (arg1 << 8), &score->unk78, &score->unk7A);
}
