// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"

INCLUDE_ASM("dra_psp/psp/dra_psp/39AA8", SetPlayerStep);

INCLUDE_ASM("dra_psp/psp/dra_psp/39AA8", func_psp_09116450);

INCLUDE_ASM("dra_psp/psp/dra_psp/39AA8", func_psp_09116720);

INCLUDE_ASM("dra_psp/psp/dra_psp/39AA8", SetPlayerAnim);

INCLUDE_ASM("dra_psp/psp/dra_psp/39AA8", func_psp_09116B88);

INCLUDE_ASM("dra_psp/psp/dra_psp/39AA8", UpdateUnarmedAnim);

INCLUDE_ASM("dra_psp/psp/dra_psp/39AA8", func_8010DBFC);

INCLUDE_ASM("dra_psp/psp/dra_psp/39AA8", UpdateAnim);

INCLUDE_ASM("dra_psp/psp/dra_psp/39AA8", func_psp_09117538);

INCLUDE_ASM("dra_psp/psp/dra_psp/39AA8", func_8010DFF0);

INCLUDE_ASM("dra_psp/psp/dra_psp/39AA8", func_8010E0A8);

INCLUDE_ASM("dra_psp/psp/dra_psp/39AA8", func_psp_091176D8);

INCLUDE_ASM("dra_psp/psp/dra_psp/39AA8", func_psp_091176F0);

void func_8010E168(s32 arg0, s16 arg1) {
    if (arg0 == 0) {
        // Create factory with unkA0 = 0x1500, blueprint #44.
        // Blueprint 44 is to make child entity #11, or EntityPlayerBlinkWhite
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(44, 0x15), 0);
        if (g_Player.timers[13] <= arg1) {
            g_Player.timers[13] = arg1;
        }
    } else if (g_Player.timers[14] <= arg1) {
        g_Player.timers[14] = arg1;
    }
}

void DecelerateX(s32 amount) {
    if (g_CurrentEntity->velocityX < 0) {
        g_CurrentEntity->velocityX += amount;
        if (g_CurrentEntity->velocityX > 0) {
            g_CurrentEntity->velocityX = 0;
        }
    } else {
        g_CurrentEntity->velocityX -= amount;
        if (g_CurrentEntity->velocityX < 0) {
            g_CurrentEntity->velocityX = 0;
        }
    }
}

void DecelerateY(s32 amount) {
    if (g_CurrentEntity->velocityY < 0) {
        g_CurrentEntity->velocityY += amount;
        if (g_CurrentEntity->velocityY > 0) {
            g_CurrentEntity->velocityY = 0;
        }
    } else {
        g_CurrentEntity->velocityY -= amount;
        if (g_CurrentEntity->velocityY < 0) {
            g_CurrentEntity->velocityY = 0;
        }
    }
}

s32 CheckMoveDirection(void) {
    if (g_Player.unk44 & 2) {
        return 0;
    }
    if (PLAYER.facingLeft == 1) {
        if (g_Player.padPressed & PAD_RIGHT) {
            PLAYER.facingLeft = 0;
            g_Player.unk4C = 1;
            return -1;
        } else if (g_Player.padPressed & PAD_LEFT) {
            return 1;
        }
    } else {
        if (g_Player.padPressed & PAD_RIGHT) {
            return 1;
        }
        if (g_Player.padPressed & PAD_LEFT) {
            PLAYER.facingLeft = 1;
            g_Player.unk4C = 1;
            return -1;
        }
    }
    return 0;
}

INCLUDE_ASM("dra_psp/psp/dra_psp/39AA8", func_psp_09117A90);

INCLUDE_ASM("dra_psp/psp/dra_psp/39AA8", SetSpeedX);

INCLUDE_ASM("dra_psp/psp/dra_psp/39AA8", func_psp_09117B78);

INCLUDE_ASM("dra_psp/psp/dra_psp/39AA8", func_8010E3E0);
