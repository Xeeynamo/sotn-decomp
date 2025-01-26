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
        if (PLAYER.velocityY < 0x6000 && -0x2000 < PLAYER.velocityY &&
            !(g_Player.unk44 & 0x20) && g_Player.padPressed & PAD_CROSS) {
            YAccel = FIX(22.0 / 128 / 5);
        } else {
            YAccel = FIX(22.0 / 128);
        }
    }

    if (branchFlags & 0x200) {
        if (PLAYER.velocityY < 0x6000 && -0x2000 < PLAYER.velocityY) {
            YAccel = FIX(11.0 / 128);
        } else {
            YAccel = FIX(22.0 / 128);
        }
    }

    if (D_80097448[0] > 0x28) {
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
                    func_8010E570(0);
                    func_8010FAF4();
                    PlaySfx(SFX_STOMP_SOFT_B, SFX_arg, 0);
                    return 1;
                }

                if (PLAYER.velocityY > FIX(6.875)) {
                    func_8010E470(1, 0);
                    PlaySfxVolPan(SFX_STOMP_HARD_B);
                    CreateEntFactoryFromEntity(g_CurrentEntity, 0, 0);
                } else {
                    if (g_Player.unk44 & 0x10) {
                        func_8010E6AC(1);
                    } else {
                        func_8010E570(0);
                    }
                    PlaySfx(SFX_STOMP_SOFT_B, SFX_arg, 0);
                }

                func_8010FAF4();
                return 1;
            }

            if (PLAYER.velocityY > FIX(6.875)) {
                if ((PLAYER.step_s == 112) || (PLAYER.step == 4)) {
                    func_8010E470(3, PLAYER.velocityX / 2);
                } else {
                    func_8010E470(1, 0);
                }
                PlaySfx(SFX_STOMP_HARD_B);
                CreateEntFactoryFromEntity(g_CurrentEntity, 0, 0);
            } else if (g_Player.unk44 & 0x10) {
                func_8010E6AC(1);
                PlaySfx(SFX_STOMP_SOFT_B, SFX_arg, 0);
            } else if (abs(PLAYER.velocityX) > 0x20000) {
                PlaySfx(SFX_STOMP_HARD_B);
                CreateEntFactoryFromEntity(g_CurrentEntity, 0, 0);
                func_8010E570(PLAYER.velocityX);
            } else {
                PlaySfx(SFX_STOMP_SOFT_B, SFX_arg, 0);
                func_8010E570(0);
            }
            return 1;
        }
        if (branchFlags & 0x20000 && g_Player.pl_vram_flag & 1) {
            func_8010E470(3, PLAYER.velocityX);
            PlaySfx(SFX_STOMP_HARD_B);
            CreateEntFactoryFromEntity(g_CurrentEntity, 0, 0);
            return 1;
        }
    }
    if (branchFlags & 4 && !(g_Player.pl_vram_flag & 1)) {
        func_8010E7AC();
        return 1;
    }

    if (branchFlags & 0x1000 &&
        g_Player.padPressed & (PAD_SQUARE | PAD_CIRCLE) &&
        func_8010EDB8() != 0) {
        return 1;
    }

    if (!(g_Player.unk46 & 0x8000)) {
        if (branchFlags & 0x10 && g_Player.padTapped & PAD_CROSS) {
            func_8010E83C(1);
            return 1;
        }

        if (branchFlags & 0x20 && IsRelicActive(RELIC_LEAP_STONE) &&
            g_Player.padTapped & PAD_CROSS && !(g_Player.unk44 & 1)) {
            func_8010E940();
            return 1;
        }

        if (branchFlags & 0x2000 && g_Player.padPressed & PAD_DOWN) {
            func_8010E470(2, 0);
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
