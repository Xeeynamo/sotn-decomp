#include "common.h"
#include "kernel.h"

void GsClearVcount() { return ResetRCnt(RCntCNT1); }
