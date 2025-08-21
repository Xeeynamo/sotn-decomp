// SPDX-License-Identifier: MIT
#include "common.h"
#include <psxsdk/libcd.h>

extern StHEADER* D_800987C8;
extern u_long D_80098894;

void StSetRing(u_long* ring_addr, u_long ring_size) {
    D_800987C8 = (StHEADER*)ring_addr;
    D_80098894 = ring_size;
    StClearRing();
}
