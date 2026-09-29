// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RCEN_H
#define RCEN_H

#include <stage.h>

#define STAGE_IS_RCEN

enum Palettes {
    PAL_NONE,
    PAL_PORTRAIT_ALUCARD = 0x210,
    PAL_PORTRAIT_SHAFT = 0x218,
    PAL_SHAFT_DEATH_FLAMES = 0x2E0,
    PAL_SHAFT_ORB_FLAME_PILLAR = 0x2E4,
    PAL_SHAFT_ORB_FLAME_TRAIL = 0x2E7
};

enum EntityID {
    E_NONE,
    E_BREAKABLE,                  // EntityBreakable
    E_EXPLOSION,                  // EntityExplosion
    E_PRIZE_DROP,                 // EntityPrizeDrop
    E_DAMAGE_DISPLAY,             // EntityDamageDisplay
    E_RED_DOOR,                   // EntityRedDoor
    E_INTENSE_EXPLOSION,          // EntityIntenseExplosion
    E_SOUL_STEAL_ORB,             // EntitySoulStealOrb
    E_ROOM_FOREGROUND,            // EntityRoomForeground
    E_STAGE_NAME_POPUP,           // EntityStageNamePopup
    E_EQUIP_ITEM_DROP,            // EntityEquipItemDrop
    E_RELIC_ORB,                  // EntityRelicOrb
    E_PERSISTENT_ITEM_DROP,       // EntityPersistentItemDrop
    E_ENEMY_BLOOD,                // EntityEnemyBlood
    E_MESSAGE_BOX,                // EntityMessageBox
    E_DUMMY_F,                    // EntityDummy
    E_DUMMY_10,                   // EntityDummy
    E_BACKGROUND_BLOCK,           // EntityBackgroundBlock
    E_LOCK_CAMERA,                // EntityLockCamera
    E_UNK_ID13,                   // EntityUnkId13
    E_EXPLOSION_VARIANTS,         // EntityExplosionVariants
    E_GREY_PUFF,                  // EntityGreyPuff
    E_SHAFT,                      // EntityShaft
    E_SHAFT_MERIDIAN_RINGS,       // EntityShaftMeridianRings
    E_SHAFT_CRYSTAL_BALL,         // EntityShaftCrystalBall
    E_CUTSCENE_SHAFT,             // EntityCutsceneShaft
    E_SHAFT_ATTACK_ORB,           // EntityShaftAttackOrb
    E_SHAFT_FLAME_TRAIL,          // EntityShaftFlameTrail
    E_SHAFT_FLAME_PILLAR,         // EntityShaftFlamePillar
    E_SHAFT_LIGHTNING,            // EntityShaftLightning
    E_SHAFT_LIGHTNING_HITBOX,     // EntityShaftLightningHitbox
    E_SHAFT_ORBIT_ORB,            // EntityShaftOrbitOrb
    E_SHAFT_DEATH_FLAMES,         // EntityShaftDeathFlames
    E_CUTSCENE_DIALOGUE,          // EntityCutscene
    E_UNK_22,                     // func_us_8019F148
    E_UNK_23,                     // func_us_8019F5F0
    E_ELEVATOR_STATIONARY_UNUSED, // EntityElevatorStationary
    E_ELEVATOR_STATIONARY,        // EntityUnkId1B
    E_UNK_26,                     // func_us_8019F9C0
    E_UNK_27,                     // func_us_801B4148_from_bo0
    E_UNK_28,                     // func_us_801C123C_from_no4
    NUM_ENTITIES,
};

#endif // RCEN_H
