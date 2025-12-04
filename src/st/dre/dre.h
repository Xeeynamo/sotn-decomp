// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef DRE_H
#define DRE_H

#include <stage.h>

#define OVL_EXPORT(x) DRE_##x
#define STAGE_IS_DRE

enum Palettes {
    PAL_NONE,
    PAL_SUCCUBUS = 0x200,
    PAL_PORTRAIT_ALUCARD = 0x208,
    PAL_PORTRAIT_LISA = 0x210,
    PAL_PORTRAIT_SUCCUBUS = 0x218,
    PAL_UNK_2E0 = 0x2E0,
};

enum Entities {
    E_NONE,
    E_BREAKABLE,                     // EntityBreakable
    E_EXPLOSION,                     // EntityExplosion
    E_PRIZE_DROP,                    // EntityPrizeDrop
    E_NUMERIC_DAMAGE,                // EntityDamageDisplay
    E_RED_DOOR,                      // OVL_EXPORT(EntityRedDoor)
    E_INTENSE_EXPLOSION,             // EntityIntenseExplosion
    E_SOUL_STEAL_ORB,                // EntitySoulStealOrb
    E_ROOM_FOREGROUND,               // EntityRoomForeground
    E_STAGE_NAME_POPUP,              // EntityStageNamePopup
    E_EQUIP_ITEM_DROP,               // EntityEquipItemDrop
    E_RELIC_ORB,                     // EntityRelicOrb
    E_HEART_DROP,                    // EntityHeartDrop
    E_ENEMY_BLOOD,                   // EntityEnemyBlood
    E_MESSAGE_BOX,                   // EntityMessageBox
    E_DUMMY_0F,                      // EntityDummy
    E_DUMMY_10,                      // EntityDummy
    E_BACKGROUND_BLOCK,              // OVL_EXPORT(EntityBackgroundBlock)
    E_LOCK_CAMERA,                   // OVL_EXPORT(EntityLockCamera)
    E_UNK_ID13,                      // EntityUnkId13
    E_EXPLOSION_VARIANTS,            // EntityExplosionVariants
    E_GREY_PUFF,                     // EntityGreyPuff
    E_3D_BACKGROUND_HOUSE,           // Entity3DBackgroundHouse
    E_3D_HOUSE_SPAWNER,              // Entity3DHouseSpawner
    E_BACKGROUND_CLOUDS,             // EntityBackgroundClouds
    E_SUCCUBUS,                      // EntitySuccubus
    E_SUCCUBUS_PETAL,                // EntitySuccubusPetal
    E_SUCCUBUS_WING_OVERLAY,         // EntitySuccubusWingOverlay
    E_SUCCUBUS_CLONE,                // EntitySuccubusClone
    E_SUCCUBUS_PINK_BALL_PROJECTILE, // EntityPinkBallProjectile
    E_SUCCUBUS_WING_SPIKE,           // EntitySuccubusWingSpike
    E_SUCCUBUS_WING_SPIKE_TIP,       // EntitySuccubusWingSpikeTip
    E_SUCCUBUS_CUTSCENE,             // OVL_EXPORT(EntityCutsceneDialogue)
    E_CS_MOVE_ALUCARD,               // EntityCSMoveAlucard
    E_FADE_TO_WHITE1,                // EntityFadeToWhite1
    E_UNK_ID23,                      // EntityUnkId23
    E_FADE_TO_WHITE2,                // EntityFadeToWhite2
};

#endif // DRE_H
