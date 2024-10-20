// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"

typedef enum {
    // most common block type
    COLLISION_TYPE_SOLID = 0x03,

    // right slanting 45* angle (/)
    COLLISION_TYPE_RIGHT_45_ANGLE = 0x80,

    // left slanting 45* angle (\)
    COLLISION_TYPE_LEFT_45_ANGLE = 0x83,

    // right slanting 45* angle on ceiling (\)
    COLLISION_TYPE_RIGHT_CEILING_45_ANGLE = 0x84,

    // left slanting 45* angle on ceiling (/)
    COLLISION_TYPE_LEFT_CEILING_45_ANGLE = 0x87,

    // 22.5* angle sloping left (/) takes two tiles to go up one tile
    COLLISION_TYPE_LEFT_225_ANGLE_1 = 0x88,

    // tile #2 of previous
    COLLISION_TYPE_LEFT_225_ANGLE_2 = 0x89,

    // flat tile you can press down + jump to drop through
    COLLISION_TYPE_FLAT_DROP_THROUGH = 0xE7,

    // water
    COLLISION_TYPE_WATER = 0xED
} CollisionTypes;

void CheckCollision(s32 x, s32 y, Collider* res, s32 unk) {
    Collider sp10;
    Collider sp38;
    s32 temp_a0_2;
    int new_var3;
    s32 temp_a0_3;
    s32 absX;
    s32 absY;
    s32 temp_v0_10;
    s32 temp_v0_11;
    int new_var;
    s32 temp_v0_6;
    s32 temp_v0_8;
    s32 temp_v0_9;
    s32 temp_v1_2;
    int new_var2;
    u32 var_a1;
    s32 var_v0_2;
    s32 temp_a0_4;
    u32 temp_a0_5;
    u32 temp_a0_6;
    u32 temp_v1_3;
    u32 temp_v1_4;
    u32 temp_v1_7;
    u32 var_v0;
    u8 colType;

    absX = x + g_Tilemap.scrollX.i.hi;
    absY = y + g_Tilemap.scrollY.i.hi;
    new_var = 0x10;
    if (absX < 0 || (u32)absX >= g_Tilemap.hSize << 8 || absY < 0 ||
        (u32)absY >= g_Tilemap.vSize << 8) {
        colType = 0;
    } else {
        u16 colTile =
            g_Tilemap.fg[(absX >> 4) + (absY >> 4) * g_Tilemap.hSize * new_var];
        colType = g_Tilemap.tileDef->collision[colTile];
    }
    res->effects = 0;
    res->unk4 = res->unk14 = -(absX & 0xF);
    res->unk8 = res->unk18 = -(absY & 0xF);
    res->unkC = res->unk1C = res->unk14 + 0xF;
    res->unk10 = res->unk20 = res->unk18 + 0xF;
    if (!(colType & 0x80)) {
        res->effects = colType & 3;
        return;
    }

    var_a1 = 0;
    switch (colType) {
    case 0x81:
    case 0x82:
    case 0x8A:
    case 0x8B:
    case 0x98:
    case 0x99:
        if (unk == 0) {
            CheckCollision(x, y + res->unk18 - 1, &sp10, 1);
            if (0x8000 & sp10.effects) {
                if (sp10.effects & EFFECT_SOLID) {
                    new_var3 = res->unk18 - 1;
                    res->unk18 = new_var3 + sp10.unk18;
                }
                res->effects = sp10.effects |= EFFECT_SOLID | EFFECT_UNK_0002;
            } else {
                res->effects = EFFECT_UNK_8000 | EFFECT_SOLID | EFFECT_UNK_0002;
            }
        } else {
            res->effects = 1;
        }
        break;
    case COLLISION_TYPE_RIGHT_45_ANGLE:
        temp_v1_2 = res->unk1C + res->unk20;
        if (temp_v1_2 < 0x10) {
            res->unk18 = temp_v1_2 - 0xF;
            res->unk14 = temp_v1_2 - 0xF;
            res->effects = EFFECT_UNK_8000 | EFFECT_SOLID;
        } else {
            res->effects = EFFECT_UNK_8000;
        }
        break;
    case COLLISION_TYPE_LEFT_225_ANGLE_1:
        var_a1 = 0x10;
    case COLLISION_TYPE_LEFT_225_ANGLE_2:
        temp_v1_3 = var_a1 + res->unk1C + res->unk20 * 2;
        if (temp_v1_3 < 0x20) {
            res->unk14 = temp_v1_3 - 0x1F;
            res->effects = EFFECT_UNK_8000 | EFFECT_UNK_1000 | EFFECT_SOLID;
            res->unk18 = ((var_a1 + res->unk1C) >> 1) + res->unk20 - 0xF;
        } else {
            res->effects = EFFECT_UNK_8000 | EFFECT_UNK_1000;
        }
        break;
    case 0x94:
        var_a1 = 0x10;
    case 0x95:
        var_a1 += 0x10;
    case 0x96:
        var_a1 += 0x10;
    case 0x97:
        temp_v1_4 = var_a1 + res->unk1C + res->unk20 * 4;
        if (temp_v1_4 < 0x40) {
            res->unk14 = temp_v1_4 - 0x3F;
            res->effects = EFFECT_UNK_8000 | EFFECT_UNK_2000 | EFFECT_SOLID;
            var_v0 = (var_a1 + res->unk1C) >> 2;
            res->unk18 = var_v0 + res->unk20 - 0xF;
        } else {
            res->effects = EFFECT_UNK_8000 | EFFECT_UNK_2000;
        }
        break;
    case COLLISION_TYPE_LEFT_45_ANGLE:
        if (res->unk1C >= res->unk20) {
            temp_v0_6 = res->unk20 - res->unk1C;
            res->unk18 = temp_v0_6;
            res->unk1C = (-temp_v0_6);
            res->effects = 0xC001;
        } else {
            res->effects = 0xC000;
        }
        break;
    case 0x8C:
        var_a1 = 0x10;
    case 0x8D:
        if (var_a1 + res->unk1C >= res->unk20 * 2) {
            res->unk18 = res->unk20 - (var_a1 + res->unk1C >> 1);
            res->effects = 0xD001;
        } else {
            res->effects = 0xD000;
        }
        break;
    case 0x9A:
        var_a1 = 0x10;
    case 0x9B:
        var_a1 += 0x10;
    case 0x9C:
        var_a1 += 0x10;
    case 0x9D:
        temp_a0_3 = res->unk20;
        temp_v1_7 = var_a1 + res->unk1C;
        if (temp_v1_7 >= temp_a0_3 * 4) {
            res->unk18 = temp_a0_3 - (temp_v1_7 >> 2);
            res->effects = 0xE001;
        } else {
            res->effects = 0xE000;
        }
        break;
    case 0x85:
    case 0x86:
    case 0x90:
    case 0x91:
    case 0xA2:
    case 0xA3:
        if (unk == 0) {
            CheckCollision(x, y + res->unk20 + 1, &sp38, 1);
            if (0x800 & sp38.effects) {
                if (sp38.effects & EFFECT_SOLID) {
                    temp_a0_2 = 1;
                    res->unk20 = res->unk20 + temp_a0_2 + sp38.unk20;
                }
                res->effects = sp38.effects |= 3;
            } else {
                res->effects = 0x803;
            }
        } else {
            res->effects = 1;
        }
        break;
    case COLLISION_TYPE_RIGHT_CEILING_45_ANGLE:
        temp_a0_4 = res->unk1C;
        if (res->unk20 >= temp_a0_4) {
            temp_v0_8 = temp_a0_4 - res->unk20;
            res->unk14 = temp_v0_8;
            res->unk20 = -temp_v0_8;
            res->effects = 0x801;
        } else {
            res->effects = 0x800;
        }
        break;
    case 0x8E:
        var_a1 = 0x10;
    case 0x8F:
        temp_a0_5 = var_a1 + res->unk1C;
        if (res->unk20 * 2 >= var_a1 + res->unk1C) {
            temp_v0_9 = temp_a0_5 - res->unk20 * 2;
            res->unk14 = temp_v0_9;
            res->unk20 = -temp_v0_9 / 2;
            res->effects = 0x1801;
        } else {
            res->effects = 0x1800;
        }
        break;
    case 0x9E:
        var_a1 = 0x10;
    case 0x9F:
        var_a1 += 0x10;
    case 0xA0:
        var_a1 += 0x10;
    case 0xA1:
        temp_a0_6 = var_a1 + res->unk1C;
        if (res->unk20 * 4 >= var_a1 + res->unk1C) {
            temp_v0_10 = temp_a0_6 - res->unk20 * 4;
            res->unk14 = temp_v0_10;
            var_v0_2 = -temp_v0_10;
            if (var_v0_2 < 0) {
                var_v0_2 += 3;
            }
            res->unk20 = (s32)(var_v0_2 >> 2);
            res->effects = 0x2801;
        } else {
            res->effects = 0x2800;
        }
        break;
    case COLLISION_TYPE_LEFT_CEILING_45_ANGLE:
        if (res->unk1C + res->unk20 >= 0xF) {
            res->effects = 0x4801;
            temp_v0_11 = res->unk18 + 0xF;
            temp_v0_11 = temp_v0_11 + res->unk14;
            res->unk20 = temp_v0_11;
            res->unk1C = (u32)temp_v0_11;
        } else {
            res->effects = 0x4800;
        }
        break;
    case 0x92:
        var_a1 = 0x10;
    case 0x93:
        if (var_a1 + res->unk1C + res->unk20 * 2 >= 0x1E) {
            temp_a0_5 = 0xF;
            res->effects = 0x5801;
            res->unk20 = ((var_a1 + res->unk14 - temp_a0_5) >> 1) +
                         (res->unk18 + temp_a0_5);
            ;
        } else {
            res->effects = 0x5800;
        }
        break;
    case 0xA4:
        var_a1 = 0x10;
    case 0xA5:
        var_a1 = var_a1 + 0x10;
    case 0xA6:
        var_a1 += 0x10;
    case 0xA7:
        new_var2 = 0xF;
        if (var_a1 + res->unk1C + res->unk20 * 4 >= 0x3C) {
            res->effects = 0x6801;
            res->unk20 =
                (((var_a1 + res->unk14) - 0x2D) >> 2) + (res->unk18 + new_var2);
        } else {
            res->effects = 0x6800;
        }
        break;
    case 0xFF:
        if (res->unk20 < 8) {
            res->effects = 3;
            res->unk18 = res->unk18 + 8;
        }
        break;
    case 0xFE:
        if (res->unk20 >= 8) {
            res->effects = 3;
            res->unk20 -= 8;
        }
        break;
    case 0xFD:
        if (res->unk20 < 8) {
            res->effects = 1;
            res->unk18 += 8;
        }
        break;
    case 0xFC:
        if (res->unk20 >= 8) {
            res->effects = 1;
            res->unk20 -= 8;
        }
        break;
    case 0xFB:
        res->effects = 4;
        break;
    case 0xFA:
        if (res->unk20 < 8) {
            if (1) {
                res->effects = 4;
            }
            res->unk18 += 8;
        }
        break;
    case 0xF9:
        if (res->unk20 < 8) {
            res->effects = 8;
            res->unk18 += 8;
        }
        break;
    case 0xF8:
        res->effects = 0x13;
        break;
    case 0xF4:
    case 0xF5:
    case 0xF6:
    case 0xF7:
        res->effects = 0x20;
        break;
    case 0xEE:
    case 0xEF:
    case 0xF0:
    case 0xF1:
    case 0xF2:
    case 0xF3:
        res->effects = 3;
        break;
    case COLLISION_TYPE_WATER:
        res->effects = 8;
        break;
    case 0xEA:
        if (res->unk20 >= 8) {
            res->effects = 8;
            res->unk20 -= 8;
        }
        break;
    case 0xE9:
        if (res->unk20 >= 8) {
            res->effects = 4;
            res->unk20 -= 8;
        }
        break;
    case 0xE8:
        if (res->unk20 < 8) {
            res->effects = 0x41;
            res->unk18 += 8;
        }
        break;
    case COLLISION_TYPE_FLAT_DROP_THROUGH:
        if (res->unk20 >= 8) {
            res->effects = 0x41;
            res->unk20 -= 8;
        }
        break;
    case 0xE6:
        if (res->unk20 < 8) {
            res->effects = 0x81;
            res->unk18 += 8;
        }
        break;
    case 0xE5:
        if (res->unk20 >= 8) {
            res->effects = 0x81;
            res->unk20 -= 8;
        }
        break;
    }
}
