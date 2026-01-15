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
#include <psxsdk/libgpu.h>

#define isSemiTrans(ptr) (((ptr)->code & 0x40) >> 6)
#define isFlatShaded(ptr) (((ptr)->code & 0x80) ? 0 : 1)

#define white GU_RGBA(0xFF, 0xFF, 0xFF, 0x80)
#define black GU_RGBA(0, 0, 0, 0x80)
#define red GU_RGBA(0xFF, 0, 0, 0x80)
#define green GU_RGBA(0, 0xFF, 0, 0x80)
#define blue GU_RGBA(0, 0, 0xFF, 0x80)
#define magenta GU_RGBA(0xFF, 0, 0xFF, 0x80)

#undef MIN
#define MIN(a, b) (a) < (b) ? (a) : (b)

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
    s32* unk10;
} Unk08919CF4;

typedef struct Unk08919D98 Unk08919D98;

typedef struct Unk08919D98 {
    s32* unk0;
    Unk08919D98* prev;
    Unk08919D98* next;
    s32 (*unkC)(Unk08919D98*);
    s32 count;
} Unk08919D98;

typedef struct {
    s32 x;
    s32 y;
} Unk08C4218C;

typedef struct {
    u32 c;
    float x, y, z;
} Vertex;

typedef struct {
    float u, v;
    u32 c;
    float x, y, z;
} TVertex;

// DATA
extern s32 D_psp_0893CED0;
extern s32 D_psp_0893CF74[];

// BSS
extern SceCtrlData D_psp_08B41F40;
extern SceCtrlData D_psp_08B41F50;
extern u16 D_psp_08B41F60;
extern u8* D_psp_08B41F64;
extern s32 D_psp_08B41F68;
extern s32 D_psp_08B41F9C;
extern s32 D_psp_08B41FB4;
extern s32 D_psp_08B41FB8;
extern s32 D_psp_08B41FBC;
extern bool D_psp_08B41FC0;
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
extern bool D_psp_08B42068;
extern s32 D_psp_08B4206C;
extern u8 D_psp_08B42080[0x20][0x8000];
extern s32 D_psp_08C42080[0x20];
extern u8* D_psp_08C42100[0x20];
extern u32 D_psp_08C42180;
extern void (*D_psp_08C42184)();
extern u32 D_psp_08C42188;
extern Unk08C4218C D_psp_08C4218C[];
extern u8 D_psp_08C429C0[0x100][0x200];
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
extern bool D_psp_08C62A44;
extern u32 D_psp_08C62A48;
extern s32 D_psp_08C62A4C;
extern s32 D_psp_08C62A50;
extern s32 D_psp_08C62A54;
extern bool D_psp_08C62A58;
extern s32 D_psp_08C62A5C;
extern s32 D_psp_08C62A60;
extern s32 D_psp_08C62A64;
extern s32 D_psp_08C62A68;
extern s32 D_psp_08C62A6C;
extern bool D_psp_08C62A70;
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
extern bool D_psp_08C630C4;
extern bool D_psp_08C630C8;
extern u32 D_psp_08C630CC;
extern s32 D_psp_08C630D0;
extern s32 D_psp_08C630E0; // play_wait - slow-downs the game
extern char D_psp_08C630E4[];
#define g_GameClearFlag (*((s32*)0x091FC418))

void* memalign(size_t, size_t);
void func_psp_08919C4C(void);
void func_psp_0891ACBC(void);
s32 func_psp_08933F7C(u8, u8);
void func_psp_08919D98(Unk08919D98* arg0);
void func_psp_0891A6A8(s32 screen_mode);
extern void func_psp_0891B538(s32 arg0);
extern void func_psp_0891B570(int arg0, int arg1);
extern void func_psp_089113A8(s32 arg0, u8 arg1);
static void func_psp_0891B6FC(void);
static void func_psp_0891CD28(u_long* p, s32 x, s32 y);
static void func_psp_0891CEB8(s32 x, s32 y);

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

static s32 func_psp_08919E44() { return func_psp_08932994(&D_psp_08B41F9C); }

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
    sceGuSetCallback2(GU_CALLBACK_FINISH, &func_psp_0891B538);
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

static s32 D_psp_089464D0 = -1;
static s32 D_psp_089464D4 = -1;
static s32 screen_w = 320;
static s32 screen_h = 240;
static float D_psp_089464E0 = 1.0f;
static float D_psp_089464E4 = 1.0f;
s32 D_psp_089464E8 = 2;
static s32 D_psp_089464EC = 1;
static s32 D_psp_089464F0 = 1;

void func_psp_0891A608(void) {
    float x = D_psp_08C629C8;
    float y = D_psp_08C629CC;

    __asm__(".set		push\n"      // save assembler option
            ".set		noreorder\n" // suppress reordering
            "lv.s		s410, 0(%0)\n"
            "lv.s		s411, 0(%1)\n"
            ".set		pop\n" // suppress reordering
            :
            : "m"(x), "m"(y));
}

void func_psp_0891A650(void) {
    float x = 16.0f;
    float y = 256.0f;

    __asm__(".set		push\n"      // save assembler option
            ".set		noreorder\n" // suppress reordering
            "lv.s		s403, 0(%1)\n"
            "lv.s		s420, 0(%0)\n"
            "vmov.s     s421, s420\n"
            "vone.s     s402\n"
            "vone.s     s422\n"
            "vone.s     s302\n"
            "vone.s     s312\n"
            "vone.s     s322\n"
            "vone.s     s332\n"
            "vzero.s    S400\n"
            ".set		pop\n" // suppress reordering
            :
            : "m"(x), "m"(y));
}

static void func_psp_0891A6A8(s32 screen_mode) {
    D_psp_08C62A30 = screen_mode;
    switch (D_psp_08C62A30) {
    case SCREEN_MODE_FULL:
        screen_w = 362;
        screen_h = 272;
        break;
    case SCREEN_MODE_PERFECT:
        screen_w = 320;
        screen_h = 240;
        break;
    }
    D_psp_08C62A34 = (GU_SCR_WIDTH - screen_w) / 2;
    D_psp_08C62A38 = (GU_SCR_HEIGHT - screen_h) / 2;
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
    func_psp_0891A6A8(SCREEN_MODE_FULL);
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
    D_psp_08B41FC0 = D_psp_08B41FC0 ? false : true;
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
        if (D_psp_08B41FC0) {
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

s32 func_psp_0891B118(s32 x0, s32 y0, s32 x1, s32 y1, s32 color) {
    Vertex v[2];

    v[0].x = x0;
    v[0].y = y0;
    v[1].x = x1;
    v[1].y = y1;
    if (v[0].x > v[1].x) {
        v[0].x++;
    }
    v[0].z = v[1].z = 1.0f;
    v[0].c = v[1].c = color;
    func_psp_08912008();
    func_psp_08910A80(v, 2, sizeof(Vertex), GU_LINES,
                      GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    return 0;
}

s32 func_psp_0891B1F8(s32 x0, s32 y0, s32 x1, s32 y1, s32 color) {
    if (D_psp_08B42068 == true) {
        func_psp_0891B118(x0, y0, x1 - 1, y0, color);
        func_psp_0891B118(x1 - 1, y0, x1 - 1, y1 - 1, color);
        func_psp_0891B118(x1 - 1, y1 - 1, x0, y1 - 1, color);
        func_psp_0891B118(x0, y1 - 1, x0, y0, color);
    }
    return 0;
}

s32 func_psp_0891B2CC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 color) {
    Vertex v[4];

    v[0].x = arg0;
    v[0].y = arg1;
    v[1].x = arg0 + arg2;
    v[1].y = arg1;
    v[2].x = arg0;
    v[2].y = arg1 + arg3;
    v[3].x = arg0 + arg2;
    v[3].y = arg1 + arg3;
    v[0].z = v[1].z = v[2].z = v[3].z = 1.0f;
    v[1].c = v[0].c = v[3].c = v[2].c = color;
    func_psp_08912008();
    func_psp_089113A8(-1, 0x80);
    func_psp_08910A80(v, 4, sizeof(Vertex), GU_TRIANGLE_STRIP,
                      GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    return 0;
}

s32 func_psp_0891B400(void) {
    if (~D_psp_089464D4 > 0U) {
    }
    D_psp_08C42180 = 0;
    D_psp_089464D4 = sceDisplayGetVcount();
    return D_psp_089464D4;
}

s32 DrawSync(s32 arg0) {
    if (D_psp_08C62A44) {
        if (sceGuSync(GU_SYNC_FINISH, GU_SYNC_NOWAIT) == 1) {
            sceGuDebugPrint(472, 0, 0xFFFFFFFF, "G");
        } else {
            sceGuDebugPrint(472, 0, 0xFFFFFFFF, "C");
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
    if (D_psp_08C62A58) {
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

u8* func_psp_0891B8F0(u16 clut, s32 arg1, s32 arg2) {
    Unk08C4218C v;
    u16 var_s0;

    if (D_psp_08C62AB4 == clut) {
        return D_psp_08C62AB8;
    }
    if (!(clut & 0x8000)) {
        v.y = (clut & 0x3F) * 0x10;
        v.x = clut >> 6;
        if (arg1 == 1 && arg2) {
            var_s0 = GetClut(v.y, v.x);
            if (var_s0 & 0x8000) {
                D_psp_08C62AB8 = D_psp_08C429C0[var_s0 & 0x7FFF];
            } else {
                func_psp_0891CEB8(v.y, v.x);
                D_psp_08C62AB8 = D_psp_08C429C0[GetClut(v.y, v.x) & 0x7FFF];
            }
        } else {
            D_psp_08C62AB8 =
                &D_psp_08B42080[(v.y / 0x40) + (v.x / 0x100) * 0x10]
                               [(v.y % 0x40) * 2 + (v.x % 0x100) * 0x80];
        }
    } else {
        D_psp_08C62AB8 = D_psp_08C429C0[clut & 0x7FFF];
    }
    D_psp_08C62AB4 = clut;
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
    sp3C = arg3 ? 0x100 : 0x100;
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
    s32 toRead;
    s32 x, y;
    s32 dx, dy;
    s32 i;
    u8* src;
    u8* dst;

    ptr = (u8*)p;
    dy = arg3 ? 0x100 : 0x100;
    for (y = rect->y; y < rect->y + rect->h; y += dy) {
        for (x = rect->x; x < rect->x + rect->w; x += dx / 2) {
            dx = MIN(rect->x + rect->w - x, 0x40);
            if ((x % 0x40) != 0) {
                dx = MIN(dx, 0x40 - (x % 0x40));
            }
            dx = dx * 2;
            toRead = MIN(rect->y + rect->h - y, dy);
            src = &D_psp_08B42080[x / 0x40 + y / 0x100 * 0x10]
                                 [(x % 0x40) * 2 + (y % 0x100) * 0x80];
            dst = &ptr[width * (y - rect->y) + (x - rect->x) * 2];
            for (i = 0; i < toRead; i++) {
                memcpy(dst, src, dx);
                dst += width;
                src += 0x80;
            }
        }
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
    s32 toWrite;
    s32 x, y;
    s32 dx, dy;
    s32 i;
    u8* data;
    u16 color;
    u16* var_s1;
    u16* var_s0;

    color = b >> 3 << 11 | g >> 2 << 5 | r >> 2;
    if (color) {
        color |= 0x8000;
    }
    dy = arg4 ? 0x100 : 0x100;
    for (y = rect->y; y < rect->y + rect->h; y += dy) {
        for (x = rect->x; x < rect->x + rect->w; x += dx / 2) {
            dx = MIN(rect->x + rect->w - x, 0x40);
            if ((x % 0x40) != 0) {
                dx = MIN(dx, 0x40 - (x % 0x40));
            }
            dx = dx * 2;
            toWrite = MIN(rect->y + rect->h - y, dy);
            func_psp_0891A99C(x / 0x40 + y / 0x100 * 0x10);
            data = &D_psp_08B42080[x / 0x40 + y / 0x100 * 0x10]
                                  [(x % 0x40) * 2 + (y % 0x100) * 0x80];
            for (i = 0; i < toWrite; i++) {
                var_s0 = (u16*)data;
                var_s1 = (u16*)(data + dx);
                while (var_s0 != var_s1) {
                    *var_s0 = color;
                    var_s0++;
                }
                data += 0x80;
            }
        }
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

s32 VSyncCallback(void (*f)()) {
    void (*temp_s0)();

    temp_s0 = D_psp_08C42184;
    D_psp_08C42184 = f;
    return (s32)temp_s0;
}

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
    case SCREEN_MODE_FULL:
        screen_w = 362;
        screen_h = 272;
        break;
    case SCREEN_MODE_PERFECT:
        screen_w = 320;
        screen_h = 240;
        break;
    }
    D_psp_08C62A34 = (GU_SCR_WIDTH - screen_w) / 2;
    D_psp_08C62A38 = (GU_SCR_HEIGHT - screen_h) / 2;
    if (D_psp_08C629D8.disp.w == 256 && D_psp_08C629D8.disp.h == 240) {
        if (D_psp_08C62A30 == SCREEN_MODE_PERFECT) {
            D_psp_08C62A34 += D_psp_08C629EC.clip.x;
            D_psp_08C62A38 += D_psp_08C629EC.clip.y;
            screen_h = D_psp_08C629EC.clip.h;
            screen_w = (D_psp_08C62A30 == SCREEN_MODE_FULL) ? 418 : 320;
        } else {
            screen_w = (D_psp_08C62A30 == SCREEN_MODE_FULL) ? 418 : 320;
            D_psp_08C62A34 = (GU_SCR_WIDTH - screen_w) / 2;
            D_psp_089464E0 = D_psp_089464E4 = 1.0f;
        }
    } else {
        if (D_psp_08C629D8.disp.w <= 480 && D_psp_08C629D8.disp.h <= 256) {
            D_psp_089464E0 = D_psp_089464E4 = 1.0f;
        } else {
            D_psp_089464E0 = (float)screen_w / (float)D_psp_08C629D8.disp.w;
            D_psp_089464E4 = (float)screen_h / (float)D_psp_08C629D8.disp.h;
        }
    }
    return env;
}

void func_psp_0891D9F4(TVertex* ptr, s32 len) {
    s32 i;

    if (len == 2) {
        ptr->x = D_psp_08C62A34 + ptr->x * D_psp_089464E0;
        ptr->y = D_psp_08C62A38 + ptr->y * D_psp_089464E4;
        ptr++;
        ptr->x = D_psp_08C62A34 + (ptr->x + 1) * D_psp_089464E0;
        ptr->y = D_psp_08C62A38 + (ptr->y + 1) * D_psp_089464E4;
    } else {
        for (i = 0; i < len; i++) {
            ptr->x = D_psp_08C62A34 + ptr->x * D_psp_089464E0;
            ptr->y = D_psp_08C62A38 + ptr->y * D_psp_089464E4;
            ptr++;
        }
    }
}

void func_psp_0891DB9C(Vertex* ptr, s32 len) {
    s32 i;

    for (i = 0; i < len; i++) {
        ptr->x = D_psp_08C62A34 + ptr->x * D_psp_089464E0;
        ptr->y = D_psp_08C62A38 + ptr->y * D_psp_089464E4;
        ptr++;
    }
}

void func_psp_0891DC48(Vertex* ptr, s32 len) {
    s32 i;

    for (i = 0; i < len; i++) {
        ptr->x = D_psp_08C62A34 + ptr->x * D_psp_089464E0;
        ptr->y = D_psp_08C62A38 + ptr->y * D_psp_089464E4;
        ptr++;
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

float D_psp_089464FC = 382.0f;
float D_psp_08946500 = 240.0f;
s32 D_psp_08946504 = GU_RGBA(0xA0, 0xA0, 0xA0, 0x80);

s32 func_psp_08920488(void*);
s32 func_psp_08920498(void*);
s32 func_psp_089215A4(void*);
s32 func_psp_08921D44(void*);
s32 func_psp_089225D8(void*);
s32 func_psp_08923FA4(void*);
s32 func_psp_08921A38(void*);
s32 func_psp_089254D8(void*);
s32 func_psp_08925600(void*);
s32 func_psp_08925860(void*);
s32 func_psp_08925A04(void*);
s32 func_psp_08925194(void*);
s32 func_psp_0891FCC0(void*);
s32 func_psp_0891FCF0(void*);
s32 func_psp_0891FD20(void*);
s32 func_psp_0891FD74(void*);
s32 func_psp_0891FDC8(void*);

s32 (*D_psp_08946508[])(void*) = {
    func_psp_08920488, // NONE
    func_psp_08920498, // SPRT
    func_psp_089215A4, // SPRT_16
    func_psp_08921D44, // POLY_FT4
    func_psp_089225D8, // POLY_GT3
    func_psp_08923FA4, // POLY_GT4
    func_psp_08921A38, // POLY_G4
    func_psp_089254D8, // LINE_F2
    func_psp_08925600, // LINE_F4
    func_psp_08925860, // LINE_G2
    func_psp_08925A04, // LINE_G4
    func_psp_08925194, // TILE
    func_psp_0891FCC0, // DR_MODE OR DR_TWIN ?
    func_psp_0891FCF0, // DR_MODE OR DR_TWIN ?
    func_psp_0891FD20, // DR_OFFSET
    func_psp_0891FD74, // DR_AREA
    func_psp_0891FDC8, // DR_ENV
};

void func_psp_0891DE74(void) {
    s32 var_s1;
    s32 var_s2;
    TVertex* v;

    var_s2 = 0;
    v = (TVertex*)SP(0);
    var_s1 = D_psp_08C62A40;

    func_psp_0891AF48(0);
    func_psp_08910660(0);
    v[0].c = v[1].c = v[2].c = v[3].c = white;
    func_psp_08911F24(0, D_psp_089464F0);
    func_psp_08911B7C();
    switch (D_psp_08B4206C) {
    case 0:
        break;
    case 1:
        v[0].x = v[0].y = v[1].y = v[2].x = 0.0f;
        v[1].x = v[2].y = v[3].x = v[3].y = 255.0f;
        v[0].z = v[1].z = v[2].z = v[3].z = 1.0f;
        v[0].u = v[0].v = v[1].v = v[2].u = 0.0f;
        v[1].u = v[2].v = v[3].u = v[3].v = 255.0f;
        func_psp_0891089C(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT);
        func_psp_08911990((s32)sceGeEdramGetAddr() + 0xCC000, 0x100);
        func_psp_08910A80(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                          GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888 |
                              GU_TEXTURE_32BITF);
        break;
    case 2:
        func_psp_08910660(1);
        func_psp_08910810(GU_ADD, GU_FIX, GU_FIX, 0xFFFFFFFF, 0xFF808080);
        v[0].c = v[1].c = v[2].c = v[3].c = 0xFFFFFFFF;
        v[0].x = v[2].x = D_psp_08C62A34;
        v[0].y = v[1].y = D_psp_08C62A38;
        v[1].x = v[3].x = D_psp_08C62A34 + screen_w;
        v[2].y = v[3].y = D_psp_08C62A38 + screen_h;
        v[0].z = v[1].z = v[2].z = v[3].z = 1.0f;
        v[0].u = v[0].v = v[1].v = v[2].u = 0.0f;
        v[1].u = D_psp_089464FC;
        v[2].v = D_psp_08946500;
        v[3].u = D_psp_089464FC;
        v[3].v = D_psp_08946500;
        func_psp_0891089C(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT);
        func_psp_08911990(func_psp_0891AC24(), 0x200);
        func_psp_08910A80(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                          GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888 |
                              GU_TEXTURE_32BITF);
        break;
    case 3:
        v[0].x = v[0].y = v[1].y = v[2].x = 0.0f;
        v[1].x = v[3].x = 63.0f;
        v[2].y = v[3].y = 63.0f;
        v[0].z = v[1].z = v[2].z = v[3].z = 1.0f;
        v[0].u = v[0].v = v[1].v = v[2].u = 0.0f;
        v[1].u = v[3].u = 63.0f;
        v[2].v = v[3].v = 63.0f;
        func_psp_0891089C(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT);
        func_psp_08911990((s32)sceGeEdramGetAddr() + 0x12C200, 0x40);
        func_psp_08910A80(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                          GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888 |
                              GU_TEXTURE_32BITF);
        break;
    case 4:
        v[0].x = 0.0f;
        v[0].y = 0.0f;
        v[1].x = 128.0f;
        v[1].y = 0.0f;
        v[2].x = 0.0f;
        v[2].y = 136.0f;
        v[3].x = 128.0f;
        v[3].y = 136.0f;
        v[0].z = v[1].z = v[2].z = v[3].z = 1.0f;
        v[0].u = 0.0f;
        v[0].v = 0.0f;
        v[1].u = 256.0f;
        v[1].v = 0.0f;
        v[2].u = 0.0f;
        v[2].v = 272.0f;
        v[3].u = 256.0f;
        v[3].v = 272.0f;
        func_psp_0891089C(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT);
        func_psp_08911990((s32)sceGeEdramGetAddr() + 0xCC000, 0x100);
        func_psp_08910A80(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                          GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888 |
                              GU_TEXTURE_32BITF);
        v[0].y += 136.0f;
        v[1].y += 136.0f;
        v[2].y += 136.0f;
        v[3].y += 136.0f;
        v[1].u = 512.0f;
        v[3].u = 512.0f;
        func_psp_08911990(func_psp_0891AC24(), 0x200);
        func_psp_08910A80(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                          GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888 |
                              GU_TEXTURE_32BITF);
        break;
    }
    func_psp_0891AF48(var_s1);
}

void func_psp_0891E420(void) {
    s32 var_s1;
    TVertex* v;

    var_s1 = 0;
    v = (TVertex*)SP(0);

    func_psp_08911990(func_psp_0891AC24(), 0x200);
    func_psp_08910660(0);
    v[0].c = v[1].c = v[2].c = v[3].c = D_psp_08946504;
    v[0].x = v[2].x = D_psp_08C62A34;
    v[0].y = v[1].y = D_psp_08C62A38;
    v[1].x = v[3].x = D_psp_08C62A34 + screen_w;
    v[2].y = v[3].y = D_psp_08C62A38 + screen_h;
    v[0].z = v[1].z = v[2].z = v[3].z = 1.0f;
    v[0].u = v[2].u = D_psp_08C629EC.clip.x;
    v[0].v = v[1].v = D_psp_08C629EC.clip.y;
    v[1].u = v[3].u = D_psp_08C629EC.clip.x + (float)D_psp_08C629EC.clip.w;
    v[2].v = v[3].v = D_psp_08C629EC.clip.y + (float)D_psp_08C629EC.clip.h;
    func_psp_0891AF48(0);
    func_psp_08911F24(0, D_psp_089464F0);
    func_psp_08911B7C();
    func_psp_089109E4(GU_TFX_MODULATE, GU_TCC_RGBA, 1);
    func_psp_0891089C(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT);
    func_psp_08910A80(
        v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
        GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888 | GU_TEXTURE_32BITF);
    func_psp_089109E4(GU_TFX_MODULATE, GU_TCC_RGBA, 0);
    func_psp_0891AF48(2);
}

void func_psp_0891E638(void) {
    s32 temp_s2;
    s32 temp_s1;
    TVertex* v;

    temp_s2 = 0;
    v = (TVertex*)SP(0);

    func_psp_08910660(0);
    v[0].c = v[1].c = v[2].c = v[3].c = white;
    v[0].x = 0.0f;
    v[0].y = 0.0f;
    v[1].x = GU_SCR_WIDTH;
    v[1].y = 0.0f;
    v[2].x = 0.0f;
    v[2].y = GU_SCR_HEIGHT;
    v[3].x = GU_SCR_WIDTH;
    v[3].y = GU_SCR_HEIGHT;
    v[0].z = v[1].z = v[2].z = v[3].z = 1.0f;
    v[0].u = 0.0f;
    v[0].v = 0.0f;
    v[1].u = GU_SCR_WIDTH;
    v[1].v = 0.0f;
    v[2].u = 0.0f;
    v[2].v = GU_SCR_HEIGHT;
    v[3].u = GU_SCR_WIDTH;
    v[3].v = GU_SCR_HEIGHT;
    temp_s1 = D_psp_08C62A40;
    func_psp_0891AF48(0);
    func_psp_08911F24(0, D_psp_089464F0);
    func_psp_08911B7C();
    func_psp_0891089C(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT);
    if (func_psp_08919E44()) {
        func_psp_08910FD8((s32)sceGeEdramGetAddr() + 0x1BC000,
                          (s32)sceGeEdramGetAddr() + 0x1DE000, 5, 0x200, 9, 9);
    } else {
        func_psp_0891B2CC(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT, black);
    }
    func_psp_08910A80(
        v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
        GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888 | GU_TEXTURE_32BITF);
    func_psp_0891AF48(temp_s1);
}

void func_psp_0891E840(void) {
    func_psp_08910D28();
    func_psp_0890FC2C();
    func_psp_0890FF84();
    func_psp_08910298(1);
    func_psp_08910558(0);
    func_psp_08910608(0);
    func_psp_089105DC(1);
    func_psp_08910660(1);
    func_psp_0891068C(1);
    func_psp_089107A4(0);
    func_psp_089106F4(0);
    func_psp_089105B0(0);
    func_psp_08910584(0);
    func_psp_08910634(1);
    func_psp_0891074C(0);
    func_psp_08910778(0);
    func_psp_0891052C(1);
    func_psp_08910720(0);
    func_psp_089107DC(1, 1);
    func_psp_089108F8(0, 0);
}

void func_psp_0891E944(void) {
    func_psp_0890FF2C();
    sceKernelDcacheWritebackAll();
    func_psp_0890FE98();
    D_psp_08C62A6C = 0;
    D_psp_08C62A68 = 0;
    D_psp_08C42188 = D_psp_08C42180;
}

void func_psp_0891E994(OT_TYPE* p) {
    s32 sp5C;
    s32 sp58;
    s32 sp54;
    s32 sp50;
    u32 fps;
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
            if (D_psp_08C62AAC.x == 0 && D_psp_08C62AAC.y == 0x100) {
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
            func_psp_0891B2CC(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT, black);
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
            case SCREEN_MODE_FULL:
                sp54 = 418;
                var_fp = 272;
                break;
            case SCREEN_MODE_PERFECT:
                sp54 = 369;
                var_fp = 240;
                break;
            }
            sp5C = (GU_SCR_WIDTH - sp54) / 2;
            sp58 = (GU_SCR_HEIGHT - var_fp) / 2;
            func_psp_0891AF48(0);
            func_psp_0891089C(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT);
            func_psp_0891B2CC(sp5C, sp58, sp54 - 1, var_fp - 1, black);
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
            func_psp_0891B2CC(0x130, 0, 0xB0, 0x70, black);
        }
        if (D_psp_08C62A58 && (D_psp_08C62A64 != 0)) {
            var_s7 = (D_psp_08C42180 != D_psp_08C42188)
                         ? (D_psp_08C42180 - D_psp_08C42188) * 0xF0
                         : 0xF0;
            func_psp_0891AF48(0);
            func_psp_0891089C(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT);
            func_psp_0891B118(
                0, 0, (D_psp_08C62A64 * var_s7) / D_psp_08C62A64, 0, white);
            func_psp_0891B118(
                0, 1, (D_psp_08C62A5C * var_s7) / D_psp_08C62A64, 1, red);
            func_psp_0891B118(
                0, 2, (D_psp_08C62A60 * var_s7) / D_psp_08C62A64, 2, green);
        }
        func_psp_0891AF48(0);
        func_psp_0891089C(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT);
        func_psp_08932228();
        func_psp_0891E944();
        if (D_psp_08C62A44) {
            fps = (D_psp_08C42180 != D_psp_08C42188)
                      ? 60 / (D_psp_08C42180 - D_psp_08C42188)
                      : 0;
            sprintf(D_psp_08C62EC4, "Frame=%d/ResetGraph=%2d/W:%d,H:%d/%2dfps",
                    D_psp_08C62A4C, D_psp_08C62A48, screen_w, screen_h, fps);
            sceGuDebugPrint(0, 264, 0xFFFFFFFF, D_psp_08C62EC4);
        }
        D_psp_08C62A4C++;
        ResetGraph(0);
    }
}

char* off_on[] = {"OFF", "ON"};
char* subBufType[] = {"OFF", "TEMP", "PS", "WOLF", "ALL"};

void DrawOTag(OT_TYPE* p) {
    s32 prevPad, thisPad;
    s32 sp48;
    s32 i;
    s32 cursor;
    s32 x, y;

    D_psp_08C62A74 = p;
    if (PadReadPSP() & PSP_CTRL_R3) {
        prevPad = PadReadPSP();
        cursor = 0;
        sp48 = -1;
        D_psp_08C62EBC = 1;
        while (cursor >= 0) {
            thisPad = PadReadPSP();
            if (prevPad == 0 && thisPad != 0) {
                if (thisPad & PSP_CTRL_CROSS) {
                    while (PadReadPSP() != 0) {
                        VSync(0);
                    }
                    D_psp_08C62EBC = 0;
                    func_psp_0891E994(p);
                    break;
                }
                if (thisPad & PSP_CTRL_UP) {
                    cursor = (cursor + 11) % 12;
                }
                if (thisPad & PSP_CTRL_DOWN) {
                    cursor = (cursor + 1) % 12;
                }
                if (cursor == 11) {
                    if (thisPad & PSP_CTRL_RIGHT) {
                        D_psp_08C630CC += 1;
                    }
                    if (thisPad & PSP_CTRL_LEFT) {
                        D_psp_08C630CC += 0x230;
                    }
                    if (thisPad & PSP_CTRL_RTRIGGER) {
                        D_psp_08C630CC += 0x14;
                    }
                    if (thisPad & PSP_CTRL_LTRIGGER) {
                        D_psp_08C630CC += 0x21D;
                    }
                    D_psp_08C630CC = D_psp_08C630CC % 0x231;
                }
                if (thisPad & PSP_CTRL_CIRCLE) {
                    switch (cursor) {
                    case 0:
                        g_GameClearFlag = g_GameClearFlag ? false : true;
                        break;
                    case 1:
                        D_psp_08C630C4 = D_psp_08C630C4 ? false : true;
                        break;
                    case 2:
                        D_psp_08C630C8 = D_psp_08C630C8 ? false : true;
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
                        D_psp_08C62A70 = D_psp_08C62A70 ? false : true;
                        break;
                    case 6:
                        D_psp_08B42068 = D_psp_08B42068 ? false : true;
                        break;
                    case 7:
                        D_psp_08B4206C =
                            (D_psp_08B4206C < 4) ? D_psp_08B4206C + 1 : 0;
                        break;
                    case 8:
                        D_psp_08C62A44 = D_psp_08C62A44 ? false : true;
                        break;
                    case 9:
                        D_psp_08C62A58 = D_psp_08C62A58 ? false : true;
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
            x = 304;
            y = 0;
            sprintf(D_psp_08C630E4, "=== DEGUG MENU ===");
            sceGuDebugPrint(x, y, 0xFFFFFFFF, D_psp_08C630E4);
            sprintf(D_psp_08C630E4, "GameClearFlag:%s",
                    off_on[g_GameClearFlag ? 1 : 0]);
            sceGuDebugPrint(x + 0x10, y + 0x8, 0xFFFFFFFF, D_psp_08C630E4);
            sprintf(D_psp_08C630E4, "MutekiFlag:%s", off_on[D_psp_08C630C4]);
            sceGuDebugPrint(x + 0x10, y + 0x10, 0xFFFFFFFF, D_psp_08C630E4);
            sprintf(D_psp_08C630E4, "Heart99:%s", off_on[D_psp_08C630C8]);
            sceGuDebugPrint(x + 0x10, y + 0x18, 0xFFFFFFFF, D_psp_08C630E4);
            sprintf(D_psp_08C630E4, "ScreenMode:%d", D_psp_08C62A30);
            sceGuDebugPrint(x + 0x10, y + 0x20, 0xFFFFFFFF, D_psp_08C630E4);
            sprintf(D_psp_08C630E4, "PlayWait:%d", D_psp_08C630E0);
            sceGuDebugPrint(x + 0x10, y + 0x28, 0xFFFFFFFF, D_psp_08C630E4);
            sprintf(D_psp_08C630E4, "FntPrint:%s", off_on[D_psp_08C62A70]);
            sceGuDebugPrint(x + 0x10, y + 0x30, 0xFFFFFFFF, D_psp_08C630E4);
            sprintf(D_psp_08C630E4, "DrawPolyline:%s", off_on[D_psp_08B42068]);
            sceGuDebugPrint(x + 0x10, y + 0x38, 0xFFFFFFFF, D_psp_08C630E4);
            sprintf(
                D_psp_08C630E4, "DispSubBuffer:%s", subBufType[D_psp_08B4206C]);
            sceGuDebugPrint(x + 0x10, y + 0x40, 0xFFFFFFFF, D_psp_08C630E4);
            sprintf(D_psp_08C630E4, "GpuEmuInfo:%s", off_on[D_psp_08C62A44]);
            sceGuDebugPrint(x + 0x10, y + 0x48, 0xFFFFFFFF, D_psp_08C630E4);
            sprintf(D_psp_08C630E4, "CpuGpuTime:%s", off_on[D_psp_08C62A58]);
            sceGuDebugPrint(x + 0x10, y + 0x50, 0xFFFFFFFF, D_psp_08C630E4);
            sprintf(D_psp_08C630E4, "OYAJI:%03d", D_psp_08C630D0);
            sceGuDebugPrint(x + 0x10, y + 0x58, 0xFFFFFFFF, D_psp_08C630E4);
            sprintf(D_psp_08C630E4, "AT3:%03d", D_psp_08C630CC);
            sceGuDebugPrint(x + 0x10, y + 0x60, 0xFFFFFFFF, D_psp_08C630E4);
            sprintf(D_psp_08C630E4, "[%s]", func_9141860(D_psp_08C630CC));
            sceGuDebugPrint(x + 0x10, y + 0x68, 0xFFFFFFFF, D_psp_08C630E4);
            func_psp_0892A8FC();
            if (func_psp_0891B528() & 0x20) {
                sceGuDebugPrint(x, y + (cursor + 1) * 8, 0xFFFFFFFF, "=>");
            }
            func_psp_0891E994(p);
            GsClearVcount();
            DrawSync(0);
            VSync(0);
            func_psp_0891AEC8();
            prevPad = thisPad;
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

s32 func_psp_0891FD20(void* p) {
    DR_OFFSET* ptr;

    ptr = p;
    D_psp_08C629C8 = ptr->ofs[0];
    D_psp_08C629CC = ptr->ofs[1];
    func_psp_0891A608();
    return 0;
}

s32 func_psp_0891FD74(void* p) {
    DR_AREA* ptr;

    ptr = p;
    D_psp_08C629D0.x = ptr->clip.x;
    D_psp_08C629D0.y = ptr->clip.y;
    D_psp_08C629D0.w = ptr->clip.w;
    D_psp_08C629D0.h = ptr->clip.h;
    return 0;
}

s32 func_psp_0891FDC8(void* p) {
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

void func_psp_089201E8(SPRT* ptr, TVertex* v, float arg2, float arg3,
                       float arg4, float arg5, u8 arg6) {
    float u0, v0;
    float u1, v1;
    u16 temp_s2;
    u16 temp_s1;
    u32 var_s0;

    if (arg6 == 0) {
        var_s0 = 0x100;
    } else if (arg6 == 1) {
        var_s0 = 0x80;
    } else if (arg6 == 2) {
        var_s0 = 0x40;
    }
    temp_s2 = (u16)ptr->u0 + arg2;
    temp_s2 %= var_s0;
    temp_s1 = (u16)ptr->v0 + arg4;
    temp_s1 %= 0x100;
    u0 = temp_s2;
    v0 = temp_s1;
    u1 = u0 + (arg3 - 0.4f);
    v1 = v0 + (arg5 - 0.4f);
    v[0].u = u0;
    v[1].u = u1;
    v[0].v = v0;
    v[1].v = v1;
}

s32 func_psp_08920488(void* p) {}

static inline u8* unkInlineFunc(s32 tpage) {
    if (D_psp_089464EC != 0) {
        if ((tpage & 0x1F) == 0x10 && ((tpage >> 7) & 3) == 2) {
            return (u8*)sceGeEdramGetAddr() + 0xCC000;
        }
        if ((tpage & 0xF000) == 0x8000) {
            return (u8*)sceGeEdramGetAddr() + 0xCC000;
        }
        if ((tpage & 0xF000) == 0x4000) {
            return (u8*)sceGeEdramGetAddr() + 0x12C200;
        }
    }
    if ((tpage & 0x1F) == 0 && ((tpage >> 7) & 3) == 2) {
        return func_psp_0891AC60();
    }
    if (D_psp_08C62AA0 == 0) {
        if ((tpage & 0x1F) == 4 && ((tpage >> 7) & 3) == 2) {
            return func_psp_0891AC24();
        }
    }
    return func_psp_0891AAC8(tpage);
}

static inline void unkInlineFunc2(u8* arg0, u8* arg1, s32 arg2) {
    if (arg0 == (u8*)((s32)sceGeEdramGetAddr() + 0xCC000)) {
        if (arg2 == 2) {
            func_psp_08911990(arg0, 0x100);
        } else {
            func_psp_0891149C(arg0, 0x400, 0x100, arg1, arg2);
        }
    } else if (arg0 == func_psp_0891AC24()) {
        func_psp_08911990(arg0, 0x200);
    } else if (arg0 == func_psp_0891AC60()) {
        func_psp_08911990(arg0, 0x200);
    } else if (arg0 == (u8*)((s32)sceGeEdramGetAddr() + 0x12C200)) {
        func_psp_0891149C(arg0, 0x40, 0x40, 0, 2);
    } else {
        func_psp_08910D44(arg0, arg1, arg2);
    }
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/1B0F0", func_psp_08920498);

s32 func_psp_089215A4(void* p) {
    SPRT_16* ptr;
    TVertex* v;

    ptr = p;

    v = (TVertex*)func_psp_089104B4(0xC);
    if (((D_psp_08C629C4 >> 7) & 3) == 2) {
    }
    func_psp_08910D44(
        D_psp_08B42080[D_psp_08C629C4 & 0x1F],
        &D_psp_08B42080[((ptr->clut & 0x3F) << 4) / 0x40 +
                        ((ptr->clut >> 6) / 0x100) * 0x10]
                       [(((ptr->clut & 0x3F) << 4) % 0x40) * 2 +
                        ((ptr->clut >> 6) % 0x100) * 0x80],
        (D_psp_08C629C4 >> 7) & 3);
    if (isSemiTrans(ptr)) {
        switch ((D_psp_08C629C4 >> 5) & 3) {
        case 0:
            func_psp_08911B84(
                1, GU_ADD, GU_FIX, GU_FIX, 0xFF808080, 0xFF808080);
            break;
        case 1:
            func_psp_08911B84(
                1, GU_ADD, GU_FIX, GU_FIX, 0xFFFFFFFF, 0xFFFFFFFF);
            break;
        case 2:
            func_psp_08911B84(
                1, GU_REVERSE_SUBTRACT, GU_FIX, GU_FIX, 0xFFFFFFFF, 0xFFFFFFFF);
            break;
        case 3:
            func_psp_08911B84(
                1, GU_ADD, GU_FIX, GU_FIX, 0xFF404040, 0xFFFFFFFF);
            break;
        default:
            func_psp_08911B84(
                0, GU_ADD, GU_FIX, GU_FIX, 0xFF808080, 0xFF808080);
            break;
        }
    } else {
        func_psp_08911B84(0, GU_ADD, GU_FIX, GU_FIX, 0xFF808080, 0xFF808080);
    }
    if (isFlatShaded(ptr)) {
        v[0].c = v[1].c = GU_RGBA(ptr->r0, ptr->g0, ptr->b0, 0x80);
    } else {
        v[0].c = v[1].c = white;
    }
    __asm__(
        ".set		push\n"      // save assembler option
        ".set		noreorder\n" // suppress reordering
        "lv.s		s700, 0xC(%1)\n"
        "vs2i.p		c710, c700\n"
        "vi2f.p		c300, c710, 16\n"
        "vadd.p		c300, c300, c410\n"
        "sv.s		s300, 0xC(%0)\n"
        "sv.s		s301, 0x10(%0)\n"
        "sv.s		s302, 0x14(%0)\n"
        "vadd.p		c310, c300, c420\n"
        "sv.s		s310, 0x24(%0)\n"
        "sv.s		s311, 0x28(%0)\n"
        "sv.s		s312, 0x2C(%0)\n"
        "lbu		$4, 0x10(%1)\n"
        "lbu		$5, 0x11(%1)\n"
        "mtv		$4, s610\n"
        "mtv		$5, s611\n"
        "vi2f.p		c620, c610, 0\n"
        "sv.s		s620, 0(%0)\n"
        "sv.s		s621, 4(%0)\n"
        "vadd.p		c630, c620, c420\n"
        "sv.s		s630, 0x18(%0)\n"
        "sv.s		s631, 0x1C(%0)\n"
        ".set		pop\n" // suppress reordering
        : "+r"(v)
        : "r"(ptr));
    if (ptr->code & 0x40) {
        func_psp_08912070(D_psp_089464F0, 0, 0, 0);
        func_psp_08910C74(v, 2, sizeof(TVertex), GU_SPRITES,
                          GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888 |
                              GU_TEXTURE_32BITF);
        func_psp_089120E4();
        func_psp_08910C74(v, 2, sizeof(TVertex), GU_SPRITES,
                          GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888 |
                              GU_TEXTURE_32BITF);
    } else {
        func_psp_0891214C(D_psp_089464F0, 0, 0, 0);
        func_psp_08910C74(v, 2, sizeof(TVertex), GU_SPRITES,
                          GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888 |
                              GU_TEXTURE_32BITF);
    }
    func_psp_0891B1F8(v[0].x, v[0].y, v[1].x, v[1].y, red);
    D_psp_08C62A50++;
    return 0;
}

s32 func_psp_08921A38(void* p) {
    Vertex v[4];
    POLY_G4* ptr;
    u8 var_s1;

    ptr = p;

    if (isSemiTrans(ptr)) {
        var_s1 = 0x80;
        func_psp_089113A8((D_psp_08C629C4 >> 5) & 3, var_s1);
    } else {
        func_psp_089113A8(-1, 0x80);
    }
    v[0].x = D_psp_08C629C8 + ptr->x0;
    v[0].y = D_psp_08C629CC + ptr->y0;
    v[0].z = 1.0f;
    v[1].x = D_psp_08C629C8 + ptr->x1;
    v[1].y = D_psp_08C629CC + ptr->y1;
    v[1].z = 1.0f;
    v[2].x = D_psp_08C629C8 + ptr->x2;
    v[2].y = D_psp_08C629CC + ptr->y2;
    v[2].z = 1.0f;
    v[3].x = D_psp_08C629C8 + ptr->x3;
    v[3].y = D_psp_08C629CC + ptr->y3;
    v[3].z = 1.0f;
    v[0].c = GU_RGBA(ptr->r0, ptr->g0, ptr->b0, 0x80);
    v[1].c = GU_RGBA(ptr->r1, ptr->g1, ptr->b1, 0x80);
    v[2].c = GU_RGBA(ptr->r2, ptr->g2, ptr->b2, 0x80);
    v[3].c = GU_RGBA(ptr->r3, ptr->g3, ptr->b3, 0x80);
    if (D_psp_08C62A40 == 0) {
        func_psp_0891DB9C(v, 4);
    }
    func_psp_08912008();
    func_psp_08910A80(v, 4, sizeof(Vertex), GU_TRIANGLE_STRIP,
                      GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    func_psp_0891B1F8(v[0].x, v[0].y, v[3].x, v[3].y, blue);
    return 0;
}

s32 func_psp_08921D44(void* p) {
    POLY_FT4* ptr;
    s32 isSemiTrans;
    u8 temp_s5;
    u8* var_s7;
    u8* var_s2;
    TVertex* v;

    ptr = p;
    var_s7 = NULL;
    isSemiTrans = isSemiTrans(ptr);
    D_psp_08C629C4 = ptr->tpage;
    v = (TVertex*)SP(0);
    temp_s5 = (ptr->tpage >> 7) & 3;
    var_s2 = unkInlineFunc(ptr->tpage);
    if (temp_s5 != 2) {
        var_s7 = func_psp_0891B8F0(ptr->clut, temp_s5, 1);
    }
    unkInlineFunc2(var_s2, var_s7, temp_s5);
    if (isSemiTrans(ptr)) {
        func_psp_089113A8((ptr->tpage >> 5) & 3, 0x80);
    } else {
        func_psp_08910660(0);
    }
    if (isFlatShaded(ptr)) {
        v[0].c = GU_RGBA(ptr->r0, ptr->g0, ptr->b0, 0x80);
        v[1].c = v[2].c = v[3].c = v[0].c;
    } else {
        v[0].c = v[1].c = v[2].c = v[3].c = white;
    }
    v[0].x = D_psp_08C629C8 + ptr->x0;
    v[0].y = D_psp_08C629CC + ptr->y0;
    v[0].z = 1.0f;
    v[1].x = D_psp_08C629C8 + ptr->x1;
    v[1].y = D_psp_08C629CC + ptr->y1;
    v[1].z = 1.0f;
    v[2].x = D_psp_08C629C8 + ptr->x2;
    v[2].y = D_psp_08C629CC + ptr->y2;
    v[2].z = 1.0f;
    v[3].x = D_psp_08C629C8 + ptr->x3;
    v[3].y = D_psp_08C629CC + ptr->y3;
    v[3].z = 1.0f;

    v[0].u = ptr->u0;
    v[0].v = ptr->v0;
    v[1].u = ptr->u1;
    v[1].v = ptr->v1;
    v[2].u = ptr->u2;
    v[2].v = ptr->v2;
    v[3].u = ptr->u3;
    v[3].v = ptr->v3;

    if (D_psp_08C62A40 == 0) {
        func_psp_0891D9F4(v, 4);
    }
    func_psp_08911F24(isSemiTrans, D_psp_089464F0);
    func_psp_08910A80(
        v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
        GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888 | GU_TEXTURE_32BITF);
    if (isSemiTrans) {
        func_psp_08911FA0();
        func_psp_08910A80(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                          GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888 |
                              GU_TEXTURE_32BITF);
    }
    if (D_psp_08B42068 == true) {
        s32 color = red;
        func_psp_0891B118(v[0].x, v[0].y, v[1].x, v[1].y, color);
        func_psp_0891B118(v[1].x, v[1].y, v[3].x, v[3].y, color);
        func_psp_0891B118(v[3].x, v[3].y, v[2].x, v[2].y, color);
        func_psp_0891B118(v[2].x, v[2].y, v[0].x, v[0].y, color);
    }
    D_psp_08C62A54++;
    return 0;
}

s32 func_psp_089225D8(void* p) {
    POLY_GT3* ptr;
    TVertex* v;
    u8 temp_s3;
    u8* var_v0;
    u8* var_s1;
    s32 isSemiTrans;

    ptr = p;

    var_s1 = NULL;
    isSemiTrans = isSemiTrans(ptr);
    D_psp_08C629C4 = ptr->tpage;
    v = (TVertex*)func_psp_089104B4(0x12);
    temp_s3 = (ptr->tpage >> 7) & 3;
    var_v0 = unkInlineFunc(ptr->tpage);
    if (temp_s3 != 2) {
        var_s1 = func_psp_0891B8F0(ptr->clut, temp_s3, 1);
    }
    unkInlineFunc2(var_v0, var_s1, temp_s3);
    if (isSemiTrans(ptr)) {
        func_psp_089113A8((ptr->tpage >> 5) & 3, 0x80);
    } else {
        func_psp_08910660(0);
    }
    if (isFlatShaded(ptr)) {
        v[0].c = GU_RGBA(ptr->r0, ptr->g0, ptr->b0, 0x80);
        v[1].c = GU_RGBA(ptr->r1, ptr->g1, ptr->b1, 0x80);
        v[2].c = GU_RGBA(ptr->r2, ptr->g2, ptr->b2, 0x80);
    } else {
        v[0].c = v[1].c = v[2].c = white;
    }
    __asm__(
        ".set		push\n"      // save assembler option
        ".set		noreorder\n" // suppress reordering
        "lv.s		s700, 0xC(%1)\n"
        "vs2i.p		c710, c700\n"
        "vi2f.p		c300, c710, 16\n"
        "vadd.p		c300, c300, c410\n"
        "sv.s		s300, 0xC(%0)\n"
        "sv.s		s301, 0x10(%0)\n"
        "sv.s		s302, 0x14(%0)\n"
        "lv.s		s700, 0x18(%1)\n"
        "vs2i.p		c710, c700\n"
        "vi2f.p		c300, c710, 16\n"
        "vadd.p		c300, c300, c410\n"
        "sv.s		s300, 0x24(%0)\n"
        "sv.s		s301, 0x28(%0)\n"
        "sv.s		s302, 0x2C(%0)\n"
        "lv.s		s700, 0x24(%1)\n"
        "vs2i.p		c710, c700\n"
        "vi2f.p		c300, c710, 16\n"
        "vadd.p		c300, c300, c410\n"
        "sv.s		s300, 0x3C(%0)\n"
        "sv.s		s301, 0x40(%0)\n"
        "sv.s		s302, 0x44(%0)\n"
        "lbu		$4, 0x10(%1)\n"
        "lbu		$5, 0x11(%1)\n"
        "mtv		$4, s610\n"
        "mtv		$5, s611\n"
        "vi2f.p		c620, c610, 0\n"
        "sv.s		s620, 0(%0)\n"
        "sv.s		s621, 4(%0)\n"
        "lbu		$4, 0x1C(%1)\n"
        "lbu		$5, 0x1D(%1)\n"
        "mtv		$4, s610\n"
        "mtv		$5, s611\n"
        "vi2f.p		c620, c610, 0\n"
        "sv.s		s620, 0x18(%0)\n"
        "sv.s		s621, 0x1C(%0)\n"
        "lbu		$4, 0x28(%1)\n"
        "lbu		$5, 0x29(%1)\n"
        "mtv		$4, s610\n"
        "mtv		$5, s611\n"
        "vi2f.p		c620, c610, 0\n"
        "sv.s		s620, 0x30(%0)\n"
        "sv.s		s621, 0x34(%0)\n"
        ".set		pop\n" // suppress reordering
        : "+r"(v)
        : "r"(ptr));

    if (D_psp_08C62A40 == 0) {
        func_psp_0891D9F4(v, 3);
    }
    func_psp_08911F24(isSemiTrans, D_psp_089464F0);
    func_psp_08910C74(
        v, 3, sizeof(TVertex), GU_TRIANGLE_STRIP,
        GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888 | GU_TEXTURE_32BITF);
    if (isSemiTrans) {
        func_psp_08911FA0();
        func_psp_08910C74(v, 3, sizeof(TVertex), GU_TRIANGLE_STRIP,
                          GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888 |
                              GU_TEXTURE_32BITF);
    }
    if (D_psp_08B42068 == true) {
        s32 color = green;
        func_psp_0891B118(v[0].x, v[0].y, v[1].x, v[1].y, color);
        func_psp_0891B118(v[1].x, v[1].y, v[2].x, v[2].y, color);
        func_psp_0891B118(v[2].x, v[2].y, v[0].x, v[0].y, color);
    }
    D_psp_08C62A54++;
    return 0;
}

s32 func_psp_08922C14(void* p) {
    POLY_GT4* ptr;
    s32 r, g, b;
    s32 fix;
    TVertex* v;

    ptr = p;
    D_psp_08C629C4 = ptr->tpage;
    v = (TVertex*)SP(0);

    func_psp_0891149C((s32)sceGeEdramGetAddr() + 0x12C200, 0x40, 0x40, 0, 2);
    r = (ptr->r0 >= 0x80) ? 0xFF : ptr->r0 * 2;
    g = (ptr->g0 >= 0x80) ? 0xFF : ptr->g0 * 2;
    b = (ptr->b0 >= 0x80) ? 0xFF : ptr->b0 * 2;
    r = g = b;
    fix = GU_RGBA(r, g, b, 0);
    func_psp_08910660(1);
    func_psp_08910810(GU_ADD, GU_FIX, GU_FIX, fix, 0x00FFFFFF - fix);
    v[0].c = v[1].c = v[2].c = v[3].c = white;
    v[0].x = D_psp_08C629C8 + ptr->x0;
    v[0].y = D_psp_08C629CC + ptr->y0;
    v[1].x = D_psp_08C629C8 + ptr->x1;
    v[1].y = D_psp_08C629CC + ptr->y1;
    v[2].x = D_psp_08C629C8 + ptr->x2;
    v[2].y = D_psp_08C629CC + ptr->y2;
    v[3].x = D_psp_08C629C8 + ptr->x3;
    v[3].y = D_psp_08C629CC + ptr->y3;
    v[0].z = v[1].z = v[2].z = v[3].z = 1.0f;
    v[0].u = ptr->u0;
    v[0].v = ptr->v0;
    v[1].u = ptr->u1;
    v[1].v = ptr->v1;
    v[2].u = ptr->u2;
    v[2].v = ptr->v2;
    v[3].u = ptr->u3;
    v[3].v = ptr->v3;
    func_psp_0891068C(0);
    func_psp_089105DC(1);
    func_psp_08911AB8(0, 0, 0);
    func_psp_08910A80(
        v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
        GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888 | GU_TEXTURE_32BITF);
    if (D_psp_08B42068 == true) {
        s32 color = magenta;
        func_psp_0891B118(v[0].x, v[0].y, v[1].x, v[1].y, color);
        func_psp_0891B118(v[1].x, v[1].y, v[3].x, v[3].y, color);
        func_psp_0891B118(v[3].x, v[3].y, v[2].x, v[2].y, color);
        func_psp_0891B118(v[2].x, v[2].y, v[0].x, v[0].y, color);
    }
    D_psp_08C62A54++;
    return 0;
}

s32 func_psp_089231F8(void* p) {
    POLY_GT4* ptr;
    u8 temp_s5;
    u8* var_fp;
    s32 isSemiTrans;
    u8* var_s2;
    TVertex* v;

    ptr = p;
    var_fp = NULL;
    isSemiTrans = isSemiTrans(ptr);
    D_psp_08C629C4 = ptr->tpage;
    temp_s5 = (ptr->tpage >> 7) & 3;
    var_s2 = unkInlineFunc(ptr->tpage);
    if (temp_s5 != 2) {
        var_fp = func_psp_0891B8F0(ptr->clut, temp_s5, 1);
    }
    unkInlineFunc2(var_s2, var_fp, temp_s5);
    if (isSemiTrans(ptr)) {
        switch ((ptr->tpage >> 5) & 3) {
        case 0:
            func_psp_08911B84(
                1, GU_ADD, GU_FIX, GU_FIX, 0xFF808080, 0xFF808080);
            break;
        case 1:
            func_psp_08911B84(
                1, GU_ADD, GU_FIX, GU_FIX, 0xFFFFFFFF, 0xFFFFFFFF);
            break;
        case 2:
            func_psp_08911B84(
                1, GU_REVERSE_SUBTRACT, GU_FIX, GU_FIX, 0xFFFFFFFF, 0xFFFFFFFF);
            break;
        case 3:
            func_psp_08911B84(
                1, GU_ADD, GU_FIX, GU_FIX, 0xFF404040, 0xFFFFFFFF);
            break;
        default:
            func_psp_08911B84(
                0, GU_ADD, GU_FIX, GU_FIX, 0xFF808080, 0xFF808080);
            break;
        }
    } else {
        func_psp_08911B84(0, GU_ADD, GU_FIX, GU_FIX, 0xFF808080, 0xFF808080);
    }
    v = (TVertex*)func_psp_089104B4(0x18);
    if (isFlatShaded(ptr)) {
        v[0].c = GU_RGBA(ptr->r0, ptr->g0, ptr->b0, 0x80);
        v[1].c = GU_RGBA(ptr->r1, ptr->g1, ptr->b1, 0x80);
        v[2].c = GU_RGBA(ptr->r2, ptr->g2, ptr->b2, 0x80);
        v[3].c = GU_RGBA(ptr->r3, ptr->g3, ptr->b3, 0x80);
    } else {
        v[0].c = v[1].c = v[2].c = v[3].c = 0xFFFFFFFF;
    }
    v[0].x = D_psp_08C629C8 + ptr->x0;
    v[0].y = D_psp_08C629CC + ptr->y0;
    v[1].x = D_psp_08C629C8 + ptr->x1;
    v[1].y = D_psp_08C629CC + ptr->y1;
    v[2].x = D_psp_08C629C8 + ptr->x2;
    v[2].y = D_psp_08C629CC + ptr->y2;
    v[3].x = D_psp_08C629C8 + ptr->x3;
    v[3].y = D_psp_08C629CC + ptr->y3;
    v[0].z = v[1].z = v[2].z = v[3].z = 1.0f;
    v[0].u = ptr->u0;
    v[0].v = ptr->v0;
    v[1].u = ptr->u1;
    v[1].v = ptr->v1;
    v[2].u = ptr->u2;
    v[2].v = ptr->v2;
    v[3].u = ptr->u3;
    v[3].v = ptr->v3;
    if (D_psp_08C62A40 == 0) {
        func_psp_0891D9F4(v, 4);
    }
    if (D_psp_08C62A40 == 1) {
        func_psp_08910634(0);
        if (isSemiTrans) {
            func_psp_0891068C(1);
            func_psp_089106B8(GU_ALWAYS, 0, 0);
            func_psp_089105DC(1);
            func_psp_08911AB8(0, 0, 0);
            func_psp_08910C74(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                              GU_TRANSFORM_2D | GU_VERTEX_32BITF |
                                  GU_COLOR_8888 | GU_TEXTURE_32BITF);
        } else {
            func_psp_0891214C(D_psp_089464F0, 0, 0, 0);
            func_psp_08910C74(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                              GU_TRANSFORM_2D | GU_VERTEX_32BITF |
                                  GU_COLOR_8888 | GU_TEXTURE_32BITF);
        }
    } else if ((temp_s5 == 2) && !isSemiTrans) {
        if ((ptr->x1 - ptr->x0) != 1) {
            func_psp_08911F24(0, D_psp_089464F0);
            func_psp_08910C74(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                              GU_TRANSFORM_2D | GU_VERTEX_32BITF |
                                  GU_COLOR_8888 | GU_TEXTURE_32BITF);
        } else {
            func_psp_08911F24(0, D_psp_089464F0);
            func_psp_08911B7C();
            func_psp_08910C74(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                              GU_TRANSFORM_2D | GU_VERTEX_32BITF |
                                  GU_COLOR_8888 | GU_TEXTURE_32BITF);
        }
    } else {
        if (ptr->u0 > ptr->u1) {
            v[0].u++;
            v[1].u++;
            v[2].u++;
            v[3].u++;
        }
        if (ptr->v0 > ptr->v2) {
            v[0].v++;
            v[1].v++;
            v[2].v++;
            v[3].v++;
        }
        if (isSemiTrans) {
            func_psp_0891068C(1);
            func_psp_089106B8(GU_ALWAYS, 0, 0);
            func_psp_089105DC(1);
            func_psp_08911AB8(0, 0, 0);
            func_psp_08910C74(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                              GU_TRANSFORM_2D | GU_VERTEX_32BITF |
                                  GU_COLOR_8888 | GU_TEXTURE_32BITF);
        } else {
            func_psp_0891214C(D_psp_089464F0, 0, 0, 0);
            func_psp_08910C74(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                              GU_TRANSFORM_2D | GU_VERTEX_32BITF |
                                  GU_COLOR_8888 | GU_TEXTURE_32BITF);
        }
    }
    if (D_psp_08B42068 == true) {
        s32 color = green;
        func_psp_0891B118(v[0].x, v[0].y, v[1].x, v[1].y, color);
        func_psp_0891B118(v[1].x, v[1].y, v[3].x, v[3].y, color);
        func_psp_0891B118(v[3].x, v[3].y, v[2].x, v[2].y, color);
        func_psp_0891B118(v[2].x, v[2].y, v[0].x, v[0].y, color);
    }
    D_psp_08C62A54++;
    return 0;
}

s32 func_psp_08923FA4(void* p) {
    POLY_GT4 sp78;
    POLY_GT4 sp40;
    SPRT sp28;

    u8 temp_s4;
    s32 var_a0;
    s32 dx0, dy0;
    s32 dx1, dy1;
    s32 i;
    s32 var_s2_3;
    s32 var_s1_2;
    u8* var_v0;
    u8* var_s2;
    TVertex* v;
    s32 isSemiTrans;
    POLY_GT4* ptr;

    ptr = p;
    var_s2 = NULL;
    isSemiTrans = isSemiTrans(ptr);
    if (LOW(((POLY_GT4*)p)->x0) == 0 && LOW(((POLY_GT4*)p)->x1) == 0 &&
        LOW(((POLY_GT4*)p)->x2) == 0 && LOW(((POLY_GT4*)p)->x3) == 0) {
        return 0;
    }
    D_psp_08C629C4 = ptr->tpage;
    if (((ptr->tpage >> 7) & 3) == 2 && (ptr->tpage & 0x1F) != 0x10) {
        if (ptr->u1 == 0xFF && ptr->u0 == 0) {
            sp78.tag = ptr->tag;
            sp78.len = ptr->len;
            sp78.r0 = ptr->r0;
            sp78.g0 = ptr->g0;
            sp78.b0 = ptr->b0;
            sp78.code = ptr->code;
            sp78.x0 = ptr->x0;
            sp78.y0 = ptr->y0;
            sp78.u0 = ptr->u0;
            sp78.v0 = ptr->v0;
            sp78.clut = ptr->clut;
            sp78.r1 = ptr->r1;
            sp78.g1 = ptr->g1;
            sp78.b1 = ptr->b1;
            sp78.p1 = ptr->p1;
            sp78.x1 = ptr->x1;
            sp78.y1 = ptr->y1;
            sp78.u1 = ptr->u1;
            sp78.v1 = ptr->v1;
            sp78.tpage = ptr->tpage;
            sp78.r2 = ptr->r2;
            sp78.g2 = ptr->g2;
            sp78.b2 = ptr->b2;
            sp78.p2 = ptr->p2;
            sp78.x2 = ptr->x2;
            sp78.y2 = ptr->y2;
            sp78.u2 = ptr->u2;
            sp78.v2 = ptr->v2;
            sp78.pad2 = ptr->pad2;
            sp78.r3 = ptr->r3;
            sp78.g3 = ptr->g3;
            sp78.b3 = ptr->b3;
            sp78.p3 = ptr->p3;
            sp78.x3 = ptr->x3;
            sp78.y3 = ptr->y3;
            sp78.u3 = ptr->u3;
            sp78.v3 = ptr->v3;
            sp78.pad3 = ptr->pad3;
            dx0 = ((ptr->x1 - ptr->x0) + 1) / 4;
            dy0 = ((ptr->y1 - ptr->y0) + 1) / 4;
            dx1 = ((ptr->x3 - ptr->x2) + 1) / 4;
            dy1 = ((ptr->y3 - ptr->y2) + 1) / 4;
            for (i = 0; i < 4; i++) {
                sp78.x0 = ptr->x0 + dx0 * i;
                sp78.y0 = ptr->y0 + dy0 * i;
                sp78.x1 = sp78.x0 + dx0;
                sp78.y1 = sp78.y0 + dy0;
                sp78.x2 = ptr->x2 + dx1 * i;
                sp78.y2 = ptr->y2 + dy1 * i;
                sp78.x3 = sp78.x2 + dx1;
                sp78.y3 = sp78.y2 + dy1;
                sp78.u0 = sp78.u2 = 0;
                sp78.u1 = sp78.u3 = 0x3F;
                func_psp_08923FA4(&sp78);
                sp78.tpage++;
            }
            return 0;
        }
        if (ptr->u1 == 0xF9 && ptr->u0 == 6) {
            sp40.tag = ptr->tag;
            sp40.len = ptr->len;
            sp40.r0 = ptr->r0;
            sp40.g0 = ptr->g0;
            sp40.b0 = ptr->b0;
            sp40.code = ptr->code;
            sp40.x0 = ptr->x0;
            sp40.y0 = ptr->y0;
            sp40.u0 = ptr->u0;
            sp40.v0 = ptr->v0;
            sp40.clut = ptr->clut;
            sp40.r1 = ptr->r1;
            sp40.g1 = ptr->g1;
            sp40.b1 = ptr->b1;
            sp40.p1 = ptr->p1;
            sp40.x1 = ptr->x1;
            sp40.y1 = ptr->y1;
            sp40.u1 = ptr->u1;
            sp40.v1 = ptr->v1;
            sp40.tpage = ptr->tpage;
            sp40.r2 = ptr->r2;
            sp40.g2 = ptr->g2;
            sp40.b2 = ptr->b2;
            sp40.p2 = ptr->p2;
            sp40.x2 = ptr->x2;
            sp40.y2 = ptr->y2;
            sp40.u2 = ptr->u2;
            sp40.v2 = ptr->v2;
            sp40.pad2 = ptr->pad2;
            sp40.r3 = ptr->r3;
            sp40.g3 = ptr->g3;
            sp40.b3 = ptr->b3;
            sp40.p3 = ptr->p3;
            sp40.x3 = ptr->x3;
            sp40.y3 = ptr->y3;
            sp40.u3 = ptr->u3;
            sp40.v3 = ptr->v3;
            sp40.pad3 = ptr->pad3;
            var_s2_3 = ptr->x0;
            while (var_s2_3 < ptr->x1) {
                var_a0 = var_s2_3 % 0x40;
                var_s1_2 = 0x40 - var_a0;
                if ((var_s2_3 + var_s1_2) > ptr->x1) {
                    var_s1_2 = ptr->x1 - var_s2_3;
                }
                sp40.x0 = sp40.x2 = var_s2_3;
                sp40.x1 = sp40.x3 = var_s2_3 + var_s1_2;
                sp40.u0 = sp40.u2 = var_a0;
                sp40.u1 = sp40.u3 = (var_a0 + var_s1_2) - 1;
                func_psp_08923FA4(&sp40);
                sp40.tpage++;
                var_s2_3 += var_s1_2;
            }
            return 0;
        }
    }
    if (ptr->tpage & 0xF000) {
        if ((ptr->tpage & 0xF000) == 0x4000) {
            return func_psp_08922C14(p);
        }
        if ((ptr->tpage & 0xF000) == 0x2000) {
            func_psp_0891B2CC(ptr->x0, ptr->y0, ptr->x3 - ptr->x0,
                              ptr->y3 - ptr->y0, GU_RGBA(0, 0, 8, 0x80));
            sp28.u0 = ptr->u0;
            sp28.v0 = ptr->v0;
            sp28.w = ptr->x3 - ptr->x0;
            sp28.h = ptr->y3 - ptr->y0;
            sp28.x0 = ptr->x0;
            sp28.y0 = ptr->y0;
            sp28.r0 = sp28.g0 = sp28.b0 = 0x80;
            sp28.clut = ptr->clut;
            sp28.code = ptr->code;
            D_psp_08C629C4 &= 0x9FF;
            return func_psp_08920498(&sp28);
        }
        if ((ptr->tpage & 0xF000) == 0x1000) {
            return func_psp_089231F8(p);
        }
    }
    temp_s4 = (ptr->tpage >> 7) & 3;
    var_v0 = unkInlineFunc(ptr->tpage);
    if (temp_s4 != 2) {
        var_s2 = func_psp_0891B8F0(ptr->clut, temp_s4, 1);
    }
    unkInlineFunc2(var_v0, var_s2, temp_s4);
    if (isSemiTrans(ptr)) {
        switch ((ptr->tpage >> 5) & 3) {
        case 0:
            func_psp_08911B84(
                1, GU_ADD, GU_FIX, GU_FIX, 0xFF808080, 0xFF808080);
            break;
        case 1:
            func_psp_08911B84(
                1, GU_ADD, GU_FIX, GU_FIX, 0xFFFFFFFF, 0xFFFFFFFF);
            break;
        case 2:
            func_psp_08911B84(
                1, GU_REVERSE_SUBTRACT, GU_FIX, GU_FIX, 0xFFFFFFFF, 0xFFFFFFFF);
            break;
        case 3:
            func_psp_08911B84(
                1, GU_ADD, GU_FIX, GU_FIX, 0xFF404040, 0xFFFFFFFF);
            break;
        default:
            func_psp_08911B84(
                0, GU_ADD, GU_FIX, GU_FIX, 0xFF808080, 0xFF808080);
            break;
        }
    } else {
        func_psp_08911B84(0, GU_ADD, GU_FIX, GU_FIX, 0xFF808080, 0xFF808080);
    }
    v = (TVertex*)func_psp_089104B4(0x18);
    if (isFlatShaded(ptr)) {
        v[0].c = GU_RGBA(ptr->r0, ptr->g0, ptr->b0, 0x80);
        v[1].c = GU_RGBA(ptr->r1, ptr->g1, ptr->b1, 0x80);
        v[2].c = GU_RGBA(ptr->r2, ptr->g2, ptr->b2, 0x80);
        v[3].c = GU_RGBA(ptr->r3, ptr->g3, ptr->b3, 0x80);
    } else {
        v[0].c = v[1].c = v[2].c = v[3].c = 0xFFFFFFFF;
    }
    __asm__(
        ".set		push\n"      // save assembler option
        ".set		noreorder\n" // suppress reordering
        "lv.s		s700, 0xC(%1)\n"
        "vs2i.p		c710, c700\n"
        "vi2f.p		c300, c710, 16\n"
        "vadd.p		c300, c300, c410\n"
        "sv.s		s300, 0xC(%0)\n"
        "sv.s		s301, 0x10(%0)\n"
        "sv.s		s302, 0x14(%0)\n"
        "lv.s		s700, 0x18(%1)\n"
        "vs2i.p		c710, c700\n"
        "vi2f.p		c300, c710, 16\n"
        "vadd.p		c300, c300, c410\n"
        "sv.s		s300, 0x24(%0)\n"
        "sv.s		s301, 0x28(%0)\n"
        "sv.s		s302, 0x2C(%0)\n"
        "lv.s		s700, 0x24(%1)\n"
        "vs2i.p		c710, c700\n"
        "vi2f.p		c300, c710, 16\n"
        "vadd.p		c300, c300, c410\n"
        "sv.s		s300, 0x3C(%0)\n"
        "sv.s		s301, 0x40(%0)\n"
        "sv.s		s302, 0x44(%0)\n"
        "lv.s		s700, 0x30(%1)\n"
        "vs2i.p		c710, c700\n"
        "vi2f.p		c300, c710, 16\n"
        "vadd.p		c300, c300, c410\n"
        "sv.s		s300, 0x54(%0)\n"
        "sv.s		s301, 0x59(%0)\n"
        "sv.s		s302, 0x5E(%0)\n"
        "lbu		$4, 0x10(%1)\n"
        "lbu		$5, 0x11(%1)\n"
        "mtv		$4, s610\n"
        "mtv		$5, s611\n"
        "vi2f.p		c620, c610, 0\n"
        "sv.s		s620, 0(%0)\n"
        "sv.s		s621, 4(%0)\n"
        "lbu		$4, 0x1C(%1)\n"
        "lbu		$5, 0x1D(%1)\n"
        "mtv		$4, s610\n"
        "mtv		$5, s611\n"
        "vi2f.p		c620, c610, 0\n"
        "sv.s		s620, 0x18(%0)\n"
        "sv.s		s621, 0x1C(%0)\n"
        "lbu		$4, 0x28(%1)\n"
        "lbu		$5, 0x29(%1)\n"
        "mtv		$4, s610\n"
        "mtv		$5, s611\n"
        "vi2f.p		c620, c610, 0\n"
        "sv.s		s620, 0x30(%0)\n"
        "sv.s		s621, 0x34(%0)\n"
        "lbu		$4, 0x34(%1)\n"
        "lbu		$5, 0x35(%1)\n"
        "mtv		$4, s610\n"
        "mtv		$5, s611\n"
        "vi2f.p		c620, c610, 0\n"
        "sv.s		s620, 0x48(%0)\n"
        "sv.s		s621, 0x4D(%0)\n"
        ".set		pop\n" // suppress reordering
        : "+r"(v)
        : "r"(ptr));

    if (D_psp_08C62A40 == 0) {
        func_psp_0891D9F4(v, 4);
    }
    if (D_psp_08C62A40 == 1) {
        func_psp_08910634(0);
        if (isSemiTrans) {
            func_psp_08912070(D_psp_089464F0, 0, 0, 0);
            func_psp_08910C74(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                              GU_TRANSFORM_2D | GU_VERTEX_32BITF |
                                  GU_COLOR_8888 | GU_TEXTURE_32BITF);
            func_psp_089120E4();
            func_psp_08910C74(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                              GU_TRANSFORM_2D | GU_VERTEX_32BITF |
                                  GU_COLOR_8888 | GU_TEXTURE_32BITF);
        } else {
            func_psp_0891214C(D_psp_089464F0, 0, 0, 0);
            func_psp_08910C74(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                              GU_TRANSFORM_2D | GU_VERTEX_32BITF |
                                  GU_COLOR_8888 | GU_TEXTURE_32BITF);
        }
    } else if ((temp_s4 == 2) && !isSemiTrans) {
        if ((ptr->x1 - ptr->x0) != 1) {
            func_psp_08911F24(0, D_psp_089464F0);
            func_psp_08910C74(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                              GU_TRANSFORM_2D | GU_VERTEX_32BITF |
                                  GU_COLOR_8888 | GU_TEXTURE_32BITF);
        } else {
            func_psp_08911F24(0, D_psp_089464F0);
            func_psp_08911B7C();
            func_psp_08910C74(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                              GU_TRANSFORM_2D | GU_VERTEX_32BITF |
                                  GU_COLOR_8888 | GU_TEXTURE_32BITF);
        }
    } else {
        if (ptr->u0 > ptr->u1) {
            v[0].u++;
            v[1].u++;
            v[2].u++;
            v[3].u++;
        }
        if (ptr->v0 > ptr->v2) {
            v[0].v++;
            v[1].v++;
            v[2].v++;
            v[3].v++;
        }
        if (isSemiTrans) {
            func_psp_08912070(D_psp_089464F0, 0, 0, 0);
            func_psp_08910C74(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                              GU_TRANSFORM_2D | GU_VERTEX_32BITF |
                                  GU_COLOR_8888 | GU_TEXTURE_32BITF);
            func_psp_089120E4();
            func_psp_08910C74(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                              GU_TRANSFORM_2D | GU_VERTEX_32BITF |
                                  GU_COLOR_8888 | GU_TEXTURE_32BITF);
        } else {
            func_psp_0891214C(D_psp_089464F0, 0, 0, 0);
            func_psp_08910C74(v, 4, sizeof(TVertex), GU_TRIANGLE_STRIP,
                              GU_TRANSFORM_2D | GU_VERTEX_32BITF |
                                  GU_COLOR_8888 | GU_TEXTURE_32BITF);
        }
    }
    if (D_psp_08B42068 == true) {
        s32 color = green;
        func_psp_0891B118(v[0].x, v[0].y, v[1].x, v[1].y, color);
        func_psp_0891B118(v[1].x, v[1].y, v[3].x, v[3].y, color);
        func_psp_0891B118(v[3].x, v[3].y, v[2].x, v[2].y, color);
        func_psp_0891B118(v[2].x, v[2].y, v[0].x, v[0].y, color);
    }
    D_psp_08C62A54++;
    return 0;
}

s32 func_psp_08925194(void* p) {
    Vertex v[4];
    TILE* ptr;
    u8 var_s1;

    ptr = p;

    if (ptr->w == 0 || ptr->h == 0) {
        return 0;
    }
    if (D_psp_08C62A40 == 1) {
        return 0;
    }
    if (isSemiTrans(ptr)) {
        var_s1 = 0x80;
        if (((D_psp_08C629C4 >> 5) & 3) == 2) {
            var_s1 = (ptr->b0 + ptr->g0 + ptr->r0) / 3;
        }
        func_psp_089113A8((D_psp_08C629C4 >> 5) & 3, var_s1);
    } else {
        func_psp_089113A8(-1, 0x80);
    }
    v[0].x = D_psp_08C629C8 + ptr->x0;
    v[0].y = D_psp_08C629CC + ptr->y0;
    v[1].x = D_psp_08C629C8 + ptr->x0 + ptr->w;
    v[1].y = D_psp_08C629CC + ptr->y0;
    v[2].x = D_psp_08C629C8 + ptr->x0;
    v[2].y = D_psp_08C629CC + ptr->y0 + ptr->h;
    v[3].x = D_psp_08C629C8 + ptr->x0 + ptr->w;
    v[3].y = D_psp_08C629CC + ptr->y0 + ptr->h;
    v[0].z = v[1].z = v[2].z = v[3].z = 1.0f;
    v[0].c = v[1].c = v[2].c = v[3].c =
        GU_RGBA(ptr->r0, ptr->g0, ptr->b0, 0x80);
    if (D_psp_08C62A40 == 0) {
        func_psp_0891DB9C(v, 4);
    }
    func_psp_08912008();
    func_psp_08910A80(v, 4, sizeof(Vertex), GU_TRIANGLE_STRIP,
                      GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    func_psp_0891B1F8(v[0].x, v[0].y, v[1].x, v[1].y, magenta);
    return 0;
}

s32 func_psp_089254D8(void* p) {
    Vertex v[2];
    LINE_F2* ptr;

    ptr = p;

    v[0].x = ptr->x0;
    v[0].y = ptr->y0;
    v[1].x = ptr->x1;
    v[1].y = ptr->y1;
    if (v[0].x > v[1].x) {
        v[0].x++;
    }
    v[0].z = v[1].z = 1.0f;
    v[0].c = v[1].c = GU_RGBA(ptr->r0, ptr->g0, ptr->b0, 0x80);
    if (D_psp_08C62A40 == 0) {
        func_psp_0891DC48(v, 2);
    }
    func_psp_08912008();
    func_psp_08910A80(v, 2, sizeof(Vertex), GU_LINES,
                      GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    return 0;
}

s32 func_psp_08925600(void* p) {
    Vertex v[2];
    LINE_F4* ptr;

    ptr = p;

    v[0].z = v[1].z = 1.0f;
    v[0].c = v[1].c = GU_RGBA(ptr->r0, ptr->g0, ptr->b0, 0x80);
    func_psp_08912008();
    v[0].x = ptr->x0;
    v[0].y = ptr->y0;
    v[1].x = ptr->x1;
    v[1].y = ptr->y1;
    if (v[0].x > v[1].x) {
        v[0].x++;
    }
    if (D_psp_08C62A40 == 0) {
        func_psp_0891DC48(v, 2);
    }
    func_psp_08910A80(v, 2, sizeof(Vertex), GU_LINES,
                      GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    v[0].x = v[1].x;
    v[0].y = v[1].y;
    v[1].x = ptr->x2;
    v[1].y = ptr->y2;
    if (v[0].x > v[1].x) {
        v[0].x++;
    }
    if (D_psp_08C62A40 == 0) {
        func_psp_0891DC48(v, 2);
    }
    func_psp_08910A80(v, 2, sizeof(Vertex), GU_LINES,
                      GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    v[0].x = v[1].x;
    v[0].y = v[1].y;
    v[1].x = ptr->x3;
    v[1].y = ptr->y3;
    if (v[0].x > v[1].x) {
        v[0].x++;
    }
    if (D_psp_08C62A40 == 0) {
        func_psp_0891DC48(v, 2);
    }
    func_psp_08910A80(v, 2, sizeof(Vertex), GU_LINES,
                      GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    return 0;
}

s32 func_psp_08925860(void* p) {
    Vertex v[2];
    LINE_G2* ptr;

    ptr = p;

    v[0].x = ptr->x0;
    v[0].y = ptr->y0;
    v[1].x = ptr->x1;
    v[1].y = ptr->y1;
    if (v[0].x > v[1].x) {
        v[0].x++;
    }
    v[0].z = v[1].z = 1.0f;
    v[0].c = GU_RGBA(ptr->r0, ptr->g0, ptr->b0, 0x80);
    v[1].c = GU_RGBA(ptr->r1, ptr->g1, ptr->b1, 0x80);
    if (D_psp_08C62A40 == 0) {
        func_psp_0891DC48(v, 2);
    }
    if (isSemiTrans(ptr)) {
        func_psp_089113A8((D_psp_08C629C4 >> 5) & 3, 0x80);
    } else {
        func_psp_089113A8(-1, 0x80);
    }
    func_psp_08912008();
    func_psp_08910A80(v, 2, sizeof(Vertex), GU_LINES,
                      GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    return 0;
}

s32 func_psp_08925A04(void* p) {
    Vertex v[2];
    LINE_G4* ptr;

    ptr = p;

    v[0].z = v[1].z = 1.0f;
    func_psp_08912008();
    v[0].x = ptr->x0;
    v[0].y = ptr->y0;
    v[1].x = ptr->x1;
    v[1].y = ptr->y1;
    if (v[0].x > v[1].x) {
        v[0].x++;
    }
    v[0].c = GU_RGBA(ptr->r0, ptr->g0, ptr->b0, 0x80);
    v[1].c = GU_RGBA(ptr->r1, ptr->g1, ptr->b1, 0x80);
    if (D_psp_08C62A40 == 0) {
        func_psp_0891DC48(v, 2);
    }
    func_psp_08910A80(v, 2, sizeof(Vertex), GU_LINES,
                      GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    v[0].x = v[1].x;
    v[0].y = v[1].y;
    v[1].x = ptr->x2;
    v[1].y = ptr->y2;
    if (v[0].x > v[1].x) {
        v[0].x++;
    }
    v[0].c = GU_RGBA(ptr->r1, ptr->g1, ptr->b1, 0x80);
    v[1].c = GU_RGBA(ptr->r2, ptr->g2, ptr->b2, 0x80);
    if (D_psp_08C62A40 == 0) {
        func_psp_0891DC48(v, 2);
    }
    func_psp_08910A80(v, 2, sizeof(Vertex), GU_LINES,
                      GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    v[0].x = v[1].x;
    v[0].y = v[1].y;
    v[1].x = ptr->x3;
    v[1].y = ptr->y3;
    if (v[0].x > v[1].x) {
        v[0].x++;
    }
    v[0].c = GU_RGBA(ptr->r2, ptr->g2, ptr->b2, 0x80);
    v[1].c = GU_RGBA(ptr->r3, ptr->g3, ptr->b3, 0x80);
    if (D_psp_08C62A40 == 0) {
        func_psp_0891DC48(v, 2);
    }
    func_psp_08910A80(v, 2, sizeof(Vertex), GU_LINES,
                      GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888);
    return 0;
}

void SetLineG2(LINE_G2* p) { setLineG2(p); }

void SetPolyG4(POLY_G4* p) { setPolyG4(p); }

void SetPolyGT3(POLY_GT3* p) { setPolyGT3(p); }

void SetPolyGT4(POLY_GT4* p) { setPolyGT4(p); }

void SetSprt(SPRT* p) { setSprt(p); }

void SetSprt16(SPRT_16* p) { setSprt16(p); }

void SetTile(TILE* p) { setTile(p); }
