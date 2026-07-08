// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RCEN_H
#define RCEN_H

#include <stage.h>

#define OVL_EXPORT(x) RCEN_##x
#define STAGE_IS_RCEN

enum Palettes {
    PAL_NONE,
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
    E_UNK_16,             // func_us_8019AAFC
    E_UNK_17,             // func_us_801ABD24
    E_UNK_18,             // func_us_8019B5A4
    E_UNK_19,             // func_us_8019B6D4
    E_UNK_1A,             // func_us_8019B8A8
    E_UNK_1B,             // func_us_8019C4EC
    E_UNK_1C,             // func_us_8019C610
    E_UNK_1D,             // func_us_8019C7B8
    E_UNK_1E,             // func_us_8019CDA0
    E_UNK_1F,             // func_us_8019CDF8
    E_UNK_20,             // func_us_8019D330
    E_CUTSCENE_DIALOGUE,  // OVL_EXPORT(EntityCutscene)
    E_UNK_22,             // func_us_8019F148
    E_UNK_23,             // func_us_8019F5F0
    E_UNK_24,             // func_us_8019FE9C
    E_UNK_ID1B,           // EntityUnkId1B
    E_UNK_26,             // func_us_8019F9C0
    E_UNK_27,             // func_us_801B4148_from_bo0
    E_UNK_28,             // func_us_801C123C_from_no4
    NUM_ENTITIES,
};

#endif // RCEN_H
