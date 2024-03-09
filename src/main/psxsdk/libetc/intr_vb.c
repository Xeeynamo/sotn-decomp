#include "common.h"

typedef void (*Callback)();

void trapIntrVSync(void);
void setIntrVSync(int index, Callback callback);
void VSync_memclr(int*, int);

extern void InterruptCallback(int, void*);
extern Callback D_8002D354[8];
extern volatile u_long* D_8002D378; /* 0x1F801114 - Timer 1 Counter Mode */
extern volatile int Vcount;

void* startIntrVSync(void) {
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

void setIntrVSync(int index, Callback callback) {
    if (callback != D_8002D354[index]) {
        D_8002D354[index] = callback;
    }
}

void VSync_memclr(int* ptr, int size) {
    int i;
    int* e = ptr;

    for (i = size - 1; i != -1; i--) {
        *e = 0;
        e++;
    }
}
