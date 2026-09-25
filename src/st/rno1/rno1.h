// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RNO1_H
#define RNO1_H

#include <stage.h>

#define STAGE_IS_RNO1

enum Palettes {
    PAL_NONE,
    PAL_BREAKABLE = 0x22C,
    PAL_BREAKABLE_DEBRIS = 0x230,
};

typedef enum EntityID {
    E_NONE,
    E_BREAKABLE,                // EntityBreakable
    E_EXPLOSION,                // EntityExplosion
    E_PRIZE_DROP,               // EntityPrizeDrop
    E_DAMAGE_DISPLAY,           // EntityDamageDisplay
    E_RED_DOOR,                 // EntityRedDoor
    E_INTENSE_EXPLOSION,        // EntityIntenseExplosion
    E_SOUL_STEAL_ORB,           // EntitySoulStealOrb
    E_ROOM_FOREGROUND,          // EntityRoomForeground
    E_STAGE_NAME_POPUP,         // EntityStageNamePopup
    E_EQUIP_ITEM_DROP,          // EntityEquipItemDrop
    E_RELIC_ORB,                // EntityRelicOrb
    E_PERSISTENT_ITEM_DROP,     // EntityPersistentItemDrop
    E_ENEMY_BLOOD,              // EntityEnemyBlood
    E_MESSAGE_BOX,              // EntityMessageBox
    E_DUMMY_F,                  // EntityDummy
    E_DUMMY_10,                 // EntityDummy
    E_BACKGROUND_BLOCK,         // EntityBackgroundBlock
    E_LOCK_CAMERA,              // EntityLockCamera
    E_UNK_ID13,                 // EntityUnkId13
    E_EXPLOSION_VARIANTS,       // EntityExplosionVariants
    E_GREY_PUFF,                // EntityGreyPuff
    E_FOG,                      // EntityFog
    E_RAIN,                     // EntityRain
    E_RAIN_SFX_FADE,            // EntityFadeRainSound
    E_PARANTHROPUS,             // EntityParanthropus
    E_PARANTHROPUS_BONE_HITBOX, // EntityParanthropusBoneHitbox
    E_PARANTHROPUS_SKULL,       // EntityParanthropusSkull
    E_PARANTHROPUS_THROWN_BONE, // EntityParanthropusThrownBone
    E_STONE_SKULL,              // EntityStoneSkull
    E_JACKO_BONES,              // EntityJackOBones
    E_JACKO_DEATH_PARTS,        // EntityJackOBonesDeathParts
    E_JACKO_JACK,               // EntityJackOBonesJack
    E_NOVA_SKELETON,            // EntityNovaSkeleton
    E_NOVA_LASER,               // EntityNovaLaser
    E_NOVA_PULSE,               // EntityNovaLaserPulse
    E_NOVA_DEATH_PARTS,         // EntityNovaSkeletonDeathParts
    E_ELEVATOR_MACHINE,         // EntityElevatorMachine
    E_SECRET_WALL,              // EntitySecretElevatorWall
    E_WALL_SEGMENT,             // EntityBreakableWallSegment
    E_WALL_PARTICLES,           // EntityWallParticles
    E_WALL_DEBRIS,              // EntityBreakableWallDebris
    E_SECRET_ELEVATOR,          // EntitySecretElevator
    E_BREAKABLE_DEBRIS,         // EntityBreakableDebris
    E_UNK_2C,                   // func_us_801A9BEC
    E_E_BOSS_NEXT_ROOM_DECOR,   // EntityBossAnteRoomDecoration
    E_E_BOSS_ROUND_HALF,        // EntityBossRoundDoorHalf
    E_E_BOSS_ROUND,             // EntityBossRoundDoor
    NUM_ENTITIES,
};

#endif // RNO1_H
