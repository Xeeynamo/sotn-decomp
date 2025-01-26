#include "common.h"
#include <psxsdk/libapi.h>
#include <psxsdk/libc.h>

void ChangeClearRCnt(s32, s32);

extern volatile s32 Vcount;
static volatile s32* D_8002C2A8 = (s32*)0x1F801814;
static volatile s32* D_8002C2AC = (s32*)0x1F801110;
static volatile s32 Hcount = 0;
static volatile s32 prevVcount = 0;

s32 VSync(s32 mode) {
    s32 temp_s0;
    s32 ret;
    s32 max;
    s32 waitCount;

    temp_s0 = *D_8002C2A8;

    ret = (*D_8002C2AC - Hcount) & 0xFFFF;
    if (mode < 0) {
        return Vcount;
    }
    if (mode == 1) {
        return ret;
    }
    if (mode > 0) {
        waitCount = 1;
        waitCount = (prevVcount - waitCount) + mode;
    } else {
        waitCount = prevVcount;
    }
    max = 0;
    if (mode > 0) {
        max = mode - 1;
    }
    v_wait(waitCount, max);
    temp_s0 = *D_8002C2A8;
    v_wait(Vcount + 1, 1);
    if ((temp_s0 & 0x80000) && ((temp_s0 ^ *D_8002C2A8) >= 0)) {
        do {

        } while (!((temp_s0 ^ *D_8002C2A8) & 0x80000000));
    }
    prevVcount = Vcount;
    Hcount = *D_8002C2AC;
    return ret;
}

void v_wait(s32 count, s32 max) {
    volatile s32 timeout[2];

    timeout[0] = max << 0xF;
    while (Vcount < count) {
        if (timeout[0]-- == 0) {
            puts("VSync: timeout\n");
            ChangeClearPAD(0);
            ChangeClearRCnt(3, 0);
            return;
        }
    }
}
