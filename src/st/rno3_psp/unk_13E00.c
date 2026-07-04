// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno3/rno3.h"

extern EInit g_EInitCommon;

extern u16 g_WaterSounds[];
extern s16 g_WaterXTbl[];

static s16 g_splashAspects[] = {0, 1, 2, 4, -1, -2, -4, 0};

static u16 func_pspeu_0924B480(s16 arg0, s16 arg1, s16 arg2, s16* arg3) {
    s16 temp_s2;
    s16 temp;
    s16* ptr;

    ptr = &g_WaterXTbl[arg0 * 8];
    arg1 -= (g_Tilemap.width - *ptr++);
    temp_s2 = *ptr++;
    arg1 += temp_s2;
    if (arg1 < 0) {
        return 0;
    }
    *arg3++ = arg1;

    temp = temp_s2 - arg1;
    if (temp <= 0) {
        return 0;
    }
    temp_s2 = temp;
    *arg3 = temp;

    temp = g_splashAspects[*ptr++];
    if (temp) {
        temp = temp_s2 / temp;
    } else {
        temp = 0;
    }

    temp = temp + (g_Tilemap.height - *ptr++);
    if (temp < arg2) {
        return 0;
    }
    if (arg2 <= (g_Tilemap.height - *ptr++)) {
        return 0;
    }
    return ((temp + 0x7FFF) + 1) - arg2;
}

void EntityAlucardWaterEffect(Entity* self) {
    s16 sp10[2];
    s16 posX, posY;
    u16 sp28;
    Entity* tempEntity;
    s16 var_s1;
    s16 var_s3;
    s16 i;
    u16 sp30;
    u16 var_s6;
    u32 var_s7;
    u16 sp4A;
    s32 status;
    Tilemap* tilemap = &g_Tilemap;
    Entity* player = &PLAYER;

    posX = player->posX.i.hi + tilemap->scrollX.i.hi;
    status = g_Player.status;
    if (status & (PLAYER_STATUS_CROUCH | PLAYER_STATUS_TRANSFORM)) {
        if (status & PLAYER_STATUS_CROUCH) {
            sp4A = 0x14;
            if (status & PLAYER_STATUS_WOLF_FORM) {
                sp4A = 0xA;
            }
            var_s6 = 0x19 - sp4A;
        } else if (
            status & (PLAYER_STATUS_MIST_FORM | PLAYER_STATUS_BAT_FORM)) {
            sp4A = 0xC;
            var_s6 = -7;
        } else if (status & PLAYER_STATUS_WOLF_FORM) {
            sp4A = 0x14;
            var_s6 = 5;
        }
    } else {
        sp4A = 0x28;
        var_s6 = -15;
    }
    posY = var_s6 + (player->posY.i.hi + tilemap->scrollY.i.hi);
    var_s3 = var_s1 = self->params;
    var_s3 &= 0xFF;
    var_s1 = var_s1 >> 8;
    for (i = 0; i < var_s1; i++, var_s3++) {
        sp28 = func_pspeu_0924B480(var_s3, posX, posY, sp10);
        if (sp28) {
            sp30 = var_s3 * 8;
            break;
        }
    }
    var_s3 = sp28 & 0x7FFF;
    FntPrint("x_max %x\n", g_Tilemap.width);
    FntPrint("mizu_chk %x\n", sp28);
    FntPrint("sabun %x,%x\n", sp10[0], sp10[1]);
    if (self->step) {
        if (F(player->velocityY).i.hi &&
            (status & (PLAYER_STATUS_MIST_FORM | PLAYER_STATUS_BAT_FORM)) ==
                0) {
            if (F(player->velocityY).i.hi > 0) {
                if (!sp28) {
                    var_s1 = self->ext.aluwater.unk7C;
                    if (var_s1 && (var_s1 & 0x7FFF) < 17) {
                        var_s1 = self->ext.aluwater.unk88;
                        if (self->ext.aluwater.unk8C < 14) {
                            var_s7 = ((14 - self->ext.aluwater.unk8C) << 11) +
                                     (g_WaterXTbl[var_s1 + 2] << 8) +
                                     (g_WaterXTbl[var_s1 + 6] << 5);
                        } else {
                            if (self->ext.aluwater.unk8E < 14) {
                                var_s7 =
                                    ((self->ext.aluwater.unk8E + 14) << 11) +
                                    (g_WaterXTbl[var_s1 + 2] << 8) +
                                    (g_WaterXTbl[var_s1 + 5] << 5);
                            } else {
                                var_s7 = g_WaterXTbl[var_s1 + 2] << 8;
                            }
                        }
                        var_s1 = (var_s7 >> 8) & 7;
                        if (!var_s1 || var_s1 == 7) {
                            var_s1 = (var_s7 >> 5) & 7;
                            if (!var_s1 || var_s1 == 7) {
                                var_s1 = 0;
                            }
                        }
                        if (var_s1) {
                            for (i = 0; i < 8; i++) {
                                tempEntity = AllocEntity(
                                    &g_Entities[224], &g_Entities[256]);
                                if (tempEntity == NULL) {
                                    break;
                                }
                                CreateEntityFromEntity(
                                    E_SIDE_WATER_SPLASH, player, tempEntity);
                                tempEntity->params =
                                    (u16)g_WaterXTbl[self->ext.aluwater.unk88 +
                                                     7] +
                                    (var_s1 << 4) + i;
                                tempEntity->posY.i.hi += var_s6 + var_s3;
                                tempEntity->zPriority = player->zPriority;
                            }
                        } else {
                            tempEntity =
                                AllocEntity(&g_Entities[224], &g_Entities[256]);
                            if (tempEntity != NULL) {
                                CreateEntityFromEntity(
                                    E_SPLASH_WATER, player, tempEntity);
                                tempEntity->posX.i.hi =
                                    self->ext.aluwater.unk80 -
                                    tilemap->scrollX.i.hi;
                                tempEntity->posY.i.hi =
                                    self->ext.aluwater.unk82 +
                                    (self->ext.aluwater.unk7C & 0x7FFF) -
                                    tilemap->scrollY.i.hi;
                                tempEntity->zPriority = player->zPriority;
                                if (player->velocityY > FIX(-4)) {
                                    tempEntity->params = var_s7 + 1;
                                } else {
                                    tempEntity->params = var_s7;
                                }
                            }
                        }
                    }
                }
            } else if (sp28 && (var_s3 < 9) && !self->ext.aluwater.unk7C) {
                if (sp10[0] < 14) {
                    var_s7 =
                        ((14 - sp10[0]) << 11) + (g_WaterXTbl[sp30 + 2] << 8) +
                        (g_WaterXTbl[sp30 + 6] << 5);
                } else if (sp10[1] < 14) {
                    var_s7 =
                        ((sp10[1] + 14) << 11) + (g_WaterXTbl[sp30 + 2] << 8) +
                        (g_WaterXTbl[sp30 + 5] << 5);
                } else {
                    var_s7 = g_WaterXTbl[sp30 + 2] << 8;
                }
                var_s1 = (var_s7 >> 8) & 7;
                if (!var_s1 || var_s1 == 7) {
                    var_s1 = (var_s7 >> 5) & 7;
                    if (!var_s1 || var_s1 == 7) {
                        var_s1 = 0;
                    }
                }
                if (var_s1) {
                    for (i = 0; i < 8; i++) {
                        tempEntity =
                            AllocEntity(&g_Entities[224], &g_Entities[256]);
                        if (tempEntity == NULL) {
                            break;
                        }
                        CreateEntityFromEntity(
                            E_SIDE_WATER_SPLASH, player, tempEntity);
                        tempEntity->params =
                            (u16)g_WaterXTbl[sp30 + 7] + (var_s1 << 4) + i;
                        tempEntity->posY.i.hi += var_s6 + var_s3;
                        tempEntity->zPriority = player->zPriority;
                    }
                } else {
                    tempEntity =
                        AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (tempEntity != NULL) {
                        CreateEntityFromEntity(
                            E_SPLASH_WATER, player, tempEntity);
                        if (player->velocityY < FIX(-4)) {
                            tempEntity->params = var_s7 + 1;
                        } else {
                            tempEntity->params = var_s7 + 2;
                        }
                        tempEntity->params =
                            var_s7; // this nullifies the above block!
                        tempEntity->posY.i.hi += var_s6 + var_s3;
                        tempEntity->zPriority = player->zPriority;
                    }
                }
            }
        } else if ((status & PLAYER_STATUS_MIST_FORM) == 0) {
            if (sp28 && !self->ext.aluwater.unk7E) {
                var_s1 = g_WaterXTbl[sp30 + 7];
                if (posX != self->ext.aluwater.unk80) {
                    if (var_s3 <= sp4A && sp10[0] >= 6 && sp10[1] >= 6) {
                        tempEntity =
                            AllocEntity(&g_Entities[224], &g_Entities[256]);
                        if (tempEntity != NULL) {
                            CreateEntityFromEntity(
                                E_SURFACING_WATER, player, tempEntity);
                            tempEntity->posY.i.hi += var_s6 + var_s3;
                            if (player->velocityX != 0) {
                                tempEntity->params = var_s3 >> 3;
                                if (tempEntity->params >= 5) {
                                    tempEntity->params = 4;
                                }
                            } else {
                                tempEntity->params = 0;
                            }
                            tempEntity->params |= g_WaterXTbl[sp30 + 2] << 8;
                            tempEntity->ext.aluwater.unk88 = sp30;
                            tempEntity->ext.aluwater.unk8A = var_s1;
                            tempEntity->zPriority = player->zPriority;
                            self->ext.aluwater.unk7E = 8;
                        }
                    }
                } else if (
                    var_s1 && var_s3 <= sp4A && sp10[0] >= 6 && sp10[1] >= 6) {
                    tempEntity =
                        AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (tempEntity != NULL) {
                        CreateEntityFromEntity(
                            E_SURFACING_WATER, player, tempEntity);
                        tempEntity->posY.i.hi += var_s6 + var_s3;
                        tempEntity->params = g_WaterXTbl[sp30 + 2] << 8;
                        tempEntity->ext.aluwater.unk88 = sp30;
                        tempEntity->ext.aluwater.unk8A = var_s1;
                        tempEntity->zPriority = player->zPriority;
                        self->ext.aluwater.unk7E = 8;
                    }
                }
            }
            if (sp28) {
                var_s1 = g_WaterXTbl[sp30 + 7];
                if (var_s1 > 0x1000 || var_s1 < -0x1000) {
                    if (var_s3 >= sp4A) {
                        if (status & PLAYER_STATUS_BAT_FORM) {
                            var_s1 = var_s1 * 3 / 4;
                        } else {
                            var_s1 /= 2;
                        }
                    } else {
                        var_s1 = (var_s1 * var_s3) / 0x50;
                    }
                    if ((var_s1 < 0 &&
                         !(g_Player.vram_flag & TOUCHING_L_WALL)) ||
                        (var_s1 > 0 &&
                         !(g_Player.vram_flag & TOUCHING_R_WALL))) {
                        i = player->posX.i.hi;
                        player->posX.val -= var_s1 << 4;
                        g_unkGraphicsStruct.shoveX.i.hi += (player->posX.i.hi - i);
                    }
                }
            }
        }
        if (self->ext.aluwater.unk7E) {
            self->ext.aluwater.unk7E--;
        }
        g_unkGraphicsStruct.D_80097448 = var_s3;
        if (var_s3 > 4) {
            g_unkGraphicsStruct.D_8009744C = var_s3 - 4;
        } else {
            g_unkGraphicsStruct.D_8009744C = 0;
        }
        g_unkGraphicsStruct.D_80097450 = var_s3;
    } else {
        InitializeEntity(g_EInitSpawner);
    }
    self->ext.aluwater.unk7C = sp28;
    self->ext.aluwater.unk80 = posX;
    self->ext.aluwater.unk82 = posY;
    self->ext.aluwater.unk88 = sp30;
    self->ext.aluwater.unk8C = sp10[0];
    self->ext.aluwater.unk8E = sp10[1];
}

INCLUDE_ASM("st/rno3_psp/nonmatchings/rno3_psp/unk_13E00", EntitySplashWater);

INCLUDE_ASM("st/rno3_psp/nonmatchings/rno3_psp/unk_13E00", EntitySurfacingWater);

INCLUDE_ASM("st/rno3_psp/nonmatchings/rno3_psp/unk_13E00", EntitySideWaterSplash);

INCLUDE_ASM("st/rno3_psp/nonmatchings/rno3_psp/unk_13E00", EntitySmallWaterDrop);

INCLUDE_ASM("st/rno3_psp/nonmatchings/rno3_psp/unk_13E00", EntityWaterDrop);
