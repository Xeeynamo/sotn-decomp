/*
 * File: objects.h
 * Description: SOTN Object header
 *
 * These entity IDs are common across all stages
 */

typedef enum {
    /* 0x00 */ ENTITY_MIN,
    /* 0x01 */ ENTITY_BREAKABLE,
    /* 0x02 */ ENTITY_EXPLOSION,
    /* 0x03 */ ENTITY_ITEM_DROP,
    /* 0x04 */ ENTITY_NUMERIC_DAMAGE,
    /* 0x05 */ ENTITY_RED_DOOR,
    /* 0x06 */ ENTITY_INTENSE_EXPLOSION,
    /* 0x07 */ ENTITY_ABSORB_ORB,
    /* 0x08 */ ENTITY_ROOM_FOREGROUND,
    /* 0x09 */ ENTITY_STAGE_NAME_POPUP,
    /* 0x0A */ ENTITY_HEART_DROP,
    /* 0x0B */ ENTITY_RELIC,
    /* 0x0C */ ENTITY_COLLECTABLE,
    /* 0x0D */ ENTITY_ENEMY_BLOOD,
    /* 0x0E */ ENTITY_0E,
    /* 0x0F */ ENTITY_0F,
    /* 0x13 */ ENTITY_13 = 0x13
} SotnEntityIds;