#include <common.h>
#include <include_asm.h>
#include <psxsdk/libetc.h>
#include <psxsdk/kernel.h>
#include <psxsdk/libapi.h>
#include "../libapi/libapi_internal.h"

static void memclr(void* ptr, s32 size);
static void trapIntr();
s32 setjmp(s32*);

#define JB_PC 0
#define JB_SP 1
#define JB_FP 2
#define JB_S0 3
#define JB_S1 4
#define JB_S2 5
#define JB_S3 6
#define JB_S4 7
#define JB_S5 8
#define JB_S6 9
#define JB_S7 10
#define JB_GP 11
#define JB_SIZE 12

typedef int jmp_buf[JB_SIZE];

typedef struct
{
    u16 interruptsInitialized;
    u16 inInterrupt;
    void (*handlers[11])();
    u16 unk30;
    u16 unk32;
    int unk34;
    jmp_buf buf;
    s32 unk68[0x3EC];
    s32 stack[0x14];
} intrEnv_t;

extern intrEnv_t D_8002C2B8;

typedef struct
{
    struct Callbacks callbacks;
    struct Callbacks* D_8002D340;
    volatile u16* D_8002D344;
    volatile u16* g_InterruptMask; // 8002D348
    volatile s32* D_8002D34C;
} D_8002D320_t;

extern D_8002D320_t D_8002D320;
extern s32 D_8002D350;

int ResetCallback(void) { return D_8002D320.D_8002D340->ResetCallback(); }

void InterruptCallback(int irq, void (*f)()) {
    D_8002D320.D_8002D340->InterruptCallback(irq, f);
}

void* DMACallback(int dma, void (*func)()) {
    return D_8002D320.D_8002D340->DMACallback(dma, func);
}

int VSyncCallback(void (*f)()) { D_8002D320.D_8002D340->VSyncCallbacks(0, f); }

int VSyncCallbacks(int ch, void (*f)()) {
    return D_8002D320.D_8002D340->VSyncCallbacks(ch, f);
}

int StopCallback(void) { return D_8002D320.D_8002D340->StopCallback(); }

int RestartCallback(void) { return D_8002D320.D_8002D340->RestartCallback(); }

int CheckCallback(void) { return D_8002C2B8.inInterrupt; }

u16 GetIntrMask(void) { return *D_8002D320.g_InterruptMask; }

u16 SetIntrMask(u16 arg0) {
    u16 mask;

    mask = *D_8002D320.g_InterruptMask;
    *D_8002D320.g_InterruptMask = arg0;
    return mask;
}

void* startIntr() {
    if (D_8002C2B8.interruptsInitialized != 0) {
        return NULL;
    }
    *D_8002D320.D_8002D344 = *D_8002D320.g_InterruptMask = 0;
    *D_8002D320.D_8002D34C = 0x33333333;
    memclr(&D_8002C2B8, sizeof(D_8002C2B8) / sizeof(s32));
    if (setjmp(D_8002C2B8.buf) != 0) {
        trapIntr();
    }
    D_8002C2B8.buf[JB_SP] = D_8002C2B8.stack;
    HookEntryInt(D_8002C2B8.buf);
    D_8002C2B8.interruptsInitialized = 1;
    D_8002D320.D_8002D340->VSyncCallbacks = startIntrVSync();
    D_8002D320.D_8002D340->DMACallback = startIntrDMA();
    _96_remove();
    ExitCriticalSection();
    return &D_8002C2B8;
}

void trapIntr() {
    s32 i;
    u16 mask;

    if (D_8002C2B8.interruptsInitialized == 0) {
        printf("unexpected interrupt(%04x)\n", *D_8002D320.D_8002D344);
        ReturnFromException();
    }
    D_8002C2B8.inInterrupt = 1;
    mask = (D_8002C2B8.unk30 & *D_8002D320.D_8002D344) & *D_8002D320.g_InterruptMask;
    while (mask != 0) {
        for (i = 0; mask && i < 11; ++i, mask >>= 1) {
            if (mask & 1) {
                *D_8002D320.D_8002D344 = ~(1 << i);
                if (D_8002C2B8.handlers[i] != NULL) {
                    D_8002C2B8.handlers[i]();
                }
            }
        }
        mask =(D_8002C2B8.unk30 & *D_8002D320.D_8002D344) & *D_8002D320.g_InterruptMask;
    }
    if (*D_8002D320.D_8002D344 & *D_8002D320.g_InterruptMask) {
        if (D_8002D350++ > 0x800) {
            printf("intr timeout(%04x:%04x)\n", *D_8002D320.D_8002D344, *D_8002D320.g_InterruptMask);
            D_8002D350 = 0;
            *D_8002D320.D_8002D344 = 0;
        }
    } else {
        D_8002D350 = 0;
    }
    D_8002C2B8.inInterrupt = 0;
    ReturnFromException();
}

s32 setIntr(s32 arg0, s32 arg1) {
    s32 temp_s3;
    s32 temp_s4;
    u16 temp_v1;
    s32 var_s3;

    temp_s4 = D_8002C2B8.handlers[arg0];
    if ((arg1 != temp_s4) && (D_8002C2B8.interruptsInitialized != 0)) {
        temp_v1 = *D_8002D320.g_InterruptMask;
        *D_8002D320.g_InterruptMask = 0;
        var_s3 = temp_v1 & 0xFFFF;
        if (arg1 != 0) {
            D_8002C2B8.handlers[arg0] = arg1;
            var_s3 = var_s3 | (1 << arg0);
            D_8002C2B8.unk30 |= (1 << arg0);
        } else {
            D_8002C2B8.handlers[arg0] = 0;
            var_s3 = var_s3 & ~(1 << arg0);
            D_8002C2B8.unk30 &= ~(1 << arg0);
        }
        if (arg0 == 0) {
            ChangeClearPAD(arg1 == 0);
            ChangeClearRCnt(3, arg1 == 0);
        }
        if (arg0 == 4) {
            ChangeClearRCnt(0, arg1 == 0);
        }
        if (arg0 == 5) {
            ChangeClearRCnt(1, arg1 == 0);
        }
        if (arg0 == 6) {
            ChangeClearRCnt(2, arg1 == 0);
        }
        *D_8002D320.g_InterruptMask = var_s3;
    }
    return temp_s4;
}

intrEnv_t* stopIntr() {
    volatile s32* p;
    if (D_8002C2B8.interruptsInitialized == 0) {
        return NULL;
    }
    EnterCriticalSection();
    D_8002C2B8.unk32 = *D_8002D320.g_InterruptMask;
    D_8002C2B8.unk34 = *D_8002D320.D_8002D34C;
    *D_8002D320.D_8002D344 = *D_8002D320.g_InterruptMask = 0;
    p = D_8002D320.D_8002D34C;
    *p &= 0x77777777;
    ResetEntryInt(p);
    D_8002C2B8.interruptsInitialized = 0;
    return &D_8002C2B8;
}

intrEnv_t* restartIntr() {
    if (D_8002C2B8.interruptsInitialized != 0) {
        return 0;
    }
    
    HookEntryInt(D_8002C2B8.buf);
    D_8002C2B8.interruptsInitialized = 1;
    *D_8002D320.g_InterruptMask = D_8002C2B8.unk32;
    *D_8002D320.D_8002D34C = D_8002C2B8.unk34;
    ExitCriticalSection();
    return &D_8002C2B8;
}

void memclr(void* ptr, s32 size) {
    s32 i;
    s32* e = (s32*)ptr;

    for (i = size - 1; i != -1; i--) {
        *e = 0;
        e++;
    }
}
