#include "common.h"
#include "dra.h"
#include "objects.h"
#include "sfx.h"

void HandleVideoPlayback(void) {
    Primitive* prim;
    u8 temp;
    s32 temp2;

    if (!(g_pads[0].tapped & PAD_START) || !g_IsTimeAttackUnlocked) {
        switch (g_GameStep) {
        case 0:
            if (!g_IsUsingCd) {
                func_800EA538(0);
                func_800EA5E4(0x1A);
                g_CdStep = CdStep_LoadInit;
                g_LoadFile = CdFile_24;
                SetCgiDisplayBuffer(0x140);
                D_8013640C = AllocPrimitives(PRIM_GT4, 2);
                prim = &g_PrimBuf[D_8013640C];
                SetTexturedPrimRect(prim, 44, 96, 232, 32, 0, 0);
                func_801072BC(prim);
                prim->tpage = 0x1C;
                prim->blendMode = 4;
                prim->p1 = 0x40;
                prim = prim->next;
                SetTexturedPrimRect(prim, 60, 208, 192, 16, 0, 32);
                func_801072DC(prim);
                prim->tpage = 0x1C;
                prim->blendMode = BLEND_VISIBLE;
                g_GameStep++;
                return;
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
            temp2 = D_8013640C;
            prim = &g_PrimBuf[temp2];
            temp = prim->r0 + 1;
            func_80107250(prim, temp);
            if (temp == 96) {
                temp2 = prim->next;
#if defined(VERSION_US)
                ((Primitive*)temp2)->blendMode = BLEND_VISIBLE;
#elif defined(VERSION_HD)
                ((Primitive*)temp2)->blendMode = 0;
#endif
            }
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
                ((Primitive*)prim->next)->blendMode = BLEND_VISIBLE;
            }
            if (temp == 0) {
                FreePrimitives(D_8013640C);
                g_GameStep++;
            }
            break;

        case 5:
            if (!g_IsUsingCd) {
                D_8003C728 = 1;
                D_8003C100 = 1;
                g_GameStep++;
            }
            break;

        case 6:
            g_api.o.unk08();
            if (D_8003C728 == 0) {
                func_800E4970();
            }
            break;
        }

    } else {
        func_800E4970();
    }
}

void nullsub_9(void) {}

void HandlePrologueEnd(void) {
    if (g_GameStep == 1) {
        if ((g_UseDisk && !g_IsUsingCd) ||
            (!g_UseDisk && LoadFileSim(6, SimFileType_System) >= 0 &&
             LoadFileSim(7, SimFileType_System) >= 0)) {
            if (func_80131F68() != 0) {
                PlaySfx(0x80);
            }
            func_800E346C();
            g_GameStep++;
            return;
        }
    }
    g_api.o.unk3C();
}

void HandleMainMenu(void) {
    s32 pad[0x40];

    switch (g_GameStep) {
    case 0:
        g_StageId = STAGE_SEL;
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_StageChr;
            g_mapTilesetId = STAGE_SEL;
        }
        g_GameStep++;
        break;
    case 1:
        if (g_UseDisk && g_IsUsingCd)
            break;

        if (g_UseDisk || LoadFileSim(12, SimFileType_System) >= 0) {
            g_GameStep++;
        }
        break;
    case 2:
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_StageSfx;
        }
        g_GameStep++;
        break;
    case 3:
        if (g_UseDisk && g_IsUsingCd)
            break;

        if (g_UseDisk || LoadFileSim(0, SimFileType_Vh) >= 0 &&
                             LoadFileSim(0, SimFileType_Vb) >= 0) {
            g_GameStep++;
        }
        break;
    case 4:
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_StagePrg;
        }
        g_GameStep++;
        break;
    case 5:
        if (g_UseDisk && g_IsUsingCd)
            break;

        if (g_UseDisk || LoadFileSim(0, SimFileType_StagePrg) >= 0) {
            D_8003C9A4 = 0;
            g_GameStep++;
        }
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
    RECT* temp_s0;
    RECT* temp_s1;
    u32 var_a0;
    u32 var_v0;

    switch (g_GameStep) {
    case 0:
        DestroyEntities(0);
        func_800EA538(0);
        func_800EAEEC();
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
            LoadImage(&g_Vram.D_800ACDE0, 0x80180000);
            LoadImage(&g_Vram.D_800ACDD8, 0x80182000);
            LoadImage(&g_Vram.D_800ACDB8, 0x80192000);
            StoreImage(&g_Vram.D_800ACDB8, &D_80070BCC);
            LoadImage(&g_Vram.D_800ACDA8, 0x80194000);
            StoreImage(&g_Vram.D_800ACDA8, &D_80070BCC - 0x1000);
            LoadClut2(g_Clut, 0x200, 0xF0);
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
            LoadClut2(g_Clut, 0x200, 0xF0);
        }
        g_GameStep++;
        break;
    case 2:
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_StagePrg;
        }
        g_GameStep = 3;
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
        D_8003C9A4 = 0;
        g_GameStep++;
        break;
    case 5:
        g_GameStep = 6;
        D_800978F8 = 0;
        break;
    case 6:
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_AlucardPrg;
        }
        g_GameStep = 7;
        if (D_800978B4 != 3 && D_800978B4 != 5) {
            g_GameStep = 8;
        }
        break;
    case 7:
        g_api.o.unk3C();
        break;
    case 8:
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                return;
            }
        } else {
            if (LoadFileSim(4, SimFileType_System) < 0) {
                break;
            }
        }
        g_GameStep++;
        break;
    case 4:
    case 9:
        g_api.o.unk28();
        break;
    case 10:
#if defined(VERSION_US)
        PlaySfx(18);
        PlaySfx(11);
        func_80132760();
#endif
        SetGameState(Game_Init);
        return;
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
    case Game_Title:
#if defined(VERSION_US)
    case Game_99:
#endif
        HandleTitle();
        break;
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
        HandleMainMenu();
        break;
    case Game_Ending:
        HandleEnding();
        break;
    }
}
