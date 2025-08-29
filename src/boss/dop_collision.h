// SPDX-License-Identifier: AGPL-3.0-or-later

extern Point16 g_DopSensorsFloor[];

static void OVL_EXPORT(CheckFloor)(void) {
    Collider collider;
    s32 temp_v1;
    u32 effects;
    s16 var_a1;
    s16 posX;
    s16 posY;
    u32 maskedEffects;

    s16 sp5e = 0;
    s32 i = 0;
    s16* dopPosY = &DOPPLEGANGER.posY.i.hi;
    s16* dopPosX = &DOPPLEGANGER.posX.i.hi;
    s32* vram_flag_p = &g_Dop.vram_flag;
    s32 sp30;

    if ((DOPPLEGANGER.velocityY == 0) && (g_Dop.unk04 & 1) &&
        !(g_Dop.status & (PLAYER_STATUS_DEAD | PLAYER_STATUS_STONE |
                          PLAYER_STATUS_MIST_FORM | PLAYER_STATUS_BAT_FORM))) {
        sp5e = 4;
    } else {
        i = 1;
    }

    for (; i < NUM_HORIZONTAL_SENSORS; i++, sp5e = 0) {

        if (g_Dop.colFloor[i].effects & EFFECT_SOLID_FROM_BELOW) {
            continue;
        }

        if (!((g_Dop.colFloor[i].effects & EFFECT_UNK_0002) ||
              (DOPPLEGANGER.velocityY >= 0) ||
              (g_Dop.status &
               (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_MIST_FORM)) ||
              (abs(DOPPLEGANGER.velocityX) >= FIX(2)))) {
            continue;
        }
        effects = g_Dop.colFloor[i].effects &
                  (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_SOLID);
        if ((effects == EFFECT_SOLID) || (effects & EFFECT_UNK_0800)) {
            if ((g_Dop.status &
                 (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_MIST_FORM)) &&
                !(effects & EFFECT_SOLID)) {
                continue;
            }
            posX = *dopPosX + g_DopSensorsFloor[i].x;
            posY = *dopPosY + g_DopSensorsFloor[i].y;
            posY += (g_Dop.colFloor[i].unk18 - 1);
            g_api.CheckCollision(posX, posY, &collider, 0);
            if ((g_Dop.status & PLAYER_STATUS_MIST_FORM) &&
                (collider.effects & EFFECT_MIST_ONLY)) {
                collider.effects &= ~(EFFECT_UNK_0002 | EFFECT_SOLID);
            }
            maskedEffects = collider.effects;
            if (!(maskedEffects & EFFECT_SOLID)) {
                if ((g_Dop.colFloor[i].effects != EFFECT_SOLID) ||
                    (DOPPLEGANGER.velocityY >= 0)) {
                    if (effects & EFFECT_UNK_0800) {
                        *dopPosY += sp5e + g_Dop.colFloor[i].unk8;
                    } else {
                        *dopPosY += sp5e + g_Dop.colFloor[i].unk18;
                    }
                    *vram_flag_p |= 1;
                    return;
                }
                continue;
            }
            if ((maskedEffects &
                 (EFFECT_UNK_8000 | EFFECT_UNK_0002 | EFFECT_SOLID)) ==
                (EFFECT_UNK_8000 | EFFECT_SOLID)) {
                if (i < 2) {
                    *vram_flag_p |=
                        ((maskedEffects & (EFFECT_UNK_4000 | EFFECT_UNK_2000 |
                                           EFFECT_UNK_1000)) +
                         0x7FFF + 2);
                    *dopPosY +=
                        g_Dop.colFloor[i].unk8 + collider.unk18 - 1 + sp5e;
                    return;
                }
                if ((i == 2) &&
                    ((maskedEffects &
                      (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_SOLID)) ==
                     (EFFECT_UNK_8000 | EFFECT_SOLID))) {
                    g_Dop.colFloor[2].effects = maskedEffects;
                    g_Dop.colFloor[2].unk10 = g_Dop.colFloor[2].unk8;
                }
                if ((i == 3) &&
                    ((maskedEffects &
                      (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_SOLID)) ==
                     (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_SOLID))) {
                    g_Dop.colFloor[3].effects = maskedEffects;
                    g_Dop.colFloor[3].unk10 = g_Dop.colFloor[3].unk8;
                }
            }
        }
        if ((effects != (EFFECT_UNK_8000 | EFFECT_SOLID)) || (i >= 2)) {
            continue;
        }
        *vram_flag_p |= g_Dop.colFloor[i].effects &
                        (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_2000 |
                         EFFECT_UNK_1000 | EFFECT_SOLID);
        *dopPosY += sp5e + g_Dop.colFloor[i].unk18;
        return;
    }

    if (DOPPLEGANGER.velocityY < 0) {
        return;
    }
    posX = *dopPosX + g_DopSensorsFloor[0].x;
    posY = *dopPosY + g_DopSensorsFloor[0].y + 10;
    g_api.CheckCollision(posX, posY, &collider, 0);
    if ((collider.effects & (EFFECT_UNK_8000 | EFFECT_SOLID)) != EFFECT_NONE) {
        return;
    }

    for (i = 2; i < NUM_HORIZONTAL_SENSORS; i++) {
        if ((g_Dop.colFloor[3].effects & EFFECT_UNK_8000) &&
            (g_Dop.colFloor[2].effects & EFFECT_UNK_8000)) {
            return;
        }
        effects = g_Dop.colFloor[i].effects;
        sp30 =
            ((effects & (EFFECT_UNK_4000 | EFFECT_UNK_2000 | EFFECT_UNK_1000)) +
             0x7FFF + 2);
        if (!(effects & EFFECT_UNK_8000)) {
            continue;
        }
        if (i == 2) {
            maskedEffects = EFFECT_UNK_4000;
            var_a1 = g_Dop.colFloor[2].unk4;
            temp_v1 = var_a1 + 8;
        } else {
            maskedEffects = 0;
            var_a1 = g_Dop.colFloor[3].unkC;
            temp_v1 = 8 - var_a1;
        }
        if ((effects & EFFECT_UNK_4000) == maskedEffects) {
            posX = var_a1 + (*dopPosX + g_DopSensorsFloor[i].x);
            posY = *dopPosY + g_DopSensorsFloor[i].y;
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                *dopPosY += collider.unk18;
                *vram_flag_p |= sp30;
                return;
            }
            continue;
        }
        if (temp_v1 <= 0) {
            continue;
        }
        if (!(effects & 1)) {
            continue;
        }
        posX = var_a1 + (*dopPosX + g_DopSensorsFloor[i].x);
        posY = *dopPosY + g_DopSensorsFloor[i].y + g_Dop.colFloor[i].unk10;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            *dopPosY += (collider.unk18 + g_Dop.colFloor[i].unk10);
            *vram_flag_p |= sp30;
            return;
        }
    }
}

// g_SensorsCeiling in DRA
extern Point16 g_DopSensorsCeiling[];

// same as DRA's CheckCeiling
static void OVL_EXPORT(CheckCeiling)(void) {
    Collider collider;
    s32 temp_fp;
    s32 temp_v1;
    u32 effects;
    s16 var_a1;
    s16 posX;
    s16 posY;
    u32 maskedEffects;

    s32 i = 1;
    s16* dopPosY = &DOPPLEGANGER.posY.i.hi;
    s16* dopPosX = &DOPPLEGANGER.posX.i.hi;
    s32* vram_flag_p = &g_Dop.vram_flag;

    for (; i < NUM_HORIZONTAL_SENSORS; i++) {
        if (g_Dop.colCeiling[i].effects & EFFECT_SOLID_FROM_ABOVE) {
            continue;
        }

        if ((g_Dop.status & PLAYER_STATUS_MIST_FORM) &&
            (collider.effects & EFFECT_MIST_ONLY)) {
            collider.effects &= ~(EFFECT_UNK_0002 | EFFECT_SOLID);
        }

        effects = g_Dop.colCeiling[i].effects &
                  (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_SOLID);

        if (effects == EFFECT_SOLID || (effects & EFFECT_UNK_8000)) {
            if ((g_Dop.status &
                 (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_MIST_FORM)) &&
                !(effects & EFFECT_SOLID)) {
                continue;
            }

            posX = *dopPosX + g_DopSensorsCeiling[i].x;
            posY = *dopPosY + g_DopSensorsCeiling[i].y +
                   g_Dop.colCeiling[i].unk10 + 1;
            g_api.CheckCollision(posX, posY, &collider, 0);
            if ((g_Dop.status & PLAYER_STATUS_MIST_FORM) &&
                (collider.effects & EFFECT_MIST_ONLY)) {
                collider.effects &= ~(EFFECT_UNK_0002 | EFFECT_SOLID);
            }

            maskedEffects = collider.effects;
            if (!(maskedEffects & EFFECT_SOLID)) {
                if (g_Dop.colCeiling[i].effects != EFFECT_SOLID ||
                    DOPPLEGANGER.velocityY <= 0) {
                    *vram_flag_p |= 2;
                    if (!(*vram_flag_p & 1)) {
                        if (g_Dop.colCeiling[i].effects & EFFECT_UNK_8000) {
                            *dopPosY += g_Dop.colCeiling[i].unk10;
                        } else {
                            *dopPosY += g_Dop.colCeiling[i].unk20;
                        }
                    }
                    return;
                }
                continue;
            }
            if ((maskedEffects &
                 (EFFECT_UNK_0800 | EFFECT_UNK_0002 | EFFECT_SOLID)) ==
                (EFFECT_UNK_0800 | EFFECT_SOLID)) {
                if (i < 2) {
                    *vram_flag_p |= 0x802 | ((maskedEffects >> 4) & 0x700);
                    if (!(*vram_flag_p & 1)) {
                        *dopPosY +=
                            g_Dop.colCeiling[i].unk10 + collider.unk20 + 1;
                    }
                    return;
                }
                if ((i == 2) &&
                    (maskedEffects &
                     (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_SOLID)) ==
                        (EFFECT_UNK_0800 | EFFECT_SOLID)) {
                    g_Dop.colFloor[2].effects = maskedEffects;
                    g_Dop.colFloor[2].unk8 = g_Dop.colFloor[2].unk10;
                }
                if ((i == 3) &&
                    ((maskedEffects &
                      (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_SOLID)) ==
                     (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_SOLID))) {
                    g_Dop.colFloor[3].effects = maskedEffects;
                    g_Dop.colFloor[3].unk8 = g_Dop.colFloor[3].unk10;
                }
            }
        }

        if (effects == (EFFECT_UNK_0800 | EFFECT_SOLID) && i < 2) {
            *vram_flag_p |=
                (EFFECT_UNK_0800 | EFFECT_UNK_0002) |
                ((g_Dop.colCeiling[i].effects >> 4) &
                 (EFFECT_UNK_0400 | EFFECT_UNK_0200 | EFFECT_UNK_0100));
            if (!(*vram_flag_p & 1)) {
                *dopPosY += g_Dop.colCeiling[i].unk20;
            }
            return;
        }
    }

    if (DOPPLEGANGER.velocityY > 0) {
        return;
    }

    posX = *dopPosX + g_DopSensorsCeiling[0].x;
    posY = *dopPosY + g_DopSensorsCeiling[0].y - 10;
    g_api.CheckCollision(posX, posY, &collider, 0);
    if ((collider.effects & EFFECT_SOLID) != EFFECT_NONE) {
        return;
    }

    for (i = 2; i < NUM_HORIZONTAL_SENSORS; i++) {
        if ((g_Dop.colCeiling[3].effects & EFFECT_UNK_0800) &&
            (g_Dop.colCeiling[2].effects & EFFECT_UNK_0800)) {
            return;
        }

        effects = g_Dop.colCeiling[i].effects;
        temp_fp = ((effects >> 4) & 0x700) + 0x802;
        if (effects & EFFECT_UNK_0800) {
            if (i == 2) {
                maskedEffects = EFFECT_UNK_4000;
                var_a1 = g_Dop.colCeiling[2].unk4;
                temp_v1 = var_a1 + 8;
            } else {
                maskedEffects = 0;
                var_a1 = g_Dop.colCeiling[3].unkC;
                temp_v1 = 8 - var_a1;
            }

            if ((effects & EFFECT_UNK_4000) == maskedEffects) {
                posX = *dopPosX + g_DopSensorsCeiling[i].x + var_a1;
                posY = *dopPosY + g_DopSensorsCeiling[i].y;
                g_api.CheckCollision(posX, posY, &collider, 0);
                if (collider.effects & EFFECT_SOLID) {
                    *vram_flag_p |= temp_fp;
                    if (!(*vram_flag_p & 1)) {
                        *dopPosY += collider.unk20;
                    }
                    return;
                }
            } else if ((temp_v1 > 0) && (effects & 1)) {
                posX = *dopPosX + g_DopSensorsCeiling[i].x + var_a1;
                posY = (*dopPosY + g_DopSensorsCeiling[i].y +
                        g_Dop.colCeiling[i].unk8);

                g_api.CheckCollision(posX, posY, &collider, 0);
                if (collider.effects & EFFECT_SOLID) {
                    if (!(*vram_flag_p & 1)) {
                        *dopPosY += collider.unk20 + g_Dop.colCeiling[i].unk8;
                    }
                    *vram_flag_p |= temp_fp;
                    return;
                }
            }
        }
    }
}

extern Point16 g_DopSensorsWall[];

static void OVL_EXPORT(CheckWallRight)(void) {
    Collider collider;

    s16* dopY;
    s16* dopX;
    s32 effects;
    s32 i;
    u32* pVramFlag;

    s16 offsetX, offsetY;

    dopY = &DOPPLEGANGER.posY.i.hi;
    dopX = &DOPPLEGANGER.posX.i.hi;

    pVramFlag = &g_Dop.vram_flag;
    effects =
        g_Dop.unk04 & (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                       EFFECT_UNK_0400 | EFFECT_UNK_0002 | EFFECT_SOLID);
    if (effects == (EFFECT_UNK_8000 | EFFECT_UNK_0002 | EFFECT_SOLID) ||
        effects == (EFFECT_UNK_0800 | EFFECT_UNK_0002 | EFFECT_SOLID) ||
        effects == (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                    EFFECT_SOLID)) {
        *pVramFlag |= 4;
        return;
    }

    for (i = 0; i < 7; i++) {
        effects = g_Dop.colWall[i].effects &
                  (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                   EFFECT_UNK_0002 | EFFECT_SOLID);
        if ((effects == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_SOLID)) ||
            (effects == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0002 |
                         EFFECT_SOLID)) ||
            (effects == (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_SOLID)) ||
            (effects == (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                         EFFECT_SOLID)) ||
            (effects == (EFFECT_UNK_8000 | EFFECT_UNK_0002 | EFFECT_SOLID)) ||
            (effects == (EFFECT_UNK_0800 | EFFECT_UNK_0002 | EFFECT_SOLID)) ||
            (effects == (EFFECT_UNK_0002 | EFFECT_SOLID))) {

            offsetX = *dopX + g_DopSensorsWall[i].x + g_Dop.colWall[i].unk4 - 1;
            offsetY = *dopY + g_DopSensorsWall[i].y;
            g_api.CheckCollision(offsetX, offsetY, &collider, 0);

            if (!(collider.effects & EFFECT_SOLID)) {
                *pVramFlag |= 4;
                *dopX += g_Dop.colWall[i].unk4;
                return;
            }
        }

        if ((effects & (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
                EFFECT_UNK_8000 &&
            i != 0 &&
            ((g_Dop.colWall[0].effects & EFFECT_UNK_0800) ||
             !(g_Dop.colWall[0].effects &
               (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
            *pVramFlag |= 4;
            *dopX += g_Dop.colWall[i].unk4;
            return;
        }

        if ((effects & (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
                EFFECT_UNK_0800 &&
            i != 6 &&
            ((g_Dop.colWall[6].effects & EFFECT_UNK_8000) ||
             !(g_Dop.colWall[6].effects &
               (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
            *pVramFlag |= 4;
            *dopX += g_Dop.colWall[i].unk4;
            return;
        }
    }
}

static void OVL_EXPORT(CheckWallLeft)(void) {
    Collider collider;

    s16* dopY;
    s16* dopX;
    s32 effects;
    s32 i;
    u32* pVramFlag;

    s16 offsetX, offsetY;
    dopY = &DOPPLEGANGER.posY.i.hi;
    dopX = &DOPPLEGANGER.posX.i.hi;

    pVramFlag = &g_Dop.vram_flag;
    effects =
        g_Dop.unk04 &
        (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_UNK_0800 |
         EFFECT_UNK_0400 | EFFECT_UNK_0002 | EFFECT_SOLID);
    if (effects == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0002 |
                    EFFECT_SOLID) ||
        effects == (EFFECT_UNK_0800 | EFFECT_UNK_0400 | EFFECT_UNK_0002 |
                    EFFECT_SOLID) ||
        effects == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                    EFFECT_UNK_0400 | EFFECT_UNK_0002 | EFFECT_SOLID)) {
        *pVramFlag |= 8;
        return;
    }

    for (i = 7; i < 14; i++) {
        effects = g_Dop.colWall[i].effects &
                  (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800 |
                   EFFECT_UNK_0002 | EFFECT_SOLID);
        if (effects == (EFFECT_UNK_8000 | EFFECT_SOLID) ||
            effects == (EFFECT_UNK_8000 | EFFECT_UNK_0002 | EFFECT_SOLID) ||
            effects == (EFFECT_UNK_0800 | EFFECT_SOLID) ||
            effects == (EFFECT_UNK_0800 | EFFECT_UNK_0002 | EFFECT_SOLID) ||
            effects == (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0002 |
                        EFFECT_SOLID) ||
            effects == (EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_UNK_0002 |
                        EFFECT_SOLID) ||
            effects == (EFFECT_UNK_0002 | EFFECT_SOLID)) {

            offsetX = *dopX + g_DopSensorsWall[i].x + g_Dop.colWall[i].unkC + 1;
            offsetY = *dopY + g_DopSensorsWall[i].y;
            g_api.CheckCollision(offsetX, offsetY, &collider, 0);

            if (!(collider.effects & EFFECT_SOLID)) {
                *pVramFlag |= 8;
                *dopX += g_Dop.colWall[i].unkC;
                return;
            }
        }

        if ((effects & (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
                (EFFECT_UNK_8000 | EFFECT_UNK_4000) &&
            i != 7 &&
            ((g_Dop.colWall[7].effects & EFFECT_UNK_0800) ||
             !(g_Dop.colWall[7].effects &
               (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
            *pVramFlag |= 8;
            *dopX += g_Dop.colWall[i].unkC;
            return;
        }

        if (((effects &
              (EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_0800)) ==
             (EFFECT_UNK_4000 | EFFECT_UNK_0800)) &&
            i != 13 &&
            ((g_Dop.colWall[13].effects & EFFECT_UNK_8000) ||
             !(g_Dop.colWall[13].effects &
               (EFFECT_UNK_8000 | EFFECT_UNK_0800 | EFFECT_UNK_0002)))) {
            *pVramFlag |= 8;
            *dopX += g_Dop.colWall[i].unkC;
            return;
        }
    }
}
