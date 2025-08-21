// SPDX-License-Identifier: MIT
#include "common.h"
#include "registers.h"

extern u32 D_8006BAF4;
extern u32 D_800987B8;
extern u32 D_800987C0;

void StSetMask(u_long mask, u_long start, u_long end) {
    D_800987C0 = mask;
    D_8006BAF4 = start;
    D_800987B8 = end;
}
