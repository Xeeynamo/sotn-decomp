// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

void GetPlayerSensor(Collider* col) {
    void (*theFunc)(Collider* col);
    u32 mod = 0;
    if (g_PlayableCharacter == PLAYER_ALUCARD) {
        if (g_Player.status & PLAYER_STATUS_WOLF_FORM) {
            mod += 2;
        }
        col->unk14 = g_SensorsWall[0].x - mod;
        col->unk1C = g_SensorsWall[0].y + mod;
        col->unk18 = g_SensorsFloor[1].y - 1;
        col->unk20 = g_SensorsCeiling[1].y + 1;
    } else {
        theFunc = g_PlOvl.GetPlayerSensor;
        theFunc(col);
    }
}

void func_8010BFFC(void) {
    s16 x;
    s16 y;
    s32 i;
    bool collided = false;
    s16 original_Y = PLAYER.posY.i.hi;

    if ((g_Player.pl_vram_flag & 1) || D_801396EA) {
        return;
    }
#ifdef VERSION_US
    if ((g_Player.status &
         (PLAYER_STATUS_TRANSFORM | PLAYER_STATUS_UNK40000000)) ||
        ((g_PlayableCharacter != 0) && (PLAYER.step == 0x18))) {
        return;
    }
#else
    if (g_Player.status & PLAYER_STATUS_TRANSFORM)
        return;
#endif
    if (g_Player.unk78 == 1) {
        return;
    }

    if (PLAYER.posY.i.hi < 48) {
        PLAYER.posY.i.hi -= 16;
        while (true) {
            for (i = 0; i < 4; i++) {
                x = PLAYER.posX.i.hi + g_SensorsFloor[i].x;
                y = PLAYER.posY.i.hi + g_SensorsFloor[i].y;
                CheckCollision(x, y, &g_Player.colFloor[i], 0);
            }
            if ((g_Player.colFloor[1].effects &
                 (EFFECT_SOLID_FROM_BELOW + EFFECT_SOLID)) == EFFECT_SOLID ||
                (g_Player.colFloor[2].effects &
                 (EFFECT_SOLID_FROM_BELOW + EFFECT_SOLID)) == EFFECT_SOLID ||
                (g_Player.colFloor[3].effects &
                 (EFFECT_SOLID_FROM_BELOW + EFFECT_SOLID)) == EFFECT_SOLID) {
                PLAYER.velocityY = 0;
                PLAYER.posY.i.hi--;
                collided = true;
                continue;
            }
            if (collided) {
                return;
            }
            PLAYER.posY.i.hi += 8;
            if (PLAYER.posY.i.hi >= 48) {
                PLAYER.posY.i.hi = original_Y;
                return;
            }
        }
    } else if (PLAYER.posY.i.hi > 176) {
        PLAYER.posY.i.hi += 32;
        while (true) {
            for (i = 0; i < 4; i++) {
                x = PLAYER.posX.i.hi + g_SensorsCeiling[i].x;
                y = PLAYER.posY.i.hi + g_SensorsCeiling[i].y;
#if defined(VERSION_US)
                if (g_PlayableCharacter != PLAYER_ALUCARD) {
                    y += 6;
                }
#endif
                CheckCollision(x, y, &g_Player.colFloor[i] + 4, 0);
            }
            if ((g_Player.colCeiling[1].effects &
                 (EFFECT_SOLID_FROM_ABOVE + EFFECT_SOLID)) == EFFECT_SOLID ||
                (g_Player.colCeiling[2].effects &
                 (EFFECT_SOLID_FROM_ABOVE + EFFECT_SOLID)) == EFFECT_SOLID ||
                (g_Player.colCeiling[3].effects &
                 (EFFECT_SOLID_FROM_ABOVE + EFFECT_SOLID)) == EFFECT_SOLID) {
                PLAYER.velocityY = 0;
                PLAYER.posY.i.hi++;
                collided = true;
                continue;
            }
            if (collided) {
                PLAYER.posY.i.hi--;
                return;
            }
            PLAYER.posY.i.hi -= 8;
            if (PLAYER.posY.i.hi <= 176) {
                PLAYER.posY.i.hi = original_Y;
                return;
            }
        }
    }
}

INCLUDE_ASM("dra_psp/psp/dra_psp/3B9B0", CheckFloor);

void CheckCeiling(void) {
    Collider collider;
    s32 temp_fp;
    u32 var_s2;
    s32 temp_v1;
    u32 var_s1;
    s16 var_a1;

    s16 argX;
    s16 argY;

    s32 i = 1;

    s16* yPosPtr = &PLAYER.posY.i.hi;
    s16* xPosPtr = &PLAYER.posX.i.hi;
    s32* vram_ptr = &g_Player.pl_vram_flag;

    if (g_unkGraphicsStruct.unk18) {
        return;
    }
    for (; i < NUM_HORIZONTAL_SENSORS; i++) {
        if (g_Player.colCeiling[i].effects & EFFECT_SOLID_FROM_ABOVE) {
            continue;
        }
        if ((g_Player.status & PLAYER_STATUS_MIST_FORM) &&
            (collider.effects & EFFECT_MIST_ONLY)) {
            collider.effects &= ~(EFFECT_UNK_0002 | EFFECT_SOLID);
        }
        var_s2 = g_Player.colCeiling[i].effects &
                 (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_SOLID);
        if ((var_s2 == EFFECT_SOLID) || (var_s2 & EFFECT_UNK_8000)) {
            if ((g_Player.status &
                 (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_MIST_FORM)) &&
                !(var_s2 & EFFECT_SOLID)) {
                continue;
            }

            argX = *xPosPtr + g_SensorsCeiling[i].x;
            argY = *yPosPtr + g_SensorsCeiling[i].y +
                   g_Player.colCeiling[i].unk10 + 1;
            CheckCollision(argX, argY, &collider, 0);
            // If in mist form, and collider is mist, then disable collision on
            // that collider!
            if (g_Player.status & PLAYER_STATUS_MIST_FORM &&
                collider.effects & EFFECT_MIST_ONLY) {
                collider.effects &= ~(EFFECT_UNK_0002 | EFFECT_SOLID);
            }
            var_s1 = collider.effects;
            if (!(var_s1 & 1)) {
                if ((g_Player.colCeiling[i].effects != EFFECT_SOLID) ||
                    (PLAYER.velocityY <= 0)) {
                    *vram_ptr |= 2;
                    if (!(*vram_ptr & 1) &&
                        ((g_Player.unk04 &
                          (EFFECT_SOLID_FROM_ABOVE | EFFECT_SOLID)) !=
                         (EFFECT_SOLID_FROM_ABOVE | EFFECT_SOLID))) {
                        if (g_Player.colCeiling[i].effects & EFFECT_UNK_8000) {
                            *yPosPtr += g_Player.colCeiling[i].unk10;
                        } else {
                            *yPosPtr += g_Player.colCeiling[i].unk20;
                        }
                    }
                    return;
                }
                continue;
            }
            if ((var_s1 & (EFFECT_UNK_0800 | EFFECT_UNK_0002 | EFFECT_SOLID)) ==
                (EFFECT_UNK_0800 | EFFECT_SOLID)) {
                if (i < 2) {
                    *vram_ptr |=
                        (EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                         ((var_s1 >> 4) & (EFFECT_UNK_0400 | EFFECT_UNK_0200 |
                                           EFFECT_UNK_0100)));
                    if (!(*vram_ptr & 1)) {
                        *yPosPtr +=
                            g_Player.colCeiling[i].unk10 + collider.unk20 + 1;
                    }
                    return;
                }
                if ((i == 2) && ((var_s1 & (EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                                            EFFECT_SOLID)) ==
                                 (EFFECT_UNK_0800 | EFFECT_SOLID))) {
                    g_Player.colFloor[2].effects = var_s1;
                    g_Player.colFloor[2].unk8 = g_Player.colFloor[2].unk10;
                }
                if ((i == 3) &&
                    ((var_s1 &
                      (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_SOLID)) ==
                     (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_SOLID))) {
                    g_Player.colFloor[3].effects = var_s1;
                    g_Player.colFloor[3].unk8 = g_Player.colFloor[3].unk10;
                }
            }
            if ((var_s1 & EFFECT_UNK_0800) == EFFECT_NONE) {
                *vram_ptr |=
                    (EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                     ((var_s1 >> 4) &
                      (EFFECT_UNK_0400 | EFFECT_UNK_0200 | EFFECT_UNK_0100)));
                if (!(*vram_ptr & 1)) {
                    *yPosPtr +=
                        g_Player.colCeiling[i].unk10 + collider.unk20 + 1;
                }
                return;
            }
        }
        if ((var_s2 == (EFFECT_UNK_0800 | EFFECT_SOLID)) && (i < 2)) {
            *vram_ptr |=
                (EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                 ((g_Player.colCeiling[i].effects >> 4) &
                  (EFFECT_UNK_0400 | EFFECT_UNK_0200 | EFFECT_UNK_0100)));
            if (!(*vram_ptr & 1)) {
                *yPosPtr += g_Player.colCeiling[i].unk20;
            }
            return;
        }
    }
    if (PLAYER.velocityY > 0) {
        return;
    }
    argX = *xPosPtr + g_SensorsCeiling[0].x;
    argY = (*yPosPtr + g_SensorsCeiling[0].y) - 10;
    CheckCollision(argX, argY, &collider, 0);
    if ((collider.effects & EFFECT_SOLID) != EFFECT_NONE) {
        return;
    }
    for (i = 2; i < NUM_HORIZONTAL_SENSORS; i++) {
        if ((g_Player.colCeiling[3].effects & EFFECT_UNK_0800) &&
            (g_Player.colCeiling[2].effects & EFFECT_UNK_0800)) {
            return;
        }
        var_s2 = g_Player.colCeiling[i].effects;
        temp_fp = ((var_s2 >> 4) &
                   (EFFECT_UNK_0400 | EFFECT_UNK_0200 | EFFECT_UNK_0100)) +
                  (EFFECT_UNK_0800 | EFFECT_UNK_0002);
        if (var_s2 & EFFECT_UNK_0800) {
            if (i == 2) {
                var_s1 = EFFECT_UNK_4000;
                var_a1 = g_Player.colCeiling[2].unk4;
                temp_v1 = var_a1 + 8;
            } else {
                var_s1 = 0;
                var_a1 = g_Player.colCeiling[3].unkC;
                temp_v1 = 8 - var_a1;
            }
            if ((var_s2 & EFFECT_UNK_4000) == var_s1) {
                argX = var_a1 + (*xPosPtr + g_SensorsCeiling[i].x);
                argY = *yPosPtr + g_SensorsCeiling[i].y;
                CheckCollision(argX, argY, &collider, 0);
                if (collider.effects & EFFECT_SOLID) {
                    *vram_ptr |= temp_fp;
                    if (!(*vram_ptr & 1)) {
                        *yPosPtr += collider.unk20;
                    }
                    return;
                }
            } else if ((temp_v1 > 0) && (var_s2 & 1)) {
                argX = var_a1 + (*xPosPtr + g_SensorsCeiling[i].x);
                argY = *yPosPtr + g_SensorsCeiling[i].y +
                       g_Player.colCeiling[i].unk8;
                CheckCollision(argX, argY, &collider, 0);
                if (collider.effects & EFFECT_SOLID) {
                    if (!(*vram_ptr & 1)) {
                        *yPosPtr +=
                            collider.unk20 + g_Player.colCeiling[i].unk8;
                    }
                    *vram_ptr |= temp_fp;
                    return;
                }
            }
        }
    }
}

void CheckWallRight(void) {
    Collider collider;
    s32 temp_s0;
    s32 i;

    s16 argX;
    s16 argY;

    s16* yPosPtr = &PLAYER.posY.i.hi;
    s16* xPosPtr = &PLAYER.posX.i.hi;
    s32* vram_ptr = &g_Player.pl_vram_flag;

    if (((g_StageId == STAGE_BO6) || (g_StageId == STAGE_RBO6) ||
         (g_StageId == STAGE_DRE)) &&
        (*xPosPtr >= 0xF8)) {
        *xPosPtr = 0xF8;
        *vram_ptr |= 4;
        return;
    }

    if (g_unkGraphicsStruct.unk18) {
        return;
    }
    temp_s0 =
        g_Player.unk04 & (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                          EFFECT_UNK_0400 | EFFECT_UNK_0002 | EFFECT_SOLID);
    if ((temp_s0 == (EFFECT_UNK_8000 | EFFECT_UNK_0002 | EFFECT_SOLID)) ||
        (temp_s0 == (EFFECT_UNK_0800 | EFFECT_UNK_0002 | EFFECT_SOLID)) ||
        (temp_s0 == (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                     EFFECT_SOLID))) {
        *vram_ptr |= 4;
        return;
    }

    for (i = 0; i < NUM_VERTICAL_SENSORS; i++) {
        temp_s0 = g_Player.colWall[i].effects &
                  (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                   EFFECT_UNK_0002 | EFFECT_SOLID);
        if ((temp_s0 == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0002 |
                         EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                         EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_8000 | EFFECT_UNK_0002 | EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_0800 | EFFECT_UNK_0002 | EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_0002 | EFFECT_SOLID))) {
            argX = *xPosPtr + g_SensorsWall[i].x + g_Player.colWall[i].unk4 - 1;
            argY = *yPosPtr + g_SensorsWall[i].y;
            CheckCollision(argX, argY, &collider, 0);
            if ((collider.effects & EFFECT_SOLID) == EFFECT_NONE) {
                *vram_ptr |= 4;
                *xPosPtr += g_Player.colWall[i].unk4;
                return;
            }
        }

        if (!(*vram_ptr & 1)) {
            if ((temp_s0 & (EFFECT_UNK_8000 | EFFECT_UNK_4000 |
                            EFFECT_UNK_0800)) == EFFECT_UNK_8000 &&
                (i != 0) &&
                ((g_Player.colWall[0].effects & EFFECT_UNK_0800) ||
                 !(g_Player.colWall[0].effects &
                   (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
                *vram_ptr |= 4;
                *xPosPtr += g_Player.colWall[i].unk4;
                return;
            }
            if (((temp_s0 & (EFFECT_UNK_8000 | EFFECT_UNK_4000 |
                             EFFECT_UNK_0800)) == EFFECT_UNK_0800) &&
                (i != 6) &&
                ((g_Player.colWall[6].effects & EFFECT_UNK_8000) ||
                 !(g_Player.colWall[6].effects &
                   (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
                *vram_ptr |= 4;
                *xPosPtr += g_Player.colWall[i].unk4;
                return;
            }
        }
    }
}

void CheckWallLeft(void) {
    Collider collider;
    s32 temp_s0;
    s32 i;
    s16 argX;
    s16 argY;

    s16* yPosPtr = &PLAYER.posY.i.hi;
    s16* xPosPtr = &PLAYER.posX.i.hi;
    s32* vram_ptr = &g_Player.pl_vram_flag;

    if (((g_StageId == STAGE_BO6) || (g_StageId == STAGE_RBO6) ||
         (g_StageId == STAGE_DRE)) &&
        (*xPosPtr <= 8)) {
        *xPosPtr = 8;
        *vram_ptr |= 8;
        return;
    }

    if (g_unkGraphicsStruct.unk18) {
        return;
    }
    temp_s0 =
        g_Player.unk04 & (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                          EFFECT_UNK_0400 | EFFECT_UNK_0002 | EFFECT_SOLID);
    if ((temp_s0 == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0002 |
                     EFFECT_SOLID)) ||
        (temp_s0 == (EFFECT_UNK_0800 | EFFECT_UNK_0400 | EFFECT_UNK_0002 |
                     EFFECT_SOLID)) ||
        (temp_s0 == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                     EFFECT_UNK_0400 | EFFECT_UNK_0002 | EFFECT_SOLID))) {
        *vram_ptr |= 8;
        return;
    }
    for (i = NUM_VERTICAL_SENSORS; i < NUM_VERTICAL_SENSORS * 2; i++) {
        temp_s0 = g_Player.colWall[i].effects &
                  (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                   EFFECT_UNK_0002 | EFFECT_SOLID);
        if ((temp_s0 == (EFFECT_UNK_8000 | EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_8000 | EFFECT_UNK_0002 | EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_0800 | EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_0800 | EFFECT_UNK_0002 | EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0002 |
                         EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                         EFFECT_SOLID)) ||
            (temp_s0 == (EFFECT_UNK_0002 | EFFECT_SOLID))) {
            argX = *xPosPtr + g_SensorsWall[i].x + g_Player.colWall[i].unkC + 1;
            argY = *yPosPtr + g_SensorsWall[i].y;
            CheckCollision(argX, argY, &collider, 0);
            if ((collider.effects & EFFECT_SOLID) == EFFECT_NONE) {
                *vram_ptr |= 8;
                *xPosPtr += g_Player.colWall[i].unkC;
                return;
            }
        }
        if (!(*vram_ptr & 1)) {
            if (((temp_s0 &
                  (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
                 (EFFECT_UNK_8000 | EFFECT_UNK_4000)) &&
                (i != 7) &&
                ((g_Player.colWall[NUM_VERTICAL_SENSORS].effects &
                  EFFECT_UNK_0800) ||
                 !(g_Player.colWall[NUM_VERTICAL_SENSORS].effects &
                   (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
                *vram_ptr |= 8;
                *xPosPtr += g_Player.colWall[i].unkC;
                return;
            }
            if (((temp_s0 &
                  (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
                 (EFFECT_UNK_4000 | EFFECT_UNK_0800)) &&
                (i != 13) &&
                ((g_Player.colWall[NUM_VERTICAL_SENSORS + 6].effects &
                  EFFECT_UNK_8000) ||
                 !(g_Player.colWall[NUM_VERTICAL_SENSORS + 6].effects &
                   (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
                *vram_ptr |= 8;
                *xPosPtr += g_Player.colWall[i].unkC;
                return;
            }
        }
    }
}
