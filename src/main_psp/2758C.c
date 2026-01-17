// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game_psp.h>

// https://pspdev.github.io/pspsdk/
#define PSP_LEGACY_TYPES_DEFINED // avoid processing psptypes.h
#include <psppower.h>
#include <psxsdk/libgpu.h>

extern s32 D_psp_08C63B24;
extern u8 g_BmpCastleMap[0x8000];
extern u16 g_Clut[3][0x1000];
extern u16 D_psp_08C63324[];

void func_psp_089262C4(void);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", FntPrint);

void func_psp_08925F7C(s32 x, s32 y0, s32 w, s32 h) {
    RECT rect;
    s32 y;
    s32 i;

    for (y = y0; y < (y0 + h); y++) {
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = 1;
        StoreImage(&rect, (u_long*)D_psp_08C63324);
        if (D_psp_08C63324[0] == 0x7FFF) {
            D_psp_08C63324[0] = 0xFFFF;
        }
        for (i = 0; i < w; i++) {
            if (D_psp_08C63324[i] == 0x8000) {
                D_psp_08C63324[i] = 0x8001;
            }
        }
        LoadImage(&rect, (u_long*)D_psp_08C63324);
    }
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_089260AC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/2758C", func_psp_089260D0);

int CdInit(void) { return 0; }

int CdMix(void* vol) { return 0; }

long CdDataCallback(void (*func)()) {
    if (func != NULL) {
        func();
    }
    return 0;
}

long CdReadyCallback(void (*func)()) { return NULL; }

void ChangeClearPAD(long) {}

void InitCARD(long val) { func_psp_08919140(); }

long StartCARD(void) { return 0; }

void _bu_init(void) {}

void SsSetStereo(void) {}

void SsSetMono(void) {}

void SsSetMVol(short voll, short volr) {}

void SsSetSerialAttr(char s_num, char attr, char mode) {}

void SsUtSetReverbDepth(short ldepth, short rdepth) {}

void SsSeqPlay(short seq_access_num, char play_mode, short l_count) {}

s16 SsSeqOpen(u32 addr, s16 vab_id) { return 0; }

void SsSeqClose(short seq_access_num) {}

void SsSeqStop(short seq_access_num) {}

void SsSeqSetVol(short arg0, short arg1, short arg2) {}

void FntLoad(s32 tx, s32 ty) {}

s32 FntOpen(s32 x, s32 y, s32 w, s32 h, s32 isbg, s32 n) { return 0; }

void SetDumpFnt(int id) {}

int SetGraphDebug(int level) { return 0; }

void PadInit(int mode) {}

u_long PadRead(int id) { return 0; }

void GsInitVcount(void) { func_psp_089262C4(); }

void func_psp_089262C4(void) { D_psp_08C63B24 = func_psp_0891B528(); }

long GsGetVcount(void) {
    return ((func_psp_0891B528() - D_psp_08C63B24) + 1) << 8;
}

int CdControl(u_char com, u_char* param, u_char* result) { return 2; }

int CdSync(int mode, u_char* result) { return 2; }

void func_psp_08926348(void) {
    u8* temp_v0;

    temp_v0 = (u8*)func_psp_08919C8C(0);
    if (func_psp_08919E6C(0, temp_v0) > 0) {
        func_psp_08910D28();
        func_psp_0890FC2C();
        func_psp_0890FF84();
        func_psp_08910298(1);
        func_psp_089117F4(
            1, 0, 0, 0x100, 0x110, 0xF0, (u8*)func_psp_08919E1C(temp_v0), 0, 0,
            0x100, (u8*)sceGeEdramGetAddr() + 0x1BC000);
        func_psp_089117F4(
            3, 0, 0, 0x100, 1, 0x100, (u8*)func_psp_08919DF4(temp_v0), 0, 0,
            0x100, (u8*)sceGeEdramGetAddr() + 0x1DE000);
        func_psp_0890FF2C();
        sceKernelDcacheWritebackAll();
        func_psp_0890FE98();
        DrawSync(0);
    }
}

void DisableAutoPowerOff(void) {
    sceKernelPowerTick(PSP_POWER_TICK_ALL);
    FntPrint("Disable Auto Power Off\n");
}

void func_psp_089264CC(s32 arg0, u_long* arg1, s32 arg2) {
    RECT rect;
    u16* var_s0;

    var_s0 = (u16*)g_Clut;
    arg0 &= 0x3FF;
    if ((arg0 >= 0) && (arg0 < 0x100)) {
        rect.x = 0x200;
    } else if ((arg0 >= 0x100) && (arg0 < 0x200)) {
        rect.x = 0;
        var_s0 += 0x1000;
    } else if ((arg0 >= 0x200) && (arg0 < 0x300)) {
        rect.x = 0x100;
        var_s0 += 0x2000;
    } else {
        return;
    }
    if (arg2 != 0) {
        u8* p = (u8*)arg1;
        p[0] = 0;
        p[1] = 0;
    }
    rect.x += (arg0 & 0xF) * 0x10;
    rect.y = ((arg0 / 0x10) & 0xF) + 0xF0;
    rect.w = 0x100;
    rect.h = 1;
    LoadImage(&rect, arg1);
    var_s0 += (((arg0 / 0x10) & 0xF) << 8) + ((arg0 & 0xF) * 0x10);
    memcpy(var_s0, arg1, 0x200);
}

void func_psp_0892667C(s32 paletteID, u16* data) {
    RECT rect;
    u16* clutPtr;

    clutPtr = (u16*)g_Clut;
    paletteID &= 0x3FF;
    if (paletteID >= 0 && paletteID < 0x100) {
        rect.x = 0x200;
    } else if (paletteID >= 0x100 && paletteID < 0x200) {
        rect.x = 0;
        clutPtr += 0x1000;
    } else if (paletteID >= 0x200 && paletteID < 0x300) {
        rect.x = 0x100;
        clutPtr += 0x2000;
    } else {
        return;
    }
    rect.x += (paletteID & 0xF) * 0x10;
    rect.y = ((paletteID / 0x10) & 0xF) + 0xF0;
    rect.w = 0x10;
    rect.h = 1;
    LoadImage(&rect, (u_long*)data);
    clutPtr += (((paletteID / 0x10) & 0xF) << 8) + ((paletteID & 0xF) * 0x10);
    memcpy(clutPtr, data, 0x20);
}

void func_psp_08926808(s32 arg0, u_long* arg1) {
    RECT rect;
    u16* clutPtr;

    clutPtr = (u16*)g_Clut;
    arg0 &= 0x3FF;
    if ((arg0 >= 0) && (arg0 < 0x100)) {
        rect.x = 0x200;
    } else if ((arg0 >= 0x100) && (arg0 < 0x200)) {
        rect.x = 0;
        clutPtr += 0x1000;
    } else if ((arg0 >= 0x200) && (arg0 < 0x300)) {
        rect.x = 0x100;
        clutPtr += 0x2000;
    } else {
        return;
    }
    rect.x += (arg0 & 0xF) * 0x10;
    rect.y = ((arg0 / 0x10) & 0xF) + 0xF0;
    rect.w = 0x10;
    rect.h = 1;
    func_psp_0891C1C0(&rect, arg1);
    clutPtr += (((arg0 / 0x10) & 0xF) << 8) + ((arg0 & 0xF) * 0x10);
    memcpy(clutPtr, arg1, 0x20);
}

void GameEntrypoint(void) {
    func_psp_08926348();
    func_psp_0892A1EC(0);
    while (func_psp_0890FB70("F_MAP.BIN;1", g_BmpCastleMap, 0, 0x8000) == 0) {
        sceKernelDelayThreadCB(1000000);
    }
    MainGame();
}
