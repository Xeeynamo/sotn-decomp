#ifndef LIBETC_H
#define LIBETC_H

struct Callbacks {
    void (*unk0)(void);
    void* (*DMACallback)(int dma, void (*func)());
    void (*unk8)(void);
    int (*ResetCallback)(void);
    int (*StopCallback)(void);
    int (*VSyncCallbacks)(int ch, void (*f)());
    int (*RestartCallback)(void);
};

extern unsigned short D_8002C2BA;
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