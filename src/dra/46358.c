#include "dra.h"

// TODO functions probably part of the same file
void func_800E3574(void);
void func_800E5D30(void* arg0, u16 arg1, u16 arg2, s32 arg3);
void func_800E6250(void);
s32 func_800E6300(void);

void func_800E6358(void) {
    void (*pfnWeapon)(u8);
    s8 var_a0;
    s32 var_s0;
    s32* var_s1;

    var_s1 = D_80136414;
    if (D_80073060 >= 3 && D_80073060 < 16) {
        func_800E5D30(var_s1, 0x40, 0x70, 0);
    }
    switch (D_80073060) {
    case 0:
        D_8003C730 = 0;
        D_80097924 = -1;
        ClearBackbuffer();
        func_800E3574();
        D_8003C9A4 = 0;
        D_80073060++;
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
            FntPrint("load:c:\\bin\\%s.bin\n", D_800A3C40[g_StageId].ovlName);
        }
        if (!(g_pads[0].tapped & 0x0800)) {
            break;
        }
        PlaySfx(0x63D);
        if (g_StageId == STAGE_MEMORYCARD) {
            func_800E4124(8);
        } else if (g_StageId == STAGE_ENDING) {
            func_800E4124(9);
        } else {
            __builtin_memcpy(g_Status.saveName, "alucard ", sizeof("alucard "));
            D_80097914 = 0;
            if (D_80098850 != 0) {
                if (g_pads[1].pressed & PAD_UP) {
                    __builtin_memcpy(g_Status.saveName, "richter ",
                                     sizeof("richter "));
                    g_CurrentPlayableCharacter = PLAYER_RICHTER;
                    g_IsTimeAttackUnlocked = true;
                } else {
                    g_CurrentPlayableCharacter = PLAYER_ALUCARD;
                    g_IsTimeAttackUnlocked = false;
                }
                if (g_pads[1].pressed & PAD_CIRCLE) {
                    func_800F0578(1);
                } else if (g_pads[1].pressed & PAD_CROSS) {
                    func_800F0578(0);
                }
            }
            D_80073060++;
        }
        break;
    case 2:
        D_800978C4 = 0;
        if (D_8006C3B0 != 0) {
            break;
        }
        if (g_UseDisk) {
            D_8006C398 = 1;
            D_8006BAFC = 2;
        } else {
            var_s0 = STAGE_ST0;
            if (g_StageId == var_s0 ||
                g_CurrentPlayableCharacter != PLAYER_ALUCARD) {
                if (func_800E81FC(5, FILETYPE_SYSTEM) < 0) {
                    break;
                }
                if (func_800E81FC(0x8002, FILETYPE_VH) < 0) {
                    break;
                }
                if (func_800E81FC(0x8003, FILETYPE_VB) < 0) {
                    break;
                }
                if (g_StageId == var_s0) {
                    if (func_800E81FC(0x8004, FILETYPE_VH) < 0) {
                        break;
                    }
                    if (func_800E81FC(0x8005, FILETYPE_VB) < 0) {
                        break;
                    }
                }
            } else {
                if (func_800E81FC(4, FILETYPE_SYSTEM) < 0) {
                    break;
                }
                if (func_800E81FC(0x8000, FILETYPE_VH) < 0) {
                    break;
                }
                if (func_800E81FC(0x8001, FILETYPE_VB) < 0) {
                    break;
                }
            }
        }
        var_s1[0] = 0;
        func_800E5D30(var_s1, 0x40, 0x70, 0);
        D_80073060++;
        break;
    case 3:
        if (g_UseDisk) {
            if (D_8006C3B0 == 0) {
                D_80073060++;
            }
        } else {
            if (g_StageId == STAGE_ST0 ||
                g_CurrentPlayableCharacter != PLAYER_ALUCARD) {
                if (func_800E81FC(13, 0) < 0) {
                    break;
                }
            } else if (func_800E81FC(1, 0) < 0) {
                break;
            }
            D_80073060++;
        }
        break;
    case 4:
        if (g_UseDisk) {
            D_8006C398 = 1;
            D_8006BAFC = 3;
            g_mapTilesetId = g_StageId;
        }
        D_80073060++;
        break;
    case 5:
        if (!g_UseDisk) {
            if (func_800E81FC(0, 5) >= 0) {
                D_80073060++;
            }
        } else if (D_8006C3B0 == 0) {
            D_80073060++;
        }
        break;
    case 6:
        if (g_UseDisk) {
            D_8006C398 = 1;
            D_8006BAFC = 0xD;
        }
        D_80073060++;
        break;
    case 7:
        if (!g_UseDisk) {
            if (func_800E81FC(0, 2) >= 0) {
                if (func_800E81FC(0, 3) >= 0) {
                    D_80073060++;
                }
            }
        } else if (D_8006C3B0 == 0) {
            D_80073060++;
        }
        break;
    case 8:
        if (g_UseDisk) {
            D_8006C398 = 1;
            D_8006BAFC = 0x100;
        }
        D_80073060++;
        break;
    case 9:
        if (!g_UseDisk) {
            if (func_800E81FC(0, 1) < 0) {
                break;
            }
            var_a0 = D_800A3C40[g_StageId].unk29;
            if (var_a0 >= 0 && func_800E81FC(var_a0, 4) < 0) {
                break;
            }
            D_80073060++;
        } else if (D_8006C3B0 == 0) {
            D_80073060++;
        }
        break;
    case 10:
        if (D_80097914 == 0) {
            func_800FF7B8(0);
        }
        D_8003C908.D_8003C90C = -1;
        D_8003C908.D_8003C910 = -1;
        D_8006CBC4 = 0;
        D_80073064 = 0;
        if (g_StageId == STAGE_ST0 ||
            g_CurrentPlayableCharacter != PLAYER_ALUCARD) {
            D_80073060 = 0x10;
        } else {
            if (g_UseDisk) {
                D_8006C398 = 1;
                D_8006BAFC = 0x11;
                var_s0 = D_800A4B04[g_Status.equipment[0]].weaponId;
                if (var_s0 == 0xFF) {
                    var_s0 = 1;
                }
                if (g_Status.equipment[3] == 0x19) {
                    var_s0 = D_800A4B04[0xD8].weaponId;
                }
                D_8003C908.D_8003C90C = var_s0;
            }
            D_80073060++;
        }
        break;
    case 11:
        if (g_UseDisk) {
            if (D_8006C3B0 != 0) {
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
                var_s0 = D_800A76F3;
            }
            if (func_800E81FC(var_s0, 7) < 0) {
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
                var_s0 = D_800A76F3;
            }
            if (func_800E81FC(var_s0, 8) >= 0) {
                D_8003C908.D_8003C910 = var_s0;
                pfnWeapon = D_8017D000.func_8017A01C;
                pfnWeapon(D_800A4B04[D_8003C908.D_8003C910].unk10);
            block_102:
                D_80073060++;
            }
        }
        break;
    case 12:
        if (g_UseDisk) {
            D_8006C398 = 1;
            D_8006BAFC = 0x12;
            var_s0 = D_800A4B04[g_Status.equipment[1]].weaponId;
            if (var_s0 == 0xFF) {
                var_s0 = 1;
            }
            if (g_Status.equipment[3] == 0x19) {
                var_s0 = D_800A76F3;
            }
            D_8003C908.D_8003C910 = var_s0;
        }
        D_80073060++;
        break;
    case 13:
        if (g_UseDisk) {
            if (D_8006C3B0 != 0) {
                break;
            }
            pfnWeapon = D_8017D000.func_8017A01C;
            pfnWeapon(D_800A4B04[D_8003C908.D_8003C910].unk10);
        } else if ((func_800E81FC(D_8003C908.D_8003C90C, FILETYPE_WEAPON0_CHR) <
                    0) ||
                   (func_800E81FC(D_8003C908.D_8003C910, FILETYPE_WEAPON1_CHR) <
                    0)) {
            break;
        }
        func_800FA7E8();
        D_80073060++;
        break;
    case 14:
        D_8006CBC4 = func_800E6300();
        if (D_8006CBC4 == 0) {
            D_80073060 += 2;
        } else {
            if (g_UseDisk) {
                D_8006C398 = 1;
                D_8006BAFC = 0x1B;
                g_mapTilesetId = D_8006CBC4 - 1;
            }
            D_80073060++;
        }
        break;
    case 15:
        if (g_UseDisk) {
            if (D_8006C3B0 != 0) {
                break;
            }
        } else {
            func_800E6250();
        }
        D_80073064 = D_8006CBC4;
        D_80073060++;
        break;
    case 16:
        func_800E5D30(var_s1, 0x40, 0x70, 1);
        if (((s32)g_StageId) >= 0x35) {
            D_8006C374 = D_800A3C40[g_StageId].unk28;
        } else {
            D_8006C374 =
                D_800A3C40[g_StageId & (u8)~STAGE_INVERTEDCASTLE_FLAG].unk28;
        }
        if (g_StageId == STAGE_NO3 &&
            g_CurrentPlayableCharacter != PLAYER_ALUCARD) {
            D_8006C374 = 0x11;
            D_8003BDEC[0x34] = 1;
        }
        D_800978C4 = 1;
        func_800E4124(2);
        break;
    }
}

const u32 rodataPadding_800DB7E4 = 0;
