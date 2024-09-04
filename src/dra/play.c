#include "dra.h"
#include "dra_bss.h"
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

REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED
REDACTED

REDACTED
    SetGameState(Game_NowLoading);
    g_GameStep = NowLoading_2;
    ClearBackbuffer();
    SetStageDisplayBuffer();
    func_800EAD7C();
    DestroyEntitiesFromIndex(0);
    DestroyAllPrimitives();
    func_800EA538(0);
    HideAllBackgroundLayers();
    ResetPendingGfxLoad();
    func_800EDAE4();
    PlaySfx(SET_UNK_12);
    PlaySfx(SET_UNK_0B);
    MuteSound();
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
        g_GameEngineStep = Engine_Init;
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
        RunMainEngine();
        break;
    case Play_PrepareNextStage:
        PlaySfx(SET_UNK_12);
        PlaySfx(SET_UNK_0B);
        MuteSound();
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
        DestroyEntitiesFromIndex(0);
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
        g_GameEngineStep = Engine_Init;
        D_8003C738 = 0;
        func_800EAD7C();
        break;
    }
}

// Game over melting effect
void func_800E5358(void) {
    Primitive* prim = &g_PrimBuf[D_8013640C];
    s32 i;

    for (i = -3; i < 256; i++, prim = prim->next) {
        if (i < 0)
            continue;
        if (prim->y0 > 256)
            continue;
        if (prim->p1 != 0) {
            prim->p1--;
            continue;
        }
        if (prim->p2 < 10 && (rand() & 1)) {
            prim->p2++;
        } else {
            if (!(rand() & 3)) {
                prim->y0++;
                prim->y1++;
            }
            prim->y0++;
            prim->y1++;
        }
        prim->y2++;
        prim->y3++;
REDACTED
REDACTED
REDACTED
REDACTED
    POLY_GT4* poly = &g_CurrentBuffer->polyGT4[g_GpuUsage.gt4];
    GpuBuffer* buffer = g_CurrentBuffer;

    setSemiTrans(poly, true);
    setShadeTex(poly, false);
    SetPrimRect(poly, 0, 0, 256, 256);
    setUV4(poly, 16, 16, 24, 16, 16, 24, 24, 24);
REDACTED
REDACTED
    poly->clut = g_ClutIds[0x15F];
    AddPrim(&buffer->ot[0x1FF], poly);
    g_GpuUsage.gt4++;
}

void HandleGameOver(void) {
    Primitive* prim;
    u8 var_s0;
    s32 i;
    u8 yScroll;

    switch (g_GameStep) {
    case Gameover_Alt:
        if (g_IsUsingCd) {
            break;
        }
        PlaySfx(0x80);
        D_80097910 = 0;
        g_GameStep++;
        break;
    case Gameover_Init:
    case Gameover_Init_Alt:
        PlaySfx(SET_UNK_11);
        if (g_StageId != STAGE_ST0) {
            g_GpuBuffers[1].draw.isbg = 0;
            g_GpuBuffers[0].draw.isbg = 0;
        }
        DestroyEntitiesFromIndex(0);
        func_800EA538(0);
        ResetPendingGfxLoad();
        DestroyAllPrimitives();
        func_800EDAE4();
        HideAllBackgroundLayers();
        func_800EAD7C();
        g_GameStep++;
        break;
    case Gameover_AllocResources_Alt:
        g_GameStep++;
        break;
    case Gameover_AllocResources:
        if (g_StageId != STAGE_ST0) {
            MoveImage(&g_CurrentBuffer->next->disp.disp, 0x300, 0);
            func_800E346C();
            g_GpuBuffers[1].draw.isbg = 1;
            g_GpuBuffers[0].draw.isbg = 1;
            D_8013640C = AllocPrimitives(PRIM_GT4, 259);
            prim = &g_PrimBuf[D_8013640C];

            SetTexturedPrimRect(prim, 0, 96, 0xFF, 0x20, 0, 0);
            func_801072BC(prim);
            prim->tpage = 8;
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_COLORS | DRAW_TRANSP;
            prim->p1 = 0x60;
            prim = prim->next;

            SetTexturedPrimRect(prim, 0, 0, 128, 240, 0, 0);
            func_801072DC(prim);
            prim->tpage = 0x8A;
            prim->clut = 0x100;
            prim->drawMode = DRAW_COLORS;
            prim = prim->next;

            SetTexturedPrimRect(prim, 128, 0, 128, 240, 0, 0);
            func_801072DC(prim);
            prim->tpage = 0x8B;
            prim->clut = 0x100;
            prim->drawMode = DRAW_COLORS;
            prim = prim->next;

            for (i = 0; i < 256; i++) {
                SetTexturedPrimRect(prim, i, 0, 1, 240, i & 63, 0);
                prim->tpage = i / 64 + 0x10C;
                prim->priority = 0x1FF;
                prim->drawMode = DRAW_DEFAULT;
                prim->p1 = (rand() & 0x1F) + 1;
                prim = prim->next;
            }
        }
        g_GameStep++;
        break;
    case Gameover_2:
    case Gameover_2_Alt:
        if (!func_80133950()) {
            break;
        }
        if (func_80131F68()) {
            break;
        }
        PlaySfx(SET_UNK_12);
        PlaySfx(SET_UNK_0B);
        g_GameStep++;
        break;
    case Gameover_3:
    case Gameover_3_Alt:
        MuteSound();
        if (g_GameStep == 103) {
            g_GameStep = 111;
            break;
        }
        if (g_StageId == STAGE_ST0) {
            g_GameStep = 11;
            break;
        }
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_26;
        }
        g_GameStep++;
        break;
    case Gameover_4:
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
            LoadImage(&g_Vram.D_800ACDD0, (u_long*)STAGE_PRG_PTR);
            LoadImage(&g_Vram.D_800ACDD8, (u_long*)0x80188000);
            LoadImage(&g_Vram.D_800ACDB8, (u_long*)0x80198000);
            StoreImage(&g_Vram.D_800ACDB8, &D_80070BCC);
            LoadImage(&g_Vram.D_800ACDA8, (u_long*)0x8019A000);
            StoreImage(&g_Vram.D_800ACDA8, &D_80070BCC - 0x1000);
        } else {
            if (LoadFileSim(8, SimFileType_System) < 0) {
                break;
            }
            if (LoadFileSim(9, SimFileType_System) < 0) {
                break;
            }
            if (LoadFileSim(10, SimFileType_System) < 0) {
                break;
            }
            if (LoadFileSim(11, SimFileType_System) < 0) {
                break;
            }
        }
#if defined(VERSION_US)
        PlaySfx(MU_LAND_OF_BENEDICTION);
#elif defined(VERSION_HD)
        if (g_PlayableCharacter == PLAYER_ALUCARD) {
            if (g_StageId == STAGE_BO6) {
                switch (rand() % 3) {
                case 0:
                    PlaySfx(0x3DA);
                    break;
                case 1:
                    PlaySfx(0x3DB);
                    break;
                case 2:
                    PlaySfx(0x3DC);
                    break;
                }
            } else if (g_StageId == STAGE_DRE) {
                PlaySfx(0x391);
            } else if (g_StageId == STAGE_RBO2) {
                switch (rand() % 3) {
                case 0:
                    PlaySfx(0x52E);
                    break;
                case 1:
                    PlaySfx(0x52F);
                    break;
                case 2:
                    PlaySfx(0x530);
                    break;
                }
            } else if (TimeAttackController(TIMEATTACK_EVENT_FIRST_MARIA_MEET,
                                            TIMEATTACK_GET_RECORD) != 0) {
                if (rand() & 7) {
                    PlaySfx(0x33B);
                } else {
                    PlaySfx(0x3CE);
                }
            } else {
                PlaySfx(0x33B);
            }
        } else {
            PlaySfx(0x33B);
        }
#endif
        g_GameStep++;
        break;
    case Gameover_5:
        func_800E5358();
        prim = &g_PrimBuf[D_8013640C];
        *(s8*)&prim->p1 -= 1; // TODO maybe it's an s8
        if (prim->p1 != 0) {
            break;
        }
        g_GameStep++;
        break;
    case Gameover_6:
        func_800E5358();
        prim = &g_PrimBuf[D_8013640C];
        var_s0 = prim->r0 + 2;
        if (var_s0 > 0x80) {
            var_s0 = 0x80;
        }

        func_80107250(prim, var_s0);
        if (var_s0 != 0x80) {
            break;
        }

        prim->p1 = 4;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        g_GameStep++;
        break;
    case Gameover_7:
        func_800E5358();
        prim = &g_PrimBuf[D_8013640C];
        if (--prim->p1) {
            break;
        }
        prim->p1 = 4;
        yScroll = prim->v0;
        if (yScroll == 0x60) {
            prim->drawMode = DRAW_COLORS;
            prim->p1 = 0;
            prim->next->p1 = 1;
            yScroll = 0x40;
            g_GameStep++;
        }
        prim->v0 = yScroll + 0x20;
        prim->v1 = yScroll + 0x20;
        prim->u0 = 0;
        prim->u1 = 0xFF;
        prim->u2 = 0;
        prim->v2 = yScroll + 0x40;
        prim->u3 = 0xFF;
        prim->v3 = yScroll + 0x40;
        break;
    case Gameover_8:
        func_800E5358();
        if (g_pads[0].tapped & PAD_START) {
            PlaySfx(0x81);
            g_GameStep++;
            break;
        }
        prim = &g_PrimBuf[D_8013640C];
        if (--prim->p1) {
            break;
        }
        prim = prim->next;
        if (prim->p1--) {
            break;
        }
        g_GameStep++;
        break;
    case Gameover_9:
        func_800E5358();
        if (func_80131F68()) {
            break;
        }
        prim = &g_PrimBuf[D_8013640C];
        var_s0 = prim->r0 - 1;
        func_80107250(prim, var_s0);
        prim = prim->next;
        func_80107250(prim, var_s0);
        prim = prim->next;
        func_80107250(prim, var_s0);
        if (var_s0) {
            break;
        }
        FreePrimitives(D_8013640C);
        g_GameStep++;
        break;
    case Gameover_10:
        g_GameStep++;
        break;
    case Gameover_11:
    case Gameover_11_Alt:
        if (g_GameStep != Gameover_11_Alt && g_StageId == STAGE_ST0) {
            SetGameState(Game_PrologueEnd);
        } else {
            SetGameState(Game_Title);
        }
        break;
    }
}
