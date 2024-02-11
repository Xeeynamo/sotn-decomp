
#include <game.h>
#include <psxsdk/libetc.h>

INCLUDE_ASM("main/nonmatchings/psxsdk/libapi/l10", ChangeClearRCnt);

int ResetCallback(void) { return D_8002D340->ResetCallback(); }

INCLUDE_ASM("main/nonmatchings/psxsdk/libapi/l10", InterruptCallback);

void* DMACallback(int dma, void (*func)()) {
    return D_8002D340->DMACallback(dma, func);
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libapi/l10", VSyncCallback);

int VSyncCallbacks(int ch, void (*f)()) {
    return D_8002D340->VSyncCallbacks(ch, f);
}

int StopCallback(void) { return D_8002D340->StopCallback(); }

int RestartCallback(void) { return D_8002D340->RestartCallback(); }

int CheckCallback(void) { return D_8002C2BA; }

INCLUDE_ASM("main/nonmatchings/psxsdk/libapi/l10", GetIntrMask);

INCLUDE_ASM("main/nonmatchings/psxsdk/libapi/l10", SetIntrMask);

INCLUDE_ASM("main/nonmatchings/psxsdk/libapi/l10", startIntr);

INCLUDE_ASM("main/nonmatchings/psxsdk/libapi/l10", trapIntr);

INCLUDE_ASM("main/nonmatchings/psxsdk/libapi/l10", setIntr);

INCLUDE_ASM("main/nonmatchings/psxsdk/libapi/l10", stopIntr);

INCLUDE_ASM("main/nonmatchings/psxsdk/libapi/l10", restartIntr);

void memclr(int* ptr, int size) {
    int i;
    int* e = ptr;

    for (i = size - 1; i != -1; i--) {
        *e = 0;
        e++;
    }
}
