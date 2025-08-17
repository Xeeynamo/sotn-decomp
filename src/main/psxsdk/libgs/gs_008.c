// SPDX-License-Identifier: MIT
#include "common.h"
#include "kernel.h"

long GsGetVcount() { return GetRCnt(RCntCNT1); }
