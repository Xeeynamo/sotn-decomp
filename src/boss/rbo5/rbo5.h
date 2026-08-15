// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RBO5_H
#define RBO5_H

#include <stage.h>

#define STAGE_IS_RBO5

#ifndef VERSION_PSP
#include "../doppleganger.h"

extern EInit g_EInitParticle;
extern EInit g_EInitLockCamera;
#else
enum Palettes {
    PAL_NONE,
};

typedef enum EntityID {
    E_NONE,
    E_BREAKABLE,          // EntityBreakable
    E_EXPLOSION,          // EntityExplosion
    E_PRIZE_DROP,         // EntityPrizeDrop
    E_DAMAGE_DISPLAY,     // EntityDamageDisplay
    E_RED_DOOR,           // EntityRedDoor
    E_INTENSE_EXPLOSION,  // EntityIntenseExplosion
    E_SOUL_STEAL_ORB,     // EntitySoulStealOrb
    E_ROOM_FOREGROUND,    // EntityRoomForeground
    E_STAGE_NAME_POPUP,   // EntityStageNamePopup
    E_EQUIP_ITEM_DROP,    // EntityEquipItemDrop
    E_RELIC_ORB,          // EntityRelicOrb
    E_HEART_DROP,         // EntityPersistentItemDrop
    E_ENEMY_BLOOD,        // EntityEnemyBlood
    E_MESSAGE_BOX,        // EntityMessageBox
    E_DUMMY_F,            // EntityDummy
    E_DUMMY_10,           // EntityDummy
    E_BACKGROUND_BLOCK,   // EntityBackgroundBlock
    E_LOCK_CAMERA,        // EntityLockCamera
    E_UNK_ID13,           // EntityUnkId13
    E_EXPLOSION_VARIANTS, // EntityExplosionVariants
    E_GREY_PUFF,          // EntityGreyPuff
    E_UNK_16,             // func_pspeu_09248698
    E_UNK_17,             // func_pspeu_0925D020
    E_UNK_18,             // func_pspeu_0925CA08
    E_UNK_19,             // func_pspeu_0925DB68
    E_UNK_1A,             // func_pspeu_0925E6E8
    E_UNK_1B,             // func_pspeu_0925FBF0
    E_UNK_1C,             // func_pspeu_0925D968
    E_UNK_1D,             // func_pspeu_092386A8
    E_UNK_1E,             // func_pspeu_0925EF30
    NUM_ENTITIES,
};
#endif

#endif // RBO5_H
