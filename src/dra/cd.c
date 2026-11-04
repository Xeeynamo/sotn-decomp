// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"
#include "dra_bss.h"
#include "lba.h"
#include "sfx.h"

#if USE_CD_SPEED_DOUBLE == 0
#define CDL_MODE_SPEED CdlModeSpeedNormal
#else
#define CDL_MODE_SPEED CdlModeSpeedDouble
#endif

#define _CD_BLOCK 11 // 2048 (0x800) bytes per sector
#define CD_BLOCK_LEN (1 << (_CD_BLOCK))
#define TO_CD_BLOCK(x) ((x) << (_CD_BLOCK))

s16 D_800AC958[] = {
    0x200, 0x220, 0x200, 0x220, 0x240, 0x260, 0x240, 0x260, 0x280, 0x2A0, 0x280,
    0x2A0, 0x2C0, 0x2E0, 0x2C0, 0x2E0, 0x300, 0x320, 0x300, 0x320, 0x340, 0x360,
    0x340, 0x360, 0x380, 0x3A0, 0x380, 0x3A0, 0x3C0, 0x3E0, 0x3C0, 0x3E0,
};
s16 D_800AC998[] = {
    0x200, 0x220, 0x200, 0x220, 0x240, 0x260, 0x240, 0x260, 0x280, 0x2A0, 0x280,
    0x2A0, 0x2C0, 0x2E0, 0x2C0, 0x2E0, 0x300, 0x320, 0x300, 0x320, 0x340, 0x360,
    0x340, 0x360, 0x380, 0x3A0, 0x380, 0x3A0, 0x3C0, 0x3E0, 0x3C0, 0x3E0,
};

CdFile g_LbaBinTitle = {OFF_BIN_FTITLE, 0, 0x80000, 0, 0, 0xFF, 0};
CdFile g_LbaBinProlo = {OFF_BIN_FPROLO, 6, 0x80000, 0, 0, 0xFF, 0};
CdFile g_LbaBinGame = {0x0000, 1, 0x42000, 0, 0, 0x13, 0};
CdFile g_LbaStageChr = {ST_NO0_F_BIN_OFF, 2, 0x40000, 0, 0, 0xFF, 0};
CdFile g_LbaSdAlkVh = {OFF_SD_ALK_VH, 19, SD_ALK_VH_LEN, 1, 1, 0xFF, 7};
CdFile g_LbaSdAlkVb = {OFF_SD_ALK_VB, 17, SD_ALK_VB_LEN, 1, 1, 0xFF, 0};
CdFile g_LbaSdRihVh = {OFF_SD_RIH_VH, 19, SD_RIH_VH_LEN, 1, 1, 0x16, 21};
CdFile g_LbaSdRihVb = {OFF_SD_RIH_VB, 17, SD_RIH_VB_LEN, 1, 1, 0xFF, 0};
CdFile g_LbaSdMarVh = {OFF_SD_MAR_VH, 19, SD_MAR_VH_LEN, 2, 2, 0xFF, 23};
CdFile g_LbaSdMarVb = {OFF_SD_MAR_VB, 17, SD_MAR_VB_LEN, 2, 2, 0xFF, 0};
CdFile g_LbaSdJ010_1_Vh = {OFF_SD_J010_VH, 19, 0x02A20, 0, 0, 0x0A, 9};
CdFile g_LbaSdJ010_1_Vb = {OFF_SD_J010_VB, 17, vab0Len, 0, 0, 0xFF, 0};
CdFile g_LbaSdJ010_2_Vh = {OFF_SD_J010_VH, 19, vab0Len, 4, 4, 0x0C, 11};
CdFile g_LbaSdJ010_2_Vb = {OFF_SD_J010_VB, 17, ST_NO0_VB_LEN, 4, 4, 0x0C, 0};
CdFile g_LbaStageSeq = {0x0000, 18, 0x00000, 0, 6, 0xFF, 0};
CdFile g_LbaStageVh = {0x0000, 19, 0x00000, 3, 3, 0xFF, 14};
CdFile g_LbaStageVb = {0x0000, 17, 0x00000, 3, 3, 0xFF, 0};
CdFile g_LbaSdJ010_3_Vh = {OFF_SD_J010_VH, 19, 0x02A20, 3, 3, 0xFF, 16};
CdFile g_LbaSdJ010_3_Vb = {OFF_SD_J010_VB, 17, vab0Len, 3, 3, 0xFF, 0};
CdFile g_LbaBinWeapon0 = {OFF_BIN_WEAPON0, 12, 0x04000, 0, 0, 0xFF, 0};
CdFile g_LbaBinWeapon1 = {OFF_BIN_WEAPON1, 13, 0x04000, 0, 0, 0xFF, 1};
CdFile g_LbaBinMonster = {OFF_BIN_MONSTER, 14, 0x05800, 0, 0, 0xFF, 0};
CdFile g_LbaBinDemokey = {OFF_BIN_DEMOKEY, 4, 0x02000, 0, 0, 0xFF, 0};

// SERVANT/FT_xxx.BIN off
s32 g_LbaServantChrOff[] = {
    OFF_FT_000_BIN, OFF_FT_001_BIN, OFF_FT_002_BIN, OFF_FT_003_BIN,
    OFF_FT_004_BIN, OFF_FT_005_BIN, OFF_FT_006_BIN,
};

// SERVANT/SD_xxx.VH off
s32 g_LbaServantVhOff[] = {
    OFF_SD_BAT_VH,   OFF_SD_GHOST_VH, OFF_SD_FAIRY_VH, OFF_SD_DEVIL_VH,
    OFF_SD_SWORD_VH, OFF_SD_FAIR2_VH, OFF_SD_DEVI2_VH,
};

// SERVANT/SD_xxx.VH len
s32 g_LbaServantVhLen[] = {
    SD_TUKA2_VH_LEN, SD_MAR2_VH_LEN, SD_TUKA1_VH_LEN, SD_KOA1_VH_LEN,
    SD_MAK_VH_LEN,   SD_FAIR2_VH_LEN, SD_KOA2_VH_LEN,
};

// SERVANT/SD_xxx.VB off
s32 g_LbaServantVbOff[] = {
    OFF_SD_BAT_VB,   OFF_SD_GHOST_VB, OFF_SD_FAIRY_VB, OFF_SD_DEVIL_VB,
    OFF_SD_SWORD_VB, OFF_SD_FAIR2_VB, OFF_SD_DEVI2_VB,
};

// SERVANT/SD_xxx.VB len
s32 g_LbaServantVbLen[] = {
    SD_TUKA2_VB_LEN, SD_GHOST_VB_LEN, SD_TUKA1_VB_LEN, SD_KOA1_VB_LEN,
    SD_MAK_VB_LEN,   SD_FAIR2_VB_LEN, SD_KOA2_VB_LEN,
};

CdFile g_LbaServantChr = {0x0000, 15, 0x06000, 0, 0, 0x1D, 0};
CdFile g_LbaServantVh = {0x0000, 19, 0x00000, 2, 2, 0xFF, 30};
CdFile g_LbaServantVb = {0x0000, 17, 0x00000, 2, 2, 0xFF, 0};
CdFile g_LbaBinRichter = {OFF_BIN_RIC, 10, LEN_BIN_RIC, 0, 0, 0x14, 0};
CdFile g_LbaBinAlucard = {OFF_BIN_ARC_F, 10, 0x31BEC, 0, 0, 0x04, 0};
CdFile g_LbaOpnWsStr = {OFF_OPN_WS_STR, 0, 0x00000, 0, 0, 0xFF, 0};
CdFile g_LbaStagePrg = {0x0000, 8, 0x00000, 0, 0, 0xFF, 0};
CdFile g_LbaBinGo = {OFF_BIN_FGO, 9, 0x1C000, 0, 0, 0xFF, 0};
CdFile g_LbaBinEnd = {OFF_BIN_FEND, 9, 0x16000, 0, 0, 0xFF, 0};
CdFile D_800ACC64 = {0x0000, 3, 0x00000, 0, 0, 0xFF, 0};

CdFile* D_800ACC74[] = {
    &g_LbaBinTitle,    &g_LbaBinTitle,    &g_LbaBinGame,     &g_LbaStageChr,
    &g_LbaSdAlkVh,     &g_LbaBinRichter,  &g_LbaBinProlo,    &g_LbaSdAlkVb,
    &g_LbaSdJ010_1_Vh, &g_LbaSdJ010_1_Vb, &g_LbaSdJ010_2_Vh, &g_LbaSdJ010_2_Vb,
    &g_LbaStageSeq,    &g_LbaStageVh,     &g_LbaStageVb,     &g_LbaSdJ010_3_Vh,
    &g_LbaSdJ010_3_Vb, &g_LbaBinWeapon0,  &g_LbaBinWeapon1,  &g_LbaBinAlucard,
    &g_LbaSdRihVh,     &g_LbaSdRihVb,     &g_LbaSdMarVh,     &g_LbaSdMarVb,
    &g_LbaOpnWsStr,    &D_800ACC64,       &g_LbaBinGo,       &g_LbaServantChr,
    &g_LbaBinMonster,  &g_LbaServantVh,   &g_LbaServantVb,   &g_LbaBinEnd,
    &g_LbaBinDemokey,
};

CdFileSeq D_800ACCF8[] = {
    {OFF_SEQ_LIB_SEQ, SEQ_LIB_SEQ_LEN, MU_SEQ_LIBRARIAN},
    {OFF_SEQ_DAI_SEQ, SEQ_DAI_SEQ_LEN, MU_SEQ_CONFESSIONAL_BELLS},
};

const char* D_800ACD10[] = {
    aPbav, aPbav_0, aPbav_1, aPbav_2, aPbav, NULL, aPqes_1,
};

void func_801080DC(void);
void CopyStageOvlCallback(void);
void CopyRicOvlCallback(void);
void func_801078C4(void);
void CopyMonsterPreviewCallback(void);
void func_80107DB4(void);
void func_80107C6C(void);
void func_80107EF0(void);
void (*g_CdCallbacks[])(void) = {
    func_801080DC,        func_801080DC,        func_801080DC,
    func_801080DC,        CopyStageOvlCallback, func_801080DC,
    func_801080DC,        func_801080DC,        CopyStageOvlCallback,
    CopyStageOvlCallback, CopyRicOvlCallback,   func_801080DC,
    func_801078C4,        func_801078C4,        CopyMonsterPreviewCallback,
    func_801078C4,        func_80107DB4,        func_80107C6C,
    func_80107DB4,        func_80107EF0,
};
s32 D_800ACD7C = 0;

extern u16 D_800A04CC[]; // palette?
extern u32* D_801EE000;
extern s32 g_VabAddrs[];

// BSS
static CdCallbacks g_CdCallback;
static CdlLOC g_CdLoc;
static CdThing g_Cd;
static s16 g_VabId;
static u8 D_80137F96;
STATIC_PAD_BSS(5);
static s32 D_80137F9C;
static s32 D_80137FA0;
STATIC_PAD_BSS(4);
static s16 D_80137FA8;
STATIC_PAD_BSS(2);
static s32 D_80137FAC;
static s32 D_80137FB0;

void func_801073C0(void) {
    CdReadyCallback(NULL);
    CdDataCallback(NULL);
}

s32 func_801073E8(void) {
    u8 res;
    s32 ret;

    if (CdSync(CdlNop, &res) == CdlNoIntr) {
        return D_80137F9C = 0;
    }

    ret = CdLastCom();
    if (ret >= CdlGetlocL && ret <= CdlGetlocP || !(res & CdlStatShellOpen)) {
        CdControlF(CdlNop, NULL);
        return D_80137F9C = 0;
    }
    return D_80137F9C = 1;
}

void func_80107460(void) {
    g_Cd.D_80137F7C = &D_801EC000[TO_CD_BLOCK(g_Cd.D_80137F6C)];
    CdGetSector(g_Cd.D_80137F7C, 0x200);
    g_Cd.D_80137F6C = (g_Cd.D_80137F6C + 1) & 7;
}

void CopyStageOvlCallback(void) {
    s32 i;
    s32 len;

    if (g_Cd.overlayBlockCount != 0) {
        len = CD_BLOCK_LEN;
    } else {
        len = g_Cd.overlayLastBlockSize;
    }
    if (g_CdCallback == CdCallback_4) {
        g_Cd.overlayCopyDst = TO_CD_BLOCK(g_Cd.D_80137F74) + DEMO_KEY_PTR;
    } else {
        g_Cd.overlayCopyDst = TO_CD_BLOCK(g_Cd.D_80137F74) + STAGE_PRG_PTR;
    }
    g_Cd.overlayCopySrc = TO_CD_BLOCK(g_Cd.D_80137F70) + D_801EC000;
#if USE_MICRO_OPTIMIZATIONS == 1
    MEMCPY(g_Cd.overlayCopyDst, g_Cd.overlayCopySrc, len);
#else
    for (i = 0; i < len; i++) {
        *g_Cd.overlayCopyDst = *g_Cd.overlayCopySrc;
        g_Cd.overlayCopySrc++;
        g_Cd.overlayCopyDst++;
    }
#endif
    g_Cd.D_80137F70 = (g_Cd.D_80137F70 + 1) & 7;
    g_Cd.D_80137F74++;
    g_Cd.overlayBlockCount--;
    if (g_Cd.overlayBlockCount < 0 ||
        (g_Cd.overlayBlockCount == 0 && g_Cd.overlayLastBlockSize == 0)) {
        g_Cd.D_80137F78 = 1;
        CdDataCallback(NULL);
    }
}

void CopyRicOvlCallback(void) {
    s32 i;
    s32 len;

    if (g_Cd.overlayBlockCount != 0) {
        len = CD_BLOCK_LEN;
    } else {
        len = g_Cd.overlayLastBlockSize;
    }
    g_Cd.overlayCopyDst = TO_CD_BLOCK(g_Cd.D_80137F74) + RIC_PRG_PTR;
    g_Cd.overlayCopySrc = TO_CD_BLOCK(g_Cd.D_80137F70) + D_801EC000;
#if USE_MICRO_OPTIMIZATIONS == 1
    MEMCPY(g_Cd.overlayCopyDst, g_Cd.overlayCopySrc, len);
#else
    for (i = 0; i < len; i++) {
        *g_Cd.overlayCopyDst = *g_Cd.overlayCopySrc;
        g_Cd.overlayCopySrc++;
        g_Cd.overlayCopyDst++;
    }
#endif
    g_Cd.D_80137F70 = (g_Cd.D_80137F70 + 1) & 7;
    g_Cd.D_80137F74++;
    g_Cd.overlayBlockCount--;
    if (g_Cd.overlayBlockCount < 0 ||
        g_Cd.overlayBlockCount == 0 && g_Cd.overlayLastBlockSize == 0) {
        g_Cd.D_80137F78 = 1;
        CdDataCallback(NULL);
    }
}

void CopySupportOvlCallback(void) {
    s32 i;
    s32 len;

    if (g_Cd.overlayBlockCount != 0) {
        len = CD_BLOCK_LEN;
    } else {
        len = g_Cd.overlayLastBlockSize;
    }

    if (g_CdCallback == CdCallback_Familiar) {
        g_Cd.overlayCopyDst = FAMILIAR_PTR;
    } else if (D_80137F96 == 0) {
        g_Cd.overlayCopyDst = WEAPON0_PTR;
    } else {
        g_Cd.overlayCopyDst = WEAPON1_PTR;
    }
    g_Cd.overlayCopyDst += TO_CD_BLOCK(g_Cd.D_80137F74);
    g_Cd.overlayCopySrc = TO_CD_BLOCK(g_Cd.D_80137F70) + D_801EC000;
#if USE_MICRO_OPTIMIZATIONS == 1
    MEMCPY(g_Cd.overlayCopyDst, g_Cd.overlayCopySrc, len);
#else
    for (i = 0; i < len; i++) {
        *g_Cd.overlayCopyDst = *g_Cd.overlayCopySrc;
        g_Cd.overlayCopySrc++;
        g_Cd.overlayCopyDst++;
    }
#endif
    g_Cd.D_80137F70 = (g_Cd.D_80137F70 + 1) & 7;
    g_Cd.D_80137F74++;
    g_Cd.overlayBlockCount--;
    if (g_Cd.overlayBlockCount < 0 ||
        g_Cd.overlayBlockCount == 0 && g_Cd.overlayLastBlockSize == 0) {
        g_Cd.D_80137F78 = 1;
        CdDataCallback(NULL);
    }
}

void func_801078C4(void) {
    s32 i;
    s32 len;
    s32 var_a3;

    if (g_Cd.overlayBlockCount != 0) {
        len = CD_BLOCK_LEN;
    } else {
        len = g_Cd.overlayLastBlockSize;
    }
    g_Cd.overlayCopyDst = TO_CD_BLOCK(g_Cd.D_80137F74) + g_Pix[0];
    g_Cd.overlayCopySrc = TO_CD_BLOCK(g_Cd.D_80137F70) + D_801EC000;
#if USE_MICRO_OPTIMIZATIONS == 1
    MEMCPY(g_Cd.overlayCopyDst, g_Cd.overlayCopySrc, len);
#else
    for (i = 0; i < len; i++) {
        *g_Cd.overlayCopyDst = *g_Cd.overlayCopySrc;
        g_Cd.overlayCopySrc++;
        g_Cd.overlayCopyDst++;
    }
#endif
    g_Cd.D_80137F70 = (g_Cd.D_80137F70 + 1) & 7;
    g_Cd.D_80137F74++;
    g_Cd.overlayBlockCount--;
    if (g_Cd.overlayBlockCount < 0 ||
        g_Cd.overlayBlockCount == 0 && g_Cd.overlayLastBlockSize == 0) {
        if (g_CdCallback == CdCallback_Familiar) {
            // Copy familiar graphics in the VRAM
            g_Cd.overlayBlockCount = 20;
            g_Cd.overlayLastBlockSize = 0;
        } else {
            // Copy weapon graphics in the VRAM
            g_Cd.overlayBlockCount = 6;
            g_Cd.overlayLastBlockSize = 0;
        }
        g_Cd.D_80137F74 = 0;
        CdDataCallback(CopySupportOvlCallback);
        if (g_CdCallback == CdCallback_12) {
            LoadTPage(g_Pix[0], 0, 0, 0x240, 0x100, 0x100, 0x80);
        } else if (g_CdCallback == CdCallback_13) {
            LoadTPage(g_Pix[0], 0, 0, 0x240, 0x180, 0x100, 0x80);
        } else {
            LoadTPage(g_Pix[0], 0, 0, 0x2C0, 0x100, 0x100, 0x80);
            LoadTPage(g_Pix[2], 0, 0, 0x2C0, 0x180, 0x80, 0x80);
        }
    }
}

void CopyMonsterPreviewCallback(void) {
    s32 i;
    s32 len;

    if (g_Cd.overlayBlockCount != 0) {
        len = CD_BLOCK_LEN;
    } else {
        len = g_Cd.overlayLastBlockSize;
    }
    g_Cd.overlayCopyDst = TO_CD_BLOCK(g_Cd.D_80137F74) + g_Pix[0];
    g_Cd.overlayCopySrc = TO_CD_BLOCK(g_Cd.D_80137F70) + D_801EC000;
#if USE_MICRO_OPTIMIZATIONS == 1
    MEMCPY(g_Cd.overlayCopyDst, g_Cd.overlayCopySrc, len);
#else
    for (i = 0; i < len; i++) {
        *g_Cd.overlayCopyDst = *g_Cd.overlayCopySrc;
        g_Cd.overlayCopySrc++;
        g_Cd.overlayCopyDst++;
    }
#endif
    g_Cd.D_80137F70 = (g_Cd.D_80137F70 + 1) & 7;
    g_Cd.D_80137F74++;
    g_Cd.overlayBlockCount--;
    if (g_Cd.overlayBlockCount < 0 ||
        (g_Cd.overlayBlockCount == 0 && g_Cd.overlayLastBlockSize == 0)) {
        LoadTPage(g_Pix[0], 2, 0, 0x20, 0x100, 0x60, 0x70);
        g_Cd.D_80137F78 = 1;
        CdDataCallback(NULL);
    }
}

void func_80107C6C(void) {
    s32 len;

    if (g_Cd.D_80137F74 != 0 && (s16)SsVabTransCompleted(SS_IMEDIATE) != 1) {
        func_801073C0();
        g_Cd.D_80137F78 = -1;
        return;
    }
    g_Cd.overlayCopySrc = (g_Cd.D_80137F70 << 0xB) + D_801EC000;
    if (g_Cd.overlayBlockCount != 0) {
        len = CD_BLOCK_LEN;
    } else {
        len = g_Cd.overlayLastBlockSize;
    }
    D_80137FA8 = SsVabTransBodyPartly(g_Cd.overlayCopySrc, len, g_VabId);
    if (D_80137FA8 == -1) {
        CdDataCallback(NULL);
        g_Cd.D_80137F78 = -3;
    }
    g_Cd.D_80137F70 = (g_Cd.D_80137F70 + 1) & 7;
    g_Cd.D_80137F74++;
    g_Cd.overlayBlockCount--;
    if (g_Cd.overlayBlockCount < 0 ||
        (g_Cd.overlayBlockCount == 0 && g_Cd.overlayLastBlockSize == 0)) {
        CdDataCallback(NULL);
        g_Cd.D_80137F78 = 1;
    }
}

void func_80107DB4(void) {
    s32 i;
    s32 len;

    if (g_Cd.overlayBlockCount != 0) {
        len = CD_BLOCK_LEN;
    } else {
        len = g_Cd.overlayLastBlockSize;
    }
    g_Cd.overlayCopyDst = TO_CD_BLOCK(g_Cd.D_80137F74) + g_Cd.addr;
    g_Cd.overlayCopySrc = TO_CD_BLOCK(g_Cd.D_80137F70) + D_801EC000;
#if USE_MICRO_OPTIMIZATIONS == 1
    MEMCPY(g_Cd.overlayCopyDst, g_Cd.overlayCopySrc, len);
#else
    for (i = 0; i < len; i++) {
        *g_Cd.overlayCopyDst = *g_Cd.overlayCopySrc;
        g_Cd.overlayCopySrc++;
        g_Cd.overlayCopyDst++;
    }
#endif
    g_Cd.D_80137F70 = (g_Cd.D_80137F70 + 1) & 7;
    g_Cd.D_80137F74++;
    g_Cd.overlayBlockCount--;
    if (g_Cd.overlayBlockCount < 0 ||
        (g_Cd.overlayBlockCount == 0 && g_Cd.overlayLastBlockSize == 0)) {
        g_Cd.D_80137F78 = 1;
        CdDataCallback(NULL);
    }
}

void func_80107EF0(void) {
    s32 i;
    s32 len;
    short res;

    if (g_Cd.overlayBlockCount != 0) {
        len = CD_BLOCK_LEN;
    } else {
        len = g_Cd.overlayLastBlockSize;
    }
    g_Cd.overlayCopyDst = TO_CD_BLOCK(g_Cd.D_80137F74) + g_Cd.addr;
    g_Cd.overlayCopySrc = TO_CD_BLOCK(g_Cd.D_80137F70) + D_801EC000;
#if USE_MICRO_OPTIMIZATIONS == 1
    MEMCPY(g_Cd.overlayCopyDst, g_Cd.overlayCopySrc, len);
#else
    for (i = 0; i < len; i++) {
        *g_Cd.overlayCopyDst = *g_Cd.overlayCopySrc;
        g_Cd.overlayCopySrc++;
        g_Cd.overlayCopyDst++;
    }
#endif
    g_Cd.D_80137F70 = (g_Cd.D_80137F70 + 1) & 7;
    g_Cd.D_80137F74++;
    g_Cd.overlayBlockCount--;
    if (g_Cd.overlayBlockCount < 0 ||
        (g_Cd.overlayBlockCount == 0 && g_Cd.overlayLastBlockSize == 0)) {
        res = SsVabOpenHeadSticky(g_Cd.addr, g_VabId, g_VabAddrs[g_VabId]);
        if (res < 0) {
            g_Cd.D_80137F78 = -2;
            CdDataCallback(NULL);
        } else {
            CdFile* cdFile = D_800ACC74[D_80137F96];
            g_Cd.overlayBlockCount = cdFile->size / CD_BLOCK_LEN;
            g_Cd.overlayLastBlockSize =
                cdFile->size - cdFile->size / CD_BLOCK_LEN * CD_BLOCK_LEN;
            g_Cd.D_80137F74 = 0;
            CdDataCallback(func_80107C6C);
        }
    }
}

void func_801080DC(void) {
    int new_var2;
    s32 new_var;
    CdThing* new_var3;
    RECT* r;

    new_var2 = 6;
    if (g_Cd.D_80137F70 == 3 || g_Cd.D_80137F70 == 7) {
        switch (g_CdCallback) {
        case CdCallback_1:
            g_Cd.dstRect.x = D_800AC958[g_Cd.D_80137F74];
            g_Cd.dstRect.y = ((g_Cd.D_80137F74 << new_var2) & 0x80) + 0x100;
            g_Cd.dstRect.w = 0x20;
            g_Cd.dstRect.h = 0x80;
            if (g_Cd.D_80137F74 == 0x1A) {
                g_Cd.dstRect.y = 0x181;
                g_Cd.dstRect.h = 0x7F;
                if (!g_Cd.D_80137F74 && !g_Cd.D_80137F74) {
                }
            }
            new_var3 = &g_Cd;
            if (new_var3->D_80137F74 == 0x20) {
                g_Cd.dstRect.x = 0;
                g_Cd.dstRect.y = 0xF0;
                g_Cd.dstRect.w = 0x100;
                g_Cd.dstRect.h = 0x10;
            }
            break;
        case CdCallback_0:
        case CdCallback_StageChr:
        case CdCallback_6:
            g_Cd.dstRect.x = D_800AC998[g_Cd.D_80137F74 & 0x1F];
            new_var = g_Cd.D_80137F74;
            g_Cd.dstRect.y = (new_var << 6) & 0x80;
            if (g_Cd.D_80137F74 >= 0x20) {
                g_Cd.dstRect.y += 0x100;
            }
            g_Cd.dstRect.w = 0x20;
            g_Cd.dstRect.h = 0x80;
            break;
        case CdCallback_3:
            g_Cd.dstRect.x = 0x100;
            g_Cd.dstRect.y = 0x100;
            g_Cd.dstRect.w = 0x40;
            g_Cd.dstRect.h = 0x40;
            break;
        }

        if (g_Cd.D_80137F70 == 7) {
            g_Cd.overlayCopySrc = &D_801EE000;
            LoadImage(&g_Cd.dstRect, g_Cd.overlayCopySrc);
            g_Cd.D_80137F74++;
        }
        if (g_Cd.D_80137F70 == 3) {
            g_Cd.overlayCopyDst = D_801EC000;
            LoadImage(&g_Cd.dstRect, g_Cd.overlayCopyDst);
            g_Cd.D_80137F74++;
        }
        if (g_Cd.D_80137F74 >= g_Cd.D_80137F68) {
            g_Cd.D_80137F78 = 1;
            if (g_CdCallback == CdCallback_1) {
                g_Cd.dstRect.x = 0x380;
                g_Cd.dstRect.y = 0x180;
                g_Cd.dstRect.w = 0x10;
                g_Cd.dstRect.h = 1;
                LoadImage(&g_Cd.dstRect, D_800A04CC);
            }
            CdDataCallback(NULL);
        }
    }
    g_Cd.D_80137F70 = (g_Cd.D_80137F70 + 1) & 7;
}

void func_8010838C(s32 cdStep) {
    func_801073C0();
    g_CdStep = cdStep;
}

void func_801083BC(void) {
    g_CdStep = CdStep_LoadInit;
    g_LoadFile = CdFile_25;
    D_8013AE9C = 10;
    D_800ACC64.loc = 0;
}

bool func_801083F0(void) {
    g_CdStep = CdStep_LoadInit;
    g_LoadFile = CdFile_25;

    if (D_8013AE9C == 0) {
        return false;
    } else {
        D_8013AE9C--;
        D_800ACC64.loc += 4;
    }

    return true;
}

void func_80107460(void);

void PlaySfx(s32);
void SsVabClose(short);

void UpdateCd(void) {
#if defined(VERSION_US) || defined(VERSION_EU) || defined(VERSION_HK) ||       \
    defined(VERSION_JP12)
    const bool UseEuWarning = true;
#elif defined(VERSION_HD) || defined(VERSION_JP10) || defined(VERSION_JP11) || \
    defined(VERSION_USPROTO)
    const bool UseEuWarning = false;
#endif

    unsigned char result[8];
    unsigned char setModeArg[24];
    CdFile* cdFile;
    s32 temp_v1_8;
    s32 temp_v1_9;
    s32 i;
    s8 seqIdx;
    u32* pSrc;
    u32* pDst;
    u16* clutAddr;
    s32* pLoadFile;
    CdMgr* cd;

    if (D_8003C728 != 0) {
        return;
    }
    pLoadFile = &g_LoadFile;
    g_IsUsingCd = g_CdStep;
    if (g_LoadFile == CdFile_StagePrg) {
        cdFile = &g_LbaStagePrg;
        if (UseEuWarning && g_StageId == STAGE_EU_WARNING) {
            g_LbaStagePrg.loc = OFF_WARNING_TIM;
            g_LbaStagePrg.size = LEN_WARNING_TIM;
            g_LbaStagePrg.nextCdFileType = CdFile_NoNext;
        } else {
            g_LbaStagePrg.loc = g_StagesLba[g_StageId].ovlOff;
            g_LbaStagePrg.size = g_StagesLba[g_StageId].ovlLen;
            seqIdx = g_StagesLba[g_StageId].seqIdx;
            if (seqIdx >= 0) { // A stage has an optional sequence file
                g_LbaStagePrg.nextCdFileType = CdFile_Seq;
                g_LbaStageSeq.loc = *(&D_800ACCF8[seqIdx].loc);
                g_LbaStageSeq.size = *(&D_800ACCF8[seqIdx].size);
            } else {
                g_LbaStagePrg.nextCdFileType = CdFile_NoNext;
            }
        }
    } else {
        cdFile = D_800ACC74[g_LoadFile & 0x7FFF];
        if (g_LoadFile == CdFile_StageChr) {
            cdFile->loc = g_StagesLba[g_LoadOvlIdx].gfxOff;
        }
        if (g_LoadFile == CdFile_StageSfx) {
            g_LbaStageVh.loc = g_StagesLba[g_LoadOvlIdx].vhOff;
            g_LbaStageVh.size = g_StagesLba[g_LoadOvlIdx].vhLen;
            g_LbaStageVb.size = g_StagesLba[g_LoadOvlIdx].vbLen;
        }
        if (*pLoadFile == CdFile_GameChr) {
            if (g_StageId == STAGE_ST0 ||
                g_PlayableCharacter != PLAYER_ALUCARD) {
                g_LbaBinGame.loc = OFF_BIN_FGAME2;
                g_LbaBinGame.nextCdFileType = CdFile_RichterPrg;
            } else {
                g_LbaBinGame.loc = OFF_BIN_FGAME;
                g_LbaBinGame.nextCdFileType = CdFile_AlucardPrg;
            }
        }
        if (g_LoadFile == CdFile_ServantChr) {
            g_LbaServantChr.loc = g_LbaServantChrOff[g_LoadOvlIdx];
            g_LbaServantVh.loc = g_LbaServantVhOff[g_LoadOvlIdx];
            g_LbaServantVh.size = g_LbaServantVhLen[g_LoadOvlIdx];
            g_LbaServantVb.loc = g_LbaServantVbOff[g_LoadOvlIdx];
            g_LbaServantVb.size = g_LbaServantVbLen[g_LoadOvlIdx];
        }
    }

    switch (g_CdStep) {
    case CdStep_None:
        break;

    case CdStep_LoadInit:
        D_80137FAC = 0;
        if (g_LoadFile == CdFile_None) {
            g_CdStep = CdStep_None;
            break;
        }

        func_801073C0();
        if (CdSync(CdlNop, NULL) == CdlNoIntr) {
            break;
        }

        CdControl(CdlNop, NULL, result);
        if (result[0] & CdlModeRT) {
            break;
        }

        if (!CdControl(CdlPause, NULL, NULL)) {
            break;
        }

        if (CdSync(CdlNop, NULL) == CdlDiskError) {
            func_8010838C(CdStep_DiskErr);
            break;
        }
        g_CdStep++;
        break;

    case CdStep_SetSpeed:
        if (CdSync(CdlNop, NULL) == CdlNoIntr) {
            break;
        }
        setModeArg[0] = CdlModeSpeed;
        if (!CdControl(CdlSetmode, setModeArg, NULL)) {
            break;
        }

        if (CdSync(CdlNop, NULL) == CdlDiskError) {
            func_8010838C(CdStep_DiskErr);
            break;
        }
        g_CdStep++;
        break;

    case CdStep_SetPos:
        if (CdSync(CdlNop, NULL) == CdlNoIntr) {
            break;
        }
        cd = &g_CdCallback;
        cd->cb = cdFile->cb;
        pLoadFile = &cdFile->size;
        g_Cd.D_80137F68 = *pLoadFile / 0x2000;
        g_VabId = cdFile->vabId;
        g_Cd.overlayBlockCount = *pLoadFile / 0x800;
        // how many bytes long will be the last block to read?
        // eg. if the file is 0x820 long, then the value will be 0x20
        g_Cd.overlayLastBlockSize = *pLoadFile % 0x800;
        D_80137F96 = cdFile->unkF;
        g_Cd.addr = D_800ACD10[cdFile->unkD];
        g_Cd.D_80137F6C = 0;
        g_Cd.D_80137F70 = 0;
        g_Cd.D_80137F74 = 0;
        g_Cd.D_80137F78 = 0;
        if (g_LoadFile & 0x8000) {
            CdIntToPos(cdFile->loc, &cd->loc);
            if (CdControl(CdlSeekL, &cd->loc, NULL)) {
                g_CdStep = CdStep_Complete;
            }
        } else {
            if (cd->cb == CdCallback_16 || cd->cb == CdCallback_Vh) {
                SsVabClose(g_VabId);
            }
            if (g_CdCallback != CdCallback_16 &&
                    g_CdCallback != CdCallback_Vh ||
                (s16)SsVabTransCompleted(SS_IMEDIATE) == 1) {
                CdIntToPos(cdFile->loc, &g_CdLoc);
                if (g_CdCallback == CdCallback_12) {
                    CdIntToPos(
                        g_EquippedWeaponIds[0] * 14 + cdFile->loc, &g_CdLoc);
                }
                if (g_CdCallback == CdCallback_13) {
                    CdIntToPos(
                        g_EquippedWeaponIds[1] * 14 + cdFile->loc, &g_CdLoc);
                }
                if (g_CdCallback == CdCallback_Monster) {
                    CdIntToPos(g_LoadOvlIdx * 11 + cdFile->loc, &g_CdLoc);
                }
                if (g_CdCallback == CdCallback_4) {
                    CdIntToPos(g_LoadOvlIdx * 4 + cdFile->loc, &g_CdLoc);
                }
                if (CdControl(CdlSetloc, &g_CdLoc, NULL)) {
                    if (CdSync(CdlNop, NULL) != CdlDiskError) {
                        g_CdStep++;
                    } else {
                        func_8010838C(CdStep_DiskErr);
                    }
                }
            }
        }
        break;

    case CdStep_Seek:
        if (CdSync(CdlNop, NULL) == CdlNoIntr) {
            break;
        }
        CdReadyCallback(func_80107460);
        CdDataCallback(g_CdCallbacks[g_CdCallback]);
        if (CdControl(CdlReadN, &g_CdLoc, NULL) == 0) {
            func_801073C0();
        } else if (CdSync(CdlNop, NULL) == CdlDiskError) {
            func_801073C0();
            func_8010838C(CdStep_DiskErr);
        } else {
            g_CdStep++;
        }
        break;

    case CdStep_5:
        if (CdSync(CdlNop, NULL) == CdlDiskError) {
            func_8010838C(CdStep_DiskErr);
            break;
        }
        if (g_Cd.D_80137F78 == -1) {
            func_8010838C(CdStep_DmaErr);
        }
        if (g_Cd.D_80137F78 == -3) {
            func_8010838C(CdStep_DmaErr);
        }
        if (g_Cd.D_80137F78 == -2) {
            func_8010838C(CdStep_SdHeaderErr);
        }
        if (g_Cd.D_80137F78 == 1) {
            func_801073C0();
            if (CdControl(CdlPause, NULL, NULL)) {
                g_CdStep++;
            }
        }
        break;

    case CdStep_6:
        if (CdSync(CdlNop, NULL) == CdlDiskError) {
            func_8010838C(CdStep_DiskErr);
            break;
        }
        switch (g_CdCallback) {
        case CdCallback_StagePrg:
            pSrc = STAGE_PRG_PTR;
            i = 0;
            pDst = &g_api.o;
            do {
                i++;
                *pDst++ = *pSrc++;
            } while (i < (s32)(sizeof(Overlay) / sizeof(void*)));
            break;
        case CdCallback_6:
            clutAddr = g_Clut[0];
            StoreImage(&g_Vram.D_800ACDB8, clutAddr);
            clutAddr = g_Clut[2];
            StoreImage(&g_Vram.D_800ACDB8, clutAddr);
            DrawSync(0);
            LoadImage(&g_Vram.D_800ACDB0, clutAddr);
            break;
        case CdCallback_0:
            LoadImage(&g_Vram.D_800ACD98, &D_800A04CC);
            break;
        case CdCallback_1:
            StoreImage(&g_Vram.D_800ACDA8, g_Clut[1]);
            break;
        case CdCallback_StageChr:
            StoreImage(&g_Vram.D_800ACDB8, g_Clut[0]);
            break;
        case CdCallback_16:
            D_80137FB0 = (short)SsVabOpenHeadSticky(
                g_Cd.addr, g_VabId, g_VabAddrs[g_VabId]);
            break;
        case CdCallback_17:
        case CdCallback_Vh:
            while ((s16)SsVabTransCompleted(SS_IMEDIATE) != 1) {
            }
            break;
        case CdCallback_Seq:
            temp_v1_9 = g_StagesLba[g_StageId].seqIdx;
            func_80131EBC(aPqes_1, D_800ACCF8[temp_v1_9].unk8);
            break;
        }

        if (D_800ACD7C != 0) {
            D_800ACD7C = 0;
            g_CdStep = CdStep_LoadInit;
        } else if (cdFile->nextCdFileType != CdFile_NoNext) {
            g_LoadFile = cdFile->nextCdFileType;
            g_CdStep = CdStep_LoadInit;
        } else if (CdControl(CdlPause, NULL, NULL)) {
            g_LoadFile = CdFile_None;
            g_CdStep = CdStep_None;
            D_80137FA0 = 0;
        }
        break;

    case CdStep_Complete:
        if (CdSync(CdlNop, NULL) == CdlDiskError) {
            func_8010838C(CdStep_DiskErr);
        } else if (CdSync(CdlNop, NULL) == CdlComplete) {
            g_LoadFile = CdFile_None;
            g_CdStep = CdStep_None;
            D_80137FA0 = 0;
        }
        break;

    case CdStep_DmaErr:
        if (g_Timer & 4) {
            FntPrint("DMA error\n");
        } else {
            FntPrint("\n");
        }
        g_CdStep = CdStep_Retry;
        break;

    case CdStep_SdHeaderErr:
        if (g_Timer & 4) {
            FntPrint("SD HEADER error\n");
        } else {
            FntPrint("\n");
        }
        g_CdStep = CdStep_Retry;
        break;

    case CdStep_DiskErr:
        if (g_Timer & 4) {
            FntPrint("disk error\n");
        } else {
            FntPrint("\n");
        }
        g_CdStep = CdStep_Retry;
        break;

    case CdStep_Retry:
        if (g_Timer & 4) {
            FntPrint("retry\n");
        } else {
            FntPrint("\n");
        }
        do {
        } while (CdInit() == 0);
        MuteSound();
        g_CdStep = CdStep_LoadInit;
        D_800ACD7C = 1;
        D_80137FA0++;
        break;

    case CdStep_RetryXa:
        if (g_Timer & 4) {
            FntPrint("retry xa\n");
        } else {
            FntPrint("\n");
        }
        do {
        } while (CdInit() == 0);
        MuteSound();
        PlaySfx(currentMusicId);
        g_CdStep = CdStep_None;
        D_800ACD7C = 1;
        break;

    case CdStep_CdShellOpenErr:
        // The CdlStatShellOpen flag is cleared only when CdlNOP is issued
        CdControlF(CdlNop, NULL);
        g_CdStep = CdStep_F1;
        if (g_Timer & 4) {
            FntPrint("cd shell open error\n");
        }
        break;

    case CdStep_F1:
        temp_v1_8 = CdSync(CdlNop, result) == CdlComplete;
        if (temp_v1_8 != 0) {
            if (!(result[0] & CdlStatShellOpen)) {
                g_CdStep = CdStep_F2;
            } else {
                g_CdStep = CdStep_CdShellOpenErr;
            }
        } else if (temp_v1_8 == 5) {
            g_CdStep = CdStep_CdShellOpenErr;
        }
        if (g_Timer & 4) {
            FntPrint("cd shell open error\n");
        }
        break;

    case CdStep_F2:
        CdControlF(CdlGetTN, NULL);
        g_CdStep = CdStep_F3;
        break;

    case CdStep_F3:
        temp_v1_9 = CdSync(CdlNop, result) == CdlComplete;
        if (temp_v1_9 != 0) {
            if ((result[0] & (CdlStatShellOpen | CdlStatStandby)) == 2) {
                g_CdStep = CdStep_Retry;
                if (g_LoadFile == CdFile_None && currentMusicId != 0 &&
                    stopMusicFlag == 0) {
                    g_CdStep = CdStep_RetryXa;
                }
            } else {
                g_CdStep = CdStep_CdShellOpenErr;
            }
        } else if (temp_v1_9 == 5) {
            g_CdStep = CdStep_CdShellOpenErr;
        }
        if (g_Timer & 4) {
            FntPrint("checking cd\n");
        } else {
            FntPrint("\n");
        }
        break;

    default:
        FntPrint("error step:%02x\n", g_CdStep);
        break;
    }

    if ((!(g_CdStep & 0xF0)) && func_801073E8() != 0) {
        func_8010838C(CdStep_CdShellOpenErr);
    }
}
