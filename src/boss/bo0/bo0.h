// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stage.h>

#define STAGE_IS_NO2
#define BOSS_IS_BO0

typedef enum EntityID {
    E_NONE,
    E_UNK_BREAKABLE,        // EntityUnkBreakable
    E_EXPLOSION,            // EntityExplosion
    E_PRIZE_DROP,           // EntityPrizeDrop
    E_DAMAGE_DISPLAY,       // EntityDamageDisplay
    E_RED_DOOR,             // EntityRedDoor
    E_INTENSE_EXPLOSION,    // EntityIntenseExplosion
    E_SOUL_STEAL_ORB,       // EntitySoulStealOrb
    E_ROOM_FOREGROUND,      // EntityRoomForeground
    E_STAGE_NAME_POPUP,     // EntityStageNamePopup
    E_EQUIP_ITEM_DROP,      // EntityEquipItemDrop
    E_RELIC_ORB,            // EntityRelicOrb
    E_PERSISTENT_ITEM_DROP, // EntityPersistentItemDrop
    E_ENEMY_BLOOD,          // EntityEnemyBlood
    E_MESSAGE_BOX,          // EntityMessageBox
    E_DUMMY_F,              // EntityDummy
    E_DUMMY_10,             // EntityDummy
    E_BACKGROUND_BLOCK,     // EntityBackgroundBlock
    E_LOCK_CAMERA,          // EntityLockCamera
    E_UNK_ID13,             // EntityUnkId13
    E_EXPLOSION_VARIANTS,   // EntityExplosionVariants
    E_GREY_PUFF,            // EntityGreyPuff
    E_SKELERANG,            // EntitySkelerang
    E_SKELERANG_BOOMERANG,  // EntitySkelerangBoomerang
    E_SKELERANG_UNKNOWN,    // EntitySkelerangUnknown
    E_UNK_19,               // func_us_801B3D8C
    E_UNK_1A,               // func_us_801B3F30
    E_UNK_1B,               // func_us_801B4148
    E_UNK_1C,               // func_us_801B41A4
    E_UNK_1D,               // func_us_801B4210
    E_3D_BACKGROUND_HOUSE,  // Entity3DBackgroundHouse
    E_3D_HOUSE_SPAWNER,     // Entity3DHouseSpawner
    E_UNK_20,               // func_us_801B4DA4
    E_SPIKES,               // EntitySpikes
    E_SPIKES_PARTS,         // EntitySpikesParts
    E_SPIKES_DUST,          // EntitySpikesDust
    E_SECRET_WALL,          // EntitySecretWall
    E_SECRET_CEILING,       // EntitySecretCeiling
    E_SECRET_WALL_DEBRIS,   // EntitySecretWallDebris
    E_UNK_27,               // EntityMarionette
    E_BIG_RED_FIREBALL,     // EntityBigRedFireball
    E_PRISONER,             // EntityPrisoner
    E_FURNITURE,            // EntityFurniture
    E_UNK_2B,               // func_us_801AD338
    E_OLROX_AFTER_IMAGE,    // EntityOlroxAfterImage
    E_UNK_2D,               // func_us_801AFAF4
    E_PORTAL,               // EntityPortal
    E_PORTAL_SKULLS,        // EntityPortalSkulls
    E_BLAST_ATTACK,         // EntityBlastAttack
    E_GROUND_BLAST,         // EntityGroundBlast
    E_UNK_32,               // func_us_801B0930
    E_UNK_33,               // func_us_801B365C
    E_UNK_34,               // func_us_801B5470
    E_UNK_35,               // func_us_801B551C
    E_UNK_36,               // EntityTrueFormTail
    E_UNK_37,               // func_us_801B6CA4
    E_UNK_38,               // EntityTrueFormHands
    E_LASER_ATTACK,         // EntityLaserAttack
    E_FIREBALL_ATTACK,      // EntityFireballAttack
    E_UNK_3B,               // func_us_801B7BAC
    E_UNK_3C,               // func_us_801B7CC8
    E_OLROX_DROOL,          // EntityRealOlroxDrool
    E_UNK_3E,               // func_us_801BA4AC
    E_LIFE_UP_SPAWN,        // EntityLifeUpSpawn
    E_OWL_KNIGHT,           // EntityOwlKnight
    E_OWL,                  // EntityOwl
    E_OWL_KNIGHT_SWORD,     // EntityOwlKnightSword
    E_OWL_TARGET,           // EntityOwlTarget
    E_BLOODY_ZOMBIE,        // EntityBloodyZombie
    E_BLOOD_DRIPS,          // EntityBloodDrips
    E_BLOOD_SPLATTER,       // EntityBloodSplatter
    E_LASER_EXPLOSION,      // EntityLaserExplosion
    E_SPIKES_DAMAGE,        // EntitySpikesDamage
    E_BOSS_DOORS,           // EntityBossDoors
    E_UNK_4A,               // EntitySealedDoor
    E_CHAIR,                // EntityChair
    E_UNK_4C,               // 0x00000000
    NUM_ENTITIES,
};

enum Palettes {
    PAL_NONE,
    PAL_SPIKES_DUST = 0x161,
    PAL_SKELERANG = 0x200,
    PAL_UNK_203 = 0x203,
    PAL_UNK_205 = 0x205,
    PAL_UNK_209 = 0x209,
    PAL_UNK_20B = 0x20B,
    PAL_BREAKABLE = 0x219,
    PAL_UNK_21B = 0x21B,
    PAL_OWL_KNIGHT = 0x21C,
    PAL_BLOODY_ZOMBIE = 0x223,
    PAL_UNK_237 = 0x237,
    PAL_OWL_KNIGHT_SWORD = 0x2CB,
    PAL_PUFF_OPAQUE_OFFSET = 0x2E0,
};

extern EInit g_EInitInteractable;
extern EInit g_EInitCommon;

#ifdef VERSION_PSP
extern s32 E_ID(SPIKES_PARTS);
extern s32 E_ID(SPIKES_DUST);
extern s32 E_ID(SPIKES_DAMAGE);
extern s32 E_ID(PRISONER);
extern s32 E_ID(3D_BACKGROUND_HOUSE);
extern s32 E_ID(BOSS_DOORS);
extern s32 E_ID(LASER_EXPLOSION);
extern s32 E_ID(FURNITURE);
extern s32 E_ID(OLROX_AFTER_IMAGE);
extern s32 E_ID(UNK_2D);
extern s32 E_ID(PORTAL);
extern s32 E_ID(BLAST_ATTACK);
extern s32 E_ID(GROUND_BLAST);
extern s32 E_ID(UNK_32);
extern s32 E_ID(PORTAL_SKULLS);
extern s32 E_ID(UNK_33);
extern s32 E_ID(FIREBALL_ATTACK);
extern s32 E_ID(LASER_ATTACK);
extern s32 E_ID(OLROX_DROOL);
extern s32 E_ID(UNK_3E);
extern s32 E_ID(LIFE_UP_SPAWN);
#endif
