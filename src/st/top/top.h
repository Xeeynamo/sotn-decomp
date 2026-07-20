// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef TOP_H
#define TOP_H

#include <stage.h>

#define OVL_EXPORT(x) TOP_##x
#define STAGE_IS_TOP

enum Palettes {
    PAL_NONE,
    PAL_BREAKABLE = 0x238,
    PAL_BREAKABLE_DEBRIS = 0x23C,
};

enum Entities {
    E_NONE,
    E_BREAKABLE,          // OVL_EXPORT(EntityBreakable)
    E_EXPLOSION,          // EntityExplosion
    E_PRIZE_DROP,         // EntityPrizeDrop
    E_DAMAGE_DISPLAY,     // EntityDamageDisplay
    E_RED_DOOR,           // OVL_EXPORT(EntityRedDoor)
    E_INTENSE_EXPLOSION,  // EntityIntenseExplosion
    E_SOUL_STEAL_ORB,     // EntitySoulStealOrb
    E_ROOM_FOREGROUND,    // EntityRoomForeground
    E_STAGE_NAME_POPUP,   // EntityStageNamePopup
    E_EQUIP_ITEM_DROP,    // EntityEquipItemDrop
    E_RELIC_ORB,          // EntityRelicOrb
    E_HEART_DROP,         // EntityHeartDrop
    E_ENEMY_BLOOD,        // EntityEnemyBlood
    E_MESSAGE_BOX,        // EntityMessageBox
    E_DUMMY_F,            // EntityDummy
    E_DUMMY_10,           // EntityDummy
    E_BACKGROUND_BLOCK,   // OVL_EXPORT(EntityBackgroundBlock)
    E_LOCK_CAMERA,        // OVL_EXPORT(EntityLockCamera)
    E_UNK_ID13,           // EntityUnkId13
    E_EXPLOSION_VARIANTS, // EntityExplosionVariants
    E_GREY_PUFF,          // EntityGreyPuff
    E_UNK_16,
    E_STAIR_SWITCH = 0x17,
    E_SECRET_STAIRS,
    E_UNK_19,
    E_UNK_1A,
    E_UNK_1B,
    E_UNK_1C,
    E_UNK_1D,
    E_UNK_1E,
    E_UNK_1F,
    E_UNK_20,
    E_FLEA_RIDER = 0x21, // EntityFleaRider
    E_UNK_22,
    E_CUTSCENE = 0x23,
    E_UNK_24,
    E_UNK_25,
    E_UNK_26,
    E_BREAKABLE_DEBRIS = 0x27,
    E_AXE_KNIGHT_BLUE,
    E_AXE_KNIGHT_AXE,
    E_AXE_KNIGHT_AXE_2,
    E_UNK_ENTITY,
    NUM_ENTITIES,
};

#endif // TOP_H
