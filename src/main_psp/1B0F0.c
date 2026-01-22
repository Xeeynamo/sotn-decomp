// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game_psp.h>

// https://pspdev.github.io/pspsdk/
#define PSP_LEGACY_TYPES_DEFINED // avoid processing psptypes.h
#include <pspctrl.h>
#include <pspgu.h>
#include <psppower.h>
#include <pspthreadman.h>
#include <psputility_modules.h>
#include <psputility_sysparam.h>

typedef enum {
    // stretches the game resolution to fill the PSP screen vertically
    SCREEN_MODE_FULL,

    // pixel perfect, but with borders around the game screen
    SCREEN_MODE_PERFECT,
} ScreenMode;

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

// DATA
extern char D_psp_0893CED0[];
extern s32 D_psp_0893CF74[];

// BSS
extern SceCtrlData D_psp_08B41F40;
extern SceCtrlData D_psp_08B41F50;
extern u16 D_psp_08B41F60;
extern u8* D_psp_08B41F64;
extern s32 D_psp_08B41F68;
extern s32 D_psp_08B41F9C;
extern s32 timeStartOfFrame;
extern s32 timeNow;
extern s32 timeSinceStartOfFrame;
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

void* memalign(size_t, size_t);
void func_psp_08919C4C(void);
s32 func_psp_08933F7C(u8, u8);
void func_psp_08919D98(Unk08919D98* arg0);
extern void FinishedRenderingCB(s32 arg0);
extern void func_psp_0891B570(int arg0, int arg1);

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

static void func_psp_08919C4C(void) {
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
    arg0->unk10 = D_psp_0893CED0;
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

u8* func_psp_08919DF4(u8* arg0) {
    return (u8*)func_psp_08932978(&D_psp_08B41F9C);
}

u8* func_psp_08919E1C(u8* arg0) {
    return (u8*)func_psp_08932994(&D_psp_08B41F9C);
}

s32 func_psp_08919E44() { return func_psp_08932994(&D_psp_08B41F9C); }

s32 func_psp_08919E6C(s32 arg0, u8* src) {
    s32 temp_v0;
    s32 var_s0;

    if (arg0 < 0 || arg0 > 0) {
        return -1;
    }
    var_s0 = func_psp_08932768();
    if (var_s0 < 0) {
        var_s0 = 0;
    }
    temp_v0 = func_psp_0890FB70(D_psp_0893CF74[var_s0], src, 0, 0x20040);
    if (temp_v0 > 0) {
        func_psp_08932830(&D_psp_08B41F9C, src);
    }
    return temp_v0;
}

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

static s32 exit_func(int count, int arg1, void* arg2) {
    func_psp_08933BA0();
    func_psp_0892A3D4();
    func_psp_0892E9E4();
    sceKernelExitGame();
    return 0;
}

static s32 func_psp_08919FF8(void) {
    D_psp_08B41FD0 = sceKernelCreateCallback("ExitGame", exit_func, NULL);
    if (D_psp_08B41FD0 <= 0) {
        return 0;
    }
    sceKernelRegisterExitCallback(D_psp_08B41FD0);
    return 1;
}

static s32 func_psp_0891A064(int module) {
    volatile s32 status;
    do {
        status = sceUtilityLoadModule(module);
        if (status < 0) {
            sceKernelDelayThreadCB(100000);
        }
    } while (status < 0);
    return 0;
}

static void func_psp_0891A0BC(void) {
    func_psp_0891A064(PSP_MODULE_AV_SASCORE);
    func_psp_0891A064(PSP_MODULE_AV_AVCODEC);
    func_psp_0891A064(PSP_MODULE_AV_MPEGBASE);
    func_psp_0891A064(PSP_MODULE_AV_ATRAC3PLUS);
}

static void func_psp_0891A104(void) {
    sceUtilityUnloadModule(PSP_MODULE_AV_ATRAC3PLUS);
    sceUtilityUnloadModule(PSP_MODULE_AV_MPEGBASE);
    sceUtilityUnloadModule(PSP_MODULE_AV_AVCODEC);
    sceUtilityUnloadModule(PSP_MODULE_AV_SASCORE);
}

char* D_psp_08946424 = "PACK/";
char* D_psp_08946430 = "sound/";
char* D_psp_0894643C = "PACK_E/";
char* D_psp_08946448 = "snd_e/";

static void func_psp_0891A14C(void) {
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
    int language;

    printf("月下開始00\n"); // Moonlight Start
    func_psp_08919FF8();
    D_psp_08B42044 = 0;
    sceGuInit();
    sceGuDisplay(GU_DISPLAY_OFF);
    memset(sceGeEdramGetAddr(), 0, 0x22100);
    sceUtilityGetSystemParamInt(PSP_SYSTEMPARAM_ID_INT_LANGUAGE, &language);
    switch (language) {
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
    func_psp_0891A0BC();
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
    func_psp_08904408(0, &func_psp_0891B570, 0);
    func_psp_08919C00(0x480000);
    func_psp_0891273C();
    func_psp_08919A0C();
    func_psp_0891ACBC();
    func_psp_08930324();
    func_psp_0891A6A8(SCREEN_MODE_FULL);
    printf("月下描画開始00\n"); // Moonlight Drawing begins
    sceGuDisplay(GU_DISPLAY_ON);
    func_psp_08910044();
    sceGuSync(GU_SYNC_FINISH, GU_SYNC_WAIT);
    printf("月下ユーティリティ開始00\n"); // Moonlight Started utility
    func_psp_0891979C(4);
    printf("月下ユーティリティ終了00\n"); // Moonlight End utility
    func_psp_0891A14C();
    func_psp_0891A6A8(
        func_psp_08932754() == 0 ? SCREEN_MODE_PERFECT : SCREEN_MODE_FULL);
    func_psp_08933A10();
    func_psp_0892E9B0();
    func_psp_0892A2D8();
    GameEntrypoint();
    func_psp_0892A3D4();
    func_psp_0892E9E4();
    func_psp_08933BA0();
    sceGuTerm();
    func_psp_08919C4C();
    func_psp_0891A104();
    func_psp_089375A0();
    func_psp_0892FAA8(0, "disc0:/PSP_GAME/SYSDIR/BOOT.BIN");
    func_psp_0892FA84(g_UserLanguage);
    func_psp_0892FCA8(GU_PSM_5551);
    func_psp_0892FC80();
    return 0;
}
