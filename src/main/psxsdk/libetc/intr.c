// SPDX-License-Identifier: MIT
#include <common.h>
#include <include_asm.h>
#include <psxsdk/libetc.h>
#include <psxsdk/kernel.h>
#include <psxsdk/libapi.h>
#include <psxsdk/libc.h>
#include "../libapi/libapi_internal.h"

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

static Callback setIntr(int arg0, Callback arg1);
static intrEnv_t* startIntr();
static intrEnv_t* stopIntr();
static intrEnv_t* restartIntr();
static void memclr(void* ptr, size_t size);
static void trapIntr();

static intrEnv_t intrEnv = {0};

static struct Callbacks callbacks = {
    .rcsid = "$Id: intr.c,v 1.73 1995/11/10 05:29:40 suzu Exp $",
    .DMACallback = NULL,
    .InterruptCallback = setIntr,
    .ResetCallback = startIntr,
    .StopCallback = stopIntr,
    .VSyncCallbacks = NULL,
    .RestartCallback = restartIntr,
    .intrEnv = &intrEnv,
};

struct Callbacks* pCallbacks = &callbacks;
static volatile u16* i_stat = (u16*)0x1F801070;
static volatile u16* g_InterruptMask = (u16*)0x1F801074;
static volatile s32* d_pcr = (s32*)0x1F8010F0;
static s32 trapMissedCount = 0;

void* ResetCallback(void) { return pCallbacks->ResetCallback(); }

void InterruptCallback(int irq, Callback f) {
    pCallbacks->InterruptCallback(irq, f);
}

Callback DMACallback(int dma, Callback f) {
    return pCallbacks->DMACallback(dma, f);
}

void VSyncCallback(Callback f) { pCallbacks->VSyncCallbacks(0, f); }

Callback VSyncCallbacks(int ch, Callback f) {
    return pCallbacks->VSyncCallbacks(ch, f);
}

void StopCallback(void) { pCallbacks->StopCallback(); }

long RestartCallback(void) { return (long)pCallbacks->RestartCallback(); }

int CheckCallback(void) { return intrEnv.inInterrupt; }

u16 GetIntrMask(void) { return *g_InterruptMask; }

u16 SetIntrMask(u16 arg0) {
    u16 mask;

    mask = *g_InterruptMask;
    *g_InterruptMask = arg0;
    return mask;
}

intrEnv_t* startIntr() {
    if (intrEnv.interruptsInitialized) {
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
    intrEnv.interruptsInitialized = true;
    pCallbacks->VSyncCallbacks = startIntrVSync();
    pCallbacks->DMACallback = startIntrDMA();
    _96_remove();
    ExitCriticalSection();
    return &intrEnv;
}

void trapIntr() {
    int i;
    u16 mask;

    if (!intrEnv.interruptsInitialized) {
        printf("unexpected interrupt(%04x)\n", *i_stat);
        ReturnFromException();
    }
    intrEnv.inInterrupt = true;
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
    intrEnv.inInterrupt = false;
    ReturnFromException();
}

Callback setIntr(int irq, Callback handler) {
    Callback prevHandler;
    int mask;

    prevHandler = intrEnv.handlers[irq];
    if (handler != prevHandler && intrEnv.interruptsInitialized) {
        mask = *g_InterruptMask;
        *g_InterruptMask = 0;
        if (handler != NULL) {
            intrEnv.handlers[irq] = handler;
            mask = mask | (1 << irq);
            intrEnv.enabledInterruptsMask |= 1 << irq;
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

intrEnv_t* stopIntr() {
    if (!intrEnv.interruptsInitialized) {
        return NULL;
    }
    EnterCriticalSection();
    intrEnv.savedMask = *g_InterruptMask;
    intrEnv.savedPcr = *d_pcr;
    *i_stat = *g_InterruptMask = 0;
    *d_pcr &= 0x77777777;
    ResetEntryInt();
    intrEnv.interruptsInitialized = false;
    return &intrEnv;
}

intrEnv_t* restartIntr() {
    if (intrEnv.interruptsInitialized) {
        return NULL;
    }

    HookEntryInt(intrEnv.buf);
    intrEnv.interruptsInitialized = true;
    *g_InterruptMask = intrEnv.savedMask;
    *d_pcr = intrEnv.savedPcr;
    ExitCriticalSection();
    return &intrEnv;
}

void memclr(void* ptr, size_t size) {
    int* e = (int*)ptr;

    while (size--) {
        *e++ = 0;
    }
}
