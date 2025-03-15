// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"


INCLUDE_ASM("dra_psp/psp/dra_psp/80", func_80102EB8);

INCLUDE_ASM("dra_psp/psp/dra_psp/80", func_psp_090DCBC8);

INCLUDE_ASM("dra_psp/psp/dra_psp/80", func_psp_090DCC60);

INCLUDE_ASM("dra_psp/psp/dra_psp/80", HandleSaveMenu);

INCLUDE_ASM("dra_psp/psp/dra_psp/80", func_80103EAC);

s32 MemcardParse(s32 nPort, s32 nCard);
s32 MemcardDetectSave(s32 nPort, char* expectedSaveName, s32 block);
s32 GetMemcardFreeBlockCount(s32 nPort);
s32 MemcardClose(s32 nPort);
s32 MemcardWriteFile(
    s32 nPort, s32 nCard, char* name, void* data, s32 flags, s32 create, s32 unk);
s32 func_800E9880(s32 nPort, s32 nCard);
void func_80103ED4(void) {
    char saveFile[32];
    s32 memCardClose;
    s32 i;
    s32 case1_state;

    switch (D_80137E4C) {
    case 0:
        MemcardInit();
        g_MemCardRetryCount = 4;
        D_80137E4C++;
        break;
    case 1:
        // This really should be doable as a switch, but that doesn't match.
        case1_state = func_800E9880(D_80097924, 0);
        if (case1_state == 0) {
            break;
        }
        if (case1_state == -1) {
            if (g_MemCardRetryCount-- == 0) {
                D_80137E4C = 7;
            }
        } else if (case1_state == -3) {
            if (g_MemCardRetryCount-- == 0) {
                D_80137E4C = 8;
            }
        } else if (case1_state == -2) {
            D_80137E4C = 9;
        } else {
            MemcardInit();
            D_80137E4C++;
        }
        break;
    case 2:
        if (MemcardParse(D_80097924, 0) >= 0) {
            g_MemCardRetryCount = 10;
            if (D_8006C378 >= 0) {
                i = 0;
                if (D_80137E54 == 2) {
                    for (i = 0; i < 15; i++) {
                        MakeMemcardPath(saveFile, i);
                        if (MemcardDetectSave(D_80097924, saveFile, 0) != 0) {
                            break;
                        }
                    }
                    if ((i == 15) &&
                        (GetMemcardFreeBlockCount(D_80097924) == 0)) {
                        D_80137E54 = 3;
                    }
                }
                D_80137E4C += 2;
                break;
            } else {
                D_80137E4C++;
                break;
            }
        }
        break;
    case 3:
        for (i = 0; i < 15; i++) {
            MakeMemcardPath(saveFile, i);
            if (MemcardDetectSave(D_80097924, saveFile, 0) == 0) {
                break;
            }
        }
        if (i == 15 || GetMemcardFreeBlockCount(D_80097924) == 0) {
            D_80137E4C = 10;
            break;
        }
        D_8006C378 = i;
        D_80137E4C++;
        break;
    case 4:
        MakeMemcardPath(saveFile, D_8006C378);
        // careful with i here, it's not an iterator.
        if (MemcardDetectSave(D_80097924, saveFile, 0) == 1) {
            i = 0;
        } else {
            i = 1;
            if (GetMemcardFreeBlockCount(D_80097924) == 0) {
                D_80137E4C = 10;
                break;
            }
        }
        // I believe the rand() call here selects the icon on the save
        // in the save-select screen.
        StoreSaveData(g_Pix, D_8006C378, rand() & 0xF);
        func_psp_090DFC68();
        if (MemcardWriteFile(D_80097924, 0, saveFile, g_Pix, 1, i, 1) != 0) {
            D_801379BC = 0x101;
            D_80137E54 = 0;
            D_80097924 = D_80137EF0;
            D_8006C378 = D_80137EF4;
            g_Player.padSim = 0;
            g_Player.D_80072EFC = 1;
            D_80137E4C = 6;
        } else {
            g_MemCardRetryCount = 10;
            D_80137E4C++;
            break;
        }
        break;
    case 5:
        memCardClose = MemcardClose(D_80097924);
        if (memCardClose == 0) {
            break;
        }
        if (memCardClose == -3) {
            if (g_MemCardRetryCount-- == 0) {
                D_80137E4C = 0;
                break;
            }
            D_80137E4C--;
            break;  
        }
        D_80137E4C = 6;
        break;
    case 6:
        break;
    }
}

INCLUDE_ASM("dra_psp/psp/dra_psp/80", func_psp_090DDAA8);

INCLUDE_ASM("dra_psp/psp/dra_psp/80", func_801042C4);

INCLUDE_ASM("dra_psp/psp/dra_psp/80", func_80104790);
