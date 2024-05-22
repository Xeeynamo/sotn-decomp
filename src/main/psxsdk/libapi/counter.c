#include "common.h"

typedef struct {
    u16 rootCounter;
    s16 unk2;
    s16 mode;
    s16 : 16;
    s16 target;
    s32 : 32;
} Counter;

// https://psx-spx.consoledev.net/timers/

extern volatile s32* D_8002D3B4;     // _interrupt_status_register
extern volatile Counter* D_8002D3B8; // _counters
extern volatile s32 D_8002D3BC[4];   // _interrupt_status_masks

s32 SetRCnt(s32 spec, s16 target, s32 flags) {
    s32 i = spec & 0xFFFF;
    s32 final_mode = 0x48;
    if (i >= 3) {
        return 0;
    }
    D_8002D3B8[i].mode = 0;
    D_8002D3B8[i].target = target;

    if (i < 2u) {
        if (flags & 0x10) {
            final_mode = 0x49;
        }
        if (!(flags & 1)) {
            final_mode |= 0x100;
        }
    } else if (i == 2u) { // nb: `else` is redundant here
        if (!(flags & 1)) {
            final_mode = 0x248;
        }
    }
    if ((flags & 0x1000) != 0) {
        final_mode |= 0x10;
    }

    D_8002D3B8[i].mode = final_mode;
    return 1;
}

long GetRCnt(long spec) {
    s32 i = spec & 0xFFFF;
    if (i >= 3) {
        return 0;
    }
    return D_8002D3B8[i].rootCounter;
}

s32 StartRCnt(s32 spec) {
    s32 i = spec & 0xFFFF;
    long* mask = D_8002D3BC;
    D_8002D3B4[1] |= mask[i];
    return i < 3;
}

long StopRCnt(long spec) {
    s32 i = spec & 0xFFFF;
    long* mask = D_8002D3BC;
    D_8002D3B4[1] &= ~mask[i];
    return 1;
}

long ResetRCnt(long spec) {
    s32 i = spec & 0xFFFF;
    if (i >= 3) {
        return 0;
    }
    D_8002D3B8[i].rootCounter = 0;
    return 1;
}
