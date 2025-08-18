// SPDX-License-Identifier: MIT
#include "common.h"
#include "kernel.h"

void GsInitVcount(void) {
    SetRCnt(RCntCNT1, 0xFFFFU, RCntMdNOINTR);
    StartRCnt(RCntCNT1);
}
