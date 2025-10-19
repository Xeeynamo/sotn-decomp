// SPDX-License-Identifier: MIT
#include "common.h"
#include "psxsdk/libcd.h"

void data_ready_callback();
extern s32 D_8003C768;

static inline void StCdInterrupt2(u_char intr, u_char* result) {
    StCdInterrupt();
}

int CdRead2(long mode) {
    u8 param = mode;
    CdControl(CdlSetmode, &param, NULL);
    if (mode & CdlModeStream) {
        if (mode & CdlModeSize1) {
            D_8003C768 = 0;
        } else {
            D_8003C768 = 1;
        }
        CdDataCallback(data_ready_callback);
        CdReadyCallback(StCdInterrupt2);
    }
    return CdControl(CdlReadS, NULL, NULL);
}
