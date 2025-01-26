#include "common.h"
#include <psxsdk/libapi.h>
#include <psxsdk/libc.h>

void ChangeClearRCnt(s32, s32);

extern volatile s32 Vcount;
static volatile s32* D_8002C2A8 = (s32*)0x1F801814;
static volatile s32* D_8002C2AC = (s32*)0x1F801110;
static volatile s32 Hcount = 0;
static volatile s32 D_8002C2B4 = 0;

s32 VSync(s32 arg0) {
    s32 temp_s0;
    s32 ret;
    s32 var_a1;
    s32 var_v0;

    temp_s0 = *D_8002C2A8;

    ret = (*D_8002C2AC - Hcount) & 0xFFFF;
    if (arg0 < 0) {
        return Vcount;
    }
    if (arg0 == 1) {
        return ret;
    }
    if (arg0 > 0) {
        var_v0 = 1;
        var_v0 = (D_8002C2B4 - var_v0) + arg0;
    } else {
        var_v0 = D_8002C2B4;
    }
    var_a1 = 0;
    if (arg0 > 0) {
        var_a1 = arg0 - 1;
    }
    v_wait(var_v0, var_a1);
    temp_s0 = *D_8002C2A8;
    v_wait(Vcount + 1, 1);
    if ((temp_s0 & 0x80000) && ((temp_s0 ^ *D_8002C2A8) >= 0)) {
        do {

        } while (!((temp_s0 ^ *D_8002C2A8) & 0x80000000));
    }
    D_8002C2B4 = Vcount;
    Hcount = *D_8002C2AC;
    return ret;
}

void v_wait(s32 arg0, s32 arg1) {
    volatile s32 sp10[2];

    sp10[0] = arg1 << 0xF;
    while (Vcount < arg0) {
        if (sp10[0]-- == 0) {
            puts("VSync: timeout\n");
            ChangeClearPAD(0);
            ChangeClearRCnt(3, 0);
            return;
        }
    }
}
