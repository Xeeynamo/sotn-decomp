// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RNZ0_H
#define RNZ0_H

#include <stage.h>

#define STAGE_IS_RNZ0

#define OVL_EXPORT(x) RNZ0_##x

enum Palettes {
    PAL_NONE,
    PAL_FIREDEMON_15E = 0x15E,
    PAL_FIREDEMON_15F = 0x15F,
    PAL_BREAKABLE = 0x236,
    PAL_UNK_237 = 0x237,
    PAL_UNK_238 = 0x238,
    PAL_UNK_239 = 0x239,
    PAL_CTULHU_DEATH = 0x2EE,
};

typedef enum EntityIDs {
    /* 0x00 */ E_NONE,
    /* 0x01 */ E_BREAKABLE,
    /* 0x02 */ E_EXPLOSION,
    /* 0x03 */ E_PRIZE_DROP,
    /* 0x04 */ E_NUMERIC_DAMAGE,
    /* 0x05 */ E_RED_DOOR,
    /* 0x06 */ E_INTENSE_EXPLOSION,
    /* 0x07 */ E_SOUL_STEAL_ORB,
    /* 0x08 */ E_ROOM_FOREGROUND,
    /* 0x09 */ E_STAGE_NAME_POPUP,
    /* 0x0A */ E_EQUIP_ITEM_DROP,
    /* 0x0B */ E_RELIC_ORB,
    /* 0x0C */ E_HEART_DROP,
    /* 0x0D */ E_ENEMY_BLOOD,
    /* 0x0E */ E_MESSAGE_BOX,
    /* 0x0F */ E_DUMMY_0F,
    /* 0x10 */ E_DUMMY_10,
    /* 0x11 */ E_BACKGROUND_BLOCK,
    /* 0x12 */ E_LOCK_CAMERA,
    /* 0x13 */ E_UNK_ID13,
    /* 0x14 */ E_EXPLOSION_VARIANTS,
    /* 0x15 */ E_GREY_PUFF,
    /* 0x16 */ E_PURPLE_BRICK_BG,
    /* 0x17 */ E_LEFT_SECRET_WALL,
    /* 0x18 */ E_BOTT_SECRET_FLOOR,
    /* 0x19 */ E_WALL_DEBRIS,
    /* 0x1A */ E_FLOORTRAP,
    /* 0x1B */ E_CTULHU,
    /* 0x1C */ E_CTULHU_FIREBALL,
    /* 0x1D */ E_CTULHU_ICE_SHOCKWAVE,
    /* 0x1E */ E_CTULHU_DEATH,
    /* 0x1F */ E_FIRE_DEMON,
    /* 0x20 */ E_UNK_20,
    /* 0x21 */ E_UNK_21,
    /* 0x22 */ E_UNK_22,
    /* 0x23 */ E_LESSER_DEMON,
    /* 0x24 */ E_UNK_24,
    /* 0x25 */ E_UNK_25,
    /* 0x26 */ E_UNK_26,
    /* 0x27 */ E_GLOBE_TABLE,
    /* 0x28 */ E_LIFE_MAX_TANK,
    /* 0x29 */ E_BLUE_FLAME_TABLE,
    /* 0x2A */ E_RELIC_CONTAINER,
    /* 0x2B */ E_SEALED_DOOR,
    /* 0x2C */ E_RED_EYE_BUST,
    /* 0x2D */ E_CANNON_LEVER,
    /* 0x2E */ E_UNK_2E,
    /* 0x2F */ E_CANNON_SHOT,
    /* 0x30 */ E_UNK_30,
    /* 0x31 */ E_BITTERFLY,
    /* 0x32 */ E_IMP,
    /* 0x33 */ E_UNK_33,
    /* 0x34 */ E_GREMLIN,
    /* 0x35 */ E_UNK_35,
    /* 0x36 */ E_UNK_36,
    /* 0x37 */ E_SALEM_WITCH,
    /* 0x38 */ E_SALEM_WITCH_GLOW,
    /* 0x39 */ E_SALEM_WITCH_CURSE,
    /* 0x3A */ E_SALEM_WITCH_TRIBOLT_LAUNCH,
    /* 0x3B */ E_SALEM_WITCH_TRIBOLT_PROJECTILE
} EntityIDs;

#endif // RNZ0_H

extern Primitive* FindFirstUnkPrim(Primitive* poly);
