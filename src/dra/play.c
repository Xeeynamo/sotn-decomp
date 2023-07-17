#include "dra.h"
#include "sfx.h"

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
    func_800EAEEC();
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
            for (i = 0; i < LEN(D_8003BDEC); i++) {
                D_8003BDEC[i] = 0;
            }
            D_8003BDEC[0xB9] = 1;
            D_8003BDEC[0x9B] = 1;
            if (g_CurrentPlayableCharacter != 0) {
                D_8003BDEC[0x35] = 1;
                D_8003BDEC[0x62] = 1;
                D_8003BDEC[0x63] = 1;
                D_8003BDEC[0x85] = 1;
                D_8003BDEC[0x95] = 1;
                D_8003BDEC[0x96] = 1;
            }

            for (i = 0, ptr = &g_MenuNavigation; i < sizeof(MenuNavigation);
                 i++) {
                *ptr++ = 0;
            }

            for (i = 0; i < BUTTON_COUNT; i++) {
                g_Settings.buttonConfig[i] = i;
                g_Settings.buttonMask[i] = D_800A0160[i];
            }
            for (i = 0; i < LEN(g_Settings.cloakExteriorColors) +
                                LEN(g_Settings.cloakLiningColors);
                 i++) {
                g_Settings.cloakExteriorColors[i] = 0;
            }

            g_Settings.windowColors[0] = 0;
            g_Settings.windowColors[1] = 0;
            g_Settings.windowColors[2] = 8;
            g_Settings.isCloakLingingReversed = 0;
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
        func_800EAF28(ANIMSET_DRA(1));
        func_800EAF28(ANIMSET_OVL(0));
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
            g_blinkTimer = 0;
            D_8003C8C4 = 0;
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
        func_800EAEEC();
        DestroyEntities(0);
        DestroyAllPrimitives();
        func_800EDAE4();
        func_801024DC();
        if (D_8003BDEC[0x13] & 0x80) {
            D_8003BDEC[0x13] = D_800A01B0[rand() & 0xF] + 0x80;
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
                g_mapTilesetId = g_StageId;
            }
            if (D_8006C374 == 0x07) {
                if (g_IsUsingCd) {
                    break;
                }
                g_CdStep = CdStep_LoadInit;
                g_LoadFile = CdFile_StageChr;
                g_mapTilesetId = g_StageId;
            }
            if (D_8006C374 == 0x3C) {
                if (g_IsUsingCd) {
                    break;
                }
                g_CdStep = CdStep_LoadInit;
                g_LoadFile = CdFile_StageChr;
                g_mapTilesetId = 9;
            }
            if (D_8006C374 == 0x25) {
                if (g_IsUsingCd) {
                    break;
                }
                g_CdStep = CdStep_LoadInit;
                g_LoadFile = CdFile_StageChr;
                g_mapTilesetId = 0x2B;
            }
            if (D_8006C374 == 0x26) {
                if (g_IsUsingCd) {
                    break;
                }
                g_CdStep = CdStep_LoadInit;
                g_LoadFile = CdFile_StageChr;
                g_mapTilesetId = 0xB;
            }
            if (D_8006C374 == 0x27) {
                if (g_IsUsingCd) {
                    break;
                }
                g_CdStep = CdStep_LoadInit;
                g_LoadFile = CdFile_StageChr;
                g_mapTilesetId = 2;
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
                0x80 +
                (((rcos(0x400 - ((i + 0) << 8)) >> 4) * D_80136410) >> 10);
            prim->y2 =
                0x80 -
                (((rsin(0x400 - ((i + 0) << 8)) >> 4) * D_80136410) >> 10);
            prim->x3 =
                0x80 +
                (((rcos(0x400 - ((i + 1) << 8)) >> 4) * D_80136410) >> 10);
            prim->y3 =
                0x80 -
                (((rsin(0x400 - ((i + 1) << 8)) >> 4) * D_80136410) >> 10);
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
            g_mapTilesetId = g_StageId;
        } else {
            if (func_800E81FC(0, SimFileType_StageChr) < 0 ||
                func_800E81FC(0, SimFileType_Vh) < 0 ||
                func_800E81FC(0, SimFileType_Vb) < 0) {
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
            if (func_800E81FC(0, SimFileType_StagePrg) < 0) {
                break;
            }
            if (g_StagesLba[g_StageId].seqIdx >= 0) {
                if (func_800E81FC(
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
