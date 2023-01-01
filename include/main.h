#ifndef MAIN_H
#define MAIN_H
#include <psxsdk/kernel.h>
#include <psxsdk/libapi.h>
#include <psxsdk/libc.h>
#include <psxsdk/libcd.h>
#include <psxsdk/libetc.h>
#include <psxsdk/libgpu.h>
#include <psxsdk/libgs.h>
#include <psxsdk/libgte.h>
#include <psxsdk/libsnd.h>

extern s32 D_8003925C;

extern void PadInit(s32 arg0);
int VSync(s32);
s32 rcos(s32);
s32 rsin(s32);
s32 ratan2(s32, s32);
void* DMACallback(int dma, void (*func)());
extern s32 func_8001D290(s32, s32);
extern s32 func_8001D374(s8, s16, s16);
extern void func_8001D2E0(s32, s32, s32);
extern void func_800202E0(s16);
extern void func_80020F44(s16);
extern void func_80021174(void);
extern void func_80021188(void);
extern s32 func_80021350(const char* str, s32, s32);
extern s32 func_80021880(s32*, s32, s32);
extern s32 func_800219E0(s32);
extern void func_80021F6C(s16, s16);
void func_8002A024(s32, s32);

#endif
