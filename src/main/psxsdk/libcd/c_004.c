// SPDX-License-Identifier: MIT
#include "common.h"
#include "registers.h"
#include <psxsdk/libcd.h>

extern StHEADER* D_800987C8;
extern s32 D_8003C768;
extern void (*D_8003C8BC)(void);
extern s32 D_800730D4;
extern s32 D_80097954;
extern s32 D_80097958;

static CdlLOC fp_2;
static s32 D_8003B688;

void data_ready_callback(void) {
    StHEADER* ptr = &D_800987C8[D_80097958];
    do {
    } while (0);

    ptr->id = 2;
    fp_2 = ptr->loc;
    D_8003B688 = ptr->frameCount;
    D_80097958 = D_80097954;
    if (D_8003C8BC != NULL) {
        D_8003C8BC();
    }
    D_800730D4 = 0;
}

s32 StGetBackloc(CdlLOC* loc) {
    if (D_8003C768) {
        return -1;
    }
    CdIntToPos(CdPosToInt(&fp_2) + 1, loc);
    return D_8003B688;
}
