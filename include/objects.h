/*
 * File: objects.h
 * Description: SOTN Object header
 *
 * Only the first 0x10 entities are common across all stages
 */

typedef enum {
    /* 0x00 */ ENTITY_UNALLOCATED,

    // Usually those are the small candles, but they can also be the jars
    // from the Arena map or other type of objects that can be broken.
    /* 0x01 */ ENTITY_BREAKABLE,

    /* 0x02 */ ENTITY_EXPLOSION,

    // The price drop that usually comes from breakable objects. Those can be
    // small hearts, big hearts, money, sub-weapons, power ups.
    // The type of drop depends from the SubID.
    /* 0x03 */ ENTITY_PRICE_DROP,

    // Shows the amount of damage dealt or received.
    // The number is the value from the SubID.
    /* 0x04 */ ENTITY_NUMERIC_DAMAGE,

    // The red door that is usually used when changing a stage.
    /* 0x05 */ ENTITY_RED_DOOR,

    /* 0x06 */ ENTITY_INTENSE_EXPLOSION,

    /* 0x07 */ ENTITY_ABSORB_ORB,

    // Used to render big foreground objects that cannot be represented as a
    // tileset. An example is the angels statue located in the loading room.
    /* 0x08 */ ENTITY_ROOM_FOREGROUND,

    // The box that shows the stage name when entering for the first time.
    /* 0x09 */ ENTITY_STAGE_NAME_POPUP,

    // Price drop representing an inventory item. The inventory item itself
    // changes based on the SubID.
    /* 0x0A */ ENTITY_INVENTORY_DROP,

    // Floating relic orb. The type of relic is based on the SubID.
    /* 0x0B */ ENTITY_RELIC_ORB,

    // Similar to ENTITY_INVENTORY but only drops small hearts.
    /* 0x0C */ ENTITY_HEART_DROP,

    // Enemy blood particle. The SubID dictates the direction where the blood
    // will spill.
    /* 0x0D */ ENTITY_ENEMY_BLOOD,

    // Invoke some kind of full-screen menu. Maybe it's the shopping menu?
    /* 0x0E */ ENTITY_0E,

    // Empty entity
    /* 0x0F */ ENTITY_0F,

    // Empty entity
    /* 0x10 */ ENTITY_RESERVED_10,

    // Its use is unknown but it is found in DRA, not in any other overlay.
    // Its meaning depends from the stage currently loaded.
    /* 0x13 */ ENTITY_13 = 0x13,

    /* 0x15 */ ENTITY_15 = 0x15
} SotnEntityIds;

void EntityBreakable(Entity*);
void EntityExplosion(Entity*);
void EntityPriceDrop(Entity*);
void EntityNumericDamage(Entity*);
void EntityRedDoor(Entity*);
void EntityIntenseExplosion(Entity*);
void EntityAbsorbOrb(Entity*);
void EntityRoomForeground(Entity*);
void EntityStageNamePopup(Entity*);
void EntityInventoryDrop(Entity*);
void EntityRelicOrb(Entity*);
void EntityHeartDrop(Entity*);
void EntityEnemyBlood(Entity*);
void EntityUnkId0E(Entity*);
void EntityDummy(Entity*);
