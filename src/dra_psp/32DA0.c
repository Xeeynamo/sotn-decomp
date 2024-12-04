// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"

extern s32 g_WingSmashButtonCounter;
extern s32 g_WingSmashButtonTimer;
extern s32 g_WingSmashTimer;
extern s32 g_BatScreechDone;
extern s32 g_MistTimer; // remaining time in mist transformation
extern s32 D_80138008;
extern s16 D_800AFDA4[];
extern s32 D_8013AECC;

void ControlBatForm(void) {
    Entity* newEntity;
    s32 pressingCross;
    // When we initially move left/right, bat makes a screech sound.
    s32 screechDone;
    s16 x_offset;
    u32 directionsPressed;

    screechDone = 0;
    if (BatFormFinished()) {
        return;
    }
    
    directionsPressed = g_Player.padPressed & (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT);
    pressingCross = g_Player.padPressed & PAD_CROSS;
    PLAYER.drawFlags = FLAG_DRAW_ROTZ;
    PLAYER.rotPivotY = 0;

#if defined(VERSION_HD)
    if (PLAYER.step_s != 3) {
#else defined(VERSION_US)
    // Just to make the curly brackets match at the end of this block
    if (1) {
#endif
        if (CheckWingSmashInput() && (!pressingCross) && (PLAYER.step_s) &&
            (CastSpell(SPELL_WING_SMASH) != 0)) {
            LearnSpell(SPELL_WING_SMASH);
            SetPlayerAnim(0xC6);
            SetSpeedX(FIX(6));
            PLAYER.step_s = 3;
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(44, 0x5c), 0);
            CreateEntFactoryFromEntity(g_CurrentEntity, 67, 0);
            g_WingSmashTimer = 0x40;
#if !defined(VERSION_HD)
            g_WingSmashButtonCounter = 0;
#endif
        } else if ((g_Player.padTapped & PAD_TRIANGLE) &&
                   (PLAYER.step_s == 1 || PLAYER.step_s == 2) &&
                   (IsRelicActive(RELIC_ECHO_OF_BAT))) {
            CreateEntFactoryFromEntity(g_CurrentEntity, 103, 0);
        } else if ((g_Player.padTapped & (PAD_SQUARE | PAD_CIRCLE)) &&
                   (PLAYER.step_s == 1 || PLAYER.step_s == 2) &&
                   (IsRelicActive(RELIC_FIRE_OF_BAT)) && (CastSpell(9) != 0)) {
            SetPlayerAnim(0xC9);
            PLAYER.step_s = 4;
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(44, 5), 0);
        }
    }

    switch (PLAYER.step_s) {
    case 0:
        g_WingSmashButtonCounter = 0;
        PLAYER.rotZ = 0;
        g_Player.unk44 = g_Player.unk46 = g_Player.unk48 = 0;
        if (g_Entities[16].entityId == 0x22) {
            PLAYER.unk5A = 0;
            PLAYER.animSet = 13;
            D_800AFDA4[1] = 6;
            PLAYER.ext.player.anim = 0xCA;
            if (!func_8011203C()) {
                return;
            }
        } else {
            if (g_Player.unk66 == 0) {
#if defined(VERSION_US)
                newEntity = CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(44, 0x20), 0);
                if (newEntity == NULL) {
                    return;
                }
#elif defined(VERSION_HD)
                CreateEntFactoryFromEntity(
                    g_CurrentEntity, FACTORY(44, 0x20), 0);
#endif
                func_8010FAF4();
                g_Player.unk66++;
            }
            DecelerateX(0x480);
            DecelerateY(0x480);
            if (abs(PLAYER.velocityY) > FIX(1.25)) {
                if (PLAYER.velocityY > 0) {
                    PLAYER.velocityY = FIX(1.25);
                } else {
                    PLAYER.velocityY = FIX(-1.25);
                }
            }
            SetPlayerAnim(0xCA);
            D_800AFDA4[1] = PLAYER.animCurFrame;
            PLAYER.palette = 0x810D;
            if (g_Player.unk66 == 1) {
                return;
            }
            if (g_Player.unk66 == 2) {
                PLAYER.unk5A = 0;
                PLAYER.animSet = 0xD;
                D_800AFDA4[1] = 6;
                return;
            }
        }
        SetPlayerAnim(0xC3);
        PLAYER.animFrameDuration = 1;
        PLAYER.animFrameIdx = 2;
        PLAYER.palette = 0x8100;
        CheckMoveDirection();
        PLAYER.step_s++;
        break;
    case 1:
        if ((directionsPressed != 0) && (pressingCross == 0)) {
            if (PLAYER.ext.player.anim == 0xC3) {
                PLAYER.animFrameIdx /= 3;
            }
            PLAYER.step_s += 1;
        } else {
            func_8011690C(0);
            DecelerateX(0x1200);
            DecelerateY(0x1200);
            break;
        }
    case 2:
        // If you're pressing cross, you can't move and inputs are ignored.
        if (pressingCross) {
            directionsPressed = 0;
        }
        switch (directionsPressed) {
        case 0:
        default:
            SetPlayerAnim(0xC3);
            PLAYER.step_s = 1;
            break;
        case PAD_UP:
            PLAYER.ext.player.anim = 0xC2;
            if (PLAYER.velocityY < FIX(-1.25)) {
                DecelerateY(0x1200);
            } else {
                PLAYER.velocityY = FIX(-1.25);
            }
            func_8011690C(-0x80);
            DecelerateX(0x1200);
            break;
        case PAD_DOWN:
            if (g_Player.pl_vram_flag & 1) {
                PLAYER.ext.player.anim = 0xC4;
            } else {
                PLAYER.ext.player.anim = 0xC5;
            }
            if (PLAYER.velocityY > FIX(1.25)) {
                DecelerateY(0x1200);
            } else {
                PLAYER.velocityY = FIX(1.25);
            }
            func_8011690C(0);
            DecelerateX(0x1200);
            break;
        case PAD_RIGHT:
            PLAYER.ext.player.anim = 0xC2;
            PLAYER.facingLeft = 0;
            func_8011690C(0x180);
            if (PLAYER.velocityX > FIX(1.25)) {
                DecelerateX(0x1200);
            } else {
                PLAYER.velocityX = FIX(1.25);
            }
            DecelerateY(0x1200);
            if (!g_BatScreechDone) {
                PlaySfx(SFX_BAT_SCREECH);
            }
            screechDone = 1;
            break;
        case PAD_LEFT:
            PLAYER.ext.player.anim = 0xC2;
            PLAYER.facingLeft = 1;
            func_8011690C(0x180);
            if (PLAYER.velocityX < FIX(-1.25)) {
                DecelerateX(0x1200);
            } else {
                PLAYER.velocityX = FIX(-1.25);
            }
            DecelerateY(0x1200);
            if (!g_BatScreechDone) {
                PlaySfx(SFX_BAT_SCREECH);
            }
            screechDone = 1;
            break;
        case PAD_RIGHT | PAD_UP:
            PLAYER.ext.player.anim = 0xC2;
            PLAYER.facingLeft = 0;
            func_8011690C(0x80);
            if (PLAYER.velocityX > FIX(0.875)) {
                DecelerateX(0xC00);
            } else {
                PLAYER.velocityX = FIX(0.875);
            }
            if (PLAYER.velocityY < FIX(-0.875)) {
                DecelerateY(0xC00);
            } else {
                PLAYER.velocityY = FIX(-0.875);
            }
            break;
        case PAD_LEFT | PAD_UP:
            PLAYER.ext.player.anim = 0xC2;
            PLAYER.facingLeft = 1;
            func_8011690C(0x80);
            if (PLAYER.velocityX < FIX(-0.875)) {
                DecelerateX(0xC00);
            } else {
                PLAYER.velocityX = FIX(-0.875);
            }
            if (PLAYER.velocityY < FIX(-0.875)) {
                DecelerateY(0xC00);
            } else {
                PLAYER.velocityY = FIX(-0.875);
            }
            break;
        case PAD_RIGHT | PAD_DOWN:
            if (g_Player.pl_vram_flag & 1) {
                PLAYER.ext.player.anim = 0xC4;
            } else {
                PLAYER.ext.player.anim = 0xC5;
            }
            PLAYER.facingLeft = 0;
            func_8011690C(0);
            if (PLAYER.velocityX > FIX(0.875)) {
                DecelerateX(0xC00);
            } else {
                PLAYER.velocityX = FIX(0.875);
            }
            if (PLAYER.velocityY > FIX(1.75)) {
                DecelerateY(0xC00);
            } else {
                PLAYER.velocityY = FIX(1.75);
            }
            break;
        case PAD_LEFT | PAD_DOWN:
            if (g_Player.pl_vram_flag & 1) {
                PLAYER.ext.player.anim = 0xC4;
            } else {
                PLAYER.ext.player.anim = 0xC5;
            }
            PLAYER.facingLeft = 1;
            func_8011690C(0);
            if (PLAYER.velocityX < FIX(-0.875)) {
                DecelerateX(0xC00);
            } else {
                PLAYER.velocityX = FIX(-0.875);
            }
            if (PLAYER.velocityY > FIX(1.75)) {
                DecelerateY(0xC00);
            } else {
                PLAYER.velocityY = FIX(1.75);
            }
            break;
        }
        break;
    case 3:
        if (!PLAYER.facingLeft && (g_Player.pl_vram_flag & 4) ||
            PLAYER.facingLeft && (g_Player.pl_vram_flag & 8)) {
            g_Player.padTapped = PAD_R1;
            BatFormFinished();
            func_80102CD8(2);
            PlaySfx(SFX_WALL_DEBRIS_B);
            PLAYER.velocityX = 0;
            g_Player.D_80072EFC = 0x20;
            g_Player.padSim = 0;
            break;
        }
        // When wing smash ends, force an un-transform
        if (--g_WingSmashTimer == 0) {
            g_Player.padTapped = PAD_R1;
            BatFormFinished();
            g_Player.D_80072EFC = 0x20;
            g_Player.padSim = 0;
        } else {
            if (directionsPressed & PAD_UP) {
                PLAYER.velocityY -= FIX(0.125);
                func_8011690C(0x80);
            }
            if (directionsPressed & PAD_DOWN) {
                PLAYER.velocityY += FIX(0.125);
            }
            if (!(directionsPressed & PAD_UP)) {
                func_8011690C(0x180);
            }
            if (!(directionsPressed & (PAD_DOWN | PAD_UP))) {
                DecelerateY(0x2000);
            }
            if (g_Player.pl_vram_flag & 0x800) {
                if (PLAYER.facingLeft && (g_Player.pl_vram_flag & 0x400) ||
                    !PLAYER.facingLeft && !(g_Player.pl_vram_flag & 0x400)) {
                    PLAYER.velocityY = FIX(6);
                }
            }
            if ((g_Player.pl_vram_flag & 0x8000) != 0) {
                if (PLAYER.facingLeft && (g_Player.pl_vram_flag & 0x4000) ||
                    !PLAYER.facingLeft && !(g_Player.pl_vram_flag & 0x4000)) {
                    PLAYER.velocityY = FIX(-6);
                }
            }
            if (PLAYER.velocityY < FIX(-6)) {
                PLAYER.velocityY = FIX(-6);
            }
            if (PLAYER.velocityY > FIX(6)) {
                PLAYER.velocityY = FIX(6);
            }
            if (g_GameTimer % 3 == 0) {
                CreateEntFactoryFromEntity(g_CurrentEntity, 65, 0);
                if (g_Player.pl_vram_flag & 1) {
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(69, 9), 0);
                }
                if (g_Player.pl_vram_flag & 2) {
                    x_offset = 3;
                    if (PLAYER.facingLeft) {
                        x_offset = -x_offset;
                    }
                    PLAYER.posY.i.hi -= 8;
                    PLAYER.posX.i.hi += x_offset;
                    CreateEntFactoryFromEntity(
                        g_CurrentEntity, FACTORY(4, 1), 0);
                    PLAYER.posY.i.hi += 8;
                    PLAYER.posX.i.hi -= x_offset;
                }
            }
        }
        break;
    // Happens when shooting fireball with Fire of Bat
    case 4:
        DecelerateX(FIX(12.0 / 128));
        DecelerateY(FIX(28.0 / 128));
        func_8011690C(0x180);
        if (PLAYER.animFrameDuration < 0) {
            // This actually creates the entity factory to produce the fireball
            CreateEntFactoryFromEntity(g_CurrentEntity, 81, 0);
            SetSpeedX(FIX(-1.5));
            func_8011690C(0);
            SetPlayerAnim(0xC3);
            PLAYER.step_s++;
        }
        break;
    // Finishing up on the fireball
    case 5:
        DecelerateX(FIX(12.0 / 128));
        DecelerateY(FIX(28.0 / 128));
        func_8011690C(0);
        if (PLAYER.ext.player.anim == 0xC4 && PLAYER.animFrameIdx == 8) {
            PLAYER.step_s = 1;
        }
        break;
    }

    if (D_8013AECC != 0) {
        if (PLAYER.velocityX > 0) {
            PLAYER.velocityX = 0;
        }
    }
    if(D_8013AECC != 0){
        if (D_8013AECC > 0) {
            D_8013AECC--;
            g_CurrentEntity->posY.i.hi++;
        } else {
            D_8013AECC++;
            g_CurrentEntity->posY.i.hi--;
        }
    }
    g_BatScreechDone = screechDone;
}


INCLUDE_ASM("dra_psp/psp/dra_psp/32DA0", func_psp_091107E8);

INCLUDE_ASM("dra_psp/psp/dra_psp/32DA0", func_psp_09110B78);

INCLUDE_ASM("dra_psp/psp/dra_psp/32DA0", func_psp_09110E90);

INCLUDE_ASM("dra_psp/psp/dra_psp/32DA0", func_psp_09110FC8);

INCLUDE_ASM("dra_psp/psp/dra_psp/32DA0", func_psp_09111648);
