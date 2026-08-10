// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RNO0_H
#define RNO0_H

#include <stage.h>

#define OVL_EXPORT(x) RNO0_##x
#define STAGE_IS_RNO0
#define INVERTED_STAGE

enum Palettes {
    PAL_NONE,
    PAL_240 = 0x240,
};

enum EntityID {
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
    E_HEART_DROP,                // EntityHeartDrop
    E_ENEMY_BLOOD,               // EntityEnemyBlood
    E_MESSAGE_BOX,               // EntityMessageBox
    E_DUMMY_F,                   // EntityDummy
    E_DUMMY_10,                  // EntityDummy
    E_BACKGROUND_BLOCK,          // EntityBackgroundBlock
    E_LOCK_CAMERA,               // EntityLockCamera
    E_UNK_ID13,                  // EntityUnkId13
    E_EXPLOSION_VARIANTS,        // EntityExplosionVariants
    E_GREY_PUFF,                 // EntityGreyPuff
    E_BG_PILLAR,                 // EntityBackgroundPillar
    E_CORR_DECOR,                // EntityCorridorDecorator
    E_CORRIDOR_EYE,              // EntityLongCorridorEye
    E_CLOCK_ROOM_CONTROLLER,     // EntityClockRoomController
    E_CLOCK_HANDS,               // EntityClockHands
    E_BIRDCAGE_DOOR,             // EntityBirdcageDoor
    E_STATUE,                    // EntityStatue
    E_STATUE_GEAR,               // EntityStatueGear
    E_STONE_DOOR,                // EntityStoneDoor
    E_UNK_1F,                    // OVL_EXPORT(Unused801C2338)
    E_CLOCK_ROOM_SHADOW,         // EntityDummy
    E_GUARDIAN,                  // EntityGuardian
    E_UNK_22,                    // func_us_801D348C_from_are
    E_GUARDIAN_FIRE_WAVE,        // EntityGuardianFireWave
    E_UNK_24,                    // func_us_801D3700_from_are
    E_UNK_25,                    // OVL_EXPORT(Unused801C2C50)
    E_FLOOR_TRAP,                // EntityFloorTrap
    E_THORNWEED,                 // EntityThornweed
    E_CORPSEWEED,                // EntityCorpseweed
    E_CORPSEWEED_PROJECTILE,     // EntityCorpseweedProjectile
    E_STONE_SKULL,               // EntityStoneSkull
    E_JACKO_BONES,               // EntityJackOBones
    E_JACKO_BONES_DEATH_PARTS,   // EntityJackOBonesDeathParts
    E_JACKO_BONES_JACK,          // EntityJackOBonesJack
    E_NOVA_SKELETON,             // EntityNovaSkeleton
    E_NOVA_LASER,                // EntityNovaLaser
    E_NOVA_LASER_PULSE,          // EntityNovaLaserPulse
    E_BLADE_SOLDIER_DEATH_PARTS, // EntityBladeSoldierDeathParts
    E_HAMMER,                    // EntityHammer
    E_GURKHA_BODY_PARTS,         // EntityGurkhaBodyParts
    E_HAMMER_WEAPON,             // EntityHammerWeapon
    E_GURKHA,                    // EntityGurkha
    E_GURKHA_WEAPON,             // EntityGurkhaWeapon
    E_BLADE,                     // EntityBlade
    E_BLADE_WEAPON,              // EntityBladeWeapon
    E_SUB_WEAPON_CONTAINER,      // EntitySubWeaponContainer
    E_SUB_WPN_CONT_GLASS,        // EntitySubWpnContGlass
    E_UNK_3B,                    // func_801C7654
    E_UNK_3C,                    // func_801C77B8
    E_UNK_3D,                    // func_801C7884
    E_GORGON,                    // EntityGorgon
    E_UNK_3F,                    // func_us_801D068C
    E_UNK_40,                    // func_us_801D0CFC
    E_UNK_41,                    // func_us_801D136C
    E_UNK_42,                    // func_us_801D15C0
    E_UNK_43,                    // func_us_801D2038
    E_UNK_44,                    // func_us_801D1BF0
    E_UNK_45,                    // func_us_801D2264
    E_UNK_46,                    // func_us_801D21C8
    E_ELEVATOR,                  // EntityElevator
    E_ELEVATOR_PART,             // EntityElevatorPart
    E_PENDULUM,                  // EntityPendulum
    E_CLOCK_TICK_SOUND,          // EntityClockTickSound
    E_PINK_BLOCK,                // EntityPinkCavernsBlock
    E_MEDUSA_HEAD_SPAWNER,       // EntityMedusaHeadSpawner
    E_MEDUSA_HEAD_BLUE,          // EntityMedusaHeadBlue
    E_MEDUSA_HEAD_YELLOW,        // EntityMedusaHeadYellow
    E_SEALED_DOOR,               // EntitySealedDoor
    NUM_ENTITIES,
};

#endif // RNO0_H
