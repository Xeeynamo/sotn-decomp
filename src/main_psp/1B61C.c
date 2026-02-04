// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game_psp.h>
#include "main_psp_private.h"

// https://pspdev.github.io/pspsdk/
#define PSP_LEGACY_TYPES_DEFINED // avoid processing psptypes.h
#include <pspctrl.h>
#include <pspgu.h>
#include <pspthreadman.h>
#include <psputility_modules.h>
#include <psputility_sysparam.h>

// BSS
static s32 timeSinceStartOfFrame;
static s32 timeNow;
static s32 timeStartOfFrame;

extern s32 D_psp_08B41FD0; // exit callback ID
extern s32 D_psp_08B41FE0;
extern s32 D_psp_08B42000; // kernel thread ID
extern s32 D_psp_08B42044;
extern s32 D_psp_08B42048;
extern int D_psp_08B4204C; // button swap
extern u32 D_psp_08B42050;
extern u32 D_psp_08B42054;
extern s32 g_UserLanguage;
extern char* D_psp_08B4205C;
extern char* D_psp_08B42060;
extern s32 D_psp_08B42064;

extern void FinishedRenderingCB(s32 arg0);
extern void VBlankhandler(int idx, void* cookie);

void ClearFrameTimer(void) {
    timeStartOfFrame = 0;
    timeNow = 0;
    timeSinceStartOfFrame = 0;
}

void StartFrameTimer(void) { timeStartOfFrame = sceKernelGetSystemTimeLow(); }

s32 GetTimeSinceStartOfFrame(void) {
    timeNow = sceKernelGetSystemTimeLow();
    timeSinceStartOfFrame = timeNow - timeStartOfFrame;
    return timeSinceStartOfFrame;
}

static s32 ExitGame(int count, int arg1, void* arg2) {
    func_psp_08933BA0();
    func_psp_0892A3D4();
    func_psp_0892E9E4();
    sceKernelExitGame();
    return 0;
}

static s32 CreateExitGameCallback(void) {
    D_psp_08B41FD0 = sceKernelCreateCallback("ExitGame", ExitGame, NULL);
    if (D_psp_08B41FD0 <= 0) {
        return 0;
    }
    sceKernelRegisterExitCallback(D_psp_08B41FD0);
    return 1;
}

static s32 LoadPSPModule(int module) {
    volatile s32 status;
    do {
        status = sceUtilityLoadModule(module);
        if (status < 0) {
            sceKernelDelayThreadCB(100000);
        }
    } while (status < 0);
    return 0;
}

static void LoadPSPModules(void) {
    LoadPSPModule(PSP_MODULE_AV_SASCORE);
    LoadPSPModule(PSP_MODULE_AV_AVCODEC);
    LoadPSPModule(PSP_MODULE_AV_MPEGBASE);
    LoadPSPModule(PSP_MODULE_AV_ATRAC3PLUS);
}

static void UnloadPSPModules(void) {
    sceUtilityUnloadModule(PSP_MODULE_AV_ATRAC3PLUS);
    sceUtilityUnloadModule(PSP_MODULE_AV_MPEGBASE);
    sceUtilityUnloadModule(PSP_MODULE_AV_AVCODEC);
    sceUtilityUnloadModule(PSP_MODULE_AV_SASCORE);
}

static void func_psp_0891A14C(void) {
    static char* D_psp_08946424 = "PACK/";
    static char* D_psp_08946430 = "sound/";
    static char* D_psp_0894643C = "PACK_E/";
    static char* D_psp_08946448 = "snd_e/";

    D_psp_08B42064 = func_psp_0893277C();
    if (D_psp_08B42064 == 0) {
        D_psp_08B4205C = D_psp_08946424;
        D_psp_08B42060 = D_psp_08946430;
    } else {
        D_psp_08B4205C = D_psp_0894643C;
        D_psp_08B42060 = D_psp_08946448;
    }
}

int main(int argc, char* argv[]) {
    int systemLang;

    printf("月下開始00\n"); // Moonlight Start
    CreateExitGameCallback();
    D_psp_08B42044 = 0;
    sceGuInit();
    sceGuDisplay(GU_DISPLAY_OFF);
    memset(sceGeEdramGetAddr(), 0, 0x22100);
    sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE, &systemLang);
    switch (systemLang) {
    default:
    case PSP_SYSTEMPARAM_LANGUAGE_ENGLISH:
        g_UserLanguage = LANG_EN;
        break;
    case PSP_SYSTEMPARAM_LANGUAGE_FRENCH:
        g_UserLanguage = LANG_FR;
        break;
    case PSP_SYSTEMPARAM_LANGUAGE_SPANISH:
        g_UserLanguage = LANG_SP;
        break;
    case PSP_SYSTEMPARAM_LANGUAGE_GERMAN:
        g_UserLanguage = LANG_GE;
        break;
    case PSP_SYSTEMPARAM_LANGUAGE_ITALIAN:
        g_UserLanguage = LANG_IT;
        break;
    }
    switch (g_UserLanguage) {
    default:
    case LANG_EN:
        D_psp_08B42048 = LANG_EN;
        break;
    case LANG_FR:
        D_psp_08B42048 = LANG_FR;
        break;
    case LANG_SP:
        D_psp_08B42048 = LANG_SP;
        break;
    case LANG_GE:
        D_psp_08B42048 = LANG_GE;
        break;
    case LANG_IT:
        D_psp_08B42048 = LANG_IT;
        break;
    }
    sceUtilityGetSystemParamInt(
        PSP_SYSTEMPARAM_ID_INT_CTRL_ASSIGN, &D_psp_08B4204C);
    if (D_psp_08B4204C == PSP_SYSTEMPARAM_CTRL_ASSIGN_CIRCLE_IS_ENTER) {
        D_psp_08B42050 = PSP_CTRL_CIRCLE;
        D_psp_08B42054 = PSP_CTRL_CROSS;
    } else if (D_psp_08B4204C == PSP_SYSTEMPARAM_CTRL_ASSIGN_CROSS_IS_ENTER) {
        D_psp_08B42050 = PSP_CTRL_CROSS;
        D_psp_08B42054 = PSP_CTRL_CIRCLE;
    }
    LoadPSPModules();
    func_psp_089127E8();
    D_psp_08B42000 = sceKernelGetThreadId();
    func_psp_0891269C();
    func_psp_0891249C();
    D_psp_08B41FE0 = sceKernelCreateEventFlag(
        "FileIOWakeUP", PSP_EVENT_WAITMULTIPLE, 0x00000000, NULL);
    sceKernelChangeCurrentThreadAttr(0, PSP_THREAD_ATTR_VFPU);
    func_psp_0891B400();
    func_psp_08937560();
    sceCtrlSetSamplingCycle(0);
    sceGuSetCallback2(GU_CALLBACK_FINISH, &FinishedRenderingCB);
    sceDisplaySetVblankCallback(0, &VBlankhandler, NULL);
    func_psp_08919C00(0x480000);
    func_psp_0891273C();
    func_psp_08919A0C();
    func_psp_0891ACBC();
    func_psp_08930324();
    SetScreenMode(SCREEN_MODE_FULL);
    printf("月下描画開始00\n"); // Moonlight Drawing begins
    sceGuDisplay(GU_DISPLAY_ON);
    func_psp_08910044();
    sceGuSync(GU_SYNC_FINISH, GU_SYNC_WAIT);
    printf("月下ユーティリティ開始00\n"); // Moonlight Started utility
    func_psp_0891979C(4);
    printf("月下ユーティリティ終了00\n"); // Moonlight End utility
    func_psp_0891A14C();
    SetScreenMode(
        GetDxCScreenMode() == 0 ? SCREEN_MODE_PERFECT : SCREEN_MODE_FULL);
    func_psp_08933A10();
    func_psp_0892E9B0();
    func_psp_0892A2D8();
    GameEntrypoint();
    func_psp_0892A3D4();
    func_psp_0892E9E4();
    func_psp_08933BA0();
    sceGuTerm();
    func_psp_08919C4C();
    UnloadPSPModules();
    func_psp_089375A0();
    func_psp_0892FAA8(0, "disc0:/PSP_GAME/SYSDIR/BOOT.BIN");
    func_psp_0892FA84(g_UserLanguage);
    func_psp_0892FCA8(GU_PSM_5551);
    func_psp_0892FC80();
    return 0;
}
