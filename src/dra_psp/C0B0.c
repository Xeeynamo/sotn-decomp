// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"

extern bool D_80137598;

INCLUDE_ASM("dra_psp/psp/dra_psp/C0B0", func_psp_090E8A30);

void func_800F24F4(void) {
    s32 x;
    s32 y;
    s32 var_a0;

    x = g_Tilemap.left + (g_PlayerX >> 8);
    y = g_Tilemap.top + (g_PlayerY >> 8);
    if (D_8003C708.flags & STAGE_INVERTEDCASTLE_FLAG) {
        if (g_StageId == STAGE_RNO0 && x == 32 && y == 36) {
            if (TimeAttackController(TIMEATTACK_EVENT_FINAL_SAVEPOINT,
                                     TIMEATTACK_GET_RECORD) == 0) {
                TimeAttackController(
                    TIMEATTACK_EVENT_FINAL_SAVEPOINT, TIMEATTACK_SET_RECORD);
            }
        }

        var_a0 = 0;
        if (g_StageId == STAGE_RNO4 && x == 18 && y == 30) {
            D_80137598 = false;
            return;
        }
        if (g_StageId == STAGE_NO4 && x == 45 && y == 33) {
            if (PLAYER.posX.i.hi == 128) {
                D_8003C730 = 1;
            } else {
                if (TimeAttackController(TIMEATTACK_EVENT_SUCCUBUS_DEFEAT,
                                         TIMEATTACK_GET_RECORD)) {
                    D_80137598 = false;
                    return;
                }
            }
            var_a0 = 1;
        }
        func_801042C4(var_a0);
        D_80137598 = true;
        func_80105428();
    } else {
        D_80137598 = false;
    }
}

INCLUDE_ASM("dra_psp/psp/dra_psp/C0B0", func_psp_090E8CA8);

INCLUDE_ASM("dra_psp/psp/dra_psp/C0B0", func_psp_090E8E58);

INCLUDE_ASM("dra_psp/psp/dra_psp/C0B0", func_psp_090E8EC0);

INCLUDE_ASM("dra_psp/psp/dra_psp/C0B0", func_800F298C);

INCLUDE_ASM("dra_psp/psp/dra_psp/C0B0", func_psp_090EAF08);

INCLUDE_ASM("dra_psp/psp/dra_psp/C0B0", func_psp_090EAFA8);

INCLUDE_ASM("dra_psp/psp/dra_psp/C0B0", func_psp_090EB028);

INCLUDE_ASM("dra_psp/psp/dra_psp/C0B0", func_psp_090EB238);

INCLUDE_ASM("dra_psp/psp/dra_psp/C0B0", func_psp_090EB298);
