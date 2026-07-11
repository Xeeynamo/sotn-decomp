// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RNO0_H
#define RNO0_H

#include <stage.h>

#define OVL_EXPORT(x) RNO0_##x
#define STAGE_IS_RNO0

enum Palettes {
    PAL_NONE,
};

enum Entities {
    E_NONE,
    E_BREAKABLE,                 // OVL_EXPORT(EntityBreakable)
    E_EXPLOSION,                 // EntityExplosion
    E_PRIZE_DROP,                // EntityPrizeDrop
    E_DAMAGE_DISPLAY,            // EntityDamageDisplay
    E_RED_DOOR,                  // OVL_EXPORT(EntityRedDoor)
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
    E_BACKGROUND_BLOCK,          // OVL_EXPORT(EntityBackgroundBlock)
    E_LOCK_CAMERA,               // OVL_EXPORT(EntityLockCamera)
    E_UNK_ID13,                  // EntityUnkId13
    E_EXPLOSION_VARIANTS,        // EntityExplosionVariants
    E_GREY_PUFF,                 // EntityGreyPuff
    E_UNK_16,                    // func_us_801CC8F8_from_no0
    E_UNK_17,                    // func_us_801CC750_from_no0
    E_UNK_18,                    // func_us_801CC9B4_from_no0
    E_CLOCK_ROOM_CONTROLLER,     // EntityClockRoomController
    E_CLOCK_HANDS,               // EntityClockHands
    E_BIRDCAGE_DOOR,             // EntityBirdcageDoor
    E_STATUE,                    // EntityStatue
    E_STATUE_GEAR,               // EntityStatueGear
    E_STONE_DOOR,                // EntityStoneDoor
    E_UNK_1F,                    // OVL_EXPORT(Unused801C2338)
    E_DUMMY_20,                  // EntityDummy
    E_ARMOR_LORD,                // EntityArmorLord
    E_UNK_22,                    // func_us_801D348C_from_are
    E_ARMOR_LORD_FIRE_WAVE,      // EntityArmorLordFireWave
    E_UNK_24,                    // func_us_801D3700_from_are
    E_UNK_25,                    // OVL_EXPORT(Unused801C2C50)
    E_FLOOR_TRAP,                // EntityFloorTrap
    E_THORNWEED,                 // EntityThornweed
    E_CORPSEWEED,                // EntityCorpseweed
    E_CORPSEWEED_PROJECTILE,     // EntityCorpseweedProjectile
    E_UNK_2A,                    // func_us_801C7F24
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
    E_UNK_3E,                    // func_us_801CFEA0
    E_UNK_3F,                    // func_us_801D068C
    E_UNK_40,                    // func_us_801D0CFC
    E_UNK_41,                    // func_us_801D136C
    E_UNK_42,                    // func_us_801D15C0
    E_UNK_43,                    // func_us_801D2038
    E_UNK_44,                    // func_us_801D1BF0
    E_UNK_45,                    // func_us_801D2264
    E_UNK_46,                    // func_us_801D21C8
    E_UNK_47,                    // func_us_801C2184_from_no0
    E_UNK_ID1B,                  // EntityUnkId1B
    E_UNK_49,                    // func_us_801C2A34_from_no0
    E_UNK_4A,                    // func_us_801C2B24_from_no0
    E_UNK_4B,                    // func_us_801B7104
    E_MEDUSA_HEAD_SPAWNER,       // EntityMedusaHeadSpawner
    E_MEDUSA_HEAD_BLUE,          // EntityMedusaHeadBlue
    E_MEDUSA_HEAD_YELLOW,        // EntityMedusaHeadYellow
    E_SEALED_DOOR,               // EntitySealedDoor
    NUM_ENTITIES,
};

#endif // RNO0_H
