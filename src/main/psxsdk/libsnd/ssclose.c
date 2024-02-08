#include "common.h"
#include "libsnd_i.h"

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/ssclose", _SsClose);

void SsSeqClose(short seq_access_num) { _SsClose(seq_access_num); }

void SsSepClose(s16 sep_access_num) { _SsClose(sep_access_num); }
