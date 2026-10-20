// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RLIB_H
#define RLIB_H

#include <stage.h>

#define STAGE_IS_RLIB

enum Palettes {
    PAL_NONE,
    PAL_LION = 0x200,
    PAL_TIN_MAN = 0x206,
    PAL_CANDLE_TABLE = 0x20F,
    PAL_BREAKABLE = 0x213,
    PAL_SCHMOO = 0x21B,
    PAL_SCARECROW = 0x21E,
    // puff params 0,1
    PAL_PUFF_OPAQUE_OFFSET = 0x2E0,
    // puff params 2 (not used directly, PAL_PUFF_OPAQUE_OFFSET + 3)
    PAL_PUFF_OPAQUE_2 = 0x2E3,
    // puff params 3 (not used directly, PAL_PUFF_OPAQUE_OFFSET + 4)
    PAL_PUFF_OPAQUE_3 = 0x2E4,
};

typedef enum EntityID {
    E_NONE,
    E_BREAKABLE,            // EntityBreakable
    E_EXPLOSION,            // EntityExplosion
    E_PRIZE_DROP,           // EntityPrizeDrop
    E_DAMAGE_DISPLAY,       // EntityDamageDisplay
    E_RED_DOOR,             // EntityRedDoor
    E_INTENSE_EXPLOSION,    // EntityIntenseExplosion
    E_SOUL_STEAL_ORB,       // EntitySoulStealOrb
    E_ROOM_FOREGROUND,      // EntityRoomForeground
    E_STAGE_NAME_POPUP,     // EntityStageNamePopup
    E_EQUIP_ITEM_DROP,      // EntityEquipItemDrop
    E_RELIC_ORB,            // EntityRelicOrb
    E_PERSISTENT_ITEM_DROP, // EntityPersistentItemDrop
    E_ENEMY_BLOOD,          // EntityEnemyBlood
    E_MESSAGE_BOX,          // EntityMessageBox
    E_DUMMY_F,              // EntityDummy
    E_DUMMY_10,             // EntityDummy
    E_BACKGROUND_BLOCK,     // EntityBackgroundBlock
    E_LOCK_CAMERA,          // EntityLockCamera
    E_UNK_ID13,             // EntityUnkId13
    E_EXPLOSION_VARIANTS,   // EntityExplosionVariants
    E_GREY_PUFF,            // EntityGreyPuff
    E_BG_BOOKCASE,          // EntityBackgroundBookcase
    E_BG_FURNITURE,         // EntityBackgroundFurniture
    E_BG_SHADOW,            // EntityBackgroundShadow
    E_DISTANT_SHELVES,      // EntityDistantBookshelves
    E_THICK_BOOKCASE,       // EntityThickBookcase
    E_METAL_LAMP,               // EntityMetalLamp
    E_LION,                 // EntityLion
    E_LION_ATTACK,          // EntityLionAttack
    E_LION_DEATH_PARTS,     // EntityLionDeathParts
    E_TINMAN,               // EntityTinMan
    E_TINMAN_ARM,           // EntityTinManArm
    E_TINMAN_PROJECTILE,    // EntityTinManProjectile
    E_TINMAN_SMOKE,         // EntityTinManSmoke
    E_TINMAN_DEATH_PARTS,   // EntityTinManDeathParts
    E_SCARECROW,            // EntityScarecrow
    E_SCARECROW_LIMB,       // EntityScarecrowLimb
    E_EXPLODE_PUFF_OPAQUE,  // EntityExplosionPuffOpaque
    E_SCHMOO,               // EntitySchmoo
    E_BREAKABLE_DEBRIS,     // EntityBreakableDebris
    E_CANDLE_TABLE,         // EntityCandleTable
    NUM_ENTITIES,
};

#endif // RLIB_H
