#include "dra.h"
#include "sfx.h"

// Game over melting effect
void func_800E5358(void) {
    Primitive* poly = &g_PrimBuf[D_8013640C];
    s32 i;

    for (i = -3; i < 256; i++, poly = poly->next) {
        if (i < 0)
            continue;
        if (poly->y0 > 256)
            continue;
        if (poly->p1 != 0) {
            poly->p1--;
            continue;
        }
        if (poly->p2 < 10 && (rand() & 1)) {
            poly->p2++;
        } else {
            if (!(rand() & 3)) {
                poly->y0++;
                poly->y1++;
            }
            poly->y0++;
            poly->y1++;
        }
        poly->y2++;
        poly->y3++;
    }
}

void func_800E5498(void) {
    POLY_GT4* poly = &g_CurrentBuffer->polyGT4[g_GpuUsage.gt4];
    GpuBuffer* buffer = g_CurrentBuffer;

    setSemiTrans(poly, true);
    setShadeTex(poly, false);
    SetPolyRect(poly, 0, 0, 256, 256);
    setUV4(poly, 16, 16, 24, 16, 16, 24, 24, 24);
    func_801072BC(poly);
    poly->tpage = 0x5A;
    poly->clut = D_8003C3C2[0];
    AddPrim(&buffer->ot[0x1FF], poly);
    g_GpuUsage.gt4++;
}

#if !defined(NON_MATCHING) && defined(VERSION_HD)
INCLUDE_ASM("asm/hd/dra/nonmatchings/gameover", HandleGameOver);
#else
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
        PlaySfx(0x11);
        if (g_StageId != STAGE_ST0) {
            g_GpuBuffers[1].draw.isbg = 0;
            g_GpuBuffers[0].draw.isbg = 0;
        }
        DestroyEntities(0);
        func_800EA538(0);
        func_800EAEEC();
        DestroyAllPrimitives();
        func_800EDAE4();
        HideAllBackgroundLayers();
        func_800EAD7C();
    case Gameover_10:
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

            func_80107360(prim, 0, 96, 0xFF, 0x20, 0, 0);
            func_801072BC(prim);
            prim->tpage = 8;
            prim->blendMode = 0x75;
            prim->p1 = 0x60;
            prim = prim->next;

            func_80107360(prim, 0, 0, 128, 240, 0, 0);
            func_801072DC(prim);
            prim->tpage = 0x8A;
            prim->clut = 0x100;
            prim->blendMode = 4;
            prim = prim->next;

            func_80107360(prim, 128, 0, 128, 240, 0, 0);
            func_801072DC(prim);
            prim->tpage = 0x8B;
            prim->clut = 0x100;
            prim->blendMode = 4;
            prim = prim->next;

            for (i = 0; i < 256; i++) {
                func_80107360(prim, i, 0, 1, 240, i & 63, 0);
                prim->tpage = i / 64 + 0x10C;
                prim->priority = 0x1FF;
                prim->blendMode = 0;
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
        PlaySfx(0x12);
        PlaySfx(0xB);
        g_GameStep++;
        break;
    case Gameover_3:
    case Gameover_3_Alt:
        func_80132760();
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
            LoadImage(&g_Vram.D_800ACDD0, (u32*)0x80180000);
            LoadImage(&g_Vram.D_800ACDD8, (u32*)0x80188000);
            LoadImage(&g_Vram.D_800ACDB8, (u32*)0x80198000);
            StoreImage(&g_Vram.D_800ACDB8, &D_80070BCC);
            LoadImage(&g_Vram.D_800ACDA8, (u32*)0x8019A000);
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
        if (g_CurrentPlayableCharacter == PLAYER_ALUCARD) {
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
        prim->blendMode = 0x31;
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
            prim->blendMode = 4;
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
#endif

#if defined(VERSION_US)
INCLUDE_ASM("asm/us/dra/nonmatchings/gameover", func_800E5D30);
#elif defined(VERSION_HD)
INCLUDE_ASM("asm/hd/dra/nonmatchings/gameover", func_800E5D30);
#endif

void func_800E6218(void) {
    if (D_8006CBC4 != 0) {
        D_80170000();
    }
}

void func_800E6250(void) {
    if (D_8006CBC4 != 0) {
        while (LoadFileSim(D_8006CBC4 - 1, SimFileType_FamiliarPrg) != 0)
            ;
        while (LoadFileSim(D_8006CBC4 - 1, SimFileType_FamiliarChr) != 0)
            ;
        while (LoadFileSim((D_8006CBC4 + 2) * 2 + 0x8000, SimFileType_Vh) != 0)
            ;
        while (LoadFileSim((D_8006CBC4 + 2) * 2 + 0x8001, SimFileType_Vb) != 0)
            ;
    }
}

extern unkStruct_800A872C D_800A872C[];

s32 func_800E6300(void) {
    s32 i;

    for (i = 0; i < 30; i++) {
        if ((D_800A872C[i].unk0 > 0) && (g_Status.relics[i] & 2)) {
            return D_800A872C[i].unk0;
        }
    }
    return 0;
}
