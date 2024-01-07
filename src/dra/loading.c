#include "dra.h"

u32 D_800A0240[] = {0x01800340, 0x00400040};

void func_800E5D30(void* arg0, u16 arg1, u16 arg2, s32 arg3);
INCLUDE_ASM("dra/nonmatchings/loading", func_800E5D30);

void func_800E6218(s32 arg0) {
    if (g_Servant != 0) {
        D_80170000(arg0);
    }
}

void func_800E6250(void) {
    if (g_Servant != 0) {
        while (LoadFileSim(g_Servant - 1, SimFileType_FamiliarPrg) != 0)
            ;
        while (LoadFileSim(g_Servant - 1, SimFileType_FamiliarChr) != 0)
            ;
        while (LoadFileSim((g_Servant + 2) * 2 + 0x8000, SimFileType_Vh) != 0)
            ;
        while (LoadFileSim((g_Servant + 2) * 2 + 0x8001, SimFileType_Vb) != 0)
            ;
    }
}

s32 func_800E6300(void) {
    s32 i;

    for (i = 0; i < LEN(g_Status.relics); i++) {
        if (g_RelicDefs[i].unk0C > 0 &&
            g_Status.relics[i] & RELIC_FLAG_ACTIVE) {
            return g_RelicDefs[i].unk0C;
        }
    }
    return 0;
}

void HandleNowLoading(void) {
    void (*pfnWeapon)(u8);
    s8 var_a0;
    s32 var_s0;
    s32* var_s1;

    var_s1 = D_80136414;
    if (g_GameStep >= 3 && g_GameStep < 16) {
        func_800E5D30(var_s1, 0x40, 0x70, 0);
    }
    switch (g_GameStep) {
    case 0:
        D_8003C730 = 0;
        D_80097924 = -1;
        ClearBackbuffer();
        SetStageDisplayBuffer();
        D_8003C9A4 = 0;
        g_GameStep++;
        break;
    case 1:
        if (g_pads[0].repeat & PAD_RIGHT) {
            PlaySfx(0x688);
            D_800987B4 += 1;
        }
        if (g_pads[0].repeat & PAD_DOWN) {
            PlaySfx(0x688);
            D_800987B4 += 8;
        }
        if (g_pads[0].repeat & PAD_LEFT) {
            PlaySfx(0x688);
            D_800987B4 -= 1;
        }
        if (g_pads[0].repeat & PAD_UP) {
            PlaySfx(0x688);
            D_800987B4 -= 8;
        }
        if (D_800987B4 >= 0x3F) {
            D_800987B4 -= 0x3F;
        }
        if (D_800987B4 < 0) {
            D_800987B4 += 0x3F;
        }

        g_StageId = g_StageSelectOrder[D_800987B4];
        FntPrint("%02x (%02x)\n", D_800987B4, g_StageId);
        if (g_StageId == STAGE_MEMORYCARD) {
            FntPrint("memory card load\n");
        } else if (g_StageId == STAGE_ENDING) {
            FntPrint("ending\n");
        } else if (g_StageId == STAGE_IWA_LOAD) {
            FntPrint("iwa load\n");
        } else if (g_StageId == STAGE_IGA_LOAD) {
            FntPrint("iga load\n");
        } else if (g_StageId == STAGE_HAGI_LOAD) {
            FntPrint("hagi load\n");
        } else {
            FntPrint("load:c:\\bin\\%s.bin\n", g_StagesLba[g_StageId].ovlName);
        }
        if (!(g_pads[0].tapped & PAD_START)) {
            break;
        }
        PlaySfx(0x63D);
        if (g_StageId == STAGE_MEMORYCARD) {
            SetGameState(Game_MainMenu);
        } else if (g_StageId == STAGE_ENDING) {
            SetGameState(Game_Ending);
        } else {
            __builtin_memcpy(g_Status.saveName, "alucard ", sizeof("alucard "));
            g_DemoMode = Demo_None;
            if (g_DebugPlayer != 0) {
                if (g_pads[1].pressed & PAD_UP) {
                    __builtin_memcpy(
                        g_Status.saveName, "richter ", sizeof("richter "));
                    g_PlayableCharacter = PLAYER_RICHTER;
                    g_IsTimeAttackUnlocked = true;
                } else {
                    g_PlayableCharacter = PLAYER_ALUCARD;
                    g_IsTimeAttackUnlocked = false;
                }
                if (g_pads[1].pressed & PAD_CIRCLE) {
                    DemoInit(1);
                } else if (g_pads[1].pressed & PAD_CROSS) {
                    DemoInit(0);
                }
            }
            g_GameStep++;
        }
        break;
    case 2:
        D_800978C4 = 0;
        if (g_IsUsingCd) {
            break;
        }
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_GameChr;
        } else {
            var_s0 = STAGE_ST0;
            if (g_StageId == var_s0 || g_PlayableCharacter != PLAYER_ALUCARD) {
                if (LoadFileSim(5, SimFileType_System) < 0) {
                    break;
                }
                if (LoadFileSim(0x8002, SimFileType_Vh) < 0) {
                    break;
                }
                if (LoadFileSim(0x8003, SimFileType_Vb) < 0) {
                    break;
                }
                if (g_StageId == var_s0) {
                    if (LoadFileSim(0x8004, SimFileType_Vh) < 0) {
                        break;
                    }
                    if (LoadFileSim(0x8005, SimFileType_Vb) < 0) {
                        break;
                    }
                }
            } else {
                if (LoadFileSim(4, SimFileType_System) < 0) {
                    break;
                }
                if (LoadFileSim(0x8000, SimFileType_Vh) < 0) {
                    break;
                }
                if (LoadFileSim(0x8001, SimFileType_Vb) < 0) {
                    break;
                }
            }
        }
        var_s1[0] = 0;
        func_800E5D30(var_s1, 0x40, 0x70, 0);
        g_GameStep++;
        break;
    case 3:
        if (g_UseDisk) {
            if (!g_IsUsingCd) {
                g_GameStep++;
            }
        } else {
            if (g_StageId == STAGE_ST0 ||
                g_PlayableCharacter != PLAYER_ALUCARD) {
                if (LoadFileSim(13, 0) < 0) {
                    break;
                }
            } else if (LoadFileSim(1, 0) < 0) {
                break;
            }
            g_GameStep++;
        }
        break;
    case 4:
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_StageChr;
            g_LoadOvlIdx = g_StageId;
        }
        g_GameStep++;
        break;
    case 5:
        if (!g_UseDisk) {
            if (LoadFileSim(0, 5) >= 0) {
                g_GameStep++;
            }
        } else if (!g_IsUsingCd) {
            g_GameStep++;
        }
        break;
    case 6:
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_StageSfx;
        }
        g_GameStep++;
        break;
    case 7:
        if (!g_UseDisk) {
            if (LoadFileSim(0, 2) >= 0) {
                if (LoadFileSim(0, 3) >= 0) {
                    g_GameStep++;
                }
            }
        } else if (!g_IsUsingCd) {
            g_GameStep++;
        }
        break;
    case 8:
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_StagePrg;
        }
        g_GameStep++;
        break;
    case 9:
        if (!g_UseDisk) {
            if (LoadFileSim(0, 1) < 0) {
                break;
            }
            var_a0 = g_StagesLba[g_StageId].seqIdx;
            if (var_a0 >= 0 && LoadFileSim(var_a0, 4) < 0) {
                break;
            }
            g_GameStep++;
        } else if (!g_IsUsingCd) {
            g_GameStep++;
        }
        break;
    case 10:
        if (g_DemoMode == Demo_None) {
            InitStatsAndGear(0);
        }
        D_8003C908.D_8003C90C = -1;
        D_8003C908.D_8003C910 = -1;
        g_Servant = 0;
        g_ServantLoaded = 0;
        if (g_StageId == STAGE_ST0 || g_PlayableCharacter != PLAYER_ALUCARD) {
            g_GameStep = 0x10;
        } else {
            if (g_UseDisk) {
                g_CdStep = CdStep_LoadInit;
                g_LoadFile = CdFile_Weapon0;
                var_s0 =
                    g_EquipDefs[g_Status.equipment[LEFT_HAND_SLOT]].weaponId;
                if (var_s0 == 0xFF) {
                    var_s0 = 1;
                }
                if (g_Status.equipment[ARMOR_SLOT] == ITEM_AXE_LORD_ARMOR) {
                    var_s0 = g_EquipDefs[0xD8].weaponId;
                }
                D_8003C908.D_8003C90C = var_s0;
            }
            g_GameStep++;
        }
        break;
    case 11:
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
            pfnWeapon = D_8017A000.LoadWeaponPalette;
            pfnWeapon(g_EquipDefs[D_8003C908.D_8003C90C].palette);
            goto block_102;
        } else {
            var_s0 = g_EquipDefs[g_Status.equipment[LEFT_HAND_SLOT]].weaponId;
            if (var_s0 == 0xFF) {
                var_s0 = 1;
            }
            if (g_Status.equipment[ARMOR_SLOT] == ITEM_AXE_LORD_ARMOR) {
                var_s0 = g_EquipDefs[0xD8].weaponId;
            }
            if (LoadFileSim(var_s0, 7) < 0) {
                break;
            }
            pfnWeapon = D_8017A000.LoadWeaponPalette;
            D_8003C908.D_8003C90C = var_s0;
            pfnWeapon(g_EquipDefs[D_8003C908.D_8003C90C].palette);
            var_s0 = g_EquipDefs[g_Status.equipment[RIGHT_HAND_SLOT]].weaponId;
            if (var_s0 == 0xFF) {
                var_s0 = 1;
            }
            if (g_Status.equipment[ARMOR_SLOT] == ITEM_AXE_LORD_ARMOR) {
                var_s0 = g_EquipDefs[0xD8].weaponId;
            }
            if (LoadFileSim(var_s0, 8) >= 0) {
                D_8003C908.D_8003C910 = var_s0;
                pfnWeapon = D_8017D000.LoadWeaponPalette;
                pfnWeapon(g_EquipDefs[D_8003C908.D_8003C910].palette);
            block_102:
                g_GameStep++;
            }
        }
        break;
    case 12:
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_Weapon1;
            var_s0 = g_EquipDefs[g_Status.equipment[RIGHT_HAND_SLOT]].weaponId;
            if (var_s0 == 0xFF) {
                var_s0 = 1;
            }
            if (g_Status.equipment[ARMOR_SLOT] == ITEM_AXE_LORD_ARMOR) {
                var_s0 = g_EquipDefs[0xD8].weaponId;
            }
            D_8003C908.D_8003C910 = var_s0;
        }
        g_GameStep++;
        break;
    case 13:
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
            pfnWeapon = D_8017D000.LoadWeaponPalette;
            pfnWeapon(g_EquipDefs[D_8003C908.D_8003C910].palette);
        } else if (
            (LoadFileSim(D_8003C908.D_8003C90C, SimFileType_Weapon0Chr) < 0) ||
            (LoadFileSim(D_8003C908.D_8003C910, SimFileType_Weapon1Chr) < 0)) {
            break;
        }
        CheckWeaponCombo();
        g_GameStep++;
        break;
    case 14:
        g_Servant = func_800E6300();
        if (g_Servant == 0) {
            g_GameStep += 2;
        } else {
            if (g_UseDisk) {
                g_CdStep = CdStep_LoadInit;
                g_LoadFile = CdFile_ServantChr;
                g_LoadOvlIdx = g_Servant - 1;
            }
            g_GameStep++;
        }
        break;
    case 15:
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
    case 16:
        func_800E5D30(var_s1, 0x40, 0x70, 1);
        if (((s32)g_StageId) >= STAGE_RNZ1_DEMO) {
            D_8006C374 = g_StagesLba[g_StageId].unk28;
        } else {
            D_8006C374 =
                g_StagesLba[g_StageId & (u8)~STAGE_INVERTEDCASTLE_FLAG].unk28;
        }
        if (g_StageId == STAGE_NO3 && g_PlayableCharacter != PLAYER_ALUCARD) {
            D_8006C374 = 0x11;
            g_CastleFlags[0x34] = 1;
        }
        D_800978C4 = 1;
        SetGameState(Game_Play);
        break;
    }
}

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
            LoadImage(&g_Vram.D_800ACDE0, STAGE_PRG_PTR);
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
        g_MenuStep = 0;
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
        MuteSound();
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
        MainMenuHandler();
        break;
    case Game_Ending:
        HandleEnding();
        break;
    }
}
