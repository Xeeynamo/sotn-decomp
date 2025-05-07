// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"

extern s32 D_8013640C;
extern s32 D_8C630D4;
extern s32 D_8C630D8;
extern u32 D_8D35C40;
extern u32 D_8D45C40;
extern u32 D_8D47C40;
extern u8 D_psp_0914C318[];
extern RECT D_psp_0914C328[];
extern char D_psp_0914C3B8[];
extern char D_psp_0914C3C8[];
extern char* D_psp_0914C3D8[];
extern s32 D_psp_0914C3E8;
extern s32 D_psp_0914D850;
extern s32 D_psp_0914EEB0;
extern s32 D_psp_09150280;
extern s32 D_psp_091518A8;
extern s32 D_psp_09152B20;
extern s32 D_psp_09154220;
extern s32 D_psp_09155948;
extern s32 D_psp_09156F10;
extern s32 D_psp_09156F1C;
extern s32 D_psp_09156F28;
extern s32 D_psp_09156F34;
extern s32 D_psp_091CE348;

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

void func_800E4A04(void) {}

void HandlePlay(void) {
    s32 i;
    u8* ptr;
    Primitive* prim;

    switch (g_GameStep) {
    case Play_Reset:
        g_GameEngineStep = Engine_Init;
        D_8003C738 = 0;
        if (D_8003C730 == 0) {
            for (i = 0; i < LEN(g_CastleFlags); i++) {
                g_CastleFlags[i] = 0;
            }
            // The Elevator in Reverse Colosseum and the Hidden Stairs in
            // Reverse Keep are always activated
            g_CastleFlags[RARE_ELEVATOR_ACTIVATED] = 1;
            g_CastleFlags[RTOP_SECRET_STAIRS] = 1;
            if (g_PlayableCharacter != PLAYER_ALUCARD) {
                g_CastleFlags[IVE_BEEN_ROBBED] = 1;
                g_CastleFlags[MET_MARIA_AFTER_HIPPOGRYPH] = 1;
                g_CastleFlags[MET_MARIA_IN_DAI] = 1;
                g_CastleFlags[MET_MARIA_IN_NZ0] = 1;
                g_CastleFlags[SHAFT_ORB_DEFEATED] = 1;
                g_CastleFlags[INVERTED_CASTLE_UNLOCKED] = 1;
            }

            for (i = 0, ptr = (u8*)&g_MenuNavigation;
                 i < sizeof(MenuNavigation); i++) {
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
        ClearStatBuffs();
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
        func_891B0DC(0, 0x100);
        func_891B6FC();
        PlaySfx(SET_UNK_12);
        PlaySfx(SET_UNK_0B);
        MuteSound();
        func_892A620(0, 1);
        func_892A620(1, 1);
        if (D_80097C98 & 0x80000000) {
            func_800E4970();
            DemoInit(2);
            if (D_8C630D4 != 0) {
                STRCPY(g_Status.saveName, D_psp_0914C3D8[D_8C630D8]);
                g_IsTimeAttackUnlocked = true;
                if (D_8C630D8 == 1) {
                    STRCPY(g_Status.saveName, D_psp_0914C3B8);
                    g_PlayableCharacter = PLAYER_RICHTER;
                    g_IsTimeAttackUnlocked = true;
                } else if (D_8C630D8 == 2) {
                    STRCPY(g_Status.saveName, D_psp_0914C3C8);
                    g_PlayableCharacter = PLAYER_MARIA;
                    g_IsTimeAttackUnlocked = true;
                } else {
                    g_PlayableCharacter = PLAYER_ALUCARD;
                    g_IsTimeAttackUnlocked = false;
                }
            }
            if (D_8C630D4 == 1) {
                DemoInit(1);
            } else if (D_8C630D4 == 2) {
                DemoInit(0);
            } else {
                break;
            }
        }
        if (D_80097C98 & 0x08000000) {
            func_892A620(0, 1);
            func_892A620(1, 1);
            func_800E4970();
            return;
        }
        if (D_8C630D4 == 0) {
            g_StageId = func_800F16D0();
        }
        g_GpuBuffers[1].draw.isbg = 0;
        g_GpuBuffers[0].draw.isbg = 0;
        HideAllBackgroundLayers();
        func_800EA538(1);
        ResetPendingGfxLoad();
        DestroyEntitiesFromIndex(0);
        DestroyAllPrimitives();
        func_800EDAE4();
        func_801024DC();
        if (g_CastleFlags[NO1_WEATHER] & 0x80) {
            g_CastleFlags[NO1_WEATHER] = D_psp_0914C318[rand() & 0xF] + 0x80;
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
                g_LoadOvlIdx = STAGE_NO4;
            }
            if (D_8006C374 == 0x25) {
                if (g_IsUsingCd) {
                    break;
                }
                g_CdStep = CdStep_LoadInit;
                g_LoadFile = CdFile_StageChr;
                g_LoadOvlIdx = STAGE_RTOP;
            }
            if (D_8006C374 == 0x26) {
                if (g_IsUsingCd) {
                    break;
                }
                g_CdStep = CdStep_LoadInit;
                g_LoadFile = CdFile_StageChr;
                g_LoadOvlIdx = STAGE_TOP;
            }
            if (D_8006C374 == 0x27) {
                if (g_IsUsingCd) {
                    break;
                }
                g_CdStep = CdStep_LoadInit;
                g_LoadFile = CdFile_StageChr;
                g_LoadOvlIdx = STAGE_LIB;
            }
        }
        g_GpuBuffers[1].draw.isbg = 1;
        g_GpuBuffers[0].draw.isbg = 1;
        D_8013640C = (s16)AllocPrimitives(PRIM_GT4, 16);
        prim = &g_PrimBuf[D_8013640C];
        for (i = 0, D_psp_091CE348 = 0; prim != NULL; i++) {
            prim->x0 = D_psp_0914C328[i].x;
            prim->y0 = D_psp_0914C328[i].y;
            prim->x1 = D_psp_0914C328[i].w;
            prim->y1 = D_psp_0914C328[i].h;
            prim->x2 =
                0x80 +
                ((rcos(0x400 - ((i + 0) << 8)) >> 4) * D_psp_091CE348 >> 10);
            prim->y2 =
                0x80 -
                ((rsin(0x400 - ((i + 0) << 8)) >> 4) * D_psp_091CE348 >> 10);
            prim->x3 =
                0x80 +
                ((rcos(0x400 - ((i + 1) << 8)) >> 4) * D_psp_091CE348 >> 10);
            prim->y3 =
                0x80 -
                ((rsin(0x400 - ((i + 1) << 8)) >> 4) * D_psp_091CE348 >> 10);
            prim->u0 = D_psp_0914C328[i].x;
            prim->v0 = D_psp_0914C328[i].y;
            prim->u1 = D_psp_0914C328[i].w;
            prim->v1 = D_psp_0914C328[i].h;
            prim->u2 = 0x80;
            prim->v2 = 0x80;
            prim->u3 = 0x80;
            prim->v3 = 0x80;
            prim->tpage = 0x110;
            prim = prim->next;
        }
        SetGPUBuffRGBZero();
        g_GameStep++;
        break;
    case Play_WaitStageChr:
        func_800E4A04();
        if (g_IsUsingCd) {
            break;
        }
        g_GameStep++;
        func_8932AD4(g_StageId);
        break;
    case Play_LoadStageSfx:
        func_800E4A04();
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_StageSfx;
            g_LoadOvlIdx = g_StageId;
        } else {
            if (!func_8932B74()) {
                break;
            }
            if (func_psp_090FAB30(0, SimFileType_StageChr, true) < 0) {
                break;
            }
            if (func_psp_090FAB30(0, SimFileType_Vh, true) < 0) {
                break;
            }
            if (func_psp_090FAB30(0, SimFileType_Vb, true) < 0) {
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
            if (func_psp_090FAB30(0, SimFileType_StagePrg, true) < 0) {
                break;
            }
            if (g_StagesLba[g_StageId].seqIdx >= 0 &&
                LoadFileSim(g_StagesLba[g_StageId].seqIdx, SimFileType_Seq) <
                    0) {
                break;
            }
        }
        FreePrimitives(D_8013640C);
        if (D_80097C98 == 4 || D_80097C98 == 5 || D_80097C98 == 6) {
            func_800EA5AC(0xFFFF, 0xFF, 0xFF, 0xFF);
        }
        g_GameStep = Play_Init;
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

    for (i = -3; i < 0x100; i++, prim = prim->next) {
        if (i < 0) {
            continue;
        }
        if (prim->y0 > 0x100) {
            continue;
        }
        if (prim->p1) {
            prim->p1--;
            continue;
        }
        if (prim->p2 < 10 && (rand() & 1)) {
            prim->p2++;
        } else {
            if ((rand() & 3) == 0) {
                prim->y0++;
                prim->y1++;
            }
            prim->y0++;
            prim->y1++;
        }
        prim->y2++;
        prim->y3++;
    }
}

void func_800E5498(void) {
    OT_TYPE* ot = g_CurrentBuffer->ot;
    POLY_GT4* poly = &g_CurrentBuffer->polyGT4[g_GpuUsage.gt4];

    setSemiTrans(poly, true);
    setShadeTex(poly, false);
    SetPrimRect((Primitive*)poly, 0, 0, 256, 256);
    setUV4(poly, 16, 16, 24, 16, 16, 24, 24, 24);
    func_801072BC(poly);
    poly->tpage = 0x5A;
    poly->clut = g_ClutIds[0x15F];
    AddPrim(&ot[0x1FF], poly);
    g_GpuUsage.gt4++;
}

void HandleGameOver(void) {
    Primitive* prim;
    s32 i;
    u8 temp;
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
        func_891B6FC();
        func_892F83C();
        g_GameStep++;
        break;
    case Gameover_AllocResources:
        if (g_StageId != STAGE_ST0) {
            func_891B0DC(0x40, 0);
            func_891AE04();
            SetGPUBuffRGBZero();
            g_GpuBuffers[1].draw.isbg = 1;
            g_GpuBuffers[0].draw.isbg = 1;
            D_8013640C = (s16)AllocPrimitives(PRIM_GT4, 0x103);
            prim = &g_PrimBuf[D_8013640C];

            SetTexturedPrimRect(prim, 0, 0x60, 0xFF, 0x20, 0, 0);
            func_801072BC(prim);
            prim->tpage = 8;
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_COLORS | DRAW_TRANSP;
            prim->p1 = 0x60;
            prim = prim->next;

            SetTexturedPrimRect(prim, 0, 0, 0x80, 0xF0, 0, 0);
            func_801072DC(prim);
            prim->tpage = 0x8A;
            prim->clut = 0x100;
            prim->drawMode = DRAW_COLORS;
            prim = prim->next;

            SetTexturedPrimRect(prim, 0x80, 0, 0x80, 0xF0, 0, 0);
            func_801072DC(prim);
            prim->tpage = 0x8B;
            prim->clut = 0x100;
            prim->drawMode = DRAW_COLORS;
            prim = prim->next;

            for (i = 0; i < 0x100; i++) {
                SetTexturedPrimRect(prim, i, 0, 1, 0xF0, i & 0x3F, 0);
                prim->tpage = (i / 0x40) + 0x101;
                prim->priority = 0x1FF;
                prim->drawMode = DRAW_DEFAULT;
                prim->p1 = (rand() & 0x1F) + 1;
                prim = prim->next;
            }
        }
    case Gameover_AllocResources_Alt:
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
        if (g_GameStep == Gameover_3_Alt) {
            g_GameStep = Gameover_11_Alt;
            break;
        }
        if (g_StageId == STAGE_ST0) {
            g_GameStep = Gameover_11;
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
            LoadImage(&g_Vram.D_800ACDD8, (u_long*)&D_8D35C40);
            LoadImage(&g_Vram.D_800ACDB8, (u_long*)&D_8D45C40);
            StoreImage(&g_Vram.D_800ACDB8, (u_long*)&g_Clut[0x2000]);
            LoadImage(&g_Vram.D_800ACDA8, (u_long*)&D_8D47C40);
            StoreImage(&g_Vram.D_800ACDA8, (u_long*)g_Clut);
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
            func_891CEB8(0, 0xF0);
        }
        D_psp_09156F1C = func_psp_090F6368(0, &D_psp_0914EEB0, &D_psp_0914D850,
                                           &D_psp_09150280, &D_psp_0914C3E8);
        if (D_psp_09156F1C != 0) {
            func_psp_091040A0(&D_psp_09156F10);
        }
        D_psp_09156F34 = func_psp_090F6368(0, &D_psp_09154220, &D_psp_09152B20,
                                           &D_psp_09155948, &D_psp_091518A8);
        if (D_psp_09156F34 != 0) {
            func_psp_091040A0(&D_psp_09156F28);
        }
        if (g_PlayableCharacter != PLAYER_ALUCARD) {
            PlaySfx(0x33B);
        } else {
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
                                            TIMEATTACK_GET_RECORD) &&
                       (rand() & 7) == 0) {
                PlaySfx(0x3CE);
            } else {
                PlaySfx(0x33B);
            }
        }
        g_GameStep++;
        break;
    case Gameover_5:
        func_800E5358();
        prim = &g_PrimBuf[D_8013640C];
        prim->p1--;
        if (prim->p1) {
            break;
        }
        g_GameStep++;
        break;
    case Gameover_6:
        func_800E5358();
        prim = &g_PrimBuf[D_8013640C];
        temp = prim->r0 + 2;
        if (temp > 0x80) {
            temp = 0x80;
        }
        func_80107250(prim, temp);
        if (temp != 0x80) {
            break;
        }
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        prim->p1 = 4;
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
            yScroll = 0x40;
            prim->drawMode = DRAW_COLORS;
            prim->p1 = 0;
            prim->next->p1 = 1;
            g_GameStep++;
        }
        prim->u0 = 0;
        prim->v0 = yScroll + 0x20;
        prim->u1 = 0xFF;
        prim->v1 = yScroll + 0x20;
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
        temp = prim->r0 - 1;
        func_80107250(prim, temp);
        prim = prim->next;
        func_80107250(prim, temp);
        prim = prim->next;
        func_80107250(prim, temp);
        if (temp) {
            break;
        }
        func_891AE68();
        FreePrimitives(D_8013640C);
        g_GameStep++;
        break;
    case Gameover_10:
        g_GameStep++;
        break;
    case Gameover_11:
    case Gameover_11_Alt:
        if (g_GameStep == Gameover_11_Alt) {
            func_892A998();
            SetGameState(Game_Title);
        } else if (g_StageId == STAGE_ST0) {
            SetGameState(Game_PrologueEnd);
        } else {
            SetGameState(Game_Title);
        }
        break;
    }
}
