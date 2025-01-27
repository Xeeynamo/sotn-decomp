#include "common.h"

typedef void (*Callback)();

Callback setIntrDMA(int index, Callback callback);
void trapIntrDMA(void);
void DMA_memclr(int* ptr, int size);

extern void InterruptCallback(int, void*);

static volatile u_long* D_8002D37C =
    (u_long*)0x1F8010F4; /* DMA Interrupt Register */
static Callback D_8002D380[8] = {0};
static u_long* D_8002D3A0 = (u_long*)0x1F801080;

void* startIntrDMA(void) {
    DMA_memclr(&D_8002D380, 8);
    *D_8002D37C = 0;
    InterruptCallback(3, &trapIntrDMA);
    return &setIntrDMA;
}

void trapIntrDMA(void) {
    u32 mask;
    int i;

    while ((mask = (*D_8002D37C >> 24) & 0x7f) != 0) {
        for (i = 0; mask != 0 && i < 7; i++, mask >>= 1) {
            if (mask & 1) {
                *D_8002D37C &= (0xffffff | (1 << (i + 24)));
                if (D_8002D380[i] != NULL) {
                    D_8002D380[i]();
                }
            }
        }
    }

    if ((*D_8002D37C & 0xFF000000) == 0x80000000 || *D_8002D37C & 0x8000) {
        printf("DMA bus error: code=%08x\n", *D_8002D37C);
        for (i = 0; i < 7; i++) {
            printf("MADR[%d]=%08x\n", i, D_8002D3A0[4 * i]);
        }
    }
}

Callback setIntrDMA(int index, Callback callback) {
    Callback prev = D_8002D380[index];
    if (callback != prev) {
        if (callback != NULL) {
            D_8002D380[index] = callback;
            *D_8002D37C =
                (*D_8002D37C & 0xFFFFFF) | 0x800000 | (1 << (index + 16));
        } else {
            D_8002D380[index] = 0;
            *D_8002D37C =
                ((*D_8002D37C & 0xFFFFFF) | 0x800000) & ~(1 << (index + 16));
        }
    }
    return prev;
}

void DMA_memclr(int* ptr, int size) {
    int i;
    int* e = ptr;

    for (i = size - 1; i != -1; i--) {
        *e = 0;
        e++;
    }
}
