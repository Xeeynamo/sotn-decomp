// SPDX-License-Identifier: AGPL-3.0-or-later
//! PSPO=4,p
#include "dra.h"
#include "dra_bss.h"
#include "servant.h"

// BSS
static s32 D_8013640C;
static s32 D_80136410;
static NowLoadingModel g_NowLoadingModel;

#include "../get_lang.h"

// Function used in a good number of places throughout
#ifdef VERSION_PSP
#define LOADFILESIM_PSPALT(F, T) func_psp_090FAB30(F, T, true)
#else
#define LOADFILESIM_PSPALT(F, T) LoadFileSim(F, T)
#endif

void SetGameState(GameState gameState) {
    g_GameState = gameState;
    g_GameStep = 0;
    g_backbufferX = 0;
    g_backbufferY = 0;
}

void func_800E414C(void) {
    RoomTeleport* tele;

    if (!(D_8003C708.flags & FLAG_UNK_40)) {
        return;
    }

    func_8010DFF0(1, 1);
    if (D_8003C708.unk2 &&
        !(PLAYER.posX.i.hi >= 8 && PLAYER.posX.i.hi <= 248)) {
        return;
    }

    switch (D_8003C708.unk2) {
    case 0:
        func_800EA538(1);
        tele = &D_800A245C[D_8003C708.zPriority];
        D_8003C710 = tele->stageId;
        if (g_StageId & STAGE_INVERTEDCASTLE_FLAG) {
            D_8003C710 ^= STAGE_INVERTEDCASTLE_FLAG;
        }
        D_8003C712 = tele->unk6;
        if (g_StageId & STAGE_INVERTEDCASTLE_FLAG) {
            D_8003C712 ^= STAGE_INVERTEDCASTLE_FLAG;
        }
        PlaySfx(0x80);
        D_80097928 = 1;
        if (D_8003C708.flags == FLAG_UNK_40) {
            g_Player.demo_timer = 24;
            g_Player.padSim = PAD_LEFT;
        } else {
            g_Player.demo_timer = 24;
            g_Player.padSim = PAD_RIGHT;
        }
        D_8003C708.unk2++;
        return;
    case 1:
        if (!func_80131F68()) {
            if (g_UseDisk != 0) {
                g_CdStep = CdStep_LoadInit;
                g_LoadFile = CdFile_StageChr | 0x8000;
            }
            g_LoadOvlIdx = D_8003C710;
#ifdef VERSION_PSP
            func_psp_08932AD4(g_LoadOvlIdx);
#endif
            D_8003C708.unk2++;
            return;
        }
        break;
    case 2:
        if (!g_UseDisk) {
            break;
        }
        if (D_8003C708.flags == FLAG_UNK_40 && PLAYER.posX.i.hi < 0x78) {
            func_801073C0();
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_StageChr;
            g_LoadOvlIdx = D_8003C710;
            D_8003C708.unk2++;
        }
        if (D_8003C708.flags == 0x41 && PLAYER.posX.i.hi > 0x88) {
            func_801073C0();
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_StageChr;
            g_LoadOvlIdx = D_8003C710;
            D_8003C708.unk2++;
            return;
        }
        break;
    case 3:
        if (!g_UseDisk) {
            break;
        }
        if (D_8003C708.flags == FLAG_UNK_40 && PLAYER.posX.i.hi > 0x88) {
            func_801073C0();
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_StageChr;
            g_LoadOvlIdx = D_8003C712;
            D_8003C708.unk2 = 2;
        }
        if (D_8003C708.flags == 0x41 && PLAYER.posX.i.hi < 0x78) {
            func_801073C0();
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_StageChr;
            g_LoadOvlIdx = D_8003C712;
            D_8003C708.unk2 = 2;
        }
        break;
    }
}

void ClearBackbuffer(void) { ClearImage(&g_Vram.D_800ACDA0, 0, 0, 0); }

void HandleTitle(void) {
    void (*callback)();

    switch (g_GameStep) {
    case 0:
        ClearBackbuffer();
        InitRenderer();
        func_800EAD7C();
        HideAllBackgroundLayers();
        DestroyAllPrimitives();
        func_800EDAE4();
        ResetEntityArray();
        DestroyEntitiesFromIndex(0);
        func_800EA538(0);
        ResetPendingGfxLoad();
        SetStageDisplayBuffer();
        g_StageId = STAGE_SEL;
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                return;
            }
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_Sel;
        }
#ifdef VERSION_PSP
        D_800974A4 = 0;
#endif
        g_GameStep++;
        break;
#if defined(VERSION_US)
    case 100:
        if (!g_IsUsingCd) {
            RECT rect;
            rect.x = 0;
            rect.y = 0;
            rect.w = 0x280;
            rect.h = 0x100;
            LoadImage(&rect, (u_long*)0x80180014);

            rect.x = 0;
            rect.y = 0x100;
            LoadImage(&rect, (u_long*)0x80180014);

            SetDefDrawEnv(&g_GpuBuffers[0].draw, 0, 0, 0x280, 0x100);
            SetDefDrawEnv(&g_GpuBuffers[1].draw, 0, 0x100, 0x280, 0x100);
            SetDefDispEnv(&g_GpuBuffers[0].disp, 0, 0x100, 0x280, 0x100);
            SetDefDispEnv(&g_GpuBuffers[1].disp, 0, 0, 0x280, 0x100);
            SetDispMask(0);
            D_8013640C = 110;
            g_GameStep++;
        }
        break;
    case 101:
        SetDispMask(1);
        if (D_8013640C == 0 || --D_8013640C == 0) {
            ClearImage(&g_Vram.D_800ACDF0, 0, 0, 0);
            SetStageDisplayBuffer();
            g_StageId = STAGE_SEL;
            if (g_UseDisk) {
                if (g_IsUsingCd) {
                    break;
                }
                g_CdStep = CdStep_LoadInit;
                g_LoadFile = CdFile_Sel;
            }
            g_GameStep = 1;
        }
        break;
#endif
    case 1:
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
        } else {
            if (LoadFileSim(2, SimFileType_System) < 0) {
                break;
            }
            if (LoadFileSim(0, SimFileType_System) < 0) {
                break;
            }
        }
        g_GameStep++;
        break;
    case 2:
#if defined(VERSION_US)
        g_GameStep = 3;
#else
        g_GameStep++;
#endif
        break;
    case 3:
#if defined(VERSION_US)
        g_GameStep = 4;
#else
        g_GameStep++;
#endif
        break;
    case 4:
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_StagePrg;
        }
#if defined(VERSION_US)
        g_GameStep = 5;
#else
        g_GameStep++;
#endif
        break;
    case 5:
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
        } else {
            if (LoadFileSim(0, SimFileType_StagePrg) < 0) {
                break;
            }
        }
        g_GameStep++;
        g_GameEngineStep = Engine_Init;
        break;
    case 6:
#if defined(VERSION_US)
        if (g_GameState == Game_Title) {
            callback = g_api.o.HitDetection;
            callback();
        } else {
            callback = g_api.o.InitRoomEntities;
            callback();
        }
#else
        if (g_GameState == Game_Init) {
            callback = g_api.o.InitRoomEntities;
            callback();
        } else {
            callback = g_api.o.HitDetection;
            callback();
        }
#endif
        break;
    }
}

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

void func_800E4A04(void) { s32 pad[3]; }

s16 g_ButtonMask[] = {
    PAD_SQUARE, PAD_CIRCLE, PAD_CROSS,     PAD_TRIANGLE,
#ifdef VERSION_PSP
    PAD_L1,     PAD_R1,     PAD_SHOULDERS,
#else
    PAD_R2,     PAD_L1,     PAD_R1,    PAD_L2,
#endif
};

#define UPRIGHT_STAGES                                                         \
    STAGE_ARE, STAGE_CAT, STAGE_CEN, STAGE_CHI, STAGE_DAI, STAGE_DRE,          \
        STAGE_LIB, STAGE_NO0, STAGE_NO1, STAGE_NO2, STAGE_NO3, STAGE_NO4,      \
        STAGE_NP3, STAGE_NZ0, STAGE_NZ1, STAGE_TOP, STAGE_WRP
#define REVERSE_STAGES                                                         \
    STAGE_RARE, STAGE_RCAT, STAGE_RCEN, STAGE_RCHI, STAGE_RDAI, STAGE_RLIB,    \
        STAGE_RNO0, STAGE_RNO1, STAGE_RNO2, STAGE_RNO3, STAGE_RNO4,            \
        STAGE_RNZ0, STAGE_RNZ1, STAGE_RTOP, STAGE_RWRP

#define BOSSES                                                                 \
    STAGE_MAR, STAGE_BO0, STAGE_BO1, STAGE_BO2, STAGE_BO3, STAGE_BO4,          \
        STAGE_BO5, STAGE_BO6, STAGE_BO7
#define REVERSE_BOSSES                                                         \
    STAGE_RBO0, STAGE_RBO1, STAGE_RBO2, STAGE_RBO3, STAGE_RBO4, STAGE_RBO5,    \
        STAGE_RBO6, STAGE_RBO7, STAGE_RBO8
#define DEBUG_STAGES                                                           \
    STAGE_MAD, STAGE_HAGI_LOAD, STAGE_IGA_LOAD, STAGE_IWA_LOAD, STAGE_TE1,     \
        STAGE_TE2, STAGE_TE3, STAGE_TE4, STAGE_TE5

static u8 g_StageSelectOrder[] = {
    STAGE_MEMORYCARD, STAGE_ST0,     UPRIGHT_STAGES,
#ifndef VERSION_PSP
    REVERSE_STAGES,   DEBUG_STAGES,  BOSSES,
    REVERSE_BOSSES,   STAGE_TOP_ALT, STAGE_ENDING,
#else
    BOSSES, REVERSE_STAGES, REVERSE_BOSSES,
    0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5 // What are these???
#endif
};

// A value is selected at random on every overlay change (including to/from
// bosses) The selected value + 0x80 is then assigned to
// g_CastleFlags[NO1_WEATHER]
static u8 g_NO1WeatherOptions[] = {
    0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2,
};

static RECT D_800A01C0[] = {
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

#ifdef VERSION_PSP
static char* D_psp_0914C3D8[] = {"alucard ", "richter ", "maria   "};

static u8 game_over_left_it[] = {
#include "../dra/gen/game_over_left_it.h"
};

static u8 game_over_left_sp[] = {
#include "../dra/gen/game_over_left_sp.h"
};

static u8 game_over_left_fr[] = {
#include "../dra/gen/game_over_left_fr.h"
};

static u8 game_over_left_ge[] = {
#include "../dra/gen/game_over_left_ge.h"
};

static u8 game_over_right_it[] = {
#include "../dra/gen/game_over_right_it.h"
};

static u8 game_over_right_sp[] = {
#include "../dra/gen/game_over_right_sp.h"
};

static u8 game_over_right_fr[] = {
#include "../dra/gen/game_over_right_fr.h"
};

static u8 game_over_right_ge[] = {
#include "../dra/gen/game_over_right_ge.h"
};

static u_long* D_psp_09156F10[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x000, 0x200, 128, 128, game_over_left_sp),
    GFX_TERMINATE(),
};

static u_long* D_psp_09156F28[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x000, 0x220, 128, 128, game_over_right_sp),
    GFX_TERMINATE(),
};

// I think these are external to the game.
// could be PSP system or from Dracula X Chronicles
extern s32 D_psp_08C630D4;
extern s32 D_psp_08C630D8;
s16 AllocPrimitives(u8 type, s32 count);
#endif

void HandlePlay(void) {
    s32 i;
    u8* ptr;
    s16 *sx, *sy, *ex, *ey;
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
#ifdef VERSION_PSP
        func_psp_0891B0DC(0, 0x100);
        func_psp_0891B6FC();
#endif
        PlaySfx(SET_UNK_12);
        PlaySfx(SET_UNK_0B);
        MuteSound();
#ifdef VERSION_PSP
        func_psp_0892A620(0, 1);
        func_psp_0892A620(1, 1);
#endif
        if (D_80097C98 & 0x80000000) {
            func_800E4970();
            DemoInit(2);
#ifndef VERSION_PSP
            return;
#else
            if (D_psp_08C630D4 != 0) {
                strcpy(g_Status.saveName, D_psp_0914C3D8[D_psp_08C630D8]);
                g_IsTimeAttackUnlocked = true;
                if (D_psp_08C630D8 == 1) {
                    strcpy(g_Status.saveName, "richter ");
                    g_PlayableCharacter = PLAYER_RICHTER;
                    g_IsTimeAttackUnlocked = true;
                } else if (D_psp_08C630D8 == 2) {
                    strcpy(g_Status.saveName, "maria   ");
                    g_PlayableCharacter = PLAYER_MARIA;
                    g_IsTimeAttackUnlocked = true;
                } else {
                    g_PlayableCharacter = PLAYER_ALUCARD;
                    g_IsTimeAttackUnlocked = false;
                }
            }
            if (D_psp_08C630D4 == 1) {
                DemoInit(1);
            } else if (D_psp_08C630D4 == 2) {
                DemoInit(0);
            } else {
                break;
            }
#endif
        }
        if (D_80097C98 & 0x08000000) {
#ifdef VERSION_PSP
            func_psp_0892A620(0, 1);
            func_psp_0892A620(1, 1);
#endif
            func_800E4970();
            return;
        }
#ifdef VERSION_PSP
        if (D_psp_08C630D4 == 0) {
            g_StageId = func_800F16D0();
        }
#else
        g_StageId = func_800F16D0();
#endif
        g_GpuBuffers[1].draw.isbg = 0;
        g_GpuBuffers[0].draw.isbg = 0;
        HideAllBackgroundLayers();
        func_800EA538(1);
        ResetPendingGfxLoad();
        DestroyEntitiesFromIndex(0);
        DestroyAllPrimitives();
        func_800EDAE4();
        InitFade();
        if (g_CastleFlags[NO1_WEATHER] & 0x80) {
            g_CastleFlags[NO1_WEATHER] =
                g_NO1WeatherOptions[rand() & 0xF] + 0x80;
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
#ifndef VERSION_PSP
        MoveImage(&g_Vram.D_800ACD80, 0, 0x100);
#endif

        g_GpuBuffers[0].draw.isbg = g_GpuBuffers[1].draw.isbg = 1;
        D_8013640C = AllocPrimitives(PRIM_GT4, 16);
        for (prim = &g_PrimBuf[D_8013640C], i = 0, D_80136410 = 0; prim != NULL;
             i++) {
            sx = &D_800A01C0[i].x;
            sy = &D_800A01C0[i].y;
            ex = &D_800A01C0[i].w;
            ey = &D_800A01C0[i].h;
            prim->x0 = *sx;
            prim->y0 = *sy;
            prim->x1 = *ex;
            prim->y1 = *ey;
            prim->x2 =
                0x80 + ((rcos(0x400 - ((i + 0) << 8)) >> 4) * D_80136410 >> 10);
            prim->y2 =
                0x80 - ((rsin(0x400 - ((i + 0) << 8)) >> 4) * D_80136410 >> 10);
            prim->x3 =
                0x80 + ((rcos(0x400 - ((i + 1) << 8)) >> 4) * D_80136410 >> 10);
            prim->y3 =
                0x80 - ((rsin(0x400 - ((i + 1) << 8)) >> 4) * D_80136410 >> 10);
            sx = &D_800A01C0[i].x;
            sy = &D_800A01C0[i].y;
            ex = &D_800A01C0[i].w;
            ey = &D_800A01C0[i].h;
            prim->u0 = *sx;
            prim->v0 = *sy;
            prim->u1 = *ex;
            prim->v1 = *ey;
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
#ifdef VERSION_PSP
        func_psp_08932AD4(g_StageId);
#endif
        break;
    case Play_LoadStageSfx:
        func_800E4A04();
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_StageSfx;
            g_LoadOvlIdx = g_StageId;
        } else {
#ifdef VERSION_PSP
            if (!func_psp_08932B74()) {
                break;
            }
#endif
            if (LOADFILESIM_PSPALT(0, SimFileType_StageChr) < 0) {
                break;
            }
            if (LOADFILESIM_PSPALT(0, SimFileType_Vh) < 0) {
                break;
            }
            if (LOADFILESIM_PSPALT(0, SimFileType_Vb) < 0) {
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
            if (LOADFILESIM_PSPALT(0, SimFileType_StagePrg) < 0) {
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
#ifdef VERSION_PSP
        func_psp_0891B6FC();
        func_psp_0892F83C();
#endif
        g_GameStep++;
        break;
    case Gameover_AllocResources:
        if (g_StageId != STAGE_ST0) {
#ifndef VERSION_PSP
            MoveImage(&g_CurrentBuffer->next->disp.disp, 0x300, 0);
#else
            func_psp_0891B0DC(0x40, 0);
            func_psp_0891AE04();
#endif
            SetGPUBuffRGBZero();
            g_GpuBuffers[1].draw.isbg = 1;
            g_GpuBuffers[0].draw.isbg = 1;
            D_8013640C = AllocPrimitives(PRIM_GT4, 0x103);
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
#ifndef VERSION_PSP
                prim->tpage = (i / 0x40) + 0x10C;
#else
                prim->tpage = (i / 0x40) + 0x101;
#endif
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
            LoadImage(&g_Vram.D_800ACDD8, (u_long*)STAGE_PRG_PTR + 0x2000);
            LoadImage(&g_Vram.D_800ACDB8, (u_long*)STAGE_PRG_PTR + 0x6000);
            StoreImage(&g_Vram.D_800ACDB8, (u_long*)g_Clut[2]);
            LoadImage(&g_Vram.D_800ACDA8, (u_long*)STAGE_PRG_PTR + 0x6800);
            StoreImage(&g_Vram.D_800ACDA8, (u_long*)g_Clut[0]);
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
#ifndef VERSION_PSP
        }
#else
            func_psp_0891CEB8(0, 0xF0);
        }
        D_psp_09156F10[3] =
            (u_long*)GetLang(NULL, game_over_left_fr, game_over_left_sp,
                             game_over_left_ge, game_over_left_it);
        if (D_psp_09156F10[3] != NULL) {
            func_psp_091040A0(D_psp_09156F10);
        }
        D_psp_09156F28[3] =
            (u_long*)GetLang(NULL, game_over_right_fr, game_over_right_sp,
                             game_over_right_ge, game_over_right_it);
        if (D_psp_09156F28[3] != NULL) {
            func_psp_091040A0(D_psp_09156F28);
        }
#endif
#if defined(VERSION_US)
        PlaySfx(MU_LAND_OF_BENEDICTION);
#else
        if (g_PlayableCharacter != PLAYER_ALUCARD) {
            PlaySfx(MU_LAND_OF_BENEDICTION);
        } else {
            if (g_StageId == STAGE_BO6) {
                switch (rand() % 3) {
                case 0:
                    PlaySfx(VO_GAMEOVER_RICHTER_TAUNT_1);
                    break;
                case 1:
                    PlaySfx(VO_GAMEOVER_RICHTER_TAUNT_2);
                    break;
                case 2:
                    PlaySfx(VO_GAMEOVER_RICHTER_TAUNT_3);
                    break;
                }
            } else if (g_StageId == STAGE_DRE) {
                PlaySfx(VO_GAMEOVER_SUCCUBUS_TAUNT);
            } else if (g_StageId == STAGE_RBO2) {
                switch (rand() % 3) {
                case 0:
                    PlaySfx(VO_GAMEOVER_DEATH_TAUNT_1);
                    break;
                case 1:
                    PlaySfx(VO_GAMEOVER_DEATH_TAUNT_2);
                    break;
                case 2:
                    PlaySfx(VO_GAMEOVER_DEATH_TAUNT_3);
                    break;
                }
            } else if (TimeAttackController(TIMEATTACK_EVENT_FIRST_MARIA_MEET,
                                            TIMEATTACK_GET_RECORD) &&
                       (rand() & 7) == 0) {
                PlaySfx(VO_GAMEOVER_MARIA);
            } else {
                PlaySfx(MU_LAND_OF_BENEDICTION);
            }
        }
#endif
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
#ifdef VERSION_PSP
        func_psp_0891AE68();
#endif
        FreePrimitives(D_8013640C);
        g_GameStep++;
        break;
    case Gameover_10:
        g_GameStep++;
        break;
    case Gameover_11:
    case Gameover_11_Alt:
        if (g_GameStep == Gameover_11_Alt) {
#ifdef VERSION_PSP
            func_psp_0892A998();
#endif
            SetGameState(Game_Title);
        } else if (g_StageId == STAGE_ST0) {
            SetGameState(Game_PrologueEnd);
        } else {
            SetGameState(Game_Title);
        }
        break;
    }
}

static RECT D_800A0240 = {0x340, 0x180, 0x40, 0x40};

#ifdef VERSION_PSP
void func_psp_08932CEC(bool, s8);
extern s32 D_psp_08C630D4;
extern u8 D_psp_091463F8;
extern u8 D_psp_09146400;
extern u8 D_psp_09146401;

u8 D_psp_09156F48[] = {
#include "../dra/gen/D_psp_09156F48.h"
};
u16 D_psp_0915AF48[] = {
#include "../dra/gen/D_psp_0915AF48.h"
};

static u8 loading_fr[] = {
#include "../dra/gen/loading_fr.h"
};

static u8 loading_it[] = {
#include "../dra/gen/loading_it.h"
};

static u8 loading_ge[] = {
#include "../dra/gen/loading_ge.h"
};

static u8 loading_sp[] = {
#include "../dra/gen/loading_sp.h"
};

static u_long* D_psp_0915E4E8[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x180, 0x2A0, 128, 128, loading_sp),
    GFX_TERMINATE(),
};

static char* D_psp_0915E500[] = {"alucard ", "richter ", "maria   "};
#endif

void AnimateNowLoading(NowLoadingModel* self, s16 x, s16 y, bool isDone) {
    Primitive* prim;
    s32 i;
    s16 posX;
    s16 posY;
    s16 angle;
    s32 verticalWave;
    s32 horizontalWave;
    s16 sx;
    s16 sy;
    s16 ex;
    s16 ey;

#ifdef VERSION_PSP
    RECT sp48;

    sp48.x = 0x740;
    sp48.y = 0x80;
    sp48.w = 0x40;
    sp48.h = 0x40;
    // These two lines load up the SOTN logo in the lower right.
    // First line loads palettized image, second loads the palette
    LoadImage(&sp48, (u_long*)&D_psp_09156F48);
    func_psp_089264CC(0x81D0, &D_psp_0915AF48, 1);
    D_psp_0915E4E8[3] =
        (u_long*)GetLang(NULL, loading_fr, loading_sp, loading_ge, loading_it);
    if (D_psp_0915E4E8[3] != NULL) {
        func_psp_091040A0(D_psp_0915E4E8);
    }
#endif

    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(PRIM_GT4, NOW_LOADING_PRIM_COUNT + 1);
        if (self->primIndex == -1) {
            return;
        }
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < NOW_LOADING_PRIM_COUNT; i++) {
            self->waveTable[i] = i << 8;
            prim->v0 = prim->v1 = 0xE8;
            prim->v2 = prim->v3 = 0xFF;
            prim->u0 = (i * 8) + 0x80;
            prim->u1 = ((i + 1) * 8) + 0x80;
            if (i == NOW_LOADING_PRIM_COUNT - 1) {
                prim->u1 = 0xFF;
            }
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            prim->tpage = 0x1A;
            prim->clut = PAL_UNK_19F;
            prim->priority = 0x1FE;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
            prim = prim->next;
        }
        prim->v0 = prim->v1 = 0x80;
        prim->v2 = prim->v3 = 0xBF;
        prim->u2 = prim->u0 = 0;
        prim->u3 = prim->u1 = 0x7F;
        prim->y0 = prim->y1 = 0xA0;
        prim->y2 = prim->y3 = 0xDF;
        prim->x2 = prim->x0 = 0x70;
        prim->x3 = prim->x1 = 0xEF;
        prim->tpage = 0x9D;
        prim->clut = 0x1D0;
        prim->priority = 0x1FE;
        prim->drawMode = DRAW_DEFAULT;
        self->x = x;
        self->y = y;
        self->unkC = 0;
        self->verticalWave = 4;
        self->horizontalWave = 4;
        self->unk12 = 0;
        self->speed = 0x20;
        self->step++;
        break;
    case 1:
        if (isDone) {
            FreePrimitives(self->primIndex);
            self->step = 0;
            ClearImage(&D_800A0240, 0, 0, 0);
            return;
        }
        if (g_pads[0].pressed & PAD_UP) {
            self->verticalWave++;
            if (self->verticalWave > 0x40) {
                self->verticalWave = 0x40;
            }
        }
        if (g_pads[0].pressed & PAD_DOWN) {
            self->verticalWave--;
            if (self->verticalWave < -0x40) {
                self->verticalWave = -0x40;
            }
        }
        if (g_pads[0].pressed & PAD_RIGHT) {
            self->horizontalWave++;
            if (self->horizontalWave > 0x40) {
                self->horizontalWave = 0x40;
            }
        }
        if (g_pads[0].pressed & PAD_LEFT) {
            self->horizontalWave--;
            if (self->horizontalWave < -0x40) {
                self->horizontalWave = -0x40;
            }
        }
        break;
    case 2:
    case 3:
        break;
    }
    posX = self->x;
    posY = self->y;
    prim = &g_PrimBuf[self->primIndex];
    verticalWave = self->verticalWave;
    horizontalWave = self->horizontalWave;
    for (i = 0; i < NOW_LOADING_PRIM_COUNT; i++) {
        angle = self->waveTable[i];
        sy = -(rsin(angle) >> 5) * verticalWave / 0x100;
        sx = (rcos(angle) >> 5) * horizontalWave / 0x100;
        angle = self->waveTable[(i + 1) % NOW_LOADING_PRIM_COUNT];
        ey = -(rsin(angle) >> 5) * verticalWave / 0x100;
        ex = (rcos(angle) >> 5) * horizontalWave / 0x100;
        prim->x0 = sx + (posX + prim->u0) - 0x80;
        prim->x1 = ex + (posX + prim->u1) - 0x80;
        prim->x2 = sx + (posX + prim->u2) - 0x80;
        prim->x3 = ex + (posX + prim->u3) - 0x80;
        prim->y0 = posY + sy;
        prim->y1 = posY + ey;
        prim->y2 = posY + 0x18 + sy;
        prim->y3 = posY + 0x18 + ey;
        self->waveTable[i] += self->speed;
        prim = prim->next;
    }
}

void InitializeServant(InitializeMode mode) {
    if (g_Servant != 0) {
        g_ServantDesc.Init(mode);
    }
}

void func_800E6250(void) {
    if (g_Servant != 0) {
        while (LOADFILESIM_PSPALT(g_Servant - 1, SimFileType_FamiliarPrg))
            ;
        while (LOADFILESIM_PSPALT(g_Servant - 1, SimFileType_FamiliarChr))
            ;
        while (LOADFILESIM_PSPALT((g_Servant + 2) * 2 + 0x8000, SimFileType_Vh))
            ;
        while (LOADFILESIM_PSPALT((g_Servant + 2) * 2 + 0x8001, SimFileType_Vb))
            ;
    }
}

s32 func_800E6300(void) {
    s32 i;

    for (i = 0; i < LEN(g_Status.relics); i++) {
        s32 servantId = g_RelicDefs[i].unk0C;
        if (servantId > 0 && g_Status.relics[i] & RELIC_FLAG_ACTIVE) {
            return servantId;
        }
    }
    return 0;
}

void HandleNowLoading(void) {
    void (*pfnWeapon)(s32);
    s32 weaponId, weaponId1, weaponId2;
    NowLoadingModel* nowLoadingModel = &g_NowLoadingModel;

#ifdef VERSION_PSP
#define ANIM_LIMIT Play_PrepareNextStage
#else
#define ANIM_LIMIT Play_Default
#endif
    if (g_GameStep >= ANIM_LIMIT && g_GameStep < Play_16) {
        AnimateNowLoading(nowLoadingModel, 0x40, 0x70, false);
    }
    switch (g_GameStep) {
    case Play_Reset:
        D_8003C730 = 0;
        D_80097924 = -1;
#ifdef VERSION_PSP
        D_8006C378 = -1;
#endif
        ClearBackbuffer();
        SetStageDisplayBuffer();
        g_GameStep++;
        g_GameEngineStep = Engine_Init;
        break;
    case Play_Init:
        if (g_pads[0].repeat & PAD_RIGHT) {
            PlaySfx(SFX_DEBUG_SELECT);
            D_800987B4 += 1;
        }
        if (g_pads[0].repeat & PAD_DOWN) {
            PlaySfx(SFX_DEBUG_SELECT);
            D_800987B4 += 8;
        }
        if (g_pads[0].repeat & PAD_LEFT) {
            PlaySfx(SFX_DEBUG_SELECT);
            D_800987B4 -= 1;
        }
        if (g_pads[0].repeat & PAD_UP) {
            PlaySfx(SFX_DEBUG_SELECT);
            D_800987B4 -= 8;
        }
#ifdef VERSION_PSP
        if (g_pads[0].repeat & PAD_SELECT) {
            g_PlayableCharacter++;
            g_PlayableCharacter %= 3;
        }
        if (D_800987B4 < 0) {
            D_800987B4 = 0x39;
        }
        if (D_800987B4 >= 0x3AU) {
            D_800987B4 = 0;
        }
#else
        if (D_800987B4 >= 0x3F) {
            D_800987B4 -= 0x3F;
        }
        if (D_800987B4 < 0) {
            D_800987B4 += 0x3F;
        }
#endif
        g_StageId = g_StageSelectOrder[D_800987B4];
#ifdef VERSION_PSP
        FntPrint("Player:%s\n", D_psp_0915E500[g_PlayableCharacter]);
#endif
        FntPrint("%02x (%02x)\n", D_800987B4, g_StageId);
        if (g_StageId == STAGE_MEMORYCARD) {
            FntPrint("memory card load\n");
#ifdef VERSION_PSP
        } else if ((g_StageId >= 0xF0) && (g_StageId < 0xFF)) {
            FntPrint("ending(type%d)\n", g_StageId - 0xF0);
#else
        } else if (g_StageId == STAGE_ENDING) {
            FntPrint("ending\n");
#endif
        } else if (g_StageId == STAGE_IWA_LOAD) {
            FntPrint("iwa load\n");
        } else if (g_StageId == STAGE_IGA_LOAD) {
            FntPrint("iga load\n");
        } else if (g_StageId == STAGE_HAGI_LOAD) {
            FntPrint("hagi load\n");
        } else {
            FntPrint("load:c:\\bin\\%s.bin\n", g_StagesLba[g_StageId].ovlName);
        }
        if (g_pads[0].tapped & PAD_START) {
            PlaySfx(SFX_START_SLAM_B);
            if (g_StageId == STAGE_MEMORYCARD) {
                SetGameState(Game_MainMenu);
#ifdef VERSION_PSP
            } else if ((g_StageId >= 0xF0) && (g_StageId < 0xFF)) {
                D_800978B4 = g_StageId - 0xF0;
#else
            } else if (g_StageId == STAGE_ENDING) {
#endif
                SetGameState(Game_Ending);
            } else {
                strcpy(g_Status.saveName, "alucard ");
                g_DemoMode = Demo_None;
                if (g_DebugPlayer != 0) {
#ifdef VERSION_PSP
                    strcpy(
                        g_Status.saveName, D_psp_0915E500[g_PlayableCharacter]);
                    g_IsTimeAttackUnlocked = true;
                    if (g_PlayableCharacter == PLAYER_RICHTER) {
#else
                    if (g_pads[1].pressed & PAD_UP) {
#endif
                        strcpy(g_Status.saveName, "richter ");
                        g_PlayableCharacter = PLAYER_RICHTER;
                        g_IsTimeAttackUnlocked = true;
#ifdef VERSION_PSP
                    } else if (g_PlayableCharacter == PLAYER_MARIA) {
                        strcpy(g_Status.saveName, "maria   ");
                        g_PlayableCharacter = PLAYER_MARIA;
                        g_IsTimeAttackUnlocked = true;
#endif
                    } else {
                        g_PlayableCharacter = PLAYER_ALUCARD;
                        g_IsTimeAttackUnlocked = false;
                    }
#ifdef VERSION_PSP
                    if (D_psp_08C630D4 == 1) {
                        DemoInit(1);
                    } else if (D_psp_08C630D4 == 2) {
                        DemoInit(0);
                    }
#else
                    if (g_pads[1].pressed & PAD_CIRCLE) {
                        DemoInit(1);
                    } else if (g_pads[1].pressed & PAD_CROSS) {
                        DemoInit(0);
                    }
#endif
                }
                g_GameStep++;
            }
        }
        break;
    case Play_PrepareDemo:
#ifdef VERSION_PSP
        if (g_StageId == STAGE_ST0 || g_PlayableCharacter != PLAYER_ALUCARD) {
            if (g_PlayableCharacter == PLAYER_MARIA) {
                func_psp_08932FD4(2);
            } else if (g_StageId == STAGE_ST0) {
                func_psp_08932FD4(3);
            } else {
                func_psp_08932FD4(1);
            }
        } else {
            func_psp_08932FD4(0);
        }
        g_GameStep = Gameover_Init_Alt;
        break;

    case Gameover_Init_Alt:
        if (!func_psp_08933000()) {
            break;
        }
#endif
        D_800978C4 = 0;
        if (g_IsUsingCd) {
            break;
        }
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_GameChr;
        } else {
            if (g_StageId == STAGE_ST0 ||
                g_PlayableCharacter != PLAYER_ALUCARD) {
#ifndef VERSION_PSP
                if (0) { // to align curly braces
#else
                if (g_PlayableCharacter == PLAYER_MARIA) {
                    if (LOADFILESIM_PSPALT(5, SimFileType_System) < 0) {
                        break;
                    }
                    if (LOADFILESIM_PSPALT(0x8014, SimFileType_Vh) < 0) {
                        break;
                    }
                    if (LOADFILESIM_PSPALT(0x8015, SimFileType_Vb) < 0) {
                        break;
                    }
#endif
                } else {
                    if (LOADFILESIM_PSPALT(5, SimFileType_System) < 0) {
                        break;
                    }
                    if (LOADFILESIM_PSPALT(0x8002, SimFileType_Vh) < 0) {
                        break;
                    }
                    if (LOADFILESIM_PSPALT(0x8003, SimFileType_Vb) < 0) {
                        break;
                    }
                    if (g_StageId == STAGE_ST0) {
#ifdef VERSION_PSP
                        // BUGS: wrong signature
                        if (LoadFileSim(0x8004, SimFileType_Vh, true) < 0) {
                            break;
                        }
                        if (LoadFileSim(0x8005, SimFileType_Vb, true) < 0) {
                            break;
                        }
#else
                        if (LoadFileSim(0x8004, SimFileType_Vh) < 0) {
                            break;
                        }
                        if (LoadFileSim(0x8005, SimFileType_Vb) < 0) {
                            break;
                        }
#endif
                    }
                }
            } else {
                if (LOADFILESIM_PSPALT(4, SimFileType_System) < 0) {
                    break;
                }
                if (LOADFILESIM_PSPALT(0x8000, SimFileType_Vh) < 0) {
                    break;
                }
                if (LOADFILESIM_PSPALT(0x8001, SimFileType_Vb) < 0) {
                    break;
                }
            }
        }
#ifdef VERSION_PSP
        g_GameStep = Play_Default;
#else
        nowLoadingModel->step = 0;
        AnimateNowLoading(nowLoadingModel, 64, 112, false);
        g_GameStep++;
#endif
        break;
    case Play_Default:
#ifdef VERSION_PSP
        if (g_StageId == STAGE_ST0 || g_PlayableCharacter != PLAYER_ALUCARD) {
            func_psp_08933130(1);
        } else {
            func_psp_08933130(0);
        }
        g_GameStep = Gameover_AllocResources_Alt;
        break;

    case Gameover_AllocResources_Alt:
        if (!func_psp_0893315C()) {
            break;
        }
#endif
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
        } else {
            if (g_StageId == STAGE_ST0 ||
                g_PlayableCharacter != PLAYER_ALUCARD) {
                if (LOADFILESIM_PSPALT(13, SimFileType_System) < 0) {
                    break;
                }
            } else {
                if (LOADFILESIM_PSPALT(1, SimFileType_System) < 0) {
                    break;
                }
            }
#ifdef VERSION_PSP
            func_psp_0891CEB8(0, 0xFD);
        }
        func_psp_08932AD4(g_StageId);
        g_GameStep = Play_PrepareNextStage;
#else
        }
        g_GameStep++;
#endif
        break;
    case Play_PrepareNextStage:
#ifdef VERSION_PSP
        if (!func_psp_08932B74(g_GameStep, 5)) {
            break;
        }
#endif
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_StageChr;
            g_LoadOvlIdx = g_StageId;
        }
        g_GameStep++;
        break;
    case Play_LoadStageChr:
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
        } else {
            if (LOADFILESIM_PSPALT(0, SimFileType_StageChr) < 0) {
                break;
            }
        }
        g_GameStep++;
        break;
    case Play_WaitStageChr:
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_StageSfx;
        }
        g_GameStep++;
        break;
    case Play_LoadStageSfx:
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
        } else {
            if (LOADFILESIM_PSPALT(0, SimFileType_Vh) < 0) {
                break;
            }
            if (LOADFILESIM_PSPALT(0, SimFileType_Vb) < 0) {
                break;
            }
        }
        g_GameStep++;
        break;
    case Play_WaitStageSfx:
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_StagePrg;
        }
        g_GameStep++;
        break;
    case Play_LoadStagePrg:
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
        } else {
            if (LOADFILESIM_PSPALT(0, SimFileType_StagePrg) < 0) {
                break;
            }
            if (g_StagesLba[g_StageId].seqIdx >= 0 &&
                LoadFileSim(g_StagesLba[g_StageId].seqIdx, 4) < 0) {
                break;
            }
        }
        g_GameStep++;
        break;
    case Play_WaitStagePrg:
        if (g_DemoMode == Demo_None) {
            InitStatsAndGear(0);
        }
        g_Servant = 0;
        g_ServantLoaded = 0;
        g_EquippedWeaponIds[0] = -1;
        g_EquippedWeaponIds[1] = -1;
        if (g_StageId == STAGE_ST0 || g_PlayableCharacter != PLAYER_ALUCARD) {
            g_GameStep = Play_16;
        } else {
#ifdef VERSION_PSP
            if (1) {
#else
            if (g_UseDisk) {
#endif
                g_CdStep = CdStep_LoadInit;
                g_LoadFile = CdFile_Weapon0;
                weaponId =
                    g_EquipDefs[g_Status.equipment[LEFT_HAND_SLOT]].weaponId;
                if (weaponId == 0xFF) {
                    weaponId = 1;
                }
                if (g_Status.equipment[ARMOR_SLOT] == ITEM_AXE_LORD_ARMOR) {
                    weaponId = g_EquipDefs[0xD8].weaponId;
#ifdef VERSION_PSP
                    weaponId1 = weaponId;
                    weaponId2 = weaponId;
                } else {
                    weaponId1 = g_EquipDefs[g_Status.equipment[LEFT_HAND_SLOT]]
                                    .weaponId;
                    if (weaponId1 == 0xFF) {
                        weaponId1 = 1;
                    }
                    weaponId2 = g_EquipDefs[g_Status.equipment[RIGHT_HAND_SLOT]]
                                    .weaponId;
                    weaponId2 = weaponId2 == 0xFF ? 1 : weaponId2;
#endif
                }
                g_EquippedWeaponIds[0] = weaponId;
#ifdef VERSION_PSP
                func_psp_08932CEC(0, weaponId1);
                func_psp_08932CEC(1, weaponId2);
#endif
            }
            g_GameStep++;
        }
        break;
    case Play_Unk11:
#ifdef VERSION_PSP
        if (!func_psp_08932D34(0)) {
            break;
        }
        if (!func_psp_08932D34(1)) {
            break;
        }
#endif
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
            pfnWeapon = D_8017A000.LoadWeaponPalette;
            pfnWeapon(g_EquipDefs[g_EquippedWeaponIds[0]].palette);
        } else {
            weaponId = g_EquipDefs[g_Status.equipment[LEFT_HAND_SLOT]].weaponId;
            if (weaponId == 0xFF) {
                weaponId = 1;
            }
            if (g_Status.equipment[ARMOR_SLOT] == ITEM_AXE_LORD_ARMOR) {
                weaponId = g_EquipDefs[0xD8].weaponId;
            }
            if (LOADFILESIM_PSPALT(weaponId, SimFileType_Weapon0Prg) < 0) {
                break;
            }
            g_EquippedWeaponIds[0] = weaponId;
            pfnWeapon = D_8017A000.LoadWeaponPalette;
            pfnWeapon(g_EquipDefs[g_EquippedWeaponIds[0]].palette);
            weaponId =
                g_EquipDefs[g_Status.equipment[RIGHT_HAND_SLOT]].weaponId;
            if (weaponId == 0xFF) {
                weaponId = 1;
            }
            if (g_Status.equipment[ARMOR_SLOT] == ITEM_AXE_LORD_ARMOR) {
                weaponId = g_EquipDefs[0xD8].weaponId;
            }
            if (LOADFILESIM_PSPALT(weaponId, SimFileType_Weapon1Prg) < 0) {
                break;
            }
            g_EquippedWeaponIds[1] = weaponId;
            pfnWeapon = D_8017D000.LoadWeaponPalette;
            pfnWeapon(g_EquipDefs[g_EquippedWeaponIds[1]].palette);
        }
        g_GameStep++;
        break;
    case Play_Unk12:
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_Weapon1;
            weaponId =
                g_EquipDefs[g_Status.equipment[RIGHT_HAND_SLOT]].weaponId;
            if (weaponId == 0xFF) {
                weaponId = 1;
            }
            if (g_Status.equipment[ARMOR_SLOT] == ITEM_AXE_LORD_ARMOR) {
                weaponId = g_EquipDefs[0xD8].weaponId;
            }
            g_EquippedWeaponIds[1] = weaponId;
        }
        g_GameStep++;
        break;
    case Play_Unk13:
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
            pfnWeapon = D_8017D000.LoadWeaponPalette;
            pfnWeapon(g_EquipDefs[g_EquippedWeaponIds[1]].palette);
        } else {
            if (LOADFILESIM_PSPALT(
                    g_EquippedWeaponIds[0], SimFileType_Weapon0Chr) < 0) {
                break;
            }
            if (LOADFILESIM_PSPALT(
                    g_EquippedWeaponIds[1], SimFileType_Weapon1Chr) < 0) {
                break;
            }
        }
        CheckWeaponCombo();
        g_GameStep++;
        break;
    case Play_Unk14:
        g_Servant = func_800E6300();
        if (g_Servant == 0) {
            g_GameStep += 2;
            break;
        }
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_ServantChr;
            g_LoadOvlIdx = g_Servant - 1;
        }
#ifdef VERSION_PSP
        func_psp_08932E78(g_Servant - 1);
#endif
        g_GameStep++;
        break;
    case Play_Unk15:
#ifdef VERSION_PSP
        if (!func_psp_08932EA4()) {
            break;
        }
#endif
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
        } else {
            func_800E6250();
        }
        g_ServantLoaded = g_Servant;
        g_GameStep++;
        break;
    case Play_16:
        AnimateNowLoading(nowLoadingModel, 64, 112, true);
#ifdef VERSION_PSP
        if (D_8003C730 != 4) {
#else
        if (1) {
#endif
            if ((s32)g_StageId > 0x34) {
                D_8006C374 = g_StagesLba[g_StageId].unk28;
            } else {
                D_8006C374 =
                    g_StagesLba[g_StageId & (u8)~STAGE_INVERTEDCASTLE_FLAG]
                        .unk28;
            }
        }
        if (g_StageId == STAGE_NO3 && g_PlayableCharacter != PLAYER_ALUCARD) {
            D_8006C374 = 0x11;
            g_CastleFlags[PROLOGUE_COMPLETE] = 1;
        }
        D_800978C4 = 1;
        SetGameState(Game_Play);
        break;
    }
}
#ifdef VERSION_PSP
static u8 intro_left_sp[] = {
#include "../dra/gen/intro_left_sp.h"
};

static u8 intro_left_it[] = {
#include "../dra/gen/intro_left_it.h"
};

static u8 intro_left_ge[] = {
#include "../dra/gen/intro_left_ge.h"
};

static u8 intro_left_fr[] = {
#include "../dra/gen/intro_left_fr.h"
};

static u8 intro_right_sp[] = {
#include "../dra/gen/intro_right_sp.h"
};

static u8 intro_right_it[] = {
#include "../dra/gen/intro_right_it.h"
};

static u8 intro_right_ge[] = {
#include "../dra/gen/intro_right_ge.h"
};

static u8 intro_right_fr[] = {
#include "../dra/gen/intro_right_fr.h"
};

static u_long* D_psp_0915FBF8[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x300, 128, 128, intro_left_sp),
    GFX_TERMINATE(),
};
static u_long* D_psp_0915FC10[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(0x100, 0x320, 128, 128, intro_right_sp),
    GFX_TERMINATE(),
};
#endif
void HandleVideoPlayback(void) {
    Primitive* prim;
    Primitive* prim2;
    u8 temp;

    if (!(g_pads[0].tapped & PAD_START) || !g_IsTimeAttackUnlocked) {
        switch (g_GameStep) {
        case 0:
            if (!g_IsUsingCd) {
                func_800EA538(0);
                func_800EA5E4(0x1A);
#ifdef VERSION_PSP
                D_psp_0915FBF8[3] =
                    (u_long*)GetLang(NULL, intro_left_fr, intro_left_sp,
                                     intro_left_ge, intro_left_it);
                if (D_psp_0915FBF8[3] != NULL) {
                    func_psp_091040A0(D_psp_0915FBF8);
                }
                D_psp_0915FC10[3] =
                    (u_long*)GetLang(NULL, intro_right_fr, intro_right_sp,
                                     intro_right_ge, intro_right_it);
                if (D_psp_0915FC10[3] != NULL) {
                    func_psp_091040A0(D_psp_0915FC10);
                }
#endif
                g_CdStep = CdStep_LoadInit;
                g_LoadFile = CdFile_24;
                SetCgiDisplayBuffer(0x140);
                D_8013640C = AllocPrimitives(PRIM_GT4, 2);
                prim = &g_PrimBuf[D_8013640C];
                SetTexturedPrimRect(prim, 44, 96, 232, 32, 0, 0);
                func_801072BC(prim);
                prim->tpage = 0x1C;
                prim->drawMode = DRAW_COLORS;
                prim->p1 = 0x40;
                prim = prim->next;
                SetTexturedPrimRect(prim, 60, 208, 192, 16, 0, 32);
                func_801072DC(prim);
                prim->tpage = 0x1C;
                prim->drawMode = DRAW_HIDE;
                g_GameStep++;
            }
            break;

        case 1:
            prim = &g_PrimBuf[D_8013640C];
            prim->p1--;
            if (prim->p1 == 0) {
                g_GameStep++;
            }
            break;

        case 2:
            prim = &g_PrimBuf[D_8013640C];
            temp = prim->r0 + 1;
            func_80107250(prim, temp);
#ifndef VERSION_PSP
            if (temp == 96) {
                prim2 = prim->next;
#if defined(VERSION_US)
                prim2->drawMode = DRAW_HIDE;
#elif defined(VERSION_HD)
                prim2->drawMode = DRAW_DEFAULT;
#endif
            }
#endif

            if (temp == 128) {
                prim->p1 = 128;
                g_GameStep++;
            }
            break;

        case 3:
            prim = &g_PrimBuf[D_8013640C];
            prim->p1--;
            if (prim->p1 == 0) {
                g_GameStep++;
            }
            break;

        case 4:
            prim = &g_PrimBuf[D_8013640C];
            temp = prim->r0 - 1;
            func_80107250(prim, temp);
            if (temp == 64) {
                prim2 = prim->next;
                prim2->drawMode = DRAW_HIDE;
            }
            if (temp == 0) {
                FreePrimitives(D_8013640C);
                g_GameStep++;
            }
            break;

        case 5:
#ifdef VERSION_PSP
            if (!g_UseDisk || !g_IsUsingCd) {
#else
            if (!g_IsUsingCd) {
#endif
                D_8003C728 = 1;
                g_CurrentStream = 1;
                g_GameStep++;
            }
            break;

        case 6:
            g_api.o.UpdateRoomPosition();
            if (!D_8003C728) {
                goto hack;
            }
            break;
        }
    } else {
    hack:
        func_800E4970();
    }
}

void nullsub_9(void) {}

void HandlePrologueEnd(void) {
    switch (g_GameStep) {
    case 1:
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
        } else {
            if (LoadFileSim(6, SimFileType_System) < 0 ||
                LoadFileSim(7, SimFileType_System) < 0) {
                break;
            }
        }
        if (func_80131F68()) {
            PlaySfx(0x80);
        }
        SetGPUBuffRGBZero();
        g_GameStep++;
        return;
    }
    g_api.o.StageEndCutScene();
}

void MainMenuHandler(void) {
    s32 pad[0x40];

    switch (g_GameStep) {
    case 0:
        g_StageId = STAGE_SEL;
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_StageChr;
            g_LoadOvlIdx = STAGE_SEL;
        }
        g_GameStep++;
        break;
    case 1:
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
        } else {
            if (LoadFileSim(12, SimFileType_System) < 0) {
                break;
            }
        }
        g_GameStep++;
        break;
    case 2:
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_StageSfx;
        }
        g_GameStep++;
        break;
    case 3:
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
        } else {
            if (LoadFileSim(0, SimFileType_Vh) < 0 ||
                LoadFileSim(0, SimFileType_Vb) < 0) {
                break;
            }
        }
        g_GameStep++;
        break;
    case 4:
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_StagePrg;
        }
        g_GameStep++;
        break;
    case 5:
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
        } else {
            if (LoadFileSim(0, SimFileType_StagePrg) < 0) {
                break;
            }
        }
        g_GameStep++;
        g_GameEngineStep = Engine_Init;
        break;
    case 6:
        g_api.o.Update();
        break;
    case 7:
        func_800E4970();
        break;
    }
}

void HandleEnding(void) {
    switch (g_GameStep) {
    case 0:
        DestroyEntitiesFromIndex(0);
        func_800EA538(0);
        ResetPendingGfxLoad();
        DestroyAllPrimitives();
        func_800EDAE4();
        HideAllBackgroundLayers();
        func_800EAD7C();
        ClearBackbuffer();
        SetStageDisplayBuffer();
        g_StageId = STAGE_SEL;
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_31;
        }
        g_GameStep++;
        break;
    case 1:
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
            LoadImage(&g_Vram.D_800ACDE0, (u_long*)STAGE_PRG_PTR);
            LoadImage(&g_Vram.D_800ACDD8, (u_long*)STAGE_PRG_PTR + 0x800);
            LoadImage(&g_Vram.D_800ACDB8, (u_long*)STAGE_PRG_PTR + 0x4800);
            StoreImage(&g_Vram.D_800ACDB8, (u_long*)g_Clut[2]);
            LoadImage(&g_Vram.D_800ACDA8, (u_long*)STAGE_PRG_PTR + 0x5000);
            StoreImage(&g_Vram.D_800ACDA8, (u_long*)g_Clut[0]);
        } else {
            if (LoadFileSim(14, SimFileType_System) < 0) {
                break;
            }
            if (LoadFileSim(15, SimFileType_System) < 0) {
                break;
            }
            if (LoadFileSim(16, SimFileType_System) < 0) {
                break;
            }
            if (LoadFileSim(17, SimFileType_System) < 0) {
                break;
            }
            if (LoadFileSim(4, SimFileType_System) < 0) {
                break;
            }
        }
        LoadClut((u_long*)g_Clut[0], 0x200, 0xF0);
        g_GameStep++;
        break;
    case 2:
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_StagePrg;
        }
        g_GameStep++;
        break;
    case 3:
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
        } else {
            if (LoadFileSim(0, SimFileType_StagePrg) < 0) {
                break;
            }
        }
        g_GameStep++;
        g_GameEngineStep = Engine_Init;
        break;
    case 4:
        g_api.o.UpdateStageEntities();
        break;
    case 5:
        g_GameStep++;
        g_MenuStep = 0;
        break;
    case 6:
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_AlucardPrg;
        }
        g_GameStep++;
        if (D_800978B4 != 3 && D_800978B4 != 5) {
            g_GameStep++;
        }
        break;
    case 7:
        g_api.o.StageEndCutScene();
        break;
    case 8:
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
        } else {
            if (LoadFileSim(4, SimFileType_System) < 0) {
                break;
            }
        }
        g_GameStep++;
        break;
    case 9:
        g_api.o.UpdateStageEntities();
        break;
    case 10:
#if defined(VERSION_US)
        PlaySfx(18);
        PlaySfx(11);
        MuteSound();
#endif
        SetGameState(Game_Init);
        break;
    case 256:
        g_StageId = STAGE_TOP_ALT;
        D_8003C730 = 3;
        func_800E4970();
        break;
    }
}

void UpdateGame(void) {
    switch (g_GameState) {
    case Game_Init:
        HandleTitle();
        break;
    case Game_Title:
        HandleTitle();
        break;
#if defined(VERSION_US)
    case Game_99:
        HandleTitle();
        break;
#endif
    case Game_Play:
        HandlePlay();
        break;
    case Game_GameOver:
        HandleGameOver();
        break;
    case Game_NowLoading:
        HandleNowLoading();
        break;
    case Game_VideoPlayback:
        HandleVideoPlayback();
        break;
    case Game_Unk6:
        nullsub_9();
        break;
    case Game_PrologueEnd:
        HandlePrologueEnd();
        break;
    case Game_MainMenu:
        MainMenuHandler();
        break;
    case Game_Ending:
        HandleEnding();
        break;
    }
}
