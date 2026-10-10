// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef TEK_H
#define TEK_H
#define STAGE_IS_TEK

#include <stage.h>

// TEK uses the same entity freeze flag that the beta MAD has in st_update.h
extern s32 D_800A6C18;
#define D_80096ED0_mad D_800A6C18

enum Palettes {
    PAL_NONE = 0,
    PAL_DODO_BIRD = 0x200,
    PAL_BONE_SCIMITAR = 0x201,
    PAL_TOAD_FROG = 0x202,
    PAL_BONE_ARCHER = 0x204,
    PAL_GRAVE_KEEPER_TOMBSTONE = 0x208,
    PAL_CROW = 0x20A,
    PAL_JACK_O_BONES = 0x20C,
    PAL_BONE_HALBERD = 0x20E,
    PAL_YORICK = 0x20F,
    PAL_BLADE_MASTER = 0x210,
    PAL_BLADE_SOLDIER = 0x212,
    PAL_NOVA_SKELETON = 0x214,
    PAL_BONE_MUSKET = 0x219,
    PAL_WINGED_GUARD = 0x21D,
    PAL_SPECTRAL_SWORD = 0x21E,
    PAL_SPECTRAL_SWORD_WEAPON = 0x21F,
    PAL_VALHALLA_KNIGHT = 0x22E,
    PAL_DRAGON_RIDER = 0x231,
    PAL_OROBOUROUS = 0x233,
    PAL_BOMB_KNIGHT = 0x236,
    PAL_THORNWEED_CORPSEWEED = 0x23C,
    PAL_VENUS_WEED = 0x240,
};

typedef enum EntityID {
    /* 0x00 */ E_NONE,
    /* 0x01 */ E_BREAKABLE,                   // EntityBreakable
    /* 0x02 */ E_EXPLOSION,                   // EntityExplosion
    /* 0x03 */ E_PRIZE_DROP,                  // EntityPrizeDrop
    /* 0x04 */ E_DAMAGE_DISPLAY,              // EntityDamageDisplay
    /* 0x05 */ E_RED_DOOR,                    // EntityRedDoor
    /* 0x06 */ E_INTENSE_EXPLOSION,           // EntityIntenseExplosion
    /* 0x07 */ E_SOUL_STEAL_ORB,              // EntitySoulStealOrb
    /* 0x08 */ E_ROOM_FOREGROUND,             // EntityRoomForeground
    /* 0x09 */ E_STAGE_NAME_POPUP,            // EntityStageNamePopup
    /* 0x0A */ E_EQUIP_ITEM_DROP,             // EntityEquipItemDrop
    /* 0x0B */ E_RELIC_ORB,                   // EntityRelicOrb
    /* 0x0C */ E_PERSISTENT_ITEM_DROP,        // EntityPersistentItemDrop
    /* 0x0D */ E_ENEMY_BLOOD,                 // EntityEnemyBlood
    /* 0x0E */ E_DUMMY_0E,                    // EntityDummy
    /* 0x0F */ E_DUMMY_0F,                    // EntityDummy
    /* 0x10 */ E_DUMMY_10,                    // EntityDummy
    /* 0x11 */ E_BACKGROUND_BLOCK,            // EntityBackgroundBlock
    /* 0x12 */ E_LOCK_CAMERA,                 // EntityLockCamera
    /* 0x13 */ E_UNK_ID13,                    // EntityUnkId13
    /* 0x14 */ E_EXPLOSION_VARIANTS,          // EntityExplosionVariants
    /* 0x15 */ E_GREY_PUFF,                   // EntityGreyPuff
    /* 0x16 */ E_DODO_BIRD,                   // EntityDodoBird
    /* 0x17 */ E_BONE_SCIMITAR,               // EntityBoneScimitar
    /* 0x18 */ E_BONE_SCIMITAR_PARTS,         // EntityBoneScimitarParts
    /* 0x19 */ E_TOAD,                        // EntityToad
    /* 0x1A */ E_FROG,                        // EntityFrog
    /* 0x1B */ E_BONE_ARCHER,                 // EntityBoneArcher
    /* 0x1C */ E_BONE_ARCHER_ARROW,           // EntityBoneArcherArrow
    /* 0x1D */ E_GRAVE_KEEPER,                // EntityGraveKeeper
    /* 0x1E */ E_GRAVE_KEEPER_HITBOX,         // EntityGraveKeeperHitbox
    /* 0x1F */ E_TOMBSTONE,                   // EntityTombstone
    /* 0x20 */ E_BLACK_CROW,                  // EntityBlackCrow
    /* 0x21 */ E_BLUE_RAVEN,                  // EntityBlueRaven
    /* 0x22 */ E_JACK_O_BONES,                // EntityJackOBones
    /* 0x23 */ E_JACK_O_BONES_PIECES,         // EntityJackOBonesPieces
    /* 0x24 */ E_JACK_O_BONES_JACK,           // EntityJackOBonesJack
    /* 0x25 */ E_BONE_HALBERD,                // EntityBoneHalberd
    /* 0x26 */ E_BONE_HALBERD_ATTACK,         // EntityBoneHalberdAttack
    /* 0x27 */ E_BONE_HALBERD_PIECES,         // EntityBoneHalberdPieces
    /* 0x28 */ E_YORICK,                      // EntityYorick
    /* 0x29 */ E_YORICK_SKULL,                // EntityYorickSkull
    /* 0x2A */ E_YORICK_PIECES,               // EntityYorickPieces
    /* 0x2B */ E_BLADE_MASTER,                // EntityBladeMaster
    /* 0x2C */ E_BLADE_MASTER_ATTACK_HITBOX,  // EntityBladeMasterAttackHitbox
    /* 0x2D */ E_BLADE_MASTER_DEATH_PARTS,    // EntityBladeMasterDeathParts
                                              /* 0x2E */
    E_BLADE_MASTER_DEATH_EXPLOSION,           // EntityBladeMasterDeathExplosion
    /* 0x2F */ E_BLADE_SOLDIER,               // EntityBladeSoldier
    /* 0x30 */ E_BLADE_SOLDIER_ATTACK_HITBOX, // EntityBladeSoldierAttackHitbox
    /* 0x31 */ E_BLADE_SOLDIER_DEATH_PARTS,   // EntityBladeSoldierDeathParts
    /* 0x32 */ E_NOVA_SKELETON,               // EntityNovaSkeleton
    /* 0x33 */ E_NOVA_LASER,                  // EntityNovaLaser
    /* 0x34 */ E_NOVA_LASER_PULSE,            // EntityNovaLaserPulse
    /* 0x35 */ E_NOVA_SKELETON_PIECES,        // EntityNovaSkeletonPieces
    /* 0x36 */ E_BONE_MUSKET,                 // EntityBoneMusket
    /* 0x37 */ E_BONE_MUSKET_UNK,             // EntityBoneMusketUnk
    /* 0x38 */ E_WINGED_GUARD,                // EntityWingedGuard
    /* 0x39 */ E_WINGED_GUARD_PARTS,          // EntityWingedGuardParts
    /* 0x3A */ E_SPECTRAL_SWORD_NO2,          // EntitySpectralSwordNO2
    /* 0x3B */ E_SPECTRAL_SWORD_NO2_AURA,     // EntitySpectralSwordNO2Aura
    /* 0x3C */ E_POLTERGEIST,                 // EntityPoltergeist
    /* 0x3D */ E_SPECTRAL_SWORD_DAI,          // EntitySpectralSwordDAI
    /* 0x3E */ E_SPECTRAL_SWORD_DAI_AURA,     // EntitySpectralSwordDAIAura
    /* 0x3F */ E_SPECTRAL_SWORD_WEAPON,       // EntitySpectralSwordWeapon
    /* 0x40 */ E_VALHALLA_KNIGHT,             // EntityValhallaKnight
    /* 0x41 */ E_VALHALLA_KNIGHT_UNK1,        // EntityValhallaKnightUnk1
    /* 0x42 */ E_VALHALLA_KNIGHT_UNK2,        // EntityValhallaKnightUnk2
    /* 0x43 */ E_SPECTRAL_SWORD_RDAI,         // EntitySpectralSwordRDAI
    /* 0x44 */ E_SPECTRAL_SWORD_RDAI_AURA,    // EntitySpectralSwordRDAIAura
    /* 0x45 */ E_SPEAR,                       // EntitySpear
    /* 0x46 */ E_SHIELD,                      // EntityShield
    /* 0x47 */ E_OROBOUROUS,                  // EntityOrobourous
    /* 0x48 */ E_OROB_SEGMENT,                // EntityOrobSegment
    /* 0x49 */ E_OROB_HEAD_PARTS,             // EntityOrobHeadParts
    /* 0x4A */ E_OROB_RIDER,                  // EntityOrobRider
    /* 0x4B */ E_OROB_HOLY_ATTACKER,          // EntityOrobHolyAttacker
    /* 0x4C */ E_DRAGON_RIDER,                // EntityDragonRider
    /* 0x4D */ E_DRAGON_SEGMENT,              // EntityDragonSegment
    /* 0x4E */ E_DRAGON_HEAD_PARTS,           // EntityDragonHeadParts
    /* 0x4F */ E_DRAGON_RIDER_HITBOX,         // EntityDragonRiderHitbox
    /* 0x50 */ E_VENUS_WEED_ROOT,             // EntityVenusWeed
    /* 0x51 */ E_VENUS_WEED_FLOWER,           // EntityVenusWeedFlower
    /* 0x52 */ E_VENUS_WEED_TENDRIL,          // EntityVenusWeedTendril
    /* 0x53 */ E_VENUS_WEED_DART,             // EntityVenusWeedDart
    /* 0x54 */ E_VENUS_WEED_SPIKE,            // EntityVenusWeedSpike
    /* 0x55 */ E_BOMB_KNIGHT,                 // EntityBombKnight
    /* 0x56 */ E_THROWN_BOMB,                 // EntityThrownBomb
    /* 0x57 */ E_BOMB_KNIGHT_DEATH_PARTS,     // EntityBombKnightDeathParts
    /* 0x58 */ E_BOMB_FUSE_SPARKS,            // EntityBombFuseSparks
    /* 0x59 */ E_THROWN_ROCK,                 // EntityThrownRock
    /* 0x5A */ E_ROCK_PIECE,                  // EntityRockPiece
    /* 0x5B */ E_BOMB_KNIGHT_ARM,             // EntityBombKnightArm
    /* 0x5C */ E_THORNWEED,                   // EntityThornweed
    /* 0x5D */ E_CORPSEWEED,                  // EntityCorpseweed
    /* 0x5E */ E_CORPSEWEED_PROJECTILE,       // EntityCorpseweedProjectile
    NUM_ENTITIES,
} EntityID;

#endif
