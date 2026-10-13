// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no2.h"

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
void func_us_801B5FB8(Entity* self);
void func_us_801B68EC(Entity* self);
void func_us_801B65A4(Entity* self);
void EntityBigRedFireball(Entity* self);
void EntityPrisoner(Entity* self);
void EntityOwlKnight(Entity* self);
void EntityOwl(Entity* self);
void EntityOwlKnightSword(Entity* self);
void EntityOwlTarget(Entity* self);
void EntityBloodyZombie(Entity* self);
void EntityBloodDrips(Entity* self);
void EntityBloodSplatter(Entity* self);
void func_us_801B72E8(Entity* self);
void EntitySpikesDamage(Entity* self);
void func_us_801B7580(Entity* self);
void EntitySealedDoor(Entity* self);
void EntityValhallaKnight(Entity* self);
void func_us_801C8954(Entity* self);
void func_us_801C8AAC(Entity* self);
void EntityHammer(Entity* self);
void EntityGurkhaBodyParts(Entity* self);
void EntityHammerWeapon(Entity* self);
void EntityGurkha(Entity* self);
void EntityGurkhaWeapon(Entity* self);
void EntityBlade(Entity* self);
void EntityBladeWeapon(Entity* self);
void EntitySpectralSword(Entity* self);
void EntitySpectralSwordAura(Entity* self);
void EntityPoltergeist(Entity* self);
void EntityBreakableDebris(Entity* self);

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
    func_us_801B5FB8,
    func_us_801B68EC,
    func_us_801B65A4,
    EntityBigRedFireball,
    EntityPrisoner,
    EntityOwlKnight,
    EntityOwl,
    EntityOwlKnightSword,
    EntityOwlTarget,
    EntityBloodyZombie,
    EntityBloodDrips,
    EntityBloodSplatter,
    func_us_801B72E8,
    EntitySpikesDamage,
    func_us_801B7580,
    EntitySealedDoor,
    EntityValhallaKnight,
    func_us_801C8954,
    func_us_801C8AAC,
    EntityHammer,
    EntityGurkhaBodyParts,
    EntityHammerWeapon,
    EntityGurkha,
    EntityGurkhaWeapon,
    EntityBlade,
    EntityBladeWeapon,
    EntitySpectralSword,
    EntitySpectralSwordAura,
    EntityPoltergeist,
    EntityBreakableDebris,
};

// clang-format off
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
EInit g_EInitOwlKnight = {ANIMSET_OVL(8), 0x10, 0x49, PAL_OWL_KNIGHT, ENEMY_OWL_KNIGHT};
EInit g_EInitOwlKnightSword = {ANIMSET_OVL(8), 0x00, 0x49, PAL_OWL_KNIGHT_SWORD, ENEMY_OWL_KNIGHT_SWORD};
EInit g_EInitOwl = {ANIMSET_OVL(8), 0x01, 0x49, PAL_OWL_KNIGHT, ENEMY_OWL};
EInit g_EInitBloodyZombie = {ANIMSET_OVL(9), 0x01, 0x4A, PAL_BLOODY_ZOMBIE, ENEMY_BLOODY_ZOMBIE};
EInit D_us_801808EC = {ANIMSET_OVL(2), 0x0E, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitValhallaKnight = {ANIMSET_OVL(5), 0x01, 0x4C, PAL_VALHALLA_KNIGHT, ENEMY_VALHALLA_KNIGHT};
EInit g_EInitValhallaKnightUnk1 = {ANIMSET_OVL(5), 0x01, 0x4C, PAL_VALHALLA_KNIGHT, ENEMY_COMMON};
EInit g_EInitValhallaKnightUnk2 = {ANIMSET_OVL(0), 0x00, 0x00, PAL_NONE, ENEMY_VALHALLA_KNIGHT_UNK2};
EInit g_EInitValhallaKnightUnk3 = {ANIMSET_OVL(0), 0x00, 0x00, PAL_NONE, ENEMY_VALHALLA_KNIGHT_UNK3};
EInit g_EInitHammer = {ANIMSET_OVL(6), 0x02, 0x4C, PAL_UNK_23E, ENEMY_HAMMER};
EInit g_EInitHammerWeapon = {ANIMSET_OVL(6), 0x12, 0x4C, PAL_UNK_23E, ENEMY_HAMMER_WEAPON};
EInit g_EInitGurkha = {ANIMSET_OVL(6), 0x02, 0x4C, PAL_GURKHA, ENEMY_GURKHA};
EInit g_EInitGurkhaWeapon = {ANIMSET_OVL(6), 0x14, 0x4C, PAL_GURKHA, ENEMY_GURKHA_WEAPON};
EInit g_EInitBlade = {ANIMSET_OVL(6), 0x02, 0x4C, PAL_BLADE, ENEMY_BLADE};
EInit g_EInitBladeWeapon = {ANIMSET_OVL(6), 0x13, 0x4C, PAL_BLADE, ENEMY_BLADE_WEAPON};
EInit g_EInitSpectralSword = {ANIMSET_OVL(4), 0x00, 0x50, PAL_SPECTRAL_SWORD, ENEMY_SPECTRAL_SWORD_NO2};
EInit g_EInitSpectralSwordAura = {ANIMSET_OVL(4), 0x00, 0x50, PAL_SPECTRAL_SWORD, ENEMY_PARTICLE};
EInit g_EInitPoltergeist = {ANIMSET_OVL(4), 0x00, 0x50, PAL_SPECTRAL_SWORD, ENEMY_POLTERGEIST};
