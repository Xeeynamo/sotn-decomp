#include <common.h>
#include <include_asm.h>
#include <psxsdk/libetc.h>
#include <psxsdk/kernel.h>
#include <psxsdk/libapi.h>
#include "../libapi/libapi_internal.h"

static void memclr(s32* ptr, s32 size);
static void trapIntr();
s32 setjmp(s32*);

#define	JB_PC		0
#define	JB_SP		1
#define	JB_FP		2
#define	JB_S0		3
#define	JB_S1		4
#define	JB_S2		5
#define	JB_S3		6
#define	JB_S4		7
#define	JB_S5		8
#define	JB_S6		9
#define	JB_S7		10
#define	JB_GP		11
#define	JB_SIZE		12

typedef int jmp_buf[JB_SIZE];

typedef struct
{
    u16 unk0[0x1A];
    int unk38;
    jmp_buf buf;
    s32 unk68[0x3EC];
} D_8002C2B8_t;

extern D_8002C2B8_t D_8002C2B8;

extern struct Callbacks* D_8002D340;
extern volatile u16* D_8002D344;
extern volatile u16* g_InterruptMask; // 8002D348
extern volatile s32* D_8002D34C;

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

u16 GetIntrMask(void) { return *g_InterruptMask; }

u16 SetIntrMask(u16 arg0) 
{
    u16 mask;

    mask = *g_InterruptMask;
    *g_InterruptMask = arg0;
    return mask;
}

void* startIntr() {
    if (D_8002C2B8.unk0[0] != 0) {
        return NULL;
    }
    *D_8002D344 = *g_InterruptMask = 0;
    *D_8002D34C = 0x33333333;
    memclr(&D_8002C2B8, 0x41A);
    if (setjmp(D_8002C2B8.buf) != 0) {
        trapIntr();
    }
    D_8002C2B8.buf[JB_SP] = (s32)(&D_8002C2B8 + 1);
    HookEntryInt(D_8002C2B8.buf);
    D_8002C2B8.unk0[0] = 1;
    D_8002D340->VSyncCallbacks = startIntrVSync();
    D_8002D340->DMACallback = startIntrDMA();
    _96_remove();
    ExitCriticalSection();
    return &D_8002C2B8;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/intr", trapIntr);

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/intr", setIntr);

u16* stopIntr() {
    volatile s32* p2;
    volatile u16* mask;
    
    if (D_8002C2B8.unk0[0] == 0) {
        return NULL;
    }
    EnterCriticalSection();
    mask = g_InterruptMask;
    D_8002C2B8.unk0[0x19] = *g_InterruptMask;
    D_8002C2B8.unk38 = *D_8002D34C;
    *D_8002D344 = *mask = 0;
    p2 = D_8002D34C;
    *p2 &= 0x77777777;
    ResetEntryInt(p2);
    D_8002C2B8.unk0[0] = 0;
    return &D_8002C2B8;
}

u16* restartIntr() {
    if (D_8002C2B8.unk0[0] != 0) {
        return 0;
    }
    
    HookEntryInt(D_8002C2B8.buf);
    D_8002C2B8.unk0[0] = 1;
    *g_InterruptMask = D_8002C2B8.unk0[0x19];
    *D_8002D34C = D_8002C2B8.unk38;
    ExitCriticalSection();
    return &D_8002C2B8.unk0[0];
}

void memclr(s32* ptr, s32 size) {
    s32 i;
    s32* e = ptr;

    for (i = size - 1; i != -1; i--) {
        *e = 0;
        e++;
    }
}
