// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game_psp.h>
#include "main_psp_private.h"

// https://pspdev.github.io/pspsdk/
#define PSP_LEGACY_TYPES_DEFINED // avoid processing psptypes.h
#include <pspctrl.h>
#include <psppower.h>

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    char* unk10;
} Unk08919CF4;

typedef struct Unk08919D98 Unk08919D98;

typedef struct Unk08919D98 {
    s32* unk0;
    Unk08919D98* prev;
    Unk08919D98* next;
    s32 (*unkC)(Unk08919D98*);
    s32 count;
} Unk08919D98;

// BSS
static Picture wallpaper;
static u8 D_psp_08B41F6C[0x30] UNUSED;
static s32 D_psp_08B41F68;
static u8* D_psp_08B41F64;
static u16 D_psp_08B41F60;
static SceCtrlData D_psp_08B41F50;
static SceCtrlData D_psp_08B41F40;

void* memalign(size_t, size_t);
void func_psp_08919C4C(void);
s32 func_psp_08933F7C(u8, u8);
void func_psp_08919D98(Unk08919D98* arg0);

void _init(void) {}

void _fini(void) {}

void func_psp_08919A0C(void) {
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
    sceCtrlReadBufferPositive(&D_psp_08B41F40, 1);
    sceCtrlReadBufferPositive(&D_psp_08B41F50, 1);
}

static void UpdatePad(void) {
    u32 buttons = 0;
    sceCtrlPeekBufferPositive(&D_psp_08B41F40, 1);
    if (func_psp_08932790()) {
        D_psp_08B41F40.Buttons &=
            ~(PSP_CTRL_UP | PSP_CTRL_RIGHT | PSP_CTRL_DOWN | PSP_CTRL_LEFT);
        if (!(D_psp_08B41F40.Buttons & PSP_CTRL_HOLD)) {
            buttons = func_psp_08933F7C(D_psp_08B41F40.Lx, D_psp_08B41F40.Ly);
        }
        if (buttons != 0) {
            sceKernelPowerTick(PSP_POWER_TICK_DISPLAY);
        }
        D_psp_08B41F40.Buttons |= buttons;
    }
    if (D_psp_08B41F40.TimeStamp != D_psp_08B41F50.TimeStamp) {
        D_psp_08B41F60 = D_psp_08B41F40.Buttons & 0xFFFF;
        D_psp_08B41F60 ^= D_psp_08B41F50.Buttons & 0xFFFF;
        D_psp_08B41F60 &= D_psp_08B41F40.Buttons & 0xFFFF;
        memcpy(&D_psp_08B41F50, &D_psp_08B41F40, sizeof(SceCtrlData));
    }
}

u32 PadReadPSP(void) {
    u32 buttons;
    UpdatePad();
    buttons = D_psp_08B41F40.Buttons & 0xFFFF;
    return buttons;
}

u32 PadRead_PSP(void) { return PadReadPSP(); }

void func_psp_08919C00(s32 arg0) {
    func_psp_08919C4C();
    D_psp_08B41F68 = arg0;
    D_psp_08B41F64 = memalign(0x40, D_psp_08B41F68);
}

void func_psp_08919C4C(void) {
    if (D_psp_08B41F64 != NULL) {
        free(D_psp_08B41F64);
        D_psp_08B41F64 = NULL;
    }
}

u8* func_psp_08919C8C(s32 arg0) {
    s32 sp10 = arg0;
    if (func_psp_08919CE4() < sp10) {
        return 0;
    }
    return D_psp_08B41F64 + arg0;
}

static s32 func_psp_08919CE4() { return D_psp_08B41F68; }

static void* func_psp_08919CF4(Unk08919CF4* arg0) {
    arg0->unk10 = "PSP_KOEI_TAIKOU4";
    arg0->unk0 = 0;
    arg0->unk4 = 0;
    arg0->unk8 = 0;
    arg0->unkC = -1;
    return arg0;
}

Unk08919D98* func_psp_08919D40(Unk08919D98* arg0, s16 arg1) {
    if (arg0 != NULL) {
        func_psp_08919D98(arg0);
        if (arg1 > 0) {
            func_psp_08934D20(arg0);
        }
    }
    return arg0;
}

static void func_psp_08919D98(Unk08919D98* arg0) {
    if (arg0->unk0 != NULL) {
        sceKernelVolatileMemUnlock(0);
        sceKernelDelayThreadCB(1);
        arg0->unk0 = NULL;
        arg0->prev = NULL;
        arg0->next = NULL;
    }
}

u8* GetWallpaperClut(u8* tm2Data) { return (u8*)GetPictureClut(&wallpaper); }

u8* GetWallpaperTex(u8* tm2Data) { return (u8*)GetPictureTex(&wallpaper); }

bool IsWallpaperValid() { return GetPictureTex(&wallpaper); }

s32 LoadWallpaper(s32 index, u8* tm2Data) {
    static char* wallpaperPaths[] = {
        "WALLPAPER/16/wp01.tm2;1", "WALLPAPER/16/wp02.tm2;1",
        "WALLPAPER/16/wp03.tm2;1", "WALLPAPER/16/wp04.tm2;1",
        "WALLPAPER/16/wp05.tm2;1", "WALLPAPER/16/wp06.tm2;1",
    };

    s32 ret;
    s32 i;

    if (index < 0 || index > 0) {
        return -1;
    }
    i = GetDxCWallpaperIndex();
    if (i < 0) {
        i = 0;
    }
    ret = func_psp_0890FB70(wallpaperPaths[i], tm2Data, 0, 0x20040);
    if (ret > 0) {
        FillPictureStruct(&wallpaper, tm2Data);
    }
    return ret;
}
