// SPDX-License-Identifier: AGPL-3.0-or-later
//! ENCODING=utf8
#include <game_psp.h>
#include "main_psp_private.h"

// https://pspdev.github.io/pspsdk/
#define PSP_LEGACY_TYPES_DEFINED // avoid processing psptypes.h
#include <pspgu.h>
#include <pspctrl.h>
#include <pspumd.h>
#include <pspthreadman.h>
#include <psploadexec.h>
#include <psputility.h>

#define gray GU_RGBA(0x80, 0x80, 0x80, 0x80)

typedef struct Unk08919D98 Unk08919D98;

typedef struct Unk08919D98 {
    s32* unk0;
    Unk08919D98* prev;
    Unk08919D98* next;
    s32 (*unkC)(Unk08919D98*);
    s32 count;
} Unk08919D98;

// BSS
static s32 D_psp_08E2E5F4;
static s32 D_psp_08E2E5F0;
static s32 D_psp_08E2E5EC;
static s32 D_psp_08E2E5E8;
static s32 dxcSaveDataTaskResult;
static s32 dxcSaveDataTaskStep;
static DxCSaveDataTask dxcSaveDataTask;
static DxCSaveData D_psp_08E0DB0C;
DxCSaveData D_psp_08DED03C;
static bool saveDataUtilityBusy;
static PspUtilitySavedataUtilityDataSize D_psp_08DED01C; // local
static PspUtilitySavedataMsDataSize D_psp_08DECFDC;      // local
static PspUtilitySavedataMsFreeSize D_psp_08DECFC8;      // local
static PspUtilitySavedataParam savedataParam;
static bool errorDialogOpen;
static pspUtilityMsgDialogParams msgDialogParam; // local
static u8 D_psp_08DB0340[0x3C440];               // local
static u8 D_psp_08DB0318[0x14] UNUSED;
static Picture D_psp_08DB0314;
static u8 D_psp_08DB0308[0xC] UNUSED;
static char D_psp_08DAFB08[4][0x200];
static u8* D_psp_08DAFB04;
static u8* D_psp_08DAFB00;
static s32* D_psp_08DAF300[0x200];
static u8 D_psp_08DAF2D0[0x30] UNUSED;
static s32* D_psp_08DAF2CC;
static s8 D_psp_08DAF2C8;

extern s32 D_psp_08B42048;
extern s32 D_psp_08B4204C;

void func_psp_08930290(void);
s32 func_psp_08931488(void);
void FillPictureStruct(Picture* out, void* tm2Data);
u8* GetPictureClut(Picture* ptr);
u8* GetPictureTex(Picture* ptr);
u16 GetPictureWidth(Picture* ptr);

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
    s8* str;

    static char* pspDraq = "PSPDRAQ";

    str = (s8*)pspDraq;

    for (i = 0; i < 7; i++) {
        arg0[i] = str[i];
    }
    arg0[i + 0] = 0;
    arg0[i + 1] = arg1;
    arg0[i + 2] = 0;
}

void func_psp_0892FBE8(u8 arg0, u8 arg1) {
    char args[10];
    SceKernelLoadExecParam params;

    sceDisplaySetHoldMode(1);
    func_psp_08930290();
    func_psp_0892FB58(args, arg1);
    params.size = sizeof(SceKernelLoadExecParam);
    params.args = 10;
    params.argp = args;
    params.key = NULL;
    sceUmdWaitDriveStat(PSP_UMD_READY);
    sceUmdReplaceProhibit();
    sceKernelLoadExec(D_psp_08DAFB08[arg0], &params);
}

void func_psp_0892FC80(void) { func_psp_0892FBE8(0, 2); }

// These are TM2 textures https://openkh.dev/common/tm2.html

static u8 D_psp_08964120[] = {
#include "gen/D_psp_08964120.h"
};

static u8 D_psp_089649A0[] = {
#include "gen/D_psp_089649A0.h"
};

static u8 D_psp_08965220[] = {
#include "gen/D_psp_08965220.h"
};

static u8 D_psp_08965AA0[] = {
#include "gen/D_psp_08965AA0.h"
};

static u8 D_psp_08966320[] = {
#include "gen/D_psp_08966320.h"
};

static u8* D_psp_08966BA0[] = {
    D_psp_08964120, D_psp_08964120, D_psp_089649A0,
    D_psp_08965220, D_psp_08965AA0, D_psp_08966320,
};

static s32 D_psp_08966BB8 = GU_PSM_8888;

void func_psp_0892FCA8(s32 arg0) { D_psp_08966BB8 = arg0; }

void func_psp_0892FCC8(void) {
    Tm2Header* header;
    u8* ptr;
    Tm2Pict* pict;

    ptr = D_psp_08966BA0[D_psp_08DAF2C8];
    header = (Tm2Header*)ptr;
    pict = (Tm2Pict*)(ptr + sizeof(Tm2Header));
    D_psp_08DAFB04 = ptr + sizeof(Tm2Header) + pict->header_size;
    D_psp_08DAFB00 =
        ptr + sizeof(Tm2Header) + pict->header_size + pict->image_size;
}

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
    sceGuStart(GU_IMMEDIATE, D_psp_08DAF300, sizeof(D_psp_08DAF300));
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
    sceGuStart(GU_IMMEDIATE, D_psp_08DAF300, sizeof(D_psp_08DAF300));
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
    case LANG_JP:
        func_psp_0890FBEC(
            "ms/jp/save00.tm2;1", D_psp_08DB0340, 0, sizeof(D_psp_08DB0340));
        break;
    case LANG_EN:
        func_psp_0890FBEC(
            "ms/en/save00.tm2;1", D_psp_08DB0340, 0, sizeof(D_psp_08DB0340));
        break;
    case LANG_FR:
        func_psp_0890FBEC(
            "ms/fr/save00.tm2;1", D_psp_08DB0340, 0, sizeof(D_psp_08DB0340));
        break;
    case LANG_SP:
        func_psp_0890FBEC(
            "ms/sp/save00.tm2;1", D_psp_08DB0340, 0, sizeof(D_psp_08DB0340));
        break;
    case LANG_GE:
        func_psp_0890FBEC(
            "ms/ge/save00.tm2;1", D_psp_08DB0340, 0, sizeof(D_psp_08DB0340));
        break;
    case LANG_IT:
        func_psp_0890FBEC(
            "ms/it/save00.tm2;1", D_psp_08DB0340, 0, sizeof(D_psp_08DB0340));
        break;
    }
    FillPictureStruct(&D_psp_08DB0314, D_psp_08DB0340);
}

static void func_psp_08930484(s16 x, s16 y, s16 w, s16 h, u16 u, u16 v, u16 du,
                              u16 dv, s32 color, bool center, u16 z) {
    TVertex vertex[2];
    s32 vertexFormat;

    if (center) {
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
    PutTexFunc(GU_TFX_MODULATE, GU_TCC_RGBA, GU_TRUE);
    func_psp_089111C0(
        GetPictureTex(&D_psp_08DB0314), GetPictureClut(&D_psp_08DB0314), 5,
        GetPictureWidth(&D_psp_08DB0314), 9, 9);
    PutTextureMappingEnable(GU_TRUE);
    PutColorTestEnable(GU_FALSE);
    PutAlphaTestEnable(GU_TRUE);
    PutAlphaFunc(GU_GEQUAL, 1, 0xFF);
    PutAlphaBlendingEnable(GU_FALSE);
    PutBlendFunc(
        GU_ADD, GU_ONE_MINUS_DST_ALPHA, GU_DST_ALPHA, 0x00000000, 0x00000000);
    func_psp_08910A80(vertex, 2, sizeof(TVertex), GU_SPRITES, vertexFormat);
    PutTexFunc(GU_TFX_MODULATE, GU_TCC_RGBA, GU_FALSE);
}

static void func_psp_089307D4(s16 x, s16 y, s16 w, s16 h, s32 color) {
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
    PutTextureMappingEnable(GU_FALSE);
    PutColorTestEnable(GU_FALSE);
    PutAlphaTestEnable(GU_TRUE);
    PutAlphaFunc(GU_GEQUAL, 1, 0xFF);
    PutAlphaBlendingEnable(GU_TRUE);
    PutBlendFunc(GU_ADD, GU_FIX, GU_FIX, gray, gray);
    func_psp_08910A80(&v, 2, sizeof(TVertex), GU_SPRITES,
                      vertexFormat); // BUG, should be sizeof(Vertex)
    PutTextureMappingEnable(GU_TRUE);
    PutAlphaFunc(GU_GEQUAL, 1, 0xFF);
}

static void ShowErrorDialog(s32 errorVal) {
    volatile s32 ret;

    memset(&msgDialogParam, 0, sizeof(pspUtilityMsgDialogParams));
    msgDialogParam.base.size = sizeof(pspUtilityMsgDialogParams);
    msgDialogParam.base.language = D_psp_08B42048;
    msgDialogParam.base.buttonSwap = D_psp_08B4204C;
    msgDialogParam.base.graphicsThread = KERNEL_USER_HIGHEST_PRIORITY + 1;
    msgDialogParam.base.accessThread = KERNEL_USER_HIGHEST_PRIORITY + 3;
    msgDialogParam.base.fontThread = KERNEL_USER_HIGHEST_PRIORITY + 2;
    msgDialogParam.base.soundThread = KERNEL_USER_HIGHEST_PRIORITY;
    msgDialogParam.errorValue = errorVal;
    msgDialogParam.mode = PSP_UTILITY_MSGDIALOG_MODE_ERROR;
    ret = sceUtilityMsgDialogInitStart(&msgDialogParam);
    switch (ret) {
    case 0:
        errorDialogOpen = true;
        break;
    default:
        break;
    }
}

bool IsErrorDialogOpen(void) { return errorDialogOpen; }

void UpdateErrorDialog(void) {
    volatile s32 ret;
    s32 status;

    if (errorDialogOpen) {
        status = sceUtilityMsgDialogGetStatus();
        switch (status) {
        case PSP_UTILITY_COMMON_STATUS_INIT:
            break;

        case PSP_UTILITY_COMMON_STATUS_RUNNING:
            ret = sceUtilityMsgDialogUpdate(1);
            if (ret == 0) {
                return;
            }
            break;

        case PSP_UTILITY_COMMON_STATUS_FINISHED:
            ret = sceUtilityMsgDialogShutdownStart();
            if (ret == 0) {
                return;
            }
            break;

        case PSP_UTILITY_COMMON_STATUS_SHUTDOWN:
            break;

        case PSP_UTILITY_COMMON_STATUS_NONE:
            errorDialogOpen = false;
            break;
        }
    }
}

void StartDxCSaveDataTask(DxCSaveDataTask task) {
    memset(&savedataParam, 0, sizeof(PspUtilitySavedataParam));
    dxcSaveDataTask = task;
    dxcSaveDataTaskStep = 0;
    dxcSaveDataTaskResult = 0;
}

s32 UpdateDxCSaveDataTask(void) {
    enum {
        START,
        WAIT_UNTIL_DONE,
        DONE,
        SHOW_ERROR_DIALOG,
        WAIT_ERROR_DIALOG,
        RETURN
    } SaveDataTaskStep;

    switch (dxcSaveDataTaskStep) {
    case START:
        switch (dxcSaveDataTask) {
        case LOAD_DXC_SAVEDATA:
            dxcSaveDataTaskResult = LoadDxCSaveData();
            break;

        case AUTOLOAD_DXC_SAVEDATA:
            dxcSaveDataTaskResult = LoadDxCSaveData();
            break;

        case SAVE_DXC_SAVEDATA:
            dxcSaveDataTaskResult = SaveDxCSaveData();
            break;

        case AUTOSAVE_DXC_SAVEDATA:
            dxcSaveDataTaskResult = SaveDxCSaveData();
            break;

        case DELETE_ALL_DXC_SAVEDATA:
            dxcSaveDataTaskResult = DeleteAllDxCSaveData();
            break;

        case GET_SIZES_DXC_SAVEDATA:
            dxcSaveDataTaskResult = GetDxCSaveDataSizes();
            break;
        }
        if (dxcSaveDataTaskResult == 0) {
            saveDataUtilityBusy = true;
            dxcSaveDataTaskStep++;
        } else {
            dxcSaveDataTaskResult = 3;
            dxcSaveDataTaskStep = RETURN;
        }
        break;

    case WAIT_UNTIL_DONE:
        if (!saveDataUtilityBusy) {
            dxcSaveDataTaskStep = DONE;
        }
        break;

    case DONE:
        switch (dxcSaveDataTask) {
        case LOAD_DXC_SAVEDATA:
        case AUTOLOAD_DXC_SAVEDATA:
            switch (savedataParam.base.result) {
            case PSP_UTILITY_COMMON_RESULT_OK:
                dxcSaveDataTaskResult = 1;
                dxcSaveDataTaskStep = RETURN;
                break;

            case PSP_UTILITY_COMMON_RESULT_CANCELED:
                dxcSaveDataTaskResult = 2;
                dxcSaveDataTaskStep = RETURN;
                break;

            default:
                if (savedataParam.base.result ==
                    PSP_UTILITY_SAVEDATA_ERROR_LOAD_NO_MS) {
                    dxcSaveDataTaskResult = 3;
                    dxcSaveDataTaskStep = RETURN;
                } else if (savedataParam.base.result ==
                           PSP_UTILITY_SAVEDATA_ERROR_LOAD_NO_DATA) {
                    dxcSaveDataTaskResult = 3;
                    dxcSaveDataTaskStep = RETURN;
                } else {
                    dxcSaveDataTaskResult = 3;
                    dxcSaveDataTaskStep = SHOW_ERROR_DIALOG;
                }
                break;

            case PSP_UTILITY_COMMON_RESULT_ABORTED:
                if (savedataParam.abortStatus == PSP_UTILITY_COMMON_RESULT_OK) {
                    dxcSaveDataTaskResult = 1;
                    dxcSaveDataTaskStep = RETURN;
                } else {
                    dxcSaveDataTaskResult = 3;
                    dxcSaveDataTaskStep = SHOW_ERROR_DIALOG;
                }
                break;
            }
            break;

        case SAVE_DXC_SAVEDATA:
        case AUTOSAVE_DXC_SAVEDATA:
            switch (savedataParam.base.result) {
            case PSP_UTILITY_COMMON_RESULT_OK:
                dxcSaveDataTaskResult = 1;
                dxcSaveDataTaskStep = RETURN;
                break;

            case PSP_UTILITY_SAVEDATA_ERROR_SAVE_MS_NOSPACE:
                dxcSaveDataTaskResult = 4;
                dxcSaveDataTaskStep = RETURN;
                break;

            case PSP_UTILITY_COMMON_RESULT_CANCELED:
                dxcSaveDataTaskResult = 2;
                dxcSaveDataTaskStep = RETURN;
                break;

            default:
                dxcSaveDataTaskResult = 3;
                dxcSaveDataTaskStep = SHOW_ERROR_DIALOG;
                break;

            case PSP_UTILITY_COMMON_RESULT_ABORTED:
                if (savedataParam.abortStatus == PSP_UTILITY_COMMON_RESULT_OK) {
                    dxcSaveDataTaskResult = 1;
                    dxcSaveDataTaskStep = RETURN;
                } else {
                    dxcSaveDataTaskResult = 3;
                    dxcSaveDataTaskStep = SHOW_ERROR_DIALOG;
                }
                break;
            }
            break;

        case DELETE_ALL_DXC_SAVEDATA:
            switch (savedataParam.base.result) {
            case PSP_UTILITY_COMMON_RESULT_OK:
                dxcSaveDataTaskResult = 1;
                dxcSaveDataTaskStep = RETURN;
                break;

            case PSP_UTILITY_COMMON_RESULT_CANCELED:
                dxcSaveDataTaskResult = 1;
                dxcSaveDataTaskStep = RETURN;
                break;

            default:
                dxcSaveDataTaskResult = 3;
                dxcSaveDataTaskStep = RETURN;
                break;
            }
            break;

        case GET_SIZES_DXC_SAVEDATA:
            switch (savedataParam.base.result) {
            case PSP_UTILITY_COMMON_RESULT_OK:
                dxcSaveDataTaskResult = 1;
                dxcSaveDataTaskStep = RETURN;
                break;

            case PSP_UTILITY_SAVEDATA_ERROR_SIZES_NO_MS:
                dxcSaveDataTaskResult = 1;
                dxcSaveDataTaskStep = RETURN;
                break;

            default:
                if (D_psp_08DECFC8.freeSpaceKB >= 0x220) {
                    dxcSaveDataTaskResult = 1;
                    dxcSaveDataTaskStep = RETURN;
                } else {
                    dxcSaveDataTaskResult = 4;
                    dxcSaveDataTaskStep = RETURN;
                }
                break;
            }
            break;
        }
        break;

    case SHOW_ERROR_DIALOG:
        if (dxcSaveDataTask == LOAD_DXC_SAVEDATA ||
            dxcSaveDataTask == SAVE_DXC_SAVEDATA) {
            dxcSaveDataTaskStep = RETURN;
        } else {
            ShowErrorDialog(savedataParam.base.result);
            dxcSaveDataTaskStep = WAIT_ERROR_DIALOG;
        }
        break;

    case WAIT_ERROR_DIALOG:
        if (!IsErrorDialogOpen()) {
            dxcSaveDataTaskStep = RETURN;
        }
        break;

    case RETURN:
        if (dxcSaveDataTaskResult == 1 &&
            (dxcSaveDataTask == LOAD_DXC_SAVEDATA ||
             dxcSaveDataTask == AUTOLOAD_DXC_SAVEDATA)) {
            memcpy(D_psp_08DED03C, D_psp_08E0DB0C, sizeof(DxCSaveData));
        }
        return dxcSaveDataTaskResult;
    }
    return 0;
}

void UpdateSaveDataUtility(void) {
    volatile s32 ret;
    s32 status;

    ret = 0;
    status = sceUtilitySavedataGetStatus();
    switch (status) {
    case PSP_UTILITY_COMMON_STATUS_INIT:
        break;

    case PSP_UTILITY_COMMON_STATUS_RUNNING:
        ret = sceUtilitySavedataUpdate(2);
        if (ret == 0) {
            return;
        }
        break;

    case PSP_UTILITY_COMMON_STATUS_FINISHED:
        ret = sceUtilitySavedataShutdownStart();
        if (ret == 0) {
            return;
        }
        break;

    case PSP_UTILITY_COMMON_STATUS_SHUTDOWN:
        break;

    case PSP_UTILITY_COMMON_STATUS_NONE:
        saveDataUtilityBusy = false;
        break;
    }
}

static u8 D_psp_08966C34[] = {
#include "gen/D_psp_08966C34.h"
};

static u8 D_psp_08969A78[] = {
#include "gen/D_psp_08969A78.h"
};

char D_psp_089ACEC8[] = "悪魔城ドラキュラＸクロニクル";
char D_psp_089ACEF4[] = "セーブデータ";
char D_psp_089ACF08[] = "開放されているオリジナルゲーム";
char D_psp_089ACF38[] = "『悪魔城ドラキュラＸ　血の輪廻』";
char D_psp_089ACF6C[] = "『悪魔城ドラキュラＸ　月下の夜想曲』";
char D_psp_089ACFA4[] = "『あくまぢょおどらきゅらペケ』";
char D_psp_089ACFD4[] = "悪魔城ドラキュラＸクロニクルのセーブデータです。";
char D_psp_089AD020[] = "Castlevania The Dracula X Chronicles";
char D_psp_089AD048[] = "Save data";
char D_psp_089AD054[] = "Unlocked Original Game";
char D_psp_089AD06C[] = "Castlevania Rondo of Blood";
char D_psp_089AD088[] = "Castlevania Symphony of the Night";
char D_psp_089AD0AC[] = "Akumajyo Dracula Peke";
char D_psp_089AD0C4[] = "Castlevania The Dracula X Chronicles save data.";
char D_psp_089AD0F4[] = "Castlevania The Dracula X Chronicles";
char D_psp_089AD11C[] = "Sauvegarde";
char D_psp_089AD128[] = "Jeu original débloqué";
char D_psp_089AD140[] = "Castlevania Rondo of Blood";
char D_psp_089AD15C[] = "Castlevania Symphony of the Night";
char D_psp_089AD180[] = "Akumajyo Dracula Peke";
char D_psp_089AD198[] = "Sauvegarde Castlevania The Dracula X Chronicles";
char D_psp_089AD1C8[] = "Castlevania The Dracula X Chronicles";
char D_psp_089AD1F0[] = "Guardar datos";
char D_psp_089AD200[] = "Juego original desbloqueado";
char D_psp_089AD21C[] = "Castlevania Rondo of Blood";
char D_psp_089AD238[] = "Castlevania Symphony of the Night";
char D_psp_089AD25C[] = "Akumajyo Dracula Peke\t";
char D_psp_089AD274[] =
    "Datos guardados de Castlevania The Dracula X Chronicles.";
char D_psp_089AD2B0[] = "Castlevania The Dracula X Chronicles";
char D_psp_089AD2D8[] = "Daten speichern\t";
char D_psp_089AD2EC[] = "Verfügbares Originalspiel\t";
char D_psp_089AD308[] = "Castlevania Rondo of Blood";
char D_psp_089AD324[] = "Castlevania Symphony of the Night";
char D_psp_089AD348[] = "Akumajyo Dracula Peke";
char D_psp_089AD360[] = "Castlevania The Dracula X Chronicles-Speicherdaten.";
char D_psp_089AD394[] = "Castlevania The Dracula X Chronicles";
char D_psp_089AD3BC[] = "Salva dati\t";
char D_psp_089AD3C8[] = "Gioco originale sbloccato";
char D_psp_089AD3E4[] = "Castlevania Rondo of Blood";
char D_psp_089AD400[] = "Castlevania Symphony of the Night";
char D_psp_089AD424[] = "Akumajyo Dracula Peke";
char D_psp_089AD43C[] =
    "Dati di salvataggio di Castlevania The Dracula X Chronicles.";

void func_psp_08931228(void) {
    PspUtilitySavedataParam* param = &savedataParam;

    memset(param, 0, sizeof(PspUtilitySavedataParam));
    param->base.size = sizeof(PspUtilitySavedataParam);
    param->base.language = D_psp_08B42048;
    param->base.buttonSwap = D_psp_08B4204C;
    param->base.graphicsThread = KERNEL_USER_HIGHEST_PRIORITY + 1;
    param->base.accessThread = KERNEL_USER_HIGHEST_PRIORITY + 3;
    param->base.fontThread = KERNEL_USER_HIGHEST_PRIORITY + 2;
    param->base.soundThread = KERNEL_USER_HIGHEST_PRIORITY;
    param->overwrite = 0;
    memcpy(param->gameName, "ULES00841", strlen("ULES00841"));
    sprintf(param->fileName, "%s", "DRACULA.BIN");
    {
        u8 key[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6};
        memcpy(param->key, key, sizeof(key));
    }
}

s32 GetDxCSaveDataSizes(void) {
    PspUtilitySavedataParam* param = &savedataParam;

    func_psp_08931228();
    memset(&D_psp_08DECFC8, 0, sizeof(PspUtilitySavedataMsFreeSize));
    memset(&D_psp_08DECFDC, 0, sizeof(PspUtilitySavedataMsDataSize));
    memset(&D_psp_08DED01C, 0, sizeof(PspUtilitySavedataUtilityDataSize));
    memcpy(D_psp_08DECFDC.gameName, "ULES00841", strlen("ULES00841"));
    param->msFree = &D_psp_08DECFC8;
    param->msData = &D_psp_08DECFDC;
    param->utilityData = &D_psp_08DED01C;
    param->mode = PSP_UTILITY_SAVEDATA_SIZES;
    return sceUtilitySavedataInitStart(param);
}

s32 LoadDxCSaveData(void) {
    PspUtilitySavedataParam* param = &savedataParam;

    func_psp_08931228();
    if (dxcSaveDataTask == LOAD_DXC_SAVEDATA) {
        param->mode = PSP_UTILITY_SAVEDATA_LOAD;
    } else {
        param->mode = PSP_UTILITY_SAVEDATA_AUTOLOAD;
    }
    param->dataBuf = &D_psp_08E0DB0C;
    param->dataBufSize = sizeof(DxCSaveData);
    return sceUtilitySavedataInitStart(param);
}

s32 SaveDxCSaveData(void) {
    PspUtilitySavedataParam* param = &savedataParam;
    char buf[0x400];
    bool unlockedROB;
    bool unlockedSOTN;
    bool unlockedADP;

    func_psp_08931228();
    if (dxcSaveDataTask == SAVE_DXC_SAVEDATA) {
        param->mode = PSP_UTILITY_SAVEDATA_SAVE;
    } else {
        param->mode = PSP_UTILITY_SAVEDATA_AUTOSAVE;
    }
    param->dataBuf = &D_psp_08DED03C;
    param->dataBufSize = sizeof(DxCSaveData);
    param->dataSize = sizeof(DxCSaveData);
    unlockedROB = GetDxCUnlockedGame(0);
    unlockedSOTN = GetDxCUnlockedGame(1);
    unlockedADP = GetDxCUnlockedGame(2);
    buf[0] = 0;
    switch (g_UserLanguage) {
    case LANG_JP:
        if (unlockedROB + unlockedSOTN + unlockedADP) {
            sprintf(buf, "%s%s\n", buf, D_psp_089ACF08);
        } else {
            sprintf(buf, "%s%s", buf, D_psp_089ACFD4);
        }
        if (unlockedROB) {
            sprintf(buf, "%s%s\n", buf, D_psp_089ACF38);
        }
        if (unlockedSOTN) {
            sprintf(buf, "%s%s\n", buf, D_psp_089ACF6C);
        }
        if (unlockedADP) {
            sprintf(buf, "%s%s", buf, D_psp_089ACFA4);
        }
        memcpy(param->sfoParam.title, D_psp_089ACEC8, 43);
        memcpy(param->sfoParam.savedataTitle, D_psp_089ACEF4, 19);
        memcpy(param->sfoParam.detail, buf, strlen(buf));
        break;

    case LANG_EN:
        if (unlockedROB + unlockedSOTN + unlockedADP) {
            sprintf(buf, "%s%s\n", buf, D_psp_089AD054);
        } else {
            sprintf(buf, "%s%s", buf, D_psp_089AD0C4);
        }
        if (unlockedROB) {
            sprintf(buf, "%s%s\n", buf, D_psp_089AD06C);
        }
        if (unlockedSOTN) {
            sprintf(buf, "%s%s\n", buf, D_psp_089AD088);
        }
        if (unlockedADP) {
            sprintf(buf, "%s%s", buf, D_psp_089AD0AC);
        }
        memcpy(param->sfoParam.title, D_psp_089AD020, 37);
        memcpy(param->sfoParam.savedataTitle, D_psp_089AD048, 10);
        memcpy(param->sfoParam.detail, buf, strlen(buf));
        break;

    case LANG_FR:
        if (unlockedROB + unlockedSOTN + unlockedADP) {
            sprintf(buf, "%s%s\n", buf, D_psp_089AD128);
        } else {
            sprintf(buf, "%s%s", buf, D_psp_089AD198);
        }
        if (unlockedROB) {
            sprintf(buf, "%s%s\n", buf, D_psp_089AD140);
        }
        if (unlockedSOTN) {
            sprintf(buf, "%s%s\n", buf, D_psp_089AD15C);
        }
        if (unlockedADP) {
            sprintf(buf, "%s%s", buf, D_psp_089AD180);
        }
        memcpy(param->sfoParam.title, D_psp_089AD0F4, 37);
        memcpy(param->sfoParam.savedataTitle, D_psp_089AD11C, 11);
        memcpy(param->sfoParam.detail, buf, strlen(buf));
        break;

    case LANG_SP:
        if (unlockedROB + unlockedSOTN + unlockedADP) {
            sprintf(buf, "%s%s\n", buf, D_psp_089AD200);
        } else {
            sprintf(buf, "%s%s", buf, D_psp_089AD274);
        }
        if (unlockedROB) {
            sprintf(buf, "%s%s\n", buf, D_psp_089AD21C);
        }
        if (unlockedSOTN) {
            sprintf(buf, "%s%s\n", buf, D_psp_089AD238);
        }
        if (unlockedADP) {
            sprintf(buf, "%s%s", buf, D_psp_089AD25C);
        }
        memcpy(param->sfoParam.title, D_psp_089AD1C8, 37);
        memcpy(param->sfoParam.savedataTitle, D_psp_089AD1F0, 14);
        memcpy(param->sfoParam.detail, buf, strlen(buf));
        break;

    case LANG_GE:
        if (unlockedROB + unlockedSOTN + unlockedADP) {
            sprintf(buf, "%s%s\n", buf, D_psp_089AD2EC);
        } else {
            sprintf(buf, "%s%s", buf, D_psp_089AD360);
        }
        if (unlockedROB) {
            sprintf(buf, "%s%s\n", buf, D_psp_089AD308);
        }
        if (unlockedSOTN) {
            sprintf(buf, "%s%s\n", buf, D_psp_089AD324);
        }
        if (unlockedADP) {
            sprintf(buf, "%s%s", buf, D_psp_089AD348);
        }
        memcpy(param->sfoParam.title, D_psp_089AD2B0, 37);
        memcpy(param->sfoParam.savedataTitle, D_psp_089AD2D8, 17);
        memcpy(param->sfoParam.detail, buf, strlen(buf));
        break;

    case LANG_IT:
        if (unlockedROB + unlockedSOTN + unlockedADP) {
            sprintf(buf, "%s%s\n", buf, D_psp_089AD3C8);
        } else {
            sprintf(buf, "%s%s", buf, D_psp_089AD43C);
        }
        if (unlockedROB) {
            sprintf(buf, "%s%s\n", buf, D_psp_089AD3E4);
        }
        if (unlockedSOTN) {
            sprintf(buf, "%s%s\n", buf, D_psp_089AD400);
        }
        if (unlockedADP) {
            sprintf(buf, "%s%s", buf, D_psp_089AD424);
        }
        memcpy(param->sfoParam.title, D_psp_089AD394, 37);
        memcpy(param->sfoParam.savedataTitle, D_psp_089AD3BC, 12);
        memcpy(param->sfoParam.detail, buf, strlen(buf));
        break;
    }
    param->sfoParam.parentalLevel = 5;
    param->icon0FileData.buf = D_psp_08966C34;
    param->icon0FileData.bufSize = 0x2E41;
    param->icon0FileData.size = 0x2E41;
    param->pic1FileData.buf = D_psp_08969A78;
    param->pic1FileData.bufSize = 0x43450;
    param->pic1FileData.size = 0x43450;
    return sceUtilitySavedataInitStart(param);
}

s32 DeleteAllDxCSaveData(void) {
    PspUtilitySavedataParam* param = &savedataParam;

    func_psp_08931228();
    param->mode = PSP_UTILITY_SAVEDATA_LISTALLDELETE;
    return sceUtilitySavedataInitStart(param);
}

void func_psp_08931D3C(void) {
    D_psp_08E2E5E8 = 0;
    D_psp_08E2E5EC = 0;
    D_psp_08E2E5F0 = 0;
    D_psp_08E2E5F4 = 0;
}

s32 func_psp_08931D64(void) {
    s32 var_s0;

    var_s0 = 0;
    if (PadReadPSP() & PSP_CTRL_LEFT) {
        var_s0 = -1;
    }
    if (PadReadPSP() & PSP_CTRL_RIGHT) {
        var_s0 = 1;
    }
    switch (D_psp_08E2E5E8) {
    case 0:
        StartDxCSaveDataTask(AUTOSAVE_DXC_SAVEDATA);
        D_psp_08E2E5E8++;
        break;

    case 1:
        switch (UpdateDxCSaveDataTask()) {
        case 0:
            break;

        case 1:
            D_psp_08E2E5E8 = 40;
            D_psp_08E2E5F4 = 1;
            break;

        case 2:
            D_psp_08E2E5E8 = 10;
            break;

        case 3:
            D_psp_08E2E5E8 = 10;
            break;

        case 4:
            D_psp_08E2E5E8 = 20;
            break;
        }
        break;

    case 10:
        D_psp_08E2E5EC = 0;
        D_psp_08E2E5F0 = 0;
        D_psp_08E2E5E8++;
        break;

    case 11:
        if (++D_psp_08E2E5EC == 10) {
            D_psp_08E2E5E8++;
        }
        break;

    case 12:
        if (PadReadPSP() & D_psp_08B42050) {
            D_psp_08E2E5E8++;
        } else if (var_s0 != 0) {
            D_psp_08E2E5F0 = (var_s0 < 0) ? 0 : 1;
        }
        break;

    case 13:
        if (--D_psp_08E2E5EC == 0) {
            if (D_psp_08E2E5F0 == 0) {
                D_psp_08E2E5E8 = 0;
            } else {
                D_psp_08E2E5E8 = 40;
                D_psp_08E2E5F4 = 2;
            }
        }
        break;

    case 20:
        D_psp_08E2E5EC = 0;
        D_psp_08E2E5F0 = 0;
        D_psp_08E2E5E8++;
        break;

    case 21:
        if (++D_psp_08E2E5EC == 10) {
            D_psp_08E2E5E8++;
        }
        break;

    case 22:
        if (PadReadPSP() & D_psp_08B42050) {
            D_psp_08E2E5E8++;
        } else if (var_s0 != 0) {
            D_psp_08E2E5F0 = (var_s0 < 0) ? 0 : 1;
        }
        break;

    case 23:
        if (--D_psp_08E2E5EC == 0) {
            if (D_psp_08E2E5F0 == 0) {
                D_psp_08E2E5E8 = 30;
            } else {
                D_psp_08E2E5E8 = 10;
            }
        }
        break;

    case 30:
        if (++D_psp_08E2E5EC == 10) {
            StartDxCSaveDataTask(DELETE_ALL_DXC_SAVEDATA);
            D_psp_08E2E5E8++;
        }
        break;

    case 31:
        if (UpdateDxCSaveDataTask() != 0) {
            if (--D_psp_08E2E5EC == 0) {
                D_psp_08E2E5E8 = 10;
            }
        }
        break;

    case 40:
        return D_psp_08E2E5F4;
    }
    return 0;
}

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
                          0x6E, alpha << 24 | lightBlue, false, 0);
        func_psp_08930484(0x70, 0x7A, 0x100, 0x10, 0, 0x72, 0x100, 0x10,
                          alpha << 24 | white, false, 0);
        func_psp_08930484(
            0x6E, 0x94, 0x70, 0x10, 0x100, 0x72, 0x70, 0x10,
            alpha << 24 | (D_psp_08E2E5F0 == 0 ? red : white), false, 0);
        func_psp_08930484(
            0x102, 0x94, 0x70, 0x10, 0x170, 0x72, 0x70, 0x10,
            alpha << 24 | (D_psp_08E2E5F0 == 1 ? red : white), false, 0);
        break;

    case 20:
    case 21:
    case 22:
    case 23:
        alpha = D_psp_08E2E5EC * 0xFF / 10;
        func_psp_089307D4(0, 0, GU_SCR_WIDTH, GU_SCR_HEIGHT, (alpha / 2) << 24);
        func_psp_08930484(0, 0x52, GU_SCR_WIDTH, 0x6E, 0, 0x92, GU_SCR_WIDTH,
                          0x6E, alpha << 24 | lightBlue, false, 0);
        func_psp_08930484(0, 0x5E, GU_SCR_WIDTH, 0x2A, 0, 0x48, GU_SCR_WIDTH,
                          0x2A, alpha << 24 | white, false, 0);
        func_psp_08930484(0x5C, 0x8E, 0x128, 0x10, 0, 0x82, 0x128, 0x10,
                          alpha << 24 | white, false, 0);
        func_psp_08930484(
            0x6E, 0xA0, 0x70, 0x10, 0x100, 0x72, 0x70, 0x10,
            alpha << 24 | (D_psp_08E2E5F0 == 0 ? red : white), false, 0);
        func_psp_08930484(
            0x102, 0xA0, 0x70, 0x10, 0x170, 0x72, 0x70, 0x10,
            alpha << 24 | (D_psp_08E2E5F0 == 1 ? red : white), false, 0);
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

s32 GetDxCUnlockedGame(s32 game) { return D_psp_08DED03C.unlockedGames[game]; }

s32 GetDxCScreenMode(void) { return D_psp_08DED03C.screenMode; }

s32 GetDxCWallpaperIndex(void) { return D_psp_08DED03C.wallpaperIndex; }

s32 func_psp_0893277C(void) { return D_psp_08DED03C.unk5; }

s32 GetDxCUseAnalogStick(void) { return D_psp_08DED03C.useAnalogStick; }

INCLUDE_ASM("main_psp/nonmatchings/main_psp/31178", func_psp_089327A4);

Unk08919D98* func_psp_089327E4(Unk08919D98* arg0, s16 arg1) {
    if (arg0 != NULL && arg1 > 0) {
        func_psp_08934D20(arg0);
    }
    return arg0;
}

void FillPictureStruct(Picture* out, void* tm2Data) {
    s32 bitPos;
    s32 msb;
    s32 inc;

    out->data = tm2Data;
    out->headerPtr = (Tm2Header*)out->data;
    out->pictPtr = (Tm2Pict*)(out->data + sizeof(Tm2Header));
    out->imagePtr = out->data + out->pictPtr->header_size + sizeof(Tm2Header);
    out->clutPtr = out->data + out->pictPtr->header_size +
                   out->pictPtr->image_size + sizeof(Tm2Header);
    out->imageWidth = out->pictPtr->image_width;

    // grow imageWidth to next pow2
    inc = 0;
    msb = -1;
    for (bitPos = 0x1F; bitPos >= 0; bitPos--) {
        if (out->pictPtr->image_width & (1 << bitPos)) {
            if (msb < 0) {
                msb = bitPos;
            } else {
                inc = 1;
            }
        }
    }
    out->imageWidth = 1 << (msb + inc);
}

u8* GetPictureClut(Picture* ptr) { return ptr->clutPtr; }

u8* GetPictureTex(Picture* ptr) { return ptr->imagePtr; }

u16 GetPictureWidth(Picture* ptr) {
    if (ptr->pictPtr == NULL) {
        return 0;
    }
    return ptr->pictPtr->image_width;
}

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
