#include "dra.h"
#include "sfx.h"

u16 g_ButtonMask[] = {
    PAD_SQUARE, PAD_CIRCLE, PAD_CROSS, PAD_TRIANGLE,
    PAD_R2,     PAD_L1,     PAD_R1,    PAD_L2,
};

u8 g_StageSelectOrder[] = {
    STAGE_MEMORYCARD, STAGE_ST0,      STAGE_ARE,      STAGE_CAT,  STAGE_CEN,
    STAGE_CHI,        STAGE_DAI,      STAGE_DRE,      STAGE_LIB,  STAGE_NO0,
    STAGE_NO1,        STAGE_NO2,      STAGE_NO3,      STAGE_NO4,  STAGE_NP3,
    STAGE_NZ0,        STAGE_NZ1,      STAGE_TOP,      STAGE_WRP,  STAGE_RARE,
    STAGE_RCAT,       STAGE_RCEN,     STAGE_RCHI,     STAGE_RDAI, STAGE_RLIB,
    STAGE_RNO0,       STAGE_RNO1,     STAGE_RNO2,     STAGE_RNO3, STAGE_RNO4,
    STAGE_RNZ0,       STAGE_RNZ1,     STAGE_RTOP,     STAGE_RWRP, STAGE_MAD,
    STAGE_HAGI_LOAD,  STAGE_IGA_LOAD, STAGE_IWA_LOAD, STAGE_TE1,  STAGE_TE2,
    STAGE_TE3,        STAGE_TE4,      STAGE_TE5,      STAGE_MAR,  STAGE_BO0,
    STAGE_BO1,        STAGE_BO2,      STAGE_BO3,      STAGE_BO4,  STAGE_BO5,
    STAGE_BO6,        STAGE_BO7,      STAGE_RBO0,     STAGE_RBO1, STAGE_RBO2,
    STAGE_RBO3,       STAGE_RBO4,     STAGE_RBO5,     STAGE_RBO6, STAGE_RBO7,
    STAGE_RBO8,       STAGE_TOP_ALT,  STAGE_ENDING,
};

// The effect of this array is unknown
// 0: 25% of chance
// 1: 62.5% of chance
// 2: 12.5% of chance
u8 g_RandomizeCastleFlag13[] = {
    0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2,
};

RECT D_800A01C0[] = {
    {128, 0, 192, 0},     // unknown usage
    {192, 0, 255, 0},     // unknown usage
    {255, 0, 255, 64},    // unknown usage
    {255, 64, 255, 128},  // unknown usage
    {255, 128, 255, 192}, // unknown usage
    {255, 192, 255, 255}, // unknown usage
    {255, 255, 192, 255}, // unknown usage
    {192, 255, 128, 255}, // unknown usage
    {128, 255, 64, 255},  // unknown usage
    {64, 255, 0, 255},    // unknown usage
    {0, 255, 0, 192},     // unknown usage
    {0, 192, 0, 128},     // unknown usage
    {0, 128, 0, 64},      // unknown usage
    {0, 64, 0, 0},        // unknown usage
    {0, 0, 64, 0},        // unknown usage
    {64, 0, 128, 0},      // unknown usage
};

void func_800E493C(void) {
    if (g_Settings.isSoundMono == false) {
        PlaySfx(SET_SOUNDMODE_STEREO);
    } else {
        PlaySfx(SET_SOUNDMODE_MONO);
    }
}

void func_800E4970(void) {
    SetGameState(Game_NowLoading);
    g_GameStep = NowLoading_2;
    ClearBackbuffer();
    SetStageDisplayBuffer();
    func_800EAD7C();
    DestroyEntities(0);
    DestroyAllPrimitives();
    func_800EA538(0);
    HideAllBackgroundLayers();
    ResetPendingGfxLoad();
    func_800EDAE4();
    PlaySfx(SET_UNK_12);
    PlaySfx(SET_UNK_0B);
    func_80132760();
    func_800E493C();
}

void func_800E4A04(void) { s32 pad[3]; }

void HandlePlay(void) {
    s32 i;
    u8* ptr;
    u16 *sx, *sy, *ex, *ey;
    Primitive* prim;

    switch (g_GameStep) {
    case Play_Reset:
        D_8003C9A4 = 0;
        D_8003C738 = 0;
        if (D_8003C730 == 0) {
            for (i = 0; i < LEN(g_CastleFlags); i++) {
                g_CastleFlags[i] = 0;
            }
            g_CastleFlags[0xB9] = 1;
            g_CastleFlags[0x9B] = 1;
            if (g_PlayableCharacter != 0) {
                g_CastleFlags[0x35] = 1;
                g_CastleFlags[0x62] = 1;
                g_CastleFlags[0x63] = 1;
                g_CastleFlags[0x85] = 1;
                g_CastleFlags[0x95] = 1;
                g_CastleFlags[0x96] = 1;
            }

            for (i = 0, ptr = &g_MenuNavigation; i < sizeof(MenuNavigation);
                 i++) {
                *ptr++ = 0;
            }

            for (i = 0; i < BUTTON_COUNT; i++) {
                g_Settings.buttonConfig[i] = i;
                g_Settings.buttonMask[i] = g_ButtonMask[i];
            }
            for (i = 0; i < LEN(g_Settings.cloakColors); i++) {
                g_Settings.cloakColors[i] = 0;
            }

            g_Settings.windowColors[0] = 0;
            g_Settings.windowColors[1] = 0;
            g_Settings.windowColors[2] = 8;
            g_Settings.isCloakLiningReversed = 0;
            g_Settings.isSoundMono = true;
            func_800E493C();
            for (i = 0; i < LEN(g_Settings.equipOrderTypes); i++) {
                g_Settings.equipOrderTypes[i] = i;
            }
        }
        func_800F2120();
        func_800FDE00();
        func_800FF0B8();
        ApplyJosephsCloakPalette();
        func_800EAD0C();
        g_GameStep++;
        break;
    case Play_Init:
        LoadGfxAsync(ANIMSET_DRA(1));
        LoadGfxAsync(ANIMSET_OVL(0));
        func_800EA5E4(ANIMSET_OVL(0));
        g_GameStep++;
        break;
    case Play_PrepareDemo:
        if (func_800EB720()) {
            break;
        }
        if (g_DemoMode != Demo_None) {
            srand(1);
            g_randomNext = 0x4D2;
            g_Timer = 0;
            g_GameTimer = 0;
        }
        g_GameStep++;
        break;
    case Play_Default:
        DemoUpdate();
        func_800F298C();
        break;
    case Play_PrepareNextStage:
        PlaySfx(SET_UNK_12);
        PlaySfx(SET_UNK_0B);
        func_80132760();
        if (D_80097C98 < 0) {
            func_800E4970();
            DemoInit(2);
            return;
        }
        if (D_80097C98 & 0x08000000) {
            func_800E4970();
            return;
        }
        g_StageId = func_800F16D0();
        g_GpuBuffers[1].draw.isbg = 0;
        g_GpuBuffers[0].draw.isbg = 0;
        HideAllBackgroundLayers();
        func_800EA538(1);
        ResetPendingGfxLoad();
        DestroyEntities(0);
        DestroyAllPrimitives();
        func_800EDAE4();
        func_801024DC();
        if (g_CastleFlags[0x13] & 0x80) {
            g_CastleFlags[0x13] = g_RandomizeCastleFlag13[rand() & 0xF] + 0x80;
        }
        g_GameStep++;
        break;
    case Play_LoadStageChr:
        if (g_UseDisk) {
            if (g_StageId == STAGE_DRE || g_StageId == STAGE_CEN ||
                g_StageId == STAGE_RCEN) {
                if (g_IsUsingCd) {
                    break;
                }
                g_CdStep = CdStep_LoadInit;
                g_LoadFile = CdFile_StageChr;
                g_LoadOvlIdx = g_StageId;
            }
            if (D_8006C374 == 0x07) {
                if (g_IsUsingCd) {
                    break;
                }
                g_CdStep = CdStep_LoadInit;
                g_LoadFile = CdFile_StageChr;
                g_LoadOvlIdx = g_StageId;
            }
            if (D_8006C374 == 0x3C) {
                if (g_IsUsingCd) {
                    break;
                }
                g_CdStep = CdStep_LoadInit;
                g_LoadFile = CdFile_StageChr;
                g_LoadOvlIdx = 9;
            }
            if (D_8006C374 == 0x25) {
                if (g_IsUsingCd) {
                    break;
                }
                g_CdStep = CdStep_LoadInit;
                g_LoadFile = CdFile_StageChr;
                g_LoadOvlIdx = 0x2B;
            }
            if (D_8006C374 == 0x26) {
                if (g_IsUsingCd) {
                    break;
                }
                g_CdStep = CdStep_LoadInit;
                g_LoadFile = CdFile_StageChr;
                g_LoadOvlIdx = 0xB;
            }
            if (D_8006C374 == 0x27) {
                if (g_IsUsingCd) {
                    break;
                }
                g_CdStep = CdStep_LoadInit;
                g_LoadFile = CdFile_StageChr;
                g_LoadOvlIdx = 2;
            }
        }
        MoveImage(&g_Vram.D_800ACD80, 0, 0x100);
        g_GpuBuffers[1].draw.isbg = 1;
        g_GpuBuffers[0].draw.isbg = 1;
        D_8013640C = AllocPrimitives(PRIM_GT4, 16);
        D_80136410 = 0;
        prim = &g_PrimBuf[D_8013640C];
        for (i = 0; prim != NULL; i++) {
            sx = &D_800A01C0[i].x;
            sy = &D_800A01C0[i].y;
            ex = &D_800A01C0[i].w;
            ey = &D_800A01C0[i].h;
            prim->x0 = *sx;
            prim->y0 = *sy;
            prim->x1 = *ex;
            prim->y1 = *ey;
            prim->x2 =
                128 +
                (((rcos(0x400 - ((i + 0) << 8)) >> 4) * D_80136410) >> 10);
            prim->y2 =
                128 -
                (((rsin(0x400 - ((i + 0) << 8)) >> 4) * D_80136410) >> 10);
            prim->x3 =
                128 +
                (((rcos(0x400 - ((i + 1) << 8)) >> 4) * D_80136410) >> 10);
            prim->y3 =
                128 -
                (((rsin(0x400 - ((i + 1) << 8)) >> 4) * D_80136410) >> 10);
            prim->u0 = *sx;
            prim->v0 = *sy;
            prim->u1 = *ex;
            prim->v1 = *ey;
            prim->u2 = 128;
            prim->v2 = 128;
            prim->u3 = 128;
            prim->v3 = 128;
            prim->tpage = 0x110;
            prim = prim->next;
        }
        func_800E346C();
        g_GameStep++;
        break;
    case Play_WaitStageChr:
        func_800E4A04();
        if (g_IsUsingCd) {
            break;
        }
        g_GameStep++;
        break;
    case Play_LoadStageSfx:
        func_800E4A04();
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_StageSfx;
            g_LoadOvlIdx = g_StageId;
        } else {
            if (LoadFileSim(0, SimFileType_StageChr) < 0 ||
                LoadFileSim(0, SimFileType_Vh) < 0 ||
                LoadFileSim(0, SimFileType_Vb) < 0) {
                break;
            }
        }
        g_GameStep++;
        break;
    case Play_WaitStageSfx:
        func_800E4A04();
        if (g_UseDisk && g_IsUsingCd) {
            break;
        }
        g_GameStep++;
        break;
    case Play_LoadStagePrg:
        func_800E4A04();
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_StagePrg;
        }
        g_GameStep++;
        break;
    case Play_WaitStagePrg:
        func_800E4A04();
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
        } else {
            if (LoadFileSim(0, SimFileType_StagePrg) < 0) {
                break;
            }
            if (g_StagesLba[g_StageId].seqIdx >= 0) {
                if (LoadFileSim(
                        g_StagesLba[g_StageId].seqIdx, SimFileType_Seq) < 0) {
                    break;
                }
            }
        }
        FreePrimitives(D_8013640C);
        if ((D_80097C98 > 3 && D_80097C98 < 6) || D_80097C98 == 6) {
            func_800EA5AC(0xFFFF, 0xFF, 0xFF, 0xFF);
        }
        g_GameStep = 1;
        D_8003C9A4 = 0;
        D_8003C738 = 0;
        func_800EAD7C();
        break;
    }
}

const u32 rodata_footer = 0;
