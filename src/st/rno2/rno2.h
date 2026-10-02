// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RNO2_H
#define RNO2_H

#include <stage.h>

#define STAGE_IS_RNO2
#define INVERTED_STAGE

enum Palettes {
    PAL_NONE,
    PAL_SPIKES_DUST = 0x161,
    PAL_AZAGHAL_BODY_A = 0x220,
    PAL_AZAGHAL_BODY_B = 0x221,
    PAL_AZAGHAL_COMBO_A = 0x222,
    PAL_AZAGHAL_COMBO_B = 0x223,
    PAL_BREAKABLE = 0x226,
    PAL_BREAKABLE_DEBRIS = 0x22A,
    PAL_CTULHU_DEATH = 0x2EE,
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
    E_DEEP_BG_ARCH,             // EntityDeepBackgroundArch
    E_FOUNTAIN_WATER,           // EntityFountainWater
    E_RAMPART,                  // EntityRampart
    E_NIGHT_SKY,                // EntityNightSky
    E_STONE_BRAZIER,            // EntityStoneBrazier
    E_3D_BACKGROUND_HOUSE,      // Entity3DBackgroundHouse
    E_3D_HOUSE_SPAWNER,         // Entity3DHouseSpawner
    E_HOUSE_SHADER,             // EntityHouseShader
    E_SPIKES,                   // EntitySpikes
    E_SPIKES_PARTS,             // EntitySpikesParts
    E_SPIKES_DUST,              // EntitySpikesDust
    E_SPIKES_DAMAGE,            // EntitySpikesDamage
    E_UNK_22,                   // EntityBreakableWall
    E_STONE_BRIDGE_SECRET,      // EntityStoneBridgeSecret
    E_UNK_24,                   // EntityBreakableWallBackside
    E_PRISONER,                 // EntityPrisoner
    E_SEALED_DOOR,              // EntitySealedDoor
    E_CTULHU,                   // EntityCtulhu
    E_CTULHU_FIREBALL,          // EntityCtulhuFireball
    E_CTULHU_ICE_SHOCKWAVE,     // EntityCtulhuIceShockwave
    E_CTULHU_DEATH,             // EntityCtulhuDeath
    E_MALACHI,                  // EntityMalachi
    E_UNK_2C,                   // func_us_801C4960
    E_UNK_2D,                   // func_us_801C4C0C
    E_UNK_2E,                   // func_us_801C4EA8
    E_KARASUMAN,                // EntityKarasuman
    E_KARASUMAN_FEATHER_ATTACK, // EntityKarasumanFeatherAttack
    E_KARASUMAN_ORB_ATTACK,     // EntityKarasumanOrbAttack
    E_KARASUMAN_RAVEN_ATTACK,   // EntityKarasumanRavenAttack
    E_KARASUMAN_FEATHER,        // EntityKarasumanFeather
    E_KARASUMAN_RAVEN_ABSORB,   // EntityKarasumanRavenAbsorb
    E_FLYING_ZOMBIE2,           // EntityFlyingZombie2
    E_FLYING_ZOMBIE1,           // EntityFlyingZombie1
    E_BLOOD_DRIPS,              // EntityBloodDrips
    E_BLOOD_SPLATTER,           // EntityBloodSplatter
    E_AZAGHAL,                  // EntityAzaghal
    E_AZAGHAL_SWORD_HITBOX,     // EntityAzaghalSwordHitbox
    E_BREAKABLE_DEBRIS,         // EntityBreakableDebris
    E_GHOST_DANCER,             // EntityGhostDancer
    E_MEDUSA_HEAD_SPAWNER,      // EntityMedusaHeadSpawner
    E_MEDUSA_HEAD_BLUE,         // EntityMedusaHeadBlue
    E_MEDUSA_HEAD_YELLOW,       // EntityMedusaHeadYellow
    NUM_ENTITIES,
};

Primitive* FindFirstUnkPrim2(Primitive* prim, u8 index);

extern EInit g_EInitObtainable;
extern EInit g_EInitParticle;
extern EInit g_EInitInteractable;
extern EInit g_EInitCommon;

#endif // RNO2_H
