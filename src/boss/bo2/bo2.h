// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef BO2_H
#define BO2_H

#include <stage.h>

#define STAGE_IS_BO2

enum Palettes {
    PAL_NONE,
};

typedef enum EntityID {
    E_NONE,
    E_BREAKABLE,                        // EntityBreakable
    E_EXPLOSION,                        // EntityExplosion
    E_PRIZE_DROP,                       // EntityPrizeDrop
    E_DAMAGE_DISPLAY,                   // EntityDamageDisplay
    E_RED_DOOR,                         // EntityRedDoor
    E_INTENSE_EXPLOSION,                // EntityIntenseExplosion
    E_SOUL_STEAL_ORB,                   // EntitySoulStealOrb
    E_ROOM_FOREGROUND,                  // EntityRoomForeground
    E_STAGE_NAME_POPUP,                 // EntityStageNamePopup
    E_EQUIP_ITEM_DROP,                  // EntityEquipItemDrop
    E_RELIC_ORB,                        // EntityRelicOrb
    E_PERSISTENT_ITEM_DROP,             // EntityPersistentItemDrop
    E_ENEMY_BLOOD,                      // EntityEnemyBlood
    E_MESSAGE_BOX,                      // EntityMessageBox
    E_DUMMY_F,                          // EntityDummy
    E_DUMMY_10,                         // EntityDummy
    E_BACKGROUND_BLOCK,                 // EntityBackgroundBlock
    E_LOCK_CAMERA,                      // EntityLockCamera
    E_UNK_ID13,                         // EntityUnkId13
    E_EXPLOSION_VARIANTS,               // EntityExplosionVariants
    E_GREY_PUFF,                        // EntityGreyPuff
    E_UNK_16,                           // func_us_801A3E04
    E_MINOTAUR,                         // func_us_801A269C
    E_MINOTAUR_ATTACK_HITBOX,           // EntityMinotaurAttackHitbox
    E_MINOTAUR_FIREBALL,                // EntityMinotaurFireball
    E_MINOTAUR_SPIT_LIQUID,             // EntityMinotaurSpitLiquid
    E_WEREWOLF,                         // func_us_801B385C
    E_WEREWOLF_ATTACK_HITBOX,           // EntityWerewolfAttackHitbox
    E_UNK_1D,                           // func_us_801B503C
    E_WEREWOLF_SPIN_ATTACK_AFTER_IMAGE, // EntityWerewolfSpinAttackAfterImage
    E_UNK_1F,                           // func_us_801B52FC
    E_WEREWOLF_DEATH_FLAMES,            // EntityWerewolfDeathFlames
    E_MINOTAUR_DEATH_PUFF,              // EntityMinotaurDeathPuff
    E_BOSS_TORCH,                       // EntityBossTorch
    E_BOSS_DOORS,                       // EntityBossDoors
    E_LIFE_UPSPAWN,                     // EntityLifeUpSpawn
    E_CUTSCENE_DIALOGUE,                // EntityCutsceneDialogue
    E_UNK_26,                           // func_us_801A6EF8
    E_UNK_27,                           // func_us_801A7340
    E_UNK_28,                           // func_us_801A460C
    E_UNK_29,                           // func_us_801A4BA4
    NUM_ENTITIES,
};

#endif // BO2_H
