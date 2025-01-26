#include <common.h>
#include <include_asm.h>
#include <psxsdk/libetc.h>
#include <psxsdk/kernel.h>
#include <psxsdk/libapi.h>
#include <psxsdk/libc.h>
#include "../libapi/libapi_internal.h"

static Callback setIntr(s32 arg0, Callback arg1);
static void* startIntr();
static void* stopIntr();
static void* restartIntr();
static void memclr(void* ptr, s32 size);
static void trapIntr();

typedef struct {
    u16 interruptsInitialized;
    u16 inInterrupt;
    Callback handlers[11];
    u16 enabledInterruptsMask;
    u16 savedMask;
    int savedPcr;
    jmp_buf buf;
    s32 stack[1024];
} intrEnv_t;

static intrEnv_t intrEnv = {
    0, // interruptsInitialized
    0, // inInterrupt
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0}, // handlers (explicit zeros for each element)
    0,   // enabledInterruptsMask
    0,   // savedMask
    0,   // savedPcr
};

static struct Callbacks callbacks = {
    "$Id: intr.c,v 1.73 1995/11/10 05:29:40 suzu Exp $",
    0,
    setIntr,
    startIntr,
    stopIntr,
    0,
    restartIntr,
    &intrEnv};
struct Callbacks* pCallbacks = &callbacks;

void* ResetCallback(void) { return pCallbacks->ResetCallback(); }

void InterruptCallback(int irq, void (*f)()) {
    pCallbacks->InterruptCallback(irq, f);
}

Callback DMACallback(int dma, void (*func)()) {
    return pCallbacks->DMACallback(dma, func);
}

void VSyncCallback(void (*f)()) { pCallbacks->VSyncCallbacks(0, f); }

Callback VSyncCallbacks(int ch, void (*f)()) {
    return pCallbacks->VSyncCallbacks(ch, f);
}

void StopCallback(void) { pCallbacks->StopCallback(); }

long RestartCallback(void) { return (long)pCallbacks->RestartCallback(); }

int CheckCallback(void) { return intrEnv.inInterrupt; }

static volatile u16* i_stat = (u16*)0x1F801070;
static volatile u16* g_InterruptMask = (u16*)0x1F801074;
static volatile s32* d_pcr = (s32*)0x1F8010F0;

u16 GetIntrMask(void) { return *g_InterruptMask; }

u16 SetIntrMask(u16 arg0) {
    u16 mask;

    mask = *g_InterruptMask;
    *g_InterruptMask = arg0;
    return mask;
}

void* startIntr() {
    if (intrEnv.interruptsInitialized != 0) {
        return NULL;
    }
    *i_stat = *g_InterruptMask = 0;
    *d_pcr = 0x33333333;
    memclr(&intrEnv, sizeof(intrEnv) / sizeof(s32));
    if (setjmp(intrEnv.buf) != 0) {
        trapIntr();
    }
    intrEnv.buf[JB_SP] = (s32)&intrEnv.stack[1004];
    HookEntryInt(intrEnv.buf);
    intrEnv.interruptsInitialized = 1;
    pCallbacks->VSyncCallbacks = startIntrVSync();
    pCallbacks->DMACallback = startIntrDMA();
    _96_remove();
    ExitCriticalSection();
    return &intrEnv;
}

static s32 trapMissedCount = 0;

void trapIntr() {
    s32 i;
    u16 mask;

    if (intrEnv.interruptsInitialized == 0) {
        printf("unexpected interrupt(%04x)\n", *i_stat);
        ReturnFromException();
    }
    intrEnv.inInterrupt = 1;
    mask = (intrEnv.enabledInterruptsMask & *i_stat) & *g_InterruptMask;
    while (mask != 0) {
        for (i = 0; mask && i < 11; ++i, mask >>= 1) {
            if (mask & 1) {
                *i_stat = ~(1 << i);
                if (intrEnv.handlers[i] != NULL) {
                    intrEnv.handlers[i]();
                }
            }
        }
        mask = (intrEnv.enabledInterruptsMask & *i_stat) & *g_InterruptMask;
    }
    if (*i_stat & *g_InterruptMask) {
        if (trapMissedCount++ > 0x800) {
            printf("intr timeout(%04x:%04x)\n", *i_stat, *g_InterruptMask);
            trapMissedCount = 0;
            *i_stat = 0;
        }
    } else {
        trapMissedCount = 0;
    }
    intrEnv.inInterrupt = 0;
    ReturnFromException();
}

Callback setIntr(s32 irq, Callback handler) {
    Callback prevHandler;
    s32 mask;

    prevHandler = intrEnv.handlers[irq];
    if ((handler != prevHandler) && (intrEnv.interruptsInitialized != 0)) {
        mask = *g_InterruptMask;
        *g_InterruptMask = 0;
        if (handler != NULL) {
            intrEnv.handlers[irq] = handler;
            mask = mask | (1 << irq);
            intrEnv.enabledInterruptsMask |= (1 << irq);
        } else {
            intrEnv.handlers[irq] = NULL;
            mask = mask & ~(1 << irq);
            intrEnv.enabledInterruptsMask &= ~(1 << irq);
        }
        if (irq == 0) {
            ChangeClearPAD(handler == NULL);
            ChangeClearRCnt(3, handler == NULL);
        }
        if (irq == 4) {
            ChangeClearRCnt(0, handler == NULL);
        }
        if (irq == 5) {
            ChangeClearRCnt(1, handler == NULL);
        }
        if (irq == 6) {
            ChangeClearRCnt(2, handler == NULL);
        }
        *g_InterruptMask = mask;
    }
    return prevHandler;
}

void* stopIntr() {
    if (intrEnv.interruptsInitialized == 0) {
        return NULL;
    }
    EnterCriticalSection();
    intrEnv.savedMask = *g_InterruptMask;
    intrEnv.savedPcr = *d_pcr;
    *i_stat = *g_InterruptMask = 0;
    *d_pcr &= 0x77777777;
    ResetEntryInt();
    intrEnv.interruptsInitialized = 0;
    return &intrEnv;
}

void* restartIntr() {
    if (intrEnv.interruptsInitialized != 0) {
        return 0;
    }

    HookEntryInt(intrEnv.buf);
    intrEnv.interruptsInitialized = 1;
    *g_InterruptMask = intrEnv.savedMask;
    *d_pcr = intrEnv.savedPcr;
    ExitCriticalSection();
    return &intrEnv;
}

void memclr(void* ptr, s32 size) {
    s32 i;
    s32* e = (s32*)ptr;

    for (i = size - 1; i != -1; i--) {
        *e = 0;
        e++;
    }
}
