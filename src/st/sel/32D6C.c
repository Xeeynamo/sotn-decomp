// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sel.h"

// BSS
static s32 D_801BAFDC;
static s32 D_801BAFE0;
static u32 D_801BAFE4;
static s32 D_801BAFE8;
static s32 g_MemCardRStep;
static s32 g_MemCardRStepSub;
static s32 D_801BAFF4;
static u32 g_MemCardRetryCount;
static s32 D_801BAFFC;
static s32 D_801BB000;
static s32 D_801BB004;
static s32 D_801BB008;
static s32 D_801BB00C;

void func_801B2D6C(void) {
    MemcardInit();
    D_801BAFDC = 0;
    D_801BAFE0 = 0;
    D_801BAFE4 = 0;
    D_801BAFE8 = 0;
}

s32 func_801B2DAC(void) { return D_801BAFE4 < 2 || D_801BAFE4 == 2; }

void func_801B2DDC(void) {}

void func_801B2DE4(void) {}

void func_801B2DEC(void) {}

void func_801B2DF4(void) {
    if (func_801B2DAC() != 0) {
        D_801BAFDC = func_800E9880(D_801BAFE8, 0);
        if (D_801BAFDC != 0) {
            D_801BAFE0 = D_801BAFDC;
        }
    }

    func_801B2DDC();
    func_801B2DE4();
    func_801B2DEC();
}

s32 func_801B2E5C(s32 port) {
    char cardName[32];
    struct DIRENTRY* dirent;
    s32 i;
    s32 j;
    s32 totalSize;
    s32 nBlockUsed;

    STRCPY(cardName, "BASLUS-00067DRAX00");
    totalSize = 0;
    nBlockUsed = g_MemcardInfo[port].nBlockUsed;
    dirent = &g_MemcardInfo[port].entries;
    for (i = 0; i < nBlockUsed; i++) {
        for (j = 0; j < 16; j++) {
            if (cardName[j] != dirent[i].name[j]) {
                break;
            }
        }
        if (j != 16) {
            totalSize += dirent[i].size;
        }
    }

    totalSize /= CARD_BLOCK_SIZE;
    return totalSize;
}

void HydrateSaveSummaryEntry(s32 port, s32 slot, s32 slotValue) {
    SaveData* save;

    g_SaveSummary[port].slot[slot] = slotValue;
    save = (SaveData*)g_Pix;
    g_SaveSummary[port].icon[slot] = save->info.cardIcon;
    g_SaveSummary[port].stage[slot] = save->info.stage;
    g_SaveSummary[port].roomX[slot] = save->info.roomX;
    g_SaveSummary[port].roomY[slot] = save->info.roomY;
    g_SaveSummary[port].nRoomsExplored[slot] = save->info.nRoomsExplored;
    g_SaveSummary[port].level[slot] = save->info.level;
    g_SaveSummary[port].gold[slot] = save->info.gold;
    g_SaveSummary[port].playHours[slot] = save->info.playHours;
    g_SaveSummary[port].playSeconds[slot] = save->info.playSeconds;
    g_SaveSummary[port].playMinutes[slot] = save->info.playMinutes;
    if (save->info.saveSize != sizeof(SaveData)) {
        save->info.endGameFlags = 0;
    }
    g_SaveSummary[port].kind[slot] = save->info.endGameFlags;
    g_SaveSummary[port].character[slot] = save->info.character;
    strcpy(g_SaveSummary[port].name[slot], save->info.name);
    g_IsTimeAttackUnlocked |= save->info.endGameFlags;
}

void func_801B3120(void) {
    s32 i;

    g_MemCardRStep = 0;
    for (i = 0; i < BLOCK_PER_CARD; i++) {
        g_SaveSummary[0].icon[i] = -1;
        g_SaveSummary[1].icon[i] = -1;
    }
}

s32 func_801B3164(void) {
    char saveFile[0x20];
    s32 slot;
    s32 port;
    s32 ret;
    s32 i;

    FntPrint("\nrstep:%d,%d\n", g_MemCardRStep, g_MemCardRStepSub);
    FntPrint("retry:%d\n", g_MemCardRetryCount);

    port = g_MemCardRStepSub / 15;
    slot = g_MemCardRStepSub % 15;

    switch (g_MemCardRStep) {
    case 0:
        g_IsTimeAttackUnlocked = 0;
        MemcardInit();
        g_MemCardRetryCount = 5;
        g_MemCardRStep++;
        break;

    case 1:
        g_SaveSummary[0].padding = func_800E9880(0, 0);
        if (g_SaveSummary[0].padding != 0) {
            if (g_SaveSummary[0].padding == -1 && g_MemCardRetryCount--) {
                g_SaveSummary[0].padding = 0;
            } else if (
                g_SaveSummary[0].padding == -3 && g_MemCardRetryCount--) {
                g_SaveSummary[0].padding = 0;
            } else {
                MemcardInit();
                g_MemCardRetryCount = 5;
                g_MemCardRStep++;
            }
        }
        break;

    case 2:
        g_SaveSummary[1].padding = func_800E9880(1, 0);
        if (g_SaveSummary[1].padding != 0) {
            if (g_SaveSummary[1].padding == -1 && g_MemCardRetryCount--) {
                g_SaveSummary[1].padding = 0;
            } else if (
                g_SaveSummary[1].padding == -3 && g_MemCardRetryCount--) {
                g_SaveSummary[1].padding = 0;
            } else {
                MemcardInit();
                g_MemCardRStep++;
            }
        }
        break;

    case 3:
        ret = MemcardParse(0, 0);
        if (ret >= 0) {
            ret = func_801B2E5C(0);
            for (i = 0; i < 15; i++) {
                MakeMemcardPath(saveFile, i);
                MemcardDetectSave(0, (u8*)saveFile, i);
                g_SaveSummary[0].icon[i] = -3;
                if (i >= (15 - ret)) {
                    g_SaveSummary[0].icon[i] = -2;
                }
            }
            MemcardInit();
            g_MemCardRStep++;
        }
        break;

    case 4:
        ret = MemcardParse(1, 0);
        if (ret >= 0) {
            ret = func_801B2E5C(1);
            for (i = 0; i < 15; i++) {
                MakeMemcardPath(saveFile, i);
                MemcardDetectSave(1, (u8*)saveFile, i);
                g_SaveSummary[1].icon[i] = -3;
                if (i >= (15 - ret)) {
                    g_SaveSummary[1].icon[i] = -2;
                }
            }
            MemcardInit();
            g_MemCardRStepSub = 0;
            D_801BAFF4 = 0;
            g_MemCardRetryCount = 10;
            g_MemCardRStep++;
        }
        break;

    case 5:
        if (IsMemcardBlockUsed(port, slot) == 0) {
            g_MemCardRStepSub++;
            if (g_MemCardRStepSub == 30) {
                g_MemCardRStep += 2;
            }
            if (g_MemCardRStepSub == 15) {
                D_801BAFF4 = 0;
            }
        } else {
            MakeMemcardPath(saveFile, slot);
            ret = MemcardReadFile(port, 0, saveFile, g_Pix, 0);
            if (ret != 0) {
                if (g_MemCardRetryCount-- == 0) {
                    g_MemCardRStep = 0;
                }
            } else {
                g_MemCardRStep++;
            }
        }
        break;

    case 6:
        ret = MemcardClose(port);
        if (ret != 0) {
            if (ret == -3) {
                if (g_MemCardRetryCount-- == 0) {
                    g_MemCardRStep = 0;
                } else {
                    g_MemCardRStep--;
                }
            } else {
                HydrateSaveSummaryEntry(port, D_801BAFF4, slot);
                D_801BAFF4++;
                g_MemCardRetryCount = 10;
                g_MemCardRStepSub++;
                if (g_MemCardRStepSub == 30) {
                    g_MemCardRStep++;
                } else {
                    if (g_MemCardRStepSub == 15) {
                        D_801BAFF4 = 0;
                    }
                    g_MemCardRStep--;
                }
            }
        }
        break;

    case 7:
        return 1;
    }
    return 0;
}

void func_801B367C(s32 arg0) {
    g_MemCardRStep = 0;
    g_MemCardRStepSub = arg0;
}

s32 TryLoadSaveData(void) {
    char saveFile[0x20];
    s32 port;
    s32 slot;
    s32 blockId;
    s32 ret;

    FntPrint("\nrstep:%d,%d\n", g_MemCardRStep, g_MemCardRStepSub);
    FntPrint("retry:%d\n", g_MemCardRetryCount);

    port = g_MemCardRStepSub / 15;
    slot = g_MemCardRStepSub % 15;
    blockId = g_SaveSummary[port].slot[slot];
    switch (g_MemCardRStep) {
    case 0:
        MemcardInit();
        g_MemCardRetryCount = 10;
        g_MemCardRStep = 3;
        break;

    case 3:
        MakeMemcardPath(saveFile, blockId);
        ret = MemcardReadFile(port, 0, saveFile, g_Pix[0], 1);
        if (ret != 0) {
            if (g_MemCardRetryCount-- == 0) {
                return -1;
            }
        } else {
            g_MemCardRStep++;
        }
        break;

    case 4:
        ret = MemcardClose(port);
        if (ret != 0) {
            if (ret == -3) {
                if (g_MemCardRetryCount-- == 0) {
                    return -1;
                }
                g_MemCardRStep--;
            } else {
                ret = LoadSaveData(g_Pix[0]);
                if (ret < 0) {
                    return -2;
                } else {
                    return 1;
                }
            }
        }
        break;
    }
    return 0;
}

void func_801B38B4(s32 arg0, s32 arg1) {
    char saveFile[0x20];
    s32 i, j;
    s32 n;

    g_MemCardRStep = 0;
    D_801BAFFC = arg0 / 15;
    n = arg0 % 15;
    D_801BB000 = g_SaveSummary[D_801BAFFC].slot[n];
    D_801BB004 = arg1 / 15;
    n = arg1 % 15;
    D_801BB00C = n;
    D_801BB008 = g_SaveSummary[D_801BB004].slot[n];

    if (g_SaveSummary[D_801BB004].icon[n] == -3) {
        for (i = 0; i < 15; i++) {
            for (j = 0; j < 15; j++) {
                if ((g_SaveSummary[D_801BB004].icon[j] >= 0) &&
                    (g_SaveSummary[D_801BB004].slot[j] == i)) {
                    break;
                }
            }

            if (j == 15) {
                D_801BB008 = i;
                return;
            }
        }
    }
}

void func_801B3A54(s32 arg0, s32 arg1) {
    char saveFile[0x20];

    g_MemCardRStep = 0;
    D_801BAFFC = arg0;
    D_801BB000 = arg1;
    D_801BB004 = arg0;
    D_801BB00C = arg1;
    D_801BB008 = arg1;
}

s32 func_801B3A94(s32 arg0) {
    char saveFile[0x20];
    s32 ret;
    SaveData* save;
    u32 var_s3;

    FntPrint("\nrstep:%d,%d,%d\n", g_MemCardRStep,
             D_801BB000 + (D_801BAFFC * 15), D_801BB008 + (D_801BB004 * 15));
    FntPrint("retry:%d\n", g_MemCardRetryCount);
    switch (g_MemCardRStep) {
    case 0:
        MemcardInit();
        g_MemCardRetryCount = 10;
        g_MemCardRStep++;
        break;

    case 1:
        MakeMemcardPath(saveFile, D_801BB000);
        ret = MemcardReadFile(D_801BAFFC, 0, saveFile, g_Pix, 1);
        if (ret != 0) {
            if (g_MemCardRetryCount-- == 0) {
                return -1;
            }
        } else {
            g_MemCardRStep++;
        }
        break;

    case 2:
        ret = MemcardClose(D_801BAFFC);
        if (ret != 0) {
            if (ret == -3) {
                if (g_MemCardRetryCount-- == 0) {
                    return -1;
                }
                g_MemCardRStep--;
            } else {
                save = (SaveData*)g_Pix;
                if (arg0 != 0) {
                    if (arg0 == 1) {
                        save->info.endGameFlags |= 1;
                    } else {
                        strcpy(save->info.name, (const char*)arg0);
                        strcpy(save->status.saveName, (const char*)arg0);
                    }
                }
                LoadSaveData(g_Pix);
                StoreSaveData(g_Pix, D_801BB008, save->info.cardIcon);
                g_MemCardRetryCount = 10;
                g_MemCardRStep++;
            }
        }
        break;

    case 3:
        if (g_SaveSummary[D_801BB004].icon[D_801BB00C] >= 0) {
            var_s3 = 0;
        } else {
            var_s3 = 1;
        }
        MakeMemcardPath(saveFile, D_801BB008);
        ret = MemcardWriteFile(D_801BB004, 0, saveFile, g_Pix, 1, var_s3);
        if (ret != 0) {
            if (g_MemCardRetryCount-- == 0) {
                return -3;
            }
        } else {
            g_MemCardRStep++;
        }
        break;

    case 4:
        ret = MemcardClose(D_801BB004);
        if (ret != 0) {
            if (ret == -3) {
                if (g_MemCardRetryCount-- == 0) {
                    return -3;
                }
                g_MemCardRStep--;
            } else {
                HydrateSaveSummaryEntry(D_801BB004, D_801BB00C, D_801BB008);
                return 1;
            }
        }
        break;
    }
    return 0;
}

void func_801B3E14(s32 arg0) {
    g_MemCardRStep = 0;
    g_MemCardRStepSub = arg0;
}

s32 func_801B3E2C(void) {
    char saveFile[0x20];
    s32 port;
    s32 slot;
    s32 blockId;
    s32 ret;

    port = g_MemCardRStepSub / 15;
    slot = g_MemCardRStepSub % 15;
    blockId = g_SaveSummary[port].slot[slot];
    switch (g_MemCardRStep) {
    case 0:
        MemcardInit();
        g_MemCardRetryCount = 10;
        g_MemCardRStep++;
        break;

    case 1:
        MakeMemcardPath(saveFile, blockId);
        ret = MemcardEraseFile(port, 0, saveFile);
        if (ret != 0) {
            if (g_MemCardRetryCount-- == 0) {
                return -1;
            }
        } else {
            g_SaveSummary[port].icon[slot] = -3;
            return 1;
        }
        break;
    }
    return 0;
}

void MemCardSetPort(s32 port) {
    g_MemCardRStep = 0;
    g_MemCardRStepSub = port;
}

s32 MemCardInitAndFormat(void) {
    char saveFile[0x20];
    u32 nPort = g_MemCardRStepSub;

    switch (g_MemCardRStep) {
    case 0:
        MemcardInit();
        g_MemCardRetryCount = 5;
        g_MemCardRStep++;
        break;

    case 1:
        if (MemcardFormat(nPort, 0) != 1) {
            if (g_MemCardRetryCount-- == 0) {
                return -1;
            }
        } else {
            return 1;
        }
        break;
    }

    return 0;
}

void SEL_Init(s32 objLayoutId) {
    switch (g_GameEngineStep) {
    case 0:
        if (g_IsUsingCd) {
            break;
        }
        g_IsTimeAttackUnlocked = true;
        D_8003C728 = 1;
        g_CurrentStream = 0;
        g_GameEngineStep = Engine_Normal;
        break;

    case 1:
        func_801B9C80();
#ifndef VERSION_PC // skip Konami logo
        if (D_8003C728) {
            break;
        }
#endif
        g_IsTimeAttackUnlocked = false;
        g_CurrentStream = 0;
        func_801B18F4();
        g_GameState = Game_Title;
        g_GameEngineStep = Engine_Init;
        break;
    }
}
