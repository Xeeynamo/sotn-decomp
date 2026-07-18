// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../cen/cen.h"

bool MarCheckInput(s32 checks) {
    s32 velYChange;

    if (checks & CHECK_FACING) {
        MarCheckFacing();
    }

    velYChange = 0;
    if (checks & CHECK_GRAVITY_FALL) {
        velYChange = FIX(28.0 / 128);
    }

    if (checks & CHECK_GRAVITY_JUMP) {
        if (MARIA.velocityY < FIX(3.0 / 8) && MARIA.velocityY > FIX(-1.0 / 8) &&
            !(g_Maria.unk44 & 0x20) && g_Maria.padPressed & PAD_CROSS) {
            // Note that 5.6 is precisely 1/5 of 28.
            velYChange = FIX(5.6 / 128);
        } else {
            velYChange = FIX(28.0 / 128);
        }
    }

    if (checks & CHECK_GRAVITY_HIT) {
        if (MARIA.velocityY < FIX(3.0 / 8) && MARIA.velocityY > FIX(-1.0 / 8)) {
            velYChange = FIX(14.0 / 128);
        } else {
            velYChange = FIX(28.0 / 128);
        }
    }

    if (g_unkGraphicsStruct.D_80097448 > 0x28) {
        velYChange /= 4;
    }

    MARIA.velocityY += velYChange;
    if (MARIA.velocityY > FIX(7)) {
        MARIA.velocityY = FIX(7);
    }

    if ((checks & CHECK_80) && g_Maria.vram_flag & TOUCHING_CEILING &&
        (MARIA.velocityY < FIX(-1))) {
        MARIA.velocityY = FIX(-1);
    }

    if (MARIA.velocityY >= 0) {
        if ((checks & CHECK_GROUND) && g_Maria.vram_flag & TOUCHING_GROUND) {
            switch (g_Maria.unk46) {
            default:
            case 0:
                if (g_Maria.unk44 & 8) {
                    MarSetCrouch(3, MARIA.velocityX);
                    g_api.PlaySfx(SFX_STOMP_HARD_E);
                    MarCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                    return true;
                }

                if (MARIA.velocityY > FIX(6.875)) {
                    MarSetCrouch(1, 0);
                    g_api.PlaySfx(SFX_STOMP_HARD_E);
                    MarCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                } else if (g_Maria.padPressed & (PAD_LEFT | PAD_RIGHT)) {
                    MarSetWalk(0);
                } else {
                    MarSetStand(0);
                }

                return true;
            case 1:
                if (MARIA.velocityY > FIX(6.875)) {
                    MARIA.step = PL_S_CROUCH;
                    MARIA.anim = mar_801555A8;
                    g_api.PlaySfx(SFX_STOMP_HARD_E);
                    MarCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                } else {
                    MARIA.step = PL_S_STAND;
                    MARIA.anim = mar_80155588;
                    if (!(g_Maria.unk44 & 8)) {
                        MARIA.velocityX = 0;
                    } else {
                        MarCreateEntFactoryFromEntity(
                            g_CurrentEntity, BP_SKID_SMOKE, 0);
                        g_api.PlaySfx(SFX_STOMP_HARD_E);
                    }
                }
                MARIA.velocityY = 0;
                g_Maria.unk44 = 0;
                return true;
            case 3:
                if ((MARIA.velocityY > FIX(6.875)) || (g_Maria.unk44 & 8)) {
                    g_api.PlaySfx(SFX_STOMP_HARD_E);
                    MarCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                }

                MARIA.velocityY = 0;
                if (!(g_Maria.unk44 & 8)) {
                    MARIA.velocityX = 0;
                }

                MARIA.step = PL_S_STAND;
                MARIA.anim = mar_80155588;
                g_Maria.unk44 = 0;
                return true;
            }
        } else if (checks & CHECK_GROUND_AFTER_HIT &&
                   g_Maria.vram_flag & TOUCHING_GROUND) {
            MarSetCrouch(1, MARIA.velocityX);
            g_api.PlaySfx(SFX_STOMP_HARD_E);
            MarCreateEntFactoryFromEntity(g_CurrentEntity, BP_SKID_SMOKE, 0);
            return true;
        }
    }

    if (checks & CHECK_FALL && !(g_Maria.vram_flag & TOUCHING_GROUND)) {
        if (g_Maria.unk46) {
            if ((g_Maria.unk46) == 1) {
                MARIA.step_s = 0x40;
                MARIA.step = PL_S_JUMP;
                MARIA.anim = mar_801555C8;
                return true;
            }

            if (g_Maria.unk46 == 3) {
                MARIA.step_s = 0x42;
                MARIA.step = PL_S_JUMP;
                MARIA.anim = mar_801555C8;
                return true;
            }
        } else {
            MarSetFall();
            return true;
        }
    }

    if (checks & CHECK_CRASH && (g_Maria.padTapped & PAD_TRIANGLE) &&
        MarDoCrash()) {
        return true;
    }

    if (checks & CHECK_SLIDE &&
        (MARIA.facingLeft != 0 ||
         !(g_Maria.colFloor[2].effects & EFFECT_UNK_8000)) &&
        (!MARIA.facingLeft ||
         !(g_Maria.colFloor[3].effects & EFFECT_UNK_8000)) &&
        (MARIA.posX.i.hi < (u8)-4 || MARIA.facingLeft != 0) &&
        (MARIA.posX.i.hi >= 5 || !MARIA.facingLeft) &&
        g_Maria.padPressed & PAD_DOWN && g_Maria.padTapped & PAD_CROSS) {
        MarSetSlide();
        return true;
    }

    if (checks & CHECK_JUMP && (g_Maria.padTapped & PAD_CROSS)) {
        MarSetJump(1);
        return true;
    }

    if (checks & CHECK_ATTACK && (g_Maria.padTapped & PAD_SQUARE) &&
        MarDoAttack()) {
        return true;
    }

    if (checks & CHECK_DOUBLEJUMP && (g_Maria.padTapped & PAD_CROSS) &&
        !(g_Maria.unk44 & 1)) {
        MarSetDoubleJump();
        return true;
    }

    if (checks & CHECK_CROUCH && (g_Maria.padPressed & PAD_DOWN)) {
        MarSetCrouch(2, 0);
        return true;
    }

    if (checks & CHECK_400) {
        if (MARIA.facingLeft == 0) {
            if (g_Maria.padTapped & PAD_R1) {
                MarSetRun(0);
                return 1;
            }
        } else if (g_Maria.padTapped & PAD_L1) {
            MarSetRun(0);
            return 1;
        }
    }

    if (checks & CHECK_800) {
        if (MARIA.facingLeft == 0) {
            if (g_Maria.padTapped & PAD_L1) {
                MarSetRun(1);
                return 1;
            }
        } else if (g_Maria.padTapped & PAD_R1) {
            MarSetRun(1);
            return 1;
        }
    }
    return false;
}

// nb. no MarGetPlayerSensor

void MarCheckFloor(void) {
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
    y = &MARIA.posY.i.hi;
    x = &MARIA.posX.i.hi;
    vramFlag = &g_Maria.vram_flag;

    if (g_unkGraphicsStruct.unk18) {
        *vramFlag = 1;
        return;
    }
    if (MARIA.step == PL_S_RUN) {
        i = 1;
    } else if (MARIA.velocityY == 0 && g_Maria.unk04 & 1) {
        yMod = 4;
    } else {
        i = 1;
    }
    for (; i < NUM_HORIZONTAL_SENSORS; i++, yMod = 0) {
        if (g_Maria.colFloor[i].effects & EFFECT_SOLID_FROM_BELOW) {
            continue;
        }
        if (!(g_Maria.colFloor[i].effects & EFFECT_UNK_0002 ||
              MARIA.velocityY >= 0 ||
              (MARIA.step == PL_S_RUN &&
               g_Maria.colFloor[i].effects & EFFECT_UNK_8000))) {
            continue;
        }
        effects2 = g_Maria.colFloor[i].effects &
                   (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_SOLID);
        if ((effects2 == EFFECT_SOLID) || (effects2 & EFFECT_UNK_0800)) {
            xCheck = *x + g_MarSensorsFloor[i].x;
            yCheck = *y + g_MarSensorsFloor[i].y;
            yCheck += g_Maria.colFloor[i].unk18 - 1;
            g_api.CheckCollision(xCheck, yCheck, &col, 0);
            effects = col.effects;
            if (!(effects & EFFECT_SOLID)) {
                if (g_Maria.colFloor[i].effects != EFFECT_SOLID ||
                    MARIA.velocityY >= 0 || MARIA.step == PL_S_RUN) {
                    if (effects2 & EFFECT_UNK_0800) {
                        *y += yMod + g_Maria.colFloor[i].unk8;
                    } else {
                        *y += yMod + g_Maria.colFloor[i].unk18;
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
                    *y += g_Maria.colFloor[i].unk8 + col.unk18 - 1 + yMod;
                    return;
                }
                if (i == 2 && (effects & (EFFECT_UNK_8000 | EFFECT_UNK_4000 |
                                          EFFECT_SOLID)) ==
                                  (EFFECT_UNK_8000 | EFFECT_SOLID)) {
                    g_Maria.colFloor[2].effects = effects;
                    g_Maria.colFloor[2].unk10 = g_Maria.colFloor[2].unk8;
                }
                if (i == 3 &&
                    (effects &
                     (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_SOLID)) ==
                        (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_SOLID)) {
                    g_Maria.colFloor[3].effects = effects;
                    g_Maria.colFloor[3].unk10 = g_Maria.colFloor[3].unk8;
                }
            }
        }
        if (effects2 == (EFFECT_UNK_8000 | EFFECT_SOLID) && i < 2) {
            *vramFlag |= g_Maria.colFloor[i].effects &
                         (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_2000 |
                          EFFECT_UNK_1000 | EFFECT_SOLID);
            *y += yMod + g_Maria.colFloor[i].unk18;
            return;
        }
    }
    if (g_Maria.colFloor[1].effects & EFFECT_QUICKSAND) {
        *vramFlag |= EFFECT_SOLID | EFFECT_MIST_ONLY;
        if (!(g_Timer & 3)) {
            (*y)++;
        }
        return;
    }
    if (g_Maria.colFloor[1].effects & EFFECT_WATER) {
        *vramFlag |= EFFECT_SOLID_FROM_BELOW;
    }
    if (MARIA.velocityY < 0) {
        return;
    }
    xCheck = *x + g_MarSensorsFloor[0].x;
    yCheck = *y + g_MarSensorsFloor[0].y + 10;
    g_api.CheckCollision(xCheck, yCheck, &col, 0);
    if ((col.effects & (EFFECT_UNK_8000 | EFFECT_SOLID)) != EFFECT_NONE) {
        return;
    }

    for (i = 2; i < NUM_HORIZONTAL_SENSORS; i++) {
        if ((g_Maria.colFloor[3].effects & EFFECT_UNK_8000) &&
            (g_Maria.colFloor[2].effects & EFFECT_UNK_8000)) {
            return;
        }
        effects2 = g_Maria.colFloor[i].effects;
        vramApply = ((effects2 &
                      (EFFECT_UNK_4000 | EFFECT_UNK_2000 | EFFECT_UNK_1000)) +
                     (EFFECT_UNK_8000 | EFFECT_SOLID));
        if (!(effects2 & EFFECT_UNK_8000)) {
            continue;
        }
        if (i == 2) {
            effects = EFFECT_UNK_4000;
            xMod = g_Maria.colFloor[2].unk4;
            xMax = xMod + 8;
        } else {
            effects = 0;
            xMod = g_Maria.colFloor[3].unkC;
            xMax = 8 - xMod;
        }
        if ((effects2 & EFFECT_UNK_4000) == effects) {
            xCheck = xMod + (*x + g_MarSensorsFloor[i].x);
            yCheck = *y + g_MarSensorsFloor[i].y;
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
        xCheck = *x + g_MarSensorsFloor[i].x + xMod;
        yCheck = *y + g_MarSensorsFloor[i].y + g_Maria.colFloor[i].unk10;
        g_api.CheckCollision(xCheck, yCheck, &col, 0);
        if (col.effects & EFFECT_SOLID) {
            *y += (col.unk18 + g_Maria.colFloor[i].unk10);
            *vramFlag |= vramApply;
            return;
        }
    }
}

void MarCheckCeiling(void) {
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
    y = &MARIA.posY.i.hi;
    x = &MARIA.posX.i.hi;
    vramFlag = &g_Maria.vram_flag;

    if (g_unkGraphicsStruct.unk18) {
        return;
    }
    for (; i < NUM_HORIZONTAL_SENSORS; i++) {
        if (g_Maria.colCeiling[i].effects & EFFECT_SOLID_FROM_ABOVE) {
            continue;
        }
        effects2 = g_Maria.colCeiling[i].effects &
                   (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_SOLID);
        if ((effects2 == EFFECT_SOLID) || (effects2 & EFFECT_UNK_8000)) {
            if ((MARIA.step == PL_S_RUN || MARIA.step == PL_S_SLIDE) &&
                !(effects2 & EFFECT_SOLID)) {
                continue;
            }
            xCheck = *x + g_MarSensorsCeiling[i].x;
            yCheck =
                *y + g_MarSensorsCeiling[i].y + g_Maria.colCeiling[i].unk10 + 1;
            g_api.CheckCollision(xCheck, yCheck, &col, 0);
            effects = col.effects;
            if (!(effects & EFFECT_SOLID)) {
                if (g_Maria.colCeiling[i].effects != EFFECT_SOLID ||
                    MARIA.velocityY <= 0) {
                    *vramFlag |= 2;
                    if (!(*vramFlag & 1) &&
                        ((g_Maria.unk04 &
                          (EFFECT_SOLID_FROM_ABOVE | EFFECT_SOLID)) !=
                         (EFFECT_SOLID_FROM_ABOVE | EFFECT_SOLID))) {
                        if (g_Maria.colCeiling[i].effects & EFFECT_UNK_8000) {
                            *y += g_Maria.colCeiling[i].unk10;
                        } else {
                            *y += g_Maria.colCeiling[i].unk20;
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
                        *y += 1 + (g_Maria.colCeiling[i].unk10 + col.unk20);
                    }
                    return;
                }
                if (i == 2 && (effects & (EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                                          EFFECT_SOLID)) ==
                                  (EFFECT_UNK_0800 | EFFECT_SOLID)) {
                    g_Maria.colFloor[2].effects = effects;
                    g_Maria.colFloor[2].unk8 = g_Maria.colFloor[2].unk10;
                }
                if (i == 3 &&
                    (effects &
                     (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_SOLID)) ==
                        (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_SOLID)) {
                    g_Maria.colFloor[3].effects = effects;
                    g_Maria.colFloor[3].unk8 = g_Maria.colFloor[3].unk10;
                }
            }
            if ((effects & EFFECT_UNK_0800) == EFFECT_NONE) {
                *vramFlag |=
                    (EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                     ((effects >> 4) &
                      (EFFECT_UNK_0400 | EFFECT_UNK_0200 | EFFECT_UNK_0100)));
                if (!(*vramFlag & 1)) {
                    *y += 1 + (g_Maria.colCeiling[i].unk10 + col.unk20);
                }
                return;
            }
        }
        if ((effects2 == (EFFECT_UNK_0800 | EFFECT_SOLID)) && i < 2) {
            *vramFlag |=
                (EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                 ((g_Maria.colCeiling[i].effects >> 4) &
                  (EFFECT_UNK_0400 | EFFECT_UNK_0200 | EFFECT_UNK_0100)));
            if (!(*vramFlag & 1)) {
                *y += g_Maria.colCeiling[i].unk20;
            }
            return;
        }
    }
    if (MARIA.velocityY > 0) {
        return;
    }
    xCheck = *x + g_MarSensorsCeiling[0].x;
    yCheck = (*y + g_MarSensorsCeiling[0].y) - 10;
    g_api.CheckCollision(xCheck, yCheck, &col, 0);
    if ((col.effects & EFFECT_SOLID) != EFFECT_NONE) {
        return;
    }
    for (i = 2; i < NUM_HORIZONTAL_SENSORS; i++) {
        if ((g_Maria.colCeiling[3].effects & EFFECT_UNK_0800) &&
            (g_Maria.colCeiling[2].effects & EFFECT_UNK_0800)) {
            return;
        }
        effects2 = g_Maria.colCeiling[i].effects;
        vramApply = ((effects2 >> 4) &
                     (EFFECT_UNK_0400 | EFFECT_UNK_0200 | EFFECT_UNK_0100)) +
                    (EFFECT_UNK_0800 | EFFECT_UNK_0002);
        if (!(effects2 & EFFECT_UNK_0800)) {
            continue;
        }
        if (i == 2) {
            effects = EFFECT_UNK_4000;
            xMod = g_Maria.colCeiling[2].unk4;
            xMax = xMod + 8;
        } else {
            effects = 0;
            xMod = g_Maria.colCeiling[3].unkC;
            xMax = 8 - xMod;
        }
        if ((effects2 & EFFECT_UNK_4000) == effects) {
            xCheck = xMod + (*x + g_MarSensorsCeiling[i].x);
            yCheck = *y + g_MarSensorsCeiling[i].y;
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
        xCheck = *x + g_MarSensorsCeiling[i].x + xMod;
        yCheck = *y + g_MarSensorsCeiling[i].y + g_Maria.colCeiling[i].unk8;
        g_api.CheckCollision(xCheck, yCheck, &col, 0);
        if (col.effects & EFFECT_SOLID) {
            if (!(*vramFlag & 1)) {
                *y += col.unk20 + g_Maria.colCeiling[i].unk8;
            }
            *vramFlag |= vramApply;
            return;
        }
    }
}

void MarCheckWallRight(void) {
    Collider col;
    s32 i;
    s32 effects;
    s16 xCheck;
    s16 yCheck;
    s16* y;
    s16* x;
    s32* vramFlag;

    y = &MARIA.posY.i.hi;
    x = &MARIA.posX.i.hi;
    vramFlag = &g_Maria.vram_flag;

    if (g_unkGraphicsStruct.unk18) {
        return;
    }
    effects =
        g_Maria.unk04 & (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                         EFFECT_UNK_0400 | EFFECT_UNK_0002 | EFFECT_SOLID);
    if ((effects == (EFFECT_UNK_8000 | EFFECT_UNK_0002 | EFFECT_SOLID)) ||
        (effects == (EFFECT_UNK_0800 | EFFECT_UNK_0002 | EFFECT_SOLID)) ||
        (effects == (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                     EFFECT_SOLID))) {
        *vramFlag |= 4;
        return;
    }

    for (i = 0; i < NUM_VERTICAL_SENSORS; i++) {
        effects = g_Maria.colWall[i].effects &
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
            xCheck = *x + g_MarSensorsWall[i].x + g_Maria.colWall[i].unk4 - 1;
            yCheck = *y + g_MarSensorsWall[i].y;
            g_api.CheckCollision(xCheck, yCheck, &col, 0);
            if ((col.effects & EFFECT_SOLID) == EFFECT_NONE) {
                *vramFlag |= 4;
                *x += g_Maria.colWall[i].unk4;
                return;
            }
        }
        if (*vramFlag & 1) {
            continue;
        }
        if ((effects & (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
                EFFECT_UNK_8000 &&
            (i != 0) &&
            ((g_Maria.colWall[0].effects & EFFECT_UNK_0800) ||
             !(g_Maria.colWall[0].effects &
               (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
            *vramFlag |= 4;
            *x += g_Maria.colWall[i].unk4;
            return;
        }
        if ((effects & (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
                EFFECT_UNK_0800 &&
            (i != 6) &&
            ((g_Maria.colWall[6].effects & EFFECT_UNK_8000) ||
             !(g_Maria.colWall[6].effects &
               (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
            *vramFlag |= 4;
            *x += g_Maria.colWall[i].unk4;
            return;
        }
    }
}

void MarCheckWallLeft(void) {
    Collider col;
    s32 i;
    s32 effects;
    s16 xCheck;
    s16 yCheck;
    s16* y;
    s16* x;
    s32* vramFlag;

    y = &MARIA.posY.i.hi;
    x = &MARIA.posX.i.hi;
    vramFlag = &g_Maria.vram_flag;

    if (g_unkGraphicsStruct.unk18) {
        return;
    }
    effects =
        g_Maria.unk04 & (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
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
        effects = g_Maria.colWall[i].effects &
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
            xCheck = *x + g_MarSensorsWall[i].x + g_Maria.colWall[i].unkC + 1;
            yCheck = *y + g_MarSensorsWall[i].y;
            g_api.CheckCollision(xCheck, yCheck, &col, 0);
            if ((col.effects & EFFECT_SOLID) == EFFECT_NONE) {
                *vramFlag |= 8;
                *x += g_Maria.colWall[i].unkC;
                return;
            }
        }
        if (!(*vramFlag & 1)) {
            if (((effects &
                  (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
                 (EFFECT_UNK_8000 | EFFECT_UNK_4000)) &&
                (i != 7) &&
                ((g_Maria.colWall[7].effects & EFFECT_UNK_0800) ||
                 !(g_Maria.colWall[7].effects &
                   (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
                *vramFlag |= 8;
                *x += g_Maria.colWall[i].unkC;
                return;
            }
            if (((effects &
                  (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
                 (EFFECT_UNK_4000 | EFFECT_UNK_0800)) &&
                (i != 13) &&
                ((g_Maria.colWall[13].effects & EFFECT_UNK_8000) ||
                 !(g_Maria.colWall[13].effects &
                   (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
                *vramFlag |= 8;
                *x += g_Maria.colWall[i].unkC;
                return;
            }
        }
    }
}
