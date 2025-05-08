// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"
#include "dra_bss.h"
#include "lba.h"


void SetGameState(GameState gameState) {
    g_GameState = gameState;
    g_GameStep = 0;
    g_backbufferX = 0;
    g_backbufferY = 0;
}

// TODO split file here

// BSS
extern s32 D_8013640C;
extern s32 D_80136410;

void func_800E414C(void) {
    RoomTeleport* temp_a1;
    s32 temp_a0;

    if (!(D_8003C708.flags & FLAG_UNK_40)) {
        return;
    }

    func_8010DFF0(1, 1);
    if (D_8003C708.unk2 != 0 &&
        !(PLAYER.posX.i.hi >= 8 && PLAYER.posX.i.hi < 249)) {
        return;
    }

    switch (D_8003C708.unk2) {
    case 0:
        func_800EA538(1);
        temp_a1 = &D_800A245C[D_8003C708.zPriority];
        temp_a0 = g_StageId & STAGE_INVERTEDCASTLE_FLAG;
        D_8003C710 = temp_a1->stageId;
        if (temp_a0 != 0) {
            D_8003C710 ^= STAGE_INVERTEDCASTLE_FLAG;
        }
        D_8003C712 = temp_a1->unk6;
        if (temp_a0 != 0) {
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
        if (D_8003C708.flags == 0x41 && PLAYER.posX.i.hi >= 0x89) {
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
        if (D_8003C708.flags == FLAG_UNK_40 && PLAYER.posX.i.hi >= 0x89) {
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
    void (*callback)(void);

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
            LoadImage(&rect, (u32*)0x80180014);

            rect.x = 0;
            rect.y = 0x100;
            LoadImage(&rect, (u32*)0x80180014);

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
        g_GameEngineStep = Engine_Init;
        g_GameStep++;
        break;
    case 6:
#if defined(VERSION_US)
        if (g_GameState == Game_Title) {
            callback = g_api.o.HitDetection;
        } else {
            callback = g_api.o.InitRoomEntities;
        }
#else
        if (g_GameState == Game_Init) {
            callback = g_api.o.InitRoomEntities;
        } else {
            callback = g_api.o.HitDetection;
        }
#endif
        callback();
        break;
    }
}

// This indicates that in HD, this file and the next one (play.c)
// are one continues C file. In US, they are not. rodata for functions
// in the same file has four 00 bytes separating them, and the fact that
// they exist in one version and not the other is indicative of a file split.
#if defined(VERSION_HD)
const int filesplit_42398_rodata = 0x00000000;
#endif
