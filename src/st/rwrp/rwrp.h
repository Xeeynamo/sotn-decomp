// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RWRP_H
#define RWRP_H

#include <stage.h>

#define OVL_EXPORT(x) RWRP_##x
#define STAGE_IS_RWRP

enum Palettes {
    PAL_NONE,
};

enum Entities {
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
    E_HEART_DROP,         // EntityHeartDrop
    E_ENEMY_BLOOD,        // EntityEnemyBlood
    E_MESSAGE_BOX,        // EntityMessageBox
    E_DUMMY_F,            // EntityDummy
    E_DUMMY_10,           // EntityDummy
    E_BACKGROUND_BLOCK,   // EntityBackgroundBlock
    E_LOCK_CAMERA,        // EntityLockCamera
    E_UNK_ID13,           // EntityUnkId13
    E_EXPLOSION_VARIANTS, // EntityExplosionVariants
    E_GREY_PUFF,          // EntityGreyPuff
    E_UNK_16,             // func_pspeu_09245270
    E_UNK_17,             // func_pspeu_09246360
    NUM_ENTITIES,
};

extern EInit g_EInitObtainable;
extern EInit g_EInitParticle;
extern EInit g_EInitInteractable;
extern EInit g_EInitCommon;
extern EInit g_EInitLockCamera;
extern EInit g_EInitSmallRocks;

#endif // RWRP_H
