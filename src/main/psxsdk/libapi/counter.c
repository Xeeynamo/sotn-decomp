#include "common.h"

typedef struct {
    u16 rootCounter;
    s16 unk2;
    s32 mode;
    s32 target;
    s32 padding;
} Counter;

// https://psx-spx.consoledev.net/timers/

extern volatile s32* D_8002D3B4;     // _interrupt_status_register
extern volatile Counter* D_8002D3B8; // _counters
extern volatile s32 D_8002D3BC[4];   // _interrupt_status_masks

INCLUDE_ASM("main/nonmatchings/psxsdk/libapi/counter", SetRCnt);

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
