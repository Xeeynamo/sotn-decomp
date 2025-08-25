// SPDX-License-Identifier: MIT
#include "common.h"
#include "libsnd_i.h"

void _SsSndTempo(s16 arg0, s16 arg1) {
    struct SeqStruct* pSeq = &_ss_score[arg0][arg1];

    pSeq->unkA0--;

    if (pSeq->unk44 > 0) {
        if ((pSeq->unkA0 % pSeq->unk44) == 0) {
            if (pSeq->unk8c > pSeq->unkA4) {
                pSeq->unk8c--;
            } else if (pSeq->unk8c < pSeq->unkA4) {
                pSeq->unk8c++;
            }

            pSeq->unk70 =
                (pSeq->unk4a * pSeq->unk8c * 10) / (VBLANK_MINUS * 60);
            if (pSeq->unk70 <= 0) {
                pSeq->unk70 = 1;
            }
        }

        if ((pSeq->unkA0 == 0) || (pSeq->unk8c == pSeq->unkA4)) {
            _ss_score[arg0][arg1].unk90 &= ~0x40;
            _ss_score[arg0][arg1].unk90 &= ~0x80;
        }
    } else {
        if (pSeq->unk8c > pSeq->unkA4) {
            pSeq->unk8c += pSeq->unk44;
            if (pSeq->unk8c < pSeq->unkA4) {
                pSeq->unk8c = pSeq->unkA4;
            }
        } else if (pSeq->unk8c < pSeq->unkA4) {
            pSeq->unk8c -= pSeq->unk44;
            if (pSeq->unkA4 < pSeq->unk8c) {
                pSeq->unk8c = pSeq->unkA4;
            }
        }

        pSeq->unk70 = (pSeq->unk4a * pSeq->unk8c * 10) / (VBLANK_MINUS * 60);
        if (pSeq->unk70 <= 0) {
            pSeq->unk70 = 1;
        }
        if ((pSeq->unkA0 == 0) || (pSeq->unk8c == pSeq->unkA4)) {
            _ss_score[arg0][arg1].unk90 &= ~0x40;
            _ss_score[arg0][arg1].unk90 &= ~0x80;
        }
    }
}
