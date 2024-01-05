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
