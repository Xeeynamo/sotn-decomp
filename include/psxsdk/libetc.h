#ifndef LIBETC_H
#define LIBETC_H

struct Callbacks
{
    void (*unk0)(void);
    void* (*DMACallback)(int dma, void (*func)());
    void (*unk8)(void);
    int (*ResetCallback)(void);
    int (*StopCallback)(void);
    int (*VSyncCallbacks)(int ch, void (*f)());
    int (*RestartCallback)(void);
};

extern u16 D_8002C2BA;
extern struct Callbacks *D_8002D340;

int ResetCallback(void);
int VSyncCallback(void (*f)());
int VSyncCallbacks(int ch, void (*f)());
int StopCallback(void);
int RestartCallback(void);
u16 CheckCallback(void);

void PadInit(int mode);
u_long PadRead(int id);
void PadStop(void);

#endif