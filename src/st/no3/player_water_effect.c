// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no3.h"

static u16 func_801D0A2C(s16 arg0, s16 arg1, s16 arg2, s16* arg3) {
    s16 temp;
    s16* ptr;

    ptr = &g_WaterXTbl[arg0 * 8];
    arg1 -= *ptr++;
    if (arg1 < 0) {
        return 0;
    }
    *arg3++ = arg1;

    temp = *ptr++ - arg1;
    if (temp <= 0) {
        return 0;
    }
    *arg3++ = temp;

    temp = g_splashAspects[*ptr++];
    if (temp) {
        temp = arg1 / temp;
    } else {
        temp = 0;
    }

    temp = *ptr++ - temp;
    if ((temp <= arg2) && (arg2 < *ptr++)) {
        return (arg2 - 0x8000) - temp;
    }
    return 0;
}

// Alucard says "ahh" and turns blue from water contact
void EntityAlucardWaterEffect(Entity* arg0) {
    s16 sp10[2];
    s16 sp18;
    s16 sp20;
    u16 sp28;
    Entity* var_s0;
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

    sp18 = player->posX.i.hi + tilemap->scrollX.i.hi;
    status = g_Player.status;
    if (status & (PLAYER_STATUS_UNK_20 | PLAYER_STATUS_TRANSFORM)) {
        if (status & PLAYER_STATUS_UNK_20) {
            sp4A = 0x14;
            var_s6 = 0x19;
            if (status & PLAYER_STATUS_WOLF_FORM) {
                sp4A = 0xA;
            }
        } else if (
            status & (PLAYER_STATUS_MIST_FORM | PLAYER_STATUS_BAT_FORM)) {
            sp4A = 0xC;
            var_s6 = 5;
        } else if (status & PLAYER_STATUS_WOLF_FORM) {
            sp4A = 0x14;
            var_s6 = 0x19;
        }
    } else {
        sp4A = 0x28;
        var_s6 = 0x19;
    }
    sp20 = var_s6 + (player->posY.i.hi + tilemap->scrollY.i.hi);
    var_s3 = var_s1 = arg0->params;
    var_s3 &= 0xFF;
    var_s1 = var_s1 >> 8;
    for (i = 0; i < var_s1; i++, var_s3++) {
        sp28 = func_801D0A2C(var_s3, sp18, sp20, sp10);
        if (sp28) {
            sp30 = var_s3 * 8;
            break;
        }
    }
    var_s3 = sp28 & 0x7FFF;
    if (arg0->step) {
        // This is significant - velocity is treated as an f32, loading with
        // FIX_TO_I. This is one of the only places in the code where this is
        // used, so we're keeping velocityY as an s32 (not f32) to avoid needing
        // to say velocityY.val everywhere.
        if (FIX_TO_I(player->velocityY) != 0 &&
            !(status & (PLAYER_STATUS_MIST_FORM | PLAYER_STATUS_BAT_FORM))) {
            if (FIX_TO_I(player->velocityY) < 0) {
                if (sp28 == 0) {
                    var_s1 = arg0->ext.aluwater.unk7C;
                    if ((var_s1) && ((var_s1 & 0x7FFF) < 0x11)) {
                        var_s1 = arg0->ext.aluwater.unk88;
                        if (arg0->ext.aluwater.unk8C < 0xE) {
                            var_s7 = ((0xE - arg0->ext.aluwater.unk8C) << 0xB) +
                                     (g_WaterXTbl[var_s1 + 2] << 8) +
                                     (g_WaterXTbl[var_s1 + 5] << 5);
                        } else {
                            if (arg0->ext.aluwater.unk8E < 0xE) {
                                var_s7 =
                                    ((arg0->ext.aluwater.unk8E + 0xE) << 0xB) +
                                    (g_WaterXTbl[var_s1 + 2] << 8) +
                                    (g_WaterXTbl[var_s1 + 6] << 5);
                            } else {
                                var_s7 = g_WaterXTbl[var_s1 + 2] << 8;
                            }
                        }
                        var_s1 = (var_s7 >> 8) & 7;
                        if (var_s1 == 0 || var_s1 == 7) {
                            var_s1 = (var_s7 >> 5) & 7;
                            if (var_s1 == 0 || var_s1 == 7) {
                                var_s1 = 0;
                            }
                        }
                        if (var_s1) {
                            for (i = 0; i < 8; i++) {
                                var_s0 = AllocEntity(
                                    &g_Entities[224], &g_Entities[256]);
                                if (var_s0 == NULL) {
                                    break;
                                }
                                CreateEntityFromEntity(
                                    E_SIDE_WATER_SPLASH, player, var_s0);
                                var_s0->params =
                                    (u16)g_WaterXTbl[arg0->ext.aluwater.unk88 +
                                                     7] +
                                    (var_s1 << 4) + i;
                                var_s0->posY.i.hi += (var_s6 - var_s3);
                                var_s0->zPriority = player->zPriority;
                            }
                        } else {
                            var_s0 =
                                AllocEntity(&g_Entities[224], &g_Entities[256]);
                            if (var_s0 != NULL) {
                                CreateEntityFromEntity(
                                    E_SPLASH_WATER, player, var_s0);
                                var_s0->posX.i.hi = arg0->ext.aluwater.unk80 -
                                                    tilemap->scrollX.i.hi;
                                var_s0->posY.i.hi =
                                    (arg0->ext.aluwater.unk82 -
                                     (arg0->ext.aluwater.unk7C & 0x7FFF)) -
                                    tilemap->scrollY.i.hi;
                                var_s0->zPriority = player->zPriority;
                                if (player->velocityY > FIX(-4)) {
                                    var_s0->params = var_s7 + 1;
                                } else {
                                    var_s0->params = var_s7;
                                }
                            }
                        }
                    }
                }
            } else if ((sp28) && (var_s3 < 9) && (!arg0->ext.aluwater.unk7C)) {
                if (sp10[0] < 0xE) {
                    var_s7 = ((0xE - sp10[0]) << 0xB) +
                             (g_WaterXTbl[sp30 + 2] << 8) +
                             (g_WaterXTbl[sp30 + 5] << 5);
                } else if (sp10[1] < 0xE) {
                    var_s7 = ((sp10[1] + 0xE) << 0xB) +
                             (g_WaterXTbl[sp30 + 2] << 8) +
                             (g_WaterXTbl[sp30 + 6] << 5);
                } else {
                    var_s7 = g_WaterXTbl[sp30 + 2] << 8;
                }
                var_s1 = (var_s7 >> 8) & 7;
                if (var_s1 == 0 || var_s1 == 7) {
                    var_s1 = (var_s7 >> 5) & 7;
                    if (var_s1 == 0 || var_s1 == 7) {
                        var_s1 = 0;
                    }
                }
                if (var_s1) {
                    for (i = 0; i < 8; i++) {
                        var_s0 =
                            AllocEntity(&g_Entities[224], &g_Entities[256]);
                        if (var_s0 == NULL) {
                            break;
                        }
                        CreateEntityFromEntity(
                            E_SIDE_WATER_SPLASH, player, var_s0);
                        var_s0->params =
                            (u16)g_WaterXTbl[sp30 + 7] + (var_s1 << 4) + i;
                        var_s0->posY.i.hi += (var_s6 - var_s3);
                        var_s0->zPriority = player->zPriority;
                    }
                } else {
                    var_s0 = AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (var_s0 != NULL) {
                        CreateEntityFromEntity(E_SPLASH_WATER, player, var_s0);
                        if (player->velocityY > FIX(4)) {
                            var_s0->params = var_s7 + 1;
                        } else {
                            var_s0->params = var_s7 + 2;
                        }
                        var_s0->posY.i.hi += (var_s6 - var_s3);
                        var_s0->params =
                            var_s7; // this nullifies the above block!
                        var_s0->zPriority = player->zPriority;
                    }
                }
            }
        } else {
            if (!(status & PLAYER_STATUS_MIST_FORM) && (sp28)) {
                if (!arg0->ext.aluwater.unk7E) {
                    var_s1 = g_WaterXTbl[sp30 + 7];
                    if (sp18 != arg0->ext.aluwater.unk80) {
                        if ((var_s3 <= sp4A) && (sp10[0] >= 6) &&
                            (sp10[1] >= 6)) {
                            var_s0 =
                                AllocEntity(&g_Entities[224], &g_Entities[256]);
                            if (var_s0 != NULL) {
                                CreateEntityFromEntity(
                                    E_SURFACING_WATER, player, var_s0);
                                var_s0->posY.i.hi += (var_s6 - var_s3);
                                if (player->velocityX != 0) {
                                    var_s0->params = ((sp4A - var_s3) >> 3);
                                    if (var_s0->params == 5) {
                                        var_s0->params = 4;
                                    }
                                } else {
                                    var_s0->params = 0;
                                }
                                var_s0->params |= (g_WaterXTbl[sp30 + 2] << 8);
                                var_s0->ext.aluwater.unk88 = sp30;
                                var_s0->ext.aluwater.unk8A = var_s1;
                                var_s0->zPriority = player->zPriority;
                                arg0->ext.aluwater.unk7E = 8;
                            }
                        }
                    } else if ((var_s1) && (var_s3 <= sp4A) && (sp10[0] >= 6) &&
                               (sp10[1] >= 6)) {
                        var_s0 =
                            AllocEntity(&g_Entities[224], &g_Entities[256]);
                        if (var_s0 != NULL) {
                            CreateEntityFromEntity(
                                E_SURFACING_WATER, player, var_s0);
                            var_s0->posY.i.hi += (var_s6 - var_s3);

                            var_s0->params = g_WaterXTbl[sp30 + 2] << 8;
                            var_s0->ext.aluwater.unk88 = sp30;
                            var_s0->ext.aluwater.unk8A = var_s1;
                            var_s0->zPriority = player->zPriority;
                            arg0->ext.aluwater.unk7E = 8;
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
                            var_s1 = (var_s1 * var_s3) / 80;
                        }
                        if (((var_s1 < 0) && ((g_Player.pl_vram_flag &
                                               TOUCHING_L_WALL) == 0)) ||
                            ((var_s1 > 0) && ((g_Player.pl_vram_flag &
                                               TOUCHING_R_WALL) == 0))) {
                            player->posX.val += var_s1 << 4;
                        }
                    }
                }
            }
        }
        if (arg0->ext.aluwater.unk7E) {
            arg0->ext.aluwater.unk7E--;
        }
        *D_80097448 = var_s3;
        if (status & (PLAYER_STATUS_UNK_20 | PLAYER_STATUS_TRANSFORM)) {
            if (status & PLAYER_STATUS_UNK_20) {
                if (status & PLAYER_STATUS_WOLF_FORM) {
                    if (var_s3 > 4) {
                        D_80097448[1] = var_s3 - 4;
                    } else {
                        D_80097448[1] = 0;
                    }
                    if (var_s3 > 12) {
                        D_80097450 = var_s3 - 12;
                    } else {
                        D_80097450 = 0;
                    }
                } else {
                    if (var_s3 > 8) {
                        D_80097448[1] = var_s3 - 8;
                    } else {
                        D_80097448[1] = 0;
                    }
                    if (var_s3 > 0x18) {
                        D_80097450 = var_s3 - 0x18;
                    } else {
                        D_80097450 = 0;
                    }
                }
            } else if (
                status & (PLAYER_STATUS_MIST_FORM | PLAYER_STATUS_BAT_FORM)) {
                if (var_s3 > 6) {
                    D_80097448[1] = var_s3 - 6;
                } else {
                    D_80097448[1] = 0;
                }
                if (var_s3 > 0x10) {
                    D_80097450 = var_s3 - 0x10;
                } else {
                    D_80097450 = 0;
                }
            } else if (status & PLAYER_STATUS_WOLF_FORM) {
                if (var_s3 > 8) {
                    D_80097448[1] = var_s3 - 8;
                } else {
                    D_80097448[1] = 0;
                }
                if (var_s3 > 0x18) {
                    D_80097450 = var_s3 - 0x18;
                } else {
                    D_80097450 = 0;
                }
            }
        } else {
            if (var_s3 > 0x10) {
                D_80097448[1] = var_s3 - 0x10;
            } else {
                D_80097448[1] = 0;
            }
            if (var_s3 > 0x30) {
                D_80097450 = var_s3 - 0x30;
            } else {
                D_80097450 = 0;
            }
        }
    } else {
        InitializeEntity(g_EInitSpawner);
    }
    arg0->ext.aluwater.unk7C = sp28;
    arg0->ext.aluwater.unk80 = sp18;
    arg0->ext.aluwater.unk82 = sp20;
    arg0->ext.aluwater.unk88 = sp30;
    arg0->ext.aluwater.unk8C = sp10[0];
    arg0->ext.aluwater.unk8E = sp10[1];
}
