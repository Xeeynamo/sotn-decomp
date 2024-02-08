#include "libsnd_i.h"

void _SsSndReplay(s16 arg0, s16 arg1) {
    _ss_score[arg0][arg1].unk2b = 1;
    _ss_score[arg0][arg1].unk90 &= ~8;
}
