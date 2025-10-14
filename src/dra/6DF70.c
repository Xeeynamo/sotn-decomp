// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"

void func_8010DF70(void) {
    g_CurrentEntity = &PLAYER;

    switch (PLAYER.ext.player.anim) {
    case 0xBA:
    case 0xBB:
    case 0xBE:
    case 0xF0:
    case 0xF1:
        PlayAnimation(D_800B0130, D_800B01B8);
    }
}

void func_8010DFF0(s32 resetAnims, s32 arg1) {
    Primitive* prim;
    s32 i;

    if (resetAnims) {
        g_Entities[E_AFTERIMAGE_1].ext.disableAfterImage.unk7D = 1;
        g_Entities[E_AFTERIMAGE_1].animCurFrame =
            g_Entities[E_AFTERIMAGE_2].animCurFrame =
                g_Entities[E_AFTERIMAGE_3].animCurFrame = 0;
        prim = &g_PrimBuf[g_Entities[E_AFTERIMAGE_1].primIndex];

        for (i = 0; i < 6; i++) {
            prim->x1 = 0;
            prim = prim->next;
        }
    }

    g_Entities[E_AFTERIMAGE_1].ext.disableAfterImage.unk7C = 1;
    g_Entities[E_AFTERIMAGE_1].ext.disableAfterImage.unk7E = 10;

    if (arg1) {
        if (arg1 < 4) {
            g_Player.timers[ALU_T_15] = 4;
        } else {
            g_Player.timers[ALU_T_15] = arg1;
        }
    }
}

void ResetAfterImageIndex(void) {
    g_Entities[E_AFTERIMAGE_1].ext.afterImage.index = 0;
}

void EnableAfterImage(void) {
    g_Entities[E_AFTERIMAGE_1].ext.afterImage.resetFlag = 0;
    g_Entities[E_AFTERIMAGE_1].ext.afterImage.disableFlag = 0;
}

void func_8010E0D0(s32 arg0) {
    Entity* entity;
    Entity* player;

    if (arg0 == 1) {
        player = &PLAYER;

        entity = CreateEntFactoryFromEntity(
            player, FACTORY(BP_BLINK_WHITE, 0x47), 0);
        if (entity != NULL) {
            entity->flags |= FLAG_UNK_10000;
        }

        entity = CreateEntFactoryFromEntity(
            player, FACTORY(BP_BLINK_WHITE, 0x40), 0);
        if (entity != NULL) {
            entity->flags |= FLAG_UNK_10000;
        }
    }
    func_8010DFF0(1, 1);
}

void func_8010E168(s32 arg0, s16 arg1) {
    if (arg0 == 0) {
        // Create factory with unkA0 = 0x1500, blueprint #44.
        // Blueprint 44 is to make child entity #11, or EntityPlayerBlinkWhite
        CreateEntFactoryFromEntity(
            g_CurrentEntity, FACTORY(BP_BLINK_WHITE, 0x15), 0);
        if (g_Player.timers[13] <= arg1) {
            g_Player.timers[13] = arg1;
        }
    } else if (g_Player.timers[14] <= arg1) {
        g_Player.timers[14] = arg1;
    }
}

#include "../decelerate.h"

// Checks the player's left/right inputs and compares to the facing direction.
// If the player is pressing the opposite of facing, we change the facing value
// to turn the player around, and return -1.
// If the player is pressing the same direction they are facing, return 1
// If the player is not pressing left or right, return 0
// Note that if the player is pressing both left and right, left is ignored.
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

s32 func_8010E334(s32 xStart, s32 xEnd) {
    g_Player.unk7A = 1;
    // Interesting - this could have been all && conditions, but if you try,
    // PS1 optimizes into loading PLAYER.step as a word, rather than doing
    // two accesses for step and step_s. Breaking it up like this prevents
    // the optimization and results in a match.
    if (PLAYER.step == Player_Stand) {
        if (PLAYER.step_s == 1 && PLAYER.posX.i.hi >= xStart &&
            PLAYER.posX.i.hi <= xEnd) {
            return 1;
        }
    }
    return 0;
}

#include "../set_speed_x.h"

// Updates the Player velocity in the X Axis
void func_8010E3B8(s32 velocityX) {
    if (PLAYER.entityRoomIndex == 1) {
        velocityX = -velocityX;
    }
    PLAYER.velocityX = velocityX;
}

void func_8010E3E0(void) {
    if (g_Player.unk48) {
        DestroyEntity(&g_Entities[16]);
        g_Player.unk48 = 0;
    }
}
