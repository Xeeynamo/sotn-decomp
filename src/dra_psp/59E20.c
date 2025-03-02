// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

void func_8012C600(void) {
    s32 x, y;
    s32 i;
    s32 t0 = PLAYER.posX.i.hi;
    s32 t1 = PLAYER.posY.i.hi;

    x = g_Entities[20].posX.i.hi + 8;
    for (i = 0; i < 9; i++) {
        if (x <= g_Entities[i + 21].posX.i.hi + 4) {
            x = g_Entities[i + 21].posX.i.hi + 4;
        }
    }
    D_8013AEBC[0] = x - t0;

    x = g_Entities[20].posX.i.hi - 8;
    for (i = 0; i < 9; i++) {
        if (x >= g_Entities[i + 21].posX.i.hi - 4) {
            x = g_Entities[i + 21].posX.i.hi - 4;
        }
    }
    D_8013AEBC[2] = x - t0;

    y = g_Entities[21].posY.i.hi;
    for (i = 0; i < 9; i++) {
        if (y >= g_Entities[i + 21].posY.i.hi) {
            y = g_Entities[i + 21].posY.i.hi;
        }
    }
    y = y - 4;
    if (y >= g_Entities[30].posY.i.hi - 12) {
        y = g_Entities[30].posY.i.hi - 12;
    }
    if (y >= g_Entities[20].posY.i.hi - 8) {
        y = g_Entities[20].posY.i.hi - 8;
    }
    D_8013AEBC[3] = y - t1;
    if (D_8013AEBC[3] < -24) {
        D_8013AEBC[3] = -24;
    }

    y = g_Entities[21].posY.i.hi;
    for (i = 0; i < 9; i++) {
        if (y <= g_Entities[i + 21].posY.i.hi) {
            y = g_Entities[i + 21].posY.i.hi;
        }
    }
    y = y + 4;

    if (y <= PLAYER.posY.i.hi + 28) {
        y = PLAYER.posY.i.hi + 28;
    }
    if (y <= g_Entities[17].posY.i.hi + 28) {
        y = g_Entities[17].posY.i.hi + 28;
    }
    D_8013AEBC[1] = y - t1;
    if (D_8013AEBC[1] > 0x27) {
        D_8013AEBC[1] = 0x27;
    }

    if (!PLAYER.facingLeft) {
        if (D_8013AEBC[2] < -0x2C) {
            D_8013AEBC[2] = -0x2C;
        }
        if (D_8013AEBC[0] > 0x13) {
            D_8013AEBC[0] = 0x13;
        }
    } else {
        if (D_8013AEBC[2] < -0x13) {
            D_8013AEBC[2] = -0x13;
        }
        if (D_8013AEBC[0] > 0x2C) {
            D_8013AEBC[0] = 0x2C;
        }
    }
}

bool WolfFormFinished(void) {
    if (PLAYER.step_s == 0 || PLAYER.step_s == 8) {
        return false;
    }
    if (D_80097448[1] != 0 && !IsRelicActive(RELIC_HOLY_SYMBOL) ||
        g_Player.padTapped & PAD_L1 ||
        HandleTransformationMP(FORM_WOLF, REDUCE) < 0) {
        SetPlayerStep(Player_UnmorphWolf);
        SetPlayerAnim(0xCA);
        D_800AFDA4[1] = 1;
        PLAYER.palette = 0x810D;
        g_Player.unk66 = 0;
        g_Player.unk68 = 0;
        // Create factory for EntityPlayerBlinkWhite
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(44, 0x24), 0);
        PLAYER.velocityY >>= 1;
        return true;
    }
    return false;
}

INCLUDE_ASM("dra_psp/psp/dra_psp/59E20", func_psp_09136D18);

INCLUDE_ASM("dra_psp/psp/dra_psp/59E20", func_psp_09136E18);
