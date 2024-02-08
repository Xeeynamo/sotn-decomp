#include "libsnd_i.h"

void _SsSndPause(s16 arg0, s16 arg1) {
    struct SeqStruct* temp_s2;
    temp_s2 = &_ss_score[arg0][arg1];
    SpuVmSeqKeyOff(arg1 << 8 | arg0, arg1 << 8);
    temp_s2->unk2b = 0;
    _ss_score[arg0][arg1].unk90 &= ~2;
}
