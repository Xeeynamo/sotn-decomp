// SPDX-License-Identifier: MIT
#include "common.h"
#include "registers.h"

extern s32 D_8003C0FC;
extern s16 D_8003C75C;
extern s32 D_8003C764;
extern void (*D_8003C8BC)();
extern void (*D_8003C8C0)();
extern s32 D_8006BAF0;
extern s32 D_80072BCC;
extern s32 D_800987A8;

void StSetStream(u_long mode, u_long start_frame, u_long end_frame, void (*func1)(), void (*func2)()) {
    StSetMask(1U, start_frame, end_frame);
    D_800987A8 = 0;
    D_8003C8BC = func1;
    D_8003C764 = mode & 1;
    D_80072BCC = 0;
    D_8006BAF0 = 0;
    D_8003C75C = 0;
    D_8003C0FC = 0;
    D_8003C8C0 = func2;
}

