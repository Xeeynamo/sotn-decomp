// SPDX-License-Identifier: AGPL-3.0-only
#include "sel.h"

s32 func_801B3164(void) {
    char saveFile[0x20];
    s32 temp_s2;
    s32 ret;
    s32 i;
    s32 port;
    u32 block;

    FntPrint(D_801A7AF8, g_MemCardRStep, g_MemCardRStepSub);
    FntPrint(D_801A7B08, g_MemCardRetryCount);

    port = g_MemCardRStepSub / 15;
    block = g_MemCardRStepSub % 15;

    switch (g_MemCardRStep) {
    case 0:
        g_IsTimeAttackUnlocked = 0;
        MemcardInit();
        g_MemCardRetryCount = 5;
        ++g_MemCardRStep;
        break;
    case 1:
        g_SaveSummary[0].padding = func_800E9880(0, 0);
        if (g_SaveSummary[0].padding != 0) {
            if (g_SaveSummary[0].padding == -1 && --g_MemCardRetryCount != -1) {
                g_SaveSummary[0].padding = 0;
            } else if (
                g_SaveSummary[0].padding == -3 && --g_MemCardRetryCount != -1) {
                g_SaveSummary[0].padding = 0;
            } else {
                MemcardInit();
                ++g_MemCardRStep;
                g_MemCardRetryCount = 5;
            }
        }
        break;
    case 2:
        g_SaveSummary[1].padding = func_800E9880(1, 0);
        if (g_SaveSummary[1].padding != 0) {
            if (g_SaveSummary[1].padding == -1 && --g_MemCardRetryCount != -1) {
                g_SaveSummary[1].padding = 0;
            } else if (
                g_SaveSummary[1].padding == -3 && --g_MemCardRetryCount != -1) {
                g_SaveSummary[1].padding = 0;
            } else {
                MemcardInit();
                ++g_MemCardRStep;
            }
        }
        break;
    case 3:
        if (MemcardParse(0, 0) >= 0) {
            temp_s2 = func_801B2E5C(0);
            for (i = 0; i < 15; ++i) {
                MakeMemcardPath(saveFile, i);
                MemcardDetectSave(0, (u8*)saveFile, i);
                g_SaveSummary[0].icon[i] = -3;
                if (i >= 15 - temp_s2) {
                    g_SaveSummary[0].icon[i] = -2;
                }
            }
            MemcardInit();
            ++g_MemCardRStep;
        }
        break;
    case 4:
        if (MemcardParse(1, 0) >= 0) {
            temp_s2 = func_801B2E5C(1);
            for (i = 0; i < 15; ++i) {
                MakeMemcardPath(saveFile, i);
                MemcardDetectSave(1, (u8*)saveFile, i);
                g_SaveSummary[1].icon[i] = -3;
                if (i >= 15 - temp_s2) {
                    g_SaveSummary[1].icon[i] = -2;
                }
            }
            MemcardInit();
            g_MemCardRStepSub = 0;
            D_801BAFF4 = 0;
            g_MemCardRetryCount = 10;
            ++g_MemCardRStep;
        }
        break;
    case 5:
        if (IsMemcardBlockUsed(port, block) == 0) {
            ++g_MemCardRStepSub;
            if (g_MemCardRStepSub == 30) {
                g_MemCardRStep += 2;
            }
            if (g_MemCardRStepSub == 15) {
                D_801BAFF4 = 0;
                break;
            }
            break;
        }
        MakeMemcardPath(saveFile, block);
        if (MemcardReadFile(port, 0, saveFile, g_Pix, 0) != 0) {
            --g_MemCardRetryCount;
            if (g_MemCardRetryCount == -1) {
                g_MemCardRStep = 0;
                break;
            }
            break;
        }
        ++g_MemCardRStep;
        break;
    case 6:
        ret = MemcardClose(port);
        if (ret == 0) {
            break;
        }
        if (ret == -3) {
            --g_MemCardRetryCount;
            if (g_MemCardRetryCount != -1) {
                --g_MemCardRStep;
                break;
            }
            g_MemCardRStep = 0;
            break;
        }
        HydrateSaveSummaryEntry(port, D_801BAFF4, block);
        g_MemCardRetryCount = 10;
        ++D_801BAFF4;
        ++g_MemCardRStepSub;
        if (g_MemCardRStepSub == 15 * 2) {
            ++g_MemCardRStep;
            break;
        }
        if (g_MemCardRStepSub == 15) {
            D_801BAFF4 = 0;
        }
        --g_MemCardRStep;
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
    char saveFile[32];
    s32 nPort;
    s32 nSlot;
    s32 temp_v0;
    s32 blockId;

    FntPrint(D_801A7AF8, g_MemCardRStep, g_MemCardRStepSub);
    FntPrint(D_801A7B08, g_MemCardRetryCount);

    nPort = g_MemCardRStepSub / 15;
    nSlot = g_MemCardRStepSub % 15;
    blockId = g_SaveSummary[nPort].slot[nSlot];
    switch (g_MemCardRStep) {
    case 0:
        MemcardInit();
        g_MemCardRetryCount = 10;
        g_MemCardRStep = 3;
        break;
    case 3:
        MakeMemcardPath(saveFile, blockId);
        if (MemcardReadFile(nPort, 0, saveFile, g_Pix[0], 1) != 0) {
            g_MemCardRetryCount--;
            if (g_MemCardRetryCount != -1) {
                return 0;
            }
            temp_v0 = -1;
            return temp_v0;
        }
        g_MemCardRStep++;
        break;
    case 4:
        temp_v0 = MemcardClose(nPort);
        if (temp_v0 != 0) {
            if (temp_v0 == -3) {
                g_MemCardRetryCount--;
                if (g_MemCardRetryCount == -1) {
                    return -1;
                } else {
                    g_MemCardRStep--;
                    do {
                        return 0;
                    } while (0); // FAKE!
                }
            }
            if (LoadSaveData(g_Pix[0]) < 0) {
                return -2;
            } else {
                return 1;
            }
        }
        break;
    }

    return 0;
}

void func_801B38B4(s32 arg0, s32 arg1) {
    char pad[32];
    s32 i;
    s32 j;
    u32 n;

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
    char pad[0x20];

    g_MemCardRStep = 0;
    D_801BAFFC = arg0;
    D_801BB000 = arg1;
    D_801BB004 = arg0;
    D_801BB00C = arg1;
    D_801BB008 = arg1;
}

extern s32 D_8007F208;
s32 func_801B3A94(s32 arg0) {
    char saveFile[0x20];
    s32 ret;
    u32 create;
    SaveData* save;

    FntPrint("\nrstep:%d,%d,%d\n", g_MemCardRStep,
             (D_801BAFFC * 15) + D_801BB000, (D_801BB004 * 15) + D_801BB008);
    FntPrint(D_801A7B08, g_MemCardRetryCount);
    switch (g_MemCardRStep) {
    case 0:
        MemcardInit();
        g_MemCardRetryCount = 10;
        g_MemCardRStep++;
        break;
    case 1:
        MakeMemcardPath(saveFile, D_801BB000);
        if (MemcardReadFile(D_801BAFFC, 0, saveFile, g_Pix, 1) != 0) {
            g_MemCardRetryCount--;
            if (g_MemCardRetryCount == -1) {
                return -1;
            }
        } else {
            g_MemCardRStep++;
        }
        break;
    case 2:
        ret = MemcardClose(D_801BAFFC);
        if (ret == 0) {
            break;
        }
        if (ret == -3) {
            g_MemCardRetryCount--;
            if (g_MemCardRetryCount == -1) {
                return -1;
            }
            g_MemCardRStep--;
            break;
        }

        save = (SaveData*)g_Pix;
        if (arg0 != 0) {
            if (arg0 == 1) {
                D_8007F208 |= 1;
            } else {
                strcpy(save->info.name, (const char*)arg0);
                strcpy(save->status.saveName, (const char*)arg0);
            }
        }
        LoadSaveData((SaveData*)g_Pix);
        StoreSaveData((SaveData*)g_Pix, D_801BB008, save->info.cardIcon);
        g_MemCardRetryCount = 10;
        g_MemCardRStep++;
        break;
    case 3:
        create = g_SaveSummary[D_801BB004].icon[D_801BB00C] < 0;
        MakeMemcardPath(saveFile, D_801BB008);
        if (MemcardWriteFile(D_801BB004, 0, saveFile, g_Pix, 1, create) != 0) {
            g_MemCardRetryCount--;
            if (g_MemCardRetryCount == -1) {
                return -3;
            }
        } else {
            g_MemCardRStep++;
        }
        break;
    case 4:
        ret = MemcardClose(D_801BB004);
        if (ret == 0) {
            break;
        }
        if (ret == -3) {
            g_MemCardRetryCount--;
            if (g_MemCardRetryCount == -1) {
                return -3;
            }
            g_MemCardRStep--;
            break;
        }
        HydrateSaveSummaryEntry(D_801BB004, D_801BB00C, D_801BB008);
        return 1;
    }
    return 0;
}

void func_801B3E14(s32 arg0) {
    g_MemCardRStep = 0;
    g_MemCardRStepSub = arg0;
}

s32 func_801B3E2C(void) {
    char path[32];
    s32 slot;
    s32 blockId;
    s32 port;

    port = g_MemCardRStepSub / 15;
    slot = g_MemCardRStepSub % 15;
    blockId = g_SaveSummary[port].slot[slot];
    switch (g_MemCardRStep) {
    case 0:
        MemcardInit(slot, blockId);
        g_MemCardRetryCount = 10;
        g_MemCardRStep++;
        break;
    case 1:
        MakeMemcardPath(path, blockId);
        if (MemcardEraseFile(port, 0, path)) {
            if (--g_MemCardRetryCount == -1) {
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

#ifndef HARD_LINK
void MemCardSetPort(s32 port) {
    g_MemCardRStep = 0;
    g_MemCardRStepSub = port;
}

s32 MemCardInitAndFormat(void) {
    int dummy[8];
    u32 nPort = g_MemCardRStepSub;
    s32 state = g_MemCardRStep;

    switch (state) {
    case 0:
        MemcardInit();
        g_MemCardRetryCount = 5;
        g_MemCardRStep++;
        break;

    case 1:
        if (MemcardFormat(nPort, 0) != 1) {
            if (--g_MemCardRetryCount == -1) {
                return -1;
            }
        } else {
            return 1;
        }
        break;
    }

    return 0;
}
#endif

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
