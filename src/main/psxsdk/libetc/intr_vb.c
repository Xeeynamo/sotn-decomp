#include "common.h"

typedef void (*Callback)();

void trapIntrVSync(void);
Callback setIntrVSync(int index, Callback callback);
void VSync_memclr(int*, int);

extern void InterruptCallback(int, void*);
extern Callback D_8002D354[8];
extern volatile u_long* D_8002D378; /* 0x1F801114 - Timer 1 Counter Mode */
extern volatile int Vcount;

Callback (*startIntrVSync(void))(s32, Callback) {
    *D_8002D378 = 0x107;
    Vcount = 0;
    VSync_memclr(&D_8002D354, 8);
    InterruptCallback(0, &trapIntrVSync);
    return &setIntrVSync;
}

void trapIntrVSync(void) {
    int i;

    Vcount += 1;
    (void)Vcount;

    for (i = 0; i < 8; i++) {
        if (D_8002D354[i] != NULL) {
            D_8002D354[i]();
        }
    }
}

Callback setIntrVSync(int index, Callback callback) {
    Callback ret = D_8002D354[index];
    if (callback != ret) {
        D_8002D354[index] = callback;
    }
    return ret;
}

void VSync_memclr(int* ptr, int size) {
    int i;
    int* e = ptr;

    for (i = size - 1; i != -1; i--) {
        *e = 0;
        e++;
    }
}
