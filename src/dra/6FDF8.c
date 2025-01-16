// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"
#include "dra_bss.h"

bool func_8010FDF8(s32 branchFlags) {
    u8 stackpad[0x28];
    s32 tempYAccel;
    s32 tempTriangle;
    s32 YAccel;

    if (branchFlags & 8 && g_Player.unk46 == 0) {
        CheckMoveDirection();
    }
    YAccel = -((branchFlags & 0x8000) != 0) & 0x2C00;
    if (branchFlags & 0x10000) {
        if (-0x2000 < PLAYER.velocityY && PLAYER.velocityY < 0x6000 &&
            !(g_Player.unk44 & 0x20) && g_Player.padPressed & PAD_CROSS) {
            YAccel = 0x08CC;
        } else {
            YAccel = 0x2C00;
        }
    }

    if (branchFlags & 0x200) {
        if (-0x2000 < PLAYER.velocityY && PLAYER.velocityY < 0x6000) {
            YAccel = 0x1600;
        } else {
            YAccel = 0x2C00;
        }
    }

    if (D_80097448[0] >= 0x29) {
        if (YAccel < 0) {
            tempYAccel = YAccel + 3;
        } else {
            tempYAccel = YAccel;
        }
        YAccel = (tempYAccel) >> 2;
    }

    PLAYER.velocityY += YAccel;

    if (PLAYER.velocityY > 0x70000) {
        PLAYER.velocityY = 0x70000;
    }
    if ((branchFlags & 0x80) && (g_Player.pl_vram_flag & 2) &&
        (PLAYER.velocityY < -0x10000)) {
        PLAYER.velocityY = -0x10000;
    }

    if (PLAYER.velocityY >= 0) {
        if (branchFlags & 1 && g_Player.pl_vram_flag & 1) {
            if (g_Player.unk46 != 0) {
                if ((g_Player.unk46 & 0x7FFF) == 0xFF) {
                    func_8010E570(0);
                    func_8010FAF4();
                label:
                    PlaySfx(SFX_STOMP_SOFT_B, 0x30, 0);
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
                    PlaySfx(SFX_STOMP_SOFT_B, 0x30, 0);
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
                return 1;
            }

            if (g_Player.unk44 & 0x10) {
                func_8010E6AC(1);
                goto label;
            }

            if (abs(PLAYER.velocityX) > 0x20000) {
                PlaySfx(SFX_STOMP_HARD_B);
                CreateEntFactoryFromEntity(g_CurrentEntity, 0, 0);
                func_8010E570(PLAYER.velocityX);
            } else {
                PlaySfx(SFX_STOMP_SOFT_B, 0x30, 0);
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

    if (g_Player.unk46 & 0x8000) {
        return 0;
    }

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
            tempTriangle = g_Player.padPressed & PAD_TRIANGLE;
        } else {
            tempTriangle = g_Player.padTapped & PAD_TRIANGLE;
        }
        if (tempTriangle != 0) {
            func_8010FD88();
            return 1;
        }
    }
    return 0;
}

s16 D_800ACF6C[] = {0, -8, -16, -22};

s16 func_80110394(void) {
    // Variables that change during execution
    Collider collider;
    s32 yvar;
    s32 collisions;
    s32 i;
    // Values that are set once and never again (but not const for some reason)
    s32 xpos = PLAYER.posX.i.hi;
    s32 xp4 = xpos + 4;
    s32 xm4 = xpos - 4;
    s32 coll_flags = EFFECT_SOLID_FROM_ABOVE | EFFECT_SOLID;

    for (i = 0; i < 4; i++) {
        yvar = PLAYER.posY.i.hi + D_800ACF6C[i];
        CheckCollision(xpos, yvar, &collider, 0);
        collisions = 0;
        if ((collider.effects & coll_flags) == EFFECT_SOLID) {
            collisions += 1;
        }
        CheckCollision(xp4, yvar, &collider, 0);
        if ((collider.effects & coll_flags) == EFFECT_SOLID) {
            collisions += 1;
        }
        CheckCollision(xm4, yvar, &collider, 0);
        if ((collider.effects & coll_flags) == EFFECT_SOLID) {
            collisions += 1;
        }
        if (collisions != 0) {
            return i + 1;
        }
    }
    return 0;
}
