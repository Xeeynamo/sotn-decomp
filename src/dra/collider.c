// SPDX-License-Identifier: AGPL-3.0-or-later
//! PSPO=4,p
#include "dra.h"

typedef enum {
    // right slanting 45* angle (/)
    COLLISION_TYPE_RIGHT_45_ANGLE = 0x00,

    // left slanting 45* angle (\)
    COLLISION_TYPE_LEFT_45_ANGLE = 0x03,

    // right slanting 45* angle on ceiling (\)
    COLLISION_TYPE_RIGHT_CEILING_45_ANGLE = 0x04,

    // left slanting 45* angle on ceiling (/)
    COLLISION_TYPE_LEFT_CEILING_45_ANGLE = 0x07,

    // 22.5* angle sloping left (/) takes two tiles to go up one tile
    COLLISION_TYPE_LEFT_225_ANGLE_1 = 0x08,

    // tile #2 of previous
    COLLISION_TYPE_LEFT_225_ANGLE_2 = 0x09,

    // flat tile you can press down + jump to drop through
    COLLISION_TYPE_FLAT_DROP_THROUGH = 0x67,

    // water
    COLLISION_TYPE_WATER = 0x6D
} CollisionTypes;

void CheckCollision(s32 x, s32 y, Collider* res, s32 unk) {
    Collider col0;
    Collider col1;
    s32 posX, posY;
    u32 offset;
    u8 colType;

    posX = x + g_Tilemap.scrollX.i.hi;
    posY = y + g_Tilemap.scrollY.i.hi;
    if (posX < 0 || posX >= g_Tilemap.hSize << 8 || posY < 0 ||
        posY >= g_Tilemap.vSize << 8) {
        colType = 0;
    } else {
        s32 tileIdx = (posX >> 4) + (posY >> 4) * g_Tilemap.hSize * 0x10;
        u16 colTile = g_Tilemap.fg[tileIdx];
        colType = g_Tilemap.tileDef->collision[colTile];
    }
    res->effects = EFFECT_NONE;
    res->unk4 = res->unk14 = -(posX & 0xF);
    res->unkC = res->unk1C = res->unk14 + 0xF;
    res->unk8 = res->unk18 = -(posY & 0xF);
    res->unk10 = res->unk20 = res->unk18 + 0xF;
    if ((colType & 0x80) == 0) {
        res->effects = colType & 3;
        return;
    }

    offset = 0;
    switch (colType - 0x80) {
    case 0x01:
    case 0x02:
    case 0x0A:
    case 0x0B:
    case 0x18:
    case 0x19:
        if (!unk) {
            CheckCollision(x, y + res->unk18 - 1, &col0, true);
            if (col0.effects & EFFECT_UNK_8000) {
                if (col0.effects & EFFECT_SOLID) {
                    res->unk18 += col0.unk18 - 1;
                }
                res->effects = col0.effects |= EFFECT_SOLID | EFFECT_UNK_0002;
            } else {
                res->effects = EFFECT_UNK_8000 | EFFECT_SOLID | EFFECT_UNK_0002;
            }
        } else {
            res->effects = EFFECT_SOLID;
        }
        break;

    case COLLISION_TYPE_RIGHT_45_ANGLE:
        if (res->unk1C + res->unk20 < 0x10) {
            res->unk14 = res->unk18 = res->unk1C + res->unk20 - 0xF;
            res->effects = EFFECT_UNK_8000 | EFFECT_SOLID;
        } else {
            res->effects = EFFECT_UNK_8000;
        }
        break;

    case COLLISION_TYPE_LEFT_225_ANGLE_1:
        offset = 0x10;
    case COLLISION_TYPE_LEFT_225_ANGLE_2:
        if (res->unk1C + offset + res->unk20 * 2 < 0x20) {
            res->unk14 = res->unk1C + offset + res->unk20 * 2 - 0x1F;
            res->unk18 = ((res->unk1C + offset) >> 1) + res->unk20 - 0xF;
            res->effects = EFFECT_UNK_8000 | EFFECT_UNK_1000 | EFFECT_SOLID;
        } else {
            res->effects = EFFECT_UNK_8000 | EFFECT_UNK_1000;
        }
        break;

    case 0x14:
        offset = 0x10;
    case 0x15:
        offset += 0x10;
    case 0x16:
        offset += 0x10;
    case 0x17:
        if (res->unk1C + offset + res->unk20 * 4 < 0x40) {
            res->unk14 = res->unk1C + offset + res->unk20 * 4 - 0x3F;
            res->unk18 = ((res->unk1C + offset) >> 2) + res->unk20 - 0xF;
            res->effects = EFFECT_UNK_8000 | EFFECT_UNK_2000 | EFFECT_SOLID;
        } else {
            res->effects = EFFECT_UNK_8000 | EFFECT_UNK_2000;
        }
        break;

    case COLLISION_TYPE_LEFT_45_ANGLE:
        if (res->unk1C >= res->unk20) {
            res->unk18 = res->unk20 - res->unk1C;
            res->unk1C = -res->unk18;
            res->effects = EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_SOLID;
        } else {
            res->effects = EFFECT_UNK_8000 | EFFECT_UNK_4000;
        }
        break;

    case 0x0C:
        offset = 0x10;
    case 0x0D:
        if (res->unk1C + offset >= res->unk20 * 2) {
            res->unk18 = res->unk20 - (offset + res->unk1C >> 1);
            res->effects = EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_1000 |
                           EFFECT_SOLID;
        } else {
            res->effects = EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_1000;
        }
        break;

    case 0x1A:
        offset = 0x10;
    case 0x1B:
        offset += 0x10;
    case 0x1C:
        offset += 0x10;
    case 0x1D:
        if (res->unk1C + offset >= res->unk20 * 4) {
            res->unk18 = res->unk20 - (res->unk1C + offset) / 4;
            res->effects = EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_2000 |
                           EFFECT_SOLID;
        } else {
            res->effects = EFFECT_UNK_8000 | EFFECT_UNK_4000 | EFFECT_UNK_2000;
        }
        break;

    case 0x05:
    case 0x06:
    case 0x10:
    case 0x11:
    case 0x22:
    case 0x23:
        if (!unk) {
            CheckCollision(x, y + res->unk20 + 1, &col1, true);
            if (col1.effects & EFFECT_UNK_0800) {
                if (col1.effects & EFFECT_SOLID) {
                    res->unk20 += col1.unk20 + 1;
                }
                res->effects = col1.effects |= EFFECT_UNK_0002 | EFFECT_SOLID;
            } else {
                res->effects = EFFECT_UNK_0800 | EFFECT_UNK_0002 | EFFECT_SOLID;
            }
        } else {
            res->effects = EFFECT_SOLID;
        }
        break;

    case COLLISION_TYPE_RIGHT_CEILING_45_ANGLE:
        if (res->unk1C <= res->unk20) {
            res->unk14 = res->unk1C - res->unk20;
            res->unk20 = -res->unk14;
            res->effects = EFFECT_UNK_0800 | EFFECT_SOLID;
        } else {
            res->effects = EFFECT_UNK_0800;
        }
        break;

    case 0x0E:
        offset = 0x10;
    case 0x0F:
        if (res->unk1C + offset <= res->unk20 * 2) {
            res->unk14 = res->unk1C + offset - res->unk20 * 2;
            res->unk20 = -res->unk14 / 2;
            res->effects = EFFECT_UNK_1000 | EFFECT_UNK_0800 | EFFECT_SOLID;
        } else {
            res->effects = EFFECT_UNK_1000 | EFFECT_UNK_0800;
        }
        break;

    case 0x1E:
        offset = 0x10;
    case 0x1F:
        offset += 0x10;
    case 0x20:
        offset += 0x10;
    case 0x21:
        if (res->unk1C + offset <= res->unk20 * 4) {
            res->unk14 = res->unk1C + offset - res->unk20 * 4;
            res->unk20 = -res->unk14 / 4;
            res->effects = EFFECT_UNK_2000 | EFFECT_UNK_0800 | EFFECT_SOLID;
        } else {
            res->effects = EFFECT_UNK_2000 | EFFECT_UNK_0800;
        }
        break;

    case COLLISION_TYPE_LEFT_CEILING_45_ANGLE:
        if (res->unk1C + res->unk20 > 0xE) {
            res->unk1C = res->unk20 = res->unk14 + 0xF + res->unk18;
            res->effects = EFFECT_UNK_4000 | EFFECT_UNK_0800 | EFFECT_SOLID;
        } else {
            res->effects = EFFECT_UNK_4000 | EFFECT_UNK_0800;
        }
        break;

    case 0x12:
        offset = 0x10;
    case 0x13:
        if (res->unk1C + offset + res->unk20 * 2 > 0x1D) {
            res->unk20 =
                (((res->unk14 + offset - 0xF) >> 1) + 0xF) + res->unk18;
            res->effects = EFFECT_UNK_4000 | EFFECT_UNK_1000 | EFFECT_UNK_0800 |
                           EFFECT_SOLID;
        } else {
            res->effects = EFFECT_UNK_4000 | EFFECT_UNK_1000 | EFFECT_UNK_0800;
        }
        break;

    case 0x24:
        offset = 0x10;
    case 0x25:
        offset += 0x10;
    case 0x26:
        offset += 0x10;
    case 0x27:
        if (res->unk1C + offset + res->unk20 * 4 > 0x3B) {
            res->unk20 =
                (((res->unk14 + offset - 0x2D) >> 2) + 0xF) + res->unk18;
            res->effects = EFFECT_UNK_4000 | EFFECT_UNK_2000 | EFFECT_UNK_0800 |
                           EFFECT_SOLID;
        } else {
            res->effects = EFFECT_UNK_4000 | EFFECT_UNK_2000 | EFFECT_UNK_0800;
        }
        break;

    case 0x7F:
        if (res->unk20 < 8) {
            res->effects = EFFECT_UNK_0002 | EFFECT_SOLID;
            res->unk18 += 8;
        }
        break;

    case 0x7E:
        if (res->unk20 >= 8) {
            res->effects = EFFECT_UNK_0002 | EFFECT_SOLID;
            res->unk20 -= 8;
        }
        break;

    case 0x7D:
        if (res->unk20 < 8) {
            res->effects = EFFECT_SOLID;
            res->unk18 += 8;
        }
        break;

    case 0x7C:
        if (res->unk20 >= 8) {
            res->effects = EFFECT_SOLID;
            res->unk20 -= 8;
        }
        break;

    case 0x7B:
        res->effects = EFFECT_QUICKSAND;
        break;

    case 0x7A:
        if (res->unk20 < 8) {
            res->effects = EFFECT_QUICKSAND;
            res->unk18 += 8;
        }
        break;

    case 0x79:
        if (res->unk20 < 8) {
            res->effects = EFFECT_WATER;
            res->unk18 += 8;
        }
        break;

    case 0x78:
        res->effects = EFFECT_MIST_ONLY | EFFECT_UNK_0002 | EFFECT_SOLID;
        break;

    case 0x77:
    case 0x76:
    case 0x75:
    case 0x74:
        res->effects = EFFECT_UNK_0020;
        break;

    case 0x73:
    case 0x72:
    case 0x71:
    case 0x70:
    case 0x6F:
    case 0x6E:
        res->effects = EFFECT_UNK_0002 | EFFECT_SOLID;
        break;

    case COLLISION_TYPE_WATER:
        res->effects = EFFECT_WATER;
        break;

    case 0x6C:
    case 0x6B:
        break;

    case 0x6A:
        if (res->unk20 >= 8) {
            res->effects = EFFECT_WATER;
            res->unk20 -= 8;
        }
        break;

    case 0x69:
        if (res->unk20 >= 8) {
            res->effects = EFFECT_QUICKSAND;
            res->unk20 -= 8;
        }
        break;

    case 0x68:
        if (res->unk20 < 8) {
            res->effects = EFFECT_SOLID_FROM_ABOVE | EFFECT_SOLID;
            res->unk18 += 8;
        }
        break;

    case COLLISION_TYPE_FLAT_DROP_THROUGH:
        if (res->unk20 >= 8) {
            res->effects = EFFECT_SOLID_FROM_ABOVE | EFFECT_SOLID;
            res->unk20 -= 8;
        }
        break;

    case 0x66:
        if (res->unk20 < 8) {
            res->effects = EFFECT_SOLID_FROM_BELOW | EFFECT_SOLID;
            res->unk18 += 8;
        }
        break;

    case 0x65:
        if (res->unk20 >= 8) {
            res->effects = EFFECT_SOLID_FROM_BELOW | EFFECT_SOLID;
            res->unk20 -= 8;
        }
        break;
    }
}
