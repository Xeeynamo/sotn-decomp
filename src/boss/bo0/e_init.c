// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo0.h"

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
void EntityMessageBox(Entity* self);
void EntityDummy(Entity* self);
void EntityBackgroundBlock(Entity* self);
void EntityLockCamera(Entity* self);
void EntityUnkId13(Entity* self);
void EntityExplosionVariants(Entity* self);
void EntityGreyPuff(Entity* self);
void EntitySkelerang(Entity* self);
void EntitySkelerangBoomerang(Entity* self);
void EntitySkelerangUnknown(Entity* self);
void func_us_801B3D8C(Entity* self);
void func_us_801B3F30(Entity* self);
void func_us_801B4148(Entity* self);
void func_us_801B41A4(Entity* self);
void func_us_801B4210(Entity* self);
void Entity3DBackgroundHouse(Entity* self);
void Entity3DHouseSpawner(Entity* self);
void func_us_801B4DA4(Entity* self);
void EntitySpikes(Entity* self);
void EntitySpikesParts(Entity* self);
void EntitySpikesDust(Entity* self);
void EntitySecretWall(Entity* self);
void EntitySecretCeiling(Entity* self);
void EntitySecretWallDebris(Entity* self);
void EntityMarionette(Entity* self);
void EntityBigRedFireball(Entity* self);
void EntityPrisoner(Entity* self);
void func_us_801B001C(Entity* self);
void func_us_801AD338(Entity* self);
void EntityOlroxAfterImage(Entity* self);
void func_us_801AFAF4(Entity* self);
void func_us_801AF8C0(Entity* self);
void func_us_801AF604(Entity* self);
void func_us_801AF31C(Entity* self);
void func_us_801AE858(Entity* self);
void func_us_801B0930(Entity* self);
void func_us_801B365C(Entity* self);
void func_us_801B5470(Entity* self);
void func_us_801B551C(Entity* self);
void func_us_801B619C(Entity* self);
void func_us_801B6CA4(Entity* self);
void func_us_801B76E4(Entity* self);
void EntityLaserAttack(Entity* self);
void EntityFireballAttack(Entity* self);
void func_us_801B7BAC(Entity* self);
void func_us_801B7CC8(Entity* self);
void EntityRealOlroxDrool(Entity* self);
void func_us_801BA4AC(Entity* self);
void EntityLifeUpSpawn(Entity* self);
void EntityOwlKnight(Entity* self);
void EntityOwl(Entity* self);
void EntityOwlKnightSword(Entity* self);
void EntityOwlTarget(Entity* self);
void EntityBloodyZombie(Entity* self);
void EntityBloodDrips(Entity* self);
void EntityBloodSplatter(Entity* self);
void func_us_801B72E8(Entity* self);
void EntitySpikesDamage(Entity* self);
void EntityBossDoors(Entity* self);
void EntitySealedDoor(Entity* self);
void EntityChair(Entity* self);

PfnEntityUpdate EntityUpdates[] = {
    EntityBreakable,
    EntityExplosion,
    EntityPrizeDrop,
    EntityDamageDisplay,
    EntityRedDoor,
    EntityIntenseExplosion,
    EntitySoulStealOrb,
    EntityRoomForeground,
    EntityStageNamePopup,
    EntityEquipItemDrop,
    EntityRelicOrb,
    EntityPersistentItemDrop,
    EntityEnemyBlood,
    EntityMessageBox,
    EntityDummy,
    EntityDummy,
    EntityBackgroundBlock,
    EntityLockCamera,
    EntityUnkId13,
    EntityExplosionVariants,
    EntityGreyPuff,
    EntitySkelerang,
    EntitySkelerangBoomerang,
    EntitySkelerangUnknown,
    func_us_801B3D8C,
    func_us_801B3F30,
    func_us_801B4148,
    func_us_801B41A4,
    func_us_801B4210,
    Entity3DBackgroundHouse,
    Entity3DHouseSpawner,
    func_us_801B4DA4,
    EntitySpikes,
    EntitySpikesParts,
    EntitySpikesDust,
    EntitySecretWall,
    EntitySecretCeiling,
    EntitySecretWallDebris,
    EntityMarionette,
    EntityBigRedFireball,
    EntityPrisoner,
    func_us_801B001C,
    func_us_801AD338,
    EntityOlroxAfterImage,
    func_us_801AFAF4,
    func_us_801AF8C0,
    func_us_801AF604,
    func_us_801AF31C,
    func_us_801AE858,
    func_us_801B0930,
    func_us_801B365C,
    func_us_801B5470,
    func_us_801B551C,
    func_us_801B619C,
    func_us_801B6CA4,
    func_us_801B76E4,
    EntityLaserAttack,
    EntityFireballAttack,
    func_us_801B7BAC,
    func_us_801B7CC8,
    EntityRealOlroxDrool,
    func_us_801BA4AC,
    EntityLifeUpSpawn,
    EntityOwlKnight,
    EntityOwl,
    EntityOwlKnightSword,
    EntityOwlTarget,
    EntityBloodyZombie,
    EntityBloodDrips,
    EntityBloodSplatter,
    func_us_801B72E8,
    EntitySpikesDamage,
    EntityBossDoors,
    EntitySealedDoor,
    EntityChair,
};

// clang-format off
// animSet, animCurFrame, unk5A, palette, enemyID
EInit g_EInitBreakable = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_BREAKABLE};
EInit g_EInitObtainable = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_OBTAINABLE};
EInit g_EInitParticle = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit g_EInitSpawner = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_SPAWNER};
EInit g_EInitInteractable = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit g_EInitLockCamera = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_OBTAINABLE};
EInit g_EInitCommon = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit g_EInitDamageNum = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit g_EInitSkelerang = {ANIMSET_OVL(1), 0x01, 0x48, PAL_SKELERANG, ENEMY_SKELERANG};
EInit g_EInitSkelerangBoomerang = {ANIMSET_OVL(1), 0x2B, 0x48, PAL_SKELERANG, ENEMY_SKELERANG_BOOMERANG};
EInit g_EInitEnvironment = {ANIMSET_OVL(2), 0x0B, 0x00, PAL_NONE, ENEMY_COMMON};
EInit g_EInitPrisoner = {ANIMSET_OVL(3), 0x01, 0x49, PAL_UNK_203, ENEMY_COMMON};
EInit g_EInitMarionette = {ANIMSET_OVL(4), 0x00, 0x48, PAL_UNK_205, ENEMY_MARIONETTE};
EInit g_EInitOwlKnight = {ANIMSET_OVL(8), 0x10, 0x49, PAL_OWL_KNIGHT, ENEMY_OWL_KNIGHT};
EInit g_EInitOwlKnightSword = {ANIMSET_OVL(8), 0x00, 0x49, PAL_OWL_KNIGHT_SWORD, ENEMY_OWL_KNIGHT_SWORD};
EInit g_EInitOwl = {ANIMSET_OVL(8), 0x01, 0x49, PAL_OWL_KNIGHT, ENEMY_OWL};
EInit g_EInitBloodyZombie = {ANIMSET_OVL(9), 0x01, 0x48, PAL_BLOODY_ZOMBIE, ENEMY_BLOODY_ZOMBIE};
EInit g_EInitOlroxAfterImage = {ANIMSET_OVL(6), 0x01, 0x48, PAL_UNK_209, ENEMY_OLROX};
EInit D_us_801806D8 = {ANIMSET_OVL(6), 0x3A, 0x48, PAL_UNK_209, ENEMY_OLROX_UNK_33};
EInit D_us_801806E4 = {ANIMSET_OVL(6), 0x50, 0x48, PAL_UNK_209, ENEMY_OLROX_UNK_34};
EInit D_us_801806F0 = {ANIMSET_OVL(6), 0x3F, 0x48, PAL_UNK_209, ENEMY_OLROX_UNK_35};
EInit D_us_801806FC = {ANIMSET_OVL(0), 0x00, 0x00, PAL_NONE, ENEMY_OLROX_UNK_36};
EInit D_us_80180708 = {ANIMSET_OVL(7), 0x01, 0x50, PAL_UNK_20B, ENEMY_OLROX_2};
EInit D_us_80180714 = {ANIMSET_OVL(7), 0x01, 0x50, PAL_UNK_20B, ENEMY_OLROX_UNK_38};
EInit g_EInitLaserAttack = {ANIMSET_OVL(0), 0x00, 0x00, PAL_NONE, ENEMY_OLROX_UNK_3C};
EInit g_EInitFireballAttack = {ANIMSET_OVL(9), 0x01, 0x00, PAL_NONE, ENEMY_OLROX_UNK_3B};
EInit g_EInitBossDoors = {ANIMSET_OVL(2), 0x0E, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
// clang-format on
