#include "dra.h"

// TODO functions probably part of the same file
void SetStageDisplayBuffer(void);
void func_800E5D30(void* arg0, u16 arg1, u16 arg2, s32 arg3);
void func_800E6250(void);
s32 func_800E6300(void);

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

        g_StageId = D_800A0170[D_800987B4];
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
                    g_CurrentPlayableCharacter = PLAYER_RICHTER;
                    g_IsTimeAttackUnlocked = true;
                } else {
                    g_CurrentPlayableCharacter = PLAYER_ALUCARD;
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
            g_LoadFile = 2;
        } else {
            var_s0 = STAGE_ST0;
            if (g_StageId == var_s0 ||
                g_CurrentPlayableCharacter != PLAYER_ALUCARD) {
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
                g_CurrentPlayableCharacter != PLAYER_ALUCARD) {
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
            g_mapTilesetId = g_StageId;
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
        D_8006CBC4 = 0;
        D_80073064 = 0;
        if (g_StageId == STAGE_ST0 ||
            g_CurrentPlayableCharacter != PLAYER_ALUCARD) {
            g_GameStep = 0x10;
        } else {
            if (g_UseDisk) {
                g_CdStep = CdStep_LoadInit;
                g_LoadFile = CdFile_Weapon0;
                var_s0 = D_800A4B04[g_Status.equipment[0]].weaponId;
                if (var_s0 == 0xFF) {
                    var_s0 = 1;
                }
                if (g_Status.equipment[3] == 0x19) {
                    var_s0 = D_800A4B04[0xD8].weaponId;
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
            pfnWeapon = D_8017A000.func_8017A01C;
            pfnWeapon(D_800A4B04[D_8003C908.D_8003C90C].unk10);
            goto block_102;
        } else {
            var_s0 = D_800A4B04[g_Status.equipment[0]].weaponId;
            if (var_s0 == 0xFF) {
                var_s0 = 1;
            }
            if (g_Status.equipment[3] == 0x19) {
                var_s0 = D_800A4B04[0xD8].weaponId;
            }
            if (LoadFileSim(var_s0, 7) < 0) {
                break;
            }
            pfnWeapon = D_8017A000.func_8017A01C;
            D_8003C908.D_8003C90C = var_s0;
            pfnWeapon(D_800A4B04[D_8003C908.D_8003C90C].unk10);
            var_s0 = D_800A4B04[g_Status.equipment[1]].weaponId;
            if (var_s0 == 0xFF) {
                var_s0 = 1;
            }
            if (g_Status.equipment[3] == 0x19) {
                var_s0 = D_800A4B04[0xD8].weaponId;
            }
            if (LoadFileSim(var_s0, 8) >= 0) {
                D_8003C908.D_8003C910 = var_s0;
                pfnWeapon = D_8017D000.func_8017A01C;
                pfnWeapon(D_800A4B04[D_8003C908.D_8003C910].unk10);
            block_102:
                g_GameStep++;
            }
        }
        break;
    case 12:
        if (g_UseDisk) {
            g_CdStep = CdStep_LoadInit;
            g_LoadFile = CdFile_Weapon1;
            var_s0 = D_800A4B04[g_Status.equipment[1]].weaponId;
            if (var_s0 == 0xFF) {
                var_s0 = 1;
            }
            if (g_Status.equipment[3] == 0x19) {
                var_s0 = D_800A4B04[0xD8].weaponId;
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
            pfnWeapon = D_8017D000.func_8017A01C;
            pfnWeapon(D_800A4B04[D_8003C908.D_8003C910].unk10);
        } else if (
            (LoadFileSim(D_8003C908.D_8003C90C, SimFileType_Weapon0Chr) < 0) ||
            (LoadFileSim(D_8003C908.D_8003C910, SimFileType_Weapon1Chr) < 0)) {
            break;
        }
        CheckWeaponCombo();
        g_GameStep++;
        break;
    case 14:
        D_8006CBC4 = func_800E6300();
        if (D_8006CBC4 == 0) {
            g_GameStep += 2;
        } else {
            if (g_UseDisk) {
                g_CdStep = CdStep_LoadInit;
                g_LoadFile = CdFile_ServantChr;
                g_mapTilesetId = D_8006CBC4 - 1;
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
        D_80073064 = D_8006CBC4;
        g_GameStep++;
        break;
    case 16:
        func_800E5D30(var_s1, 0x40, 0x70, 1);
        if (((s32)g_StageId) >= STAGE_RNZ1) {
            D_8006C374 = g_StagesLba[g_StageId].unk28;
        } else {
            D_8006C374 =
                g_StagesLba[g_StageId & (u8)~STAGE_INVERTEDCASTLE_FLAG].unk28;
        }
        if (g_StageId == STAGE_NO3 &&
            g_CurrentPlayableCharacter != PLAYER_ALUCARD) {
            D_8006C374 = 0x11;
            D_8003BDEC[0x34] = 1;
        }
        D_800978C4 = 1;
        SetGameState(Game_Play);
        break;
    }
}

const u32 rodataPadding_800DB7E4 = 0;
