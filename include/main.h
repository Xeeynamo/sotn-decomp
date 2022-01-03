#ifndef MAIN_H
#define MAIN_H
#include <psxsdk/libetc.h>

typedef struct
{
    u32 tag;
    u8 r0;
    u8 g0;
    u8 b0;
    u8 code;
    s16 x0;
    s16 y0;
    s8 u0;
    s8 v0;
    u16 clut;
    s16 w;
    s16 h;
} SPRT;

extern s32 D_8003925C;
extern s32 D_8003C734;                            /* extern */
extern s32 D_80073080;

extern void func_80015238(s32 arg0);
extern unsigned char func_80019424();
extern unsigned char func_80019434();
extern unsigned char func_80019444();
extern void func_800195C8(s32);
extern void func_800199D0(s32);
extern void func_80021F6C(s16, s16);

#endif
