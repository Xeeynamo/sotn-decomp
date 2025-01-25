#ifndef LIBETC_H
#define LIBETC_H

struct Callbacks {
    const char* rcsid; /* "$Id: intr.c,v 1.73 1995/11/10 05:29:40 suzu Exp $" */
    void* (*DMACallback)(int dma, void (*func)());
    void* (*InterruptCallback)(int irq, void (*f)());
    int (*ResetCallback)(void);
    int (*StopCallback)(void);
    int (*VSyncCallbacks)(int ch, void (*f)());
    int (*RestartCallback)(void);
    void* D_8002C2B8;
};

extern struct Callbacks* D_8002D340;

int VSync(int mode);
int VSyncCallback(void (*f)());
int VSyncCallbacks(int ch, void (*f)());

void* DMACallback(int dma, void (*func)());
int ResetCallback(void);
int StopCallback(void);
int RestartCallback(void);
int CheckCallback(void);

long SetVideoMode(long mode);

void PadInit(int mode);
u_long PadRead(int id);
void PadStop(void);

#endif
