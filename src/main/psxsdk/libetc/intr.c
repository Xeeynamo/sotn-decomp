
#include <common.h>
#include <include_asm.h>
#include <psxsdk/libetc.h>
#include <psxsdk/kernel.h>

int ResetCallback(void) { return D_8002D340->ResetCallback(); }

void InterruptCallback(int irq, void (*f)()) {
    D_8002D340->InterruptCallback(irq, f);
}

void* DMACallback(int dma, void (*func)()) {
    return D_8002D340->DMACallback(dma, func);
}

int VSyncCallback(void (*f)()) { D_8002D340->VSyncCallbacks(0, f); }

int VSyncCallbacks(int ch, void (*f)()) {
    return D_8002D340->VSyncCallbacks(ch, f);
}

int StopCallback(void) { return D_8002D340->StopCallback(); }

int RestartCallback(void) { return D_8002D340->RestartCallback(); }

int CheckCallback(void) { return D_8002C2BA; }

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/intr", GetIntrMask);

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/intr", SetIntrMask);

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/intr", startIntr);

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/intr", trapIntr);

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/intr", setIntr);

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/intr", stopIntr);

void HookEntryInt(unsigned short*);                               /* extern */
extern unsigned short D_8002C2B8;
extern unsigned short D_8002C2EA;
extern int D_8002C2EC;
extern volatile int* D_8002D34C;
extern u16* g_InterruptMask;

u16* restartIntr() {
    u16* p = &D_8002C2B8;
    
    if (*p != 0) {
        return 0;
    }
    
    HookEntryInt(p + 0x1C);
    *p = 1;
    *g_InterruptMask = D_8002C2EA;
    *D_8002D34C = D_8002C2EC;
    ExitCriticalSection();
    return p;
}

void memclr(int* ptr, int size) {
    int i;
    int* e = ptr;

    for (i = size - 1; i != -1; i--) {
        *e = 0;
        e++;
    }
}
