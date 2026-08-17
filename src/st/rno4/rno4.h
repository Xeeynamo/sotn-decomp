// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RNO4_H
#define RNO4_H

#include <stage.h>

#define STAGE_IS_RNO4

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
    E_DUMMY_E,                   // EntityDummy
    E_DUMMY_F,                   // EntityDummy
    E_DUMMY_10,                  // EntityDummy
    E_BACKGROUND_BLOCK,          // EntityBackgroundBlock
    E_LOCK_CAMERA,               // EntityLockCamera
    E_DUMMY_13,                  // EntityDummy
    E_EXPLOSION_VARIANTS,        // EntityExplosionVariants
    E_GREY_PUFF,                 // EntityGreyPuff
    E_ALUCARD_WATER_EFFECT,      // EntityAlucardWaterEffect
    E_SPLASH_WATER,              // EntitySplashWater
    E_SURFACING_WATER,           // EntitySurfacingWater
    E_SIDE_WATER_SPLASH,         // EntitySideWaterSplash
    E_SMALL_WATER_DROP,          // EntitySmallWaterDrop
    E_WATER_DROP,                // EntityWaterDrop
    E_UNK_1C,                    // func_us_801C12B0_from_no4
    E_UNK_1D,                    // func_us_801C15F8_from_no4
    E_UNK_1E,                    // func_us_801C5364
    E_UNK_1F,                    // EntityBgColumnsParallax_from_no4
    E_UNK_20,                    // func_us_801C1EE4_from_no4
    E_UNK_21,                    // func_us_801C5C78
    E_UNK_22,                    // func_us_801C5EE4
    E_UNK_23,                    // func_us_801C2850_from_no4
    E_UNK_24,                    // func_us_801C2B78_from_no4
    E_UNK_25,                    // func_us_801C2E60_from_no4
    E_UNK_26,                    // func_us_801C3160_from_no4
    E_UNK_27,                    // func_us_801C34EC_from_no4
    E_UNK_28,                    // func_us_801C37C8_from_no4
    E_UNK_29,                    // func_us_801C3A04_from_no4
    E_UNK_2A,                    // func_us_801C3CC4_from_no4
    E_UNK_2B,                    // func_us_801C3FB0_from_no4
    E_UNK_2C,                    // func_us_801C4228_from_no4
    E_UNK_2D,                    // Unused801C8768
    E_UNK_2E,                    // Unused801C8770
    E_BOAT_ELEVATOR_CHAINS,      // EntityBoatElevatorChains
    E_UNK_30,                    // Unused801C8BD4
    E_UNK_31,                    // Unused801C8BDC
    E_UNK_32,                    // func_us_801A07CC_from_bo3
    E_WATER_BOX,                 // EntityWaterBox
    E_UNK_34,                    // func_us_801C81C8
    E_FLOATING_ICE_PLATFORM,     // EntityFloatingIcePlatform
    E_UNK_36,                    // func_us_801C5518_from_no4
    E_UNK_37,                    // func_us_801C8C54
    E_UNK_38,                    // func_us_801C909C
    E_UNK_39,                    // func_us_801C4BD8_from_no4
    E_UNK_3A,                    // func_us_801C8668
    E_UNK_3B,                    // Unused801C8704
    E_UNK_3C,                    // func_us_801C123C_from_no4
    E_SUBWPN_IN_CONT,            // func_us_801D511C
    E_UNK_3E,                    // func_us_801D58FC
    E_UNK_3F,                    // func_us_801D5BA4
    E_UNK_40,                    // func_us_801D5E90
    E_UNK_41,                    // func_us_801D68E0
    E_UNK_42,                    // func_us_801D6B8C
    E_VENUS_WEED,                // EntityVenusWeed
    E_VENUS_WEED_FLOWER,         // EntityVenusWeedFlower
    E_VENUS_WEED_TENDRIL,        // EntityVenusWeedTendril
    E_VENUS_WEED_DART,           // EntityVenusWeedDart
    E_VENUS_WEED_SPIKE,          // EntityVenusWeedSpike
    E_UNK_48,                    // func_us_801BBE58_from_rnz1
    E_UNK_49,                    // func_us_801BC650_from_rnz1
    E_UNK_4A,                    // func_us_801BCE4C_from_rnz1
    E_UNK_4B,                    // func_us_801BCA5C_from_rnz1
    E_UNK_4C,                    // func_us_801BCB9C_from_rnz1
    E_UNK_4D,                    // func_us_801BCD80_from_rnz1
    E_UNK_4E,                    // func_us_801BCFC8_from_rnz1
    E_UNK_4F,                    // func_us_801C870C
    E_BREAKABLE_CRYSTAL_FLOOR,   // EntityBreakableCrystalFloor
    E_BREAKABLE_WALL,            // EntityBreakableWall
    E_BREAKABLE_WALL_DEBRIS,     // EntityBreakableWallDebris
    E_JACKO_BONES,               // EntityJackOBones
    E_JACKO_DEATH_PARTS,         // EntityJackOBonesDeathParts
    E_JACKO_JACK,                // EntityJackOBonesJack
    E_NOVA_SKELETON,             // EntityNovaSkeleton
    E_NOVA_LASER,                // EntityNovaLaser
    E_NOVA_PULSE,                // EntityNovaLaserPulse
    E_BLADE_SOLDIER_DEATH_PARTS, // EntityBladeSoldierDeathParts
    E_IMP,                       // EntityImp
    E_IMP_SMOKE,                 // EntityImpSmoke
    E_RDAI_UNK33,                // EntityRdaiUnk33
    E_IMP_DEATH_PARTICLE,        // EntityImpDeathParticle
    E_KILLER_FISH,               // EntityKillerFish
    E_KILLER_FISH_DEATH_PUFF,    // EntityKillerFishDeathPuff
    NUM_ENTITIES,
};

#endif // RNO4_H
