#ifndef LIBETC_H
#define LIBETC_H

typedef void (*Callback)();

struct Callbacks {
    const char* rcsid; /* "$Id: intr.c,v 1.73 1995/11/10 05:29:40 suzu Exp $" */
    Callback (*DMACallback)(int dma, Callback f);
    Callback (*InterruptCallback)(int irq, Callback f);
    void* (*ResetCallback)(void);
    void* (*StopCallback)(void);
    Callback (*VSyncCallbacks)(int ch, Callback f);
    void* (*RestartCallback)(void);
    void* D_8002C2B8;
};

extern struct Callbacks* D_8002D340;

int VSync(int mode);
void VSyncCallback(Callback f);
Callback VSyncCallbacks(int ch, Callback f);
Callback DMACallback(int dma, Callback f);
void* ResetCallback(void);
void StopCallback(void);
long RestartCallback(void);
int CheckCallback(void);

long SetVideoMode(long mode);

void PadInit(int mode);
u_long PadRead(int id);
void PadStop(void);

#endif
