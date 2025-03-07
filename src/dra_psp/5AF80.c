// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

void func_8012D3E8(void) {
    byte pad[0x28];
    s32 directionsPressed =
        g_Player.padPressed & (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT);

    if ((g_Player.padTapped & PAD_CROSS) && (D_800B0914 != 4)) {
        func_8012CCE4();
        return;
    }
    if (!(g_Player.pl_vram_flag & 1) && (D_800B0914 != 4)) {
        func_8012CED4();
        return;
    }
    if ((g_Player.padPressed & PAD_DOWN) && (D_800B0914 != 4)) {
        func_8012CFF0();
        return;
    }

    switch (D_800B0914) {
    case 0:
        if (g_Player.padTapped & (PAD_SQUARE | PAD_CIRCLE)) {
            func_8012CC30(0);
            break;
        }
        if (PLAYER.animFrameIdx >= 3) {
            if (PLAYER.animFrameDuration < 0) {
                func_8012CB4C();
                if (!(directionsPressed & (PAD_LEFT | PAD_RIGHT))) {
                    // Evil! This function takes no arguments! This is
                    // why func_8012CA64 had to be commented out of dra.h.
                    func_8012CA64(0);
                    break;
                }
            }
            SetSpeedX(FIX(1));
            break;
        }
        if (PLAYER.animFrameDuration == 1 && PLAYER.animFrameIdx == 2) {
            PLAYER.facingLeft++;
            PLAYER.facingLeft &= 1;
        }
        SetSpeedX(FIX(-1));
        break;

    case 1:
        if (g_Player.padTapped & (PAD_SQUARE | PAD_CIRCLE)) {
            func_8012CC30(0);
            break;
        }
        SetSpeedX(FIX(1));
        if ((PLAYER.facingLeft && (directionsPressed & PAD_RIGHT)) ||
            (!PLAYER.facingLeft && (directionsPressed & PAD_LEFT))) {
            D_800B0914 = 0;
            SetPlayerAnim(0xE1);
        }

        if (!(directionsPressed & (PAD_LEFT | PAD_RIGHT))) {
            func_8012CA64();
        }
        break;
    case 2:
        if ((g_Player.padTapped & (PAD_SQUARE | PAD_CIRCLE)) &&
            (abs(PLAYER.velocityX) < FIX(3))) {
            func_8012CC30(0);
            break;
        }

        if (g_GameTimer % 6 == 0) {
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(69, 1), 0);
        }
        if (PLAYER.velocityX > 0) {
            PLAYER.velocityX += FIX(3.0 / 128);
            if (PLAYER.velocityX > FIX(9)) {
                PLAYER.velocityX = FIX(9);
            }
            if (!IsRelicActive(RELIC_POWER_OF_WOLF) &&
                PLAYER.velocityX > FIX(3)) {
                PLAYER.velocityX = FIX(3);
            }
        }
        if (PLAYER.velocityX < 0) {
            PLAYER.velocityX -= FIX(3.0 / 128);
            if (PLAYER.velocityX < FIX(-9)) {
                PLAYER.velocityX = FIX(-9);
            }
            // @bug The end of this should be FIX(-3) since we're capping
            // the negative velocity. This is weird and could be useful for
            // someone! Namely, if velocity is less than 0 (which was already
            // checked) then you will instantly accelerate up to -3.
            if (!IsRelicActive(RELIC_POWER_OF_WOLF) &&
                PLAYER.velocityX < FIX(3)) {
                PLAYER.velocityX = FIX(-3);
            }
        }
        if (((g_Player.pl_vram_flag & 4) && PLAYER.velocityX > FIX(5.5)) ||
            ((g_Player.pl_vram_flag & 8) && PLAYER.velocityX < FIX(-5.5))) {
            func_8012D28C(1);
            break;
        }
        if (((g_Player.pl_vram_flag & 4) && PLAYER.velocityX > FIX(4)) ||
            ((g_Player.pl_vram_flag & 8) && PLAYER.velocityX < FIX(-5.5))) {
            func_8012D28C(0);
            break;
        }
        if ((g_Player.pl_vram_flag & 4) && PLAYER.velocityX > 0 ||
            (g_Player.pl_vram_flag & 8) && PLAYER.velocityX < 0 ||
            (directionsPressed & (PAD_LEFT | PAD_RIGHT)) == 0) {
            PLAYER.ext.player.anim = 0xE0;
            // Set the state to 3, and the timer to 24. Note that in case 3,
            // this decrements.
            D_800B0914 = 3;
            D_800B091C = 24;
            break;
        }

        if (PLAYER.facingLeft) {
            if (((g_Player.unk04 & 0xF001) == 1) &&
                ((D_80138438 & 0xF001) == 0xC001)) {
                func_8012CCE4();
                PLAYER.velocityY /= 4;
            }
            if (((g_Player.unk04 & 0xF001) == 0x8001) &&
                ((D_80138438 & 0xF001) == 1)) {
                func_8012CCE4();
                PLAYER.velocityY /= 2;
            }
        } else {
            if (((g_Player.unk04 & 0xF001) == 1) &&
                ((D_80138438 & 0xF001) == 0x8001)) {
                func_8012CCE4();
                PLAYER.velocityY /= 4;
            }
            if (((g_Player.unk04 & 0xF001) == 0xC001) &&
                ((D_80138438 & 0xF001) == 1)) {
                func_8012CCE4();
                PLAYER.velocityY /= 2;
            }
        }
        break;
    case 3:
        if ((g_Player.padTapped & (PAD_SQUARE | PAD_CIRCLE)) &&
            (abs(PLAYER.velocityX) < FIX(3))) {
            func_8012CC30(0);
            break;
        }
        if (abs(PLAYER.velocityX) > FIX(1)) {
            DecelerateX(0x2000);
        }
        if ((PLAYER.facingLeft && (directionsPressed & PAD_RIGHT)) ||
            (!PLAYER.facingLeft && (directionsPressed & PAD_LEFT))) {
            D_800B0914 = 0;
            SetPlayerAnim(0xE1);
        }

        if (--D_800B091C == 0) {
            D_800B0914 = 1;
            D_8013842C = 0xC;
        }
        break;
    case 4:
        DecelerateX(0x400);
        if (!(g_GameTimer % 2)) {
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(69, 1), 0);
        }
        if (PLAYER.animFrameDuration >= 0) {
            break;
        }
        if (((g_Player.padPressed & PAD_RIGHT) && !PLAYER.facingLeft) ||
            ((g_Player.padPressed & PAD_LEFT) && PLAYER.facingLeft)) {
            SetPlayerAnim(0xE2);
            D_800B0914 = 2;
            if (abs(PLAYER.velocityX) < FIX(2)) {
                SetSpeedX(FIX(2));
                break;
            }
        } else {
            func_8012CA64();
            PLAYER.velocityX = 0;
        }
        break;
    }
}

void func_8012DBBC(void) {
    s32 vel_boost;

    if (g_Player.timers[5] && (g_Player.padTapped & PAD_CROSS)) {
        func_8012CCE4();
        return;
    }
    if ((PLAYER.facingLeft && !(g_Player.padPressed & PAD_LEFT)) ||
        (!PLAYER.facingLeft && !(g_Player.padPressed & PAD_RIGHT))) {
        DecelerateX(FIX(4.0 / 128));
    }
    if (g_Player.pl_vram_flag & 1) {
        if (D_800B0914 == 1) {
            PLAYER.step_s = 2;
            D_800B0914 = 2;
            SetPlayerAnim(0xE2);
        } else if (PLAYER.velocityY > FIX(6.875)) {
            PLAYER.step_s = 3;
            D_800B0914 = 3;
            SetPlayerAnim(0xE5);
            CreateEntFactoryFromEntity(g_CurrentEntity, 0, 0);
        } else {
            func_8012CA64();
        }
        PLAYER.velocityY = 0;
        PlaySfx(SFX_STOMP_SOFT_B);
        return;
    }
    if (g_Player.padTapped & (PAD_SQUARE | PAD_CIRCLE)) {
        func_8012CC30(1);
    }
    switch (D_800B0914) {
    case 0:
        CheckMoveDirection();
        break;
    case 1:
        if (((g_Player.pl_vram_flag & 4) && PLAYER.velocityX > FIX(5.5)) ||
            ((g_Player.pl_vram_flag & 8) && PLAYER.velocityX < FIX(-5.5))) {
            func_8012D28C(1);
            return;
        }
        if (((g_Player.pl_vram_flag & 4) && PLAYER.velocityX > FIX(4)) ||
            ((g_Player.pl_vram_flag & 8) && PLAYER.velocityX < FIX(-5.5))) {
            func_8012D28C(0);
            return;
        }
        if (((g_Player.pl_vram_flag & 4) && (PLAYER.velocityX > FIX(2.5))) ||
            ((g_Player.pl_vram_flag & 8) && (PLAYER.velocityX < FIX(-2.5)))) {
            DecelerateX(FIX(0.125));
        }
        if (PLAYER.animFrameIdx == 3) {
            PLAYER.animFrameDuration = 6;
        }
    }
    vel_boost = FIX(20.0 / 128);
    if (D_80097448[0] > 12) {
        vel_boost /= 4;
    }
    PLAYER.velocityY += vel_boost;
    if (PLAYER.velocityY > FIX(7)) {
        PLAYER.velocityY = FIX(7);
    }
}

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_8012DF04);

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_8012E040);

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_8012E550);

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_8012E7A4);

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_8012E9C0);

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_8012EAD0);

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_8012ED30);

void func_8012EF2C(void) {
    s32 i;
    s32 xSpeed;
    s32 var_s0;

    PLAYER.palette = 0x104;
    PLAYER.drawMode = DRAW_DEFAULT;
#if defined(VERSION_US)
    PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter - 2;
#endif
    if (WolfFormFinished()) {
        return;
    }
    if (D_8013842C != 0) {
        D_8013842C--;
    }
    if (D_80138440 != 0) {
        D_80138440--;
    }
    D_80138444 = 0;
    func_8012C97C();
    D_800B0920 = 14;
    switch (PLAYER.step_s) {
    case 0:
        func_8012E7A4();
        break;
    case 1:
        func_8012D024();
        break;
    case 2:
        func_8012D3E8();
        break;
    case 3:
        func_8012E550();
        break;
    case 4:
        func_8012E040();
        break;
    case 5:
        func_8012DBBC();
        break;
    case 7:
        func_8012D178();
        break;
    case 6:
        func_8012DF04();
        break;
    case 8:
        func_8012E9C0();
        break;
    case 9:
        func_8012ED30();
    }
    D_80138438 = g_Player.unk04;
    for (i = 0; i < 8; i++) {
        var_s0 = 4;
        xSpeed = abs(PLAYER.velocityX);
        if (xSpeed >= FIX(4)) {
            var_s0--;
        }
        if (xSpeed >= FIX(5)) {
            var_s0--;
        }
        if (xSpeed >= FIX(6)) {
            var_s0--;
        }
        // Might be misusing D_800AFFB8 here
        D_800AFFB8[i * 2] = var_s0;
    }
    if (D_80138430 < 0x600) {
        D_80138430 = 0x600;
    }
    if (D_80138430 > 0xA00) {
        D_80138430 = 0xA00;
    }
#if defined(VERSION_US)
    PLAYER.zPriority = g_unkGraphicsStruct.g_zEntityCenter - 2;
#endif
}

// func_8012F178
INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_psp_09139B50);
// func_8012F83C
INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_psp_0913A3A0);

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_8012F894);

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_80130264);

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_80130618);

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_801309B4);

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_80130E94);

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", func_8013136C);

INCLUDE_ASM("dra_psp/psp/dra_psp/5AF80", EntityGiantSpinningCross);
