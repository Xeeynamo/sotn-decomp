// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game_psp.h>

// https://pspdev.github.io/pspsdk/
#define PSP_LEGACY_TYPES_DEFINED // avoid processing psptypes.h
#include <pspctrl.h>
#include <pspgu.h>
#include <pspthreadman.h>
#include <psputility_modules.h>
#include <psputility_sysparam.h>
#include <psxsdk/libgpu.h>

typedef enum {
    SCREEN_MODE_ZERO,
    SCREEN_MODE_ONE,
} ScreenMode;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32* unk10;
} Unk08919CF4;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Unk08919D98;

typedef struct {
    s32 x;
    s32 y;
} Unk08C4218C;

typedef struct {
    s32 unk0;
    float unk4;
    float unk8;
    float unkC;
} Unk0891B118;

typedef struct {
    float unk0;
    float unk4;
    s32 unk8;
    float unkC;
    float unk10;
    float unk14;
} Unk0891D9F4;

extern s32 D_psp_0893CED0;
extern s32 D_psp_0893CF74[];
extern char D_psp_08946410[];
extern s32 D_psp_08946424;
extern s32 D_psp_08946430;
extern s32 D_psp_0894643C;
extern s32 D_psp_08946448;
extern char D_psp_0894644C[];
extern char D_psp_08946458[];
extern char D_psp_08946468[];
extern char D_psp_08946478[];
extern char D_psp_08946494[];
extern s32 /*?*/ D_psp_089464B0;
extern s32 D_psp_089464D0;
extern u32 D_psp_089464D4;
extern s32 D_psp_089464D8; // screen_w
extern s32 D_psp_089464DC; // screen_h
extern float D_psp_089464E0;
extern float D_psp_089464E4;
extern s32 D_psp_089464E8;
extern s32 D_psp_089464EC;
extern s32 D_psp_089464F0;
extern const char D_psp_089464F4[];
extern const char D_psp_089464F8[];
extern float D_psp_089464FC;
extern float D_psp_08946500;
extern s32 D_psp_08946504;
extern s32 (*D_psp_08946508[])(OT_TYPE*);
extern char D_psp_0894654C[];
extern char* D_psp_08946580[];
extern char* D_psp_089465A0[];
extern char D_psp_089465B4[];
extern char D_psp_089465C8[];
extern char D_psp_089465DC[];
extern char D_psp_089465EC[];
extern char D_psp_089465F8[];
extern char D_psp_08946608[];
extern char D_psp_08946614[];
extern char D_psp_08946620[];
extern char D_psp_08946630[];
extern char D_psp_08946644[];
extern char D_psp_08946654[];
extern char D_psp_08946664[];
extern char D_psp_08946670[];
extern char D_psp_0894667C[];
extern char D_psp_08946684[];
extern char D_psp_08946688;
extern u8 D_psp_089466A0[];
extern SceCtrlData D_psp_08B41F40;
extern SceCtrlData D_psp_08B41F50;
extern u16 D_psp_08B41F60;
extern u8* D_psp_08B41F64;
extern s32 D_psp_08B41F68;
extern s32 D_psp_08B41F9C;
extern s32 D_psp_08B41FB4;
extern s32 D_psp_08B41FB8;
extern s32 D_psp_08B41FBC;
extern s32 D_psp_08B41FC0;
extern s32 D_psp_08B41FD0; // exit callback ID
extern s32 D_psp_08B41FE0;
extern s32 D_psp_08B42000; // kernel thread ID
extern s32 D_psp_08B42044;
extern s32 D_psp_08B42048;
extern int D_psp_08B4204C; // button swap
extern s32 D_psp_08B42050;
extern s32 D_psp_08B42054;
extern s32 g_UserLanguage;
extern s32 D_psp_08B4205C;
extern s32 D_psp_08B42060;
extern s32 D_psp_08B42064;
extern s32 D_psp_08B42068;
extern s32 D_psp_08B4206C;
extern u8 D_psp_08B42080[0x20][0x8000];
extern s32 D_psp_08C42080[0x20];
extern u8* D_psp_08C42100[0x20];
extern u32 D_psp_08C42180;
extern void (*D_psp_08C42184)();
extern u32 D_psp_08C42188;
extern Unk08C4218C D_psp_08C4218C[];
extern u8 D_psp_08C429C0[][0x200];
extern s32 D_psp_08C629C0;
extern u32 D_psp_08C629C4;
extern s32 D_psp_08C629C8;
extern s32 D_psp_08C629CC;
extern RECT D_psp_08C629D0;
extern DISPENV D_psp_08C629D8;
extern DRAWENV D_psp_08C629EC;
extern s32 D_psp_08C62A30; // screen_mode
extern s32 D_psp_08C62A34; // screen_center_x
extern s32 D_psp_08C62A38; // screen_center_y
extern s32 D_psp_08C62A3C;
extern s32 D_psp_08C62A40;
extern s32 D_psp_08C62A44;
extern u32 D_psp_08C62A48;
extern s32 D_psp_08C62A4C;
extern s32 D_psp_08C62A50;
extern s32 D_psp_08C62A54;
extern s32 D_psp_08C62A58;
extern s32 D_psp_08C62A5C;
extern s32 D_psp_08C62A60;
extern s32 D_psp_08C62A64;
extern s32 D_psp_08C62A70;
extern OT_TYPE* D_psp_08C62A74;
extern char D_psp_08C62A78[0x20];
extern s8 D_psp_08C62A98;
extern s32 D_psp_08C62A9C;
extern s32 D_psp_08C62AA0;
extern s32 D_psp_08C62AA4;
extern bool D_psp_08C62AA8;
extern Unk08C4218C D_psp_08C62AAC;
extern u16 D_psp_08C62AB4;
extern u8* D_psp_08C62AB8;
extern u16 D_psp_08C62ABC[];
extern u16 D_psp_08C62CBC[];
extern s32 D_psp_08C62EBC;
extern s32 D_psp_08C62EC0;
extern char D_psp_08C62EC4[];
extern s32 D_psp_08C630C4;
extern s32 D_psp_08C630C8;
extern u32 D_psp_08C630CC;
extern s32 D_psp_08C630D0;
extern s32 D_psp_08C630E0;
extern char D_psp_08C630E4[];
extern s32 D_psp_08C63B24;
extern u8 g_BmpCastleMap[0x8000];
extern u16 g_Clut[3][0x1000];
#define g_IsTimeAttackUnlocked (*((s32*)0x091FC418))

void* memalign(size_t, size_t);
void func_psp_08919C4C(void);
u32 func_psp_08919BA8(void);
void func_psp_0891AEC8(void);
void func_psp_0891FC64(void);
void func_psp_089262C4(void);
s32 func_psp_08919F70(void);
void GameEntrypoint(void);
void func_psp_0891ACBC(void);
s32 func_psp_08933F7C(u8, u8);
void func_psp_08919D98(Unk08919D98* arg0);
void func_psp_0891A6A8(s32 screen_mode);
extern void func_psp_0891B538(s32 arg0);
extern void func_psp_0891B570(int arg0, int arg1);
extern void func_psp_089113A8(s32 arg0, u8 arg1);
static void func_psp_0891B6FC(void);
void func_psp_08934D20(Unk08919D98* arg0);
s32 func_psp_0893277C(void);
void sceGuDebugPrint(int x, int y, unsigned int color, const char* msg);
void func_psp_089117F4(s32, s32, s32, s32, s32, s32, u8*, s32, s32, s32, u8*);
static void func_psp_0891CD28(u_long* p, s32 x, s32 y);
static void func_psp_0891CEB8(s32 x, s32 y);

void _init(void) {}

void _fini(void) {}

void func_psp_08919A0C(void) {
    sceCtrlSetSamplingMode(1);
    sceCtrlReadBufferPositive(&D_psp_08B41F40, 1);
    sceCtrlReadBufferPositive(&D_psp_08B41F50, 1);
}

static void func_psp_08919A58(void) {
    u32 buttons = 0;
    sceCtrlPeekBufferPositive(&D_psp_08B41F40, 1);
    if (func_psp_08932790()) {
        D_psp_08B41F40.Buttons &=
            ~(PSP_CTRL_UP | PSP_CTRL_RIGHT | PSP_CTRL_DOWN | PSP_CTRL_LEFT);
        if (!(D_psp_08B41F40.Buttons & PSP_CTRL_HOLD)) {
            buttons = func_psp_08933F7C(D_psp_08B41F40.Lx, D_psp_08B41F40.Ly);
        }
        if (buttons) {
            sceKernelPowerTick(6);
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

u32 func_psp_08919BA8(void) {
    u32 buttons;
    func_psp_08919A58();
    buttons = D_psp_08B41F40.Buttons & 0xFFFF;
    return buttons;
}

u32 PadRead_PSP(void) { return func_psp_08919BA8(); }

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
    arg0->unk10 = &D_psp_0893CED0;
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
    if (arg0->unk0) {
        sceKernelVolatileMemUnlock(0);
        sceKernelDelayThreadCB(1);
        arg0->unk0 = 0;
        arg0->unk4 = 0;
        arg0->unk8 = 0;
    }
}

static u8* func_psp_08919DF4(u8* arg0) {
    return (u8*)func_psp_08932978(&D_psp_08B41F9C);
}

static u8* func_psp_08919E1C(u8* arg0) {
    return (u8*)func_psp_08932994(&D_psp_08B41F9C);
}

static void func_psp_08919E44() { func_psp_08932994(&D_psp_08B41F9C); }

static s32 func_psp_08919E6C(s32 arg0, u8* src) {
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

static void func_psp_08919F28(void) {
    D_psp_08B41FB4 = 0;
    D_psp_08B41FB8 = 0;
    D_psp_08B41FBC = 0;
}

static void func_psp_08919F48(void) {
    D_psp_08B41FB4 = sceKernelGetSystemTimeLow();
}

static s32 func_psp_08919F70(void) {
    D_psp_08B41FB8 = sceKernelGetSystemTimeLow();
    D_psp_08B41FBC = D_psp_08B41FB8 - D_psp_08B41FB4;
    return D_psp_08B41FBC;
}

static s32 exit_func(int count, int arg1, void* arg2) {
    func_psp_08933BA0();
    func_psp_0892A3D4();
    func_psp_0892E9E4();
    sceKernelExitGame();
    return 0;
}

static s32 func_psp_08919FF8(void) {
    D_psp_08B41FD0 = sceKernelCreateCallback(D_psp_08946410, exit_func, NULL);
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

    printf(D_psp_0894644C);
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
    D_psp_08B41FE0 =
        sceKernelCreateEventFlag(D_psp_08946458, PSP_EVENT_WAITMULTIPLE, 0, 0);
    sceKernelChangeCurrentThreadAttr(0, PSP_THREAD_ATTR_VFPU);
    func_psp_0891B400();
    func_psp_08937560();
    sceCtrlSetSamplingCycle(0);
    sceGuSetCallback2(GU_CALLBACK_FINISH, &func_psp_0891B538);
    func_psp_08904408(0, &func_psp_0891B570, 0);
    func_psp_08919C00(0x480000);
    func_psp_0891273C();
    func_psp_08919A0C();
    func_psp_0891ACBC();
    func_psp_08930324();
    func_psp_0891A6A8(SCREEN_MODE_ZERO);
    printf(D_psp_08946468);
    sceGuDisplay(GU_DISPLAY_ON);
    func_psp_08910044();
    sceGuSync(0, 0);
    printf(D_psp_08946478);
    func_psp_0891979C(4);
    printf(D_psp_08946494);
    func_psp_0891A14C();
    func_psp_0891A6A8(
        func_psp_08932754() == 0 ? SCREEN_MODE_ONE : SCREEN_MODE_ZERO);
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
    func_psp_0892FAA8(0, &D_psp_089464B0);
    func_psp_0892FA84(g_UserLanguage);
    func_psp_0892FCA8(1);
    func_psp_0892FC80();
    return 0;
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0891A608);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0891A650);

static void func_psp_0891A6A8(s32 screen_mode) {
    D_psp_08C62A30 = screen_mode;
    switch (D_psp_08C62A30) {
    case SCREEN_MODE_ZERO:
        D_psp_089464D8 = 362;
        D_psp_089464DC = 272;
        break;
    case SCREEN_MODE_ONE:
        D_psp_089464D8 = 320;
        D_psp_089464DC = 240;
        break;
    }
    D_psp_08C62A34 = (480 - D_psp_089464D8) / 2;
    D_psp_08C62A38 = (272 - D_psp_089464DC) / 2;
    D_psp_089464E8 = 2;
}

void func_psp_0891A790(void) {
    s32 i;

    for (i = 0; i < LEN(D_psp_08C42080); i++) {
        D_psp_08C42080[i] = -1;
        D_psp_08C42100[i] = D_psp_08B42080[i];
    }
}

void func_psp_0891A800(void) {
    s32 i;

    for (i = 0; i < LEN(D_psp_08C42080); i++) {
        if (D_psp_08C42080[i] >= 0) {
            D_psp_08C42080[i] = 1;
        }
    }
}

static void func_psp_0891A868(s32 arg0, s32 arg1) {
    s32 i;
    u8* addr;

    arg0 &= 0x1F;
    if (arg1) {
        D_psp_08C42080[arg0] = 1;
        D_psp_08C42100[arg0] = NULL;
    } else {
        D_psp_08C42080[arg0] = -1;
        D_psp_08C42100[arg0] = D_psp_08B42080[arg0];
    }
    addr = (u8*)((long)sceGeEdramGetAddr() + 0x12E200);
    for (i = 0; i < LEN(D_psp_08C42080); i++) {
        if (D_psp_08C42080[i] >= 0) {
            D_psp_08C42100[i] = addr;
            addr += 0x8000;
        }
    }
}

static void func_psp_0891A99C(s32 arg0) {
    arg0 &= 0x1F;
    if (D_psp_08C42080[arg0] >= 0) {
        D_psp_08C42080[arg0 & 0x1F]++;
    }
}

static char* func_psp_0891AA00(void) {
    s32 i;

    D_psp_08C62A98 = 0;
    for (i = 0; i < LEN(D_psp_08C42080); i++) {
        if (D_psp_08C42080[i] < 0) {
            D_psp_08C62A78[i] = 'X';
        } else if (D_psp_08C42080[i] == 0) {
            D_psp_08C62A78[i] = '-';
        } else {
            D_psp_08C62A78[i] = 'O';
        }
    }
    return D_psp_08C62A78;
}

static u8* func_psp_0891AAC8(s32 arg0) { return D_psp_08C42100[arg0 & 0x1F]; }

static void func_psp_0891AAF8() {
    s32 i;

    if (D_psp_08C62A44) {
        sceGuDebugPrint(0, 0x100, 0xFFFFFFFF, func_psp_0891AA00());
    }
    for (i = 0; i < LEN(D_psp_08C42080); i++) {
        if (D_psp_08C42080[i] > 0) {
            func_psp_089117F4(1, 0, 0, 0x40, 0x100, 0x40, D_psp_08B42080[i], 0,
                              0, 0x40, func_psp_0891AAC8(i));
            D_psp_08C42080[i] = 0;
        }
    }
}

static void func_psp_0891ABE4(void) { D_psp_08C62A9C = D_psp_08C62A9C ? 0 : 1; }

static u8* func_psp_0891AC24(void) {
    return (u8*)((long)sceGeEdramGetAddr() + 0xEC000 + D_psp_08C62A9C * 0x200);
}

static u8* func_psp_0891AC60(void) {
    return (u8*)((long)sceGeEdramGetAddr() + 0xEC000 +
                 (D_psp_08C62A9C ? 0 : 1) * 0x200);
}

static void func_psp_0891ACBC(void) {
    func_psp_0891B6FC();
    D_psp_08C629C0 = 0;
    D_psp_08C629C4 = 0;
    D_psp_08C629C8 = 0;
    D_psp_08C629CC = 0;
    func_psp_0891A608();
    D_psp_08C62A40 = 0;
    D_psp_089464D0 = -1;
    D_psp_089464D4 = -1;
    D_psp_08C42180 = 0;
    D_psp_08C42184 = NULL;
    D_psp_08C42188 = 0;
    func_psp_0891A790();
    func_psp_0891A800();
    func_psp_0891A6A8(0);
    func_psp_0891A868(24, 1);
    func_psp_0891A868(8, 1);
    func_psp_0891A868(9, 1);
    func_psp_0891A868(10, 1);
    func_psp_0891A868(11, 1);
    func_psp_0891A868(12, 1);
    func_psp_0891A868(13, 1);
    func_psp_0891A868(14, 1);
    func_psp_0891A868(15, 1);
    func_psp_08911C3C(0, 0, 0);
    func_psp_0891A650();
}

void func_psp_0891AE04(void) {
    func_psp_0891A868(1, 1);
    func_psp_0891A868(2, 1);
    func_psp_0891A868(3, 1);
    func_psp_0891A868(4, 1);
    D_psp_08C62AA0 = 1;
}

void func_psp_0891AE68(void) {
    func_psp_0891A868(1, 0);
    func_psp_0891A868(2, 0);
    func_psp_0891A868(3, 0);
    func_psp_0891A868(4, 0);
    D_psp_08C62AA0 = 0;
}

void func_psp_0891AEC8(void) {
    D_psp_08B41FC0 = D_psp_08B41FC0 ? 0 : 1;
    sceGuSwapBuffers();
    if (D_psp_08C62A58) {
        D_psp_08C62A64 = func_psp_08919F70();
        func_psp_08919F28();
        func_psp_08919F48();
    }
}

void func_psp_0891AF48(s32 arg0) {
    s32 base_addr;

    switch (arg0) {
    case 1:
        D_psp_08C62A40 = 1;
        func_psp_08910A20((u8*)sceGeEdramGetAddr() + 0xCC000, 0x100);
        func_psp_08910944(GU_NEAREST, GU_NEAREST);
        break;
    case 3:
        D_psp_08C62A40 = 3;
        func_psp_08910A20((u8*)sceGeEdramGetAddr() + 0x12C200, 0x40);
        func_psp_08910944(GU_NEAREST, GU_NEAREST);
        break;
    case 2:
        D_psp_08C62A40 = 2;
        func_psp_08910A20(func_psp_0891AC24(), 0x200);
        func_psp_08910944(GU_NEAREST, GU_NEAREST);
        break;
    default:
    case 0:
        D_psp_08C62A40 = 0;
        if (D_psp_08B41FC0 != 0) {
            base_addr = 0x44000;
        } else {
            base_addr = 0;
        }
        func_psp_08910A20((u8*)sceGeEdramGetAddr() + base_addr, 0x200);
        func_psp_08910944(GU_LINEAR, GU_LINEAR);
        break;
    }
}

void func_psp_0891B0BC(s32 arg0) { D_psp_089464F0 = arg0; }

void func_psp_0891B0DC(s32 x, s32 y) {
    D_psp_08C62AA8 = true;
    D_psp_08C62AAC.x = x;
    D_psp_08C62AAC.y = y;
}

s32 func_psp_0891B118(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Unk0891B118 a[2];

    a[0].unk4 = arg0;
    a[0].unk8 = arg1;
    a[1].unk4 = arg2;
    a[1].unk8 = arg3;
    if (a[0].unk4 > a[1].unk4) {
        a[0].unk4++;
    }
    a[0].unkC = a[1].unkC = 1.0f;
    a[0].unk0 = a[1].unk0 = arg4;
    func_psp_08912008();
    func_psp_08910A80(a, 2, sizeof(Unk0891B118), GU_LINES, GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    return 0;
}

s32 func_psp_0891B1F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (D_psp_08B42068 == 1) {
        func_psp_0891B118(arg0, arg1, arg2 - 1, arg1, arg4);
        func_psp_0891B118(arg2 - 1, arg1, arg2 - 1, arg3 - 1, arg4);
        func_psp_0891B118(arg2 - 1, arg3 - 1, arg0, arg3 - 1, arg4);
        func_psp_0891B118(arg0, arg3 - 1, arg0, arg1, arg4);
    }
    return 0;
}

s32 func_psp_0891B2CC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Unk0891B118 a[4];

    a[0].unk4 = arg0;
    a[0].unk8 = arg1;
    a[1].unk4 = arg0 + arg2;
    a[1].unk8 = arg1;
    a[2].unk4 = arg0;
    a[2].unk8 = arg1 + arg3;
    a[3].unk4 = arg0 + arg2;
    a[3].unk8 = arg1 + arg3;
    a[0].unkC = a[1].unkC = a[2].unkC = a[3].unkC = 1.0f;
    a[1].unk0 = a[0].unk0 = a[3].unk0 = a[2].unk0 = arg4;
    func_psp_08912008();
    func_psp_089113A8(-1, 0x80);
    func_psp_08910A80(a, 4, sizeof(Unk0891B118), GU_TRIANGLE_STRIP, GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    return 0;
}

s32 func_psp_0891B400(void) {
    if (~D_psp_089464D4 > 0) {
    }
    D_psp_08C42180 = 0;
    D_psp_089464D4 = sceDisplayGetVcount();
    return D_psp_089464D4;
}

s32 DrawSync(s32 arg0) {
    if (D_psp_08C62A44) {
        if (sceGuSync(GU_SYNC_FINISH, GU_SYNC_NOWAIT) == 1) {
            sceGuDebugPrint(472, 0, 0xFFFFFFFF, D_psp_089464F4);
        } else {
            sceGuDebugPrint(472, 0, 0xFFFFFFFF, D_psp_089464F8);
        }
    }
    if (arg0 == 0) {
        if (D_psp_08C62A58) {
            D_psp_08C62A5C = func_psp_08919F70();
        }
        sceGuSync(GU_SYNC_FINISH, GU_SYNC_WAIT);
        return 0;
    }
    return sceGuSync(GU_SYNC_FINISH, GU_SYNC_NOWAIT);
}

s32 func_psp_0891B528() { return D_psp_08C42180; }

void func_psp_0891B538(s32 arg0) {
    if (D_psp_08C62A58 != 0) {
        D_psp_08C62A60 = func_psp_08919F70();
    }
}

void func_psp_0891B570(int arg0, int arg1) {
    D_psp_08C42180++;
    if (D_psp_08C42184 != NULL) {
        D_psp_08C42184();
    }
}

s32 VSync(s32 arg0) {
    s32 vCount;
    if (arg0 == 0) {
        sceDisplayWaitVblankStartCB();
        D_psp_089464D0 = sceDisplayGetVcount();
    } else if (arg0 == 1) {
        vCount = sceDisplayGetVcount();
        return D_psp_089464D0 - vCount;
    } else if (arg0 > 1) {
        while (arg0) {
            sceDisplayWaitVblankStartCB();
            D_psp_089464D0 = sceDisplayGetVcount();
            arg0--;
        }
    } else {
        vCount = sceDisplayGetVcount();
        return vCount - D_psp_089464D4;
    }
    return 0;
}

s32 ResetGraph(s32 mode) {
    if (mode == 0) {
        D_psp_08C62A48 = 0;
    } else {
        D_psp_08C62A48 += mode;
    }
    return 0;
}

static void func_psp_0891B6FC() { D_psp_08C629C0 = 0; }

static s32 func_psp_0891B70C(s32 x, s32 y) {
    s32 i;

    for (i = 0; i < D_psp_08C629C0; i++) {
        if (x == D_psp_08C4218C[i].x && y == D_psp_08C4218C[i].y) {
            return i;
        }
    }
    return -1;
}

static s32 func_psp_0891B7A0(s32 x, s32 y, s32 w, void* ptr) {
    s32 var_s1;
    Unk08C4218C* var_s0;

    if ((var_s1 = func_psp_0891B70C(x, y)) < 0) {
        if (D_psp_08C629C0 < 0x100) {
            var_s1 = D_psp_08C629C0;
            D_psp_08C629C0 = var_s1 + 1;
        } else {
            return 0;
            var_s0 = var_s0; // FAKE!
        }
    }
    var_s0 = &D_psp_08C4218C[var_s1];
    var_s0->x = x;
    var_s0->y = y;
    memcpy(D_psp_08C429C0[var_s1], ptr, w * 2);
    return 1;
}

static u16 GetClut(s32 x, s32 y) {
    s32 temp_v0 = func_psp_0891B70C(x, y);
    if (temp_v0 >= 0) {
        return (u16)temp_v0 | 0x8000;
    } else {
        return getClut(x, y);
    }
}

u8* func_psp_0891B8F0(u16 arg0, s32 arg1, s32 arg2) {
    Unk08C4218C p;
    u16 clut;

    if (D_psp_08C62AB4 == arg0) {
        return D_psp_08C62AB8;
    }
    if (!(arg0 & 0x8000)) {
        p.y = (arg0 & 0x3F) * 0x10;
        p.x = arg0 >> 6;
        if ((arg1 == 1) && (arg2 != 0)) {
            clut = GetClut(p.y, p.x);
            if (clut & 0x8000) {
                D_psp_08C62AB8 = D_psp_08C429C0[clut & 0x7FFF];
            } else {
                func_psp_0891CEB8(p.y, p.x);
                D_psp_08C62AB8 = D_psp_08C429C0[GetClut(p.y, p.x) & 0x7FFF];
            }
        } else {
            D_psp_08C62AB8 =
                &D_psp_08B42080[(p.y / 0x40) + (p.x / 0x100) * 0x10]
                               [(p.y % 0x40) * 2 + (p.x % 0x100) * 0x80];
        }
    } else {
        D_psp_08C62AB8 = D_psp_08C429C0[arg0 & 0x7FFF];
    }
    D_psp_08C62AB4 = arg0;
    return D_psp_08C62AB8;
}

void func_psp_0891BB18(RECT* rect, u_long* p, s32 width) {
    u16* dst = (u16*)p;
    s32 x1 = rect->x + rect->w;
    s32 x0 = rect->x;

    while (x0 < x1) {
        s32 dx = 0x40 - (x0 % 0x40);
        if (x1 < (x0 + dx)) {
            dx = x1 - x0;
        }

        memcpy(&D_psp_08B42080[x0 / 0x40 + (rect->y / 0x100) * 0x10]
                              [(x0 % 0x40) * 2 + (rect->y % 0x100) * 0x80],
               &dst[x0 - rect->x], dx * 2);
        x0 += dx;
    }
}

s32 func_psp_0891BCA0(RECT* rect, u_long* p, s32 width, s32 arg3) {
    s32 sp3C;
    s32 x0, y0;
    s32 x1, y1;
    s32 sp34;
    u8* ptr;
    s32 i;
    u8* dst;
    u8* src;

    ptr = (u8*)p;
    if (rect->h == 1) {
        func_psp_0891BB18(rect, p, width);
        return 0;
    }
    x1 = rect->x + rect->w;
    y1 = rect->y + rect->h;
    if (arg3) {
        sp34 = 0x100;
    } else {
        sp34 = 0x100;
    }
    sp3C = sp34;
    y0 = rect->y;
    while (y0 < y1) {
        s32 dy = sp3C - (y0 % sp3C);
        if (y0 + dy > y1) {
            dy = y1 - y0;
        }
        x0 = rect->x;
        while (x0 < x1) {
            s32 dx = 0x40 - (x0 % 0x40);
            if (x1 < x0 + dx) {
                dx = x1 - x0;
            }
            dx = dx * 2;
            func_psp_0891A99C(x0 / 0x40 + (y0 / 0x100) * 0x10);
            dst = &D_psp_08B42080[x0 / 0x40 + (y0 / 0x100) * 0x10]
                                 [(x0 % 0x40) * 2 + (y0 % 0x100) * 0x80];
            src = &ptr[width * (y0 - rect->y) + (x0 - rect->x) * 2];
            for (i = 0; i < dy; i++) {
                memcpy(dst, src, dx);
                src += width;
                dst += 0x80;
            }
            x0 += dx / 2;
        }
        y0 += dy;
        if (y0 >= 0x200) {
            break;
        }
    }
    return 0;
}

s32 LoadImage(RECT* rect, u_long* p) {
    s32 var_a4;
    u16* var_a3;
    s32 w, h;
    s32 i;

    var_a4 = 0;
    if (rect->h == 1 &&
        (rect->w == 0x10 || rect->w == 0x100 || rect->w == 0x80)) {
        h = rect->h;
        w = rect->w;
        for (i = 0; i < w * h; i++) {
            if (((u16*)p)[i] == 0x8000) {
                D_psp_08C62ABC[i] = 0x8001;
            } else {
                D_psp_08C62ABC[i] = ((u16*)p)[i];
            }
        }
        var_a3 = D_psp_08C62ABC;
        p = (u_long*)var_a3;
    }
    if (rect->h == 1 && rect->w == 0x100) {
        func_psp_0891B7A0(rect->x, rect->y, rect->w, p);
    }
    return func_psp_0891BCA0(rect, p, rect->w * 2, var_a4);
}

void func_psp_0891C1C0(RECT* rect, u_long* p) {
    func_psp_0891BCA0(rect, p, rect->w * 2, 0);
}

static int func_psp_0891C204(RECT* rect, u_long* p, s32 width, s32 arg3) {
    u8* ptr;
    s32 sp38;
    s32 sp34;
    s32 sp30;
    s32 var_fp;
    s32 size;
    s32 toRead;
    s32 y;
    s32 x;
    s32 var_s3;
    s32 i;
    u8* src;
    u8* dst;

    ptr = (u8*)p;
    if (arg3) {
        sp34 = 0x100;
    } else {
        sp34 = 0x100;
    }
    sp38 = sp34;
    y = rect->y;
    while (y < rect->y + rect->h) {
        x = rect->x;
        while (x < rect->x + rect->w) {
            if (rect->x + rect->w - x < 0x40) {
                sp30 = rect->x + rect->w - x;
            } else {
                sp30 = 0x40;
            }
            var_s3 = sp30;
            if (x % 0x40) {
                if (var_s3 < 0x40 - (x % 0x40)) {
                    var_fp = var_s3;
                } else {
                    var_fp = 0x40 - (x % 0x40);
                }
                var_s3 = var_fp;
            }
            var_s3 = var_s3 * 2;
            if (rect->y + rect->h - y < sp38) {
                size = rect->y + rect->h - y;
            } else {
                size = sp38;
            }
            toRead = size;
            src = &D_psp_08B42080[x / 0x40 + y / 0x100 * 0x10]
                                 [(x % 0x40) * 2 + (y % 0x100) * 0x80];
            dst = &ptr[width * (y - rect->y) + (x - rect->x) * 2];
            for (i = 0; i < toRead; i++) {
                memcpy(dst, src, var_s3);
                dst += width;
                src += 0x80;
            }
            x += var_s3 / 2;
        }
        y += sp38;
    }
    return 0;
}

s32 StoreImage(RECT* rect, u_long* p) {
    if (rect->y + rect->h > 0x200) {
    }
    if (rect->w == 0x100 && rect->h == 1) {
        func_psp_0891CD28(p, rect->x, rect->y);
        return 0;
    }
    return func_psp_0891C204(rect, p, rect->w * 2, 0);
}

static int func_psp_0891C668(RECT* rect, u8 r, u8 g, u8 b, s32 arg4) {
    s32 sp4C;
    s32 sp48;
    s32 sp44;
    s32 sp40;
    s32 size;
    s32 y;
    s32 toWrite;
    s32 x;
    s32 var_s5;
    s32 i;
    u8* data;
    u16 color;
    u16* var_s1;
    u16* var_s0;

    color = b >> 3 << 11 | g >> 2 << 5 | r >> 2;
    if (color) {
        color |= 0x8000;
    }
    if (arg4) {
        sp48 = 0x100;
    } else {
        sp48 = 0x100;
    }
    sp4C = sp48;
    y = rect->y;
    while (y < rect->y + rect->h) {
        x = rect->x;
        while (x < rect->x + rect->w) {
            if (rect->x + rect->w - x < 0x40) {
                sp44 = (rect->x + rect->w) - x;
            } else {
                sp44 = 0x40;
            }
            var_s5 = sp44;
            if (x % 0x40) {
                if (var_s5 < 0x40 - (x % 0x40)) {
                    sp40 = var_s5;
                } else {
                    sp40 = 0x40 - (x % 0x40);
                }
                var_s5 = sp40;
            }
            var_s5 = var_s5 * 2;
            if (rect->y + rect->h - y < sp4C) {
                size = rect->y + rect->h - y;
            } else {
                size = sp4C;
            }
            toWrite = size;
            func_psp_0891A99C(x / 0x40 + y / 0x100 * 0x10);
            data = &D_psp_08B42080[x / 0x40 + y / 0x100 * 0x10]
                                  [(x % 0x40) * 2 + (y % 0x100) * 0x80];
            for (i = 0; i < toWrite; i++) {
                var_s0 = (u16*)data;
                var_s1 = (u16*)(data + var_s5);
                while (var_s0 != var_s1) {
                    *var_s0 = color;
                    var_s0++;
                }
                data += 0x80;
            }
            x += var_s5 / 2;
        }
        y += sp4C;
    }
    return 0;
}

int ClearImage(RECT* rect, u_char r, u_char g, u_char b) {
    s32 var_s0 = 0;
    func_psp_0891C668(rect, r, g, b, var_s0);
}

s32 MoveImage(RECT* rect, s32 x, s32 y) {
    RECT load;
    u_long* ptr;
    s32 size;
    s32 w, h;

    size = rect->w * rect->h * 2;
    ptr = (u_long*)malloc(size);
    if (ptr) {
        StoreImage(rect, ptr);
        load.x = x;
        load.y = y;
        load.w = rect->w;
        load.h = rect->h;
        LoadImage(&load, ptr);
        free(ptr);
    }
    return 0;
}

static s32 func_psp_0891CB80(
    s32 x, s32 y, s32 w, s32 h, s32 dstx, s32 dsty, s32 unused) {
    RECT rect;
    s32 var_s1;
    s32 i;

    for (i = 0; i < w; i += 0x100) {
        rect.x = x + i;
        rect.y = y;
        if (i + 0x100 < w) {
            var_s1 = 0x100;
        } else {
            var_s1 = w - i;
        }
        rect.w = var_s1;
        rect.h = h;
        MoveImage(&rect, dstx, dsty);
    }
    return 0;
}

u_short LoadClut(u_long* clut, s32 x, s32 y) {
    RECT rect;

    rect.x = x;
    rect.y = y;
    rect.w = 0x100;
    rect.h = 1;
    LoadImage(&rect, clut);
    return GetClut(x, y);
}

void func_psp_0891CCBC(u_long* clut, s32 x, s32 y) {
    RECT rect;

    rect.x = x;
    rect.y = y;
    rect.w = 0x10;
    rect.h = 1;
    LoadImage(&rect, clut);
    GetClut(x, y);
}

static void func_psp_0891CD28(u_long* p, s32 x, s32 y) {
    RECT rect;
    s32 index;

    if ((index = func_psp_0891B70C(x, y)) < 0) {
        rect.x = x;
        rect.y = y;
        rect.w = 0x100;
        rect.h = 1;
        func_psp_0891C204(&rect, p, rect.w * 2, 0);
        return;
    }
    memcpy(p, &D_psp_08C429C0[index], sizeof(*D_psp_08C429C0));
}

static void func_psp_0891CDE0(u16* clut, s32 x, s32 y) {
    u16* var_s1;
    s32 i;

    for (i = 0; i < 0x100; i++) {
        if (clut[i] == 0x8000) {
            D_psp_08C62ABC[i] = 0x8001;
        } else {
            D_psp_08C62ABC[i] = clut[i];
        }
    }
    var_s1 = D_psp_08C62ABC;
    clut = var_s1;
    func_psp_0891B7A0(x, y, 0x100, clut);
}

static void func_psp_0891CEB8(s32 x, s32 y) {
    RECT rect;

    rect.x = x;
    rect.y = y;
    rect.w = 0x100;
    rect.h = 1;
    func_psp_0891C204(&rect, (u_long*)D_psp_08C62CBC, rect.w * 2, 0);
    func_psp_0891CDE0(D_psp_08C62CBC, x, y);
}

u_short LoadTPage(u_long* pix, s32 tp, s32 abr, s32 x, s32 y, s32 w, s32 h) {
    RECT rect;

    rect.x = x;
    rect.y = y;
    rect.w = (tp == 0) ? w / 4 : (tp == 1) ? w / 2 : w;
    rect.h = h;
    LoadImage(&rect, pix);
    return ((tp & 3) << 7) | ((abr & 3) << 5) | ((y & 0x100) >> 4) |
           ((x & 0x3FF) >> 6) | ((y & 0x200) << 2);
}

void AddPrim(void* ot, void* p) { addPrim(ot, p); }

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", VSyncCallback);

OT_TYPE* ClearOTag(OT_TYPE* ot, int n) {
    P_TAG* pTag;
    s32 i;

    pTag = (P_TAG*)ot;

    for (i = 0; i < (n - 1); i++) {
        pTag->addr = (u32)(pTag + 1);
        pTag->len = 0;
        pTag->code = 0;
        pTag++;
    }
    pTag->len = 0;
    pTag->code = 0;
    pTag->addr = -1;
    return ot;
}

void SetSemiTrans(void* p, int abe) {
    P_TAG* pTag = p;
    if (abe) {
        pTag->code |= 0x40;
    } else {
        pTag->code &= ~0x40;
    }
}

void SetShadeTex(void* p, int tge) {
    P_TAG* pTag = p;
    if (tge) {
        pTag->code |= 0x80;
    } else {
        pTag->code &= ~0x80;
    }
}

void SetDrawMode(DR_MODE* p, s32 dfe, s32 dtd, s32 tpage, RECT* tw) {
    p->len = 2;
    p->code[0] =
        0x0C000000 | (dtd ? 0x200 : 0) | (dfe ? 0x400 : 0) | (tpage & 0x9FF);
    p->code[1] = (tw != NULL) ? (0xE2000000 | (((tw->y & 0xFF) >> 3) << 0xF) |
                                 (((tw->x & 0xFF) >> 3) << 0xA) |
                                 (((~(tw->h - 1) & 0xFF) >> 3) << 5) |
                                 ((~(tw->w - 1) & 0xFF) >> 3))
                              : 0;
}

void SetDrawEnv(DR_ENV* dr_env, DRAWENV* env) {
    dr_env->len = 8;
    dr_env->code = 0x10;
    if (env != NULL) {
        dr_env->clip.x = env->clip.x;
        dr_env->clip.y = env->clip.y;
        dr_env->clip.w = env->clip.w;
        dr_env->clip.h = env->clip.h;
        dr_env->ofs[0] = env->ofs[0];
        dr_env->ofs[1] = env->ofs[1];
        dr_env->tw.x = env->tw.x;
        dr_env->tw.y = env->tw.y;
        dr_env->tw.w = env->tw.w;
        dr_env->tw.h = env->tw.h;
        dr_env->tpage = env->tpage;
        dr_env->dtd = env->dtd;
        dr_env->dfe = env->dfe;
        dr_env->isbg = env->isbg;
        dr_env->r0 = env->r0;
        dr_env->g0 = env->g0;
        dr_env->b0 = env->b0;
    }
}

DRAWENV* PutDrawEnv(DRAWENV* env) {
    D_psp_08C629EC.clip = env->clip;
    D_psp_08C629EC.ofs = env->ofs;
    D_psp_08C629EC.tw = env->tw;
    D_psp_08C629EC.tpage = env->tpage;
    D_psp_08C629EC.dtd = env->dtd;
    D_psp_08C629EC.dfe = env->dfe;
    D_psp_08C629EC.isbg = env->isbg;
    D_psp_08C629EC.r0 = env->r0;
    D_psp_08C629EC.g0 = env->g0;
    D_psp_08C629EC.b0 = env->b0;
    D_psp_08C629EC.dr_env = env->dr_env;
    SetDrawEnv(&D_psp_08C629EC.dr_env, &D_psp_08C629EC);
    D_psp_08C629D0.x = env->clip.x;
    D_psp_08C629D0.y = env->clip.y;
    D_psp_08C629D0.w = env->clip.w;
    D_psp_08C629D0.h = env->clip.h;
    D_psp_08C629C4 = env->tpage;
    D_psp_08C629C8 = D_psp_08C629EC.ofs[0];
    D_psp_08C629CC = D_psp_08C629EC.ofs[1];
    func_psp_0891A608();
    return env;
}

DISPENV* PutDispEnv(DISPENV* env) {
    D_psp_08C629D8.disp = env->disp;
    D_psp_08C629D8.screen = env->screen;
    D_psp_08C629D8.isinter = env->isinter;
    D_psp_08C629D8.isrgb24 = env->isrgb24;
    D_psp_08C629D8.pad0 = env->pad0;
    D_psp_08C629D8.pad1 = env->pad1;
    switch (D_psp_08C62A30) {
    case 0:
        D_psp_089464D8 = 0x16A;
        D_psp_089464DC = 0x110;
        break;
    case 1:
        D_psp_089464D8 = 0x140;
        D_psp_089464DC = 0xF0;
        break;
    }
    D_psp_08C62A34 = (GU_SCR_WIDTH - D_psp_089464D8) / 2;
    D_psp_08C62A38 = (GU_SCR_HEIGHT - D_psp_089464DC) / 2;
    if ((D_psp_08C629D8.disp.w == 0x100) && (D_psp_08C629D8.disp.h == 0xF0)) {
        if (D_psp_08C62A30 == 1) {
            D_psp_08C62A34 += D_psp_08C629EC.clip.x;
            D_psp_08C62A38 += D_psp_08C629EC.clip.y;
            D_psp_089464DC = D_psp_08C629EC.clip.h;
            D_psp_089464D8 = (D_psp_08C62A30 == 0) ? 0x1A2 : 0x140;
        } else {
            D_psp_089464D8 = (D_psp_08C62A30 == 0) ? 0x1A2 : 0x140;
            D_psp_08C62A34 = (0x1E0 - D_psp_089464D8) / 2;
            D_psp_089464E0 = D_psp_089464E4 = 1.0f;
        }
    } else {
        if (!(D_psp_08C629D8.disp.w > 0x1E0) &&
            !(D_psp_08C629D8.disp.h > 0x100)) {
            D_psp_089464E0 = D_psp_089464E4 = 1.0f;
        } else {
            D_psp_089464E0 =
                (float)D_psp_089464D8 / (float)D_psp_08C629D8.disp.w;
            D_psp_089464E4 =
                (float)D_psp_089464DC / (float)D_psp_08C629D8.disp.h;
        }
    }
    return env;
}

void func_psp_0891D9F4(Unk0891D9F4* arg0, s32 arg1) {
    s32 i;

    if (arg1 == 2) {
        arg0->unkC = D_psp_08C62A34 + arg0->unkC * D_psp_089464E0;
        arg0->unk10 = D_psp_08C62A38 + arg0->unk10 * D_psp_089464E4;
        arg0++;
        arg0->unkC = D_psp_08C62A34 + (1.0f + arg0->unkC) * D_psp_089464E0;
        arg0->unk10 = D_psp_08C62A38 + (1.0f + arg0->unk10) * D_psp_089464E4;
    } else {
        for (i = 0; i < arg1; i++) {
            arg0->unkC = D_psp_08C62A34 + arg0->unkC * D_psp_089464E0;
            arg0->unk10 = D_psp_08C62A38 + arg0->unk10 * D_psp_089464E4;
            arg0++;
        }
    }
}

void func_psp_0891DB9C(Unk0891B118* arg0, s32 arg1) {
    s32 i;

    for (i = 0; i < arg1; i++) {
        arg0->unk4 = D_psp_08C62A34 + arg0->unk4 * D_psp_089464E0;
        arg0->unk8 = D_psp_08C62A38 + arg0->unk8 * D_psp_089464E4;
        arg0++;
    }
}

void func_psp_0891DC48(Unk0891B118* arg0, s32 arg1) {
    s32 i;

    for (i = 0; i < arg1; i++) {
        arg0->unk4 = D_psp_08C62A34 + arg0->unk4 * D_psp_089464E0;
        arg0->unk8 = D_psp_08C62A38 + arg0->unk8 * D_psp_089464E4;
        arg0++;
    }
}

DRAWENV* SetDefDrawEnv(DRAWENV* env, s32 x, s32 y, s32 w, s32 h) {
    env->clip.x = x;
    env->clip.y = y;
    env->clip.w = w;
    env->clip.h = h;
    env->ofs[0] = x;
    env->ofs[1] = y;
    env->tw.x = 0;
    env->tw.y = 0;
    env->tw.w = 0;
    env->tw.h = 0;
    env->tpage = 0;
    env->dtd = 1;
    env->dfe = 1;
    env->isbg = 0;
    env->r0 = 0;
    env->g0 = 0;
    env->b0 = 0;
    return env;
}

DISPENV* SetDefDispEnv(DISPENV* env, s32 x, s32 y, s32 w, s32 h) {
    env->disp.x = x;
    env->disp.y = y;
    env->disp.w = w;
    env->disp.h = h;
    env->screen.x = 0;
    env->screen.y = 0;
    env->screen.w = 0;
    env->screen.h = 0;
    env->isinter = 0;
    env->isrgb24 = 0;
    return env;
}

void func_psp_0891DE74(void) {
    s32 var_s1;
    s32 var_s2;
    Unk0891D9F4* p;

    var_s2 = 0;
    p = (Unk0891D9F4*)SP(0);
    var_s1 = D_psp_08C62A40;

    func_psp_0891AF48(0);
    func_psp_08910660(0);
    p[0].unk8 = p[1].unk8 = p[2].unk8 = p[3].unk8 = 0x80FFFFFF;
    func_psp_08911F24(0, D_psp_089464F0);
    func_psp_08911B7C();
    switch (D_psp_08B4206C) {
    case 0:
        break;
    case 1:
        p[0].unkC = p[0].unk10 = p[1].unk10 = p[2].unkC = 0.0f;
        p[1].unkC = p[2].unk10 = p[3].unkC = p[3].unk10 = 255.0f;
        p[0].unk14 = p[1].unk14 = p[2].unk14 = p[3].unk14 = 1.0f;
        p[0].unk0 = p[0].unk4 = p[1].unk4 = p[2].unk0 = 0.0f;
        p[1].unk0 = p[2].unk4 = p[3].unk0 = p[3].unk4 = 255.0f;
        func_psp_0891089C(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT);
        func_psp_08911990((s32)sceGeEdramGetAddr() + 0xCC000, 0x100);
        func_psp_08910A80(p, 4, sizeof(Unk0891D9F4), GU_TRIANGLE_STRIP, GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
        break;
    case 2:
        func_psp_08910660(1);
        func_psp_08910810(0, 0xA, 0xA, 0xFFFFFFFF, 0xFF808080);
        p[0].unk8 = p[1].unk8 = p[2].unk8 = p[3].unk8 = 0xFFFFFFFF;
        p[0].unkC = p[2].unkC = D_psp_08C62A34;
        p[0].unk10 = p[1].unk10 = D_psp_08C62A38;
        p[1].unkC = p[3].unkC = D_psp_08C62A34 + D_psp_089464D8;
        p[2].unk10 = p[3].unk10 = D_psp_08C62A38 + D_psp_089464DC;
        p[0].unk14 = p[1].unk14 = p[2].unk14 = p[3].unk14 = 1.0f;
        p[0].unk0 = p[0].unk4 = p[1].unk4 = p[2].unk0 = 0.0f;
        p[1].unk0 = D_psp_089464FC;
        p[2].unk4 = D_psp_08946500;
        p[3].unk0 = D_psp_089464FC;
        p[3].unk4 = D_psp_08946500;
        func_psp_0891089C(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT);
        func_psp_08911990(func_psp_0891AC24(), 0x200);
        func_psp_08910A80(p, 4, sizeof(Unk0891D9F4), GU_TRIANGLE_STRIP, GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
        break;
    case 3:
        p[0].unkC = p[0].unk10 = p[1].unk10 = p[2].unkC = 0.0f;
        p[1].unkC = p[3].unkC = 63.0f;
        p[2].unk10 = p[3].unk10 = 63.0f;
        p[0].unk14 = p[1].unk14 = p[2].unk14 = p[3].unk14 = 1.0f;
        p[0].unk0 = p[0].unk4 = p[1].unk4 = p[2].unk0 = 0.0f;
        p[1].unk0 = p[3].unk0 = 63.0f;
        p[2].unk4 = p[3].unk4 = 63.0f;
        func_psp_0891089C(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT);
        func_psp_08911990((s32)sceGeEdramGetAddr() + 0x12C200, 0x40);
        func_psp_08910A80(p, 4, sizeof(Unk0891D9F4), GU_TRIANGLE_STRIP, GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
        break;
    case 4:
        p[0].unkC = 0.0f;
        p[0].unk10 = 0.0f;
        p[1].unkC = 128.0f;
        p[1].unk10 = 0.0f;
        p[2].unkC = 0.0f;
        p[2].unk10 = 136.0f;
        p[3].unkC = 128.0f;
        p[3].unk10 = 136.0f;
        p[0].unk14 = p[1].unk14 = p[2].unk14 = p[3].unk14 = 1.0f;
        p[0].unk0 = 0.0f;
        p[0].unk4 = 0.0f;
        p[1].unk0 = 256.0f;
        p[1].unk4 = 0.0f;
        p[2].unk0 = 0.0f;
        p[2].unk4 = 272.0f;
        p[3].unk0 = 256.0f;
        p[3].unk4 = 272.0f;
        func_psp_0891089C(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT);
        func_psp_08911990((s32)sceGeEdramGetAddr() + 0xCC000, 0x100);
        func_psp_08910A80(p, 4, sizeof(Unk0891D9F4), GU_TRIANGLE_STRIP, GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
        p[0].unk10 += 136.0f;
        p[1].unk10 += 136.0f;
        p[2].unk10 += 136.0f;
        p[3].unk10 += 136.0f;
        p[1].unk0 = 512.0f;
        p[3].unk0 = 512.0f;
        func_psp_08911990(func_psp_0891AC24(), 0x200);
        func_psp_08910A80(p, 4, sizeof(Unk0891D9F4), GU_TRIANGLE_STRIP, GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
        break;
    }
    func_psp_0891AF48(var_s1);
}

void func_psp_0891E420(void) {
    s32 var_s1;
    Unk0891D9F4* p;

    var_s1 = 0;
    p = (Unk0891D9F4*)SP(0);

    func_psp_08911990(func_psp_0891AC24(), 0x200);
    func_psp_08910660(0);
    p[0].unk8 = p[1].unk8 = p[2].unk8 = p[3].unk8 = D_psp_08946504;
    p[0].unkC = p[2].unkC = D_psp_08C62A34;
    p[0].unk10 = p[1].unk10 = D_psp_08C62A38;
    p[1].unkC = p[3].unkC = D_psp_08C62A34 + D_psp_089464D8;
    p[2].unk10 = p[3].unk10 = D_psp_08C62A38 + D_psp_089464DC;
    p[0].unk14 = p[1].unk14 = p[2].unk14 = p[3].unk14 = 1.0f;
    p[0].unk0 = p[2].unk0 = D_psp_08C629EC.clip.x;
    p[0].unk4 = p[1].unk4 = D_psp_08C629EC.clip.y;
    p[1].unk0 = p[3].unk0 =
        D_psp_08C629EC.clip.x + (float)D_psp_08C629EC.clip.w;
    p[2].unk4 = p[3].unk4 =
        D_psp_08C629EC.clip.y + (float)D_psp_08C629EC.clip.h;
    func_psp_0891AF48(0);
    func_psp_08911F24(0, D_psp_089464F0);
    func_psp_08911B7C();
    func_psp_089109E4(GU_TFX_MODULATE, GU_TCC_RGBA, 1);
    func_psp_0891089C(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT);
    func_psp_08910A80(p, 4, sizeof(Unk0891D9F4), GU_TRIANGLE_STRIP, GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    func_psp_089109E4(GU_TFX_MODULATE, GU_TCC_RGBA, 0);
    func_psp_0891AF48(2);
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0891E638);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0891E840);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0891E944);

void func_psp_0891E994(OT_TYPE* p) {
    s32 sp5C;
    s32 sp58;
    s32 sp54;
    s32 sp50;
    u32 sp4C;
    s32 code;
    u8* temp_s5;
    s32 temp_v0;
    s32 var_fp;
    s32 i;
    s32 var_s4;
    s32 var_s3;
    OT_TYPE* var_s1;
    OT_TYPE* var_s6;
    u32 var_s7;

    if (p != (OT_TYPE*)-1) {
        D_psp_08C62A74 = p;
        func_psp_0891E840();
        if (D_psp_08C62AA8) {
            D_psp_08C62AA8 = false;
            temp_s5 = func_psp_0891AC24();
            if ((D_psp_08C62AAC.x == 0) && (D_psp_08C62AAC.y == 0x100)) {
                func_psp_089117F4(1, 0, 0, 0x100, 0x100, 0x200, temp_s5, 0, 0,
                                  0x100, (u8*)sceGeEdramGetAddr() + 0xCC000);
                for (i = 0; i < 0x20; i++) {
                    func_psp_0891A99C(i);
                }
            } else {
                var_s4 = 0;
                while (var_s4 < 0x100) {
                    func_psp_089117F4(
                        1, var_s4, 0, 0x40, 0xF0, 0x200, temp_s5, 0, 0, 0x40,
                        &D_psp_08B42080[(D_psp_08C62AAC.x + var_s4) / 0x40 +
                                        (D_psp_08C62AAC.y / 0x100) * 0x10]
                                       [((D_psp_08C62AAC.x + var_s4) % 0x40) *
                                            2 +
                                        (D_psp_08C62AAC.y % 0x100) * 0x80]);
                    var_s4 += 0x40;
                }
                for (i = 0; i < 0x20; i++) {
                    func_psp_0891A99C(i);
                }
            }
        }
        if (D_psp_08C62AA4 != 0) {
            D_psp_08C62AA4 = 0;
            var_s3 = 0;
            while (var_s3 < 0x40) {
                func_psp_089117F4(
                    1, var_s3, 0, 0x40, 0x100, 0x100,
                    (u8*)sceGeEdramGetAddr() + 0xCC000, 0, 0, 0x40,
                    &D_psp_08B42080[(var_s3 / 0x40) + 0x10]
                                   [(var_s3 % 0x40) * 2]);
                var_s3 += 0x40;
            }
            for (i = 0; i < 0x20; i++) {
                func_psp_0891A99C(i);
            }
        }
        func_psp_0891AAF8();
        func_psp_0891ABE4();
        if (D_psp_08C62A3C > 0) {
            func_psp_0891089C(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT);
            func_psp_0891B2CC(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT, 0x80000000);
            if (D_psp_08C62A3C > 0) {
                D_psp_08C62A3C--;
            }
        }
        if ((D_psp_08C629D8.disp.w > 0x100) || (D_psp_089464E8 > 0)) {
            func_psp_0891E638();
            if (D_psp_089464E8 > 0) {
                D_psp_089464E8--;
            }
        } else {
            sp50 = D_psp_08C62A40;
            switch (D_psp_08C62A30) {
            case 0:
                sp54 = 0x1A2;
                var_fp = 0x110;
                break;
            case 1:
                sp54 = 0x171;
                var_fp = 0xF0;
                break;
            }
            sp5C = (GU_SCR_WIDTH - sp54) / 2;
            sp58 = (GU_SCR_HEIGHT - var_fp) / 2;
            func_psp_0891AF48(0);
            func_psp_0891089C(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT);
            func_psp_0891B2CC(sp5C, sp58, sp54 - 1, var_fp - 1, 0x80000000);
            func_psp_0891AF48(sp50);
        }
        func_psp_0891FDC8(&D_psp_08C629EC.dr_env);
        D_psp_08C62EC0 = 0;
        D_psp_08C62A50 = 0;
        D_psp_08C62A54 = 0;
        var_s1 = p;
        var_s6 = NULL;
        while (var_s1 != NULL) {
            code = getcode(var_s1) & 0x3F;
            if ((code >= 0) && (code < 0x11) && (code != 0)) {
                D_psp_08946508[code](var_s1);
                if (code != 0) {
                    D_psp_08C62EC0++;
                }
            }
            if (getaddr(var_s1) == -1 || getaddr(var_s1) == NULL) {
                break;
            }
            var_s6 = var_s1;
            var_s1 = (OT_TYPE*)getaddr(var_s1);
        }
        if (D_psp_08C62A40 == 2) {
            func_psp_0891E420();
        }
        if (D_psp_08B4206C != 0) {
            func_psp_0891DE74();
        }
        if (D_psp_08C62EBC != 0) {
            func_psp_0891AF48(0);
            func_psp_0891089C(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT);
            func_psp_0891B2CC(0x130, 0, 0xB0, 0x70, 0x80000000);
        }
        if ((D_psp_08C62A58 != 0) && (D_psp_08C62A64 != 0)) {
            var_s7 = (D_psp_08C42180 != D_psp_08C42188)
                         ? (D_psp_08C42180 - D_psp_08C42188) * 0xF0
                         : 0xF0;
            func_psp_0891AF48(0);
            func_psp_0891089C(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT);
            func_psp_0891B118(0, 0, (D_psp_08C62A64 * var_s7) / D_psp_08C62A64,
                              0, 0x80FFFFFF);
            func_psp_0891B118(0, 1, (D_psp_08C62A5C * var_s7) / D_psp_08C62A64,
                              1, 0x800000FF);
            func_psp_0891B118(0, 2, (D_psp_08C62A60 * var_s7) / D_psp_08C62A64,
                              2, 0x8000FF00);
        }
        func_psp_0891AF48(0);
        func_psp_0891089C(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT);
        func_psp_08932228();
        func_psp_0891E944();
        if (D_psp_08C62A44 != 0) {
            sp4C = (D_psp_08C42180 != D_psp_08C42188)
                       ? 0x3C / (D_psp_08C42180 - D_psp_08C42188)
                       : 0;
            sprintf(D_psp_08C62EC4, D_psp_0894654C, D_psp_08C62A4C,
                    D_psp_08C62A48, D_psp_089464D8, D_psp_089464DC, sp4C);
            sceGuDebugPrint(0, 0x108, 0xFFFFFFFF, D_psp_08C62EC4);
        }
        D_psp_08C62A4C++;
        ResetGraph(0);
    }
}

void DrawOTag(OT_TYPE* p) {
    s32 sp4C;
    s32 sp48;
    s32 i;
    s32 temp_s2;
    s32 var_s3;
    s32 x;
    s32 y;

    D_psp_08C62A74 = p;
    if (func_psp_08919BA8() & 4) {
        sp4C = func_psp_08919BA8();
        var_s3 = 0;
        sp48 = -1;
        D_psp_08C62EBC = 1;
        while (var_s3 >= 0) {
            temp_s2 = func_psp_08919BA8();
            if ((sp4C == 0) && (temp_s2 != 0)) {
                if (temp_s2 & 0x4000) {
                    while (func_psp_08919BA8()) {
                        VSync(0);
                    }
                    D_psp_08C62EBC = 0;
                    func_psp_0891E994(p);
                    break;
                }
                if (temp_s2 & 0x10) {
                    var_s3 = (var_s3 + 11) % 12;
                }
                if (temp_s2 & 0x40) {
                    var_s3 = (var_s3 + 1) % 12;
                }
                if (var_s3 == 0xB) {
                    if (temp_s2 & 0x20) {
                        D_psp_08C630CC += 1;
                    }
                    if (temp_s2 & 0x80) {
                        D_psp_08C630CC += 0x230;
                    }
                    if (temp_s2 & 0x200) {
                        D_psp_08C630CC += 0x14;
                    }
                    if (temp_s2 & 0x100) {
                        D_psp_08C630CC += 0x21D;
                    }
                    D_psp_08C630CC = D_psp_08C630CC % 561;
                }
                if (temp_s2 & 0x2000) {
                    switch (var_s3) {
                    case 0:
                        g_IsTimeAttackUnlocked = g_IsTimeAttackUnlocked ? 0 : 1;
                        break;
                    case 1:
                        D_psp_08C630C4 = D_psp_08C630C4 ? 0 : 1;
                        break;
                    case 2:
                        D_psp_08C630C8 = D_psp_08C630C8 ? 0 : 1;
                        break;
                    case 3:
                        D_psp_08C62A30 = (D_psp_08C62A30 + 1) % 2;
                        func_psp_0891A6A8(D_psp_08C62A30);
                        break;
                    case 4:
                        D_psp_08C630E0++;
                        if (D_psp_08C630E0 > 6) {
                            D_psp_08C630E0 = 0;
                        }
                        break;
                    case 5:
                        D_psp_08C62A70 = D_psp_08C62A70 ? 0 : 1;
                        break;
                    case 6:
                        D_psp_08B42068 = D_psp_08B42068 ? 0 : 1;
                        break;
                    case 7:
                        D_psp_08B4206C =
                            (D_psp_08B4206C < 4) ? D_psp_08B4206C + 1 : 0;
                        break;
                    case 8:
                        D_psp_08C62A44 = D_psp_08C62A44 ? 0 : 1;
                        break;
                    case 9:
                        D_psp_08C62A58 = D_psp_08C62A58 ? 0 : 1;
                        break;
                    case 11:
                        func_9141878(D_psp_08C630CC);
                        break;
                    case 10:
                        D_psp_08C630D0 = D_psp_08C630D0 ? 0 : 1;
                        break;
                    }
                }
            }
            x = 0x130;
            y = 0;
            sprintf(D_psp_08C630E4, D_psp_089465B4);
            sceGuDebugPrint(x, y, 0xFFFFFFFF, D_psp_08C630E4);
            sprintf(D_psp_08C630E4, D_psp_089465C8,
                    D_psp_08946580[g_IsTimeAttackUnlocked ? 1 : 0]);
            sceGuDebugPrint(x + 0x10, y + 0x8, 0xFFFFFFFF, D_psp_08C630E4);
            sprintf(
                D_psp_08C630E4, D_psp_089465DC, D_psp_08946580[D_psp_08C630C4]);
            sceGuDebugPrint(x + 0x10, y + 0x10, 0xFFFFFFFF, D_psp_08C630E4);
            sprintf(
                D_psp_08C630E4, D_psp_089465EC, D_psp_08946580[D_psp_08C630C8]);
            sceGuDebugPrint(x + 0x10, y + 0x18, 0xFFFFFFFF, D_psp_08C630E4);
            sprintf(D_psp_08C630E4, D_psp_089465F8, D_psp_08C62A30);
            sceGuDebugPrint(x + 0x10, y + 0x20, 0xFFFFFFFF, D_psp_08C630E4);
            sprintf(D_psp_08C630E4, D_psp_08946608, D_psp_08C630E0);
            sceGuDebugPrint(x + 0x10, y + 0x28, 0xFFFFFFFF, D_psp_08C630E4);
            sprintf(
                D_psp_08C630E4, D_psp_08946614, D_psp_08946580[D_psp_08C62A70]);
            sceGuDebugPrint(x + 0x10, y + 0x30, 0xFFFFFFFF, D_psp_08C630E4);
            sprintf(
                D_psp_08C630E4, D_psp_08946620, D_psp_08946580[D_psp_08B42068]);
            sceGuDebugPrint(x + 0x10, y + 0x38, 0xFFFFFFFF, D_psp_08C630E4);
            sprintf(
                D_psp_08C630E4, D_psp_08946630, D_psp_089465A0[D_psp_08B4206C]);
            sceGuDebugPrint(x + 0x10, y + 0x40, 0xFFFFFFFF, D_psp_08C630E4);
            sprintf(
                D_psp_08C630E4, D_psp_08946644, D_psp_08946580[D_psp_08C62A44]);
            sceGuDebugPrint(x + 0x10, y + 0x48, 0xFFFFFFFF, D_psp_08C630E4);
            sprintf(
                D_psp_08C630E4, D_psp_08946654, D_psp_08946580[D_psp_08C62A58]);
            sceGuDebugPrint(x + 0x10, y + 0x50, 0xFFFFFFFF, D_psp_08C630E4);
            sprintf(D_psp_08C630E4, D_psp_08946664, D_psp_08C630D0);
            sceGuDebugPrint(x + 0x10, y + 0x58, 0xFFFFFFFF, D_psp_08C630E4);
            sprintf(D_psp_08C630E4, D_psp_08946670, D_psp_08C630CC);
            sceGuDebugPrint(x + 0x10, y + 0x60, 0xFFFFFFFF, D_psp_08C630E4);
            sprintf(
                D_psp_08C630E4, D_psp_0894667C, func_9141860(D_psp_08C630CC));
            sceGuDebugPrint(x + 0x10, y + 0x68, 0xFFFFFFFF, D_psp_08C630E4);
            func_psp_0892A8FC();
            if (func_psp_0891B528() & 0x20) {
                sceGuDebugPrint(
                    x, y + (var_s3 + 1) * 8, 0xFFFFFFFF, D_psp_08946684);
            }
            func_psp_0891E994(p);
            GsClearVcount();
            DrawSync(0);
            VSync(0);
            func_psp_0891AEC8();
            sp4C = temp_s2;
        }
        D_psp_08C62EBC = 0;
        D_psp_089464E8 = 2;
    } else {
        for (i = 0; i < D_psp_08C630E0; i++) {
            GsClearVcount();
            VSync(0);
        }
        func_psp_0891E994(p);
    }
}

void func_psp_0891FC64(void) {
    if (D_psp_08C62A74 != NULL) {
        DrawOTag(D_psp_08C62A74);
    } else {
        DrawOTag(NULL);
    }
}

void SetDispMask(int mask) {}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0891FCC0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0891FCF0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0891FD20);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0891FD74);

s32 func_psp_0891FDC8(DR_ENV* p) {
    DR_ENV* ptr;
    RECT rect;
    s32 x, y;

    ptr = p;

    D_psp_08C629EC.dr_env.tag = ptr->tag;
    D_psp_08C629EC.dr_env.len = ptr->len;
    D_psp_08C629EC.dr_env.r0 = ptr->r0;
    D_psp_08C629EC.dr_env.g0 = ptr->g0;
    D_psp_08C629EC.dr_env.b0 = ptr->b0;
    D_psp_08C629EC.dr_env.code = ptr->code;
    D_psp_08C629EC.dr_env.clip = ptr->clip;
    D_psp_08C629EC.dr_env.ofs = ptr->ofs;
    D_psp_08C629EC.dr_env.tw = ptr->tw;
    D_psp_08C629EC.dr_env.tpage = ptr->tpage;
    D_psp_08C629EC.dr_env.dtd = ptr->dtd;
    D_psp_08C629EC.dr_env.dfe = ptr->dfe;
    D_psp_08C629EC.dr_env.isbg = ptr->isbg;
    if ((ptr->ofs[0] == 0x40) && (ptr->clip.x == 0x40)) {
        D_psp_08C629C8 = 0x40;
    } else {
        D_psp_08C629C8 = 0;
    }
    D_psp_08C629CC = 0;
    func_psp_0891A608();
    x = 0;
    y = 0;
    rect = ptr->clip;
    if (D_psp_089464EC && ptr->ofs[1] == 0x100) {
        func_psp_0891AF48(1);
        rect.y -= ptr->ofs[1];
    } else if (ptr->ofs[0] == 0x200 && ptr->ofs[1] == 0x1C0) {
        func_psp_0891AF48(3);
        rect.x = 0;
        rect.y = 0;
    } else if (
        D_psp_08C629D8.disp.w <= 0x1E0 && D_psp_08C629D8.disp.h <= 0x100) {
        func_psp_0891AF48(2);
    } else {
        func_psp_0891AF48(0);
        x = D_psp_08C62A34;
        y = D_psp_08C62A38;
        rect.x *= D_psp_089464E0;
        rect.y *= D_psp_089464E4;
        rect.w *= D_psp_089464E0;
        rect.h *= D_psp_089464E4;
    }
    func_psp_0891089C(
        x + rect.x, y + rect.y, x + rect.x + rect.w, y + rect.y + rect.h);
    if (ptr->isbg == 1) {
        func_psp_0891B2CC(x + rect.x, y + rect.y, rect.w, rect.h,
                          GU_RGBA(ptr->r0, ptr->g0, ptr->b0, 0x80));
    }
    func_psp_08910634(D_psp_08C629EC.dtd ? 1 : 0);
    return 0;
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_089201E8);

s32 func_psp_08920488(void* p) {}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_08920498);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_089215A4);

s32 func_psp_08921A38(POLY_G4* p) {
    Unk0891B118 a[4];
    POLY_G4* ptr;
    u8 var_s1;

    ptr = p;

    if ((ptr->code & 0x40) >> 6) {
        var_s1 = 0x80;
        func_psp_089113A8((D_psp_08C629C4 >> 5) & 3, var_s1);
    } else {
        func_psp_089113A8(-1, 0x80);
    }
    a[0].unk4 = D_psp_08C629C8 + ptr->x0;
    a[0].unk8 = D_psp_08C629CC + ptr->y0;
    a[0].unkC = 1.0f;
    a[1].unk4 = D_psp_08C629C8 + ptr->x1;
    a[1].unk8 = D_psp_08C629CC + ptr->y1;
    a[1].unkC = 1.0f;
    a[2].unk4 = D_psp_08C629C8 + ptr->x2;
    a[2].unk8 = D_psp_08C629CC + ptr->y2;
    a[2].unkC = 1.0f;
    a[3].unk4 = D_psp_08C629C8 + ptr->x3;
    a[3].unk8 = D_psp_08C629CC + ptr->y3;
    a[3].unkC = 1.0f;
    a[0].unk0 = GU_RGBA(ptr->r0, ptr->g0, ptr->b0, 0x80);
    a[1].unk0 = GU_RGBA(ptr->r1, ptr->g1, ptr->b1, 0x80);
    a[2].unk0 = GU_RGBA(ptr->r2, ptr->g2, ptr->b2, 0x80);
    a[3].unk0 = GU_RGBA(ptr->r3, ptr->g3, ptr->b3, 0x80);
    if (D_psp_08C62A40 == 0) {
        func_psp_0891DB9C(a, 4);
    }
    func_psp_08912008();
    func_psp_08910A80(a, 4, sizeof(Unk0891B118), GU_TRIANGLE_STRIP, GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    func_psp_0891B1F8(a[0].unk4, a[0].unk8, a[3].unk4, a[3].unk8, 0x80FF0000);
    return 0;
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_08921D44);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_089225D8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_08922C14);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_089231F8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_08923FA4);

s32 func_psp_08925194(TILE* p) {
    Unk0891B118 a[4];
    TILE* ptr;
    u8 var_s1;

    ptr = p;

    if ((ptr->w == 0) || (ptr->h == 0)) {
        return 0;
    }
    if (D_psp_08C62A40 == 1) {
        return 0;
    }
    if ((ptr->code & 0x40) >> 6) {
        var_s1 = 0x80;
        if (((D_psp_08C629C4 >> 5) & 3) == 2) {
            var_s1 = (ptr->b0 + ptr->g0 + ptr->r0) / 3;
        }
        func_psp_089113A8((D_psp_08C629C4 >> 5) & 3, var_s1);
    } else {
        func_psp_089113A8(-1, 0x80);
    }
    a[0].unk4 = D_psp_08C629C8 + ptr->x0;
    a[0].unk8 = D_psp_08C629CC + ptr->y0;
    a[1].unk4 = D_psp_08C629C8 + ptr->x0 + ptr->w;
    a[1].unk8 = D_psp_08C629CC + ptr->y0;
    a[2].unk4 = D_psp_08C629C8 + ptr->x0;
    a[2].unk8 = D_psp_08C629CC + ptr->y0 + ptr->h;
    a[3].unk4 = D_psp_08C629C8 + ptr->x0 + ptr->w;
    a[3].unk8 = D_psp_08C629CC + ptr->y0 + ptr->h;
    a[0].unkC = a[1].unkC = a[2].unkC = a[3].unkC = 1.0f;
    a[0].unk0 = a[1].unk0 = a[2].unk0 = a[3].unk0 =
        GU_RGBA(ptr->r0, ptr->g0, ptr->b0, 0x80);
    if (D_psp_08C62A40 == 0) {
        func_psp_0891DB9C(a, 4);
    }
    func_psp_08912008();
    func_psp_08910A80(a, 4, sizeof(Unk0891B118), GU_TRIANGLE_STRIP, GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    func_psp_0891B1F8(a[0].unk4, a[0].unk8, a[1].unk4, a[1].unk8, 0x80FF00FF);
    return 0;
}

s32 func_psp_089254D8(LINE_F2* p) {
    Unk0891B118 a[2];
    LINE_F2* ptr;

    ptr = p;

    a[0].unk4 = ptr->x0;
    a[0].unk8 = ptr->y0;
    a[1].unk4 = ptr->x1;
    a[1].unk8 = ptr->y1;
    if (a[0].unk4 > a[1].unk4) {
        a[0].unk4++;
    }
    a[0].unkC = a[1].unkC = 1.0f;
    a[0].unk0 = a[1].unk0 = GU_RGBA(ptr->r0, ptr->g0, ptr->b0, 0x80);
    if (D_psp_08C62A40 == 0) {
        func_psp_0891DC48(a, 2);
    }
    func_psp_08912008();
    func_psp_08910A80(a, 2, sizeof(Unk0891B118), GU_LINES, GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    return 0;
}

s32 func_psp_08925600(LINE_F4* p) {
    Unk0891B118 a[2];
    LINE_F4* ptr;

    ptr = p;

    a[0].unkC = a[1].unkC = 1.0f;
    a[0].unk0 = a[1].unk0 = GU_RGBA(ptr->r0, ptr->g0, ptr->b0, 0x80);
    func_psp_08912008();
    a[0].unk4 = ptr->x0;
    a[0].unk8 = ptr->y0;
    a[1].unk4 = ptr->x1;
    a[1].unk8 = ptr->y1;
    if (a[0].unk4 > a[1].unk4) {
        a[0].unk4++;
    }
    if (D_psp_08C62A40 == 0) {
        func_psp_0891DC48(a, 2);
    }
    func_psp_08910A80(a, 2, sizeof(Unk0891B118), GU_LINES, GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    a[0].unk4 = a[1].unk4;
    a[0].unk8 = a[1].unk8;
    a[1].unk4 = ptr->x2;
    a[1].unk8 = ptr->y2;
    if (a[0].unk4 > a[1].unk4) {
        a[0].unk4++;
    }
    if (D_psp_08C62A40 == 0) {
        func_psp_0891DC48(a, 2);
    }
    func_psp_08910A80(a, 2, sizeof(Unk0891B118), GU_LINES, GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    a[0].unk4 = a[1].unk4;
    a[0].unk8 = a[1].unk8;
    a[1].unk4 = ptr->x3;
    a[1].unk8 = ptr->y3;
    if (a[0].unk4 > a[1].unk4) {
        a[0].unk4++;
    }
    if (D_psp_08C62A40 == 0) {
        func_psp_0891DC48(a, 2);
    }
    func_psp_08910A80(a, 2, sizeof(Unk0891B118), GU_LINES, GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    return 0;
}

s32 func_psp_08925860(LINE_G2* p) {
    Unk0891B118 a[2];
    LINE_G2* ptr;

    ptr = p;

    a[0].unk4 = ptr->x0;
    a[0].unk8 = ptr->y0;
    a[1].unk4 = ptr->x1;
    a[1].unk8 = ptr->y1;
    if (a[0].unk4 > a[1].unk4) {
        a[0].unk4++;
    }
    a[0].unkC = a[1].unkC = 1.0f;
    a[0].unk0 = GU_RGBA(ptr->r0, ptr->g0, ptr->b0, 0x80);
    a[1].unk0 = GU_RGBA(ptr->r1, ptr->g1, ptr->b1, 0x80);
    if (D_psp_08C62A40 == 0) {
        func_psp_0891DC48(a, 2);
    }
    if ((ptr->code & 0x40) >> 6) {
        func_psp_089113A8((D_psp_08C629C4 >> 5) & 3, 0x80);
    } else {
        func_psp_089113A8(-1, 0x80);
    }
    func_psp_08912008();
    func_psp_08910A80(a, 2, sizeof(Unk0891B118), GU_LINES, GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    return 0;
}

s32 func_psp_08925A04(LINE_G4* p) {
    Unk0891B118 a[2];
    LINE_G4* ptr;

    ptr = p;

    a[0].unkC = a[1].unkC = 1.0f;
    func_psp_08912008();
    a[0].unk4 = ptr->x0;
    a[0].unk8 = ptr->y0;
    a[1].unk4 = ptr->x1;
    a[1].unk8 = ptr->y1;
    if (a[0].unk4 > a[1].unk4) {
        a[0].unk4++;
    }
    a[0].unk0 = GU_RGBA(ptr->r0, ptr->g0, ptr->b0, 0x80);
    a[1].unk0 = GU_RGBA(ptr->r1, ptr->g1, ptr->b1, 0x80);
    if (D_psp_08C62A40 == 0) {
        func_psp_0891DC48(a, 2);
    }
    func_psp_08910A80(a, 2, sizeof(Unk0891B118), GU_LINES, GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    a[0].unk4 = a[1].unk4;
    a[0].unk8 = a[1].unk8;
    a[1].unk4 = ptr->x2;
    a[1].unk8 = ptr->y2;
    if (a[0].unk4 > a[1].unk4) {
        a[0].unk4++;
    }
    a[0].unk0 = GU_RGBA(ptr->r1, ptr->g1, ptr->b1, 0x80);
    a[1].unk0 = GU_RGBA(ptr->r2, ptr->g2, ptr->b2, 0x80);
    if (D_psp_08C62A40 == 0) {
        func_psp_0891DC48(a, 2);
    }
    func_psp_08910A80(a, 2, sizeof(Unk0891B118), GU_LINES, GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    a[0].unk4 = a[1].unk4;
    a[0].unk8 = a[1].unk8;
    a[1].unk4 = ptr->x3;
    a[1].unk8 = ptr->y3;
    if (a[0].unk4 > a[1].unk4) {
        a[0].unk4++;
    }
    a[0].unk0 = GU_RGBA(ptr->r2, ptr->g2, ptr->b2, 0x80);
    a[1].unk0 = GU_RGBA(ptr->r3, ptr->g3, ptr->b3, 0x80);
    if (D_psp_08C62A40 == 0) {
        func_psp_0891DC48(a, 2);
    }
    func_psp_08910A80(a, 2, sizeof(Unk0891B118), GU_LINES, GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    return 0;
}

void SetLineG2(LINE_G2* p) { setLineG2(p); }

void SetPolyG4(POLY_G4* p) { setPolyG4(p); }

void SetPolyGT3(POLY_GT3* p) { setPolyGT3(p); }

void SetPolyGT4(POLY_GT4* p) { setPolyGT4(p); }

void SetSprt(SPRT* p) { setSprt(p); }

void SetSprt16(SPRT_16* p) { setSprt16(p); }

void SetTile(TILE* p) { setTile(p); }

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", FntPrint);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_08925F7C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_089260AC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_089260D0);

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

    temp_v0 = func_psp_08919C8C(0);
    if (func_psp_08919E6C(0, temp_v0) > 0) {
        func_psp_08910D28();
        func_psp_0890FC2C();
        func_psp_0890FF84();
        func_psp_08910298(1);
        func_psp_089117F4(
            1, 0, 0, 0x100, 0x110, 0xF0, func_psp_08919E1C(temp_v0), 0, 0,
            0x100, (u8*)sceGeEdramGetAddr() + 0x1BC000);
        func_psp_089117F4(3, 0, 0, 0x100, 1, 0x100, func_psp_08919DF4(temp_v0),
                          0, 0, 0x100, (u8*)sceGeEdramGetAddr() + 0x1DE000);
        func_psp_0890FF2C();
        sceKernelDcacheWritebackAll();
        func_psp_0890FE98();
        DrawSync(0);
    }
}

void func_psp_08926498(void) {
    sceKernelPowerTick(0);
    FntPrint(&D_psp_08946688);
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

void func_psp_0892667C(s32 arg0, u_long* arg1) {
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
    rect.x += (arg0 & 0xF) * 0x10;
    rect.y = ((arg0 / 0x10) & 0xF) + 0xF0;
    rect.w = 0x10;
    rect.h = 1;
    LoadImage(&rect, arg1);
    var_s0 += (((arg0 / 0x10) & 0xF) << 8) + ((arg0 & 0xF) * 0x10);
    memcpy(var_s0, arg1, 0x20);
}

void func_psp_08926808(s32 arg0, u_long* arg1) {
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
    rect.x += (arg0 & 0xF) * 0x10;
    rect.y = ((arg0 / 0x10) & 0xF) + 0xF0;
    rect.w = 0x10;
    rect.h = 1;
    func_psp_0891C1C0(&rect, arg1);
    var_s0 += (((arg0 / 0x10) & 0xF) << 8) + ((arg0 & 0xF) * 0x10);
    memcpy(var_s0, arg1, 0x20);
}

static void GameEntrypoint(void) {
    func_psp_08926348();
    func_psp_0892A1EC(0);
    while (func_psp_0890FB70(&D_psp_089466A0, g_BmpCastleMap, 0, 0x8000) == 0) {
        sceKernelDelayThreadCB(1000000);
    }
    MainGame();
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_08926A08);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", Krom2RawAdd);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", ApplyRotMatrix);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", ScaleMatrix);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", CompMatrix);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", DpqColor);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", NormalColorDpq);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", NormalClip);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", RotTrans);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", RotTransPers);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", RotTransPers3);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", RotTransPers4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", RotAverage3);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", RotAverage4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", RotAverageNclip3);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", RotAverageNclip4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_08927C5C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", SquareRoot0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", SquareRoot12);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", ratan2);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", VectorNormalS);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", rcos);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", rsin);

void gte_stub(void) {}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", InitGeom);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", SetGeomScreen);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", SetGeomOffset);

void SetFarColor() {}

void SetFogNear() {}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_089280CC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892827C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_08928428);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_08928498);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892851C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_089285A0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", RotMatrixX);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", RotMatrixY);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", RotMatrixZ);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", RotMatrix);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", RotMatrixYXZ);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", SetRotMatrix);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", TransMatrix);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", SetTransMatrix);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", gte_SetTransVector);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", gte_ldv0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", gte_ldv1);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", gte_ldv2);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", gte_ldv3c);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", gte_ldtx);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", gte_ldty);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", gte_ldtz);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", gte_ldtr);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_08928980);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", gte_rtps);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", gte_rtpt);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", gte_stsxy);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", gte_stsxy3_gt3);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", gte_stsxy3);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", gte_stszotz);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", gte_stotz);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", gte_stopz);

void gte_dpcs(void) {}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", gte_strgb);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", gte_ldrgb);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", gte_nclip);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", gte_avsz3);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_089295E4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", gte_avsz4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", gte_ldv01c);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", gte_stsxy01c);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", SetColorMatrix);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", SetLightMatrix);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", SetBackColor);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_08929838);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_08929860);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", NormalColorCol);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_08929FA8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892A018);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892A0C4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892A0F0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892A1EC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892A21C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892A28C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892A2D8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892A3D4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892A414);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892A620);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892A70C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892A76C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892A7E0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892A8C0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892A8FC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892A97C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892A998);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", SsSetSerialVol);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892A9E0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", strFileOpen);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", strFileClose);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", strFileRead);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", strFileLseek);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", play_bgm);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", init_atrac3plus);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", play_atrac3plus);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", createPlayModeFlag);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", setPlayMode);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", checkPlayMode);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", waitPlayMode);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", clearPlayMode);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", release_arg);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", at3plus_addData);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", reset_position);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", fadeoutOperation);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", DvdUmdIoInit);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", DvdUmdIoTerm);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", DvdUmdRetryOpenCB);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", DvdUmdRetryRead);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892BF14);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892BF48);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892BFD0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892BFD8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892C168);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892C174);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892C188);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892C214);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892C3D4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892C4F8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892C524);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892C540);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892C62C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892C660);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892C860);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892CA28);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892CA90);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892CAD8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892CB10);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892CB1C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892CB30);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892CB40);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892CC48);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892CD48);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892CDE0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892CEB0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892CF0C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892CF34);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892CF7C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892CF88);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892CF90);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892D030);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892D130);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892D154);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892D1B0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892D1D8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892D220);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892D2E8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892D3B8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892D4A8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892D518);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892D520);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892D598);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892D5F0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892D674);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892D818);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892D844);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892D96C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892DADC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892DB90);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892DBE4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892DC40);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892DCD8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892DD54);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892DDB0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892DF08);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892DF70);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892DFCC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892E498);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892E6A4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892E718);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892E798);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892E818);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892E8B8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892E914);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892E978);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892E994);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892E9B0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892E9E4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", GsClearVcount);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892EA24);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892EAFC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892EB04);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892EBE8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892EC7C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", SpuGetAllKeysStatus);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", SsUtKeyOnV);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", SsUtSetVVol);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", SpuSetKey);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", SpuSetVoiceAttr);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_0892F83C);
