// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RNO1_H
#define RNO1_H

#include <stage.h>

#define STAGE_IS_RNO1

enum Palettes {
    PAL_NONE,
};

typedef enum EntityID {
    E_NONE,
    E_BREAKABLE,                 // EntityBreakable
    E_EXPLOSION,                 // EntityExplosion
    E_PRIZE_DROP,                // EntityPrizeDrop
    E_DAMAGE_DISPLAY,            // EntityDamageDisplay
    E_RED_DOOR,                  // EntityRedDoor
    E_INTENSE_EXPLOSION,         // EntityIntenseExplosion
    E_SOUL_STEAL_ORB,            // EntitySoulStealOrb
    E_ROOM_FOREGROUND,           // EntityRoomForeground
    E_STAGE_NAME_POPUP,          // EntityStageNamePopup
    E_EQUIP_ITEM_DROP,           // EntityEquipItemDrop
    E_RELIC_ORB,                 // EntityRelicOrb
    E_PERSISTENT_ITEM_DROP,      // EntityPersistentItemDrop
    E_ENEMY_BLOOD,               // EntityEnemyBlood
    E_MESSAGE_BOX,               // EntityMessageBox
    E_DUMMY_F,                   // EntityDummy
    E_DUMMY_10,                  // EntityDummy
    E_BACKGROUND_BLOCK,          // EntityBackgroundBlock
    E_LOCK_CAMERA,               // EntityLockCamera
    E_UNK_ID13,                  // EntityUnkId13
    E_EXPLOSION_VARIANTS,        // EntityExplosionVariants
    E_GREY_PUFF,                 // EntityGreyPuff
    E_UNK_16,                    // func_us_801A68AC
    E_UNK_17,                    // func_us_801A700C
    E_UNK_18,                    // func_us_801B7CC4_from_no1
    E_PARANTHROPUS,              // EntityParanthropus
    E_PARANTHROPUS_BONE_HITBOX,  // EntityParanthropusBoneHitbox
    E_PARANTHROPUS_SKULL,        // EntityParanthropusSkull
    E_PARANTHROPUS_THROWN_BONE,  // EntityParanthropusThrownBone
    E_UNK_1D,                    // func_us_801C7F24_from_rno0
    E_JACKO_BONES,               // EntityJackOBones
    E_JACKO_DEATH_PARTS,         // EntityJackOBonesDeathParts
    E_JACKO_JACK,                // EntityJackOBonesJack
    E_NOVA_SKELETON,             // EntityNovaSkeleton
    E_NOVA_LASER,                // EntityNovaLaser
    E_NOVA_PULSE,                // EntityNovaLaserPulse
    E_BLADE_SOLDIER_DEATH_PARTS, // EntityBladeSoldierDeathParts
    E_UNK_25,                    // func_us_801B8F50_from_no1
    E_UNK_26,                    // func_us_801BE880_from_no1
    E_UNK_27,                    // func_us_801BEB54_from_no1
    E_UNK_28,                    // func_us_801BEE00_from_no1
    E_UNK_29,                    // func_us_801BF074_from_no1
    E_UNK_2A,                    // func_us_801A86A8
    E_BREAKABLE_DEBRIS,          // EntityBreakableDebris
    E_UNK_2C,                    // func_us_801A9BEC
    E_UNK_2D,                    // func_us_801B9028_from_no1
    E_UNK_2E,                    // func_us_80198A18_from_rbo4
    E_UNK_2F,                    // func_us_801A9A8C
    NUM_ENTITIES,
};

#endif // RNO1_H
