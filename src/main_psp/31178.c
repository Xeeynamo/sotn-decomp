// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game_psp.h>

// https://pspdev.github.io/pspsdk/
#define PSP_LEGACY_TYPES_DEFINED // avoid processing psptypes.h
#include <pspgu.h>
#include <pspumd.h>
#include <pspthreadman.h>
#include <psploadexec.h>
#include <psputility.h>

#define gray GU_RGBA(0x80, 0x80, 0x80, 0x80)

typedef struct {
    u32 c;
    float x, y, z;
} Vertex;

typedef struct {
    float u, v;
    u32 c;
    float x, y, z;
} TVertex;

extern s8* D_psp_0896411C;
extern s32 D_psp_08966BB8;
extern s32 D_psp_08966BBC;
extern s32 D_psp_08966BD0;
extern s32 D_psp_08966BE4;
extern s32 D_psp_08966BF8;
extern s32 D_psp_08966C0C;
extern s32 D_psp_08966C20;
extern s32 D_psp_08B42048;
extern s32 D_psp_08B4204C;
extern s8 D_psp_08DAF2C8;
extern s32* D_psp_08DAF2CC;
extern u8 D_psp_08DAF300[];
extern s32* D_psp_08DAFB00;
extern s32* D_psp_08DAFB04;
extern char D_psp_08DAFB08[][0x200];
extern s32 D_psp_08DB0314;
extern s32 D_psp_08DB0340;
extern pspUtilityMsgDialogParams D_psp_08DEC780;
extern s32 D_psp_08DEC9C4;
extern SceUtilitySavedataParam D_psp_08DEC9C8;
extern u32 D_psp_08DECFD0;
extern s32 D_psp_08DED038;
extern u8 D_psp_08DED03C[0x20AD0];
extern u8 D_psp_08E0DB0C[0x20AD0];
extern s32 D_psp_08E2E5DC;
extern s32 D_psp_08E2E5E0;
extern s32 D_psp_08E2E5E4;
extern s32 D_psp_08E2E5E8;
extern s32 D_psp_08E2E5EC;
extern s32 D_psp_08E2E5F0;
extern s32 g_UserLanguage;

u16 func_psp_089329B0(s32*);
void func_psp_08930290(void);

void func_psp_0892FA84(s32 arg0) { D_psp_08DAF2C8 = arg0; }

void func_psp_0892FAA8(s32 arg0, char* arg1) {
    s32 len;
    s32 i;
    s8* var_s0;
    s8* var_s1;

    if (arg1 != NULL) {
        var_s0 = (s8*)arg1;
        len = 0;
        while (*var_s0) {
            len++;
            var_s0++;
        }
        var_s0 = (s8*)arg1;
        var_s1 = (s8*)D_psp_08DAFB08[arg0];
        for (i = 0; i < len; i++) {
            *var_s1 = *var_s0;
            var_s1++;
            var_s0++;
        }
        *var_s1 = 0;
    }
}

void func_psp_0892FB58(char* arg0, u8 arg1) {
    s32 i;
    s8* c;

    c = D_psp_0896411C;

    for (i = 0; i < 7; i++) {
        arg0[i] = c[i];
    }
    arg0[i + 0] = 0;
    arg0[i + 1] = arg1;
    arg0[i + 2] = 0;
}

void func_psp_0892FBE8(u8 arg0, u8 arg1) {
    char args[10];
    struct SceKernelLoadExecParam params;

    sceDisplaySetHoldMode(1);
    func_psp_08930290();
    func_psp_0892FB58(args, arg1);
    params.size = 0x10;
    params.args = 10;
    params.argp = args;
    params.key = NULL;
    sceUmdWaitDriveStat(PSP_UMD_READY);
    sceUmdReplaceProhibit();
    sceKernelLoadExec(D_psp_08DAFB08[arg0], &params);
}

void func_psp_0892FC80(void) { func_psp_0892FBE8(0, 2); }

void func_psp_0892FCA8(s32 arg0) { D_psp_08966BB8 = arg0; }

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_0892FCC8);

void func_psp_0892FD50(void) {
    s32 i;
    s32* var_s3;
    s32* var_s2;
    s32* var_s1;

    var_s3 = (s32*)sceGeEdramGetAddr();
    sceGuInit();
    sceGuStart(GU_IMMEDIATE, D_psp_08DAF300, 0x200);
    sceGuDrawBuffer(GU_PSM_8888, GU_VRAM_BP_0, GU_VRAM_WIDTH);
    sceGuDispBuffer(GU_SCR_WIDTH, GU_SCR_HEIGHT, GU_VRAM_BP32_1, GU_VRAM_WIDTH);
    sceGuDepthBuffer(GU_VRAM_BP32_2, GU_VRAM_WIDTH);
    D_psp_08DAF2CC = (s32*)((s32)var_s3 + 0x154000);
    i = 0x22000;
    var_s2 = var_s3;
    var_s1 = D_psp_08DAF2CC;
    for (; i > 0; i--) {
        *var_s1++ = *var_s2++;
    }
    sceGuOffset(0, 0);
    sceGuScissor(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT);
    sceGuEnable(GU_SCISSOR_TEST);
    sceGuBlendFunc(
        GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0x00000000, 0x00000000);
    sceGuEnable(GU_BLEND);
    sceGuTexFunc(GU_TFX_MODULATE, GU_TCC_RGBA);
    sceGuTexFilter(GU_LINEAR_MIPMAP_LINEAR, GU_NEAREST);
    sceGuTexWrap(GU_REPEAT, GU_REPEAT);
    sceGuClearColor(0x00000000);
    sceGuClearDepth(0);
    sceGuClearStencil(0);
    sceGuTexWrap(GU_CLAMP, GU_CLAMP);
    sceGuAlphaFunc(GU_GREATER, 1, 0xFF);
    sceGuDisable(GU_FOG);
    sceGuDisable(GU_COLOR_TEST);
    sceGuDisable(GU_STENCIL_TEST);
    sceGuDisable(GU_LIGHTING);
    sceGuTexFilter(GU_LINEAR, GU_NEAREST);
    sceGuDisable(GU_SCISSOR_TEST);
    sceGuColor(0xFFFFFFFF);
    sceGuDisable(GU_DEPTH_TEST);
    sceGuDisable(GU_CULL_FACE);
    sceGuEnable(GU_BLEND);
    sceGuEnable(GU_ALPHA_TEST);
    sceGuFinish();
    sceGuSync(GU_SYNC_FINISH, GU_SYNC_WAIT);
    sceDisplayWaitVblankStart();
    sceGuDisplay(GU_DISPLAY_ON);
}

void func_psp_0892FFD0(void) {
    sceKernelDcacheWritebackAll();
    sceGuSwapBuffers();
    sceGuStart(GU_IMMEDIATE, D_psp_08DAF300, 0x800);
    sceGuClearColor(0x00000000);
    sceGuClear(GU_CLEAR_ALL);
    sceGuBlendFunc(
        GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0x00000000, 0x00000000);
    sceGuEnable(GU_TEXTURE_2D);
    sceGuTexMode(GU_PSM_T4, 0, GU_SINGLE_CLUT, GU_TEXBUF_NORMAL);
    sceGuTexFunc(GU_TFX_MODULATE, GU_TCC_RGBA);
    sceGuClutMode(GU_PSM_8888, 0, 0xFF, 0);
    sceGuClutLoad(16, D_psp_08DAFB00);
    sceGuSpriteMode(0xC0, 0x10, 0xC0, 0x10);
    sceGuTexImage(0, 0x100, 0x10, 0x100, D_psp_08DAFB04);
    sceGuDrawSprite(0xF6, 0xDF, 1, 0x35, 0, GU_NOFLIP, GU_NOROTATE);
    sceGuFinish();
    sceGuSync(GU_SYNC_FINISH, GU_SYNC_WAIT);
    sceDisplayWaitVblankStartCB();
}

void func_psp_08930120(u8 c) {
    s32 color;
    sceKernelDcacheWritebackAll();
    sceGuSwapBuffers();
    sceGuStart(GU_IMMEDIATE, D_psp_08DAF300, 0x800);
    sceGuClearColor(0x00000000);
    sceGuClear(GU_CLEAR_ALL);
    color = 0xFF000000;
    color |= c;
    color |= c << 8;
    color |= c << 16;
    sceGuDisable(GU_ALPHA_TEST);
    sceGuBlendFunc(GU_ADD, GU_FIX, GU_FIX, color, 0xFFFFFFFF);
    sceGuEnable(GU_TEXTURE_2D);
    sceGuTexMode(D_psp_08966BB8, 0, GU_SINGLE_CLUT, GU_TEXBUF_NORMAL);
    sceGuTexFunc(GU_TFX_MODULATE, GU_TCC_RGBA);
    sceGuSpriteMode(GU_SCR_WIDTH, GU_SCR_HEIGHT, GU_SCR_WIDTH, GU_SCR_HEIGHT);
    sceGuTexImage(0, 0x200, 0x200, 0x200, D_psp_08DAF2CC);
    sceGuDrawSprite(0, 0, 1, 0, 0, GU_NOFLIP, GU_NOROTATE);
    sceGuFinish();
    sceGuSync(GU_SYNC_FINISH, GU_SYNC_WAIT);
    sceDisplayWaitVblankStartCB();
}

void func_psp_08930290(void) {
    s32 i;
    u8 c;

    c = 0xFF;
    func_psp_0892FD50();
    func_psp_0892FCC8();
    for (i = 0; i < 16; i++) {
        func_psp_08930120(c);
        c -= 0x10;
    }
    for (i = 0; i < 2; i++) {
        func_psp_0892FFD0();
    }
}

void func_psp_08930324(void) {
    switch (g_UserLanguage) {
    case 0:
        func_psp_0890FBEC(&D_psp_08966BBC, &D_psp_08DB0340, 0, 0x3C440);
        break;
    case 1:
        func_psp_0890FBEC(&D_psp_08966BD0, &D_psp_08DB0340, 0, 0x3C440);
        break;
    case 2:
        func_psp_0890FBEC(&D_psp_08966BE4, &D_psp_08DB0340, 0, 0x3C440);
        break;
    case 3:
        func_psp_0890FBEC(&D_psp_08966BF8, &D_psp_08DB0340, 0, 0x3C440);
        break;
    case 4:
        func_psp_0890FBEC(&D_psp_08966C0C, &D_psp_08DB0340, 0, 0x3C440);
        break;
    case 5:
        func_psp_0890FBEC(&D_psp_08966C20, &D_psp_08DB0340, 0, 0x3C440);
        break;
    }
    func_psp_08932830(&D_psp_08DB0314, &D_psp_08DB0340);
}

void func_psp_08930484(s16 x, s16 y, s16 w, s16 h, u16 u, u16 v, u16 du, u16 dv,
                       s32 color, s32 arg9, u16 z) {
    TVertex vertex[2];
    s32 vertexFormat;

    if (arg9) {
        x -= w / 2;
        y -= h / 2;
    }
    vertexFormat =
        GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888 | GU_TEXTURE_32BITF;
    vertex[0].u = u;
    vertex[0].v = v;
    vertex[0].c = color;
    vertex[0].x = x;
    vertex[0].y = y;
    vertex[0].z = z;
    vertex[1].u = u + du;
    vertex[1].v = v + dv;
    vertex[1].c = color;
    vertex[1].x = x + w;
    vertex[1].y = y + h;
    vertex[1].z = z;
    func_psp_089109E4(GU_TFX_MODULATE, GU_TCC_RGBA, 1);
    func_psp_089111C0(
        func_psp_08932994(&D_psp_08DB0314), func_psp_08932978(&D_psp_08DB0314),
        5, func_psp_089329B0(&D_psp_08DB0314), 9, 9);
    func_psp_089105DC(1);
    func_psp_08910778(0);
    func_psp_0891068C(1);
    func_psp_089106B8(GU_GEQUAL, 1, 0xFF);
    func_psp_08910660(0);
    func_psp_08910810(
        GU_ADD, GU_ONE_MINUS_DST_ALPHA, GU_DST_ALPHA, 0x00000000, 0x00000000);
    func_psp_08910A80(vertex, 2, sizeof(TVertex), GU_SPRITES, vertexFormat);
    func_psp_089109E4(GU_TFX_MODULATE, GU_TCC_RGBA, 0);
}

void func_psp_089307D4(s16 x, s16 y, s16 w, s16 h, s32 color) {
    Vertex v[2];
    s32 vertexFormat;

    vertexFormat = GU_TRANSFORM_2D | GU_VERTEX_32BITF | GU_COLOR_8888;
    v[0].c = color;
    v[0].x = x;
    v[0].y = y;
    v[0].z = 0.0f;
    v[1].c = color;
    v[1].x = x + w;
    v[1].y = y + h;
    v[1].z = 0.0f;
    func_psp_089105DC(0);
    func_psp_08910778(0);
    func_psp_0891068C(1);
    func_psp_089106B8(GU_GEQUAL, 1, 0xFF);
    func_psp_08910660(1);
    func_psp_08910810(GU_ADD, GU_FIX, GU_FIX, gray, gray);
    func_psp_08910A80(&v, 2, sizeof(TVertex), GU_SPRITES,
                      vertexFormat); // BUG, should be sizeof(Vertex)
    func_psp_089105DC(1);
    func_psp_089106B8(GU_GEQUAL, 1, 0xFF);
}

void func_psp_08930934(s32 errorVal) {
    s32 ret[1];

    memset(&D_psp_08DEC780, 0, sizeof(pspUtilityMsgDialogParams));
    D_psp_08DEC780.base.size = sizeof(pspUtilityMsgDialogParams);
    D_psp_08DEC780.base.language = D_psp_08B42048;
    D_psp_08DEC780.base.buttonSwap = D_psp_08B4204C;
    D_psp_08DEC780.base.graphicsThread = KERNEL_USER_HIGHEST_PRIORITY + 1;
    D_psp_08DEC780.base.accessThread = KERNEL_USER_HIGHEST_PRIORITY + 3;
    D_psp_08DEC780.base.fontThread = KERNEL_USER_HIGHEST_PRIORITY + 2;
    D_psp_08DEC780.base.soundThread = KERNEL_USER_HIGHEST_PRIORITY;
    D_psp_08DEC780.errorValue = errorVal;
    D_psp_08DEC780.mode = PSP_UTILITY_MSGDIALOG_MODE_ERROR;
    ret[0] = sceUtilityMsgDialogInitStart(&D_psp_08DEC780);
    switch (ret[0]) {
    case 0:
        D_psp_08DEC9C4 = 1;
        break;
    default:
        break;
    }
}

s32 func_psp_08930A0C(void) { return D_psp_08DEC9C4; }

void func_psp_08930A1C(void) {
    s32 ret[1];
    s32 status;

    if (D_psp_08DEC9C4 != 0) {
        status = sceUtilityMsgDialogGetStatus();
        switch (status) {
        case PSP_UTILITY_COMMON_STATUS_INIT:
            break;

        case PSP_UTILITY_COMMON_STATUS_RUNNING:
            ret[0] = sceUtilityMsgDialogUpdate(1);
            if (ret[0] == 0) {
                return;
            }
            break;

        case PSP_UTILITY_COMMON_STATUS_FINISHED:
            ret[0] = sceUtilityMsgDialogShutdownStart();
            if (ret[0] == 0) {
                return;
            }
            break;

        case PSP_UTILITY_COMMON_STATUS_SHUTDOWN:
            break;

        case PSP_UTILITY_COMMON_STATUS_NONE:
            D_psp_08DEC9C4 = 0;
            break;
        }
    }
}

void func_psp_08930AE4(s32 arg0) {
    memset(&D_psp_08DEC9C8, 0, sizeof(SceUtilitySavedataParam));
    D_psp_08E2E5DC = arg0;
    D_psp_08E2E5E0 = 0;
    D_psp_08E2E5E4 = 0;
}

s32 func_psp_08930B34(void) {
    switch (D_psp_08E2E5E0) {
    case 0:
        switch (D_psp_08E2E5DC) {
        case 0:
            D_psp_08E2E5E4 = func_psp_08931410();
            break;

        case 1:
            D_psp_08E2E5E4 = func_psp_08931410();
            break;

        case 2:
            D_psp_08E2E5E4 = func_psp_08931488();
            break;

        case 3:
            D_psp_08E2E5E4 = func_psp_08931488();
            break;

        case 4:
            D_psp_08E2E5E4 = func_psp_08931CF8();
            break;

        case 5:
            D_psp_08E2E5E4 = func_psp_08931334();
            break;
        }
        if (D_psp_08E2E5E4 == 0) {
            D_psp_08DED038 = 1;
            D_psp_08E2E5E0++;
        } else {
            D_psp_08E2E5E4 = 3;
            D_psp_08E2E5E0 = 5;
        }
        break;

    case 1:
        if (D_psp_08DED038 == 0) {
            D_psp_08E2E5E0 = 2;
        }
        break;

    case 2:
        switch (D_psp_08E2E5DC) {
        case 0:
        case 1:
            switch (D_psp_08DEC9C8.base.result) {
            case PSP_UTILITY_COMMON_RESULT_OK:
                D_psp_08E2E5E4 = 1;
                D_psp_08E2E5E0 = 5;
                break;

            case PSP_UTILITY_COMMON_RESULT_CANCELED:
                D_psp_08E2E5E4 = 2;
                D_psp_08E2E5E0 = 5;
                break;

            default:
                if (D_psp_08DEC9C8.base.result ==
                    PSP_UTILITY_SAVEDATA_ERROR_LOAD_NO_MS) {
                    D_psp_08E2E5E4 = 3;
                    D_psp_08E2E5E0 = 5;
                } else if (D_psp_08DEC9C8.base.result ==
                           PSP_UTILITY_SAVEDATA_ERROR_LOAD_NO_DATA) {
                    D_psp_08E2E5E4 = 3;
                    D_psp_08E2E5E0 = 5;
                } else {
                    D_psp_08E2E5E4 = 3;
                    D_psp_08E2E5E0 = 3;
                }
                break;

            case PSP_UTILITY_COMMON_RESULT_ABORTED:
                if (D_psp_08DEC9C8.abortStatus ==
                    PSP_UTILITY_COMMON_RESULT_OK) {
                    D_psp_08E2E5E4 = 1;
                    D_psp_08E2E5E0 = 5;
                } else {
                    D_psp_08E2E5E4 = 3;
                    D_psp_08E2E5E0 = 3;
                }
                break;
            }
            break;

        case 2:
        case 3:
            switch (D_psp_08DEC9C8.base.result) {
            case PSP_UTILITY_COMMON_RESULT_OK:
                D_psp_08E2E5E4 = 1;
                D_psp_08E2E5E0 = 5;
                break;

            case PSP_UTILITY_SAVEDATA_ERROR_SAVE_MS_NOSPACE:
                D_psp_08E2E5E4 = 4;
                D_psp_08E2E5E0 = 5;
                break;

            case PSP_UTILITY_COMMON_RESULT_CANCELED:
                D_psp_08E2E5E4 = 2;
                D_psp_08E2E5E0 = 5;
                break;

            default:
                D_psp_08E2E5E4 = 3;
                D_psp_08E2E5E0 = 3;
                break;

            case PSP_UTILITY_COMMON_RESULT_ABORTED:
                if (D_psp_08DEC9C8.abortStatus ==
                    PSP_UTILITY_COMMON_RESULT_OK) {
                    D_psp_08E2E5E4 = 1;
                    D_psp_08E2E5E0 = 5;
                } else {
                    D_psp_08E2E5E4 = 3;
                    D_psp_08E2E5E0 = 3;
                }
                break;
            }
            break;

        case 4:
            switch (D_psp_08DEC9C8.base.result) {
            case PSP_UTILITY_COMMON_RESULT_OK:
                D_psp_08E2E5E4 = 1;
                D_psp_08E2E5E0 = 5;
                break;

            case PSP_UTILITY_COMMON_RESULT_CANCELED:
                D_psp_08E2E5E4 = 1;
                D_psp_08E2E5E0 = 5;
                break;

            default:
                D_psp_08E2E5E4 = 3;
                D_psp_08E2E5E0 = 5;
                break;
            }
            break;

        case 5:
            switch (D_psp_08DEC9C8.base.result) {
            case PSP_UTILITY_COMMON_RESULT_OK:
                D_psp_08E2E5E4 = 1;
                D_psp_08E2E5E0 = 5;
                break;

            case PSP_UTILITY_SAVEDATA_ERROR_SIZES_NO_MS:
                D_psp_08E2E5E4 = 1;
                D_psp_08E2E5E0 = 5;
                break;

            default:
                if (D_psp_08DECFD0 >= 0x220) {
                    D_psp_08E2E5E4 = 1;
                    D_psp_08E2E5E0 = 5;
                } else {
                    D_psp_08E2E5E4 = 4;
                    D_psp_08E2E5E0 = 5;
                }
                break;
            }
            break;
        }
        break;

    case 3:
        if ((D_psp_08E2E5DC == 0) || (D_psp_08E2E5DC == 2)) {
            D_psp_08E2E5E0 = 5;
        } else {
            func_psp_08930934(D_psp_08DEC9C8.base.result);
            D_psp_08E2E5E0 = 4;
        }
        break;

    case 4:
        if (func_psp_08930A0C() == 0) {
            D_psp_08E2E5E0 = 5;
        }
        break;

    case 5:
        if ((D_psp_08E2E5E4 == 1) &&
            ((D_psp_08E2E5DC == 0) || (D_psp_08E2E5DC == 1))) {
            memcpy(D_psp_08DED03C, D_psp_08E0DB0C, sizeof(D_psp_08E0DB0C));
        }
        return D_psp_08E2E5E4;
    }
    return 0;
}

void func_psp_0893116C(void) {
    s32 ret[1];
    s32 status;

    ret[0] = 0;
    status = sceUtilitySavedataGetStatus();
    switch (status) {
    case PSP_UTILITY_COMMON_STATUS_INIT:
        break;

    case PSP_UTILITY_COMMON_STATUS_RUNNING:
        ret[0] = sceUtilitySavedataUpdate(2);
        if (ret[0] == 0) {
            return;
        }
        break;

    case PSP_UTILITY_COMMON_STATUS_FINISHED:
        ret[0] = sceUtilitySavedataShutdownStart();
        if (ret[0] == 0) {
            return;
        }
        break;

    case PSP_UTILITY_COMMON_STATUS_SHUTDOWN:
        break;

    case PSP_UTILITY_COMMON_STATUS_NONE:
        D_psp_08DED038 = 0;
        break;
    }
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08931228);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08931334);

s32 func_psp_08931410(void) {
    SceUtilitySavedataParam* param = &D_psp_08DEC9C8;

    func_psp_08931228();
    if (D_psp_08E2E5DC == 0) {
        param->mode = PSP_UTILITY_SAVEDATA_LOAD;
    } else {
        param->mode = PSP_UTILITY_SAVEDATA_AUTOLOAD;
    }
    param->dataBuf = D_psp_08E0DB0C;
    param->dataBufSize = sizeof(D_psp_08E0DB0C);
    return sceUtilitySavedataInitStart(param);
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08931488);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08931CF8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08931D3C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08931D64);

void func_psp_08932228(void) {
    s32 alpha;

    const s32 white = GU_RGBA(0xFF, 0xFF, 0xFF, 0);
    const s32 red = GU_RGBA(0xFF, 0, 0, 0);
    const s32 lightBlue = GU_RGBA(0x64, 0xA0, 0xFF, 0);

    switch (D_psp_08E2E5E8) {
    case 0:
    case 1:
        break;

    case 10:
    case 11:
    case 12:
    case 13:
        alpha = D_psp_08E2E5EC * 0xFF / 10;
        func_psp_089307D4(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT, (alpha / 2) << 24);
        func_psp_08930484(0, 0x52, GU_SCR_WIDTH, 0x6E, 0, 0x92, GU_SCR_WIDTH,
                          0x6E, alpha << 24 | lightBlue, 0, 0);
        func_psp_08930484(0x70, 0x7A, 0x100, 0x10, 0, 0x72, 0x100, 0x10,
                          alpha << 24 | white, 0, 0);
        func_psp_08930484(
            0x6E, 0x94, 0x70, 0x10, 0x100, 0x72, 0x70, 0x10,
            alpha << 24 | (D_psp_08E2E5F0 == 0 ? red : white), 0, 0);
        func_psp_08930484(
            0x102, 0x94, 0x70, 0x10, 0x170, 0x72, 0x70, 0x10,
            alpha << 24 | (D_psp_08E2E5F0 == 1 ? red : white), 0, 0);
        break;

    case 20:
    case 21:
    case 22:
    case 23:
        alpha = D_psp_08E2E5EC * 0xFF / 10;
        func_psp_089307D4(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT, (alpha / 2) << 24);
        func_psp_08930484(0, 0x52, GU_SCR_WIDTH, 0x6E, 0, 0x92, GU_SCR_WIDTH,
                          0x6E, alpha << 24 | lightBlue, 0, 0);
        func_psp_08930484(0, 0x5E, GU_SCR_WIDTH, 0x2A, 0, 0x48, GU_SCR_WIDTH,
                          0x2A, alpha << 24 | white, 0, 0);
        func_psp_08930484(0x5C, 0x8E, 0x128, 0x10, 0, 0x82, 0x128, 0x10,
                          alpha << 24 | white, 0, 0);
        func_psp_08930484(
            0x6E, 0xA0, 0x70, 0x10, 0x100, 0x72, 0x70, 0x10,
            alpha << 24 | (D_psp_08E2E5F0 == 0 ? red : white), 0, 0);
        func_psp_08930484(
            0x102, 0xA0, 0x70, 0x10, 0x170, 0x72, 0x70, 0x10,
            alpha << 24 | (D_psp_08E2E5F0 == 1 ? red : white), 0, 0);
        break;

    case 30:
    case 31:
        alpha = D_psp_08E2E5EC * 0xFF / 10;
        func_psp_089307D4(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT, (alpha / 2) << 24);
        break;

    case 40:
        break;
    }
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932728);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932754);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932768);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_0893277C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932790);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_089327A4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_089327E4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932830);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932978);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932994);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_089329B0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_089329EC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932A7C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932AD4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932B50);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932B74);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932B98);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932BC4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932BF0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932C14);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932C38);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932C5C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932C80);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932CA4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932CC8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932CEC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932D34);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932D60);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932D94);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932DC8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932DF4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932E20);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932E4C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932E78);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932EA4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932EC8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932EF4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932F20);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932F44);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932F68);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932F8C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932FB0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08932FD4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08933000);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08933024);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08933050);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_0893307C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_089330A0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_089330C4);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_089330E8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_0893310C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08933130);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_0893315C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08933180);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_089331AC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_089331D0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_0893325C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08933304);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08933760);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_089337A8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_089337EC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08933830);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08933870);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_089338BC);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08933954);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08933A10);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08933BA0);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08933C30);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08933E38);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08933ED8);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08933F5C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08933F6C);

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_08933F7C);
