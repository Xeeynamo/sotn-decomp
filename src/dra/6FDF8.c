// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"
#include "dra_bss.h"

bool func_8010FDF8(s32 branchFlags) {
    u8 stackpad[0x28];
    s32 SFX_arg;
    s32 YAccel;

    if (branchFlags & 8 && g_Player.unk46 == 0) {
        CheckMoveDirection();
    }
    YAccel = 0;
    if (branchFlags & 0x8000) {
        YAccel = FIX(22.0 / 128);
    }
    if (branchFlags & 0x10000) {
        if (PLAYER.velocityY < FIX(3.0 / 8) &&
            FIX(-1.0 / 8) < PLAYER.velocityY && !(g_Player.unk44 & 0x20) &&
            g_Player.padPressed & PAD_CROSS) {
            YAccel = FIX(22.0 / 128 / 5);
        } else {
            YAccel = FIX(22.0 / 128);
        }
    }

    if (branchFlags & 0x200) {
        if (PLAYER.velocityY < FIX(3.0 / 8) &&
            FIX(-1.0 / 8) < PLAYER.velocityY) {
            YAccel = FIX(11.0 / 128);
        } else {
            YAccel = FIX(22.0 / 128);
        }
    }

    if (D_80097448[0] > 40) {
        YAccel = YAccel / 4;
    }

    PLAYER.velocityY += YAccel;

    if (PLAYER.velocityY > FIX(7)) {
        PLAYER.velocityY = FIX(7);
    }
    if ((branchFlags & 0x80) && (g_Player.pl_vram_flag & 2) &&
        (PLAYER.velocityY < FIX(-1))) {
        PLAYER.velocityY = FIX(-1);
    }

    if (PLAYER.velocityY >= 0) {
        SFX_arg = 0x30;
        if (branchFlags & 1 && g_Player.pl_vram_flag & 1) {
            if (g_Player.unk46) {
                if ((g_Player.unk46 & 0x7FFF) == 0xFF) {
                    LandToTheGround(0);
                    DestroyEquippedWeapon();
                    PlaySfx(SFX_STOMP_SOFT_B, SFX_arg, 0);
                    return 1;
                }

                if (PLAYER.velocityY > FIX(6.875)) {
                    ExecuteCrouch(1, 0);
                    PlaySfxVolPan(SFX_STOMP_HARD_B);
                    CreateEntFactoryFromEntity(g_CurrentEntity, 0, 0);
                } else {
                    if (g_Player.unk44 & 0x10) {
                        ExecuteWalk(1);
                    } else {
                        LandToTheGround(0);
                    }
                    PlaySfx(SFX_STOMP_SOFT_B, SFX_arg, 0);
                }

                DestroyEquippedWeapon();
                return 1;
            }

            if (PLAYER.velocityY > FIX(6.875)) {
                if ((PLAYER.step_s == 112) || (PLAYER.step == 4)) {
                    ExecuteCrouch(3, PLAYER.velocityX / 2);
                } else {
                    ExecuteCrouch(1, 0);
                }
                PlaySfx(SFX_STOMP_HARD_B);
                CreateEntFactoryFromEntity(g_CurrentEntity, 0, 0);
            } else if (g_Player.unk44 & 0x10) {
                ExecuteWalk(1);
                PlaySfx(SFX_STOMP_SOFT_B, SFX_arg, 0);
            } else if (abs(PLAYER.velocityX) > FIX(2)) {
                PlaySfx(SFX_STOMP_HARD_B);
                CreateEntFactoryFromEntity(g_CurrentEntity, 0, 0);
                LandToTheGround(PLAYER.velocityX);
            } else {
                PlaySfx(SFX_STOMP_SOFT_B, SFX_arg, 0);
                LandToTheGround(0);
            }
            return 1;
        }
        if (branchFlags & 0x20000 && g_Player.pl_vram_flag & 1) {
            ExecuteCrouch(3, PLAYER.velocityX);
            PlaySfx(SFX_STOMP_HARD_B);
            CreateEntFactoryFromEntity(g_CurrentEntity, 0, 0);
            return 1;
        }
    }
    if (branchFlags & 4 && !(g_Player.pl_vram_flag & 1)) {
        ExecuteFall();
        return 1;
    }

    if (branchFlags & 0x1000 &&
        g_Player.padPressed & (PAD_SQUARE | PAD_CIRCLE) &&
        HandlePlayerAttack() != 0) {
        return 1;
    }

    if (!(g_Player.unk46 & 0x8000)) {
        if (branchFlags & 0x10 && g_Player.padTapped & PAD_CROSS) {
            ExecuteJump(1);
            return 1;
        }

        if (branchFlags & 0x20 && IsRelicActive(RELIC_LEAP_STONE) &&
            g_Player.padTapped & PAD_CROSS && !(g_Player.unk44 & 1)) {
            ExecuteJumpKick();
            return 1;
        }

        if (branchFlags & 0x2000 && g_Player.padPressed & PAD_DOWN) {
            ExecuteCrouch(2, 0);
            return 1;
        }

        if (branchFlags & 0x40000 && PLAYER.ext.player.anim != 0xDB) {
            if (g_Player.unk46 & 0x7FFF) {
                if (g_Player.padPressed & PAD_TRIANGLE) {
                    func_8010FD88();
                    return 1;
                }
            } else {
                if (g_Player.padTapped & PAD_TRIANGLE) {
                    func_8010FD88();
                    return 1;
                }
            }
        }
    }
    return 0;
}
