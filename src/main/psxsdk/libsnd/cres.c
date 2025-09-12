// SPDX-License-Identifier: MIT
#include "common.h"
#include "libsnd_i.h"

void _SsSndCrescendo(s16 arg0, s16 arg1) {
    struct SeqStruct* score = &_ss_score[arg0][arg1];
    u16 voll, volr;

    score->unk98--;

    if (score->unk42 > 0) {
        if ((score->unk98 % score->unk42) == 0) {
            score->unk40--;
            if (score->unk40 >= 0) {
                SpuVmGetSeqVol(arg0 | (arg1 << 8), &voll, &volr);
                if ((voll + 1) <= (voll + score->unk40)) {
                    SpuVmSetSeqVol(arg0 | (arg1 << 8), voll + 1, volr + 1, 0);
                }
            } else {
                SpuVmSetSeqVol(arg0 | (arg1 << 8), 0x7F, 0x7F, 0);
                _ss_score[arg0][arg1].unk90 &= ~0x10;
            }
            if ((score->unk98 == 0) || (score->unk40 == 0)) {
                _ss_score[arg0][arg1].unk90 &= ~0x10;
            }
        }
    } else if (score->unk42 < 0) {
        score->unk40 += score->unk42;
        if (score->unk40 >= 0) {
            SpuVmGetSeqVol(arg0 | (arg1 << 8), &voll, &volr);
            if (((voll - score->unk42) >= 0x7F) &&
                ((volr - score->unk42) >= 0x7F)) {
                SpuVmSetSeqVol(arg0 | (arg1 << 8), 0x7F, 0x7F, 0);
            }
            if (((score->unk94 - score->unk98) * -score->unk42) <
                score->unk3E) {
                SpuVmSetSeqVol(arg0 | (arg1 << 8), voll - score->unk42,
                               volr - score->unk42, 0);
            }
        } else {
            SpuVmSetSeqVol(arg0 | (arg1 << 8), 0x7F, 0x7F, 0);
            _ss_score[arg0][arg1].unk90 &= ~0x10;
        }
        if ((score->unk98 == 0) || (score->unk40 == 0)) {
            _ss_score[arg0][arg1].unk90 &= ~0x10;
        }
    }
    SpuVmGetSeqVol(arg0 | (arg1 << 8), &score->unk78, &score->unk7A);
}
