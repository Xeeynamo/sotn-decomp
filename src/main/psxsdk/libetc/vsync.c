#include "common.h"
#include <psxsdk/libapi.h>
#include <psxsdk/libc.h>

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/vsync", VSync);

void ChangeClearRCnt(s32, s32);
extern volatile s32 Vcount;

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
