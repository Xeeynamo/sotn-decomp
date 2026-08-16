// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RLIB_H
#define RLIB_H

#include <stage.h>

#define STAGE_IS_RLIB

enum Palettes {
    PAL_NONE,
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
    E_UNK_16,               // func_us_801AF280_from_lib
    E_UNK_17,               // func_us_801AF538_from_lib
    E_UNK_18,               // func_us_801AF7B8_from_lib
    E_UNK_19,               // func_us_801AFA80_from_lib
    E_UNK_1A,               // func_us_801AE8E8_from_lib
    E_UNK_1B,               // func_us_801AE7AC_from_lib
    E_UNK_1C,               // func_us_801ADBE8
    E_HARPY_KICK,           // EntityHarpyKick
    E_UNK_1E,               // func_us_801AE414
    E_UNK_1F,               // func_us_801AE534
    E_UNK_20,               // func_us_801AED4C
    E_UNK_21,               // func_us_801D8D44_from_no4
    E_UNK_22,               // func_us_801AEFE0
    E_UNK_23,               // func_us_801AF11C
    E_UNK_24,               // func_us_801AF448
    E_UNK_25,               // func_us_801AF9E8
    E_EXPLODE_PUFF_OPAQUE,  // EntityExplosionPuffOpaque
    E_UNK_27,               // func_us_801AFC88
    E_UNK_28,               // func_us_801AE84C_from_lib
    E_UNK_29,               // func_us_801BAF60_from_lib
    NUM_ENTITIES,
};

#endif // RLIB_H
