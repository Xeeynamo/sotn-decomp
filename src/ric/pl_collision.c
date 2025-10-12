// SPDX-License-Identifier: AGPL-3.0-or-later
#include "ric.h"

bool RicCheckInput(s32 checks) {
    s32 velYChange;
    u32 effects;

    if (checks & CHECK_FACING) {
        if (g_Player.unk46 == 0) {
            RicCheckFacing();
        }
    }
    velYChange = 0;
    if (checks & CHECK_GRAVITY_FALL) {
        velYChange = FIX(28.0 / 128);
    }
    if (checks & CHECK_GRAVITY_JUMP) {
        if (PLAYER.velocityY < FIX(3.0 / 8) &&
            PLAYER.velocityY > FIX(-1.0 / 8) && !(g_Player.unk44 & 0x20) &&
            (g_Player.padPressed & PAD_CROSS)) {
            // Note that 5.6 is precisely 1/5 of 28.
            velYChange = FIX(5.6 / 128);
        } else {
            velYChange = FIX(28.0 / 128);
        }
    }
    if (checks & CHECK_GRAVITY_HIT) {
        if (PLAYER.velocityY < FIX(3.0 / 8) &&
            PLAYER.velocityY > FIX(-1.0 / 8)) {
            velYChange = FIX(14.0 / 128);
        } else {
            velYChange = FIX(28.0 / 128);
        }
    }
    if (*D_80097448 > 0x28) {
        velYChange /= 4;
    }
    PLAYER.velocityY += velYChange;
    if (PLAYER.velocityY > FIX(7)) {
        PLAYER.velocityY = FIX(7);
    }
    if ((checks & CHECK_80) && (g_Player.vram_flag & TOUCHING_CEILING) &&
        (PLAYER.velocityY < FIX(-1))) {
        PLAYER.velocityY = FIX(-1);
    }
    if (PLAYER.velocityY >= 0) {
        if ((checks & CHECK_GROUND) && (g_Player.vram_flag & TOUCHING_GROUND)) {
            switch (g_Player.unk46) {
            case 0:
            default:
                if (g_Player.unk44 & 8) {
                    RicSetCrouch(3, PLAYER.velocityX);
                    g_api.PlaySfx(SFX_STOMP_SOFT_A);
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                    return true;
                }
                if (PLAYER.velocityY > FIX(6.875)) {
                    RicSetCrouch(1, 0);
                    g_api.PlaySfx(SFX_STOMP_SOFT_A);
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                } else if (g_Player.padPressed & (PAD_LEFT | PAD_RIGHT)) {
                    if (g_Player.unk44 & 0x10
#if defined(VERSION_US)
                        && !g_Player.unk7A
#endif
                    ) {
                        RicSetRun();
                    } else {
                        RicSetWalk(0);
                    }
                } else {
                    RicSetStand(0);
                }
                return true;
            case 1:
                if (PLAYER.velocityY > FIX(6.875)) {
                    PLAYER.step = PL_S_CROUCH;
                    PLAYER.anim = D_801555A8;
                    g_api.PlaySfx(SFX_STOMP_HARD_B);
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                } else {
                    PLAYER.step = PL_S_STAND;
                    PLAYER.anim = D_80155588;
                    if (!(g_Player.unk44 & 8)) {
                        PLAYER.velocityX = 0;
                    } else {
                        RicCreateEntFactoryFromEntity(
                            g_CurrentEntity, BP_SKID_SMOKE, 0);
                        g_api.PlaySfx(SFX_STOMP_HARD_B);
                    }
                }
                PLAYER.velocityY = 0;
                g_Player.unk44 = 0;
                return true;
            case 2:
                if (PLAYER.velocityY > FIX(6.875)) {
                    PLAYER.step = PL_S_CROUCH;
                    PLAYER.anim = D_80155738;
                    g_api.PlaySfx(SFX_STOMP_SOFT_A);
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                } else {
                    PLAYER.step = PL_S_STAND;
                    PLAYER.anim = ric_anim_brandish_whip;
                    if (!(g_Player.unk44 & 8)) {
                        PLAYER.velocityX = 0;
                    } else {
                        RicCreateEntFactoryFromEntity(
                            g_CurrentEntity, BP_SKID_SMOKE, 0);
                        g_api.PlaySfx(SFX_STOMP_SOFT_A);
                    }
                }
                PLAYER.velocityY = 0;
                g_Player.unk44 = 0;
                return true;
            case 3:
                if ((PLAYER.velocityY > FIX(6.875)) || (g_Player.unk44 & 8)) {
                    g_api.PlaySfx(SFX_STOMP_SOFT_A);
                    RicCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                }
                PLAYER.velocityY = 0;
                if (!(g_Player.unk44 & 8)) {
                    PLAYER.velocityX = 0;
                }
                PLAYER.step = PL_S_STAND;
                PLAYER.anim = D_801555E8;
                g_Player.unk44 = 0;
                return true;
            }
        } else if (checks & CHECK_GROUND_AFTER_HIT &&
                   (g_Player.vram_flag & TOUCHING_GROUND)) {
            RicSetCrouch(1, PLAYER.velocityX);
            g_api.PlaySfx(SFX_STOMP_SOFT_A);
            if (g_Player.unk5C && (g_Status.hp < 2)) {
                RicSetDeadPrologue();
                return true;
            } else {
                RicCreateEntFactoryFromEntity(
                    g_CurrentEntity, BP_SKID_SMOKE, 0);
            }
            return true;
        }
    }
    if (checks & CHECK_FALL && !(g_Player.vram_flag & TOUCHING_GROUND)) {
        if (g_Player.unk46) {
            if (g_Player.unk46 == 1) {
                PLAYER.step_s = 0x40;
                PLAYER.step = PL_S_JUMP;
                PLAYER.anim = D_801555C8;
                return true;
            }
            if (g_Player.unk46 == 2) {
                PLAYER.step_s = 0x41;
                PLAYER.step = PL_S_JUMP;
                PLAYER.anim = D_801555C8;
                return true;
            }
            if (g_Player.unk46 == 3) {
                PLAYER.step_s = 0x42;
                PLAYER.step = PL_S_JUMP;
                PLAYER.anim = D_80155638;
                return true;
            }
        } else {
            RicSetFall();
            return true;
        }
    }
    if (g_Player.unk46) {
        return false;
    }
    if (checks & CHECK_CRASH && (g_Player.padTapped & PAD_TRIANGLE) &&
        RicDoCrash()) {
        return true;
    }
    if (checks & CHECK_SLIDE &&
        !(PLAYER.facingLeft == 0 &&
          g_Player.colFloor[2].effects & EFFECT_UNK_8000) &&
        !(PLAYER.facingLeft &&
          g_Player.colFloor[3].effects & EFFECT_UNK_8000) &&
        (PLAYER.posX.i.hi < (u8)-4 || PLAYER.facingLeft != 0) &&
        (PLAYER.posX.i.hi >= 5 || !PLAYER.facingLeft) &&
        g_Player.padPressed & PAD_DOWN && g_Player.padTapped & PAD_CROSS) {
        RicSetSlide();
        return true;
    }
    if (checks & CHECK_JUMP && (g_Player.padTapped & PAD_CROSS)) {
        RicSetJump();
        return true;
    }
    if (checks & CHECK_ATTACK && (g_Player.padTapped & PAD_SQUARE) &&
        RicDoAttack()) {
        return true;
    }
    if (checks & CHECK_CROUCH && (g_Player.padPressed & PAD_DOWN)) {
        RicSetCrouch(2, 0);
        return true;
    }
    return false;
}

static s32 debug_wait_info_timer;
static void DebugShowWaitInfo(const char* msg) {
    g_CurrentBuffer = g_CurrentBuffer->next;
    FntPrint(msg);
    if (debug_wait_info_timer++ & 4) {
        FntPrint("\no\n");
    }
    DrawSync(0);
    VSync(0);
    PutDrawEnv(&g_CurrentBuffer->draw);
    PutDispEnv(&g_CurrentBuffer->disp);
    FntFlush(-1);
}

static void DebugInputWait(const char* msg) {
    while (PadRead(0))
        DebugShowWaitInfo(msg);
    while (PadRead(0) == 0)
        DebugShowWaitInfo(msg);
}

void func_8015E484(void) {
    s32 i;
    s32 collision = 0;
    s16 startingPosY = PLAYER.posY.i.hi;

    if (g_Player.vram_flag & TOUCHING_GROUND || g_RicDebug.enabled ||
        g_Player.unk78 == 1) {
        return;
    }
    if (PLAYER.posY.i.hi < 0x30) {
        PLAYER.posY.i.hi -= 0x10;
        while (true) {
            for (i = 0; i < NUM_HORIZONTAL_SENSORS; ++i) {
                g_api.CheckCollision(
                    (s16)(PLAYER.posX.i.hi + g_RicSensorsFloor[i].x),
                    (s16)(PLAYER.posY.i.hi + g_RicSensorsFloor[i].y),
                    &g_Player.colFloor[i], 0);
            }

            if ((g_Player.colFloor[1].effects &
                 (EFFECT_SOLID_FROM_BELOW | EFFECT_SOLID)) == 1 ||
                (g_Player.colFloor[2].effects &
                 (EFFECT_SOLID_FROM_BELOW | EFFECT_SOLID)) == 1 ||
                (g_Player.colFloor[3].effects &
                 (EFFECT_SOLID_FROM_BELOW | EFFECT_SOLID)) == 1) {
                PLAYER.velocityY = 0;
                PLAYER.posY.i.hi -= 1;
                collision = 1;
            } else if (collision == 0) {
                PLAYER.posY.i.hi += 8;
                if (PLAYER.posY.i.hi >= 0x30) {
                    PLAYER.posY.i.hi = startingPosY;
                    return;
                }
            } else {
                return;
            }
        }

    } else if (PLAYER.posY.i.hi >= 0xB1) {
        PLAYER.posY.i.hi += 0x20;
        while (true) {
            for (i = 0; i < NUM_HORIZONTAL_SENSORS; ++i) {
                g_api.CheckCollision(
                    (s16)(PLAYER.posX.i.hi + g_RicSensorsCeiling[i].x),
                    (s16)(PLAYER.posY.i.hi + g_RicSensorsCeiling[i].y),
                    &g_Player.colCeiling[i], 0);
            }

            if ((g_Player.colCeiling[1].effects &
                 (EFFECT_SOLID_FROM_ABOVE | EFFECT_SOLID)) == 1 ||
                (g_Player.colCeiling[2].effects &
                 (EFFECT_SOLID_FROM_ABOVE | EFFECT_SOLID)) == 1 ||
                (g_Player.colCeiling[3].effects &
                 (EFFECT_SOLID_FROM_ABOVE | EFFECT_SOLID)) == 1) {
                PLAYER.velocityY = 0;
                PLAYER.posY.i.hi += 1;
                collision = 1;
            } else if (collision != 0) {
                PLAYER.posY.i.hi -= 1;
                return;
            } else {
                PLAYER.posY.i.hi -= 8;
                if (PLAYER.posY.i.hi < 0xB1) {
                    PLAYER.posY.i.hi = startingPosY;
                    return;
                }
            }
        }
    }
}

void RicGetPlayerSensor(Collider* col) {
    col->unk14 = g_RicSensorsWall[0].x;
    col->unk1C = g_RicSensorsWall[0].y;
    col->unk18 = g_RicSensorsFloor[1].y - 1;
    col->unk20 = g_RicSensorsCeiling[1].y + 1;
}

void RicCheckFloor(void) {
    Collider col;
    s32 i;
    s32 effects;
    s32 effects2;
    s16 yCheck;
    s16 xCheck;
    s16* x;
    s16* y;
    s32* vramFlag;
    s32 vramApply;
    s16 xMod;
    s32 xMax;
    s16 yMod;

    yMod = 0;
    i = 0;
    y = &PLAYER.posY.i.hi;
    x = &PLAYER.posX.i.hi;
    vramFlag = &g_Player.vram_flag;

    if (g_unkGraphicsStruct.unk18) {
        *vramFlag = 1;
        return;
    }
    if (PLAYER.velocityY == 0 && g_Player.unk04 & 1) {
        yMod = 4;
    } else {
        i = 1;
    }
    for (; i < NUM_HORIZONTAL_SENSORS; i++, yMod = 0) {
        if (g_Player.colFloor[i].effects & EFFECT_SOLID_FROM_BELOW) {
            continue;
        }
        if (!(g_Player.colFloor[i].effects & EFFECT_UNK_0002 ||
              PLAYER.velocityY >= 0 ||
              (PLAYER.step == PL_S_SLIDE_KICK &&
               g_Player.colFloor[i].effects & EFFECT_UNK_8000))) {
            continue;
        }
        effects2 = g_Player.colFloor[i].effects &
                   (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_SOLID);
        if ((effects2 == EFFECT_SOLID) || (effects2 & EFFECT_UNK_0800)) {
            xCheck = *x + g_RicSensorsFloor[i].x;
            yCheck = *y + g_RicSensorsFloor[i].y;
            yCheck += g_Player.colFloor[i].unk18 - 1;
            g_api.CheckCollision(xCheck, yCheck, &col, 0);
            effects = col.effects;
            if (!(effects & EFFECT_SOLID)) {
                if (g_Player.colFloor[i].effects != EFFECT_SOLID ||
                    PLAYER.velocityY >= 0 || PLAYER.step == PL_S_SLIDE_KICK) {
                    if (effects2 & EFFECT_UNK_0800) {
                        *y += yMod + g_Player.colFloor[i].unk8;
                    } else {
                        *y += yMod + g_Player.colFloor[i].unk18;
                    }
                    *vramFlag |= 1;
                    return;
                }
                continue;
            }
            if ((effects &
                 (EFFECT_UNK_8000 | EFFECT_UNK_0002 | EFFECT_SOLID)) ==
                (EFFECT_UNK_8000 | EFFECT_SOLID)) {
                if (i < 2) {
                    *vramFlag |= (effects & (EFFECT_UNK_4000 | EFFECT_UNK_2000 |
                                             EFFECT_UNK_1000)) +
                                 (EFFECT_UNK_8000 | EFFECT_SOLID);
                    *y += g_Player.colFloor[i].unk8 + col.unk18 - 1 + yMod;
                    return;
                }
                if (i == 2 && (effects & (EFFECT_UNK_8000 | EFFECT_UNK_4000 |
                                          EFFECT_SOLID)) ==
                                  (EFFECT_UNK_8000 | EFFECT_SOLID)) {
                    g_Player.colFloor[2].effects = effects;
                    g_Player.colFloor[2].unk10 = g_Player.colFloor[2].unk8;
                }
                if (i == 3 &&
                    (effects &
                     (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_SOLID)) ==
                        (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_SOLID)) {
                    g_Player.colFloor[3].effects = effects;
                    g_Player.colFloor[3].unk10 = g_Player.colFloor[3].unk8;
                }
            }
        }
        if (effects2 == (EFFECT_UNK_8000 | EFFECT_SOLID) && i < 2) {
            *vramFlag |= g_Player.colFloor[i].effects &
                         (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_2000 |
                          EFFECT_UNK_1000 | EFFECT_SOLID);
            *y += yMod + g_Player.colFloor[i].unk18;
            return;
        }
    }
    if (g_Player.colFloor[1].effects & EFFECT_QUICKSAND) {
        *vramFlag |= EFFECT_SOLID | EFFECT_MIST_ONLY;
        if (!(g_Timer & 3)) {
            (*y)++;
        }
        return;
    }
    if (g_Player.colFloor[1].effects & EFFECT_WATER) {
        *vramFlag |= EFFECT_SOLID_FROM_BELOW;
    }
    if (PLAYER.velocityY < 0) {
        return;
    }
    xCheck = *x + g_RicSensorsFloor[0].x;
    yCheck = *y + g_RicSensorsFloor[0].y + 10;
    g_api.CheckCollision(xCheck, yCheck, &col, 0);
    if ((col.effects & (EFFECT_UNK_8000 | EFFECT_SOLID)) != EFFECT_NONE) {
        return;
    }

    for (i = 2; i < NUM_HORIZONTAL_SENSORS; i++) {
        if ((g_Player.colFloor[3].effects & EFFECT_UNK_8000) &&
            (g_Player.colFloor[2].effects & EFFECT_UNK_8000)) {
            return;
        }
        effects2 = g_Player.colFloor[i].effects;
        vramApply = ((effects2 &
                      (EFFECT_UNK_4000 | EFFECT_UNK_2000 | EFFECT_UNK_1000)) +
                     (EFFECT_UNK_8000 | EFFECT_SOLID));
        if (!(effects2 & EFFECT_UNK_8000)) {
            continue;
        }
        if (i == 2) {
            effects = EFFECT_UNK_4000;
            xMod = g_Player.colFloor[2].unk4;
            xMax = xMod + 8;
        } else {
            effects = 0;
            xMod = g_Player.colFloor[3].unkC;
            xMax = 8 - xMod;
        }
        if ((effects2 & EFFECT_UNK_4000) == effects) {
            xCheck = xMod + (*x + g_RicSensorsFloor[i].x);
            yCheck = *y + g_RicSensorsFloor[i].y;
            g_api.CheckCollision(xCheck, yCheck, &col, 0);
            if (col.effects & EFFECT_SOLID) {
                *y += col.unk18;
                *vramFlag |= vramApply;
                return;
            }
            continue;
        }
        if (xMax <= 0) {
            continue;
        }
        if (!(effects2 & 1)) {
            continue;
        }
        xCheck = *x + g_RicSensorsFloor[i].x + xMod;
        yCheck = *y + g_RicSensorsFloor[i].y + g_Player.colFloor[i].unk10;
        g_api.CheckCollision(xCheck, yCheck, &col, 0);
        if (col.effects & EFFECT_SOLID) {
            *y += (col.unk18 + g_Player.colFloor[i].unk10);
            *vramFlag |= vramApply;
            return;
        }
    }
}

void RicCheckCeiling(void) {
    Collider col;
    s32 i;
    u32 effects;
    u32 effects2;
    s16 xCheck;
    s16 yCheck;
    s16* x;
    s16* y;
    s32* vramFlag;
    s32 vramApply;
    s16 xMod;
    s32 xMax;

    i = 1;
    y = &PLAYER.posY.i.hi;
    x = &PLAYER.posX.i.hi;
    vramFlag = &g_Player.vram_flag;

    if (g_unkGraphicsStruct.unk18) {
        return;
    }
    for (; i < NUM_HORIZONTAL_SENSORS; i++) {
        if (g_Player.colCeiling[i].effects & EFFECT_SOLID_FROM_ABOVE) {
            continue;
        }
        effects2 = g_Player.colCeiling[i].effects &
                   (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_SOLID);
        if ((effects2 == EFFECT_SOLID) || (effects2 & EFFECT_UNK_8000)) {
            if ((PLAYER.step == PL_S_SLIDE_KICK || PLAYER.step == PL_S_SLIDE) &&
                !(effects2 & EFFECT_SOLID)) {
                continue;
            }
            xCheck = *x + g_RicSensorsCeiling[i].x;
            yCheck = *y + g_RicSensorsCeiling[i].y +
                     g_Player.colCeiling[i].unk10 + 1;
            g_api.CheckCollision(xCheck, yCheck, &col, 0);
            effects = col.effects;
            if (!(effects & EFFECT_SOLID)) {
                if (g_Player.colCeiling[i].effects != EFFECT_SOLID ||
                    PLAYER.velocityY <= 0) {
                    *vramFlag |= 2;
                    if (!(*vramFlag & 1) &&
                        ((g_Player.unk04 &
                          (EFFECT_SOLID_FROM_ABOVE | EFFECT_SOLID)) !=
                         (EFFECT_SOLID_FROM_ABOVE | EFFECT_SOLID))) {
                        if (g_Player.colCeiling[i].effects & EFFECT_UNK_8000) {
                            *y += g_Player.colCeiling[i].unk10;
                        } else {
                            *y += g_Player.colCeiling[i].unk20;
                        }
                    }
                    return;
                }
                continue;
            }
            if ((effects &
                 (EFFECT_UNK_0800 | EFFECT_UNK_0002 | EFFECT_SOLID)) ==
                (EFFECT_UNK_0800 | EFFECT_SOLID)) {
                if (i < 2) {
                    *vramFlag |=
                        (EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                         ((effects >> 4) & (EFFECT_UNK_0400 | EFFECT_UNK_0200 |
                                            EFFECT_UNK_0100)));
                    if (!(*vramFlag & 1)) {
                        *y += 1 + (g_Player.colCeiling[i].unk10 + col.unk20);
                    }
                    return;
                }
                if (i == 2 && (effects & (EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                                          EFFECT_SOLID)) ==
                                  (EFFECT_UNK_0800 | EFFECT_SOLID)) {
                    g_Player.colFloor[2].effects = effects;
                    g_Player.colFloor[2].unk8 = g_Player.colFloor[2].unk10;
                }
                if (i == 3 &&
                    (effects &
                     (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_SOLID)) ==
                        (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_SOLID)) {
                    g_Player.colFloor[3].effects = effects;
                    g_Player.colFloor[3].unk8 = g_Player.colFloor[3].unk10;
                }
            }
            if ((effects & EFFECT_UNK_0800) == EFFECT_NONE) {
                *vramFlag |=
                    (EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                     ((effects >> 4) &
                      (EFFECT_UNK_0400 | EFFECT_UNK_0200 | EFFECT_UNK_0100)));
                if (!(*vramFlag & 1)) {
                    *y += 1 + (g_Player.colCeiling[i].unk10 + col.unk20);
                }
                return;
            }
        }
        if ((effects2 == (EFFECT_UNK_0800 | EFFECT_SOLID)) && i < 2) {
            *vramFlag |=
                (EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                 ((g_Player.colCeiling[i].effects >> 4) &
                  (EFFECT_UNK_0400 | EFFECT_UNK_0200 | EFFECT_UNK_0100)));
            if (!(*vramFlag & 1)) {
                *y += g_Player.colCeiling[i].unk20;
            }
            return;
        }
    }
    if (PLAYER.velocityY > 0) {
        return;
    }
    xCheck = *x + g_RicSensorsCeiling[0].x;
    yCheck = (*y + g_RicSensorsCeiling[0].y) - 10;
    g_api.CheckCollision(xCheck, yCheck, &col, 0);
    if ((col.effects & EFFECT_SOLID) != EFFECT_NONE) {
        return;
    }
    for (i = 2; i < NUM_HORIZONTAL_SENSORS; i++) {
        if ((g_Player.colCeiling[3].effects & EFFECT_UNK_0800) &&
            (g_Player.colCeiling[2].effects & EFFECT_UNK_0800)) {
            return;
        }
        effects2 = g_Player.colCeiling[i].effects;
        vramApply = ((effects2 >> 4) &
                     (EFFECT_UNK_0400 | EFFECT_UNK_0200 | EFFECT_UNK_0100)) +
                    (EFFECT_UNK_0800 | EFFECT_UNK_0002);
        if (!(effects2 & EFFECT_UNK_0800)) {
            continue;
        }
        if (i == 2) {
            effects = EFFECT_UNK_4000;
            xMod = g_Player.colCeiling[2].unk4;
            xMax = xMod + 8;
        } else {
            effects = 0;
            xMod = g_Player.colCeiling[3].unkC;
            xMax = 8 - xMod;
        }
        if ((effects2 & EFFECT_UNK_4000) == effects) {
            xCheck = xMod + (*x + g_RicSensorsCeiling[i].x);
            yCheck = *y + g_RicSensorsCeiling[i].y;
            g_api.CheckCollision(xCheck, yCheck, &col, 0);
            if (col.effects & EFFECT_SOLID) {
                *vramFlag |= vramApply;
                if (!(*vramFlag & 1)) {
                    *y += col.unk20;
                }
                return;
            }
            continue;
        }
        if (xMax <= 0) {
            continue;
        }
        if (!(effects2 & 1)) {
            continue;
        }
        xCheck = *x + g_RicSensorsCeiling[i].x + xMod;
        yCheck = *y + g_RicSensorsCeiling[i].y + g_Player.colCeiling[i].unk8;
        g_api.CheckCollision(xCheck, yCheck, &col, 0);
        if (col.effects & EFFECT_SOLID) {
            if (!(*vramFlag & 1)) {
                *y += col.unk20 + g_Player.colCeiling[i].unk8;
            }
            *vramFlag |= vramApply;
            return;
        }
    }
}

void RicCheckWallRight(void) {
    Collider col;
    s32 i;
    s32 effects;
    s16 xCheck;
    s16 yCheck;
    s16* y;
    s16* x;
    s32* vramFlag;

    y = &PLAYER.posY.i.hi;
    x = &PLAYER.posX.i.hi;
    vramFlag = &g_Player.vram_flag;

    if (g_unkGraphicsStruct.unk18) {
        return;
    }
    effects =
        g_Player.unk04 & (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                          EFFECT_UNK_0400 | EFFECT_UNK_0002 | EFFECT_SOLID);
    if ((effects == (EFFECT_UNK_8000 | EFFECT_UNK_0002 | EFFECT_SOLID)) ||
        (effects == (EFFECT_UNK_0800 | EFFECT_UNK_0002 | EFFECT_SOLID)) ||
        (effects == (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                     EFFECT_SOLID))) {
        *vramFlag |= 4;
        return;
    }

    for (i = 0; i < NUM_VERTICAL_SENSORS; i++) {
        effects = g_Player.colWall[i].effects &
                  (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                   EFFECT_UNK_0002 | EFFECT_SOLID);
        if (effects == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_SOLID) ||
            effects == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0002 |
                        EFFECT_SOLID) ||
            effects == (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_SOLID) ||
            effects == (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                        EFFECT_SOLID) ||
            effects == (EFFECT_UNK_8000 | EFFECT_UNK_0002 | EFFECT_SOLID) ||
            effects == (EFFECT_UNK_0002 | EFFECT_SOLID)) {
            xCheck = *x + g_RicSensorsWall[i].x + g_Player.colWall[i].unk4 - 1;
            yCheck = *y + g_RicSensorsWall[i].y;
            g_api.CheckCollision(xCheck, yCheck, &col, 0);
            if ((col.effects & EFFECT_SOLID) == EFFECT_NONE) {
                *vramFlag |= 4;
                *x += g_Player.colWall[i].unk4;
                return;
            }
        }
        if (*vramFlag & 1) {
            continue;
        }
        if ((effects & (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
                EFFECT_UNK_8000 &&
            (i != 0) &&
            ((g_Player.colWall[0].effects & EFFECT_UNK_0800) ||
             !(g_Player.colWall[0].effects &
               (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
            *vramFlag |= 4;
            *x += g_Player.colWall[i].unk4;
            return;
        }
        if ((effects & (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
                EFFECT_UNK_0800 &&
            (i != 6) &&
            ((g_Player.colWall[6].effects & EFFECT_UNK_8000) ||
             !(g_Player.colWall[6].effects &
               (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
            *vramFlag |= 4;
            *x += g_Player.colWall[i].unk4;
            return;
        }
    }
}

void RicCheckWallLeft(void) {
    Collider col;
    s32 i;
    s32 effects;
    s16 xCheck;
    s16 yCheck;
    s16* y;
    s16* x;
    s32* vramFlag;

    y = &PLAYER.posY.i.hi;
    x = &PLAYER.posX.i.hi;
    vramFlag = &g_Player.vram_flag;

    if (g_unkGraphicsStruct.unk18) {
        return;
    }
    effects =
        g_Player.unk04 & (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                          EFFECT_UNK_0400 | EFFECT_UNK_0002 | EFFECT_SOLID);
    if ((effects == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0002 |
                     EFFECT_SOLID)) ||
        (effects == (EFFECT_UNK_0800 | EFFECT_UNK_0400 | EFFECT_UNK_0002 |
                     EFFECT_SOLID)) ||
        (effects == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                     EFFECT_UNK_0400 | EFFECT_UNK_0002 | EFFECT_SOLID))) {
        *vramFlag |= 8;
        return;
    }
    for (i = NUM_VERTICAL_SENSORS; i < NUM_VERTICAL_SENSORS * 2; i++) {
        effects = g_Player.colWall[i].effects &
                  (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                   EFFECT_UNK_0002 | EFFECT_SOLID);
        if ((effects == (EFFECT_UNK_8000 | EFFECT_SOLID)) ||
            (effects == (EFFECT_UNK_8000 | EFFECT_UNK_0002 | EFFECT_SOLID)) ||
            (effects == (EFFECT_UNK_0800 | EFFECT_SOLID)) ||
            (effects == (EFFECT_UNK_0800 | EFFECT_UNK_0002 | EFFECT_SOLID)) ||
            (effects == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0002 |
                         EFFECT_SOLID)) ||
            (effects == (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                         EFFECT_SOLID)) ||
            (effects == (EFFECT_UNK_0002 | EFFECT_SOLID))) {
            xCheck = *x + g_RicSensorsWall[i].x + g_Player.colWall[i].unkC + 1;
            yCheck = *y + g_RicSensorsWall[i].y;
            g_api.CheckCollision(xCheck, yCheck, &col, 0);
            if ((col.effects & EFFECT_SOLID) == EFFECT_NONE) {
                *vramFlag |= 8;
                *x += g_Player.colWall[i].unkC;
                return;
            }
        }
        if (!(*vramFlag & 1)) {
            if (((effects &
                  (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
                 (EFFECT_UNK_8000 | EFFECT_UNK_4000)) &&
                (i != 7) &&
                ((g_Player.colWall[7].effects & EFFECT_UNK_0800) ||
                 !(g_Player.colWall[7].effects &
                   (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
                *vramFlag |= 8;
                *x += g_Player.colWall[i].unkC;
                return;
            }
            if (((effects &
                  (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
                 (EFFECT_UNK_4000 | EFFECT_UNK_0800)) &&
                (i != 13) &&
                ((g_Player.colWall[13].effects & EFFECT_UNK_8000) ||
                 !(g_Player.colWall[13].effects &
                   (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
                *vramFlag |= 8;
                *x += g_Player.colWall[i].unkC;
                return;
            }
        }
    }
}
