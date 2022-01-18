#ifndef MAIN_H
#define MAIN_H
#include <psxsdk/libetc.h>
#include <psxsdk/libgpu.h>

extern s32 D_8003925C;
extern s32 D_8003C734;
extern s32 g_SettingsCloakMode;
extern s32 g_SettingsSoundMode;
extern s32 g_CurrentPlayableCharacter;
extern s32 D_8003CACC;

extern void func_80015238(s32 arg0);
extern unsigned char func_80019424();
extern unsigned char func_80019434();
extern unsigned char func_80019444();
extern void func_800195C8(s32);
extern void func_800199D0(s32);
extern void func_80021F6C(s16, s16);

#endif
