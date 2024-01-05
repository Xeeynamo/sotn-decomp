#include "sel.h"

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

INCLUDE_ASM("asm/us/st/sel/nonmatchings/3367C", func_801B38B4);

void func_801B3A54(s32 arg0, s32 arg1) {
    char pad[0x20];

    g_MemCardRStep = 0;
    D_801BAFFC = arg0;
    D_801BB000 = arg1;
    D_801BB004 = arg0;
    D_801BB00C = arg1;
    D_801BB008 = arg1;
}

INCLUDE_ASM("asm/us/st/sel/nonmatchings/3367C", func_801B3A94);

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

void InitRoomEntities(s32 objLayoutId) {
    switch (D_8003C9A4) {
    case 0:
        if (g_IsUsingCd) {
            break;
        }
        g_IsTimeAttackUnlocked = true;
        D_8003C728 = 1;
        D_8003C100 = 0;
        D_8003C9A4 = 1;
        break;

    case 1:
        func_801B9C80();
        if (D_8003C728) {
            break;
        }
        g_IsTimeAttackUnlocked = false;
        D_8003C100 = 0;
        func_801B18F4();
        g_GameState = Game_Title;
        D_8003C9A4 = 0;
        break;
    }
}
