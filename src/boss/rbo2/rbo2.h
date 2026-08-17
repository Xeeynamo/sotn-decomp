// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RBO2_H
#define RBO2_H

#include <stage.h>

#define STAGE_IS_RBO2

enum Palettes {
    PAL_NONE,
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
    E_UNK_16,               // func_us_8019B52C
    E_UNK_17,               // func_us_8019C718
    E_UNK_18,               // func_us_8019C924
    E_UNK_19,               // func_us_8019D4CC
    E_UNK_1A,               // func_us_8019D950
    E_UNK_1B,               // func_us_8019DA04
    E_UNK_1C,               // func_us_8019E558
    E_UNK_1D,               // func_us_8019E920
    E_UNK_1E,               // func_us_8019ECCC
    E_UNK_1F,               // func_us_8019F260
    E_UNK_20,               // func_us_8019F4AC
    E_CERBERUS_GATE_DEBUG,  // EntityCerberusGateDebug
    E_LIFE_UPSPAWN,         // EntityLifeUpSpawn
    E_CUTSCENE_DIALOGUE,    // EntityCutsceneDialogue
    E_UNK_24,               // func_us_801A17C8
    NUM_ENTITIES,
};

#endif // RBO2_H
