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
    E_BREAKABLE,               // OVL_EXPORT(EntityBreakable)
    E_EXPLOSION,               // EntityExplosion
    E_PRIZE_DROP,              // EntityPrizeDrop
    E_DAMAGE_DISPLAY,          // EntityDamageDisplay
    E_RED_DOOR,                // OVL_EXPORT(EntityRedDoor)
    E_INTENSE_EXPLOSION,       // EntityIntenseExplosion
    E_SOUL_STEAL_ORB,          // EntitySoulStealOrb
    E_ROOM_FOREGROUND,         // EntityRoomForeground
    E_STAGE_NAME_POPUP,        // EntityStageNamePopup
    E_EQUIP_ITEM_DROP,         // EntityEquipItemDrop
    E_RELIC_ORB,               // EntityRelicOrb
    E_HEART_DROP,              // EntityHeartDrop
    E_ENEMY_BLOOD,             // EntityEnemyBlood
    E_MESSAGE_BOX,             // EntityMessageBox
    E_DUMMY_F,                 // EntityDummy
    E_DUMMY_10,                // EntityDummy
    E_BACKGROUND_BLOCK,        // OVL_EXPORT(EntityBackgroundBlock)
    E_LOCK_CAMERA,             // OVL_EXPORT(EntityLockCamera)
    E_UNK_ID13,                // EntityUnkId13
    E_EXPLOSION_VARIANTS,      // EntityExplosionVariants
    E_GREY_PUFF,               // EntityGreyPuff
    E_UNK_16,                  // func_pspeu_0924B1E8
    E_STAIR_SWITCH = 0x17,     // func_pspeu_0924AE50
    E_SECRET_STAIRS,           // func_pspeu_0924B4F0
    E_UNK_19,                  // func_pspeu_0924FD00
    E_UNK_1A,                  // func_pspeu_09250290
    E_UNK_1B,                  // func_pspeu_0924F928
    E_UNK_1C,                  // func_pspeu_09249B38
    E_UNK_1D,                  // func_pspeu_0924BB48
    E_UNK_1E,                  // func_pspeu_0924BCD0
    E_UNK_1F,                  // func_pspeu_0924F810
    E_UNK_20,                  // func_pspeu_0924A3B0
    E_FLEA_RIDER = 0x21,       // EntityFleaRider
    E_UNK_22,                  // func_pspeu_0924F6C8
    E_CUTSCENE = 0x23,         // func_pspeu_0924CC10
    E_UNK_24,                  // func_pspeu_09248F70
    E_UNK_25,                  // func_pspeu_09249208
    E_UNK_26,                  // func_pspeu_09249388
    E_BREAKABLE_DEBRIS = 0x27, // func_pspeu_09248B90
    E_AXE_KNIGHT_BLUE,         // func_pspeu_09239580
    E_AXE_KNIGHT_AXE,          // func_pspeu_0923A6F0
    E_AXE_KNIGHT_AXE_2,        // func_pspeu_0923A8F8
    E_UNK_ENTITY,              // func_pspeu_09242F28
    E_UNK_2C,                  // func_pspeu_09249898
    E_UNK_2D,                  // func_pspeu_092496C8
    E_UNK_2E,                  // func_pspeu_092497B0
    NUM_ENTITIES,
};

#endif // TOP_H
