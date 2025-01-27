// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"

void GetPlayerSensor(Collider* col) {
    void (*theFunc)(Collider* col);
    u32 mod = 0;
    if (g_PlayableCharacter == PLAYER_ALUCARD) {
        if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
            mod += 2;
        }
        col->unk14 = g_SensorsWall[0].x - mod;
        col->unk1C = g_SensorsWall[0].y + mod;
        col->unk18 = g_SensorsFloor[1].y - 1;
        col->unk20 = g_SensorsCeiling[1].y + 1;
    } else {
        theFunc = g_PlOvl.GetPlayerSensor;
        theFunc(col);
    }
}

// func_8010BFFC
INCLUDE_ASM("dra_psp/psp/dra_psp/3B9B0", func_psp_09118408);
// CheckFloor
INCLUDE_ASM("dra_psp/psp/dra_psp/3B9B0", func_psp_091187D8);
// CheckCeiling
INCLUDE_ASM("dra_psp/psp/dra_psp/3B9B0", func_psp_091190E0);
// CheckWallRight
INCLUDE_ASM("dra_psp/psp/dra_psp/3B9B0", func_psp_09119950);
// CheckWallLeft
INCLUDE_ASM("dra_psp/psp/dra_psp/3B9B0", func_psp_09119D00);
