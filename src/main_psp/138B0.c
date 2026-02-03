// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game_psp.h>
#include "main_psp_private.h"

// https://pspdev.github.io/pspsdk/
#define PSP_LEGACY_TYPES_DEFINED // avoid processing psptypes.h
#include <pspgu.h>
#include <pspumd.h>
#include <psppower.h>

char D_psp_0893CD20[] = "DVDUMD_SAMPLE";
char D_psp_0893CD30[] = PSP_UMD_ALIAS_NAME;
char D_psp_0893CD38[] = "DVDUMD_CTRL";
extern s32 g_drawWallpaperBackground;
extern s32 D_psp_08B1FB54;
extern s32 D_psp_08B1FB58;
extern s32 D_psp_08B1FB5C;
extern s32 D_psp_08B1FB60;
extern s32 D_psp_08B1FB64;
extern s32 D_psp_08B1FB68;
extern s32 D_psp_08B1FB70;
extern s32 D_psp_08B41FF0;
extern volatile s32 D_psp_08B1FB50;
extern s32 D_psp_089B7140[2][0xD000];

void func_psp_089144BC(void);

s32 func_psp_089121BC(s32 count, s32 arg, void* param) {
    D_psp_08B1FB58 = arg;
    if (arg & PSP_UMD_MEDIA_IN) {
        D_psp_08B1FB54 |= 1;
    } else if (arg & PSP_UMD_MEDIA_OUT) {
        D_psp_08B1FB54 = 0;
        D_psp_08B1FB58 = 0;
    }
    if (arg & PSP_UMD_READABLE) {
        D_psp_08B1FB58 = 2;
    } else if (arg & PSP_UMD_READY) {
        D_psp_08B1FB58 = 1;
    } else if (arg & PSP_UMD_NOT_READY) {
        D_psp_08B1FB58 = 0;
    }
    return 0;
}

void func_psp_0891228C(void) {
    volatile s32 ret;

    D_psp_08B1FB50 =
        sceKernelCreateCallback(D_psp_0893CD20, func_psp_089121BC, NULL);
    D_psp_08B1FB50;
    ret = sceUmdRegisterUMDCallBack(D_psp_08B1FB50);
    ret;
    if (sceUmdCheckMedium() == 0) {
        sceUmdWaitDriveStatCB(PSP_UMD_MEDIA_IN, 0);
    }
    ret = sceUmdActivate(PSP_UMD_MODE_POWERON, D_psp_0893CD30);
    if (ret < 0) {
        sceUmdUnRegisterUMDCallBack(D_psp_08B1FB50);
        sceKernelDeleteCallback(D_psp_08B1FB50);
    }
    D_psp_08B1FB5C = 1;
    sceUmdWaitDriveStatCB(PSP_UMD_READABLE, 0);
    while (func_psp_089123B8() == 0) {
        sceKernelDelayThreadCB(100);
    }
    D_psp_08B1FB54 = 1;
}

s32 func_psp_08912398(s32 argc, void* argv) {
    s32 var_s0;

    while (true) {
        sceKernelDelayThreadCB(100);
    }
    return var_s0;
}

s32 func_psp_089123B8(void) {
    u8 var_s2;
    u8 var_s1;
    u8 var_s0;

    sceKernelWaitSemaCB(D_psp_08B1FB68, 1, 0);
    sceKernelSignalSema(D_psp_08B1FB68, 1);
    var_s2 = 0;
    var_s1 = 0;
    var_s0 = 0;
    if (D_psp_08B1FB58 == 2 && D_psp_08B1FB54 == 1) {
        var_s0 = 1;
    }
    if (var_s0 && D_psp_08B1FB5C) {
        var_s1 = 1;
    }
    if (var_s1 && !D_psp_08B1FB60 != 0) {
        var_s2 = 1;
    }
    return var_s2;
}

void func_psp_0891249C(void) {
    volatile s32 sp1C;
    volatile s32 sp18;

    D_psp_08B1FB54 = 0;
    D_psp_08B1FB58 = 0;
    D_psp_08B1FB5C = 0;
    func_psp_0891228C();
    sp18 = sceKernelCreateThread(
        D_psp_0893CD38, func_psp_08912398, 0x32, 0x1000, 0, NULL);
    sp18;
    D_psp_08B41FF0 = sp18;
    sp1C = sceKernelStartThread(D_psp_08B41FF0, 0, 0);
    sp1C;
}

s32 func_psp_08912530(s32 count, s32 arg, void* param) {
    if (arg & PSP_POWER_CB_POWER_SWITCH) {
        D_psp_08B1FB70 = 1;
    }
    if (arg & PSP_POWER_CB_HOLD_SWITCH) {
    }
    if (arg & PSP_POWER_CB_STANDBY) {
    }
    if (arg & PSP_POWER_CB_RESUME_COMPLETE) {
        D_psp_08B1FB70 = 0;
        D_psp_08B1FB60 = 0;
        D_psp_08B1FB64++;
    }
    if (arg & PSP_POWER_CB_RESUMING) {
        D_psp_08B1FB60 = 1;
    }
    if (arg & PSP_POWER_CB_SUSPENDING) {
        D_psp_08B1FB60 = 1;
    }
    return 0;
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_089125F8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08912608);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08912640);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_0891269C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_0891273C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_0891274C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_0891275C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_089127D8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_089127E8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08912814);

s32 func_psp_08912820(s32 arg0, s32 arg1) {
    s32 temp_s0;

    func_psp_0892A8C0();
    DrawSync(0);
    VSync(0);
    temp_s0 = func_psp_089128C4(arg0, arg1);
    g_drawWallpaperBackground = 2;
    func_psp_08910044();
    func_psp_0891A800();
    sceGuSync(0, 0);
    func_psp_089144BC();
    func_psp_089144BC();
    func_psp_089144BC();
    return temp_s0;
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_089128C4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_089132C8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08913314);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_089133D4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08913A04);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08913B48);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08913B98);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08913C24);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08913C58);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08913CA0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08913CF0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08913D20);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08913DD4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08913E60);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08913F5C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_089140DC);

void func_psp_089144BC(void) {
    s32* dispList = D_psp_089B7140[0];

    sceGuStart(0, dispList, sizeof(D_psp_089B7140[0]));
    sceGuTexMode(GU_PSM_T8, 0, GU_SINGLE_CLUT, GU_TEXBUF_NORMAL);
    sceGuTexImage(0, 0x200, 0x200, 0x200, (u8*)(WALLPAPER_TEX_ADDR));
    sceGuClutMode(GU_PSM_5551, 0, 0xFF, 0);
    sceGuClutLoad(32, (u8*)(WALLPAPER_CLUT_ADDR));
    sceGuEnable(GU_TEXTURE_2D);
    sceGuBlendFunc(GU_ADD, GU_FIX, GU_FIX, 0xFFFFFFFF, 0x00000000);
    sceGuEnable(GU_BLEND);
    sceGuColor(0xFFFFFFFF);
    sceGuSpriteMode(GU_SCR_WIDTH, GU_SCR_HEIGHT, GU_SCR_WIDTH, GU_SCR_HEIGHT);
    sceGuDrawSprite(0, 0, 0, 0, 0, GU_NOFLIP, GU_NOROTATE);
    sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0x00000000, 0x00000000);
    sceGuFinish();
    sceGuSync(GU_SYNC_FINISH, GU_SYNC_WAIT);
    sceDisplayWaitVblankStartCB();
    EndFrame();
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08914638);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08914854);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_0891490C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_0891499C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08914A18);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08914AB8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08914AE8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08914B08);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08914B58);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08914BA4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08914BF4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08914C20);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", dispbuf_func);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08914E44);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08914E74);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08914EE0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08914F18);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08914FA8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08914FFC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_0891504C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08915070);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08915088);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08915228);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08915250);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_0891527C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08915294);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08915324);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08915340);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_0891535C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_0891539C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08915454);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08915470);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", read_func);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08915C70);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08915F5C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08915FD0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08916094);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08916110);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08916188);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_089161D8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08916278);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_089162A8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_089162C8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_089162F0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08916310);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", soundbuf_func);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08916550);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08916630);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08916724);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08916830);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_0891689C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_089168E8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_0891692C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/138B0", func_psp_08916984);
