// SPDX-License-Identifier: AGPL-3.0-or-later
#include "maria.h"

bool MarCheckInput(s32 checks) {
    s32 velYChange;
    u32 effects;

    if (checks & CHECK_FACING) {
        MarCheckFacing();
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
    if ((checks & CHECK_80) && (g_Player.vram_flag & 2) &&
        (PLAYER.velocityY < FIX(-1))) {
        PLAYER.velocityY = FIX(-1);
    }
    if (PLAYER.velocityY >= 0) {
        if ((checks & CHECK_GROUND) && (g_Player.vram_flag & 1)) {
            switch (g_Player.unk46) {
            case 0:
            default:
                if (g_Player.unk44 & 8) {
                    MarSetCrouch(3, PLAYER.velocityX);
                    g_api.PlaySfx(SFX_STOMP_HARD_E);
                    MarCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                    return true;
                }
                if (PLAYER.velocityY > FIX(6.875)) {
                    MarSetCrouch(1, 0);
                    g_api.PlaySfx(SFX_STOMP_HARD_E);
                    MarCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                } else if (g_Player.padPressed & (PAD_LEFT | PAD_RIGHT)) {
                    MarSetWalk(0);
                } else {
                    MarSetStand(0);
                }
                return true;
            case 1:
                if (PLAYER.velocityY > FIX(6.875)) {
                    PLAYER.step = PL_S_CROUCH;
                    PLAYER.anim = mar_801555A8;
                    g_api.PlaySfx(SFX_STOMP_HARD_E);
                    MarCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                } else {
                    PLAYER.step = PL_S_STAND;
                    PLAYER.anim = mar_80155588;
                    if (!(g_Player.unk44 & 8)) {
                        PLAYER.velocityX = 0;
                    } else {
                        MarCreateEntFactoryFromEntity(
                            g_CurrentEntity, BP_SKID_SMOKE, 0);
                        g_api.PlaySfx(SFX_STOMP_HARD_E);
                    }
                }
                PLAYER.velocityY = 0;
                g_Player.unk44 = 0;
                return true;
            case 3:
                if ((PLAYER.velocityY > FIX(6.875)) || (g_Player.unk44 & 8)) {
                    g_api.PlaySfx(SFX_STOMP_HARD_E);
                    MarCreateEntFactoryFromEntity(
                        g_CurrentEntity, BP_SKID_SMOKE, 0);
                }
                PLAYER.velocityY = 0;
                if (!(g_Player.unk44 & 8)) {
                    PLAYER.velocityX = 0;
                }
                PLAYER.step = PL_S_STAND;
                PLAYER.anim = mar_80155588;
                g_Player.unk44 = 0;
                return true;
            }
        } else if (
            checks & CHECK_GROUND_AFTER_HIT && (g_Player.vram_flag & 1)) {
            MarSetCrouch(1, PLAYER.velocityX);
            g_api.PlaySfx(SFX_STOMP_HARD_E);
            MarCreateEntFactoryFromEntity(g_CurrentEntity, BP_SKID_SMOKE, 0);
            return true;
        }
    }
    if (checks & CHECK_FALL && !(g_Player.vram_flag & 1)) {
        if (g_Player.unk46) {
            if (g_Player.unk46 == 1) {
                PLAYER.step_s = 0x40;
                PLAYER.step = PL_S_JUMP;
                PLAYER.anim = mar_801555C8;
                return true;
            }
            if (g_Player.unk46 == 3) {
                PLAYER.step_s = 0x42;
                PLAYER.step = PL_S_JUMP;
                PLAYER.anim = mar_801555C8;
                return true;
            }
        } else {
            MarSetFall();
            return true;
        }
    }
    if (checks & CHECK_CRASH && (g_Player.padTapped & PAD_TRIANGLE) &&
        MarDoCrash()) {
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
        MarSetSlide();
        return true;
    }
    if (checks & CHECK_JUMP && g_Player.padTapped & PAD_CROSS) {
        MarSetJump(1);
        return true;
    }
    if (checks & CHECK_ATTACK && g_Player.padTapped & PAD_SQUARE &&
        MarDoAttack()) {
        return true;
    }
    if (checks & CHECK_20 && g_Player.padTapped & PAD_CROSS &&
        !(g_Player.unk44 & 1)) {
        func_pspeu_092B2040();
        return 1;
    }
    if (checks & CHECK_CROUCH && (g_Player.padPressed & PAD_DOWN)) {
        MarSetCrouch(2, 0);
        return true;
    }
    if (checks & CHECK_400) {
        if (PLAYER.facingLeft == 0) {
            if (g_Player.padTapped & PAD_R1) {
                MarSetRun(0);
                return 1;
            }
        } else {
            if (g_Player.padTapped & PAD_L1) {
                MarSetRun(0);
                return 1;
            }
        }
    }
    if (checks & CHECK_800) {
        if (PLAYER.facingLeft == 0) {
            if (g_Player.padTapped & PAD_L1) {
                MarSetRun(1);
                return 1;
            }
        } else {
            if (g_Player.padTapped & PAD_R1) {
                MarSetRun(1);
                return 1;
            }
        }
    }
    return false;
}

void MarGetPlayerSensor(Collider* col) {
    col->unk14 = g_MarSensorsWall[0].x;
    col->unk1C = g_MarSensorsWall[0].y;
    col->unk18 = g_MarSensorsFloor[1].y - 1;
    col->unk20 = g_MarSensorsCeiling[1].y + 1;
}

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
    y = &PLAYER.posY.i.hi;
    x = &PLAYER.posX.i.hi;
    vramFlag = &g_Player.vram_flag;

    if (g_unkGraphicsStruct.unk18) {
        *vramFlag = 1;
        return;
    }
    if (PLAYER.step == PL_S_RUN) {
        i = 1;
    } else if (PLAYER.velocityY == 0 && g_Player.unk04 & 1) {
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
              (PLAYER.step == PL_S_RUN &&
               g_Player.colFloor[i].effects & EFFECT_UNK_8000))) {
            continue;
        }
        effects2 = g_Player.colFloor[i].effects &
                   (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_SOLID);
        if ((effects2 == EFFECT_SOLID) || (effects2 & EFFECT_UNK_0800)) {
            xCheck = *x + g_MarSensorsFloor[i].x;
            yCheck = *y + g_MarSensorsFloor[i].y;
            yCheck += g_Player.colFloor[i].unk18 - 1;
            g_api.CheckCollision(xCheck, yCheck, &col, 0);
            effects = col.effects;
            if (!(effects & EFFECT_SOLID)) {
                if (g_Player.colFloor[i].effects != EFFECT_SOLID ||
                    PLAYER.velocityY >= 0 || PLAYER.step == PL_S_RUN) {
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
    xCheck = *x + g_MarSensorsFloor[0].x;
    yCheck = *y + g_MarSensorsFloor[0].y + 10;
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
        yCheck = *y + g_MarSensorsFloor[i].y + g_Player.colFloor[i].unk10;
        g_api.CheckCollision(xCheck, yCheck, &col, 0);
        if (col.effects & EFFECT_SOLID) {
            *y += (col.unk18 + g_Player.colFloor[i].unk10);
            *vramFlag |= vramApply;
            return;
        }
    }
}

INCLUDE_ASM("maria_psp/nonmatchings/pl_collision", MarCheckCeiling);

INCLUDE_ASM("maria_psp/nonmatchings/pl_collision", MarCheckWallRight);

INCLUDE_ASM("maria_psp/nonmatchings/pl_collision", MarCheckWallLeft);
