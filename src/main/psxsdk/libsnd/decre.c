#include "common.h"
#include "libsnd_i.h"

struct StackStruct {
    u16 voll;
    u16 volr;
    u32 unk1;
    u32 unk2;
};

void _SsSndDecrescendo(s16 arg0, s16 arg1) {
    struct StackStruct stack;
    s32 temp_a2;
    s32 temp;
    struct SeqStruct* score;

    score = &_ss_score[arg0][arg1];
    temp_a2 = score->unk42;
    temp = temp_a2;
    score->unk98--;

    if (temp_a2 > 0) {
        if ((score->unk98 % temp_a2) == 0) {
            score->unk40--;
            if ((score->unk40) > 0) {
                SpuVmGetSeqVol(arg0 | (arg1 << 8), &stack.voll, &stack.volr);
                if (((stack.voll - score->unk40) > 0) &&
                    ((stack.volr - score->unk40) > 0) && stack.voll != 1) {
                    SpuVmSetSeqVol(
                        arg0 | (arg1 << 8), stack.voll - 1, stack.volr - 1, 0);
                } else {
                    SpuVmSetSeqVol((arg0 | (arg1 << 8)), 1, 1, 0);
                }
            } else {
                _ss_score[arg0][arg1].unk90 &= ~0x20;
            }

        } else {
            goto out;
        }
    } else {
        score->unk40 += temp;
        if ((score->unk40) > 0) {
            SpuVmGetSeqVol(arg0 | (arg1 << 8), &stack.voll, &stack.volr);
            if ((score->unk3E >=
                 ((score->unk94 - score->unk98) * -score->unk42)) &&
                ((-score->unk42 < stack.voll) != 0)) {
                SpuVmSetSeqVol(arg0 | (arg1 << 8), stack.voll + score->unk42,
                               stack.volr + score->unk42, 0);
            } else {
                SpuVmSetSeqVol((arg0 | (arg1 << 8)), 1, 1, 0);
            }
        } else {
            _ss_score[arg0][arg1].unk90 &= ~0x20;
        }
    }

    if ((score->unk98 == 0) || (score->unk40 == 0)) {
        _ss_score[arg0][arg1].unk90 &= ~0x20;
    }
out:
    SpuVmGetSeqVol((arg0 | (arg1 << 8)), &score->unk78, &score->unk7A);
}
