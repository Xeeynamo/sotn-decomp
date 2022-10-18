#include "common.h"
#include <main.h>
#include <psxsdk/libapi.h>
#include <psxsdk/libetc.h>

INCLUDE_ASM("asm/main/nonmatchings/5A38", PadInit);
// void PadInit(s32 arg0) {
//     D_80073080 = arg0;
//     D_8003925C = -1;
//     ResetCallback();
//     PAD_init(0x20000001, &D_8003925C);
//     ChangeClearPAD(0);
// }

INCLUDE_ASM("asm/main/nonmatchings/5A38", PadRead);

INCLUDE_ASM("asm/main/nonmatchings/5A38", PadStop);

INCLUDE_ASM("asm/main/nonmatchings/5A38", StopPAD);

INCLUDE_ASM("asm/main/nonmatchings/5A38", PAD_init);

INCLUDE_ASM("asm/main/nonmatchings/5A38", PAD_dr);

INCLUDE_ASM("asm/main/nonmatchings/5A38", VSync);

INCLUDE_ASM("asm/main/nonmatchings/5A38", v_wait);

INCLUDE_ASM("asm/main/nonmatchings/5A38", ChangeClearRCnt);

s32 ResetCallback(void) { return D_8002D340->ResetCallback(); }

INCLUDE_ASM("asm/main/nonmatchings/5A38", InterruptCallback);

void *DMACallback(s32 dma, void (*func)()) {
    return D_8002D340->DMACallback(dma, func);
}

INCLUDE_ASM("asm/main/nonmatchings/5A38", VSyncCallback);
// s32 VSyncCallback(void (*f)()) {
//     return D_8002D340->VSyncCallbacks(0, f);
// }

s32 VSyncCallbacks(s32 ch, void (*f)()) {
    return D_8002D340->VSyncCallbacks(ch, f);
}

s32 StopCallback(void) { return D_8002D340->StopCallback(); }

s32 RestartCallback(void) { return D_8002D340->RestartCallback(); }

u16 CheckCallback(void) { return D_8002C2BA; }