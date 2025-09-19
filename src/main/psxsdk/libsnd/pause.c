// SPDX-License-Identifier: MIT
#include "libsnd_i.h"

void _SsSndPause(s16 arg0, s16 arg1) {
    struct SeqStruct* score = &_ss_score[arg0][arg1];
    SpuVmSeqKeyOff(arg1 << 8 | arg0, arg1 << 8);
    score->unk2b = 0;
    _ss_score[arg0][arg1].unk90 &= ~2;
}
