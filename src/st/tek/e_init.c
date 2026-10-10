// SPDX-License-Identifier: AGPL-3.0-or-later
#include "tek.h"

void EntityBreakable(Entity* self);
void EntityExplosion(Entity* self);
void EntityPrizeDrop(Entity* self);
void EntityDamageDisplay(Entity* self);
void EntityRedDoor(Entity* self);
void EntityIntenseExplosion(Entity* self);
void EntitySoulStealOrb(Entity* self);
void EntityRoomForeground(Entity* self);
void EntityStageNamePopup(Entity* self);
void EntityEquipItemDrop(Entity* self);
void EntityRelicOrb(Entity* self);
void EntityPersistentItemDrop(Entity* self);
void EntityEnemyBlood(Entity* self);
void EntityDummy(Entity* self);
void EntityBackgroundBlock(Entity* self);
void EntityLockCamera(Entity* self);
void EntityUnkId13(Entity* self);
void EntityExplosionVariants(Entity* self);
void EntityGreyPuff(Entity* self);
void EntityDodoBird(Entity* self);
void EntityBoneScimitar(Entity* self);
void EntityBoneScimitarParts(Entity* self);
void EntityToad(Entity* self);
void EntityFrog(Entity* self);
void EntityBoneArcher(Entity* self);
void EntityBoneArcherArrow(Entity* self);
void EntityGraveKeeper(Entity* self);
void EntityGraveKeeperHitbox(Entity* self);
void EntityTombstone(Entity* self);
void EntityBlackCrow(Entity* self);
void EntityBlueRaven(Entity* self);
void EntityJackOBones(Entity* self);
void EntityJackOBonesPieces(Entity* self);
void EntityJackOBonesJack(Entity* self);
void EntityBoneHalberd(Entity* self);
void EntityBoneHalberdAttack(Entity* self);
void EntityBoneHalberdPieces(Entity* self);
void EntityYorick(Entity* self);
void EntityYorickSkull(Entity* self);
void EntityYorickPieces(Entity* self);
void EntityBladeMaster(Entity* self);
void EntityBladeMasterAttackHitbox(Entity* self);
void EntityBladeMasterDeathParts(Entity* self);
void EntityBladeMasterDeathExplosion(Entity* self);
void EntityBladeSoldier(Entity* self);
void EntityBladeSoldierAttackHitbox(Entity* self);
void EntityBladeSoldierDeathParts(Entity* self);
void EntityNovaSkeleton(Entity* self);
void EntityNovaLaser(Entity* self);
void EntityNovaLaserPulse(Entity* self);
void EntityNovaSkeletonPieces(Entity* self);
void EntityBoneMusket(Entity* self);
void EntityBoneMusketUnk(Entity* self);
void EntityWingedGuard(Entity* self);
void EntityWingedGuardParts(Entity* self);
void EntitySpectralSwordNO2(Entity* self);
void EntitySpectralSwordNO2Aura(Entity* self);
void EntityPoltergeist(Entity* self);
void EntitySpectralSwordDAI(Entity* self);
void EntitySpectralSwordDAIAura(Entity* self);
void EntitySpectralSwordWeapon(Entity* self);
void EntityValhallaKnight(Entity* self);
void EntityValhallaKnightUnk1(Entity* self);
void EntityValhallaKnightUnk2(Entity* self);
void EntitySpectralSwordRDAI(Entity* self);
void EntitySpectralSwordRDAIAura(Entity* self);
void EntitySpear(Entity* self);
void EntityShield(Entity* self);
void EntityOrobourous(Entity* self);
void EntityOrobSegment(Entity* self);
void EntityOrobHeadParts(Entity* self);
void EntityOrobRider(Entity* self);
void EntityOrobHolyAttacker(Entity* self);
void EntityDragonRider(Entity* self);
void EntityDragonSegment(Entity* self);
void EntityDragonHeadParts(Entity* self);
void EntityDragonRiderHitbox(Entity* self);
void EntityVenusWeed(Entity* self);
void EntityVenusWeedFlower(Entity* self);
void EntityVenusWeedTendril(Entity* self);
void EntityVenusWeedDart(Entity* self);
void EntityVenusWeedSpike(Entity* self);
void EntityBombKnight(Entity* self);
void EntityThrownBomb(Entity* self);
void EntityBombKnightDeathParts(Entity* self);
void EntityBombFuseSparks(Entity* self);
void EntityThrownRock(Entity* self);
void EntityRockPiece(Entity* self);
void EntityBombKnightArm(Entity* self);
void EntityThornweed(Entity* self);
void EntityCorpseweed(Entity* self);
void EntityCorpseweedProjectile(Entity* self);

PfnEntityUpdate EntityUpdates[] = {
    /* 0x01 */ EntityBreakable,
    /* 0x02 */ EntityExplosion,
    /* 0x03 */ EntityPrizeDrop,
    /* 0x04 */ EntityDamageDisplay,
    /* 0x05 */ EntityRedDoor,
    /* 0x06 */ EntityIntenseExplosion,
    /* 0x07 */ EntitySoulStealOrb,
    /* 0x08 */ EntityRoomForeground,
    /* 0x09 */ EntityStageNamePopup,
    /* 0x0A */ EntityEquipItemDrop,
    /* 0x0B */ EntityRelicOrb,
    /* 0x0C */ EntityPersistentItemDrop,
    /* 0x0D */ EntityEnemyBlood,
    /* 0x0E */ EntityDummy,
    /* 0x0F */ EntityDummy,
    /* 0x10 */ EntityDummy,
    /* 0x11 */ EntityBackgroundBlock,
    /* 0x12 */ EntityLockCamera,
    /* 0x13 */ EntityUnkId13,
    /* 0x14 */ EntityExplosionVariants,
    /* 0x15 */ EntityGreyPuff,
    /* 0x16 */ EntityDodoBird,
    /* 0x17 */ EntityBoneScimitar,
    /* 0x18 */ EntityBoneScimitarParts,
    /* 0x19 */ EntityToad,
    /* 0x1A */ EntityFrog,
    /* 0x1B */ EntityBoneArcher,
    /* 0x1C */ EntityBoneArcherArrow,
    /* 0x1D */ EntityGraveKeeper,
    /* 0x1E */ EntityGraveKeeperHitbox,
    /* 0x1F */ EntityTombstone,
    /* 0x20 */ EntityBlackCrow,
    /* 0x21 */ EntityBlueRaven,
    /* 0x22 */ EntityJackOBones,
    /* 0x23 */ EntityJackOBonesPieces,
    /* 0x24 */ EntityJackOBonesJack,
    /* 0x25 */ EntityBoneHalberd,
    /* 0x26 */ EntityBoneHalberdAttack,
    /* 0x27 */ EntityBoneHalberdPieces,
    /* 0x28 */ EntityYorick,
    /* 0x29 */ EntityYorickSkull,
    /* 0x2A */ EntityYorickPieces,
    /* 0x2B */ EntityBladeMaster,
    /* 0x2C */ EntityBladeMasterAttackHitbox,
    /* 0x2D */ EntityBladeMasterDeathParts,
    /* 0x2E */ EntityBladeMasterDeathExplosion,
    /* 0x2F */ EntityBladeSoldier,
    /* 0x30 */ EntityBladeSoldierAttackHitbox,
    /* 0x31 */ EntityBladeSoldierDeathParts,
    /* 0x32 */ EntityNovaSkeleton,
    /* 0x33 */ EntityNovaLaser,
    /* 0x34 */ EntityNovaLaserPulse,
    /* 0x35 */ EntityNovaSkeletonPieces,
    /* 0x36 */ EntityBoneMusket,
    /* 0x37 */ EntityBoneMusketUnk,
    /* 0x38 */ EntityWingedGuard,
    /* 0x39 */ EntityWingedGuardParts,
    /* 0x3A */ EntitySpectralSwordNO2,
    /* 0x3B */ EntitySpectralSwordNO2Aura,
    /* 0x3C */ EntityPoltergeist,
    /* 0x3D */ EntitySpectralSwordDAI,
    /* 0x3E */ EntitySpectralSwordDAIAura,
    /* 0x3F */ EntitySpectralSwordWeapon,
    /* 0x40 */ EntityValhallaKnight,
    /* 0x41 */ EntityValhallaKnightUnk1,
    /* 0x42 */ EntityValhallaKnightUnk2,
    /* 0x43 */ EntitySpectralSwordRDAI,
    /* 0x44 */ EntitySpectralSwordRDAIAura,
    /* 0x45 */ EntitySpear,
    /* 0x46 */ EntityShield,
    /* 0x47 */ EntityOrobourous,
    /* 0x48 */ EntityOrobSegment,
    /* 0x49 */ EntityOrobHeadParts,
    /* 0x4A */ EntityOrobRider,
    /* 0x4B */ EntityOrobHolyAttacker,
    /* 0x4C */ EntityDragonRider,
    /* 0x4D */ EntityDragonSegment,
    /* 0x4E */ EntityDragonHeadParts,
    /* 0x4F */ EntityDragonRiderHitbox,
    /* 0x50 */ EntityVenusWeed,
    /* 0x51 */ EntityVenusWeedFlower,
    /* 0x52 */ EntityVenusWeedTendril,
    /* 0x53 */ EntityVenusWeedDart,
    /* 0x54 */ EntityVenusWeedSpike,
    /* 0x55 */ EntityBombKnight,
    /* 0x56 */ EntityThrownBomb,
    /* 0x57 */ EntityBombKnightDeathParts,
    /* 0x58 */ EntityBombFuseSparks,
    /* 0x59 */ EntityThrownRock,
    /* 0x5A */ EntityRockPiece,
    /* 0x5B */ EntityBombKnightArm,
    /* 0x5C */ EntityThornweed,
    /* 0x5D */ EntityCorpseweed,
    /* 0x5E */ EntityCorpseweedProjectile,
};

// clang-format off
EInit D_80180950 = {ANIMSET_DRA(0x03), 0x00, 0x00, PAL_NONE, ENEMY_BREAKABLE};
EInit D_8018095C = {ANIMSET_DRA(0x03), 0x00, 0x00, PAL_NONE, ENEMY_OBTAINABLE};
EInit D_80180968 = {ANIMSET_DRA(0x03), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit D_80180974 = {ANIMSET_DRA(0x00), 0x00, 0x00, PAL_NONE, ENEMY_SPAWNER};
EInit D_80180980 = {ANIMSET_DRA(0x00), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit D_8018098C = {ANIMSET_DRA(0x02), 0x00, 0x00, PAL_NONE, ENEMY_WHITE_DRAGON_FLAME_BREATH};
EInit D_80180998 = {ANIMSET_OVL(0x05), 0x00, 0x24, PAL_NONE, ENEMY_COMMON};
EInit D_801809A4 = {ANIMSET_DRA(0x02), 0x00, 0x48, PAL_NONE, ENEMY_LOCK_CAMERA_VARIANT};
EInit D_801809B0 = {ANIMSET_DRA(0x03), 0x00, 0x48, PAL_NONE, ENEMY_UNK_5C};
EInit D_801809BC = {ANIMSET_DRA(0x00), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit D_801809C8 = {ANIMSET_DRA(0x00), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit D_801809D4 = {ANIMSET_DRA(0x00), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit D_801809E0 = {ANIMSET_DRA(0x00), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit D_801809EC = {ANIMSET_OVL(0x01), 0x01, 0x48, PAL_DODO_BIRD, ENEMY_DODO_BIRD};
EInit D_801809F8 = {ANIMSET_OVL(0x02), 0x01, 0x49, PAL_BONE_SCIMITAR, ENEMY_BONE_SCIMITAR};
EInit D_80180A04 = {ANIMSET_OVL(0x02), 0x00, 0x49, PAL_BONE_SCIMITAR, ENEMY_PARTICLE};
EInit D_80180A10 = {ANIMSET_OVL(0x03), 0x01, 0x4A, PAL_TOAD_FROG, ENEMY_TOAD};
EInit D_80180A1C = {ANIMSET_OVL(0x04), 0x01, 0x4B, PAL_BONE_ARCHER, ENEMY_BONE_ARCHER};
EInit D_80180A28 = {ANIMSET_OVL(0x04), 0x01, 0x4B, PAL_BONE_ARCHER, ENEMY_BONE_ARCHER_ARROW};
EInit D_80180A34 = {ANIMSET_OVL(0x06), 0x01, 0x4D, PAL_GRAVE_KEEPER_TOMBSTONE, ENEMY_GRAVE_KEEPER};
EInit D_80180A40 = {ANIMSET_OVL(0x00), 0x00, 0x00, PAL_NONE, ENEMY_GRAVE_KEEPER_HITBOX};
EInit D_80180A4C = {ANIMSET_OVL(0x06), 0x15, 0x4D, PAL_GRAVE_KEEPER_TOMBSTONE, ENEMY_TOMBSTONE};
EInit D_80180A58 = {ANIMSET_OVL(0x07), 0x00, 0x4F, PAL_CROW, ENEMY_BLUE_RAVEN};
EInit D_80180A64 = {ANIMSET_OVL(0x08), 0x01, 0x50, PAL_JACK_O_BONES, ENEMY_JACK_O_BONES};
EInit D_80180A70 = {ANIMSET_OVL(0x08), 0x00, 0x50, PAL_JACK_O_BONES, ENEMY_PARTICLE};
EInit D_80180A7C = {ANIMSET_OVL(0x08), 0x15, 0x50, PAL_JACK_O_BONES, ENEMY_JACK_O_BONES_3};
EInit D_80180A88 = {ANIMSET_OVL(0x09), 0x01, 0x58, PAL_BONE_HALBERD, ENEMY_BONE_HALBERD};
EInit D_80180A94 = {ANIMSET_OVL(0x00), 0x00, 0x00, PAL_DODO_BIRD, ENEMY_BONE_HALBERD_ATTACK};
EInit D_80180AA0 = {ANIMSET_OVL(0x0A), 0x01, 0x56, PAL_YORICK, ENEMY_YORICK};
EInit D_80180AAC = {ANIMSET_OVL(0x0A), 0x1E, 0x56, PAL_YORICK, ENEMY_YORICK_SKULL};
EInit D_80180AB8 = {ANIMSET_OVL(0x0B), 0x01, 0x51, PAL_BLADE_MASTER, ENEMY_BLADE_MASTER};
EInit D_80180AC4 = {ANIMSET_OVL(0x00), 0x00, 0x00, PAL_NONE, ENEMY_BLADE_MASTER_ATTACK_HITBOX};
EInit D_80180AD0 = {ANIMSET_OVL(0x0C), 0x01, 0x57, PAL_BLADE_SOLDIER, ENEMY_BLADE_SOLDIER};
EInit D_80180ADC = {ANIMSET_OVL(0x00), 0x00, 0x00, PAL_NONE, ENEMY_BLADE_SOLDIER_ATTACK_HITBOX};
EInit D_80180AE8 = {ANIMSET_OVL(0x0D), 0x01, 0x48, PAL_NOVA_SKELETON, ENEMY_NOVA_SKELETON};
EInit D_80180AF4 = {ANIMSET_OVL(0x0E), 0x00, 0x52, PAL_BONE_MUSKET, ENEMY_BONE_MUSKET};
EInit D_80180B00 = {ANIMSET_OVL(0x0E), 0x00, 0x52, PAL_BONE_MUSKET, ENEMY_UNK_67};
EInit D_80180B0C = {ANIMSET_OVL(0x0F), 0x00, 0x49, PAL_WINGED_GUARD, ENEMY_WINGED_GUARD};
EInit D_80180B18 = {ANIMSET_OVL(0x0F), 0x00, 0x49, PAL_WINGED_GUARD, ENEMY_COMMON};
EInit D_80180B24 = {ANIMSET_OVL(0x18), 0x00, 0x50, PAL_SPECTRAL_SWORD, ENEMY_SPECTRAL_SWORD_NO2};
EInit D_80180B30 = {ANIMSET_OVL(0x18), 0x00, 0x50, PAL_SPECTRAL_SWORD, ENEMY_POLTERGEIST};
EInit D_80180B3C = {ANIMSET_OVL(0x19), 0x00, 0x51, PAL_SPECTRAL_SWORD, ENEMY_SPECTRAL_SWORD_DAI};
EInit D_80180B48 = {ANIMSET_OVL(0x19), 0x00, 0x51, PAL_SPECTRAL_SWORD_WEAPON, ENEMY_SPECTRAL_SWORD_WEAPON};
EInit D_80180B54 = {ANIMSET_OVL(0x19), 0x00, 0x51, PAL_SPECTRAL_SWORD_WEAPON, ENEMY_SPECTRAL_SWORD_RDAI};
EInit D_80180B60 = {ANIMSET_OVL(0x19), 0x00, 0x51, PAL_SPECTRAL_SWORD_WEAPON, ENEMY_SPEAR};
EInit D_80180B6C = {ANIMSET_OVL(0x19), 0x00, 0x51, PAL_SPECTRAL_SWORD_WEAPON, ENEMY_SHIELD};
EInit D_80180B78 = {ANIMSET_OVL(0x1A), 0x01, 0x48, PAL_VALHALLA_KNIGHT, ENEMY_VALHALLA_KNIGHT};
EInit D_80180B84 = {ANIMSET_OVL(0x1A), 0x01, 0x48, PAL_VALHALLA_KNIGHT, ENEMY_COMMON};
EInit D_80180B90 = {ANIMSET_OVL(0x00), 0x00, 0x00, PAL_NONE, ENEMY_VALHALLA_KNIGHT_UNK2};
EInit D_80180B9C = {ANIMSET_OVL(0x00), 0x00, 0x00, PAL_NONE, ENEMY_VALHALLA_KNIGHT_UNK3};
EInit D_80180BA8 = {ANIMSET_OVL(0x1B), 0x01, 0x51, PAL_OROBOUROUS, ENEMY_OROBOUROUS};
EInit D_80180BB4 = {ANIMSET_OVL(0x1B), 0x04, 0x51, PAL_OROBOUROUS, ENEMY_ORUBUROS};
EInit D_80180BC0 = {ANIMSET_OVL(0x1B), 0x04, 0x50, PAL_OROBOUROUS, ENEMY_PARTICLE};
EInit D_80180BCC = {ANIMSET_OVL(0x1B), 0x04, 0x50, PAL_OROBOUROUS, ENEMY_ORUBUROS_RIDER};
EInit D_80180BD8 = {ANIMSET_OVL(0x1B), 0x01, 0x50, PAL_DRAGON_RIDER, ENEMY_DRAGON_RIDER_1};
EInit D_80180BE4 = {ANIMSET_OVL(0x1B), 0x04, 0x50, PAL_DRAGON_RIDER, ENEMY_DRAGON_RIDER_2};
EInit D_80180BF0 = {ANIMSET_OVL(0x1B), 0x04, 0x50, PAL_DRAGON_RIDER, ENEMY_PARTICLE};
EInit D_80180BFC = {ANIMSET_OVL(0x1E), 0x00, 0x4C, PAL_THORNWEED_CORPSEWEED, ENEMY_THORNWEED};
EInit D_80180C08 = {ANIMSET_OVL(0x1E), 0x00, 0x4C, PAL_THORNWEED_CORPSEWEED, ENEMY_CORPSEWEED_UNUSED};
EInit D_80180C14 = {ANIMSET_OVL(0x1E), 0x00, 0x4C, PAL_THORNWEED_CORPSEWEED, ENEMY_CORPSEWEED};
EInit D_80180C20 = {ANIMSET_OVL(0x1E), 0x00, 0x4C, PAL_THORNWEED_CORPSEWEED, ENEMY_CORPSEWEED_PROJECTILE};
EInit D_80180C2C = {ANIMSET_OVL(0x1F), 0x00, 0x50, PAL_VENUS_WEED, ENEMY_VENUS_WEED_ROOT};
EInit D_80180C38 = {ANIMSET_OVL(0x1F), 0x00, 0x50, PAL_VENUS_WEED, ENEMY_VENUS_WEED_FLOWER};
EInit D_80180C44 = {ANIMSET_OVL(0x1F), 0x00, 0x50, PAL_VENUS_WEED, ENEMY_VENUS_WEED_TENDRIL};
EInit D_80180C50 = {ANIMSET_OVL(0x1F), 0x37, 0x50, PAL_VENUS_WEED, ENEMY_VENUS_WEED_DART};
EInit D_80180C5C = {ANIMSET_OVL(0x1C), 0x01, 0x48, PAL_BOMB_KNIGHT, ENEMY_BOMB_KNIGHT};
EInit D_80180C68 = {ANIMSET_OVL(0x1C), 0x24, 0x48, PAL_BOMB_KNIGHT, ENEMY_BOMB};
EInit D_80180C74 = {ANIMSET_OVL(0x1C), 0x00, 0x48, PAL_BOMB_KNIGHT, ENEMY_PARTICLE};
EInit D_80180C80 = {ANIMSET_OVL(0x1C), 0x41, 0x48, PAL_BOMB_KNIGHT, ENEMY_ROCK};
