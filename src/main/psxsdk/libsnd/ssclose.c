#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libsnd/ssclose", _SsClose);

void _SsClose(s16);

void SsSeqClose(short seq_access_num) { _SsClose(seq_access_num); }

void SsSepClose(s16 sep_access_num) { _SsClose(sep_access_num); }
