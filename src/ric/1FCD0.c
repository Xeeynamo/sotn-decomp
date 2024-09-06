// SPDX-License-Identifier: AGPL-3.0-or-later
#include "ric.h"
#include "sfx.h"

// Corresponding DRA function is func_80115DA0
void func_8015BCD0(void) {
    PLAYER.velocityY = 0;
    PLAYER.velocityX = 0;
    g_Player.padSim = 0;
    g_Player.D_80072EFC = 4;
    switch (PLAYER.step_s) {
    case 0:
        if (PLAYER.animFrameIdx == 5 && PLAYER.animFrameDuration == 1 &&
            RicCreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 77), 0) ==
                NULL) {
            PLAYER.animFrameDuration = 2;
        }
        if (PLAYER.animFrameDuration < 0) {
            RicSetStand(0);
        }
        break;

    case 2:
        func_8015BB80();
        if (PLAYER.animFrameIdx == 5 && PLAYER.animFrameDuration == 1 &&
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(0x200, 77), 0) == NULL) {
            PLAYER.animFrameDuration = 2;
        }
        if (PLAYER.animFrameDuration < 0) {
            RicSetStand(0);
        }
        break;

    case 4:
        func_8015BB80();
        if (PLAYER.animFrameIdx == 5 && PLAYER.animFrameDuration == 1 &&
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(0x400, 77), 0) == NULL) {
            PLAYER.animFrameDuration = 2;
        }
        if (PLAYER.animFrameDuration < 0) {
            RicSetStand(0);
        }
        break;

    case 1:
    case 3:
    case 5:
        if (PLAYER.animFrameDuration < 0) {
            RicSetStand(0);
        }
        if (g_Player.unk1C != 0) {
            RicSetStand(0);
        }
    }
}

void RicHandleSlideKick(void) {
    // If we are pressing square while in contact with an enemy
    // (as detected in g_Player.unk44), we will bounce back.
    if (g_Player.padPressed & PAD_SQUARE && g_Player.unk44 & 0x80) {
        PLAYER.step = PL_S_JUMP;
        RicSetAnimation(D_8015555C);
        RicSetSpeedX(FIX(-1.5));
        PLAYER.velocityY = 0;
        if (!g_Player.unk72) {
            PLAYER.velocityY = FIX(-4.5);
        }
        PLAYER.step_s = 2;
        g_Player.unk44 |= (8 + 2);
        g_Player.unk44 &= ~4;
        return;
    }
    RicDecelerateX(0x1000);
    PLAYER.velocityY += 0x1000;

    if (g_Player.pl_vram_flag & 1) {
        g_CurrentEntity->velocityX /= 2;
        RicCreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 0), 0);
        PLAYER.facingLeft = (PLAYER.facingLeft + 1) & 1;
        RicSetCrouch(3, PLAYER.velocityX);
        g_api.PlaySfx(SFX_STOMP_SOFT_A);
        return;
    }

    if (g_Player.pl_vram_flag & 0xC) {
        PLAYER.velocityX = 0;
    }

    if (PLAYER.velocityX < 0) {
        if (g_Player.padPressed & PAD_RIGHT) {
            RicDecelerateX(0x2000);
        }
        if ((PLAYER.velocityX > (s32)0xFFFD0000) ||
            (g_Player.pl_vram_flag & 8)) {
            PLAYER.velocityX /= 2;
            PLAYER.facingLeft = (PLAYER.facingLeft + 1) & 1;
            RicSetAnimation(D_80155788);
            g_Player.unk44 = 0xA;
            PLAYER.step_s = 2;
            PLAYER.step = PL_S_JUMP;
        }
    }

    if (PLAYER.velocityX > 0) {
        if (g_Player.padPressed & PAD_LEFT) {
            RicDecelerateX(0x2000);
        }
        if ((PLAYER.velocityX <= 0x2FFFF) || (g_Player.pl_vram_flag & 4)) {
            PLAYER.velocityX /= 2;
            PLAYER.facingLeft = (PLAYER.facingLeft + 1) & 1;
            RicSetAnimation(D_80155788);
            g_Player.unk44 = 0xA;
            PLAYER.step_s = 2;
            PLAYER.step = PL_S_JUMP;
        }
    }
}

void RicHandleBladeDash(void) {
    RicDecelerateX(0x1C00);

    if (PLAYER.animFrameDuration < 0) {
        g_Player.unk46 = 0;
        RicSetStand(0);
    } else if (PLAYER.animFrameIdx >= 0x12 && !(g_Player.pl_vram_flag & 1)) {
        g_Player.unk46 = 0;
        RicSetFall();
    } else {
        if (!(g_GameTimer & 3) && PLAYER.animFrameIdx < 0x12 &&
            g_Player.pl_vram_flag & 1) {
            RicCreateEntFactoryFromEntity(
                g_CurrentEntity, FACTORY(0x200, 24), 0);
        }

        if (PLAYER.animFrameIdx == 18 && PLAYER.animFrameDuration == 1 &&
            (g_Player.pl_vram_flag & 1)) {
            RicCreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0, 0), 0);
        }
    }
}
