// SPDX-License-Identifier: AGPL-3.0-or-later
#include "stage.h"

#define OVL_EXPORT(x) NO0_##x

void EntityExplosionVariants(Entity* entity);
void EntityGreyPuff(Entity* entity);

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
    /* 0x0E */ E_SAVE_GAME_POPUP,
    /* 0x0F */ E_DUMMY_0F,
    /* 0x10 */ E_DUMMY_10,

    /* 0x11 */ E_ID_11 = 0x11,
    /* 0x14 */ E_ID_14 = 0x14,
    /* 0x15 */ E_GREY_PUFF = 0x15,
    /* 0x17 */ E_BG_LIGHTNING = 0x17,
    /* 0x1E */ E_CAVERN_DOOR_LEVER_UNK0 = 0x1E,
    /* 0x20 */ E_DUMMY_20 = 0x20,
    /* 0x27 */ E_FALLING_ROCK_2 = 0x27,
    /* 0x2E */ E_ID_2E = 0x2E,
    /* 0x30 */ E_ID_30 = 0x30,
    /* 0x31 */ E_ID_31,
    /* 0x32 */ E_ID_32,
    /* 0x33 */ E_ID_33,
    /* 0x35 */ E_SPLASH_WATER = 0x35,
    /* 0x36 */ E_SURFACING_WATER,
    /* 0x37 */ E_SIDE_WATER_SPLASH,
    /* 0x38 */ E_SMALL_WATER_DROP,
    /* 0x39 */ E_WATER_DROP,
    /* 0x3A */ E_MERMAN_SPAWNER_3A,
    /* 0x3B */ E_MERMAN_JUMP_WATER,
    /* 0x3C */ E_MERMAN2_UNK1,
    /* 0x3D */ E_MEDIUM_WATER_SPLASH,
    /* 0x3E */ E_MERMAN2_SPIT_FIRE,
    /* 0x3F */ E_MERMAN2_DYING,
    /* 0x40 */ E_MERMAN2_JUMP_AIR,
    /* 0x41 */ E_MERMAN_SPAWNER_41,
    /* 0x42 */ E_MERMAN_SPIT_FIRE,
    /* 0x43 */ E_MERMAN_JUMP_AIR,
    /* 0x44 */ E_MERMAN_DYING,
    /* 0x47 */ E_BONE_SCIMITAR_HEAD = 0x47,
    /* 0x4C */ E_ZOMBIE = 0x4C,
    /* 0x59 */ E_ID_59 = 0x59,
    /* 0x5B */ E_DEATH_5B = 0x5B,
    /* 0x5D */ E_FALLING_ROCK = 0x5D,
    /* 0x5E */ E_DEATH_5E,
    /* 0x60 */ E_FLYING_OWL_UNK60 = 0x60,
    /* 0x62 */ E_WARG_EXP_OPAQUE = 0x62,
} EntityIDs;

extern s16 g_SineTable[];
extern u16 g_eInitGeneric2[];
extern u16 g_InitializeEntityData0[];
extern u16 g_HeartDropArray[];
