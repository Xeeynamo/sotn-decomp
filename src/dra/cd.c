#include "dra.h"
#include "lba.h"
#include "sfx.h"

#if USE_CD_SPEED_DOUBLE == 0
#define CDL_MODE_SPEED CdlModeSpeedNormal
#else
#define CDL_MODE_SPEED CdlModeSpeedDouble
#endif

extern u16 D_800A04CC[]; // palette?
extern s16 D_800AC998[];
extern u32* D_801EE000;
extern s32 D_8003C90C;
extern s32 D_8003C910;
extern u32 D_8006EBCC;
extern s32 D_800AC9F8;
extern s8 D_800ACA06;
extern s32 D_800ACAB8;
extern s32 D_800ACAC0;
extern s32 D_800ACAC8;
extern s32 D_800ACAD0;
extern s32 D_800ACAE0;
extern s32 D_800ACB48[]; // FT_xxx.BIN off
extern s32 D_800ACB64[]; // SD_xxx.VH off
extern s32 D_800ACB80[]; // SD_xxx.VH len
extern s32 D_800ACB9C[]; // SD_xxx.VB off
extern s32 D_800ACBB8[]; // SD_xxx.VB len
extern s32 D_800ACBD4;
extern s32 D_800ACBE4;
extern s32 D_800ACBEC;
extern s32 D_800ACBF4;
extern s32 D_800ACBFC;
extern CdFile D_800ACC34;
extern s8 D_800ACC42;

extern CdFileSeq D_800ACCF8[];
extern s32 D_800ACD10[];
extern void (*g_CdCallbacks[])(void);
extern s32 D_800ACD7C;
extern s32 D_800BD1C8[];
extern u8 D_80137F96;
extern s32 D_80137FA0;
extern s32 D_80137FAC;
extern s32 D_80137FB0;
extern const char aPqes_1[];

typedef struct {
    RECT dstRect;
    s32 D_80137F68;
    s32 D_80137F6C;
    s32 overlayCopySrcIndex;
    s32 overlayCopyDstIndex;
    s32 D_80137F78;
    u32* overlayCopySrc;
    s32* overlayCopyDst;
    s8* D_80137F88;
    s32 overlayBlockCount;
    s32 overlayLastBlockSize;
    s16 D_80137F94;
} CdThing;

CdCallbacks g_CdCallback;
extern CdThing g_Cd;
extern CdlLOC g_CdLoc;
extern s32 D_80137F68;
extern s32 g_OverlayCopySrcIndex;
extern s32 g_OverlayCopyDstIndex;
extern s32 D_80137F78[];
extern u32* g_OverlayCopySrc;
extern s32* g_OverlayCopyDst;
extern s8* D_80137F88;
extern s32 g_OverlayBlockCount;
extern s32 g_OverlayLastBlockSize;
extern s16 D_80137F94;

INCLUDE_ASM("asm/us/dra/nonmatchings/cd", CopyMapOverlayCallback);
// DECOMP_ME_WIP CopyMapOverlayCallback https://decomp.me/scratch/1AWN1

INCLUDE_ASM("asm/us/dra/nonmatchings/cd", func_80107614);
// DECOMP_ME_WIP func_80107614 https://decomp.me/scratch/U0IGY

INCLUDE_ASM("asm/us/dra/nonmatchings/cd", func_80107750);

INCLUDE_ASM("asm/us/dra/nonmatchings/cd", func_801078C4);

INCLUDE_ASM("asm/us/dra/nonmatchings/cd", func_80107B04);

INCLUDE_ASM("asm/us/dra/nonmatchings/cd", func_80107C6C);

INCLUDE_ASM("asm/us/dra/nonmatchings/cd", func_80107DB4);

INCLUDE_ASM("asm/us/dra/nonmatchings/cd", func_80107EF0);

void func_801080DC(void) {
    int new_var2;
    s32 new_var;
    RECT* r;

    new_var2 = 6;
    if (g_Cd.overlayCopySrcIndex == 3 || g_Cd.overlayCopySrcIndex == 7) {
        switch (g_CdCallback) {
        case CdCallback_1:
            g_Cd.dstRect.x = D_800AC958[g_OverlayCopyDstIndex];
            g_Cd.dstRect.y =
                ((g_OverlayCopyDstIndex << new_var2) & 0x80) + 0x100;
            g_Cd.dstRect.w = 0x20;
            g_Cd.dstRect.h = 0x80;
            if (g_OverlayCopyDstIndex == 0x1A) {
                g_Cd.dstRect.y = 0x181;
                g_Cd.dstRect.h = 0x7F;
                if (!g_OverlayCopyDstIndex && !g_OverlayCopyDstIndex) {
                }
            }
            if (g_OverlayCopyDstIndex == 0x20) {
                g_Cd.dstRect.x = 0;
                g_Cd.dstRect.y = 0xF0;
                g_Cd.dstRect.w = 0x100;
                g_Cd.dstRect.h = 0x10;
            }
            break;
        case CdCallback_0:
        case CdCallback_2:
        case CdCallback_6:
            g_Cd.dstRect.x = D_800AC998[g_OverlayCopyDstIndex & 0x1F];
            new_var = g_OverlayCopyDstIndex;
            g_Cd.dstRect.y = (new_var << 6) & 0x80;
            if (g_OverlayCopyDstIndex >= 0x20) {
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

        if (g_Cd.overlayCopySrcIndex == 7) {
            g_OverlayCopySrc = &D_801EE000;
            LoadImage(&g_Cd.dstRect, g_OverlayCopySrc);
            g_OverlayCopyDstIndex++;
        }
        if (g_Cd.overlayCopySrcIndex == 3) {
            g_OverlayCopyDst = D_801EC000;
            LoadImage(&g_Cd.dstRect, g_OverlayCopyDst);
            g_OverlayCopyDstIndex++;
        }
        if (g_OverlayCopyDstIndex >= g_Cd.D_80137F68) {
            D_80137F78[0] = 1;
            if (g_CdCallback == CdCallback_1) {
                g_Cd.dstRect.x = 0x380;
                g_Cd.dstRect.y = 0x180;
                g_Cd.dstRect.w = 0x10;
                g_Cd.dstRect.h = 1;
                LoadImage(&g_Cd.dstRect, D_800A04CC);
            }
            CdDataCallback(0);
        }
    }
    g_Cd.overlayCopySrcIndex = (g_Cd.overlayCopySrcIndex + 1) & 7;
}

void func_8010838C(s32 cdStep) {
    func_801073C0();
    g_CdStep = cdStep;
}

void func_801083BC(void) {
    g_CdStep = CdStep_LoadInit;
    D_8006BAFC = CdFileType_25;
    D_8013AE9C = 10;
    D_800ACC64[0] = 0;
}

bool func_801083F0(void) {
    g_CdStep = CdStep_LoadInit;
    D_8006BAFC = CdFileType_25;

    if (D_8013AE9C == 0) {
        return false;
    } else {
        D_8013AE9C--;
        D_800ACC64[0] += 4;
    }

    return true;
}

void func_80107460(void);

void PlaySfx(s32);
void SsVabClose(short);

void func_80108448(void) {
    unsigned char result[8];
    unsigned char setModeArg[24];
    u32* var_v1;
    CdFile* cdFile;
    s32 temp_v1_2;
    s32 temp_v1_8;
    s32 temp_v1_9;
    s32 var_a0;
    s32 cdFileSize;
    s32 var_v0_3;
    s32 var_v0_4;
    s8 seqIdx;
    u32 temp_v1_3;
    u32 temp_v1_4;
    u32* temp_s0;
    u8 temp_a0;
    u32* var_a1;
    u16* clutAddr;

    s32* pCdFileSize;
    CdMgr* cd;

    if (D_8003C728 != 0) {
        return;
    }
    pCdFileSize = &D_8006BAFC;
    D_8006C3B0 = g_CdStep;
    if (D_8006BAFC == CdFileType_StagePrg) {
        cdFile = &D_800ACC34;
        if (g_StageId == STAGE_EU_WARNING) {
            D_800ACC34.loc = OFF_WARNING_TIM;
            D_800ACC34.size = LEN_WARNING_TIM;
            D_800ACC34.nextCdFileType = CdFileType_NoNext;
        } else {
            D_800ACC34.loc = g_StagesLba[g_StageId].ovlOff;
            D_800ACC34.size = g_StagesLba[g_StageId].ovlLen;
            seqIdx = g_StagesLba[g_StageId].seqIdx;
            if (seqIdx >= 0) { // A stage has an optional sequence file
                D_800ACC34.nextCdFileType = CdFileType_Seq;
                D_800ACAB8 = *(temp_s0 = &D_800ACCF8[seqIdx].loc);
                D_800ACAC0 = *(temp_s0 = &D_800ACCF8[seqIdx].size);
            } else {
                D_800ACC34.nextCdFileType = CdFileType_NoNext;
            }
        }
    } else {
        cdFile = D_800ACC74[D_8006BAFC & 0x7FFF];
        if (D_8006BAFC == CdFileType_StageChr) {
            cdFile->loc = g_StagesLba[g_mapTilesetId].gfxOff;
        }
        if (D_8006BAFC == CdFileType_StageSfx) {
            D_800ACAC8 = *(temp_s0 = &g_StagesLba[g_mapTilesetId].vhOff);
            D_800ACAD0 = *(temp_s0 = &g_StagesLba[g_mapTilesetId].vhLen);
            D_800ACAE0 = *(temp_s0 = &g_StagesLba[g_mapTilesetId].vbLen);
        }
        if (*pCdFileSize == CdFileType_GameChr) {
            if (g_StageId == STAGE_ST0 ||
                g_CurrentPlayableCharacter != PLAYER_ALUCARD) {
                D_800AC9F8 = OFF_BIN_FGAME2;
                D_800ACA06 = 5;
            } else {
                D_800AC9F8 = OFF_BIN_FGAME;
                D_800ACA06 = 0x13;
            }
        }
        if (D_8006BAFC == CdFileType_Servant) {
            // SERVANT/FT_xxx.BIN
            D_800ACBD4 = *(temp_s0 = &D_800ACB48[g_mapTilesetId]);

            // SERVANT/SD_xxx.VH
            D_800ACBE4 = *(temp_s0 = &D_800ACB64[g_mapTilesetId]);
            D_800ACBEC = *(temp_s0 = &D_800ACB80[g_mapTilesetId]);

            // SERVANT/SD_xxx.VB
            D_800ACBF4 = *(temp_s0 = &D_800ACB9C[g_mapTilesetId]);
            D_800ACBFC = *(temp_s0 = &D_800ACBB8[g_mapTilesetId]);
        }
    }

    switch (g_CdStep) {
    case CdStep_None:
        break;

    case CdStep_LoadInit:
        D_80137FAC = 0;
        if (D_8006BAFC == CdFileType_None) {
            g_CdStep = CdStep_None;
            break;
        }

        func_801073C0();
        if (CdSync(1, 0) == CdlNoIntr) {
            break;
        }

        CdControl(CdlNop, 0, result);
        if (result[0] & CdlModeRT) {
            break;
        }

        if (!CdControl(CdlPause, 0, 0)) {
            break;
        }

        if (CdSync(1, 0) == CdlDiskError) {
            func_8010838C(CdStep_DiskErr);
            break;
        }
        g_CdStep++;
        break;

    case CdStep_SetSpeed:
        if (CdSync(1, 0) == CdlNoIntr) {
            break;
        }
        setModeArg[0] = CdlModeSpeed;
        if (!CdControl(CdlSetmode, setModeArg, CDL_MODE_SPEED)) {
            break;
        }

        if (CdSync(1, 0) == CdlDiskError) {
            func_8010838C(CdStep_DiskErr);
            break;
        }
        g_CdStep++;
        break;

    case CdStep_SetPos:
        if (CdSync(1, 0) == CdlNoIntr) {
            break;
        }
        cd = &g_CdCallback;
        cd->cb = cdFile->cb;
        pCdFileSize = &cdFile->size;
        cdFileSize = *pCdFileSize;
        if (cdFileSize < 0) {
            cdFileSize += 0x1FFF;
        }
        D_80137F68 = cdFileSize >> 13;
        temp_a0 = cdFile->unkC;
        D_80137F94 = temp_a0;
        var_v0_3 = *pCdFileSize;
        if (var_v0_3 < 0) {
            var_v0_3 += 0x7FF;
        }
        g_OverlayBlockCount = var_v0_3 >> 11;
        temp_v1_2 = (var_v0_4 = *pCdFileSize);
        if (temp_v1_2 < 0) {
            var_v0_4 += 0x7FF;
        }

        // how many bytes long will be the last block to read?
        // eg. if the file is 0x820 long, then the value will be 0x20
        g_OverlayLastBlockSize = temp_v1_2 - (var_v0_4 >> 11 << 11);
        D_80137F96 = cdFile->unkF;
        D_80137F88 = D_800ACD10[cdFile->unkD];
        D_80137F6C = 0;
        D_80137F78[0] = 0;
        g_OverlayCopySrcIndex = 0;
        g_OverlayCopyDstIndex = 0;
        if (D_8006BAFC & 0x8000) {
            CdIntToPos(cdFile->loc, &cd->loc);
            if (CdControl(CdlSeekL, &cd->loc, 0) != 0) {
                g_CdStep = CdStep_Complete;
            }
        } else {
            if (cd->cb == CdCallback_16 || cd->cb == CdCallback_Vh) {
                SsVabClose(temp_a0);
            }
            if (g_CdCallback != CdCallback_16 &&
                    g_CdCallback != CdCallback_Vh ||
                func_800219E0(0) == 1) {
                CdIntToPos(cdFile->loc, &g_CdLoc);
                if (g_CdCallback == CdCallback_12) {
                    CdIntToPos(D_8003C90C * 14 + cdFile->loc, &g_CdLoc);
                }
                if (g_CdCallback == CdCallback_13) {
                    CdIntToPos(D_8003C910 * 14 + cdFile->loc, &g_CdLoc);
                }
                if (g_CdCallback == CdCallback_14) {
                    CdIntToPos(g_mapTilesetId * 11 + cdFile->loc, &g_CdLoc);
                }
                if (g_CdCallback == CdCallback_4) {
                    CdIntToPos(g_mapTilesetId * 4 + cdFile->loc, &g_CdLoc);
                }
                if (CdControl(CdlSetloc, &g_CdLoc, 0) != 0) {
                    if (CdSync(1, 0) != 5) {
                        g_CdStep++;
                    } else {
                        func_8010838C(CdStep_DiskErr);
                    }
                }
            }
        }
        break;

    case CdStep_Seek:
        if (CdSync(1, 0) == CdlNoIntr) {
            break;
        }
        CdReadyCallback(func_80107460);
        CdDataCallback(g_CdCallbacks[g_CdCallback]);
        if (CdControl(CdlReadN, &g_CdLoc, 0) == 0) {
            func_801073C0();
        } else if (CdSync(1, 0) == CdlDiskError) {
            func_801073C0();
            func_8010838C(CdStep_DiskErr);
        } else {
            g_CdStep++;
        }
        break;

    case CdStep_5:
        if (CdSync(1, 0) == CdlDiskError) {
            func_8010838C(CdStep_DiskErr);
            break;
        }
        if (D_80137F78[0] == -1) {
            func_8010838C(CdStep_DmaErr);
        }
        if (D_80137F78[0] == -3) {
            func_8010838C(CdStep_DmaErr);
        }
        if (D_80137F78[0] == -2) {
            func_8010838C(CdStep_SdHeaderErr);
        }
        if (D_80137F78[0] == 1) {
            func_801073C0();
            if (CdControl(CdlPause, 0, 0) != 0) {
                g_CdStep++;
            }
        }
        break;

    case CdStep_6:
        if (CdSync(1, 0) == CdlDiskError) {
            func_8010838C(CdStep_DiskErr);
            break;
        }
        switch (g_CdCallback) {
        case CdCallback_StagePrg:
            var_a1 = 0x80180000;
            var_a0 = 0;
            var_v1 = &g_api;
            for (; var_a0 < 0x10;) {
                *var_v1 = *var_a1;
                var_a0++;
                var_v1++;
                var_a1++;
            }

            break;

        case CdCallback_6:
            clutAddr = g_Clut;
            StoreImage(&g_Vram.D_800ACDB8, clutAddr);
            clutAddr = g_Clut + 0x2000;
            StoreImage(&g_Vram.D_800ACDB8, clutAddr);
            DrawSync(0);
            LoadImage(&g_Vram.D_800ACDB0, clutAddr);
            break;

        case CdCallback_0:
            LoadImage(&g_Vram.D_800ACD98, &D_800A04CC);
            break;

        case CdCallback_1:
            StoreImage(&g_Vram.D_800ACDA8, &D_8006EBCC);
            break;

        case CdCallback_2:
            StoreImage(&g_Vram.D_800ACDB8, g_Clut);
            break;

        case CdCallback_16:
            D_80137FB0 =
                func_80021350(D_80137F88, D_80137F94, D_800BD1C8[D_80137F94]);
            break;

        case CdCallback_17:
        case CdCallback_Vh:
            while (func_800219E0(0) != 1) {
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
        } else if (cdFile->nextCdFileType != CdFileType_NoNext) {
            D_8006BAFC = cdFile->nextCdFileType;
            g_CdStep = CdStep_LoadInit;
        } else if (CdControl(CdlPause, 0, 0) != 0) {
            D_8006BAFC = CdFileType_None;
            g_CdStep = CdStep_None;
            D_80137FA0 = 0;
        }
        break;

    case CdStep_Complete:
        if (CdSync(1, 0) == CdlDiskError) {
            func_8010838C(CdStep_DiskErr);
        } else if (CdSync(1, 0) == CdlComplete) {
            D_8006BAFC = CdFileType_None;
            g_CdStep = CdStep_None;
            D_80137FA0 = 0;
        }
        break;

    case CdStep_DmaErr:
        if (g_blinkTimer & 4) {
            FntPrint("DMA error\n");
        } else {
            FntPrint("\n");
        }
        g_CdStep = CdStep_Retry;
        break;

    case CdStep_SdHeaderErr:
        if (g_blinkTimer & 4) {
            FntPrint("SD HEADER error\n");
        } else {
            FntPrint("\n");
        }
        g_CdStep = CdStep_Retry;
        break;

    case CdStep_DiskErr:
        if (g_blinkTimer & 4) {
            FntPrint("disk error\n");
        } else {
            FntPrint("\n");
        }
        g_CdStep = CdStep_Retry;
        break;

    case CdStep_Retry:
        if (g_blinkTimer & 4) {
            FntPrint("retry\n");
        } else {
            FntPrint("\n");
        }
        do {
        } while (CdInit() == 0);
        func_80132760();
        g_CdStep = CdStep_LoadInit;
        D_800ACD7C = 1;
        D_80137FA0++;
        break;

    case CdStep_RetryXa:
        if (g_blinkTimer & 4) {
            FntPrint("retry xa\n");
        } else {
            FntPrint("\n");
        }
        do {
        } while (CdInit() == 0);
        func_80132760();
        PlaySfx(D_80097910);
        g_CdStep = CdStep_None;
        D_800ACD7C = 1;
        break;

    case CdStep_CdShellOpenErr:
        // The CdlStatShellOpen flag is cleared only when CdlNOP is issued
        CdControlF(CdlNop, 0);
        g_CdStep = CdStep_F1;
        if (g_blinkTimer & 4) {
            FntPrint("cd shell open error\n");
        }
        break;

    case CdStep_F1:
        temp_v1_8 = CdSync(1, result) == CdlComplete;
        if (temp_v1_8 != 0) {
            if (!(result[0] & CdlStatShellOpen)) {
                g_CdStep = CdStep_F2;
            } else {
                g_CdStep = CdStep_CdShellOpenErr;
            }
        } else if (temp_v1_8 == 5) {
            g_CdStep = CdStep_CdShellOpenErr;
        }
        if (g_blinkTimer & 4) {
            FntPrint("cd shell open error\n");
        }
        break;

    case CdStep_F2:
        CdControlF(CdlGetTN, 0);
        g_CdStep = CdStep_F3;
        break;

    case CdStep_F3:
        temp_v1_9 = CdSync(1, result) == CdlComplete;
        if (temp_v1_9 != 0) {
            if ((result[0] & (CdlStatShellOpen | CdlStatStandby)) == 2) {
                g_CdStep = CdStep_Retry;
                if (D_8006BAFC == CdFileType_None && D_80097910 != 0 &&
                    D_80097928 == 0) {
                    g_CdStep = CdStep_RetryXa;
                }
            } else {
                g_CdStep = CdStep_CdShellOpenErr;
            }
        } else if (temp_v1_9 == 5) {
            g_CdStep = CdStep_CdShellOpenErr;
        }
        if (g_blinkTimer & 4) {
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
