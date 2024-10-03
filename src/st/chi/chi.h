#ifndef CHI_H
#define CHI_H

#include "stage.h"

#define OVL_EXPORT(x) CHI_##x

typedef enum {
    /* 0x00 */ E_NONE,
    /* 0x01 */ E_ID_01,
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
    /* 0x11 */ E_BACKGROUND_BLOCK,
    /* 0x12 */ E_ID_12,
    /* 0x13 */ E_ID_13,
    /* 0x14 */ E_ID_14,
    /* 0x15 */ E_ID_15, // Created in EntityDemonSwitchWall
    /* 0x16 */ E_DEMON_SWITCH_WALL,
    /* 0x17 */ E_DEMON_SWITCH,
    /* 0x18 */ E_BREAKABLE_WALL,
    /* 0x19 */ E_BREAKABLE_WALL_DEBRIS, // Created in EntityBreakableWallDebris, EntityBreakableWall
    /* 0x1A */ E_ID_1A, //func_8019B914 - CEN.func_8018DB18 (E_ELEVATOR_STATIONARY)? - Created in EntityUnkId01
    /* 0x1B */ E_ID_1B, //func_8019CBA8
    /* 0x1C */ E_FALLING_STAIRS,
    /* 0x1D */ E_FALLING_STEP,
    /* 0x1E */ E_GREMLIN,
    /* 0x1F */ E_GREMLIN_EFFECT,
    /* 0x20 */ E_GREMLIN_FIRE,
    /* 0x21 */ E_SALEM_WITCH,
    /* 0x22 */ E_SALEM_WITCH_GLOW,
    /* 0x23 */ E_SALEM_WITCH_CURSE,
    /* 0x24 */ E_SALEM_WITCH_TRIBOLT_LAUNCH,
    /* 0x25 */ E_SALEM_WITCH_TRIBOLT_PROJECTILE,
    /* 0x26 */ E_THORNWEED,
    /* 0x27 */ E_ID_27, //func_801AA390
    /* 0x28 */ E_ID_28, //func_801AB0C0
    /* 0x29 */ E_ID_29, //func_801AB7CC
    /* 0x2A */ E_ID_2A, //func_801AC074
    /* 0x2B */ E_ID_2B, //func_801AC730
    /* 0x2C */ E_ID_2C, //func_801ACB6C
    /* 0x2D */ E_ID_2D, //func_801ACEF4
} EntityIDs;

extern PfnEntityUpdate PfnEntityUpdates[];

#endif
